#include <stdint.h>

typedef struct {
    uint8_t reserved[0xdd];
    volatile uint8_t status;
} Device;

extern void FUN_08007958(Device *object, uint32_t value);
extern void FUN_080079b6(Device *object, uint32_t request, uint32_t value);

uint32_t FUN_080062bc(Device *object, uint32_t request, uint32_t value) {
    if (object->status == 2) {
        return 2;
    }
    object->status = 2;
    if (request == 6) {
        FUN_08007958(object, value);
    } else {
        FUN_080079b6(object, request, value);
    }
    object->status = 1;
    return 0;
}
