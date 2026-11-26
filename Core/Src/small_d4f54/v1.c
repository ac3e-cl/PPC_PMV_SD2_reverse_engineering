/* FUN_08004f54: HRT-style init sequence; polls CR bits 3/0 with 10-tick timeouts. */
#include <stdint.h>

typedef struct {
    volatile uint32_t _r00[3];    /* 0x00 */
    volatile uint32_t R0C;        /* 0x0c */
    volatile uint32_t R10;        /* 0x10 */
    volatile uint32_t _r14;       /* 0x14 */
    volatile uint32_t CR;         /* 0x18 */
    volatile uint32_t R1C;        /* 0x1c */
    volatile uint32_t _r20[40];   /* 0x20 */
    volatile uint32_t R0C0;       /* 0xc0 */
} Periph;

typedef struct {
    Periph *Instance;             /* 0x00 */
    uint32_t p1;                  /* 0x04 */
    uint32_t p2;                  /* 0x08 */
    uint32_t p3;                  /* 0x0c */
    uint8_t b10;                  /* 0x10 */
    uint8_t b11;                  /* 0x11 */
    uint8_t b12;                  /* 0x12 */
    uint8_t _pad13;               /* 0x13 */
    uint32_t p5;                  /* 0x14 */
    uint32_t p6;                  /* 0x18 */
    uint32_t p7;                  /* 0x1c */
    uint32_t p8;                  /* 0x20 */
    uint32_t p9;                  /* 0x24 */
    uint32_t p10;                 /* 0x28 */
    uint32_t p11;                 /* 0x2c */
    uint32_t p12;                 /* 0x30 */
    uint32_t _pad34[2];           /* 0x34 */
    uint32_t p15;                 /* 0x3c */
    uint32_t _pad40[6];           /* 0x40 */
    uint32_t w58;                 /* 0x58 */
    volatile uint8_t state;       /* 0x5c */
    uint8_t flag;                 /* 0x5d */
    uint8_t _pad5e[2];            /* 0x5e */
    uint32_t err;                 /* 0x60 */
} Handle;

extern void FUN_08002404(Handle *param_1);
extern uint32_t FUN_08002a18(void);
extern void FUN_08005acc(Handle *param_1);

uint32_t FUN_08004f54(Handle *param_1)
{
    uint32_t t0;

    if (param_1 == 0) {
        return 1u;
    }
    if (param_1->state == 0u) {
        param_1->flag = 0u;
        FUN_08002404(param_1);
    }
    param_1->Instance->CR &= ~0x10u;
    t0 = FUN_08002a18();
    while ((param_1->Instance->CR & 8u) == 8u) {
        if ((uint32_t)(FUN_08002a18() - t0) > 10u) {
            param_1->err |= 1u;
            param_1->state = 3u;
            return 1u;
        }
    }
    param_1->Instance->CR |= 1u;
    t0 = FUN_08002a18();
    while ((param_1->Instance->CR & 1u) == 0u) {
        if ((uint32_t)(FUN_08002a18() - t0) > 10u) {
            param_1->err |= 1u;
            param_1->state = 3u;
            return 1u;
        }
    }
    param_1->Instance->CR |= 2u;
    if (param_1->Instance == (const Periph *)0x40006400u) {
        *(volatile uint32_t *)0x40006500u = param_1->p1;
    }
    if (param_1->b10 == 1u) {
        param_1->Instance->CR &= ~0x40u;
    } else {
        param_1->Instance->CR |= 0x40u;
    }
    if (param_1->b11 == 1u) {
        param_1->Instance->CR |= 0x4000u;
    } else {
        param_1->Instance->CR &= ~0x4000u;
    }
    if (param_1->b12 == 1u) {
        param_1->Instance->CR &= ~0x1000u;
    } else {
        param_1->Instance->CR |= 0x1000u;
    }
    param_1->Instance->CR = (param_1->Instance->CR & 0xfffffcffu) | param_1->p2;
    param_1->Instance->CR &= ~0xa4u;
    param_1->Instance->R10 &= ~0x10u;
    if (param_1->p3 == 1u) {
        param_1->Instance->CR |= 4u;
    } else if (param_1->p3 != 0u) {
        if (param_1->p3 != 2u) {
            param_1->Instance->CR |= 0x80u;
            param_1->Instance->R10 |= 0x10u;
            if (param_1->p3 == 3u) {
                param_1->Instance->CR |= 0x20u;
            }
        } else {
            param_1->Instance->CR |= 0x20u;
        }
    }
    param_1->Instance->R1C = (param_1->p6 - 1u) << 25 | (param_1->p7 - 1u) << 8 |
                             (param_1->p8 - 1u) | (param_1->p5 - 1u) << 16;
    if (param_1->p2 == 0x300u) {
        param_1->Instance->R0C = (param_1->p10 - 1u) | (param_1->p11 - 1u) << 8 |
                                 (param_1->p12 - 1u) << 4 | (param_1->p9 - 1u) << 16;
    }
    param_1->Instance->R0C0 = param_1->Instance->R0C0 | param_1->p15;
    FUN_08005acc(param_1);
    param_1->w58 = 0u;
    param_1->err = 0u;
    param_1->state = 1u;
    return 0u;
}
