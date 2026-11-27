#include <stdbool.h>
#include <stdint.h>

extern void FUN_08004dd4(int irq, uint32_t priority);
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_Type;
extern volatile SysTick_Type SYSTICK;

bool FUN_08004e90(int param_1)
{
    if ((uint32_t)(param_1 - 1u) >= 0x01000000u) {
        return true;
    }
    register volatile SysTick_Type *base __asm__("r2") = &SYSTICK;
    register uint32_t reload __asm__("r3") = (uint32_t)(param_1 - 1);
    base->LOAD = reload;
    FUN_08004dd4(-1, 0x0fu);
    SYSTICK.VAL = 0;
    SYSTICK.CTRL = 7;
    return false;
}
