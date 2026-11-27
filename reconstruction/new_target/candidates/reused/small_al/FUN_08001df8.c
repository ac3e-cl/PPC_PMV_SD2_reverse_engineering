#include <stdint.h>

typedef struct { uint32_t field[7]; } GlobalState;
extern volatile GlobalState GLOBAL_STATE;
#define INITIAL_PERIPHERAL 0x40001400u

extern int FUN_080091d8(volatile uint32_t *);
extern int FUN_0800982c(volatile uint32_t *, uint32_t *);
extern void FUN_08002244(void);

void FUN_08001df8(uint32_t param_1)
{
    volatile uint32_t locals[3] = {0, 0, 0};

    GLOBAL_STATE.field[0] = INITIAL_PERIPHERAL;
    GLOBAL_STATE.field[1] = 999;
    GLOBAL_STATE.field[2] = 0;
    GLOBAL_STATE.field[3] = param_1;
    GLOBAL_STATE.field[6] = 0x80;
    if (FUN_080091d8(&GLOBAL_STATE.field[0]) != 0)
        FUN_08002244();

    locals[0] = 0;
    locals[2] = 0;
    if (FUN_0800982c(&GLOBAL_STATE.field[0], (uint32_t *)&locals[0]) != 0)
        FUN_08002244();
}
