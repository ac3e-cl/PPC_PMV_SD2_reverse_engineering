#!/usr/bin/env python3
"""Rebuild compiler runtime blocks separately from reconstructed C."""
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
TC = Path(os.environ.get("ARM_TC", str(Path.home() / ".local/opt/gnu-tools-for-stm32-13.3.rel1")))
GCC, AR, LD, OBJCOPY = (TC / "bin" / f"arm-none-eabi-{tool}" for tool in ("gcc", "ar", "ld", "objcopy"))


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def compare(actual: bytes, expected: bytes) -> None:
    if actual != expected:
        mismatch = next((i for i, (a, b) in enumerate(zip(actual, expected)) if a != b), min(len(actual), len(expected)))
        raise ValueError(f"mismatch +{mismatch:#x}; emitted {len(actual)} B, expected {len(expected)} B")


def self_test() -> None:
    compare(b"abc", b"abc")
    for bad in (b"axc", b"ab", b"abcd", b""):
        try:
            compare(bad, b"abc")
        except ValueError:
            continue
        raise AssertionError("runtime comparator accepted non-identical bytes")


def write_json(path: Path, value: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2) + "\n")


def main() -> int:
    self_test()
    target = (ROOT / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
    manifest = json.loads((CASE / "evidence/runtime_manifest.json").read_text())
    target_sha = manifest["target_sha256"]
    if digest(target) != target_sha:
        raise ValueError("runtime manifest target identity mismatch")
    base = int(manifest["base_address"], 0)
    flags = manifest["archive_flags"]
    archive = Path(subprocess.check_output([str(GCC), *flags, "-print-libgcc-file-name"], text=True).strip())
    compiler = subprocess.check_output([str(GCC), "--version"], text=True).splitlines()[0]
    build = CASE / "candidates/runtime_libgcc/build"
    build.mkdir(parents=True, exist_ok=True)

    c_manifest = json.loads((CASE / "evidence/accepted.json").read_text())
    c_intervals = [(int(x["address"], 0), int(x["address"], 0) + int(x["size"])) for x in c_manifest["functions"]]
    intervals = []
    results = []
    for block in manifest["blocks"]:
        address, size = int(block["address"], 0), int(block["size"])
        start, end = address - base, address - base + size
        if start < 0 or end > len(target):
            raise ValueError(f"runtime block outside target image: {block['name']}")
        if any(address < c_end and c_start < address + size for c_start, c_end in c_intervals):
            raise ValueError(f"runtime/C overlap: {block['name']}")
        if any(address < other_end and other_start < address + size for other_start, other_end in intervals):
            raise ValueError(f"runtime overlap: {block['name']}")
        intervals.append((address, address + size))

        obj = build / block.get("member", "runtime.o")
        script = build / f"{block['name'].replace(':', '_').replace('.', '_')}.ld"
        elf = build / f"{block['name'].replace(':', '_').replace('.', '_')}.elf"
        binary = build / f"{block['name'].replace(':', '_').replace('.', '_')}.bin"
        link_flags = []
        objects = []
        object_hashes = []
        if block.get("kind") == "toolchain_object":
            source_obj = Path(subprocess.check_output(
                [str(GCC), *flags, f"-print-file-name={block['member']}"], text=True).strip())
            if not source_obj.is_file() or str(source_obj) == block["member"]:
                raise FileNotFoundError(f"toolchain object not found: {block['member']}")
            obj.write_bytes(source_obj.read_bytes())
            object_hash = digest(obj.read_bytes())
            if block.get("expected_object_sha256") and object_hash != block["expected_object_sha256"]:
                raise ValueError(f"toolchain object identity mismatch: {block['member']}")
            support = block["support_sections"]
            section = block.get("section", ".text")
            if section == ".text":
                outputs = f".text {address:#x} : {{ *(.text) }} "
            else:
                text_address = int(support["text"], 0)
                outputs = (f".text {text_address:#x} : {{ *(.text) }} "
                           f"{section} {address:#x} : {{ *({section}) }} ")
            script.write_text(
                f"SECTIONS {{ {outputs}"
                f".data {int(support['data'], 0):#x} : {{ *(.data) }} "
                f".bss {int(support['bss'], 0):#x} (NOLOAD) : {{ *(.bss) }} "
                f".eh_frame {int(support['eh_frame'], 0):#x} : {{ *(.eh_frame) }} "
                "/DISCARD/ : { *(*) } }\n"
            )
            source_description = f"{source_obj} ({section})"
            link_flags = ["--relax"]
            objects = [obj]
            object_hashes = [object_hash]
        elif block.get("kind") == "toolchain_section_set":
            members = list(block["members"])
            expected_hashes = list(block["expected_object_sha256"])
            if len(members) != len(expected_hashes):
                raise ValueError(f"runtime object hash count mismatch: {block['name']}")
            source_objects = []
            for member, expected_hash in zip(members, expected_hashes):
                source_obj = Path(subprocess.check_output(
                    [str(GCC), *flags, f"-print-file-name={member}"], text=True).strip())
                if not source_obj.is_file() or str(source_obj) == member:
                    raise FileNotFoundError(f"toolchain object not found: {member}")
                obj_path = build / member
                obj_path.write_bytes(source_obj.read_bytes())
                object_hash = digest(obj_path.read_bytes())
                if object_hash != expected_hash:
                    raise ValueError(f"toolchain object identity mismatch: {member}")
                objects.append(obj_path)
                object_hashes.append(object_hash)
                source_objects.append(source_obj)
            section = block["section"]
            script.write_text(
                f"SECTIONS {{ {section} {address:#x} : {{ *({section}) }} "
                "/DISCARD/ : { *(*) } }\n"
            )
            source_description = " + ".join(str(path) for path in source_objects) + f" ({section})"
        else:
            with obj.open("wb") as stream:
                subprocess.run([str(AR), "p", str(archive), block["member"]], stdout=stream, check=True)
            script.write_text(
                f"SECTIONS {{ .text {address:#x} : {{ *(.text) }} "
                "/DISCARD/ : { *(.ARM.attributes) *(.comment) *(.note*) *(.debug*) } }\n"
            )
            source_description = f"{archive}:{block['member']} (.text)"
            objects = [obj]
            object_hashes = [digest(obj.read_bytes())]
        subprocess.run([str(LD), *link_flags, "-T", str(script), *map(str, objects), "-o", str(elf)], check=True)
        subprocess.run([str(OBJCOPY), "-O", "binary", f"--only-section={block.get('section', '.text')}", str(elf), str(binary)], check=True)
        actual = binary.read_bytes()
        expected = target[start:end]
        compare(actual, expected)
        entry = {
            **block,
            "object": [str(path.relative_to(CASE)) for path in objects] if len(objects) > 1 else str(objects[0].relative_to(CASE)),
            "object_sha256": object_hashes if len(objects) > 1 else object_hashes[0],
            "binary": str(binary.relative_to(CASE)),
            "binary_sha256": digest(actual),
            "source": source_description,
            "matched": True
        }
        results.append(entry)
        print(f"PASS runtime {block['name']}: exact {size} bytes at {address:#010x}")

    function_rows = list(csv.DictReader((CASE / "evidence/functions.tsv").open(), delimiter="\t"))
    runtime_function_entries = [
        row for row in function_rows
        if any(start <= int(row["address"], 16) < end for start, end in intervals)
    ]
    c_report_path = CASE / "build/verification.json"
    c_report = json.loads(c_report_path.read_text())
    c_bytes = int(c_report["matched_C_bytes_including_pools"])
    runtime_bytes = sum(int(row["size"]) for row in results)
    combined = c_bytes + runtime_bytes
    image_bytes = len(target)
    pending = [row for row in c_report.get("pending_C", c_report.get("pending", []))
               if not any(start <= int(row["address"], 0) < end for start, end in intervals)]
    c_report.update({
        "status": "partial_C_and_runtime_fragment_coverage",
        "runtime_matches": results,
        "matched_runtime_blocks": len(results),
        "matched_runtime_detected_functions": len(runtime_function_entries),
        "matched_runtime_bytes": runtime_bytes,
        "matched_image_bytes_total": combined,
        "image_percentage_total": round(100 * combined / image_bytes, 4),
        "image_percentage_from_matched_C": round(100 * c_bytes / image_bytes, 4),
        "image_percentage_from_C_plus_runtime": round(100 * combined / image_bytes, 4),
        "image_percentage_from_C_runtime_data_and_startup": round(100 * combined / image_bytes, 4),
        "pending_C": pending,
        "pending": pending,
        "pending_C_functions": len(pending),
        "pending_detected_functions": len(pending)
    })
    write_json(c_report_path, c_report)

    full_path = CASE / "full_image/build/verification.json"
    full = json.loads(full_path.read_text()) if full_path.exists() else {}
    full.update({
        "runtime_matches": results,
        "matched_runtime_blocks": len(results),
        "matched_runtime_detected_functions": len(runtime_function_entries),
        "runtime_bytes": runtime_bytes,
        "verified_C_plus_runtime_bytes": combined,
        "verified_C_plus_runtime_percentage": round(100 * combined / image_bytes, 4),
        "unverified_image_bytes": image_bytes - combined,
        "match": False,
        "note": "No complete candidate image exists; exact C sections and compiler runtime blocks still do not prove whole-image equality."
    })
    write_json(full_path, full)

    accepted = {
        "target_sha256": target_sha,
        "compiler": compiler,
        "archive": str(archive),
        "archive_flags": flags,
        "runtime_bytes": runtime_bytes,
        "matched_detected_functions": len(runtime_function_entries),
        "blocks": results
    }
    write_json(CASE / "evidence/runtime_accepted.json", accepted)
    print(f"RUNTIME VERIFIED: {len(results)} compiler runtime blocks, {runtime_bytes} bytes; C+runtime {combined}/{image_bytes} bytes ({c_report['image_percentage_total']}%)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
