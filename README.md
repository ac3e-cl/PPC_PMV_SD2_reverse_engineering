# PPC_PMV_SD2 — proyecto CMake para STM32CubeIDE

Proyecto CMake importable en STM32CubeIDE para STM32G474RETx (STM32G474RET6). Incluye 124 unidades C con 178 funciones aceptadas por matching y una reconstrucción legible en ensamblador de `HAL_ADC_ConfigChannel` (2.176 bytes). La función ensamblador no se contabiliza como C.

## Importar en STM32CubeIDE

Requiere **STM32CubeIDE 2.0.0 o posterior** y CMake **3.30.8 o posterior** para el flujo CMake de STM32CubeIDE (según la nota ST AN5952).

1. Abre `File > STM32 Project Create/Import`.
2. Elige `Import STM32 Project` y selecciona `STM32 CMake Project`.
3. Selecciona este repositorio como la estructura CMake existente (raíz/source directory del repositorio).
4. Elige el toolchain MCU ARM GCC y el dispositivo STM32G474RETx; configura el preset CMake `Debug` o `Release`.
5. Ejecuta `Build Project`. El resultado será una biblioteca estática.

Referencia oficial ST: [AN5952 — How to use CMake in STM32CubeIDE](https://www.st.com/resource/en/application_note/an5952-how-to-use-cmake-in-stm32cubeide-stmicroelectronics.pdf).

También se puede compilar desde consola con CMake y Ninja:

```sh
cmake --preset Debug
cmake --build --preset Debug
# o Release
cmake --preset Release
cmake --build --preset Release
```

Los presets usan `cmake/arm-none-eabi-gcc.cmake`. El toolchain se busca en `$ARM_TC`, luego `$GNU_TOOLS_FOR_STM32_COMPILER_PATH`, y como fallback en `~/.local/opt/gnu-tools-for-stm32-13.3.rel1`; también puede estar en `PATH`. Para CMake CLI se requiere CMake ≥3.21 y Ninja. La salida es `build/cmake/<preset>/lib/libPPC_PMV_SD2_reverse_engineering.a`.

## Pruebas

Con Python 3.10+ y GNU Tools for STM32 13.3.1:

```sh
python3 tests/test_sources.py
# o
make test
```

Esto compila las 124 unidades C y ensambla/enlaza `HAL_ADC_ConfigChannel` en su dirección original, verificando longitud y SHA-256 exactos de sus 2.176 bytes. La prueba C es de compilación, no de enlace ni de igualdad binaria por función; `manifest.json` conserva flags, direcciones, símbolos y hashes aceptados. No se distribuye la imagen de referencia.

CMake crea una biblioteca estática de los fragmentos, usando por unidad los flags de la primera entrada de esa unidad registrados en el manifiesto. Los flags por función pueden diferir dentro de una unidad; por eso el artefacto de biblioteca no se presenta como matching exacto del firmware. La prueba Python separada sigue siendo la verificación focal reproducible.

## Alcance

Este repositorio **no** es una imagen completa ni un ejecutable arrancable para flashear. No incluye startup/vector table original, linker script, runtime libgcc, todos los datos ni símbolos externos para reconstruir el enlace completo. La igualdad completa observada previamente correspondía a una imagen mixta de C, ensamblador, startup, runtime y datos; sus componentes de build/experimentales se excluyeron aquí.

La placa auxiliar no era la de referencia; no se validó el firmware completo en hardware ni se flasheó. No usar estos fragmentos para energizar una etapa de potencia.
