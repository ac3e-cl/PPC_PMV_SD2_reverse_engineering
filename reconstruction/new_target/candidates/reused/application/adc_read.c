#include <stdint.h>

typedef struct {
    uint32_t reserved[16];
    volatile uint32_t input;
} ADC_Registers;

uint32_t FUN_0800262c(ADC_Registers *adc)
{
    return adc->input & 0xffffu;
}
