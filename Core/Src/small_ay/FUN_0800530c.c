#include <stdint.h>

/* Device register window; status at +0xc4 (bit21 set => busy path,
   bits 17:16 => channel select), channel mask written at +0xcc. */
typedef struct {
    uint8_t          reserved0[0xc4]; /* 0x00 */
    volatile uint32_t status;         /* 0xc4 */
    uint8_t          reserved1[4];    /* 0xc8 */
    volatile uint32_t chan_mask;      /* 0xcc */
} Dev;

typedef struct {
    Dev              *dev;            /* 0x00 */
    uint8_t           reserved2[0x54]; /* 0x04 */
    uint32_t          chan_bits;      /* 0x58 */
    volatile uint8_t  state;          /* 0x5c */
    uint8_t           pad[3];         /* 0x5d */
    uint32_t          flags;          /* 0x60 */
} Ctx;

extern void FUN_08005ba4(Ctx *ctx, uint32_t mode, uint32_t value, uint32_t sel);

uint32_t FUN_0800530c(Ctx *ctx, uint32_t mode, uint32_t value)
{
    if (ctx->state == 2) {
        if ((ctx->dev->status & 0x200000u) != 0) {
            ctx->flags = ctx->flags | 0x200u;
            return 1;
        }
        uint32_t sel = (ctx->dev->status >> 16) & 3u;
        FUN_08005ba4(ctx, mode, value, sel);
        ctx->dev->chan_mask = 1u << sel;
        ctx->chan_bits = 1u << sel;
        return 0;
    }
    ctx->flags = ctx->flags | 8u;
    return 1;
}
