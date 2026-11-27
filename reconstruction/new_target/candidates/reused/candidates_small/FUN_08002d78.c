#include "registers.h"

uint32_t FUN_08002d78(Registers *r)
{
    return r->CR & 0xe000U;
}
