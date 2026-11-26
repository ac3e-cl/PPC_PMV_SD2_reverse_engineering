#include <stdint.h>

extern void FUN_080099e4(void *, uint8_t, int32_t);
extern uint32_t FUN_080081e8(int32_t);
extern uint32_t FUN_08008350(uint32_t *);
extern uint32_t FUN_08008974(uint32_t *, uint32_t);
extern void FUN_08002244(void);

/* Boot config init (0x080015c0): clear+fill the 14-word request struct,
 * start the engine, submit it, then re-submit a trimmed variant.
 * Any nonzero return from either submit halts via FUN_08002244. */
void FUN_080015c0(void)
{
    uint32_t cfg[14];
    FUN_080099e4(cfg, 0, 0x38);
    uint32_t req[5] = {0};
    FUN_080081e8(0);
    cfg[0] = 1;
    cfg[1] = 0x10000;
    cfg[7] = 2;
    cfg[8] = 3;
    cfg[9] = 6;
    cfg[10] = 0x55;
    cfg[11] = 2;
    cfg[12] = 2;
    cfg[13] = 2;
    if (FUN_08008350(cfg) != 0) {
        FUN_08002244();
    }
    req[0] = 0xf;
    req[1] = 3;
    req[2] = 0;
    req[3] = 0;
    req[4] = 0;
    if (FUN_08008974(req, 4) != 0) {
        FUN_08002244();
    }
}
