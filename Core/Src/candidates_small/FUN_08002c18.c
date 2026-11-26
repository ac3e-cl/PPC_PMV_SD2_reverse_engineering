#include "registers.h"

uint32_t FUN_08002c18(Registers *r)
{
    return ((r->CFGR & 0xc00U) == 0x0U) ? 1U : 0U;
}
