#include <stdint.h>

typedef struct {
    uint32_t reserved[22];
    volatile uint32_t apb1_enable;
    uint32_t reserved_5c;
    volatile uint32_t apb2_enable;
} RCC_Registers;
#define RCC ((RCC_Registers *)0x40021000u)
extern void FUN_08008330(void);

void FUN_08002250(void)
{
    {
        volatile uint32_t delay;
        RCC->apb2_enable |= 1;
        delay = RCC->apb2_enable & 1;
        (void)delay;
    }
    {
        volatile uint32_t delay;
        RCC->apb1_enable |= 0x10000000;
        delay = RCC->apb1_enable & 0x10000000;
        (void)delay;
    }
    FUN_08008330();
}
