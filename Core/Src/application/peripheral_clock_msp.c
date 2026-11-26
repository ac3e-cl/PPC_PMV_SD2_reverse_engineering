#include <stdint.h>

typedef struct { uint32_t pin, mode, pull, speed, alternate; } GPIO_Init;
typedef struct {
    uint32_t reserved[19];
    volatile uint32_t ahb2_enable;
    uint32_t reserved_50_5c[4];
    volatile uint32_t apb2_enable;
} RCC_Registers;
#define RCC ((RCC_Registers *)0x40021000u)
extern void FUN_08005c9c(void *gpio, GPIO_Init *init);

void FUN_080024c8(uint32_t *handle)
{
    GPIO_Init init = {0};
    if (*handle == 0x40016800) {
        {
            volatile uint32_t delay;
            RCC->apb2_enable |= 0x4000000;
            delay = RCC->apb2_enable & 0x4000000;
            (void)delay;
        }
        {
            volatile uint32_t delay;
            RCC->ahb2_enable |= 4;
            delay = RCC->ahb2_enable & 4;
            (void)delay;
        }
        init.pin = 0x400;
        init.mode = 2;
        init.pull = 1;
        init.speed = 0;
        init.alternate = 13;
        FUN_08005c9c((void *)0x48000800, &init);
    }
}
