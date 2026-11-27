#include "registers.h"

void FUN_08002e30(Registers *r)
{
    r->CR = (r->CR & 0x7fffffc0U) | 0x1U;
}
