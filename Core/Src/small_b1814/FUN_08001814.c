#include <stdint.h>

typedef struct {
    uint32_t w0, w1, w2, w3;   /* 0x00-0x0c */
    uint8_t  b0, b1, b2;       /* 0x10-0x12, pad 0x13 */
    uint32_t w[11];            /* 0x14-0x3c */
} DacInitCfg;

extern volatile DacInitCfg DAC_INIT_CFG;   /* = 0x20000100 */

#define FLASH_BASE 0x40006800u             /* non-encodable imm: stays in literal pool */

extern int  FUN_08004f54(volatile DacInitCfg *);
extern void FUN_08002244(void);
extern void FUN_08005208(volatile DacInitCfg *, uint32_t *);

void FUN_08001814(void)
{
    DAC_INIT_CFG.w0 = FLASH_BASE;
    DAC_INIT_CFG.w1 = 0;
    DAC_INIT_CFG.w2 = 0;
    DAC_INIT_CFG.w3 = 0;
    DAC_INIT_CFG.b0 = 0;
    DAC_INIT_CFG.b1 = 0;
    DAC_INIT_CFG.b2 = 0;
    DAC_INIT_CFG.w[0] = 0x50;
    DAC_INIT_CFG.w[1] = 1;
    DAC_INIT_CFG.w[2] = 0xe;
    DAC_INIT_CFG.w[3] = 2;
    DAC_INIT_CFG.w[4] = 1;
    DAC_INIT_CFG.w[5] = 1;
    DAC_INIT_CFG.w[6] = 1;
    DAC_INIT_CFG.w[7] = 1;
    DAC_INIT_CFG.w[8] = 0;
    DAC_INIT_CFG.w[9] = 0;
    DAC_INIT_CFG.w[10] = 0;
    if (FUN_08004f54(&DAC_INIT_CFG) != 0)
        FUN_08002244();
    uint32_t locals[6];
    locals[0] = 0x40000000u;
    locals[1] = 0;
    locals[2] = 2;
    locals[3] = 0;
    locals[4] = 0;
    locals[5] = 0;
    FUN_08005208(&DAC_INIT_CFG, locals);
}
