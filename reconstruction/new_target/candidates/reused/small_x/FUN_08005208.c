#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t pad0[0x40];
    uint32_t *tx_base;
    uint32_t *rx_base;
    uint8_t pad1[0x14];
    volatile uint8_t state;
    uint8_t pad2[3];
    uint32_t status;
} Handle;

typedef struct {
    uint32_t mode;
    uint32_t index;
    uint32_t w2;
    uint32_t w3;
    uint32_t w4;
    uint32_t w5;
} Request;

bool FUN_08005208(Handle *param_1, Request *param_2)
{
    uint8_t st = param_1->state;
    uint32_t *addr;
    uint32_t v1, v2;

    if (st == 1 || st == 2) {
        if (param_2->mode == 0) {
            v1 = param_2->w2 << 30 | param_2->w3 << 27 | param_2->w4 << 16 | param_2->w5;
            addr = param_1->tx_base + param_2->index;
            *addr = v1;
        } else {
            v1 = param_2->w3 << 29 | param_2->w4;
            v2 = param_2->w2 << 30 | param_2->w5;
            addr = param_1->rx_base + param_2->index * 2;
            *addr = v1;
            addr++;
            *addr = v2;
        }
        return false;
    }
    param_1->status |= 2u;
    return true;
}
