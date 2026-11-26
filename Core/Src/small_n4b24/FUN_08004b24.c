#include <stdint.h>

typedef struct {
    uint32_t reserved[2];
    uint32_t status;
} Handle;

typedef struct {
    uint32_t base;
    uint8_t pad1[0x34];
    uint8_t byte38;
    uint8_t pad2[0x1f];
    uint8_t flag58;
    uint8_t pad3[3];
    uint32_t ctrl;
} Cfg;

typedef struct {
    uint32_t w[3];
} Words;

extern int FUN_08004956(Handle *param_1);
extern int FUN_080049d6(Handle *param_1);

uint8_t FUN_08004b24(Cfg *param_1, Words *param_2)
{
    uint8_t ret;
    int v78;
    Words *v74;
    uint32_t state[27];

    ret = 0;
    if (param_1->flag58 == 1) {
        return 2;
    }
    param_1->flag58 = 1;
    state[23] = 0;
    state[24] = 0;
    if (param_1->base == 0x50000000u) {
        state[0] = 0x50000100u;
    } else if (param_1->base == 0x50000400u) {
        state[0] = 0x50000500u;
    } else {
        state[0] = 0;
    }
    if (state[0] == 0) {
        param_1->ctrl = param_1->ctrl | 0x20u;
        param_1->flag58 = 0;
        return 1;
    }
    v78 = FUN_080049d6((Handle *)(uintptr_t)state[0]);
    if (FUN_080049d6((Handle *)(uintptr_t)param_1->base) == 0 && v78 == 0) {
        v74 = (param_1->base == 0x50000000u || param_1->base == 0x50000100u)
                  ? (Words *)0x50000300u
                  : (Words *)0x50000700u;
        if (param_2->w[0] != 0) {
            v74->w[2] = (v74->w[2] & 0xffff1fffu) | (param_2->w[1] | ((uint32_t)param_1->byte38 << 13));
            if ((param_1->base == 0x50000000u || param_1->base == 0x50000100u)
                    ? ((FUN_08004956((Handle *)0x50000000u) |
                        FUN_08004956((Handle *)(uintptr_t)0x50000100u)) == 0)
                    : ((FUN_08004956((Handle *)(uintptr_t)0x50000400u) |
                        FUN_08004956((Handle *)(uintptr_t)0x50000500u) |
                        FUN_08004956((Handle *)(uintptr_t)0x50000600u)) == 0)) {
                v74->w[2] = (v74->w[2] & 0xfffff0e0u) | (param_2->w[0] | param_2->w[2]);
            }
        } else {
            v74->w[2] = v74->w[2] & 0xffff1fffu;
            if ((param_1->base == 0x50000000u || param_1->base == 0x50000100u)
                    ? ((FUN_08004956((Handle *)0x50000000u) |
                        FUN_08004956((Handle *)(uintptr_t)0x50000100u)) == 0)
                    : ((FUN_08004956((Handle *)(uintptr_t)0x50000400u) |
                        FUN_08004956((Handle *)(uintptr_t)0x50000500u) |
                        FUN_08004956((Handle *)(uintptr_t)0x50000600u)) == 0)) {
                v74->w[2] = v74->w[2] & 0xfffff0e0u;
            }
        }
    } else {
        param_1->ctrl = param_1->ctrl | 0x20u;
        ret = 1;
    }
    param_1->flag58 = 0;
    return ret;
}
