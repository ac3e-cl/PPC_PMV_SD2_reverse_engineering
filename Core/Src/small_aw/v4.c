#include <stdint.h>

typedef struct { volatile uint32_t ISER[8]; } NVIC_Type;
#define NVIC ((NVIC_Type *)0xe000e100u)

void FUN_08004d98(uint8_t param_1)
{
    if ((int8_t)param_1 >= 0) {
        NVIC->ISER[(uint32_t)(int8_t)param_1 >> 5] = 1u << ((uint32_t)param_1 & 0x1ful);
    }
}
