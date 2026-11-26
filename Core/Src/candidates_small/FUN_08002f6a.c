#include "registers.h"

uint32_t FUN_08002f6a(Registers *r)
{
    return ((r->CR & 0x8U) == 0x8U) ? 1U : 0U;
}
