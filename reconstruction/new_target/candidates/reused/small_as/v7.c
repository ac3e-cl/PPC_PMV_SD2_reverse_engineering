#include <stdint.h>

uint32_t FUN_08004e28(uint32_t param_1, uint32_t param_2, uint32_t param_3)
{
    uint32_t a = param_1 & 7u;
    /* Ternary with (7u - a) inline: -O0 keeps the rsb result in r3 across the
       it cs/mov.cs, so the clamp stores once instead of spilling first. */
    uint32_t uVar1 = (7u - a) >= 4u ? 4u : 7u - a;
    uint32_t c = a + 4u > 6u ? a - 3u : 0u;
    return ((~(0xffffffffu << uVar1) & param_2) << c) | (param_3 & ~(0xffffffffu << c));
}
