#include <stdint.h>

typedef struct {
    volatile uint32_t moder;
    volatile uint8_t reserved0[0x14 - sizeof(uint32_t)];
    volatile uint32_t otyper;
    volatile uint32_t ospeedr;
} GPIO_TypeDef;

typedef struct { GPIO_TypeDef *Instance; } Handle;
typedef struct { uint32_t a, b, c, d; } Config;

void FUN_08007958(Handle *param_1, Config *param_2)
{
    uint32_t value = param_1->Instance->moder;
    value &= 0xfffffff8u;
    value |= param_2->c;
    value &= 0xffffffe7u;
    value |= param_2->d;
    param_1->Instance->moder = value;
    param_1->Instance->otyper = param_2->a;
    param_1->Instance->ospeedr = param_2->b;
}
