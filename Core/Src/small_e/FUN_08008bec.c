#include <stdint.h>

/* RCC at 0x40021000; CFGR field at +0x8, PLLCFGR at +0xc. */
typedef struct { uint32_t reserved[2]; volatile uint32_t CFGR; volatile uint32_t PLLCFGR; } RCC_Fields;
extern volatile RCC_Fields RCC;

/* System clock frequency: HSI (16 MHz) / HSE (24 MHz) / PLL derived. */
uint32_t FUN_08008bec(void)
{
    uint32_t unused;
    uint32_t multiplier;
    uint32_t divider;
    uint32_t prescaler;
    uint32_t product;
    uint32_t result;

    (void)unused;
    if ((RCC.CFGR & 0xcu) == 4u) {
        result = 0x00f42400u;
    } else if ((RCC.CFGR & 0xcu) == 8u) {
        result = 0x016e3600u;
    } else if ((RCC.CFGR & 0xcu) == 0xcu) {
        prescaler = RCC.PLLCFGR & 3u;
        divider = ((RCC.PLLCFGR >> 4) & 0xfu) + 1u;
        if (prescaler == 3u) {
            product = (0x016e3600u / divider) * ((RCC.PLLCFGR >> 8) & 0x7fu);
        } else {
            product = (0x00f42400u / divider) * ((RCC.PLLCFGR >> 8) & 0x7fu);
            __asm__ volatile ("nop");
        }
        multiplier = (((RCC.PLLCFGR >> 25) & 3u) + 1u) * 2u;
        result = product / multiplier;
    } else {
        result = 0u;
    }
    return result;
}
