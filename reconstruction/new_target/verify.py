"""Rebuild and byte-verify the isolated updated-bin case; never import old coverage."""
from __future__ import annotations

import csv
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
TC = Path(os.environ.get("ARM_TC", str(Path.home() / ".local/opt/gnu-tools-for-stm32-13.3.rel1")))
GCC = TC / "bin/arm-none-eabi-gcc"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def write_json(path: Path, value: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2) + "\n")


def empty_report(target: bytes, functions: list[dict], status: str) -> dict:
    return {
        "status": status,
        "target_file": "bin/PPC_PMV_SD2_reverse_engineering.bin",
        "firmware_sha256": TARGET_SHA256,
        "image_bytes": len(target),
        "analysis_engine": "Ghidra 12.2 headless; ARM Cortex-M Thumb",
        "detected_functions": len(functions),
        "matched_C_functions": 0,
        "matched_C_bytes_including_pools": 0,
        "matched_image_bytes_total": 0,
        "image_percentage_total": 0.0,
        "image_percentage_from_matched_C": 0.0,
        "image_percentage_from_C_plus_runtime": 0.0,
        "image_percentage_from_C_runtime_data_and_startup": 0.0,
        "pending_C_functions": len(functions),
        "pending_detected_functions": len(functions),
        "pending_C": functions,
        "matches": [],
        "runtime_matches": [],
        "assembly_matches": [],
        "vendor_startup_matches": [],
        "matched_vendor_startup_bytes": 0,
        "vendor_startup_address": None,
        "data_matches": [],
        "linker_gap_ranges": [],
        "limitations": [
            "Ghidra output is reverse-engineering evidence, not original source or matching proof.",
            "Only source sections rebuilt by this verifier are counted as matched.",
            "A partial fragment ledger does not imply full-image equality.",
            "No target firmware has been flashed or executed on the board."
        ]
    }


