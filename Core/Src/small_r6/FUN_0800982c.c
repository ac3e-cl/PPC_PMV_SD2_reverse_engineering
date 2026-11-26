#include <stdint.h>

#define K3c 0x40012c00u
#define K40 0x40013400u
#define K44 0x40015000u
#define K48 0x40000400u
#define K4c 0x40000800u
#define K50 0x40000c00u
#define K54 0x40014000u

typedef struct { volatile uint32_t r0, r4, r8; } Peri;

typedef struct { uint32_t w0, w1, w2; } Args;

typedef struct {
    Peri *base;
    uint8_t pad0[0x38];
    uint8_t busy;
    uint8_t state;
} Handle;

uint32_t FUN_0800982c(Handle *param_1, const Args *param_2)
{
    uint32_t flags;
    uint32_t ctl;

    if (param_1->busy == 1u) return 2u;
    param_1->busy = 1;
    param_1->state = 2;
    flags = param_1->base->r4;
    ctl = param_1->base->r8;
    if (param_1->base == (Peri *)K3c || param_1->base == (Peri *)K40 || param_1->base == (Peri *)K44) {
        flags &= ~0xf00000u;
        flags |= param_2->w1;
    }
    flags &= 0xfdffffffu & ~0x70u;
    flags |= param_2->w0;
    param_1->base->r4 = flags;
    if (param_1->base == (Peri *)K3c || param_1->base == (Peri *)0x40000000u || param_1->base == (Peri *)K48
        || param_1->base == (Peri *)K4c || param_1->base == (Peri *)K50 || param_1->base == (Peri *)K40
        || param_1->base == (Peri *)K54 || param_1->base == (Peri *)K44) {
        ctl &= ~0x80u;
        ctl |= param_2->w2;
        param_1->base->r8 = ctl;
    }
    param_1->state = 1;
    param_1->busy = 0;
    return 0;
}
