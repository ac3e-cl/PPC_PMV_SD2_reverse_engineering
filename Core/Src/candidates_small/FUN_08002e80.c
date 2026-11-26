#include "registers.h"

uint32_t FUN_08002e80(Registers *r)
{
    return ((r->CR & 0x1U) == 0x1U) ? 1U : 0U;
}
