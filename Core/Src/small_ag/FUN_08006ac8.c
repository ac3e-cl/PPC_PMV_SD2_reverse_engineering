#include <stdint.h>

typedef struct {
    volatile uint8_t reserved[0x3d0];
    volatile uint32_t control0;
    volatile uint32_t control1;
} Peripheral;

typedef struct { Peripheral *Instance; } Handle;

void FUN_08006ac8(Handle *handle, uint32_t param_2, uint32_t param_3)
{
    if ((param_2 & 1u) != 0u)
        handle->Instance->control0 = (handle->Instance->control0 & 0xfffffffeu) | (param_3 & 1u);
    if ((param_2 & 2u) != 0u)
        handle->Instance->control0 = (handle->Instance->control0 & 0xfffffeffu) | ((param_3 & 1u) << 8);
    if ((param_2 & 4u) != 0u)
        handle->Instance->control0 = (handle->Instance->control0 & 0xfffeffffu) | ((param_3 & 1u) << 16);
    if ((param_2 & 8u) != 0u)
        handle->Instance->control0 = (handle->Instance->control0 & 0xfeffffffu) | ((param_3 & 1u) << 24);
    if ((param_2 & 0x10u) != 0u)
        handle->Instance->control1 = (handle->Instance->control1 & 0xfffffffeu) | (param_3 & 1u);
    if ((param_2 & 0x20u) != 0u)
        handle->Instance->control1 = (handle->Instance->control1 & 0xfffffeffu) | ((param_3 & 1u) << 8);
}
