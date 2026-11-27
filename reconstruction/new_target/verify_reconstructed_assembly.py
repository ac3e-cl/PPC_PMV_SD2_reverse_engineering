#!/usr/bin/env python3
"""Rebuild and accept the ADC section as reconstructed assembly, never as C."""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

CASE = Path(__file__).resolve().parent
ROOT = CASE.parents[1]
BASE = 0x08000000
TARGET_SHA256 = "5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752"
PROBE = CASE / "candidates/probes/adc_assembly_reuse"
MANIFEST_PATH = PROBE / "manifest.json"
PROBE_RESULT = PROBE / "build/verification.json"
BINARY_PATH = PROBE / "build/HAL_ADC_ConfigChannel.bin"
OBJECT_PATH = PROBE / "build/HAL_ADC_ConfigChannel.o"
EXPECTED_AUTHORIZATION = (
    "The user explicitly authorized assembly for the ADC function only; all other reconstructed "
    "functions must remain C. This target-specific section is accepted under a separate "
    "reconstructed-assembly ledger, never as C."
)


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def write_json(path: Path, value: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_suffix(path.suffix + ".tmp")
    temporary.write_text(json.dumps(value, indent=2) + "\n")
    temporary.replace(path)


def address(item: dict, field: str = "address") -> int:
    return int(item[field], 0)


def main() -> int:
    target = (ROOT / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
    if digest(target) != TARGET_SHA256:
        raise SystemExit("FAIL: target identity mismatch")

    manifest = json.loads(MANIFEST_PATH.read_text())
    if manifest.get("target_sha256") != TARGET_SHA256:
        raise SystemExit("FAIL: ADC manifest is not pinned to this target")
    if manifest.get("classification") != "reconstructed_assembly_not_C":
        raise SystemExit("FAIL: ADC block must remain separately classified from C")
    if manifest.get("authorization_context") != EXPECTED_AUTHORIZATION:
        raise SystemExit("FAIL: explicit ADC-only assembly authorization is missing")
    if manifest.get("name") != "FUN_08003cec" or int(manifest.get("size", 0)) != 2176:
        raise SystemExit("FAIL: unexpected ADC section identity or size")

    env = os.environ.copy()
    result = subprocess.run(
        [sys.executable, str(PROBE / "verify.py")], cwd=CASE, env=env,
        text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT
    )
    if result.stdout:
        print(result.stdout, end="")
    if result.returncode:
        raise SystemExit("FAIL: isolated ADC assembly rebuild did not pass")

    built = json.loads(PROBE_RESULT.read_text())
    if (not built.get("matched") or built.get("target_sha256") != TARGET_SHA256
            or built.get("source_sha256") != manifest.get("source_sha256")
            or built.get("address") != manifest.get("address")
            or int(built.get("size", 0)) != int(manifest["size"])):
        raise SystemExit("FAIL: isolated ADC build report does not match its pinned manifest")

    emitted = BINARY_PATH.read_bytes()
    start = address(manifest)
    size = int(manifest["size"])
    end = start + size
    if start < BASE or end > BASE + len(target):
        raise SystemExit("FAIL: ADC section lies outside the target image")
    expected = target[start - BASE:end - BASE]
    if len(emitted) != size or emitted != expected:
        raise SystemExit("FAIL: strict ADC section comparison failed")
    if digest(emitted) != built.get("binary_sha256"):
        raise SystemExit("FAIL: ADC output hash disagrees with the isolated verifier")

    project = ROOT
    source = project / manifest["source_relpath"]
    workspace_copy = ROOT / manifest["source_workspace_copy"]
    if digest(source.read_bytes()) != manifest["source_sha256"]:
        raise SystemExit("FAIL: reference-project ADC source hash mismatch")
    if digest(workspace_copy.read_bytes()) != manifest["source_sha256"]:
        raise SystemExit("FAIL: reconstruction ADC source-copy hash mismatch")

    report_path = CASE / "build/verification.json"
    report = json.loads(report_path.read_text())
    category_keys = ("matches", "runtime_matches", "data_matches", "assembly_matches", "vendor_startup_matches")
    adc_name = manifest["name"]
    prior_adc = []
    component_ranges = []
    for key in category_keys:
        for item in report.get(key, []):
            if key == "assembly_matches" and item.get("name") == adc_name:
                prior_adc.append(item)
                continue
            item_start = address(item)
            item_end = item_start + int(item["size"])
            if item_start < BASE or item_end > BASE + len(target):
                raise SystemExit(f"FAIL: accepted section outside target: {item['name']}")
            component_ranges.append((item_start, item_end, item["name"]))
    if len(prior_adc) > 1:
        raise SystemExit("FAIL: duplicate ADC assembly entries in central report")
    if prior_adc and (address(prior_adc[0]) != start or int(prior_adc[0]["size"]) != size
                      or prior_adc[0].get("binary_sha256") != digest(emitted)):
        raise SystemExit("FAIL: conflicting prior ADC assembly entry")

    gap_ranges = []
    gap_total = 0
    for gap in report.get("linker_gap_ranges", []):
        gap_start = address(gap, "gap_start")
        gap_size = int(gap["gap_bytes"])
        gap_end = gap_start + gap_size
        if gap_start < BASE or gap_end > BASE + len(target):
            raise SystemExit("FAIL: linker gap outside target")
        gap_ranges.append((gap_start, gap_end, f"linker gap {gap['gap_start']}"))
        gap_total += gap_size

    all_ranges = component_ranges + [(start, end, adc_name)] + gap_ranges
    all_ranges.sort()
    for previous, current in zip(all_ranges, all_ranges[1:]):
        if previous[1] > current[0]:
            raise SystemExit(f"FAIL: ADC section overlaps {previous[2]} / {current[2]}")

    entry = {
        "name": adc_name,
        "kind": manifest["classification"],
        "classification": manifest["classification"],
        "authorization_context": manifest["authorization_context"],
        "inferred_name": manifest["inferred_name"],
        "historical_name": manifest["historical_name"],
        "address": manifest["address"],
        "size": size,
        "section": ".text",
        "source_project": "PPC_PMV_SD2_reverse_engineering/" + manifest["source_relpath"],
        "source_workspace_copy": manifest["source_workspace_copy"],
        "source_sha256": manifest["source_sha256"],
        "source_manifest": manifest["source_manifest_path"],
        "source_manifest_sha256": digest((ROOT / manifest["source_manifest_path"]).read_bytes()),
        "acceptance_manifest": str(MANIFEST_PATH.relative_to(CASE)),
        "acceptance_manifest_sha256": digest(MANIFEST_PATH.read_bytes()),
        "historical_firmware_sha256": manifest["historical_firmware_sha256"],
        "rebase_delta": manifest["rebase_delta"],
        "symbol_mapping": manifest["symbol_mapping"],
        "historical_literal_pools": manifest["historical_literal_pools"],
        "assembler_flags": manifest["assembler_flags"],
        "defsyms": built["defsyms"],
        "compiler": built["compiler"],
        "verifier": str((PROBE / "verify.py").relative_to(CASE)),
        "object": str(OBJECT_PATH.relative_to(CASE)),
        "object_sha256": digest(OBJECT_PATH.read_bytes()),
        "binary": str(BINARY_PATH.relative_to(CASE)),
        "binary_sha256": digest(emitted),
        "matched": True,
    }
    other_assembly = [item for item in report.get("assembly_matches", []) if item.get("name") != adc_name]
    assembly_entries = other_assembly + [entry]
    component_bytes = sum(right - left for left, right, _ in component_ranges) + size
    matched_total = component_bytes + gap_total
    if matched_total > len(target):
        raise SystemExit("FAIL: verified coverage exceeds image size")
    recorded_total = int(report.get("matched_image_bytes_total", -1))
    previous_adc_bytes = int(prior_adc[0]["size"]) if prior_adc else 0
    expected_recorded_total = component_bytes - size + previous_adc_bytes + gap_total
    if recorded_total != expected_recorded_total:
        raise SystemExit(
            f"FAIL: pre-integration coverage total is inconsistent: {recorded_total} != {expected_recorded_total}"
        )

    report.update({
        "status": ("partial_C_reconstructed_ADC_assembly_runtime_data_vendor_startup_and_linker_alignment_coverage"
                   if gap_total else "partial_C_reconstructed_ADC_assembly_runtime_data_vendor_startup_coverage"),
        "assembly_matches": assembly_entries,
        "reconstructed_assembly_entries": len(assembly_entries),
        "reconstructed_assembly_bytes": sum(int(item["size"]) for item in assembly_entries),
        "matched_image_bytes_total": matched_total,
        "image_percentage_total": round(100 * matched_total / len(target), 4),
        "image_percentage_with_reconstructed_assembly_excluding_linker_gaps": round(100 * component_bytes / len(target), 4),
        "remaining_original_bytes": len(target) - matched_total,
    })

    full_path = CASE / "full_image/build/verification.json"
    full = json.loads(full_path.read_text())
    full.update({
        "assembly_matches": assembly_entries,
        "reconstructed_assembly_entries": len(assembly_entries),
        "reconstructed_assembly_bytes": sum(int(item["size"]) for item in assembly_entries),
        "verified_C_plus_runtime_data_startup_reconstructed_assembly_bytes": component_bytes,
        "verified_C_plus_runtime_data_startup_reconstructed_assembly_percentage": round(100 * component_bytes / len(target), 4),
        "verified_all_categories_plus_linker_alignment_bytes": matched_total,
        "verified_all_categories_plus_linker_alignment_percentage": round(100 * matched_total / len(target), 4),
        "matched_image_bytes_total": matched_total,
        "unverified_image_bytes": len(target) - matched_total,
        "actual_size": 0,
        "actual_sha256": None,
        "different_bytes": None,
        "match": False,
        "single_link_from_all_sources": False,
        "binary_patches_applied": False,
        "note": "ADC is accepted only as reconstructed assembly; the full-image builder separately assembles all independently verified fragments and checks the resulting candidate against the pinned target.",
    })

    accepted = {
        "target_sha256": TARGET_SHA256,
        "classification": "reconstructed_assembly_not_C",
        "authorization_context": EXPECTED_AUTHORIZATION,
        "source_manifest": str(MANIFEST_PATH.relative_to(CASE)),
        "source_manifest_sha256": digest(MANIFEST_PATH.read_bytes()),
        "compiler": built["compiler"],
        "assembly_bytes": sum(int(item["size"]) for item in assembly_entries),
        "blocks": assembly_entries,
        "note": "This ledger covers the ADC function only. All other reconstructed application functions remain C; the section is never counted as C bytes.",
    }
    write_json(CASE / "evidence/reconstructed_assembly_accepted.json", accepted)
    write_json(report_path, report)
    write_json(full_path, full)
    print(f"PASS reconstructed ADC assembly {adc_name}: exact {size} bytes at {start:#010x}; separately accepted, not C")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
