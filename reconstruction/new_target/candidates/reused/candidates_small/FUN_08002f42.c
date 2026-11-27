#include "registers.h"

void FUN_08002f42(Registers *r)
{
    r->CR = (r->CR & 0x7fffffc0U) | 0x20U;
}
