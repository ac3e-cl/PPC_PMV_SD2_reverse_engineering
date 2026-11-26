/* FUN_0800810c: enable one HRTIM output by index (switch jump table). */
#include <stdint.h>

typedef struct { uint32_t *Instance; } HrtHandle;
typedef struct { volatile uint32_t p0[225]; volatile uint32_t CTRL; } HrtPeriph;

void FUN_0800810c(HrtHandle *param_1, uint32_t param_2)
{
    switch (param_2) {
    case 6:
        ((HrtPeriph *)param_1->Instance)->CTRL = ((HrtPeriph *)param_1->Instance)->CTRL | 1u;
        break;
    case 0:
        ((HrtPeriph *)param_1->Instance)->CTRL = ((HrtPeriph *)param_1->Instance)->CTRL | 2u;
        break;
    case 1:
        ((HrtPeriph *)param_1->Instance)->CTRL = ((HrtPeriph *)param_1->Instance)->CTRL | 4u;
        break;
    case 2:
        ((HrtPeriph *)param_1->Instance)->CTRL = ((HrtPeriph *)param_1->Instance)->CTRL | 8u;
        break;
    case 3:
        ((HrtPeriph *)param_1->Instance)->CTRL = ((HrtPeriph *)param_1->Instance)->CTRL | 0x10u;
        break;
    case 4:
        ((HrtPeriph *)param_1->Instance)->CTRL = ((HrtPeriph *)param_1->Instance)->CTRL | 0x20u;
        break;
    case 5:
        ((HrtPeriph *)param_1->Instance)->CTRL = ((HrtPeriph *)param_1->Instance)->CTRL | 0x40u;
        break;
    default:
        break;
    }
}
