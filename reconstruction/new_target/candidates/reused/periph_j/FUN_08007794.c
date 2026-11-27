#include <stdint.h>

struct State {
    uint8_t pad[0xdc];
    uint8_t c;
    volatile uint8_t d;
};
extern void FUN_08007f3c(struct State *, uint32_t, uint32_t, void *);

uint32_t FUN_08007794(struct State *param_1, uint32_t param_2,
                      uint32_t param_3, void *param_4)
{
    if (param_1->d == 2) return 2;
    if (param_1->c == 1) return 2;
    param_1->c = 1;
    param_1->d = 2;
    FUN_08007f3c(param_1, param_2, param_3, param_4);
    param_1->d = 1;
    param_1->c = 0;
    return 0;
}
