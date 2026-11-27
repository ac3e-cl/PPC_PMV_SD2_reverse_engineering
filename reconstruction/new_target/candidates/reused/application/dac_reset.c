#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
    volatile uint32_t BRR;
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t control;
    volatile uint8_t reserved[0x394 - sizeof(uint32_t)];
    volatile uint32_t request;
} Peripheral;

typedef struct {
    Peripheral *Instance;
    uint8_t reserved[0xd8];
    uint8_t state;
    uint8_t busy;
} Handle;

extern void FUN_08005fa0(GPIO_TypeDef *gpio, uint16_t pins, char set);
extern uint32_t FUN_08007850(Handle *handle, uint32_t mask);
extern uint32_t FUN_08007900(Handle *handle, uint32_t mask);

extern Handle dac_handle;
extern uint16_t sample_dac_first, sample_dac_second, sample_dac_third;

void FUN_080020b4(void)
{
    FUN_08005fa0((GPIO_TypeDef *)0x48000c00u, 4, 0);
    FUN_08007850(&dac_handle, 0x100);
    FUN_08007850(&dac_handle, 0x200);
    FUN_08007850(&dac_handle, 0x400);
    FUN_08007850(&dac_handle, 0x800);
    FUN_08007900(&dac_handle, 0x10000);
    FUN_08007900(&dac_handle, 0x200000);
    FUN_08007900(&dac_handle, 0x400000);
    FUN_08005fa0((GPIO_TypeDef *)0x48000400u, 0x10, 0);
    FUN_08005fa0((GPIO_TypeDef *)0x48000400u, 8, 0);
    FUN_08005fa0((GPIO_TypeDef *)0x48000800u, 0x1000, 0);
    sample_dac_first = 0;
    sample_dac_second = 0;
    sample_dac_third = 0;
}
