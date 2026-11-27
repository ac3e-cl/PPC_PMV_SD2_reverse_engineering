#!/usr/bin/env python3
"""Rebuild and account for linker-generated alignment gaps between matched sections."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

CASE = Path(__file__).resolve().parent
ROOT = CASE.parents[1]
BASE = 0x08000000
TARGET_SHA = "5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752"
TOOL = Path(os.environ.get("ARM_TC", str(Path.home() / ".local/opt/gnu-tools-for-stm32-13.3.rel1"))) / "bin"
PAIR_VERIFIER = CASE / "candidates/probes/linker_alignment/verify_c_pairs.py"
PAIR_RESULT = CASE / "candidates/probes/linker_alignment/build_c_pairs/result.json"

EXPECTED_GAPS = {
    "0x08000a94": 4, "0x08001652": 2, "0x080028f6": 2, "0x08002c8a": 2,
    "0x080034ae": 2, "0x08004e06": 2, "0x08004eca": 2, "0x08006676": 2,
    "0x080091fe": 2, "0x0800934e": 2,
}


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def write_json(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2) + "\n")


def main() -> int:
    image = (ROOT / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
    if digest(image) != TARGET_SHA:
        raise SystemExit("FAIL: linker-gap target identity mismatch")
    subprocess.run([sys.executable, str(PAIR_VERIFIER)], cwd=CASE, check=True)
    pairs = json.loads(PAIR_RESULT.read_text())
    if pairs.get("target_sha256") != TARGET_SHA or not pairs.get("all_pass"):
        raise SystemExit("FAIL: input-section pair links did not pass")
    blocks = pairs["results"]
    actual_gaps = {item["gap_start"]: int(item["gap_bytes"]) for item in blocks}
    if actual_gaps != EXPECTED_GAPS:
        raise SystemExit(f"FAIL: verified gap inventory changed: {actual_gaps}")
    if any(not item.get("pair_match") or item.get("pair_diff_count") != 0 for item in blocks):
        raise SystemExit("FAIL: complete two-section link did not match its target span")

    report_path = CASE / "build/verification.json"
    report = json.loads(report_path.read_text())
    classes = ("matches", "runtime_matches", "data_matches", "assembly_matches", "vendor_startup_matches")
    entries = [item for key in classes for item in report.get(key, [])]
    intervals = []
    by_name = {}
    for item in entries:
        start = int(item["address"], 0)
        end = start + int(item["size"])
        intervals.append((start, end, item["name"]))
        by_name[item["name"]] = item
    intervals.sort()
    for previous, current in zip(intervals, intervals[1:]):
        if previous[1] > current[0]:
            raise SystemExit(f"FAIL: accepted component overlap: {previous[2]} / {current[2]}")

    accepted_blocks = []
    gap_intervals = []
    for item in blocks:
        start = int(item["gap_start"], 0)
        size = int(item["gap_bytes"])
        end = start + size
        if start < BASE or end > BASE + len(image):
            raise SystemExit("FAIL: linker alignment gap outside image")
        target_slice = image[start - BASE:end - BASE]
        if target_slice.hex() != item["target_hex"] or target_slice.hex() != item["linked_hex"]:
            raise SystemExit(f"FAIL: gap bytes differ at {start:#010x}")
        left = by_name.get(item["from"])
        right = by_name.get(item["to"])
        if left is None or right is None:
            raise SystemExit(f"FAIL: pair references an unaccepted section: {item['from']} -> {item['to']}")
        if int(left["address"], 0) + int(left["size"]) != start:
            raise SystemExit(f"FAIL: gap does not follow {item['from']}")
        if int(right["address"], 0) != end:
            raise SystemExit(f"FAIL: gap does not precede {item['to']}")
        if any(start < old_end and old_start < end for old_start, old_end, _ in intervals):
            raise SystemExit(f"FAIL: gap overlaps an accepted section at {start:#010x}")
        if any(start < old_end and old_start < end for old_start, old_end in gap_intervals):
            raise SystemExit(f"FAIL: linker gap ranges overlap at {start:#010x}")
        gap_intervals.append((start, end))

        block = dict(item)
        block["objects"] = [str(Path(path).resolve().relative_to(CASE)) for path in item["objects"]]
        object_paths = [CASE / path for path in block["objects"]]
        block["object_sha256"] = [digest(path.read_bytes()) for path in object_paths]
        linker_script = Path(item["linker_script"]).resolve()
        linked_binary = linker_script.with_suffix(".bin")
        block["linker_script"] = str(linker_script.relative_to(CASE))
        block["linker_script_sha256"] = digest(linker_script.read_bytes())
        block["linked_pair_binary"] = str(linked_binary.relative_to(CASE))
        block["linked_pair_sha256"] = digest(linked_binary.read_bytes())
        accepted_blocks.append(block)

    base_total = sum(int(item["size"]) for item in entries)
    gap_total = sum(int(item["gap_bytes"]) for item in accepted_blocks)
    matched_total = base_total + gap_total
    if matched_total > len(image):
        raise SystemExit("FAIL: verified byte total exceeds image size")
    compiler = subprocess.check_output([str(TOOL / "arm-none-eabi-ld"), "--version"], text=True).splitlines()[0]
    accepted = {
        "target_sha256": TARGET_SHA,
        "classification": "linker-generated input-section alignment; not C/runtime source bytes",
        "linker": compiler,
        "base_verified_bytes_before_gaps": base_total,
        "linker_gap_bytes": gap_total,
        "note": "Each gap is emitted by GNU ld between independently accepted adjacent input sections; the complete linked pair span is byte-identical. This does not prove original whole-image link provenance.",
        "blocks": accepted_blocks,
    }
    write_json(CASE / "evidence/linker_gaps_accepted.json", accepted)

    report.update({
        "status": "partial_C_reconstructed_ADC_assembly_runtime_data_vendor_startup_and_linker_alignment_coverage",
        "linker_gap_ranges": accepted_blocks,
        "matched_linker_gap_bytes": gap_total,
        "matched_image_bytes_total": matched_total,
        "image_percentage_total": round(100 * matched_total / len(image), 4),
        "image_percentage_with_verified_linker_padding": round(100 * matched_total / len(image), 4),
        "remaining_original_bytes": len(image) - matched_total,
    })
    write_json(report_path, report)

    full_path = CASE / "full_image/build/verification.json"
    full = json.loads(full_path.read_text())
    full.update({
        "linker_gap_ranges": accepted_blocks,
        "verified_linker_gap_bytes": gap_total,
        "verified_all_categories_plus_linker_alignment_bytes": matched_total,
        "verified_all_categories_plus_linker_alignment_percentage": round(100 * matched_total / len(image), 4),
        "matched_image_bytes_total": matched_total,
        "unverified_image_bytes": len(image) - matched_total,
        "match": False,
        "single_link_from_all_sources": False,
        "note": "No complete candidate image exists; exact C/runtime/data/vendor-startup sections, reconstructed ADC assembly and reproduced linker-alignment gaps do not prove whole-image equality.",
    })
    write_json(full_path, full)
    print(f"LINKER GAPS VERIFIED: {len(accepted_blocks)} gaps, {gap_total} bytes; total coverage {matched_total}/{len(image)} B ({report['image_percentage_total']}%)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
