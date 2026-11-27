#include <stdint.h>

typedef struct {
    uint32_t reserved[2];
    uint32_t value;
} Handle;

void FUN_0800497c(Handle *param_1, uint32_t param_2)
{
    param_1->value = (param_1->value & 0x3fffffc0u) |
                     (param_2 & 0x40000000u) | 0x80000000u;
}