def main() -> int:
    target_path = ROOT / "bin/PPC_PMV_SD2_reverse_engineering.bin"
    target = target_path.read_bytes()
    if digest(target) != TARGET_SHA256:
        raise ValueError("case target hash changed")

    with (CASE / "evidence/functions.tsv").open(newline="") as stream:
        functions = list(csv.DictReader(stream, delimiter="\t"))
    if not functions:
        raise ValueError("Ghidra function inventory is missing")
    for row in functions:
        row["address"] = f"0x{int(row['address'], 16):08x}"
        row["body_bytes"] = int(row["body_bytes"])

    report_path = CASE / "build/verification.json"
    report = empty_report(target, functions, "verification_failed")
    write_json(report_path, report)
    accepted_path = CASE / "evidence/accepted.json"
    manifest = json.loads(accepted_path.read_text())
    if manifest.get("target_sha256") != TARGET_SHA256:
        raise ValueError("accepted manifest is not pinned to this target")
    if int(manifest.get("base_address", "0"), 0) != BASE:
        raise ValueError("unexpected base address")

    matches = []
    intervals = []
    seen_names = set()
    try:
        for item in manifest["functions"]:
            name = item["name"]
            address = int(item["address"], 0)
            size = int(item["size"])
            if name in seen_names:
                raise ValueError(f"duplicate function name: {name}")
            seen_names.add(name)
            source = CASE / item["source"]
            if not source.is_file() or digest(source.read_bytes()) != item["source_sha256"]:
                raise ValueError(f"source missing or hash changed: {item['source']}")
            if not any(int(row["address"], 0) == address for row in functions):
                raise ValueError(f"address not present in Ghidra inventory: {address:#x}")
            flags = list(item.get("compiler_flags", []))
            defsyms = list(item.get("defsyms", []))
            command = [sys.executable, str(CASE / "tools/harness.py"), name, str(source),
                       hex(address), str(size), *flags]
            for symbol in defsyms:
                command += ["--defsym", symbol]
            fragment_tc = Path(os.environ.get("ARM_TC_14_3", item.get("toolchain_root", str(TC))) if item.get("toolchain_root") else str(TC)).expanduser()
            fragment_env = os.environ.copy()
            fragment_env["ARM_TC"] = str(fragment_tc)
            result = subprocess.run(command, cwd=CASE, env=fragment_env, text=True,
                                    stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            if result.stdout:
                print(result.stdout, end="")
            if result.returncode:
                raise RuntimeError(f"strict section rebuild failed for {name}")
            binary = source.parent / "build" / f"{name}.bin"
            emitted = binary.read_bytes()
            start = address - BASE
            if len(emitted) != size or target[start:start + size] != emitted:
                raise ValueError(f"post-build byte verification failed: {name}")
            fragment_compiler = subprocess.run(
                [str(fragment_tc / "bin/arm-none-eabi-gcc"), "--version"], check=True, text=True,
                stdout=subprocess.PIPE).stdout.splitlines()[0]
            entry = {
                "name": name,
                "address": f"0x{address:08x}",
                "size": size,
                "source": item["source"],
                "source_sha256": item["source_sha256"],
                "binary": str(binary.relative_to(CASE)),
                "binary_sha256": digest(emitted),
                "compiler": fragment_compiler,
                "compiler_flags": flags,
                "defsyms": defsyms,
                "configuration": item.get("configuration", "unspecified"),
                "matched": True
            }
            if item.get("toolchain_root"):
                entry["toolchain_root"] = str(fragment_tc)
            matches.append(entry)
            intervals.append((start, start + size, entry))

        intervals.sort(key=lambda interval: interval[0])
        for previous, current in zip(intervals, intervals[1:]):
            if previous[1] > current[0]:
                raise ValueError(f"overlapping verified ranges: {previous[2]['name']} / {current[2]['name']}")
        matched_bytes = sum(end - start for start, end, _ in intervals)
        covered_functions = [
            row for row in functions
            if any(BASE + start <= int(row["address"], 0) < BASE + end for start, end, _ in intervals)
        ]
        pending = [row for row in functions if row not in covered_functions]
        compilers = sorted({entry["compiler"] for entry in matches})
        compiler_summary = compilers[0] if len(compilers) == 1 else "multiple toolchains; see compilers and per-match records"
        report = empty_report(target, functions, "partial_C_fragment_coverage")
        report.update({
            "compiler": compiler_summary,
            "compilers": compilers,
            "configuration": "fragment configuration recorded per match",
            "matched_C_functions": len(matches),
            "matched_C_bytes_including_pools": matched_bytes,
            "matched_image_bytes_total": matched_bytes,
            "image_percentage_total": round(100 * matched_bytes / len(target), 4),
            "image_percentage_from_matched_C": round(100 * matched_bytes / len(target), 4),
            "image_percentage_from_C_plus_runtime": round(100 * matched_bytes / len(target), 4),
            "image_percentage_from_C_runtime_data_and_startup": round(100 * matched_bytes / len(target), 4),
            "remaining_original_bytes": len(target) - matched_bytes,
            "pending_C_functions": len(pending),
            "pending_detected_functions": len(pending),
            "pending_C": pending,
            "pending": pending,
            "matches": matches,
            "limitations": [
                "Only the listed source sections were recompiled and byte-verified against this target.",
                "Ghidra names and pseudocode are inferred and are not original source provenance.",
                "This partial fragment coverage is not a single-link full firmware image.",
                "No target firmware has been flashed or executed on the board."
            ]
        })
        write_json(report_path, report)
        full_path = CASE / "full_image/build/verification.json"
        full_report = json.loads(full_path.read_text()) if full_path.exists() else {}
        full_report.update({
            "classification": "new_target_not_yet_reconstructed",
            "target_file": "bin/PPC_PMV_SD2_reverse_engineering.bin",
            "reference_size": len(target),
            "reference_sha256": TARGET_SHA256,
            "actual_size": 0,
            "actual_sha256": None,
            "different_bytes": None,
            "match": False,
            "matched_C_entries": len(matches),
            "reconstructed_assembly_entries": 0,
            "assembly_matches": [],
            "vendor_startup_matches": [],
            "vendor_startup_entries": 0,
            "matched_vendor_startup_bytes": 0,
            "vendor_startup_address": None,
            "verified_C_plus_runtime_data_startup_bytes": None,
            "verified_C_plus_runtime_data_startup_percentage": None,
            "single_link_from_all_sources": False,
            "binary_patches_applied": False,
            "note": "No complete candidate image exists; partial section matches do not prove whole-image equality."
        })
        write_json(full_path, full_report)
        for verifier, label in (("verify_runtime.py", "runtime"), ("verify_data.py", "data"), ("verify_assembly.py", "vendor startup"), ("verify_reconstructed_assembly.py", "reconstructed ADC assembly"), ("verify_linker_gaps.py", "linker alignment gaps")):
            result = subprocess.run([sys.executable, str(CASE / verifier)], cwd=CASE,
                                    text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            if result.stdout:
                print(result.stdout, end="")
            if result.returncode:
                report = json.loads(report_path.read_text())
                raise RuntimeError(f"{label} block verification failed")
        report = json.loads(report_path.read_text())
        print(f"VERIFIED: {report['matched_C_functions']} C sections ({report['matched_C_bytes_including_pools']} B) + "
              f"{report['reconstructed_assembly_bytes']} ADC-assembly B + {report['matched_runtime_bytes']} runtime B + "
              f"{report['matched_data_bytes']} data B + {report['matched_vendor_startup_bytes']} vendor-startup B + "
              f"{report['matched_linker_gap_bytes']} linker-padding B = "
              f"{report['matched_image_bytes_total']}/{len(target)} B ({report['image_percentage_total']}%); "
              f"{report['pending_C_functions']} functions remain pending")
        return 0
    except Exception as error:
        report["verification_error"] = str(error)
        write_json(report_path, report)
        raise


if __name__ == "__main__":
    raise SystemExit(main())
