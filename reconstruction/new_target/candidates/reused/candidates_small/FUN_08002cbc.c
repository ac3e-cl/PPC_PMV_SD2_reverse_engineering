#include "registers.h"

void FUN_08002cbc(Registers *r, uint32_t channel, uint32_t sampling)
{
    volatile uint32_t *reg = (volatile uint32_t *)((uint32_t)&r->SMPR1 + (((channel >> 25) & 1U) << 2));
    *reg = (*reg & ~(7U << ((channel >> 20) & 0x1fU))) | (sampling << ((channel >> 20) & 0x1fU));
}
