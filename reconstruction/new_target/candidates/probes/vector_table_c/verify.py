#!/usr/bin/env python3
"""Strictly rebuild the C vector-table data block from its pinned manifest."""
import hashlib
import json
import os
from pathlib import Path
import subprocess

HERE = Path(__file__).resolve().parent
CASE = HERE.parents[2]
BASE = 0x08000000
TC = Path(os.environ.get("ARM_TC", str(Path.home() / ".local/opt/gnu-tools-for-stm32-13.3.rel1")))
GCC, LD, OBJCOPY = (TC / "bin" / f"arm-none-eabi-{tool}" for tool in ("gcc", "ld", "objcopy"))


def compare(actual: bytes, expected: bytes) -> int | None:
    if len(actual) == len(expected) and actual == expected:
        return None
    return next((i for i, (a, b) in enumerate(zip(actual, expected)) if a != b), min(len(actual), len(expected)))


def self_test() -> None:
    expected = b"abcd"
    assert compare(expected, expected) is None
    for bad in (b"abce", b"abc", b"abcde", b""):
        assert compare(bad, expected) is not None


def main() -> int:
    self_test()
    manifest = json.loads((CASE / "evidence/data_manifest.json").read_text())
    if manifest["target_sha256"] != "5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752":
        raise SystemExit("FAIL: data manifest target identity changed")
    if int(manifest["base_address"], 0) != BASE:
        raise SystemExit("FAIL: unexpected data manifest base")
    verifier = "candidates/probes/vector_table_c/verify.py"
    blocks = [item for item in manifest["blocks"] if item["verifier"] == verifier]
    if len(blocks) != 1:
        raise SystemExit("FAIL: expected exactly one vector-table block")
    block = blocks[0]
    address, size = int(block["address"], 0), int(block["size"])
    target = (CASE.parents[1] / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
    digest = hashlib.sha256(target).hexdigest()
    if digest != manifest["target_sha256"]:
        raise SystemExit(f"FAIL: target identity changed: {digest}")
    if address < BASE or address + size > BASE + len(target):
        raise SystemExit("FAIL: vector table range outside target")
    source = CASE / block["source"]
    source_hash = hashlib.sha256(source.read_bytes()).hexdigest()
    if source_hash != block["source_sha256"]:
        raise SystemExit(f"FAIL: source identity changed: {source_hash}")

    build = (CASE / block["binary"]).parent
    build.mkdir(parents=True, exist_ok=True)
    obj, elf, binary, script = (build / name for name in ("vectors.o", "vectors.elf", "vector_table.bin", "link.ld"))
    subprocess.run([str(GCC), *block["compiler_flags"], "-c", str(source), "-o", str(obj)], check=True)
    section = block["section"]
    script.write_text(f"SECTIONS {{ {section} {address:#x} : {{ KEEP(*({section})) }} /DISCARD/ : {{ *(*) }} }}\n")
    subprocess.run([str(LD), *[f"--defsym={symbol}" for symbol in block["defsyms"]], "-T", str(script), str(obj), "-o", str(elf)], check=True)
    subprocess.run([str(OBJCOPY), "-O", "binary", f"--only-section={section}", str(elf), str(binary)], check=True)
    actual = binary.read_bytes()
    expected = target[address - BASE:address - BASE + size]
    mismatch = compare(actual, expected)
    if mismatch is not None:
        print(f"FAIL {block['name']}: first difference +{mismatch:#x} at {address + mismatch:#010x}; emitted {len(actual)} B, expected {len(expected)} B")
        return 1
    print(f"PASS {block['name']}: exact {size} bytes at {address:#010x}–{address + size - 1:#010x} (target sha256 {digest})")
    print(f"binary sha256 {hashlib.sha256(actual).hexdigest()}")
    print(subprocess.check_output([str(GCC), "--version"], text=True).splitlines()[0])
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
