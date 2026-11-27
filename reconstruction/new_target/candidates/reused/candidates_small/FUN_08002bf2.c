#include "registers.h"

void FUN_08002bf2(Registers *r, uint32_t value)
{
    r->SMPR1 = (r->SMPR1 & 0x7fffffffU) | value;
}
