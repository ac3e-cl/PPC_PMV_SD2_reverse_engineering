#include <stdint.h>

typedef struct {
    uint32_t pad0[5];              /* 0x00-0x10 */
    uint32_t w14, w18, w1c, w20;   /* 0x14-0x20 */
    uint32_t w24, w28, w2c, w30;   /* 0x24-0x30 */
    uint32_t w34, w38, w3c, w40;   /* 0x34-0x40 */
    uint32_t w44, w48, w4c, w50;   /* 0x44-0x50 */
    uint32_t w54, w58;             /* 0x54-0x58 */
} Cfg;

typedef uint8_t Row[128];
typedef struct { uint8_t gap[0x3a0]; uint32_t ctl; } Bank;
typedef struct { uint32_t value; uint8_t pad[124]; } ControlRow;
typedef struct { uint8_t pad[128]; ControlRow row[]; } ControlBlock;
typedef struct { uint32_t d4; uint8_t gap[12]; uint32_t e4, e8; uint8_t pad[104]; } DataRow;
typedef struct { uint8_t pad[0xd4]; DataRow row[]; } DataBlock;


void FUN_08007b70(Row **param_1, uint32_t param_2, Cfg *param_3)
{
    uint32_t v24;
    uint32_t v20;
    uint32_t v1c;
    uint32_t v18;
    uint32_t v14;

    ((ControlBlock *)*param_1)->row[param_2].value = ((ControlBlock *)*param_1)->row[param_2].value & 0x0fffffffU;
    v24 = ((ControlBlock *)*param_1)->row[param_2].value;
    v18 = ((DataBlock *)*param_1)->row[param_2].e8;
    v20 = ((DataBlock *)*param_1)->row[param_2].e4;
    v1c = ((Bank *)(void *)(*param_1))->ctl;
    v24 = v24 & ~0x20U;
    v24 = v24 | param_3->w14;
    if (param_3->w14 == 0x20U || param_3->w18 == 2U) {
        v24 = v24 & ~0x180U;
        v24 = v24 | 0x20U;
    } else if (param_3->w18 == 3U) {
        v24 = v24 | 0x80U;
        v24 = v24 & ~0x100U;
    } else if (param_3->w18 == 4U) {
        v24 = v24 | 0x100U;
        v24 = v24 & ~0x80U;
    } else {
        v24 = v24 & ~0x20U;
        v24 = v24 & ~0x180U;
    }
    v24 = v24 & ~0x800U;
    v24 = v24 | param_3->w1c;
    v24 = v24 & ~0x400U;
    v24 = v24 | param_3->w20;
    v24 = v24 & ~0x6000000U;
    v24 = v24 | param_3->w24;
    v24 = v24 & ~0x8000000U;
    v24 = v24 | param_3->w28;
    v24 = v24 & ~0xf0000000U;
    v24 = v24 | param_3->w2c;
    v24 = v24 & ~0x20000U;
    if (param_3->w34 == 0x20000000U) {
        v24 = v24 | 0x20000U;
    }
    v24 = v24 & ~0x40U;
    v24 = v24 | param_3->w38;
    v24 = v24 & ~0x40000U;
    v24 = v24 | param_3->w58;
    v24 = v24 & 0xfe06ffffU;
    v24 = v24 | param_3->w50;
    v18 = v18 & ~0x3fU;
    v18 = v18 | (param_3->w3c & 0x3fU);
    v18 = v18 & ~0x80000000U;
    v18 = v18 | param_3->w40;
    v20 = v20 & ~0x100U;
    v20 = v20 | param_3->w44;
    if ((param_3->w48 != 0xe00U && param_3->w48 != 0x1e00U) || param_3->w38 == 0x40U) {
        v20 = v20 & ~0x1e00U;
        v20 = v20 | param_3->w48;
    }
    v20 = v20 & ~0x4000U;
    v20 = v20 | param_3->w4c;
    v14 = param_3->w54;
    switch (param_2) {
    case 0:
        v1c = v1c & ~0x20000U;
        v1c = v1c | (param_3->w30 << 1);
        break;
    case 1:
        v1c = v1c & ~0x40000U;
        v1c = v1c | (param_3->w30 << 2);
        break;
    case 2:
        v1c = v1c & ~0x80000U;
        v1c = v1c | (param_3->w30 << 3);
        break;
    case 3:
        v1c = v1c & ~0x100000U;
        v1c = v1c | (param_3->w30 << 4);
        break;
    case 4:
        v1c = v1c & ~0x200000U;
        v1c = v1c | (param_3->w30 << 5);
        break;
    case 5:
        v1c = v1c & ~0x400000U;
        v1c = v1c | (param_3->w30 << 6);
        break;
    default:
        break;
    }
    ((ControlBlock *)*param_1)->row[param_2].value = v24;
    ((DataBlock *)*param_1)->row[param_2].e8 = v18;
    ((DataBlock *)*param_1)->row[param_2].e4 = v20;
    ((DataBlock *)*param_1)->row[param_2].d4 = v14;
    ((Bank *)(void *)(*param_1))->ctl = v1c;
    return;
}
