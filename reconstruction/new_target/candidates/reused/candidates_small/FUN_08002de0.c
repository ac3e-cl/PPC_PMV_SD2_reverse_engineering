#include "registers.h"

void FUN_08002de0(Registers *r)
{
    r->CR = (r->CR & 0x6fffffc0U) | 0x10000000U;
}
