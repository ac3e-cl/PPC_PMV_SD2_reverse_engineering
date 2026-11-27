#!/usr/bin/env python3
"""Build a complete fixed-address candidate only when every target byte is sourced."""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

CASE = Path(__file__).resolve().parents[1]
BASE = 0x08000000
SIZE = 38536
TARGET_SHA256 = "5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752"
DEFAULT_TC = Path.home() / ".local/opt/gnu-tools-for-stm32-13.3.rel1"
TC = Path(os.environ.get("ARM_TC", DEFAULT_TC))
BIN = TC / "bin"
LD = BIN / "arm-none-eabi-ld"
OBJCOPY = BIN / "arm-none-eabi-objcopy"
OUT = Path(__file__).resolve().parent / "build"
REPORT_PATH = CASE / "build/verification.json"
FULL_REPORT_PATH = OUT / "verification.json"
CATEGORY_KEYS = ("matches", "runtime_matches", "data_matches", "assembly_matches", "vendor_startup_matches")


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def write_json(path: Path, value: dict) -> None:
    temporary = path.with_suffix(path.suffix + ".tmp")
    temporary.write_text(json.dumps(value, indent=2) + "\n")
    temporary.replace(path)


def checked_path(relative: str) -> Path:
    path = (CASE / relative).resolve()
    if not path.is_relative_to(CASE):
        raise ValueError(f"fragment path escapes target case: {relative}")
    return path


def uncovered_ranges(records: list[dict]) -> list[dict]:
    ranges = sorted(records, key=lambda item: item["address"])
    cursor = BASE
    holes = []
    for item in ranges:
        start = item["address"]
        end = start + item["size"]
        if start < cursor:
            raise ValueError(f"fragment overlap at {start:#010x}: {item['name']}")
        if start > cursor:
            holes.append({"start": f"0x{cursor:08x}", "end_exclusive": f"0x{start:08x}", "size": start - cursor})
        cursor = end
    image_end = BASE + SIZE
    if cursor < image_end:
        holes.append({"start": f"0x{cursor:08x}", "end_exclusive": f"0x{image_end:08x}", "size": image_end - cursor})
    if cursor > image_end:
        raise ValueError(f"fragment coverage exceeds target end: {cursor:#010x}")
    return holes


