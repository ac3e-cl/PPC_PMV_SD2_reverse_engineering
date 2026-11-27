# PPC_PMV_SD2_reverse_engineering — STM32CubeIDE

Proyecto gestionado para STM32G474RETx (Cortex-M4, FPv4-SP-D16, ABI hard), con configuraciones Debug/Release, `.ioc`, startup, linker scripts y dependencias CMSIS/HAL. En STM32CubeIDE impórtalo con **File → Import → General → Existing Projects into Workspace** y selecciona esta carpeta.

## Reconstruir el BIN exacto

Desde la raíz del repositorio ejecuta:

```sh
make firmware
```

El objetivo recompila y compara estrictamente las secciones fuente aceptadas, runtime, datos, startup ST, ensamblador ADC y alineaciones verificadas; arma el candidato completo en `reconstruction/new_target/full_image/build/candidate.bin`, exige 38.536 bytes y cero diferencias, y actualiza `bin/PPC_PMV_SD2_reverse_engineering.bin`. El BIN versionado se usa como referencia de comparación; el constructor no copia bytes de esa referencia para rellenar huecos. Los verificadores exigen cobertura completa antes de producir el candidato.

Requisitos: Python 3.10+, GNU Make y las versiones exactas **GNU Tools for STM32 13.3.1** y **14.3.1**. Los valores por defecto esperan las instalaciones bajo `~/.local/opt/gnu-tools-for-stm32-13.3.rel1` y `~/.local/opt/gnu-tools-for-stm32-14.3.rel1/tools`. Si están en otra ubicación, configura `ARM_TC` y `ARM_TC_14_3`, respectivamente.

```sh
make test
(cd bin && sha256sum -c PPC_PMV_SD2_reverse_engineering.bin.sha256)
```

## Alcance y procedencia

La imagen final se reconstruye a partir de fragmentos independientes con direcciones fijas y después se verifica byte por byte. Incluye 165 secciones C, 2.176 bytes de ensamblador reconstruido para ADC, runtime, datos, startup de ST y 22 bytes de alineación. El ensamblador ADC y el startup de proveedor están clasificados por separado; no se cuentan como C.

El proyecto es importable en CubeIDE, pero su conjunto de fuentes no constituye un enlace integral de una aplicación original completa ni produce por sí solo un ELF depurable equivalente. No se probó la importación con la GUI (CubeIDE no está instalado en este entorno); el flujo reproducible del BIN es `make firmware`, que puede ejecutarse desde una terminal integrada del IDE. No se flasheó hardware.
