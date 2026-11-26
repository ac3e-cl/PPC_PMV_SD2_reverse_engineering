#include "registers.h"

void FUN_08002a9a(Registers *r, uint32_t value)
{
    r->CR = (r->CR & 0xfe3fffffU) | value;
}
