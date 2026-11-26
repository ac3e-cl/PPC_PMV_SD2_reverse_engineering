#include <stdint.h>

typedef struct { volatile uint32_t value; uint8_t pad[124]; } Row;
typedef struct { uint8_t pad[0xec]; Row row[]; } RegBlock;
typedef struct { volatile uint32_t f[8]; } Cfg;

void FUN_08007e7c(RegBlock **param_1, uint32_t channel, const Cfg *config)
{
    uint32_t v = (*param_1)->row[channel].value;
    v &= ~0x10u;
    v |= config->f[0] << 4;
    v &= ~0x100000u;
    v |= config->f[1];
    v &= ~0x10000u;
    v |= config->f[3];
    v &= ~0x20000u;
    v |= config->f[2];
    if (config->f[6] == 1u) {
        v &= ~0x4u;
        v |= config->f[4];
        v &= ~0x2u;
        v |= config->f[5];
        v &= ~0x1u;
        v |= config->f[6];
    }
    (*param_1)->row[channel].value = v;
}
