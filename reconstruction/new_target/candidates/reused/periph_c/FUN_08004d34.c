#include <stdint.h>

typedef struct {
    volatile uint32_t reserved[3];
    volatile uint32_t CPACR;
} SCB_Type;
extern volatile SCB_Type SCB_BASE;

void FUN_08004d34(uint32_t param_1)
{
    uint32_t field = param_1 & 7u;
    uint32_t value = SCB_BASE.CPACR;
    value &= 0x0000f8ffu;
    value = value | (field << 8) | 0x05fa0000u;
    SCB_BASE.CPACR = value;
}
