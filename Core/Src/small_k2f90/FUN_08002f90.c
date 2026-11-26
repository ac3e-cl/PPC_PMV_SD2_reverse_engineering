/* FUN_08002f90: request-block bring-up — idle checks, clock-derived delay
 * spin (clk/200000 ticks), peripheral-address probing, then composition of
 * the mapped peripheral regs 0xc / 0x10 / 0x30 / 0xc0. */
#include <stdint.h>
#include <stdbool.h>

typedef struct peri {
    volatile uint32_t pad00[3];   /* 0x00 */
    volatile uint32_t reg0c;      /* 0x0c */
    volatile uint32_t reg10;      /* 0x10 */
    volatile uint32_t pad14[7];   /* 0x14 */
    volatile uint32_t reg30;      /* 0x30 */
    volatile uint32_t pad34[35];  /* 0x34 */
    volatile uint32_t regc0;      /* 0xc0 */
} peri_t;

typedef struct {
    volatile peri_t *f00;
    volatile uint32_t f04;
    volatile uint32_t f08;
    volatile uint32_t f0c;
    volatile uint32_t f10;
    volatile uint32_t f14;
    volatile uint32_t f18;
    uint8_t  f1c;
    uint8_t  f1d;
    uint8_t           pad1e[2];
    volatile uint32_t f20;
    uint8_t  f24;
    uint8_t           pad25[3];
    volatile uint32_t f28;
    volatile uint32_t f2c;
    volatile uint32_t f30;
    volatile uint32_t f34;
    uint8_t  f38;
    uint8_t           pad39[3];
    volatile uint32_t f3c;
    uint8_t  f40;
    uint8_t           pad41[3];
    volatile uint32_t f44;
    volatile uint32_t f48;
    volatile uint32_t f4c;
    volatile uint32_t f50;
    uint8_t           pad54[4];
    uint8_t  f58;
    uint8_t           pad59[3];
    volatile uint32_t f5c;
    volatile uint32_t f60;
} cfg_t;

/* Pool-resident clock word via --defsym 0x20000000. */
extern volatile uint32_t CLK;

extern void     FUN_08002298(cfg_t *);
extern uint32_t FUN_08002db8(volatile peri_t *);
extern uint32_t FUN_08002d94(volatile peri_t *);
extern uint32_t FUN_08002e08(volatile peri_t *);
extern uint32_t FUN_08002de0(volatile peri_t *);
extern uint32_t FUN_08002f1c(volatile peri_t *);
extern uint32_t FUN_08002e80(volatile peri_t *);
extern uint32_t FUN_08002a74(volatile peri_t *, uint32_t);
extern uint32_t FUN_08002f6a(volatile peri_t *);

#define BASE0 ((volatile peri_t *)0x50000000u)
#define BASE1 ((volatile peri_t *)0x50000100u)

bool FUN_08002f90(cfg_t *p)
{
    bool flag = 0;     /* slot 0x1c, byte 0x1f */
    uint32_t local18;  /* slot 0x18 */
    uint32_t iVar;
    uint32_t ret6a;
    volatile uint32_t cnt = 0;

    if (p == 0) {
        return 1;
    }
    /* Original: empty then-branch, else jumps onto the f5c test (dead cmp). */
    if (p->f14 == 0) {
    } else {
        goto f5c_test;
    }
f5c_test:
    if (p->f5c == 0) {
        FUN_08002298(p);
        p->f60 = 0;
        p->f58 = 0;
    }
    if (FUN_08002db8(p->f00) != 0) {
        FUN_08002d94(p->f00);
    }
    if (FUN_08002e08(p->f00) == 0) {
        FUN_08002de0(p->f00);
        for (cnt = (CLK / 200000u + 1u) * 2u; cnt != 0; cnt--) {
        }
    }
    if (FUN_08002e08(p->f00) == 0) {
        p->f5c = p->f5c | 0x10u;
        p->f60 = p->f60 | 1u;
        flag = 1;
    }
    iVar = FUN_08002f1c(p->f00);
    if ((p->f5c & 0x10u) == 0 && iVar == 0) {
        p->f5c = (p->f5c & ~0x102u) | 2u;
        if (FUN_08002e80(p->f00) == 0) {
            if ((p->f00 == BASE0 || p->f00 == BASE1)
                    ? (bool)((FUN_08002e80(BASE0) | FUN_08002e80(BASE1)) == 0)
                    : (bool)((FUN_08002e80((volatile peri_t *)0x50000400u)
                              | FUN_08002e80((volatile peri_t *)0x50000500u)
                              | FUN_08002e80((volatile peri_t *)0x50000600u)) == 0)) {
                FUN_08002a74((p->f00 == BASE0 || p->f00 == BASE1)
                                 ? (volatile peri_t *)0x50000300u
                                 : (volatile peri_t *)0x50000700u,
                             p->f04);
            }
        }
        local18 = (uint32_t)p->f1d << 13 | p->f3c | p->f0c | p->f08
                  | (uint32_t)p->f24 << 16;
        if (p->f24 == 1) {
            local18 |= (p->f28 - 1u) << 17;
        }
        if (p->f2c != 0) {
            local18 |= (p->f2c & 0x3e0u) | p->f30;
        }
        p->f00->reg0c = (p->f00->reg0c & 0xfff04007u) | local18;
        p->f00->reg10 = (p->f00->reg10 & 0xf3ffffffu) | p->f34;
        ret6a = FUN_08002f6a(p->f00);
        if (iVar == 0 && ret6a == 0) {
            local18 = (uint32_t)p->f1c << 14 | (uint32_t)p->f38 << 1;
            p->f00->reg0c = (p->f00->reg0c & 0xffffbffd) | local18;
            if (p->f10 != 0) {
                p->f00->reg10 = p->f00->reg10 | 0x10000u;
                p->f00->regc0 = (p->f00->regc0 & 0xffffc000) | p->f10;
            } else {
                p->f00->reg10 = p->f00->reg10 & ~0x10000u;
                p->f00->regc0 = p->f00->regc0 & 0xffffc000u;
            }
            if (p->f40 == 1) {
                p->f00->reg10 = (p->f00->reg10 & 0xfffff803)
                                 | (p->f44 | p->f48 | p->f4c | p->f50) | 1u;
            } else {
                p->f00->reg10 = p->f00->reg10 & ~1u;
            }
        }
        if (p->f14 == 1) {
            p->f00->reg30 = (p->f00->reg30 & 0xfffffff0) | (p->f20 - 1u);
        } else {
            p->f00->reg30 = p->f00->reg30 & 0xfffffff0u;
        }
        p->f5c = (p->f5c & ~3u) | 1u;
    } else {
        p->f5c = p->f5c | 0x10u;
        flag = 1;
    }
    return flag;
}
