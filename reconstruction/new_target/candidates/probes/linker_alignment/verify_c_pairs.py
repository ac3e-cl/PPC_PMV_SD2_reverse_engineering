#!/usr/bin/env python3
"""Reproduce short inter-section gaps by linking accepted function objects."""
import json
import os
import subprocess
from pathlib import Path

BASE = Path(__file__).resolve().parents[3]
ROOT = BASE.parents[1]
REPORT = BASE / 'build/verification.json'
IMAGE = ROOT / 'bin/PPC_PMV_SD2_reverse_engineering.bin'
TOOL = Path(os.environ.get('ARM_TC', str(Path.home() / '.local/opt/gnu-tools-for-stm32-13.3.rel1'))) / 'bin'
OUT = BASE / 'candidates/probes/linker_alignment/build_c_pairs'
FLASH = 0x08000000

report = json.loads(REPORT.read_text())
image = IMAGE.read_bytes()
if len(image) != report['image_bytes'] or report['firmware_sha256'] != '5b1f405c2a270c77de55cd59d6b3f9fa0b8e4ca1dedeb99c81eab2047841b752':
    raise SystemExit('target identity/length mismatch')
functions = sorted(report['matches'], key=lambda x: int(x['address'], 0))
OUT.mkdir(parents=True, exist_ok=True)
results = []

for left, right in zip(functions, functions[1:]):
    start = int(left['address'], 0)
    end = start + int(left['size'])
    next_start = int(right['address'], 0)
    gap = next_start - end
    if not 0 < gap <= 4:
        continue
    left_obj = (BASE / left['binary']).with_suffix('.o')
    right_obj = (BASE / right['binary']).with_suffix('.o')
    if not left_obj.is_file() or not right_obj.is_file():
        raise SystemExit(f'missing object for {left["name"]} -> {right["name"]}')
    script = OUT / f'{start:08x}_{next_start:08x}.ld'
    elf = script.with_suffix('.elf')
    raw = script.with_suffix('.bin')
    script.write_text(
        f'SECTIONS {{ .text {start:#x} : {{ *(.text.{left["name"]}) *(.text.{right["name"]}) }} '
        '/DISCARD/ : { *(.ARM.exidx*) *(.ARM.extab*) *(.comment*) *(.note*) *(.debug*) *(.data*) *(.bss*) *(.rodata*) } }\n'
    )
    symbols = {}
    for entry in (left, right):
        for item in entry.get('defsyms', []):
            name, value = item.split('=', 1)
            if name in symbols and symbols[name] != value:
                raise SystemExit(f'conflicting defsym {name}: {symbols[name]} vs {value}')
            symbols[name] = value
    cmd = [str(TOOL / 'arm-none-eabi-ld'), '-T', str(script), '--unresolved-symbols=ignore-all']
    for name, value in symbols.items():
        cmd += ['--defsym', f'{name}={value}']
    cmd += [str(left_obj), str(right_obj), '-o', str(elf)]
    subprocess.run(cmd, check=True, capture_output=True, text=True)
    subprocess.run([str(TOOL / 'arm-none-eabi-objcopy'), '-O', 'binary', '--only-section=.text', str(elf), str(raw)], check=True)
    linked = raw.read_bytes()
    expected = image[end - FLASH:next_start - FLASH]
    actual = linked[int(left['size']):int(left['size']) + gap]
    expected_pair = image[start - FLASH:next_start + int(right['size']) - FLASH]
    pair_match = len(linked) == len(expected_pair) and linked == expected_pair
    pair_diff_count = sum(a != b for a, b in zip(linked, expected_pair)) + abs(len(linked) - len(expected_pair))
    nm = subprocess.check_output([str(TOOL / 'arm-none-eabi-nm'), '-n', str(elf)], text=True)
    next_symbol = next((line for line in nm.splitlines() if line.split()[-1] == right['name']), None)
    if next_symbol is None:
        raise SystemExit(f'next symbol absent: {right["name"]}')
    address = int(next_symbol.split()[0], 16) & ~1
    passed = len(actual) == gap and actual == expected and address == next_start
    result = {
        'from': left['name'], 'to': right['name'], 'gap_start': f'{end:#010x}',
        'gap_bytes': gap, 'target_hex': expected.hex(), 'linked_hex': actual.hex(),
        'next_symbol': f'{address:#010x}', 'pass': passed,
        'pair_bytes': len(linked), 'pair_match': pair_match, 'pair_diff_count': pair_diff_count,
        'objects': [str(left_obj), str(right_obj)], 'linker_script': str(script),
    }
    results.append(result)
    print(json.dumps(result, sort_keys=True))

