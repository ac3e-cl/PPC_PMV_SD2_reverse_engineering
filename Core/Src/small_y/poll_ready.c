#include <stdint.h>
extern uint32_t HAL_GetTick(void);
typedef struct { volatile uint32_t registers[0x389/4]; } Peripheral;
typedef struct { Peripheral *Instance; uint8_t reserved[0xd8]; uint8_t busy; uint8_t state; } Handle;

uint32_t FUN_08006254(Handle *handle, uint32_t timeout)
{
    uint32_t start = HAL_GetTick();
    while ((handle->Instance->registers[0x388/4] & 0x10000u) != 0x10000u) {
        if (timeout != 0xffffffffu &&
            ((HAL_GetTick() - start) > timeout || timeout == 0u)) {
            handle->state = 7;
            return 3;
        }
    }
    handle->state = 1;
    handle->busy = 0;
    return 0;
}