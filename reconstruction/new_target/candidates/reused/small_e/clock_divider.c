#include <stdint.h>

typedef struct { uint32_t reserved[3]; volatile uint32_t CFGR; } RCC_Registers;
extern volatile RCC_Registers RCC;

uint32_t FUN_08008cb0(void)
{
    uint32_t unused;
    uint32_t result;
    uint32_t divisor;
    uint32_t divider;
    uint32_t prescaler;
    uint32_t product;

    (void)unused;
    prescaler = RCC.CFGR & 3u;
    divider = ((RCC.CFGR >> 4) & 0xfu) + 1u;
    if (prescaler == 3u) {
        product = (0x16e3600u / divider) * ((RCC.CFGR >> 8) & 0x7fu);
    } else {
        product = (0x00f42400u / divider) * ((RCC.CFGR >> 8) & 0x7fu);
        __asm__ volatile ("nop");
    }
    divisor = (((RCC.CFGR >> 25) & 3u) + 1u) * 2u;
    result = product / divisor;
    return result;
}
