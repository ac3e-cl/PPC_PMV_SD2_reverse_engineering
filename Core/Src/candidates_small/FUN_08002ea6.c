#include "registers.h"

uint32_t FUN_08002ea6(Registers *r)
{
    return ((r->CR & 0x2U) == 0x2U) ? 1U : 0U;
}
