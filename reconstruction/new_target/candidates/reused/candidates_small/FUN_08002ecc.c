#include "registers.h"

void FUN_08002ecc(Registers *r)
{
    r->CR = (r->CR & 0x7fffffc0U) | 0x4U;
}
