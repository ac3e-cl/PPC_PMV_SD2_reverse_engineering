#!/usr/bin/env python3
"""Strictly rebuild the target's separately classified ST startup assembly."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

CASE = Path(__file__).resolve().parent
ROOT = CASE.parent
BASE = 0x08000000
TARGET_SHA256 = "5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752"
TC = Path(os.environ.get("ARM_TC", str(Path.home() / ".local/opt/gnu-tools-for-stm32-13.3.rel1")))
BIN = TC / "bin"
GCC, LD, OBJCOPY = (BIN / f"arm-none-eabi-{name}" for name in ("gcc", "ld", "objcopy"))


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def exact(actual: bytes, expected: bytes) -> bool:
    return len(actual) == len(expected) and actual == expected


def image_intervals(report: dict) -> list[tuple[int, int, str]]:
    intervals = []
    for key in ("matches", "runtime_matches", "data_matches", "assembly_matches", "vendor_startup_matches"):
        for item in report.get(key, []):
            start = int(item["address"], 0) - BASE
            intervals.append((start, start + int(item["size"]), item["name"]))
    return intervals


def main() -> int:
    manifest = json.loads((CASE / "evidence/assembly_manifest.json").read_text())
    target = (ROOT.parent / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
    if digest(target) != TARGET_SHA256 or manifest.get("target_sha256") != TARGET_SHA256:
        raise SystemExit("FAIL: target identity mismatch")
    if len(manifest.get("blocks", [])) != 1:
        raise SystemExit("FAIL: expected one vendor startup block")
    block = manifest["blocks"][0]
    address, size = int(block["address"], 0), int(block["size"])
    if block["kind"] != "vendor_startup_assembly" or address < BASE or address + size > BASE + len(target):
        raise SystemExit("FAIL: invalid startup block classification or range")

    source = (CASE / block["source"]).resolve()
    license_path = (CASE / block["license"]).resolve()
    if not source.is_relative_to(ROOT) or not license_path.is_relative_to(ROOT):
        raise SystemExit("FAIL: vendor source or license escapes reconstruction root")
    if digest(source.read_bytes()) != block["source_sha256"]:
        raise SystemExit("FAIL: vendor startup source hash mismatch")
    if digest(license_path.read_bytes()) != block["license_sha256"]:
        raise SystemExit("FAIL: vendor startup license hash mismatch")

    build = CASE / "candidates/vendor_startup/build"
    build.mkdir(parents=True, exist_ok=True)
    obj = CASE / block["object"]
    elf = CASE / block["elf"]
    script = CASE / block["linker_script"]
    binary = CASE / block["binary"]
    for path in (obj, elf, script, binary):
        if not path.resolve().is_relative_to(CASE):
            raise SystemExit(f"FAIL: build output escapes case: {path}")
        path.parent.mkdir(parents=True, exist_ok=True)
    section = block["section"]
    script.write_text(f"SECTIONS {{ {section} {address:#x} : {{ KEEP(*(.text.Reset_Handler)) }} /DISCARD/ : {{ *(*) }} }}\n")
    subprocess.run([str(GCC), *block["assembler_flags"], "-c", str(source), "-o", str(obj)], check=True)
    subprocess.run([str(LD), "-T", str(script), *(f"--defsym={symbol}" for symbol in block["defsyms"]), str(obj), "-o", str(elf)], check=True)
    subprocess.run([str(OBJCOPY), "-O", "binary", f"--only-section={section}", str(elf), str(binary)], check=True)

    expected = target[address - BASE:address - BASE + size]
    actual = binary.read_bytes()
    if exact(expected, expected[:-1]) or exact(expected, expected + b"\0") or exact(expected, bytes([expected[0] ^ 1]) + expected[1:]):
        raise SystemExit("FAIL: strict comparator self-test failed")
    if not exact(actual, expected):
        offset = next((i for i, (a, b) in enumerate(zip(actual, expected)) if a != b), min(len(actual), len(expected)))
        raise SystemExit(f"FAIL: startup mismatch +{offset:#x} at {address + offset:#010x}; emitted {len(actual)} B, expected {size} B")

    report_path = CASE / "build/verification.json"
    report = json.loads(report_path.read_text())
    existing = [item for item in report.get("vendor_startup_matches", []) if item["name"] == block["name"]]
    if len(existing) > 1 or any(int(item["address"], 0) != address or int(item["size"]) != size for item in existing):
        raise SystemExit("FAIL: conflicting prior vendor-startup record")
    prior_bytes = sum(int(item["size"]) for item in existing)
    all_intervals = [item for item in image_intervals(report) if item[2] != block["name"]]
    start, end = address - BASE, address - BASE + size
    for old_start, old_end, name in all_intervals:
        if start < old_end and old_start < end:
            raise SystemExit(f"FAIL: startup range overlaps {name}")
    all_intervals.append((start, end, block["name"]))
    combined = sum(right - left for left, right, _ in all_intervals)
    if combined != int(report["matched_image_bytes_total"]) - prior_bytes + size:
        raise SystemExit("FAIL: aggregate coverage disagrees with disjoint intervals")

    compiler = subprocess.check_output([str(GCC), "--version"], text=True).splitlines()[0]
    entry = {
        **block,
        "binary_sha256": digest(actual),
        "object_sha256": digest(obj.read_bytes()),
        "source_path": str(source),
        "license_path": str(license_path),
        "matched": True
    }
    report.update({
        "status": "partial_C_runtime_data_and_vendor_startup_coverage",
        "vendor_startup_matches": [entry],
        "matched_vendor_startup_bytes": size,
        "vendor_startup_address": f"0x{address:08x}",
        "matched_image_bytes_total": combined,
        "image_percentage_total": round(100 * combined / len(target), 4),
        "image_percentage_from_C_runtime_data_and_startup": round(100 * combined / len(target), 4),
        "remaining_original_bytes": len(target) - combined
    })
    (CASE / "build/verification.json").write_text(json.dumps(report, indent=2) + "\n")

    full_path = CASE / "full_image/build/verification.json"
    full = json.loads(full_path.read_text())
    full.update({
        "vendor_startup_matches": [entry],
        "vendor_startup_entries": 1,
        "matched_vendor_startup_bytes": size,
        "vendor_startup_address": f"0x{address:08x}",
        "matched_image_bytes_total": combined,
        "verified_C_plus_runtime_data_startup_bytes": combined,
        "verified_C_plus_runtime_data_startup_percentage": round(100 * combined / len(target), 4),
        "unverified_image_bytes": len(target) - combined,
        "match": False,
        "note": "No complete candidate image exists; exact C, runtime, data, vendor startup and any separately accepted reconstructed assembly do not prove whole-image equality."
    })
    full_path.write_text(json.dumps(full, indent=2) + "\n")
    accepted = {
        "target_sha256": TARGET_SHA256,
        "classification": manifest["classification"],
        "upstream": manifest["upstream"],
        "compiler": compiler,
        "assembly_bytes": size,
        "blocks": [entry]
    }
    (CASE / "evidence/assembly_accepted.json").write_text(json.dumps(accepted, indent=2) + "\n")
    print(f"PASS vendor startup {block['name']}: exact {size} bytes at {address:#010x}–{address + size - 1:#010x}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