runtime = next((x for x in report.get('runtime_matches', []) if x['name'] == 'libgcc:_arm_truncdfsf2.o:.text'), None)
right = next((x for x in report['matches'] if x['name'] == 'FUN_08000a98'), None)
if runtime is None or right is None:
    raise SystemExit('missing accepted runtime/C pair for the 0x08000a94 gap')
start = int(runtime['address'], 0)
left_size = int(runtime['size'])
next_start = int(right['address'], 0)
gap = next_start - (start + left_size)
left_obj = BASE / runtime['object']
right_obj = (BASE / right['binary']).with_suffix('.o')
script = OUT / f'{start:08x}_{next_start:08x}.ld'
elf = script.with_suffix('.elf')
raw = script.with_suffix('.bin')
script.write_text(
    f'SECTIONS {{ .text {start:#x} : {{ *(.text) *(.text.{right["name"]}) }} '
    '/DISCARD/ : { *(.ARM.exidx*) *(.ARM.extab*) *(.comment*) *(.note*) *(.debug*) *(.data*) *(.bss*) *(.rodata*) } }\n'
)
cmd = [str(TOOL / 'arm-none-eabi-ld'), '-T', str(script), '--unresolved-symbols=ignore-all']
for item in right.get('defsyms', []):
    cmd += ['--defsym', item]
cmd += [str(left_obj), str(right_obj), '-o', str(elf)]
subprocess.run(cmd, check=True, capture_output=True, text=True)
subprocess.run([str(TOOL / 'arm-none-eabi-objcopy'), '-O', 'binary', '--only-section=.text', str(elf), str(raw)], check=True)
linked = raw.read_bytes()
expected_gap = image[start + left_size - FLASH:next_start - FLASH]
actual_gap = linked[left_size:left_size + gap]
expected_pair = image[start - FLASH:next_start + int(right['size']) - FLASH]
pair_match = len(linked) == len(expected_pair) and linked == expected_pair
nm = subprocess.check_output([str(TOOL / 'arm-none-eabi-nm'), '-n', str(elf)], text=True)
next_symbol = next((line for line in nm.splitlines() if line.split()[-1] == right['name']), None)
if next_symbol is None:
    raise SystemExit(f'next symbol absent: {right["name"]}')
address = int(next_symbol.split()[0], 16) & ~1
passed = gap == 4 and actual_gap == expected_gap and address == next_start and pair_match
results.append({
    'from': runtime['name'], 'to': right['name'], 'gap_start': f'{start + left_size:#010x}',
    'gap_bytes': gap, 'target_hex': expected_gap.hex(), 'linked_hex': actual_gap.hex(),
    'next_symbol': f'{address:#010x}', 'pass': passed, 'pair_bytes': len(linked),
    'pair_match': pair_match, 'pair_diff_count': sum(a != b for a, b in zip(linked, expected_pair)) + abs(len(linked) - len(expected_pair)),
    'objects': [str(left_obj), str(right_obj)], 'linker_script': str(script),
})
print(json.dumps(results[-1], sort_keys=True))

summary = {'checked': len(results), 'passed': sum(x['pass'] for x in results), 'all_pass': bool(results) and all(x['pass'] for x in results)}
(OUT / 'result.json').write_text(json.dumps({'target_sha256': report['firmware_sha256'], **summary, 'results': results}, indent=2) + '\n')
print(json.dumps(summary, sort_keys=True))
if not summary['all_pass']:
    raise SystemExit(1)
