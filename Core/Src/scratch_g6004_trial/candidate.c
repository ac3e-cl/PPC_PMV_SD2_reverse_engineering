/* FUN_08006004: cfg reset + clock-source field merge + per-channel wave zeroing. */
#include <stdint.h>

typedef struct {
    volatile uint32_t *Instance;   /* 0x00 */
    uint32_t res0;                 /* 0x04 */
    uint32_t flags;                /* 0x08 */
    uint32_t f0c;                  /* 0x0c */
    uint32_t f10;                  /* 0x10 */
    uint32_t f14;                  /* 0x14 */
    struct { volatile uint32_t a,b,c,d,e,f,g; } buf[7];        /* 0x18..0xdb */
    uint8_t bdc;                   /* 0xdc */
    uint8_t bdd;                   /* 0xdd */
    uint8_t res2[2];
    uint32_t tail[7];              /* 0xe0..0xf8 */
} Cfg;

typedef struct { volatile uint32_t p0[24]; volatile uint32_t REG60; } RCC_TypeDef_;
#define RCC ((RCC_TypeDef_ *)0x40021000u)

extern void FUN_080024c8(Cfg *cfg);

uint32_t FUN_08006004(Cfg *cfg)
{
    volatile uint32_t v3;
    uint32_t u;
    uint8_t i;

    if (cfg == (Cfg *)0) {
        return 1u;
    }
    cfg->bdd = 2u;
    cfg->tail[0] = 0u;
    cfg->tail[1] = 0u;
    cfg->tail[2] = 0u;
    cfg->tail[3] = 0u;
    cfg->tail[4] = 0u;
    cfg->tail[5] = 0u;
    cfg->tail[6] = 0u;
    if ((cfg->flags & 1u) != 0u) {
        if (cfg->Instance == (volatile uint32_t *)0x40016800u) {
            RCC->REG60 |= 0x4000000u;
            v3 = RCC->REG60 & 0x4000000u;
            (void)v3; /* ST HAL dummy readback */
        }
        u = cfg->Instance[0];
        u &= ~0xc000u;
        u |= cfg->f10 & 0xc000u;
        u &= ~0x3000u;
        u |= cfg->f14 & 0x3000u;
        cfg->Instance[0] = u;
    }
    FUN_080024c8(cfg);
    if ((cfg->flags & 2u) != 0u) {
        u = cfg->Instance[0];
        u &= ~0x300u;
        u |= cfg->f0c & 0x300u;
        cfg->Instance[0] = u;
    }
    cfg->bdd = 1u;
    cfg->bdc = 0u;
    for (i = 0u; i < 7u; i = (uint8_t)(i + 1u)) {
        cfg->buf[i].a = 0u;
        cfg->buf[i].b = 0u;
        cfg->buf[i].c = 0u;
        cfg->buf[i].d = 0u;
        cfg->buf[i].e = 0u;
        cfg->buf[i].g = 0u;
    }
    return 0u;
}
