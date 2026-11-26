#include "registers.h"

uint32_t FUN_08002d5c(Registers *r)
{
    return r->CR & 0x1fU;
}
