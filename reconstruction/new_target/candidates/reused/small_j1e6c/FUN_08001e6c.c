/* FUN_08001e6c: GPIO clock-enable + MX_GPIO_Init bring-up, from disassembly at 0x08001e6c. */
#include <stdint.h>

typedef struct { volatile uint32_t r[19]; volatile uint32_t AHB2ENR; } RCC_TypeDef;
typedef struct { volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2]; } GPIO_TypeDef;
typedef struct { uint32_t Pin, Mode, Pull, Speed, Alternate; } GPIO_InitTypeDef;

#define RCC   ((RCC_TypeDef *)0x40021000u)
#define GPIOA ((GPIO_TypeDef *)0x48000000u)
#define GPIOB ((GPIO_TypeDef *)0x48000400u)
#define GPIOC ((GPIO_TypeDef *)0x48000800u)
#define GPIOD ((GPIO_TypeDef *)0x48000c00u)

extern void FUN_08005fa0(GPIO_TypeDef *base, uint32_t channel, uint32_t state);
extern void FUN_08005c9c(GPIO_TypeDef *Instance, GPIO_InitTypeDef *Init);

void FUN_08001e6c(void)
{
    GPIO_InitTypeDef init = {0};
    volatile uint32_t vF, vA, vC, vD, vB;

    RCC->AHB2ENR |= 0x20u;
    vF = RCC->AHB2ENR & 0x20u;
    (void)vF;
    RCC->AHB2ENR |= 0x1u;
    vA = RCC->AHB2ENR & 0x1u;
    (void)vA;
    RCC->AHB2ENR |= 0x4u;
    vC = RCC->AHB2ENR & 0x4u;
    (void)vC;
    RCC->AHB2ENR |= 0x8u;
    vD = RCC->AHB2ENR & 0x8u;
    (void)vD;
    RCC->AHB2ENR |= 0x2u;
    vB = RCC->AHB2ENR & 0x2u;
    (void)vB;

    FUN_08005fa0(GPIOA, 0x9000u, 0);
    FUN_08005fa0(GPIOC, 0x1000u, 0);
    FUN_08005fa0(GPIOD, 4u, 0);
    FUN_08005fa0(GPIOB, 0x218u, 0);

    init.Pin = 0x9000u;
    init.Mode = 1u;
    init.Pull = 0u;
    init.Speed = 0u;
    FUN_08005c9c(GPIOA, &init);

    init.Pin = 0x1000u;
    init.Mode = 1u;
    init.Pull = 0u;
    init.Speed = 0u;
    FUN_08005c9c(GPIOC, &init);

    init.Pin = 4u;
    init.Mode = 1u;
    init.Pull = 0u;
    init.Speed = 0u;
    FUN_08005c9c(GPIOD, &init);

    init.Pin = 0x218u;
    init.Mode = 1u;
    init.Pull = 0u;
    init.Speed = 0u;
    FUN_08005c9c(GPIOB, &init);
}
