#include "registers.h"

void FUN_08002bbc(Registers *r, uint32_t index, uint32_t value)
{
    volatile uint32_t *reg = (volatile uint32_t *)((uint32_t)&r->OFR[0] + (index << 2));
    *reg = (*reg & 0xfdffffffU) | value;
}
