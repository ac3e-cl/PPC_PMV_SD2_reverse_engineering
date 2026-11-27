#!/usr/bin/env python3
"""Rebuild and account for pinned non-function data sections."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

CASE = Path(__file__).resolve().parent
BASE = 0x08000000
TARGET_SHA256 = "5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752"
TC = Path(os.environ.get("ARM_TC", str(Path.home() / ".local/opt/gnu-tools-for-stm32-13.3.rel1")))
GCC = TC / "bin/arm-none-eabi-gcc"


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def address(value) -> int:
    return int(value, 0) if isinstance(value, str) else int(value)


def write_json(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, indent=2) + "\n")


def main() -> int:
    manifest = json.loads((CASE / "evidence/data_manifest.json").read_text())
    target = (CASE.parents[1] / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
    if digest(target) != TARGET_SHA256 or manifest.get("target_sha256") != TARGET_SHA256:
        raise ValueError("data verifier target identity mismatch")
    if address(manifest.get("base_address", 0)) != BASE:
        raise ValueError("unexpected data manifest base")

    accepted = json.loads((CASE / "evidence/accepted.json").read_text())["functions"]
    runtime = json.loads((CASE / "evidence/runtime_accepted.json").read_text())["blocks"]
    intervals = []
    for category, items in (("C", accepted), ("runtime", runtime), ("data", manifest["blocks"])):
        for item in items:
            start = address(item["address"])
            size = int(item["size"])
            if size <= 0 or start < BASE or start + size > BASE + len(target):
                raise ValueError(f"invalid {category} interval: {item['name']}")
            intervals.append((start, start + size, category, item["name"]))
    intervals.sort()
    for previous, current in zip(intervals, intervals[1:]):
        if previous[1] > current[0]:
            raise ValueError(f"overlapping intervals: {previous[3]} / {current[3]}")

    for block in manifest["blocks"]:
        source = CASE / block["source"]
        if digest(source.read_bytes()) != block["source_sha256"]:
            raise ValueError(f"source hash mismatch: {block['source']}")
    for verifier in sorted({block["verifier"] for block in manifest["blocks"]}):
        command = [sys.executable, str(CASE / verifier)]
        run = subprocess.run(command, cwd=CASE, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        if run.stdout:
            print(run.stdout, end="")
        if run.returncode:
            raise RuntimeError(f"data verifier failed: {verifier}")

    results = []
    for block in manifest["blocks"]:
        source = CASE / block["source"]
        binary = CASE / block["binary"]
        emitted = binary.read_bytes()
        size, start = int(block["size"]), address(block["address"])
        expected = target[start - BASE:start - BASE + size]
        if len(emitted) != size or emitted != expected:
            raise ValueError(f"post-build data verification failed: {block['name']}")
        results.append({
            **block,
            "source_sha256": digest(source.read_bytes()),
            "binary_sha256": digest(emitted),
            "matched": True
        })

    report_path = CASE / "build/verification.json"
    report = json.loads(report_path.read_text())
    data_bytes = sum(int(item["size"]) for item in results)
    c_bytes = int(report["matched_C_bytes_including_pools"])
    runtime_bytes = int(report["matched_runtime_bytes"])
    combined = c_bytes + runtime_bytes + data_bytes
    if combined != sum(end - start for start, end, _, _ in intervals):
        raise ValueError("coverage sum disagrees with disjoint interval map")
    image_bytes = len(target)
    report.update({
        "status": "partial_C_runtime_and_data_fragment_coverage",
        "data_matches": results,
        "matched_data_blocks": len(results),
        "matched_data_bytes": data_bytes,
        "matched_image_bytes_total": combined,
        "image_percentage_total": round(100 * combined / image_bytes, 4),
        "image_percentage_from_C_runtime_data_and_startup": round(100 * combined / image_bytes, 4),
        "remaining_original_bytes": image_bytes - combined
    })
    write_json(report_path, report)

    full_path = CASE / "full_image/build/verification.json"
    full = json.loads(full_path.read_text()) if full_path.exists() else {}
    full.update({
        "data_matches": results,
        "matched_data_blocks": len(results),
        "data_bytes": data_bytes,
        "matched_image_bytes_total": combined,
        "verified_C_plus_runtime_data_bytes": combined,
        "verified_C_plus_runtime_data_percentage": round(100 * combined / image_bytes, 4),
        "unverified_image_bytes": image_bytes - combined,
        "match": False,
        "note": "No complete candidate image exists; exact C sections, runtime blocks and data sections do not prove whole-image equality."
    })
    write_json(full_path, full)

    compiler = subprocess.check_output([str(GCC), "--version"], text=True).splitlines()[0]
    write_json(CASE / "evidence/data_accepted.json", {
        "target_sha256": TARGET_SHA256,
        "classification": manifest["classification"],
        "compiler": compiler,
        "data_bytes": data_bytes,
        "blocks": results
    })
    print(f"DATA VERIFIED: {len(results)} blocks, {data_bytes} bytes; C+runtime+data {combined}/{image_bytes} bytes ({report['image_percentage_total']}%)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
