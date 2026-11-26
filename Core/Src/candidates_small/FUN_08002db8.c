#include "registers.h"

uint32_t FUN_08002db8(Registers *r)
{
    return ((r->CR & 0x20000000U) == 0x20000000U) ? 1U : 0U;
}
