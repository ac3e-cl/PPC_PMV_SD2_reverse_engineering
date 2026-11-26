#include "registers.h"

void FUN_08002d94(Registers *r)
{
    r->CR = (r->CR & 0x5fffffc0U);
}
