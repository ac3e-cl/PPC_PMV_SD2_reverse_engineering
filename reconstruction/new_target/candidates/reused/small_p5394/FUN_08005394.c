#include <stdint.h>

extern const uint8_t DAT_08009a64[];

typedef struct {
    uint32_t _r00[0x20];   /* 0x00 */
    volatile uint32_t r80; /* 0x80 */
    uint32_t _r84[3];
    volatile uint32_t r90; /* 0x90 */
    volatile uint32_t r94; /* 0x94 */
    volatile uint32_t r98; /* 0x98 */
    volatile uint32_t r9c; /* 0x9c */
} Blk;

typedef struct {
    Blk *b;                /* 0x00 */
    uint32_t _r04[17];
    uint32_t base40;       /* 0x48 */
    uint32_t base41;       /* 0x4c */
    uint32_t _r50[3];
    uint8_t mode;          /* 0x5c */
    uint8_t _r5d[3];
    uint32_t flags;        /* 0x60 */
} Handle;

typedef struct {
    uint32_t f0, f1, f2, f3, f4, f5, f6, f7, f8, f9;
} Out;

uint32_t FUN_08005394(Handle *p1, uint32_t p2, Out *p3, uint8_t *p4)
{
    uint32_t *sel;
    uint32_t i;
    uint32_t acc;
    uint8_t mode;
    uint8_t *src;
    acc = 0;
    mode = p1->mode;
    if (mode == 2) {
        if (p2 == 0x40) {
            if ((p1->b->r90 & 0xfu) == 0) {
                p1->flags = p1->flags | 0x100u;
                return 1;
            }
            if (((p1->b->r90 & 0x1000000u) == 0x1000000u) &&
                ((p1->b->r80 & 0x200u) == 0x200u)) {
                acc = 1;
            }
            acc = ((p1->b->r90 >> 8) & 3u) + acc;
            sel = (uint32_t *)(p1->base40 + acc * 0x48u);
        } else {
            if ((p1->b->r98 & 0xfu) == 0) {
                p1->flags = p1->flags | 0x100u;
                return 1;
            }
            if (((p1->b->r98 & 0x1000000u) == 0x1000000u) &&
                ((p1->b->r80 & 0x100u) == 0x100u)) {
                acc = 1;
            }
            acc = ((p1->b->r98 >> 8) & 3u) + acc;
            sel = (uint32_t *)(p1->base41 + acc * 0x48u);
        }
        p3->f1 = *sel & 0x40000000u;
        if (p3->f1 == 0) {
            p3->f0 = (*sel >> 0x12) & 0x7ffu;
        } else {
            p3->f0 = *sel & 0x1fffffffu;
        }
        p3->f2 = *sel & 0x20000000u;
        p3->f4 = *sel & 0x80000000u;
        sel++;
        p3->f7 = *sel & 0xffffu;
        p3->f3 = (*sel >> 0x10) & 0xfu;
        p3->f5 = *sel & 0x100000u;
        p3->f6 = *sel & 0x200000u;
        p3->f8 = (*sel >> 0x18) & 0x7fu;
        p3->f9 = *sel >> 0x1f;
        sel++;
        src = (uint8_t *)sel;
        for (i = 0; i < DAT_08009a64[p3->f3]; i++) {
            p4[i] = src[i];
        }
        if (p2 == 0x40) {
            p1->b->r94 = acc;
        } else {
            p1->b->r9c = acc;
        }
        return 0;
    }
    p1->flags = p1->flags | 8u;
    return 1;
}
