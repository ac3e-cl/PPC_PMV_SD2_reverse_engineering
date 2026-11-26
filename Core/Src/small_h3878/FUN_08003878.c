/* FUN_08003878: HRTIM timer-output event dispatch. Reconstructed from
 * disassembly at 0x08003878 (1216-byte section incl. split literal pools). */
#include <stdint.h>

typedef struct hrt_regs {
    volatile uint32_t cr;    /* 0x00 control */
    volatile uint32_t sr;    /* 0x04 status  */
    volatile uint32_t rsv8;  /* 0x08          */
    volatile uint32_t conf;  /* 0x0c config   */
} hrt_regs;

typedef struct hrt_ctx {
    volatile hrt_regs *h;         /* 0x00 */
    volatile uint32_t pad0[14];   /* 0x04-0x38 */
    volatile uint32_t enabled;    /* 0x3c */
    volatile uint32_t pad1[7];    /* 0x40-0x58 */
    volatile uint32_t flags;      /* 0x5c */
    volatile uint32_t flags2;     /* 0x60 */
} hrt_ctx;

#define H0   0x50000000u
#define H100 0x50000100u
#define H300 0x50000300u
#define H400 0x50000400u
#define H500 0x50000500u
#define H700 0x50000700u

/* handle -> "master-or-flt" remap used by the set/reset dispatch */
#define REMAP(h) ((h) == H100 ? H0 : ((h) == H500 ? H400 : (h)))

extern uint32_t FUN_08002d5c(uint32_t base);
extern uint32_t FUN_08002d78(uint32_t base);
extern uint32_t FUN_08002c18(uint32_t h);
extern uint32_t FUN_08002c96(uint32_t h);
extern uint32_t FUN_08002f1c(uint32_t h);
extern uint32_t FUN_08002f6a(uint32_t h);
extern void FUN_08004b10(hrt_ctx *p);
extern void FUN_08003d38(hrt_ctx *p);
extern void FUN_08004ac0(hrt_ctx *p);
extern void FUN_08003d4c(hrt_ctx *p);
extern void FUN_08004ae8(hrt_ctx *p);
extern void FUN_08004afc(hrt_ctx *p);
extern void FUN_08003d60(hrt_ctx *p);
extern void FUN_08004ad4(hrt_ctx *p);

void FUN_08003878(hrt_ctx *p)
{
    uint32_t b = 0;                                    /* 0x24 */
    uint32_t cr = (uint32_t)p->h->cr;                  /* 0x1c */
    uint32_t sr = (uint32_t)p->h->sr;                  /* 0x18 */
    uint32_t mode = FUN_08002d5c((uint32_t)p->h == H0 ||
                                 (uint32_t)p->h == H100 ? H300 : H700); /* 0x14 */
    uint32_t conf;                                     /* 0x20 */
    uint32_t y;                                        /* 0x10 */
    uint32_t v96;                                      /* 0x0c */
    uint32_t v18;                                      /* 0x08 */

    if ((cr & 2) && (sr & 2)) {
        if ((p->flags & 0x10) == 0) {
            p->flags |= 0x800;
        }
        FUN_08004b10(p);
        p->h->cr = 2;
    }
    if ((cr & 4) && (sr & 4) || (cr & 8) && (sr & 8)) {
        if ((p->flags & 0x10) == 0) {
            p->flags |= 0x200;
        }
        if (FUN_08002c18((uint32_t)p->h) != 0) {
            if (REMAP((uint32_t)p->h) == (uint32_t)p->h || mode == 0 ||
                mode == 5 || mode == 9) {
                conf = (uint32_t)p->h->conf;
            } else {
                y = REMAP((uint32_t)p->h);
                conf = (uint32_t)((volatile hrt_regs *)y)->conf;
            }
            if ((conf & 0x2000) == 0 && (p->h->cr & 8) == 8) {
                if (FUN_08002f1c((uint32_t)p->h) == 0) {
                    p->h->sr &= ~0xcu;
                    p->flags &= ~0x100u;
                    if ((p->flags & 0x1000) == 0) {
                        p->flags |= 1;
                    }
                } else {
                    p->flags |= 0x10;
                    p->flags2 |= 1;
                }
            }
        }
        FUN_08003d38(p);
        p->h->cr = 0xc;
    }
    if ((cr & 0x20) && (sr & 0x20) || (cr & 0x40) && (sr & 0x40)) {
        if ((p->flags & 0x10) == 0) {
            p->flags |= 0x2000;
        }
        v96 = FUN_08002c96((uint32_t)p->h);
        v18 = FUN_08002c18((uint32_t)p->h);
        if (REMAP((uint32_t)p->h) == (uint32_t)p->h || mode == 0 ||
            mode == 6 || mode == 7) {
            conf = (uint32_t)p->h->conf;
        } else {
            y = REMAP((uint32_t)p->h);
            conf = (uint32_t)((volatile hrt_regs *)y)->conf;
        }
        if (v96 != 0 &&
            ((conf & 0x2000000) == 0 || (v18 != 0 && (conf & 0x2000) == 0)) &&
            (p->h->cr & 0x40) == 0x40 && (conf & 0x200000) == 0) {
            if (FUN_08002f6a((uint32_t)p->h) == 0) {
                p->h->sr &= ~0x60u;
                p->flags &= ~0x1000u;
                if ((p->flags & 0x100) == 0) {
                    p->flags |= 1;
                }
            } else {
                p->flags |= 0x10;
                p->flags2 |= 1;
            }
        }
        FUN_08004ac0(p);
        p->h->cr = 0x60;
    }
    if ((cr & 0x80) && (sr & 0x80)) {
        p->flags |= 0x10000;
        FUN_08003d4c(p);
        p->h->cr = 0x80;
    }
    if ((cr & 0x100) && (sr & 0x100)) {
        p->flags |= 0x20000;
        FUN_08004ae8(p);
        p->h->cr = 0x100;
    }
    if ((cr & 0x200) && (sr & 0x200)) {
        p->flags |= 0x40000;
        FUN_08004afc(p);
        p->h->cr = 0x200;
    }
    if ((cr & 0x10) && (sr & 0x10)) {
        if (p->enabled == 0) {
            b = 1;
        } else if (mode != 0) {
            if (FUN_08002d78((uint32_t)p->h == H0 ||
                              (uint32_t)p->h == H100 ? H300 : H700) != 0) {
                b = 1;
            }
        } else {
            if (((uint32_t)p->h->conf & 1) != 0) {
                b = 1;
            }
        }
        if (b == 1) {
            p->flags |= 0x400;
            p->flags2 |= 2;
            FUN_08003d60(p);
        }
        p->h->cr = 0x10;
    }
    if ((cr & 0x400) && (sr & 0x400)) {
        p->flags |= 0x4000;
        p->flags2 |= 8;
        p->h->cr = 0x400;
        FUN_08004ad4(p);
    }
}