def main() -> int:
    target = (CASE.parents[1] / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
    if len(target) != SIZE or digest(target) != TARGET_SHA256:
        raise SystemExit("FAIL: target size or SHA-256 changed")

    verify_env = os.environ.copy()
    verify_env["ARM_TC"] = str(TC)
    verified = subprocess.run(
        [sys.executable, str(CASE / "verify.py")], cwd=CASE, env=verify_env,
        text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT
    )
    if verified.stdout:
        print(verified.stdout, end="")
    if verified.returncode:
        raise SystemExit("FAIL: aggregate fragment verification did not pass")

    report = json.loads(REPORT_PATH.read_text())
    if report.get("firmware_sha256") != TARGET_SHA256 or report.get("image_bytes") != SIZE:
        raise SystemExit("FAIL: aggregate report is not pinned to the target")

    records = []
    by_name = {}
    for category in CATEGORY_KEYS:
        for entry in report.get(category, []):
            start = int(entry["address"], 0)
            size = int(entry["size"])
            path = checked_path(entry["binary"])
            data = path.read_bytes()
            if start < BASE or start + size > BASE + SIZE or len(data) != size:
                raise ValueError(f"invalid fragment bounds or length: {entry['name']}")
            target_slice = target[start - BASE:start - BASE + size]
            if data != target_slice:
                raise ValueError(f"stale or nonmatching fragment: {entry['name']} at {start:#010x}")
            record = {"address": start, "size": size, "name": entry["name"], "category": category,
                      "data": data, "path": path}
            records.append(record)
            if entry["name"] in by_name:
                raise ValueError(f"duplicate fragment name: {entry['name']}")
            by_name[entry["name"]] = record

    for gap in report.get("linker_gap_ranges", []):
        gap_start = int(gap["gap_start"], 0)
        gap_size = int(gap["gap_bytes"])
        left = by_name.get(gap["from"])
        right = by_name.get(gap["to"])
        if left is None or right is None:
            raise ValueError(f"linker gap lacks accepted neighbors: {gap['from']} -> {gap['to']}")
        if left["address"] + left["size"] != gap_start or right["address"] != gap_start + gap_size:
            raise ValueError(f"linker gap is not bounded by its accepted neighbors: {gap['gap_start']}")
        pair_path = checked_path(gap["linked_pair_binary"])
        pair = pair_path.read_bytes()
        pair_offset = gap_start - left["address"]
        expected_pair_size = left["size"] + gap_size + right["size"]
        if len(pair) != expected_pair_size:
            raise ValueError(f"linker-pair output has unexpected size for {gap['gap_start']}")
        gap_data = pair[pair_offset:pair_offset + gap_size]
        if len(gap_data) != gap_size or gap_data.hex() != gap.get("linked_hex"):
            raise ValueError(f"linker-generated gap bytes are not reproducible at {gap['gap_start']}")
        if gap_data != target[gap_start - BASE:gap_start - BASE + gap_size]:
            raise ValueError(f"linker-generated gap differs from target at {gap['gap_start']}")
        records.append({"address": gap_start, "size": gap_size, "name": f"linker gap {gap['gap_start']}",
                        "category": "linker_alignment", "data": gap_data, "path": None})

    holes = uncovered_ranges(records)
    hole_bytes = sum(item["size"] for item in holes)
    if holes:
        full = json.loads(FULL_REPORT_PATH.read_text()) if FULL_REPORT_PATH.exists() else {}
        full.update({
            "build_status": "blocked_incomplete_coverage",
            "candidate_binary": None,
            "candidate_binary_written": False,
            "uncovered_ranges": holes,
            "actual_size": 0,
            "actual_sha256": None,
            "different_bytes": None,
            "match": False,
            "single_link_from_all_sources": False,
            "binary_patches_applied": False,
            "unverified_image_bytes": hole_bytes,
            "note": "No candidate image was written: the builder refuses to fill uncovered ranges from the reference BIN or with padding.",
        })
        write_json(FULL_REPORT_PATH, full)
        rendered = ", ".join(f"{item['start']}–{item['end_exclusive']} ({item['size']} B)" for item in holes)
        print(f"BLOCKED: no candidate image written; {hole_bytes} unverified bytes in {rendered}")
        return 0

    OUT.mkdir(parents=True, exist_ok=True)
    build_records = []
    for index, record in enumerate(sorted(records, key=lambda item: item["address"])):
        if record["path"] is None:
            source = OUT / f"gap_{record['address']:08x}.bin"
            source.write_bytes(record["data"])
        else:
            source = record["path"]
        obj = OUT / f"fragment_{index:03d}.o"
        section = f".part_{index:03d}"
        subprocess.run([
            str(OBJCOPY), "-I", "binary", "-O", "elf32-littlearm", "-B", "arm",
            "--rename-section", f".data={section},alloc,load,readonly,data,contents",
            "--set-section-alignment", ".data=1", str(source), str(obj)
        ], check=True)
        build_records.append((record["address"], record["size"], obj, section))

    script_lines = ["SECTIONS {"]
    for address_value, _, _, section in build_records:
        script_lines.append(f"  {section} {address_value:#x} : {{ *({section}) }}")
    script_lines.append("}")
    script_path = OUT / "candidate.ld"
    script_path.write_text("\n".join(script_lines) + "\n")
    elf_path = OUT / "candidate.elf"
    binary_path = OUT / "candidate.bin"
    subprocess.run([str(LD), "--fatal-warnings", "-T", str(script_path),
                    *(str(item[2]) for item in build_records), "-o", str(elf_path)], check=True)
    subprocess.run([str(OBJCOPY), "-O", "binary", str(elf_path), str(binary_path)], check=True)

    actual = binary_path.read_bytes()
    differences = [index for index in range(max(len(actual), len(target)))
                   if (actual[index] if index < len(actual) else None)
                   != (target[index] if index < len(target) else None)]
    full = json.loads(FULL_REPORT_PATH.read_text())
    full.update({
        "classification": "mixed_C_reconstructed_assembly_vendor_startup_runtime_and_data",
        "build_status": "complete_candidate_built",
        "candidate_binary": str(binary_path.relative_to(CASE)),
        "candidate_binary_written": True,
        "uncovered_ranges": [],
        "actual_size": len(actual),
        "actual_sha256": digest(actual),
        "different_bytes": len(differences),
        "match": actual == target,
        "single_link_from_all_sources": False,
        "binary_patches_applied": False,
        "unverified_image_bytes": 0,
        "note": "Candidate is assembled from independently rebuilt, strictly verified fixed-address fragments; it is not a single-link build from all original C sources.",
    })
    write_json(FULL_REPORT_PATH, full)
    print(f"reference: length={len(target)} sha256={TARGET_SHA256}")
    print(f"candidate: length={len(actual)} sha256={digest(actual)}")
    print(f"differing bytes: {len(differences)}")
    for offset in differences:
        got = "--" if offset >= len(actual) else f"{actual[offset]:02x}"
        expected_byte = "--" if offset >= len(target) else f"{target[offset]:02x}"
        print(f"  {BASE + offset:#010x}: candidate={got} reference={expected_byte}")
    return 0 if actual == target and len(actual) == SIZE and digest(actual) == TARGET_SHA256 else 1


if __name__ == "__main__":
    raise SystemExit(main())
