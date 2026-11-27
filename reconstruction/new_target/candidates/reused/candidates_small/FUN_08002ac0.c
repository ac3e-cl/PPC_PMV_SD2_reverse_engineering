#include "registers.h"

uint32_t FUN_08002ac0(Registers *r)
{
    return r->CR & 0x1c00000U;
}
