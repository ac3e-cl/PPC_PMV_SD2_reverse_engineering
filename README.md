# PPC_PMV_SD2 — proyecto de fuentes STM32G474RETx

Proyecto organizado para importar en **STM32CubeIDE** como biblioteca estática de fragmentos para el objetivo STM32G474RETx (STM32G474RET6). La estructura sigue el patrón CubeIDE (`Core/Inc`, `Core/Src`, `.project`, `.cproject`); no incluye dependencias o binarios generados innecesarios.

## Alcance y limitaciones

Incluye 124 unidades de traducción C que contienen 178 funciones aceptadas por matching y una reconstrucción en ensamblador legible de `HAL_ADC_ConfigChannel` (2.176 bytes). Esta última está separada bajo `Core/Src/assembly/` y **no es C**.

Esto es una biblioteca estática de las fuentes recuperadas, no una aplicación firmware completa ni un ejecutable listo para flashear. No están incluidos el runtime de libgcc, startup/vector table original, linker script, HAL/CMSIS completos, datos de imagen ni los símbolos externos originales necesarios para formar un único enlace. Por ello, la compilación de CubeIDE produce objetos/biblioteca, no una imagen arrancable ni una reproducción completa del binario. No se debe añadir un `main()` ficticio ni tratar esta biblioteca como firmware desplegable.

## Abrir en STM32CubeIDE

1. `File > Import... > General > Existing Projects into Workspace`.
2. Selecciona `/home/isaiash/PPC_PMV_SD2_reverse_engineering` como raíz y marca el proyecto detectado.
3. Selecciona configuración `Debug` y ejecuta `Project > Build Project`.

La configuración apunta a STM32G474RETx, Cortex-M4, FPU FPv4-SP-D16 y ABI hard. Las fuentes conservan flags de reconstrucción independientes; los valores exactos usados para las pruebas por fragmento están en `manifest.json`. La configuración CubeIDE es principalmente para explorar/compilar como biblioteca; **no valida matching exacto al compilar todos los archivos con un único set global de flags**.

## Requisitos y pruebas reproducibles

- Python 3.10+.
- GNU Tools for STM32 13.3.1 (ARM GCC, ld y objcopy). Por defecto el test usa `~/.local/opt/gnu-tools-for-stm32-13.3.rel1`; configura `ARM_TC` para indicar otra raíz.
- `make` es opcional.

Desde la raíz del repositorio:

```sh
python3 tests/test_sources.py
# equivalente:
make test
```

El test compila las **124 unidades C** con flags asociados a una función de cada unidad (prueba de compilación, no de enlace), y ensambla/enlaza `HAL_ADC_ConfigChannel` en su dirección original para verificar longitud y SHA-256 exactos de sus 2.176 bytes. Los hashes y parámetros esperados están en `manifest.json`; la imagen de referencia no se incluye. La compilación C es compile-only porque símbolos externos absolutos y mapas de memoria por función no pueden inferirse correctamente para un enlace común. Un `PASS C compile` significa solo que el compilador produjo el objeto, no que ese bloque C iguale byte por byte al original en esta prueba aislada.

`make clean` elimina `build/`, `Debug/` y `Release/`.

## Git

Este directorio es un repositorio Git; los resultados y objetos compilados están ignorados. Revisa los cambios con `git status` y crea commits según el flujo de trabajo del equipo.

## Seguridad y procedencia

La reconstrucción binaria completa histórica fue una mezcla de C, ensamblador, startup, runtime y datos; sus fuentes se mantienen fuera de este paquete para cumplir el alcance de solo fuentes de código del proyecto. La placa auxiliar no era la placa de referencia; no se validó el firmware completo en hardware ni se flasheó. No usar estos fragmentos para energizar una etapa de potencia.
