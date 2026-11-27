#include "registers.h"

void FUN_08002c3e(Registers *r, uint32_t rank, uint32_t channel)
{
    volatile uint32_t *reg = (volatile uint32_t *)((uint32_t)&r->SQR1 + (((rank >> 8) & 3U) << 2));
    *reg = (*reg & ~(0x1fU << (rank & 0x1fU))) | (((channel >> 26) & 0x1fU) << (rank & 0x1fU));
}
