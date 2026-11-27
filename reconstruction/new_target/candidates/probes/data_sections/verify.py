#!/usr/bin/env python3
"""Build and strictly compare C data sections reused from the prior reconstruction."""
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


def main() -> int:
    manifest = json.loads((CASE / "evidence/data_manifest.json").read_text())
    target = (CASE.parents[1] / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
    if hashlib.sha256(target).hexdigest() != manifest["target_sha256"]:
        raise SystemExit("FAIL: target hash mismatch")
    relative_verifier = Path(__file__).resolve().relative_to(CASE).as_posix()
    blocks = [item for item in manifest["blocks"] if item["verifier"] == relative_verifier]
    if not blocks:
        raise SystemExit("FAIL: no data blocks assigned to this verifier")
    sources = {item["source"] for item in blocks}
    flags = {tuple(item["compiler_flags"]) for item in blocks}
    if len(sources) != 1 or len(flags) != 1:
        raise SystemExit("FAIL: data blocks must share one source and compiler flags")
    source = (CASE / next(iter(sources))).resolve()
    source_sha = hashlib.sha256(source.read_bytes()).hexdigest()
    if any(item["source_sha256"] != source_sha for item in blocks):
        raise SystemExit(f"FAIL: source hash mismatch: {source}")

    build = HERE / "build"
    build.mkdir(parents=True, exist_ok=True)
    obj, elf, script = build / "data.o", build / "data.elf", build / "data.ld"
    subprocess.run([str(GCC), *next(iter(flags)), "-c", str(source), "-o", str(obj)], check=True)
    outputs = " ".join(
        f"{item['section']} {int(item['address'], 0):#x} : {{ KEEP(*({item['section']})) }}"
        for item in blocks
    )
    script.write_text(f"SECTIONS {{ {outputs} /DISCARD/ : {{ *(*) }} }}\n")
    subprocess.run([str(LD), "-T", str(script), str(obj), "-o", str(elf)], check=True)

    for block in blocks:
        address, size = int(block["address"], 0), int(block["size"])
        binary = CASE / block["binary"]
        binary.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run([str(OBJCOPY), "-O", "binary", f"--only-section={block['section']}", str(elf), str(binary)], check=True)
        actual = binary.read_bytes()
        expected = target[address - BASE:address - BASE + size]
        mismatch = compare(actual, expected)
        if mismatch is not None:
            print(f"FAIL {block['name']}: first difference +{mismatch:#x} at {address + mismatch:#010x}; emitted {len(actual)} B, expected {size} B")
            return 1
        print(f"PASS {block['name']}: exact {size} bytes at {address:#010x}–{address + size - 1:#010x}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
