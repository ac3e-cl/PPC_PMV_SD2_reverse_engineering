#include <stdint.h>

extern uint32_t FUN_08004d7c(void);
extern uint32_t FUN_08004e28(uint32_t, uint32_t, uint32_t);
extern void FUN_08004dd4(int8_t, uint32_t);

void FUN_08004eea(int8_t param_1, uint32_t param_2, uint32_t param_3)
{
    uint32_t uVar1 = FUN_08004d7c();
    FUN_08004dd4(param_1,
                  FUN_08004e28(uVar1, param_2, param_3));
}
