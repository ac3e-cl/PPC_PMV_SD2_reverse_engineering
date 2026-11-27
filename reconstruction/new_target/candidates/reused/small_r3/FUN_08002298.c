/* FUN_08002298: HRTIM-driven ADC init for two instances + RCC AHB2 gating + NVIC. */
#include <stdint.h>

typedef struct { uint32_t *Instance; } ADC_HandleTypeDef_;
typedef struct { volatile uint32_t p0[19]; volatile uint32_t AHB2ENR;
                 volatile uint32_t p1[2]; volatile uint32_t AHB3ENR; } RCC_TypeDef;
#define RCC ((RCC_TypeDef *)0x40021000u)

extern uint32_t hr_counter;

extern void FUN_080099e4(void *, uint8_t, int32_t);
extern uint32_t FUN_08008d3c(void *);
extern void FUN_08002244(void);
extern void FUN_08005c9c(void *, void *);
extern void FUN_08004eea(uint32_t, uint32_t, uint32_t);
extern void FUN_08004f1e(uint8_t);

void FUN_08002298(ADC_HandleTypeDef_ *param_1)
{
    uint32_t hrt[5] = {0u};
    uint32_t ini[21];
    volatile uint32_t a1;
    volatile uint32_t b1;
    volatile uint32_t a2;
    volatile uint32_t b2;

    FUN_080099e4(ini, 0u, 0x54);
    if (param_1->Instance == (uint32_t *)0x50000000u) {
        ini[0] = 0x8000u;
        ini[17] = 0x20000000u;
        if (FUN_08008d3c(ini) != 0u) {
            FUN_08002244();
        }
        hr_counter = hr_counter + 1u;
        if (hr_counter == 1u) {
            RCC->AHB2ENR |= 0x2000u;
            a1 = RCC->AHB2ENR & 0x2000u;
            (void)a1; /* ST HAL dummy readback (UNUSED) */
        }
        RCC->AHB2ENR |= 1u;
        b1 = RCC->AHB2ENR & 1u;
        (void)b1;
        hrt[0] = 8u;
        hrt[1] = 3u;
        hrt[2] = 0u;
        FUN_08005c9c((void *)0x48000000u, hrt);
        FUN_08004eea(0x12u, 1u, 0u);
        FUN_08004f1e(0x12u);
    } else if (param_1->Instance == (uint32_t *)0x50000100u) {
        ini[0] = 0x8000u;
        ini[17] = 0x20000000u;
        if (FUN_08008d3c(ini) != 0u) {
            FUN_08002244();
        }
        hr_counter = hr_counter + 1u;
        if (hr_counter == 1u) {
            RCC->AHB2ENR |= 0x2000u;
            a2 = RCC->AHB2ENR & 0x2000u;
            (void)a2;
        }
        RCC->AHB2ENR |= 4u;
        b2 = RCC->AHB2ENR & 4u;
        (void)b2;
        hrt[0] = 0x10u;
        hrt[1] = 3u;
        hrt[2] = 0u;
        FUN_08005c9c((void *)0x48000800u, hrt);
        FUN_08004eea(0x12u, 1u, 0u);
        FUN_08004f1e(0x12u);
    }
}
