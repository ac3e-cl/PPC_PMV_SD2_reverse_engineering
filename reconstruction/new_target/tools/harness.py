#!/usr/bin/env python3
"""Strict per-section rebuild against the pinned PPC_PMV_SD2_reverse_engineering.bin."""
from pathlib import Path
import hashlib
import os
import subprocess
import sys

CASE = Path(__file__).resolve().parents[1]
BASE = 0x08000000
TARGET_SHA256 = "5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752"
TC = Path(os.environ.get("ARM_TC", str(Path.home() / ".local/opt/gnu-tools-for-stm32-13.3.rel1")))
GCC, LD, OBJCOPY = (TC / "bin" / f"arm-none-eabi-{tool}" for tool in ("gcc", "ld", "objcopy"))


def main():
    if len(sys.argv) < 5:
        raise SystemExit("usage: harness.py NAME source.c ADDRESS SIZE [compiler flags] [--defsym SYMBOL=VALUE ...]")
    name, source = sys.argv[1], Path(sys.argv[2]).resolve()
    address = int(sys.argv[3], 0)
    size = int(sys.argv[4])
    rest = sys.argv[5:]
    flags, defsyms = [], []
    i = 0
    while i < len(rest):
        if rest[i] == "--defsym":
            defsyms.append(rest[i + 1]); i += 2
        else:
            flags.append(rest[i]); i += 1
    if not flags:
        flags = ["-O0"]
    target_path = CASE.parents[1] / "bin/PPC_PMV_SD2_reverse_engineering.bin"
    target = target_path.read_bytes()
    digest = hashlib.sha256(target).hexdigest()
    if digest != TARGET_SHA256:
        raise SystemExit(f"FAIL: target identity changed: {digest}")
    if address < BASE or address + size > BASE + len(target):
        raise SystemExit("FAIL: candidate range outside pinned image")
    out = source.parent / "build"
    out.mkdir(parents=True, exist_ok=True)
    obj, elf, lds, binary = (out / f"{name}.{ext}" for ext in ("o", "elf", "ld", "bin"))
    common = ["-mcpu=cortex-m4", "-mthumb", "-mfloat-abi=hard", "-mfpu=fpv4-sp-d16", "-ffreestanding", "-fno-builtin", "-ffunction-sections", "-fdata-sections", "-fno-asynchronous-unwind-tables", "-fno-unwind-tables"]
    subprocess.run([str(GCC), *flags, *common, "-c", str(source), "-o", str(obj)], check=True)
    lds.write_text("\n".join((f"ENTRY({name})", "SECTIONS {", f"  .text {address:#x} : {{ KEEP(*(.text.{name})) }}", "  /DISCARD/ : { *(.text.*) *(.ARM.attributes) *(.comment) *(.note*) }", "}", "")))
    subprocess.run([str(LD), *[f"--defsym={s}" for s in defsyms], "-T", str(lds), str(obj), "-o", str(elf)], check=True)
    subprocess.run([str(OBJCOPY), "-O", "binary", "--only-section=.text", str(elf), str(binary)], check=True)
    actual = binary.read_bytes()
    expected = target[address - BASE:address - BASE + size]
    if actual != expected:
        mismatch = next((i for i, pair in enumerate(zip(actual, expected)) if pair[0] != pair[1]), min(len(actual), len(expected)))
        print(f"FAIL {name}: mismatch +{mismatch:#x}; emitted {len(actual)} B, expected {len(expected)} B")
        return 1
    print(f"PASS {name}: exact {size} bytes at {address:#010x} (target sha256 {digest})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
