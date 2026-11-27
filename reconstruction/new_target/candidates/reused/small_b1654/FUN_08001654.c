/* FUN_08001654: request-block bring-up at 0x20000028 — fill config words,
 * init, query a[0], then submit the 0x10c00010-parameter block. */
#include <stdint.h>

typedef struct {
    volatile uint32_t f00;
    volatile uint32_t f04;
    volatile uint32_t f08;
    volatile uint32_t f0c;
    volatile uint32_t f10;
    volatile uint32_t f14;
    volatile uint32_t f18;
    volatile uint8_t  f1c;
    volatile uint8_t  f1d;
    volatile uint32_t f20;
    volatile uint8_t  f24;
    uint8_t           pad25[7];
    volatile uint32_t f2c;
    volatile uint32_t f30;
    uint8_t           pad34[4];
    volatile uint8_t  f38;
    volatile uint32_t f3c;
    volatile uint8_t  f40;
} cfg_t;

/* Pool-resident base: extern symbol via --defsym keeps per-statement
 * ldr r3,[pool] reloads and displacement addressing. */
extern volatile cfg_t REQ_BLOCK;

extern void FUN_080099e4(void *, uint8_t, int32_t);
extern uint32_t FUN_08002f90(volatile cfg_t *);
extern uint32_t FUN_08004b24(volatile cfg_t *, volatile uint32_t *);
extern uint32_t FUN_08003d74(volatile cfg_t *, volatile uint32_t *);
extern void FUN_08002244(void);

void FUN_08001654(void)
{
    uint32_t a[3] = {0};
    uint32_t buf[8];

    FUN_080099e4(buf, 0, 0x20);
    REQ_BLOCK.f00 = 0x50000000;
    REQ_BLOCK.f04 = 0x30000;
    REQ_BLOCK.f08 = 0;
    REQ_BLOCK.f0c = 0;
    REQ_BLOCK.f10 = 0;
    REQ_BLOCK.f14 = 0;
    REQ_BLOCK.f18 = 4;
    REQ_BLOCK.f1c = 0;
    REQ_BLOCK.f1d = 0;
    REQ_BLOCK.f20 = 1;
    REQ_BLOCK.f24 = 0;
    REQ_BLOCK.f2c = 0x6a0;
    REQ_BLOCK.f30 = 0x400;
    REQ_BLOCK.f38 = 0;
    REQ_BLOCK.f3c = 0;
    REQ_BLOCK.f40 = 0;
    if (FUN_08002f90(&REQ_BLOCK) != 0) {
        FUN_08002244();
    }
    a[0] = 0;
    if (FUN_08004b24(&REQ_BLOCK, &a[0]) != 0) {
        FUN_08002244();
    }
    buf[0] = 0x10c00010;
    buf[1] = 6;
    buf[2] = 0;
    buf[3] = 0x7f;
    buf[4] = 4;
    buf[5] = 0;
    if (FUN_08003d74(&REQ_BLOCK, buf) != 0) {
        FUN_08002244();
    }
}
