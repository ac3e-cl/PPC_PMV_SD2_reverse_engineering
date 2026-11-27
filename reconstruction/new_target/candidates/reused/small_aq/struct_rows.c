#include <stdint.h>

typedef struct { volatile uint32_t a, b; uint8_t pad[120]; } Row;
typedef struct { uint8_t pad[0x94]; Row row[]; } RegBlock;
typedef struct { volatile uint32_t f0, f1, f2, f3; } Src;

void FUN_080079b6(uint8_t *volatile *param_1, uint32_t param_2, volatile Src *param_3)
{
    uint32_t cfg = *(volatile uint32_t *)(*param_1 + (param_2 + 1) * 0x80);
    cfg &= ~7u;
    cfg |= param_3->f2;
    cfg &= ~0x18u;
    cfg |= param_3->f3;
    *(volatile uint32_t *)(*param_1 + (param_2 + 1) * 0x80) = cfg;
    ((RegBlock *)*param_1)->row[param_2].a = param_3->f0;
    ((RegBlock *)*param_1)->row[param_2].b = param_3->f1;
}
