#include "registers.h"

uint32_t FUN_08002e08(Registers *r)
{
    return ((r->CR & 0x10000000U) == 0x10000000U) ? 1U : 0U;
}
