#include "registers.h"

void FUN_08002e58(Registers *r)
{
    r->CR = (r->CR & 0x7fffffc0U) | 0x2U;
}
