# Prebuilt Release library

`libPPC_PMV_SD2_reverse_engineering.a` is the CMake `Release` static library for the STM32G474RETx target. It contains 124 compiled C translation units plus the reconstructed `HAL_ADC_ConfigChannel` assembly unit (125 archive members total). This is the build product of this repository, not a complete firmware image.

Verify integrity from this directory:

```sh
sha256sum -c libPPC_PMV_SD2_reverse_engineering.a.sha256
```

The archive is built deterministically (`ar qcD`, `ranlib -D`) so a clean rebuild with the same compiler/toolchain and sources can be compared byte for byte. `.elf` and `.bin` are intentionally absent: the repository does not contain the startup, vector table, runtime, memory map/linker script, and complete data needed to link a bootable image. Creating those files would imply a firmware executable that this CMake library does not provide.
