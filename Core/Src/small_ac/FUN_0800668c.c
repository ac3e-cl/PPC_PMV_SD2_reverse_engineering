#include <stdint.h>

typedef struct {
    volatile uint32_t reserved[0x3d4 / 4];
    volatile uint32_t config;
} Peripheral;

typedef struct {
    Peripheral *Instance;
    uint8_t reserved[0xd8];
    uint8_t busy;
    volatile uint8_t state;
} Handle;

uint32_t FUN_0800668c(Handle *handle, uint32_t param_2)
{
    if (handle->state == 2) return 2;
    if (handle->busy == 1) return 2;
    handle->busy = 1;
    handle->state = 2;
    handle->Instance->config = (handle->Instance->config & 0xfcffffffu) |
                               (param_2 & 0x03000000u);
    handle->state = 1;
    handle->busy = 0;
    return 0;
}
