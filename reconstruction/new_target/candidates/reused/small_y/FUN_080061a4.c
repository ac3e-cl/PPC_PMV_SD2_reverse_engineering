#include <stdint.h>
typedef struct { volatile uint32_t registers[0x3d0/4]; } Peripheral;
typedef struct { Peripheral *Instance; uint8_t reserved[0xd8]; uint8_t busy; uint8_t state; } Handle;

uint32_t FUN_080061a4(Handle *handle, uint32_t mode)
{
    if (handle->busy == 1) {
        return 2;
    }
    handle->busy = 1;
    handle->state = 2;
    if (mode == 0xffffffffu) {
        handle->Instance->registers[0x3cc/4] &= ~2u;
        handle->Instance->registers[0x3cc/4] |= 1u;
    } else {
        handle->Instance->registers[0x3cc/4] |= 2u;
        handle->Instance->registers[0x3cc/4] = (handle->Instance->registers[0x3cc/4] & ~0xcu) | mode;
        handle->Instance->registers[0x3cc/4] |= 1u;
    }
    handle->state = 1;
    return 0;
}
