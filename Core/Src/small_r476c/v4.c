#include <stdint.h>

typedef struct { volatile uint32_t reg0, reserved, status; } Device;
typedef struct {
    uint8_t reserved[0x5c];
    volatile uint32_t status;
    volatile uint32_t control;
} Handle;
extern int FUN_08002e80(uint32_t);
extern void FUN_08002e30(uint32_t);
extern uint32_t FUN_08002ac0(uint32_t);
extern uint32_t FUN_08002a18(void);
extern volatile uint32_t CLK;

uint32_t FUN_0800476c(Handle *p)
{
    volatile uint32_t delay = 0;
    uint32_t started;

    if (FUN_08002e80(*(uint32_t *)p) == 0) {
    if ((0x8000003fu & ((Device *)(uintptr_t)*(uint32_t *)p)->status) != 0) {
        p->status |= 0x10u;
        p->control |= 1u;
        return 1;
    }
    FUN_08002e30(*(uint32_t *)p);
    if ((FUN_08002ac0((*(uint32_t *)p == 0x50000000u || *(uint32_t *)p == 0x50000100u) ? 0x50000300u : 0x50000700u) & 0x800000u) != 0) {
        delay = (*(volatile uint32_t *)&CLK / 200000u + 1u) * 12u;
        while (delay != 0) delay--;
    }
    started = FUN_08002a18();
    while ((*(volatile uint32_t *)(*(uint32_t *)p) & 1u) != 1u) {
        if (FUN_08002e80(*(uint32_t *)p) == 0)
            FUN_08002e30(*(uint32_t *)p);
        if ((uint32_t)(FUN_08002a18() - started) > 2u &&
            (*(volatile uint32_t *)(*(uint32_t *)p) & 1u) != 1u) {
            p->status |= 0x10u;
            p->control |= 1u;
            return 1;
        }
    }
    }
    return 0;
}
