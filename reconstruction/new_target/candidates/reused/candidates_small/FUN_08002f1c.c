#include "registers.h"

uint32_t FUN_08002f1c(Registers *r)
{
    return ((r->CR & 0x4U) == 0x4U) ? 1U : 0U;
}
