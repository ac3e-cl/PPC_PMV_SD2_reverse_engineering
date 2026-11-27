#include <stdint.h>

typedef struct {
    volatile uint8_t reserved0[0x58];
    uint8_t busy;
    uint8_t reserved1[3];
    volatile uint32_t status;
} Handle;

extern char FUN_080045f4(Handle *, uint32_t);
extern char FUN_08004898(Handle *);

char FUN_080034d0(Handle *handle)
{
    if (handle->busy == 1) return 2;
    handle->busy = 1;
    char result = FUN_080045f4(handle, 3);
    if (result == 0) {
        result = FUN_08004898(handle);
        if (result == 0) handle->status = (handle->status & 0xffffeefeu) | 1u;
    }
    handle->busy = 0;
    return result;
}
