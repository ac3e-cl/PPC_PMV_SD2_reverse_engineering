/* FUN_08005794 - 614-byte candidate, GCC 13.3 -O0, exact byte match target. */
#include <stdint.h>

typedef struct { uint32_t w[0x39]; } Reg;   /* regs at 0x50,0x54,0xd4,0xd8,0xdc,0xe0 */
typedef struct { Reg *reg; uint32_t pad[0x17]; uint32_t w60; } Dev;

extern void FUN_08005a8e(Dev *d);
extern void FUN_08005a50(Dev *d, uint32_t v);
extern void FUN_080059fa(Dev *d, uint32_t v);
extern void FUN_08001fbc(Dev *d, uint32_t v);
extern void FUN_08005a10(Dev *d, uint32_t v);
extern void FUN_08005a26(Dev *d);
extern void FUN_08005a3a(Dev *d, uint32_t v);
extern void FUN_08005a66(Dev *d);
extern void FUN_08005a7a(Dev *d);
extern void FUN_08005ab6(Dev *d, uint32_t v);
extern void FUN_08005aa2(Dev *d);

void FUN_08005794(Dev *param)
{
    uint32_t m1, m2, m3, m4, m5, r54, r50, t8, t7;

    m1 = param->reg->w[0x14] & 0x1c00u;
    m1 = param->reg->w[0x15] & m1;
    m2 = param->reg->w[0x14] & 7u;
    m2 = param->reg->w[0x15] & m2;
    m3 = param->reg->w[0x14] & 0x38u;
    m3 = param->reg->w[0x15] & m3;
    m4 = param->reg->w[0x14] & 0xf10000u;
    m4 = param->reg->w[0x15] & m4;
    m5 = param->reg->w[0x14] & 0xe0000u;
    m5 = param->reg->w[0x15] & m5;
    r54 = param->reg->w[0x15];
    r50 = param->reg->w[0x14];

    if ((((r50 >> 6) & 1u) != 0u) && (((r54 >> 6) & 1u) != 0u)) {
        param->reg->w[0x14] = 0x40u;
        FUN_08005a8e(param);
    }
    if ((((r50 >> 8) & 1u) != 0u) && (((r54 >> 8) & 1u) != 0u)) {
        t8 = param->reg->w[0x36];
        t8 = param->reg->w[0x38] & t8;
        param->reg->w[0x14] = 0x100u;
        FUN_08005a50(param, t8);
    }
    if (m1 != 0u) {
        param->reg->w[0x14] = m1;
        FUN_080059fa(param, m1);
    }
    if (m2 != 0u) {
        param->reg->w[0x14] = m2;
        FUN_08001fbc(param, m2);
    }
    if (m3 != 0u) {
        param->reg->w[0x14] = m3;
        FUN_08005a10(param, m3);
    }
    if ((((r50 >> 9) & 1u) != 0u) && (((r54 >> 9) & 1u) != 0u)) {
        param->reg->w[0x14] = 0x200u;
        FUN_08005a26(param);
    }
    if ((((r50 >> 7) & 1u) != 0u) && (((r54 >> 7) & 1u) != 0u)) {
        t7 = param->reg->w[0x35];
        t7 = param->reg->w[0x37] & t7;
        param->reg->w[0x14] = 0x80u;
        FUN_08005a3a(param, t7);
    }
    if ((((r50 >> 0xd) & 1u) != 0u) && (((r54 >> 0xd) & 1u) != 0u)) {
        param->reg->w[0x14] = 0x2000u;
        FUN_08005a66(param);
    }
    if ((((r50 >> 0xf) & 1u) != 0u) && (((r54 >> 0xf) & 1u) != 0u)) {
        param->reg->w[0x14] = 0x8000u;
        FUN_08005a7a(param);
    }
    if ((((r50 >> 0xe) & 1u) != 0u) && (((r54 >> 0xe) & 1u) != 0u)) {
        param->reg->w[0x14] = 0x4000u;
        param->w60 = param->w60 | 0x80u;
    }
    if (m5 != 0u) {
        param->reg->w[0x14] = m5;
        FUN_08005ab6(param, m5);
    }
    if (m4 != 0u) {
        param->reg->w[0x14] = m4;
        param->w60 = param->w60 | m4;
    }
    if (param->w60 != 0u) {
        FUN_08005aa2(param);
    }
}
