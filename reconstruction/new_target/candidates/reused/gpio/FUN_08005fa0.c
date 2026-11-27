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

void FUN_08005fa0(GPIO_TypeDef *gpio, uint16_t pins, char set)
{
    if (set != 0) {
        gpio->BSRR = pins;
    } else {
        gpio->BRR = pins;
    }
}
