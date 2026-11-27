#include <stdint.h>

/* Peripheral window reached through ctx->peri; two CCMR-like control
   words at +0x408/+0x40c carry 2-bit mode fields at bit pairs
   (1:0),(9:8),(17:16),(25:24) fed by arg->value. */
typedef struct {
    uint8_t             reserved0[0x408]; /* 0x00 */
    volatile uint32_t   cr408;            /* 0x408 */
    volatile uint32_t   cr40c;            /* 0x40c */
} Peri;

typedef struct {
    uint8_t             reserved1[8];     /* 0x00 */
    uint32_t            value;            /* 0x08 */
} Arg;

typedef struct {
    Peri               *peri;             /* 0x00 */
    uint8_t             reserved2[0xd8];  /* 0x04 */
    uint8_t             dc;               /* 0xdc */
    volatile uint8_t    dd;               /* 0xdd */
} Ctx;

uint32_t FUN_08006700(Ctx *ctx, uint32_t mode, Arg *arg)
{
    if ((unsigned int)ctx->dd == 2u) {
        return 2u;
    }
    if (ctx->dc == 1u) {
        return 2u;
    }
    ctx->dc = 1u;
    ctx->dd = 2u;
    switch (mode) {
    case 1u:
        ctx->peri->cr408 = (ctx->peri->cr408 & ~0x3u) | (arg->value << 0x1) | 0x1u;
        break;
    case 2u:
        ctx->peri->cr408 = (ctx->peri->cr408 & ~0x300u) | (arg->value << 0x9) | 0x100u;
        break;
    case 4u:
        ctx->peri->cr408 = (ctx->peri->cr408 & ~0x30000u) | (arg->value << 0x11) | 0x10000u;
        break;
    case 8u:
        ctx->peri->cr408 = (ctx->peri->cr408 & ~0x3000000u) | (arg->value << 0x19) | 0x1000000u;
        break;
    case 16u:
        ctx->peri->cr40c = (ctx->peri->cr40c & ~0x3u) | (arg->value << 0x1) | 0x1u;
        break;
    case 32u:
        ctx->peri->cr40c = (ctx->peri->cr40c & ~0x300u) | (arg->value << 0x9) | 0x100u;
        break;
    default:
        ctx->dd = 7u;
        ctx->dc = 0u;
        break;
    }
    if ((unsigned int)ctx->dd == 7u) {
        return 1u;
    }
    ctx->dd = 1u;
    ctx->dc = 0u;
    return 0u;
}
