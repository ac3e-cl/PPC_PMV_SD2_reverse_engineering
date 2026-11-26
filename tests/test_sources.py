#!/usr/bin/env python3
"""Compile all pinned C sources and exactly verify the reconstructed ADC assembly."""
from pathlib import Path
import hashlib
import json
import os
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = json.loads((ROOT / 'manifest.json').read_text())
TC = Path(os.environ.get('ARM_TC', str(Path.home() / '.local/opt/gnu-tools-for-stm32-13.3.rel1'))) / 'bin'
CC, LD, OBJCOPY = (str(TC / f'arm-none-eabi-{x}') for x in ('gcc', 'ld', 'objcopy'))


def run(args):
    subprocess.run(args, check=True, cwd=ROOT)


def build(entry, assembly=False):
    name, addr = entry['name'], int(entry['address'], 16)
    with tempfile.TemporaryDirectory(prefix='fw-match-') as td:
        d = Path(td); obj, elf, binary = d/'unit.o', d/'unit.elf', d/'unit.bin'
        flags = entry['flags'] if isinstance(entry['flags'], list) else entry['flags'].split()
        run([CC, *flags, '-I', str(ROOT/'Core/Inc'), '-c', str(ROOT/entry['source']), '-o', str(obj)])
        if not assembly:
            if not obj.is_file() or obj.stat().st_size == 0:
                raise AssertionError(f'compiler produced no object for {name}')
            return
        section = f'.text.{name}'
        (d/'unit.ld').write_text(f'ENTRY({name})\nSECTIONS {{ .text {addr:#x} : {{ KEEP(*({section})) }} }}\n')
        defs = entry['defsyms']
        if isinstance(defs, list):
            defs = dict(x.split('=', 1) for x in defs)
        run([LD, '--fatal-warnings', *[f'--defsym={k}={v}' for k,v in defs.items()], '-T', str(d/'unit.ld'), str(obj), '-o', str(elf)])
        run([OBJCOPY, '-O', 'binary', '--only-section=.text', str(elf), str(binary)])
        actual = binary.read_bytes(); digest = hashlib.sha256(actual).hexdigest()
        if len(actual) != entry['size'] or digest != entry['sha256']:
            raise AssertionError(f'{name} at {addr:#010x}: got {len(actual)} bytes sha256={digest}; expected {entry["size"]} bytes sha256={entry["sha256"]}')


def main():
    sources = sorted({e['source'] for e in MANIFEST['c_entries']})
    for i, source in enumerate(sources, 1):
        entries = [e for e in MANIFEST['c_entries'] if e['source'] == source]
        # Compile this translation unit using the flags from its first recorded entry.
        build(entries[0])
        print(f'PASS C compile {i}/{len(sources)}: {source}')
    entry = MANIFEST['assembly_entry']; build(entry, assembly=True)
    print(f'PASS exact reconstructed assembly (not C): {entry["name"]}, {entry["size"]} bytes')
    print('NOTE: C compilation is compile-only; whole-section matching needs per-entry symbol resolution.')


if __name__ == '__main__':
    main()
