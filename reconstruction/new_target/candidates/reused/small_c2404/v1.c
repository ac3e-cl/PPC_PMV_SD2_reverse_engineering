/* FUN_08002404: ADC1 ADC_Init + HRT timer config + NVIC enables. */
#include <stdint.h>

typedef struct { uint32_t *Instance; } ADC_HandleTypeDef_;
typedef struct { volatile uint32_t p0[19]; volatile uint32_t AHB2ENR;
                 volatile uint32_t p1[2]; volatile uint32_t AHB3ENR; } RCC_TypeDef;
#define RCC ((RCC_TypeDef *)0x40021000u)

extern void FUN_080099e4(void *, uint8_t, int32_t);
extern uint32_t FUN_08008d3c(void *);
extern void FUN_08002244(void);
extern void FUN_08005c9c(void *, void *);
extern void FUN_08004eea(uint32_t, uint32_t, uint32_t);
extern void FUN_08004f1e(uint8_t);

void FUN_08002404(ADC_HandleTypeDef_ *param_1)
{
    uint32_t hrt[5] = {0u};
    uint32_t ini[21];
    volatile uint32_t v3;
    volatile uint32_t v2;

    FUN_080099e4(ini, 0u, 0x54);
    if (param_1->Instance == (uint32_t *)0x40006800u) {
        ini[0] = 0x1000u;
        ini[14] = 0x2000000u;
        if (FUN_08008d3c(ini) != 0u) {
            FUN_08002244();
        }
        RCC->AHB3ENR |= 0x2000000u;
        v3 = RCC->AHB3ENR & 0x2000000u;
        (void)v3; /* ST HAL dummy readback (UNUSED) */
        RCC->AHB2ENR |= 0x2u;
        v2 = RCC->AHB2ENR & 0x2u;
        (void)v2;
        hrt[0] = 0x60u;
        hrt[1] = 2u;
        hrt[2] = 0u;
        hrt[3] = 0u;
        hrt[4] = 9u;
        FUN_08005c9c((void *)0x48000400u, hrt);
        FUN_08004eea(0x56u, 0u, 0u);
        FUN_08004f1e(0x56u);
    }
}
