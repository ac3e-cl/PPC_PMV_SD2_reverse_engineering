#include <stdint.h>
typedef struct { volatile uint32_t ISER[8]; uint32_t RESERVED0[24]; volatile uint32_t ICER[8]; uint32_t RESERVED1[24];
                 volatile uint32_t ISPR[8]; uint32_t RESERVED2[24]; volatile uint32_t ICPR[8]; uint32_t RESERVED3[24];
                 volatile uint32_t IABR[8]; uint32_t RESERVED4[56]; volatile uint8_t IP[828]; } NVIC_Type;
#define NVIC ((NVIC_Type *)0xe000e100u)
typedef struct { volatile uint32_t CPUID; volatile uint32_t ICSR; volatile uint32_t VTOR; volatile uint32_t AIRCR;
                 volatile uint32_t SCR; volatile uint32_t CCR; volatile uint8_t SHP[12]; } SCB_Type;
#define SCB ((SCB_Type *)0xe000ed00u)

void FUN_08004dd4(int8_t param_1, uint32_t param_2)
{
    if ((param_1 >= 0)) {
        NVIC->IP[param_1] = (uint8_t)(param_2 << 4);
    } else {
        SCB->SHP[((uint32_t)param_1 & 0xFu) - 4u] = (uint8_t)(param_2 << 4);
    }
}
