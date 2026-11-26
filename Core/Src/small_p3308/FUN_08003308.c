/* FUN_08003308: HRTIM enable sequence. Reconstructed from disassembly at
 * 0x08003308 (456-byte section: 434-byte body, 2-byte align, 20-byte pool). */
#include <stdint.h>

typedef struct hrt_regs {
    volatile uint32_t cr;    /* 0x00 control */
    volatile uint32_t sr;    /* 0x04 status  */
    volatile uint32_t rsv8;  /* 0x08          */
    volatile uint32_t conf;  /* 0x0c config   */
} hrt_regs;

typedef struct hrt_ctx {
    volatile hrt_regs *h;           /* 0x00 */
    volatile uint32_t reserved[21]; /* 0x04-0x57 */
    uint8_t busy;                   /* 0x58, non-volatile to match uxtb-free loads */
    uint8_t pad[3];                 /* 0x59-0x5b */
    volatile uint32_t flags;        /* 0x5c */
    volatile uint32_t flags2;       /* 0x60 */
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
extern uint32_t FUN_08002f1c(uint32_t h);
extern char FUN_0800476c(hrt_ctx *p);
extern void FUN_08002ecc(uint32_t h);

char FUN_08003308(hrt_ctx *p)
{
    uint32_t m, y;
    char res;

    m = FUN_08002d5c((uint32_t)p->h == H0 || (uint32_t)p->h == H100 ? H300 : H700);
    if (FUN_08002f1c((uint32_t)p->h) == 0) {
        if (p->busy == 1) return 2;
        p->busy = 1;
        res = FUN_0800476c(p);
        if (res == 0) {
            p->flags = (p->flags & ~0xF00u & ~0x1u) | 0x100u;
            if (REMAP((uint32_t)p->h) == (uint32_t)p->h || m == 0) {
                p->flags &= ~0x100000u;
            }
            if ((p->flags & 0x1000u) == 0x1000u) {
                p->flags2 &= ~6u;
            } else {
                p->flags2 = 0;
            }
            p->h->cr = 0x1c;
            p->busy = 0;
            if (REMAP((uint32_t)p->h) == (uint32_t)p->h || m == 0 || m == 5 || m == 9) {
                if ((p->h->conf & 0x2000000u) != 0) {
                    p->flags = (p->flags & ~0x3000u) | 0x1000u;
                }
                FUN_08002ecc((uint32_t)p->h);
            } else {
                p->flags |= 0x100000u;
                y = REMAP((uint32_t)p->h);
                if ((uint32_t)((volatile hrt_regs *)y)->conf & 0x2000000u) {
                    p->flags = (p->flags & ~0x3000u) | 0x1000u;
                }
            }
        } else {
            p->busy = 0;
        }
    } else {
        res = 2;
    }
    return res;
}
