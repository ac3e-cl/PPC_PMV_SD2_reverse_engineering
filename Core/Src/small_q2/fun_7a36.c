/* FUN_08007a36: compose channel word + ext word from a config struct into
 * the block referenced by *param_1. All constants fold to modified immediates. */
#include <stdint.h>

typedef struct {
    uint32_t pad00[5];
    uint32_t f14;
    uint32_t f18;
    uint32_t f1c;
    uint32_t f20;
    uint32_t f24;
    uint32_t f28;
    uint32_t f2c;
    uint32_t f30;
    uint32_t f34;
} cfg_t;

typedef struct {
    uint32_t f00;
    uint32_t pad04[0xe7];
    uint32_t f3a0;
} blk_t;

void FUN_08007a36(blk_t **param_1, cfg_t *param_2)
{
    uint32_t uVar1;
    uint32_t local_c;

    local_c = (*param_1)->f00;
    uVar1 = (*param_1)->f3a0;
    local_c &= ~0x20u;
    local_c = param_2->f14 | local_c;
    local_c &= ~0xc0u;
    if (param_2->f14 == 0x20u || param_2->f18 == 2u) {
        local_c &= ~0xc0u;
        local_c |= 0x20u;
    } else if (param_2->f18 == 3u) {
        local_c |= 0x40u;
        local_c &= ~0x80u;
    } else if (param_2->f18 == 4u) {
        local_c |= 0x80u;
        local_c &= ~0x40u;
    } else {
        local_c &= ~0x20u;
        local_c &= ~0xc0u;
    }
    local_c &= ~0x800u;
    local_c = param_2->f1c | local_c;
    local_c &= ~0x400u;
    local_c = param_2->f20 | local_c;
    local_c &= ~0x6000000u;
    local_c = param_2->f24 | local_c;
    local_c &= ~0x8000000u;
    local_c = param_2->f28 | local_c;
    local_c &= ~0xc0000000u;
    local_c = (param_2->f2c << 2) | local_c;
    local_c &= ~0x20000000u;
    local_c = param_2->f34 | local_c;
    uVar1 &= ~0x10000u;
    uVar1 = param_2->f30 | uVar1;
    (*param_1)->f00 = local_c;
    (*param_1)->f3a0 = uVar1;
}
