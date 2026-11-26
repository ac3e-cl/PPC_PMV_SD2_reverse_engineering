#include <stdbool.h>
#include <stdint.h>

typedef struct { volatile uint32_t regs[7]; } Peripheral;
typedef struct {
    Peripheral *Instance;
    uint8_t reserved[0x58];
    volatile uint8_t state;
    uint8_t pad[3];
    uint32_t status;
} Handle;

bool FUN_080052bc(Handle *param_1)
{
    if (param_1->state == 1u) {
        param_1->state = 2;
        param_1->Instance->regs[6] &= ~1u;
        param_1->status = 0;
        return false;
    }
    param_1->status |= 4u;
    return true;
}
