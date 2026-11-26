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
} GPIO_TypeDef;

void FUN_08005fd0(GPIO_TypeDef *gpio, uint16_t pins)
{
    uint32_t output = gpio->ODR;
    gpio->BSRR = ((output & pins) << 16) | (~output & pins);
}
