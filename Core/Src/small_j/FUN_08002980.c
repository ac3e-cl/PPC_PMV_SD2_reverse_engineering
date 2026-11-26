#include <stdint.h>

extern volatile uint32_t RATE;
extern volatile uint32_t TIMER;
extern volatile uint32_t STATE;

extern int helper_busy(uint32_t);
extern void helper_apply(uint32_t, uint32_t, uint32_t);

uint8_t FUN_08002980(uint32_t param_1)
{
    uint8_t result = 0;
    if (RATE != 0) {
        if (helper_busy(TIMER / (1000u / RATE)) == 0) {
            if (param_1 < 16u) {
                helper_apply(0xffffffffu, param_1, 0);
                STATE = param_1;
            } else {
                result = 1;
            }
        } else {
            result = 1;
        }
    } else {
        result = 1;
    }
    return result;
}
