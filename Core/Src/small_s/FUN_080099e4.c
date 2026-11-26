#include <stdint.h>

uint8_t *FUN_080099e4(uint8_t *param_1, uint8_t param_2, int param_3)
{
    uint8_t *end = param_1 + param_3;
    uint8_t *current = param_1;
    while (current != end) {
        *current = param_2;
        ++current;
    }
    return param_1;
}
