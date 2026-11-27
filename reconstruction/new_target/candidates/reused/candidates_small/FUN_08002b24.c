#include "registers.h"

uint32_t FUN_08002b24(Registers *r, uint32_t index)
{
    volatile uint32_t *reg = (volatile uint32_t *)((uint32_t)&r->OFR[0] + (index << 2));
    return *reg & 0x7c000000U;
}
