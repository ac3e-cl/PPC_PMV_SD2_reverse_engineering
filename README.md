# PPC_PMV_SD2 — proyecto STM32CubeIDE (managed Makefile)

Proyecto convertido al mismo tipo y configuración STM32CubeIDE que `/home/isaiash/PPC_PMV_SD2`: MCU executable, builder gestionado de CubeIDE/Make, configuraciones `Debug` y `Release`, STM32G474RETx, Cortex-M4, FPv4-SP-D16 y ABI hard. La configuración CubeMX `.ioc`, startup, drivers STM32CubeG4, headers de plataforma y linker scripts se copiaron desde el proyecto base; el nombre de proyecto y las rutas de salida se ajustaron para este repositorio. El código reconstruido permanece bajo `Core/Src` y el header de registros bajo `Core/Inc`.

Se conservaron los fragmentos fuente: 124 unidades C con 178 funciones aceptadas por matching, más `HAL_ADC_ConfigChannel` en ensamblador legible. Esa función no se cuenta como C.

## Abrir y compilar

Importa el repositorio en STM32CubeIDE mediante `File > Import... > General > Existing Projects into Workspace`, seleccionando la raíz para detectar `.project`. El proyecto incluye las configuraciones `Debug` y `Release`; la configuración del dispositivo corresponde a STM32G474RETx y el `.ioc` conserva el proyecto CubeMX base.

El `.cproject` produce un ejecutable STM32CubeIDE (`.elf`) y tiene habilitadas las salidas HEX/BIN igual que el proyecto base. **Sin embargo, el conjunto de fuentes reconstruidas de este repositorio no contiene el programa completo ni todas las unidades de aplicación requeridas para un enlace de firmware arrancable** (por ejemplo, `main` y el wiring de interrupciones/MSP de la aplicación). Por tanto, la configuración de IDE se conserva, pero no afirmo que este source set actual pueda producir un nuevo ELF/BIN válido. No agregué código de aplicación del proyecto base ni un `main()` ficticio para ocultar esa carencia.

## Fuentes y pruebas de matching

Con Python 3.10+ y GNU Tools for STM32 13.3.1 ejecuta desde la raíz:

```sh
python3 tests/test_sources.py
# o
make test
```

Esto compila las 124 unidades C y ensambla/enlaza `HAL_ADC_ConfigChannel` en su dirección original; se exige el tamaño y SHA-256 exactos para sus 2.176 bytes. La prueba de C es compile-only, no prueba el enlace completo ni verifica byte-matching de cada función; los flags, direcciones, símbolos y hashes aceptados están en `manifest.json`.

## Artefactos precompilados

`artifacts/Release/` conserva la biblioteca estática generada antes del cambio de tipo de proyecto y el par `firmware.elf`/`firmware.bin` de la reconstrucción mixta completa verificada. El binario es de 39.560 bytes y coincide byte por byte con la imagen de referencia. El ELF es un contenedor ejecutable mínimo del mismo binario, con un único segmento `.firmware`, entry del vector de reset y sin símbolos DWARF. **Estos artefactos no se regeneran desde el source set actual de este proyecto**; sus procedencias y checksums están documentados en `artifacts/Release/README.md`.

Verifica los checksums desde `artifacts/Release/`:

```sh
sha256sum -c firmware.sha256
sha256sum -c libPPC_PMV_SD2_reverse_engineering.a.sha256
```

No se validó el firmware completo en hardware ni se flasheó. La placa auxiliar no era la placa objetivo. No usar estos archivos para energizar una etapa de potencia sin revisar el hardware y el firmware de destino.
