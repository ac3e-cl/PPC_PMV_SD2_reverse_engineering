# Release artifacts

This folder intentionally contains two different deliverables:

- `libPPC_PMV_SD2_reverse_engineering.a`: prebuilt static archive from the repository's previous CMake fragment-library configuration (124 C translation units + 1 ASM object). It is retained as a historical binary artifact; the current project uses the STM32CubeIDE managed Makefile executable project type and does not build this archive.
- `firmware.bin`: the complete 39,560-byte image from the previously verified mixed-source reconstruction. SHA-256: `6061eaf7d206f075f8c80e78b6ca227219004336b732e5b7c52ddcc2939d606b`.
- `firmware.elf`: an ELF32/ARM executable container for that exact `.bin`, with one loadable `.firmware` segment at `0x08000000` and entry `0x080028fd` from the binary's reset vector. Its firmware segment was extracted and compared byte-for-byte with `firmware.bin`. It is a minimal wrapper without DWARF/debug symbols, not a full source-linked IDE ELF.

The firmware image pair is retained from the previously verified mixed-source reconstruction; it is not rebuilt by the current CubeIDE project because its source set lacks the complete application/startup/runtime/data needed for a full link.

Verify checksums from this directory:

```sh
sha256sum -c firmware.sha256
sha256sum -c libPPC_PMV_SD2_reverse_engineering.a.sha256
```

The static archive is deterministic (`ar qcD`, `ranlib -D`) and repeated clean Release builds were byte-identical. Do not flash or run the firmware without separately validating the target hardware and deployment safety.
