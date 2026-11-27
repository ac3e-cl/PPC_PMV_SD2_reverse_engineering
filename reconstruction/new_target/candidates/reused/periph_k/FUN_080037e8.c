#include <stdint.h>

typedef struct {
    volatile uint32_t reserved;
    volatile uint32_t control;
} Peripheral;

typedef struct {
    Peripheral *peripheral;
    uint8_t reserved[0x54];
    uint8_t busy;
    uint8_t reserved1[3];
    uint32_t status;
} Handle;

extern char FUN_080045f4(Handle *, uint32_t);
extern char FUN_08004898(Handle *);

char FUN_080037e8(Handle *handle)
{
    if (handle->busy == 1) return 2;
    handle->busy = 1;
    char result = FUN_080045f4(handle, 3);
    if (result == 0) {
        handle->peripheral->control &= 0xffffffe3u;
        result = FUN_08004898(handle);
        if (result == 0) handle->status = (handle->status & 0xffffeefeu) | 1u;
    }
    handle->busy = 0;
    return result;
}
