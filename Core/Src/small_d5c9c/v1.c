/* FUN_08005c9c: ST HAL-style GPIO_Init with SYSCFG EXTICR + EXTI edge/mask handling. */
#include <stdint.h>

typedef struct {
    volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct {
    uint32_t Pin, Mode, Pull, Speed, Alternate;
} GPIO_InitTypeDef_;

typedef struct { volatile uint32_t r[24]; volatile uint32_t ENR; } RCC_TypeDef_;
typedef struct { volatile uint32_t w[2]; volatile uint32_t EXTICR[8]; } SYSCFG_TypeDef_;
typedef struct { volatile uint32_t IMR1, EMR1, RTSR1, FTSR1; } EXTI_TypeDef_;

#define GPIOA ((GPIO_TypeDef *)0x48000000u)
#define GPIOB ((GPIO_TypeDef *)0x48000400u)
#define GPIOC ((GPIO_TypeDef *)0x48000800u)
#define GPIOD ((GPIO_TypeDef *)0x48000c00u)
#define GPIOE ((GPIO_TypeDef *)0x48001000u)
#define GPIOF ((GPIO_TypeDef *)0x48001400u)
#define RCC   ((RCC_TypeDef_ *)0x40021000u)
#define SYSE  ((SYSCFG_TypeDef_ *)0x40010000u)
#define EXTI  ((EXTI_TypeDef_ *)0x40010400u)

void FUN_08005c9c(GPIO_TypeDef *Instance, GPIO_InitTypeDef_ *Init)
{
    uint32_t pinpos, tmpreg, currentpin;
    volatile uint32_t v;

    for (pinpos = 0U; (Init->Pin >> pinpos) != 0U; pinpos++) {
        currentpin = Init->Pin & (1UL << pinpos);
        if (currentpin != 0U) {
            if (((Init->Mode & 3U) == 1U) || ((Init->Mode & 3U) == 2U)) {
                tmpreg = Instance->OSPEEDR;
                tmpreg &= ~(3UL << (pinpos << 1));
                tmpreg |= (Init->Speed << (pinpos << 1));
                Instance->OSPEEDR = tmpreg;
                tmpreg = Instance->OTYPER;
                tmpreg &= ~(1UL << pinpos);
                tmpreg |= ((Init->Mode >> 4) & 1UL) << pinpos;
                Instance->OTYPER = tmpreg;
            }
            if ((Init->Mode & 3U) != 3U) {
                tmpreg = Instance->PUPDR;
                tmpreg &= ~(3UL << (pinpos << 1));
                tmpreg |= (Init->Pull << (pinpos << 1));
                Instance->PUPDR = tmpreg;
            }
            if ((Init->Mode & 3U) == 2U) {
                tmpreg = Instance->AFR[pinpos >> 3];
                tmpreg &= ~(0xFUL << ((pinpos & 7UL) * 4UL));
                tmpreg |= (Init->Alternate << ((pinpos & 7UL) * 4UL));
                Instance->AFR[pinpos >> 3] = tmpreg;
            }
            tmpreg = Instance->MODER;
            tmpreg &= ~(3UL << (pinpos << 1));
            tmpreg |= ((Init->Mode & 3UL) << (pinpos << 1));
            Instance->MODER = tmpreg;
            if ((Init->Mode & 0x30000UL) != 0UL) {
                RCC->ENR |= 1UL;
                v = RCC->ENR & 1UL;
                (void)v; /* ST HAL dummy readback (UNUSED) */
                tmpreg = SYSE->EXTICR[pinpos >> 2];
                tmpreg &= ~(0xFUL << ((pinpos & 3UL) * 4UL));
                tmpreg |= (Instance == GPIOA ? 0UL :
                           Instance == GPIOB ? 1UL :
                           Instance == GPIOC ? 2UL :
                           Instance == GPIOD ? 3UL :
                           Instance == GPIOE ? 4UL :
                           Instance == GPIOF ? 5UL : 6UL) << ((pinpos & 3UL) * 4UL);
                SYSE->EXTICR[pinpos >> 2] = tmpreg;
                tmpreg = EXTI->RTSR1;
                tmpreg &= ~currentpin;
                if ((Init->Mode & 0x100000UL) != 0UL) {
                    tmpreg |= currentpin;
                }
                EXTI->RTSR1 = tmpreg;
                tmpreg = EXTI->FTSR1;
                tmpreg &= ~currentpin;
                if ((Init->Mode & 0x200000UL) != 0UL) {
                    tmpreg |= currentpin;
                }
                EXTI->FTSR1 = tmpreg;
                tmpreg = EXTI->EMR1;
                tmpreg &= ~currentpin;
                if ((Init->Mode & 0x20000UL) != 0UL) {
                    tmpreg |= currentpin;
                }
                EXTI->EMR1 = tmpreg;
                tmpreg = EXTI->IMR1;
                tmpreg &= ~currentpin;
                if ((Init->Mode & 0x10000UL) != 0UL) {
                    tmpreg |= currentpin;
                }
                EXTI->IMR1 = tmpreg;
            }
        }
    }
}
