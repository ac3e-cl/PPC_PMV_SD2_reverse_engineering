#include <stdint.h>

/* 5-bit field windows at +0x400/+0x404, fed by the raw third parameter. */
typedef struct {
    uint8_t           reserved0[0x400];
    volatile uint32_t cr400;   /* 0x400 */
    volatile uint32_t cr404;   /* 0x404 */
} Peri;

typedef struct {
    Peri             *peri;    /* 0x00 */
    uint8_t           reserved1[0xd8];
    uint8_t           dc;      /* 0xdc: non-volatile (ldrb, no uxtb) */
    volatile uint8_t  dd;      /* 0xdd: volatile (ldrb + uxtb) */
} Ctx;

uint32_t FUN_08006fa4(Ctx *ctx, uint32_t mode, uint32_t value)
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
        ctx->peri->cr400 = (ctx->peri->cr400 & ~0x1fu) | (value & 0x1fu);
        break;
    case 2u:
        ctx->peri->cr400 = (ctx->peri->cr400 & ~0x7c0u) | ((value << 0x6) & 0x7c0u);
        break;
    case 4u:
        ctx->peri->cr400 = (ctx->peri->cr400 & ~0x1f000u) | ((value << 0xc) & 0x1f000u);
        break;
    case 8u:
        ctx->peri->cr400 = (ctx->peri->cr400 & ~0x7c0000u) | ((value << 0x12) & 0x7c0000u);
        break;
    case 16u:
        ctx->peri->cr400 = (ctx->peri->cr400 & ~0x1f000000u) | ((value << 0x18) & 0x1f000000u);
        break;
    case 32u:
        ctx->peri->cr404 = (ctx->peri->cr404 & ~0x1fu) | (value & 0x1fu);
        break;
    case 64u:
        ctx->peri->cr404 = (ctx->peri->cr404 & ~0x7c0u) | ((value << 0x6) & 0x7c0u);
        break;
    case 128u:
        ctx->peri->cr404 = (ctx->peri->cr404 & ~0x1f000u) | ((value << 0xc) & 0x1f000u);
        break;
    case 256u:
        ctx->peri->cr404 = (ctx->peri->cr404 & ~0x7c0000u) | ((value << 0x12) & 0x7c0000u);
        break;
    case 512u:
        ctx->peri->cr404 = (ctx->peri->cr404 & ~0x1f000000u) | ((value << 0x18) & 0x1f000000u);
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
