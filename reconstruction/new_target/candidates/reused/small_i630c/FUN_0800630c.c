#include <stdint.h>

typedef struct {
    volatile uint32_t reserved[0x3d0 / 4];
    volatile uint32_t reg0;  /* 0x3d0 */
    volatile uint32_t reg1;  /* 0x3d4 */
} Peripheral;

typedef struct {
    Peripheral *Instance;
    uint8_t reserved[0xd8];
    uint8_t busy;            /* 0xdc */
    volatile uint8_t state;  /* 0xdd */
} Handle;

/* struct members so -O0 folds ldr offsets (array subscript emits adds+ldr) */
typedef struct {
    uint32_t w0;
    uint32_t w1;
    uint32_t w2;
    uint32_t w3;
} Cfg;

uint32_t FUN_0800630c(Handle *handle, uint32_t sel, Cfg *p)
{
    if (handle->state == 2) return 2;
    if (handle->busy == 1) return 2;
    handle->busy = 1;
    handle->state = 2;

    uint32_t v0 = handle->Instance->reg0;
    uint32_t v1 = handle->Instance->reg1;
    uint32_t b0 = p->w0 & 1u;
    uint32_t b1 = (p->w0 >> 1) & 1u;

    switch (sel) {
    case 1:
        v0 = v0 & ~0xfeu;
        v0 = (p->w1 & 2u) | v0;
        v0 = (b0 << 2) | v0;
        v1 = v1 & ~0x10000u;
        v1 = (b1 << 0x10) | v1;
        v0 = (p->w2 & 0x78u) | v0;
        v0 = (p->w3 & 0x80u) | v0;
        break;
    case 2:
        v0 = v0 & ~0xfe00u;
        v0 = ((p->w1 << 8) & 0x200u) | v0;
        v0 = (b0 << 0xa) | v0;
        v1 = v1 & ~0x20000u;
        v1 = (b1 << 0x11) | v1;
        v0 = ((p->w2 << 8) & 0x7800u) | v0;
        v0 = ((p->w3 << 8) & 0x8000u) | v0;
        break;
    case 4:
        v0 = v0 & ~0xfe0000u;
        v0 = ((p->w1 << 16) & 0x20000u) | v0;
        v0 = (b0 << 0x12) | v0;
        v1 = v1 & ~0x40000u;
        v1 = (b1 << 0x12) | v1;
        v0 = ((p->w2 << 16) & 0x780000u) | v0;
        v0 = ((p->w3 << 16) & 0x800000u) | v0;
        break;
    case 8:
        v0 = v0 & ~0xfe000000u;
        v0 = ((p->w1 << 24) & 0x2000000u) | v0;
        v0 = (b0 << 0x1a) | v0;
        v1 = v1 & ~0x80000u;
        v1 = (b1 << 0x13) | v1;
        v0 = ((p->w2 << 24) & 0x78000000u) | v0;
        v0 = ((p->w3 << 24) & 0x80000000u) | v0;
        break;
    case 16:
        v1 = v1 & ~0xfeu;
        v1 = (p->w1 & 2u) | v1;
        v1 = (b0 << 2) | v1;
        v1 = v1 & ~0x100000u;
        v1 = (b1 << 0x14) | v1;
        v1 = (p->w2 & 0x78u) | v1;
        v1 = (p->w3 & 0x80u) | v1;
        break;
    case 32:
        v1 = v1 & ~0xfe00u;
        v1 = ((p->w1 << 8) & 0x200u) | v1;
        v1 = (b0 << 0xa) | v1;
        v1 = v1 & ~0x200000u;
        v1 = (b1 << 0x15) | v1;
        v1 = ((p->w2 << 8) & 0x7800u) | v1;
        v1 = ((p->w3 << 8) & 0x8000u) | v1;
        break;
    default:
        handle->state = 7;
        handle->busy = 0;
        break;
    }

    if (handle->state == 7) return 1;
    handle->Instance->reg0 = v0 & 0x7f7f7f7fu;
    handle->Instance->reg1 = v1 & 0xffff7f7fu;
    handle->Instance->reg0 = handle->Instance->reg0 | (v0 & 0x80808080u);
    handle->Instance->reg1 = handle->Instance->reg1 | (v1 & 0x8080u);
    handle->state = 1;
    handle->busy = 0;
    return 0;
}
