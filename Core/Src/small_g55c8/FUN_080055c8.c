#include <stdint.h>

typedef struct {
    uint8_t pad50[0x54];
    volatile uint32_t r54, r58, r5c;
    uint8_t pad60[0x7c];
    volatile uint32_t rdc, re0;
} Periph;

typedef struct {
    Periph *h;
    uint8_t pad4[0x58];
    volatile uint8_t state;
    uint8_t pad5d[3];
    volatile uint32_t flags;
} Ctrl;

uint32_t FUN_080055c8(Ctrl *param_1, uint32_t param_2, uint32_t param_3)
{
    uint8_t b = param_1->state;
    if (b == 1 || b == 2) {
        uint32_t uVar1 = param_1->h->r58;
        if ((param_2 & 7) != 0 && (uVar1 & 1) == 0 ||
            (param_2 & 0x38) != 0 && (uVar1 & 2) == 0 ||
            (param_2 & 0x1c0) != 0 && (uVar1 & 4) == 0 ||
            (param_2 & 0x1e00) != 0 && (uVar1 & 8) == 0 ||
            (param_2 & 0xe000) != 0 && (uVar1 & 0x10) == 0 ||
            (param_2 & 0x30000) != 0 && (uVar1 & 0x20) == 0 ||
            (param_2 & 0xfc0000) != 0 && (uVar1 & 0x40) == 0) {
            param_1->h->r5c = param_1->h->r5c | 1;
        }
        if ((param_2 & 7) != 0 && (uVar1 & 1) != 0 ||
            (param_2 & 0x38) != 0 && (uVar1 & 2) != 0 ||
            (param_2 & 0x1c0) != 0 && (uVar1 & 4) != 0 ||
            (param_2 & 0x1e00) != 0 && (uVar1 & 8) != 0 ||
            (param_2 & 0xe000) != 0 && (uVar1 & 0x10) != 0 ||
            (param_2 & 0x30000) != 0 && (uVar1 & 0x20) != 0 ||
            (param_2 & 0xfc0000) != 0 && (uVar1 & 0x40) != 0) {
            param_1->h->r5c = param_1->h->r5c | 2;
        }
        if ((param_2 & 0x80) != 0) {
            param_1->h->rdc = param_3 | param_1->h->rdc;
        }
        if ((param_2 & 0x100) != 0) {
            param_1->h->re0 = param_3 | param_1->h->re0;
        }
        param_1->h->r54 = param_2 | param_1->h->r54;
        return 0;
    }
    param_1->flags = param_1->flags | 2;
    return 1;
}
