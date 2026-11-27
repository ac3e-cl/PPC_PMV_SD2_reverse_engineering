#include "registers.h"

uint32_t FUN_08002c96(Registers *r)
{
    return ((r->JSQR & 0x180U) == 0x0U) ? 1U : 0U;
}
