#include "registers.h"

void FUN_08002adc(Registers *r, uint32_t index, uint32_t channel, uint32_t offset)
{
    volatile uint32_t *reg = (volatile uint32_t *)((uint32_t)&r->OFR[0] + (index << 2));
    *reg = (*reg & 0x03fff000U) | ((channel & 0x7c000000U) | offset) | 0x80000000U;
}
