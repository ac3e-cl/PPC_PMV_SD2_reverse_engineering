#include <stdint.h>

extern const uint8_t TBL_08009a64[];

typedef struct { uint8_t r[0x54]; volatile uint32_t dma; } P1;
typedef struct { volatile uint32_t f[9]; } P2;

void FUN_08005ba4(const P1 *param_1, const P2 *param_2,
                  const uint8_t *param_3, uint32_t param_4)
{
    uint32_t flags;
    uint32_t *p;
    uint32_t i;
    uint32_t word;

    if (param_2->f[1] == 0u) {
        flags = param_2->f[4] | param_2->f[2] | (param_2->f[0] << 0x12);
    } else {
        flags = param_2->f[4] | param_2->f[2] | param_2->f[0] | 0x40000000u;
    }
    word = (param_2->f[8] << 0x18) | param_2->f[7] | param_2->f[6] | param_2->f[5]
         | (param_2->f[3] << 0x10);
    p = (uint32_t *)(uintptr_t)(param_1->dma + param_4 * 72u);
    *p = flags;
    p += 1;
    *p = word;
    p += 1;
    for (i = 0u; i < TBL_08009a64[param_2->f[3]]; i += 4u) {
        *p = ((uint32_t)param_3[i + 3u] << 24) | ((uint32_t)param_3[i + 2u] << 16)
           | ((uint32_t)param_3[i + 1u] << 8) | (uint32_t)param_3[i];
        p += 1;
    }
}
