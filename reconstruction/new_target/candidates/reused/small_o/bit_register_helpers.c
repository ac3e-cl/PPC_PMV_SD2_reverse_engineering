#include <stdint.h>

typedef struct {
    volatile uint32_t control;
    volatile uint8_t reserved[0x394 - sizeof(uint32_t)];
    volatile uint32_t request;
} Peripheral;

typedef struct {
    Peripheral *Instance;
    uint8_t reserved[0xd8];
    uint8_t state;
    uint8_t busy;
} Handle;

uint32_t FUN_080078aa(Handle *param_1, uint32_t param_2)
{
    if (param_1->state == 1) {
        return 2;
    }
    param_1->state = 1;
    param_1->busy = 2;
    param_1->Instance->control |= param_2;
    param_1->busy = 1;
    param_1->state = 0;
    return 0;
}

uint32_t FUN_08007900(Handle *param_1, uint32_t param_2)
{
    if (param_1->state == 1) {
        return 2;
    }
    param_1->state = 1;
    param_1->busy = 2;
    param_1->Instance->control &= ~param_2;
    param_1->busy = 1;
    param_1->state = 0;
    return 0;
}
