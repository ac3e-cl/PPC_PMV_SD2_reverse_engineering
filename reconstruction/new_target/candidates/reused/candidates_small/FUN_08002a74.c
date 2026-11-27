#include "registers.h"

void FUN_08002a74(Registers *r, uint32_t value)
{
    r->CR = (r->CR & 0xffc0ffffU) | value;
}
