#include <stdint.h>

typedef struct {
    volatile uint32_t control;
    uint8_t reserved_04[8];
    volatile uint32_t enable;
    uint8_t reserved_10[16];
    volatile uint32_t status;
} Peripheral;

typedef struct {
    Peripheral *peripheral;
    uint8_t reserved_04[0x39];
    uint8_t status;
} Handle;

int FUN_08009378(Handle *handle)
{
    handle->peripheral->enable &= ~1u;
    if ((handle->peripheral->status & 0x1111u) == 0u &&
        (handle->peripheral->status & 0x4444u) == 0u) {
        handle->peripheral->control &= ~1u;
    }
    handle->status = 1u;
    return 0;
}
