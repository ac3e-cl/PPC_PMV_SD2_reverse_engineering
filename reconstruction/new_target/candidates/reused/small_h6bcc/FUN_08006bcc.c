#include <stdint.h>

typedef struct {
    volatile uint32_t reserved0[0xe0];
    volatile uint32_t reg380;
    volatile uint32_t reserved1[0xe];
    volatile uint32_t reg3bc;
    volatile uint32_t reg3c0;
    volatile uint32_t reg3c4;
    volatile uint32_t reg3c8;
    volatile uint32_t reserved2[0xb];
    volatile uint32_t reg3f8;
    volatile uint32_t reg3fc;
} Peripheral;

typedef struct { Peripheral *Instance; uint8_t reserved[0xd8]; uint8_t busy; volatile uint8_t state; } Handle;

typedef struct { uint32_t lo; uint32_t hi; } Value;

uint32_t FUN_08006bcc(Handle *h, uint32_t channel, Value *v)
{
    uint32_t lo, hi;

    if (h->state == 2) return 2;
    if (h->busy == 1) return 2;
    h->busy = 1;
    h->state = 2;
    lo = h->Instance->reg380;
    hi = h->Instance->reg3fc;
    switch (channel) {
    case 1:
        lo &= ~0x70000u;
        lo = (v->lo & 0x70000u) | lo;
        h->Instance->reg3bc = v->hi;
        break;
    case 2:
        lo &= ~0x380000u;
        lo = ((v->lo << 3) & 0x380000u) | lo;
        h->Instance->reg3c0 = v->hi;
        break;
    case 4:
        lo &= ~0x1c00000u;
        lo = ((v->lo << 6) & 0x1c00000u) | lo;
        h->Instance->reg3c4 = v->hi;
        break;
    case 8:
        lo &= ~0xe000000u;
        lo = ((v->lo << 9) & 0xe000000u) | lo;
        h->Instance->reg3c8 = v->hi;
        break;
    case 16:
        hi &= ~7u;
        hi = ((v->lo >> 16) & 7u) | hi;
        h->Instance->reg3f8 &= ~0x1fu;
        h->Instance->reg3f8 |= v->hi & 0x1fu;
        break;
    case 32:
        hi &= ~0x70u;
        hi = ((v->lo >> 12) & 0x70u) | hi;
        h->Instance->reg3f8 &= ~0x3e0u;
        h->Instance->reg3f8 |= (v->hi << 5) & 0x3e0u;
        break;
    case 64:
        hi &= ~0x700u;
        hi = ((v->lo >> 8) & 0x700u) | hi;
        h->Instance->reg3f8 &= ~0x7c00u;
        h->Instance->reg3f8 |= (v->hi << 10) & 0x7c00u;
        break;
    case 128:
        hi &= ~0x7000u;
        hi = ((v->lo >> 4) & 0x7000u) | hi;
        h->Instance->reg3f8 &= ~0x1f0000u;
        h->Instance->reg3f8 |= (v->hi << 16) & 0x1f0000u;
        break;
    case 256:
        hi &= ~0x70000u;
        hi = (v->lo & 0x70000u) | hi;
        h->Instance->reg3f8 &= ~0x3e00000u;
        h->Instance->reg3f8 |= (v->hi << 21) & 0x3e00000u;
        break;
    case 512:
        hi &= ~0x700000u;
        hi = ((v->lo << 4) & 0x700000u) | hi;
        h->Instance->reg3f8 &= ~0x7c000000u;
        h->Instance->reg3f8 |= (v->hi << 26) & 0x7c000000u;
        break;
    default:
        h->state = 7;
        h->busy = 0;
        break;
    }
    if (h->state == 7) return 1;
    if (channel <= 0xf)
        h->Instance->reg380 = lo;
    else
        h->Instance->reg3fc = hi;
    h->state = 1;
    h->busy = 0;
    return 0;
}
