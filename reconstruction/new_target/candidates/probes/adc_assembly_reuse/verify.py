#!/usr/bin/env python3
"""Strictly test the prior complete ADC assembly reconstruction against new_target.

This probe does not update any central acceptance ledger or coverage report.
"""
from pathlib import Path
import hashlib
import json
import os
import re
import subprocess

HERE = Path(__file__).resolve().parent
CASE = HERE.parents[2]
ROOT = CASE.parents[1]
META = json.loads((HERE / "manifest.json").read_text())
BASE = 0x08000000


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def exact(a: bytes, b: bytes) -> bool:
    return len(a) == len(b) and a == b


def comparator_self_test(expected: bytes) -> None:
    if exact(expected, expected[:-1]) or exact(expected, expected + b"\0"):
        raise SystemExit("FAIL: comparator accepted a length mismatch")
    mutated = bytes([expected[0] ^ 1]) + expected[1:]
    if exact(mutated, expected):
        raise SystemExit("FAIL: comparator accepted a changed byte")


def main() -> int:
    target = (ROOT / "bin/PPC_PMV_SD2_reverse_engineering.bin").read_bytes()
    if sha256(target) != META["target_sha256"]:
        raise SystemExit("FAIL: new-target identity mismatch")
    if len(target) != 38536:
        raise SystemExit(f"FAIL: unexpected image size {len(target)}")

    project = ROOT
    source = project / META["source_relpath"]
    workspace_copy = ROOT / META["source_workspace_copy"]
    historical_manifest_path = ROOT / META["source_manifest_path"]
    historical_manifest = json.loads(historical_manifest_path.read_text())
    old_entry, = historical_manifest["functions"]
    source_bytes = source.read_bytes()
    if sha256(source_bytes) != META["source_sha256"]:
        raise SystemExit("FAIL: reference-project source hash mismatch")
    if sha256(workspace_copy.read_bytes()) != META["source_sha256"]:
        raise SystemExit("FAIL: reconstruction source copy hash mismatch")
    if old_entry["source_sha256"] != META["source_sha256"]:
        raise SystemExit("FAIL: historical source manifest disagrees")
    if old_entry["size"] != META["size"]:
        raise SystemExit("FAIL: historical function size disagrees")

    text = source_bytes.decode()
    if re.search(r"^\s*\.(?:incbin|inst|byte|hword|short|2byte|4byte|quad|fill|space|skip|org)\b", text, re.M):
        raise SystemExit("FAIL: binary inclusion or instruction-byte directives are forbidden")
    old_pools = [(int(p["start"], 16), int(p["end_exclusive"], 16)) for p in META["historical_literal_pools"]]
    words = [int(value, 16) for value in re.findall(r"^\s*\.word\s+\S+\s+@\s+(0x[0-9a-f]+):", text, re.M)]
    expected_words = [address for start, end in old_pools for address in range(start, end, 4)]
    if words != expected_words:
        raise SystemExit("FAIL: .word directives exceed the historical literal-pool ranges")

    address, size = int(META["address"], 0), int(META["size"])
    if address < BASE or address + size > BASE + len(target):
        raise SystemExit("FAIL: candidate span is outside the pinned target")
    expected = target[address - BASE:address - BASE + size]
    if len(expected) != size:
        raise SystemExit("FAIL: target slice has wrong length")
    comparator_self_test(expected)

    tc = Path(os.environ.get("ARM_TC", str(Path.home() / ".local/opt/gnu-tools-for-stm32-13.3.rel1"))) / "bin"
    gcc, ld, objcopy = (tc / f"arm-none-eabi-{name}" for name in ("gcc", "ld", "objcopy"))
    build = HERE / "build"
    build.mkdir(parents=True, exist_ok=True)
    obj, elf, raw, script = (build / f"HAL_ADC_ConfigChannel.{ext}" for ext in ("o", "elf", "bin", "ld"))
    flags = META["assembler_flags"]
    subprocess.run([str(gcc), *flags, "-c", str(source), "-o", str(obj)], check=True)

    delta = int(META["rebase_delta"])
    defsyms = {}
    for name, value in old_entry["defsyms"].items():
        val = int(value, 0)
        defsyms[name] = val if name == "SystemCoreClock" else val + delta
    if defsyms.get("SystemCoreClock") != 0x20000000:
        raise SystemExit("FAIL: unexpected SystemCoreClock mapping")
    script.write_text(f"ENTRY({META['historical_name']})\nSECTIONS {{ .text {address:#x} : {{ KEEP(*(.text.{META['historical_name']})) }} }}\n")
    subprocess.run([str(ld), "--fatal-warnings", *[f"--defsym={name}={value:#x}" for name, value in defsyms.items()], "-T", str(script), str(obj), "-o", str(elf)], check=True)
    subprocess.run([str(objcopy), "-O", "binary", "--only-section=.text", str(elf), str(raw)], check=True)
    actual = raw.read_bytes()
    if not exact(actual, expected):
        mismatch = next((i for i, pair in enumerate(zip(actual, expected)) if pair[0] != pair[1]), min(len(actual), len(expected)))
        raise SystemExit(f"FAIL: assembly mismatch +{mismatch:#x}; emitted {len(actual)} B, expected {size} B")

    compiler = subprocess.check_output([str(gcc), "--version"], text=True).splitlines()[0]
    report = {
        "classification": META["classification"],
        "name": META["name"],
        "address": META["address"],
        "size": size,
        "matched": True,
        "updates_central_ledger": False,
        "target_sha256": META["target_sha256"],
        "source_sha256": META["source_sha256"],
        "binary_sha256": sha256(actual),
        "compiler": compiler,
        "assembler_flags": flags,
        "defsyms": {k: f"0x{v:x}" for k, v in defsyms.items()},
        "note": "This probe only rebuilds and byte-checks the section; verify_reconstructed_assembly.py records central acceptance separately, never as C."
    }
    (build / "verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(f"PASS isolated reconstructed assembly: exact {size} bytes at {address:#010x}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
