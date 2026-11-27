#include <stdint.h>

typedef struct { volatile uint32_t value; uint8_t pad[124]; } Row;
typedef struct { uint8_t pad[0xb8]; Row row[]; } RegBlock;
typedef struct {
    RegBlock *Instance;
    uint8_t reserved[0xd8];
    uint8_t busy;
    volatile uint8_t state;
} Handle;

typedef struct {
    uint32_t field0, field1, field2, field3, field4;
    uint32_t field5, field6, field7, field8;
} Config;

#define DAT_080074b0 0x01ff0000u
#define DAT_080074b4 0x3c002000u

uint32_t FUN_080073b8(Handle *handle, int channel, const Config *config)
{
    if (handle->state == 2) return 2;
    if (handle->busy == 1) return 2;
    handle->busy = 1;
    handle->state = 2;

    uint32_t value = config->field0 & 0x00001c00u;
    value |= config->field1 & 0x000001ffu;
    value |= config->field2 & 0x00000200u;
    value |= config->field4 & 0x00004000u;
    value |= config->field3 & 0x00008000u;
    value |= DAT_080074b0 & (config->field5 << 16);
    value |= config->field6 & 0x02000000u;
    value |= config->field8 & 0x40000000u;
    value |= config->field7 & 0x80000000u;

    handle->Instance->row[channel].value =
        (handle->Instance->row[channel].value & DAT_080074b4) | value;

    handle->state = 1;
    handle->busy = 0;
    return 0;
}
