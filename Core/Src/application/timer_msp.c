#include <stdint.h>

extern void FUN_08004eea(uint32_t irq, uint32_t preemption, uint32_t subpriority);
extern void FUN_08004f1e(uint32_t irq);

typedef struct {
    uint32_t reserved[22];
    volatile uint32_t apb1_enable;
} RCC_Registers;
#define RCC ((RCC_Registers *)0x40021000u)

void FUN_080025e0(uint32_t *handle)
{
    if (*handle == 0x40001400) {
        volatile uint32_t delay;
        RCC->apb1_enable |= 0x20;
        delay = RCC->apb1_enable & 0x20;
        (void)delay;
        FUN_08004eea(0x37, 0, 0);
        FUN_08004f1e(0x37);
    }
}
