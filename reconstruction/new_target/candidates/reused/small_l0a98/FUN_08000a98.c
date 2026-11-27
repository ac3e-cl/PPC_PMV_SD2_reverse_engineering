/* FUN_08000a98 — main state-machine task, byte-match candidate (v2). */
#include <stdint.h>

extern void FUN_0800294e(void);
extern void FUN_080015c0(void);
extern void FUN_08001e6c(void);
extern void FUN_08001748(void);
extern void FUN_080018cc(void);
extern void FUN_08001814(void);
extern void FUN_08001654(void);
extern void FUN_08001df8(uint32_t);
extern void FUN_08002a30(uint32_t);
extern void FUN_08006ac8(void *, uint32_t, uint32_t);
extern void FUN_080049fc(void *, uint32_t);
extern void FUN_080052bc(void *);
extern void FUN_080055c8(void *, uint32_t, uint32_t);
extern void FUN_080020b4(void);
extern void FUN_0800215c(uint32_t);
extern void FUN_08005fa0(void *, uint32_t, uint32_t);
extern void FUN_08005fd0(void *, uint32_t);
extern void FUN_08009288(void *);
extern void FUN_08009378(void *);
extern void FUN_08003308(void *);
extern uint32_t FUN_0800385e(void *);
extern void FUN_080034d0(void *);
extern void FUN_080037e8(void *);
extern void FUN_08001ff0(void);
extern uint64_t FUN_080004bc(uint32_t);
extern uint64_t FUN_080004e0(uint32_t);
extern uint64_t FUN_08000590(uint64_t, uint64_t);
extern uint64_t FUN_08000224(int64_t, uint64_t);
extern uint64_t FUN_08000220(int64_t, uint64_t);
extern uint64_t FUN_080007e4(uint64_t, uint64_t);
extern uint32_t FUN_080009f4(int64_t);
extern uint32_t FUN_080009b4(int64_t);

/* Absolute-address RAM globals as extern symbols (defsym'd in the harness):
 * matches firmware store ordering — the pool base materializes AT the store
 * insn (after the value), not before the call chain. Cast-pointer macros
 * gimplify the address into an earlier SSA temp and reorders codegen. */
extern uint8_t ST;                      /* 0x20000324 */
extern uint32_t MSG;                    /* 0x2000032c */
extern uint8_t Q[8];                    /* 0x200002c8 */
extern uint32_t OUT;                    /* 0x20000330 */
extern uint8_t F0[8];                   /* 0x200002d0 */
extern uint8_t FLAG;                    /* 0x2000033e */
extern uint16_t SHI, SLO;               /* 0x334, 0x336 */
extern uint16_t SW1, SW2, SW3;          /* 0x33a, 0x33c, 0x338 */
extern uint16_t PW1, PW2, PW3, PW4, PW5;/* 0x2b2, 0x2b4, 0x2ae, 0x2b0, 0x2ac */
typedef union { float f; uint32_t u; } FWord;   /* one symbol/address = one pool word */
extern FWord FW1, FW2, FW3, FW4;
#define SH16(i, j) ((unsigned short)(short)(((short)Q[i] << 8) | (short)Q[j]))

void FUN_08000a98(void)
{
    unsigned short loop = 0;
    unsigned short delta = 0;

    FUN_0800294e();
    FUN_080015c0();
    FUN_08001e6c();
    FUN_08001748();
    FUN_080018cc();
    FUN_08001814();
    FUN_08001654();
    FUN_08001df8(0x69a);
    FUN_08002a30(10);
    FUN_08006ac8((void *)0x20000164u, 0x20, 1);
    FUN_080049fc((void *)0x20000028u, 0x7f);
    FUN_080049fc((void *)0x20000094u, 0x7f);
    FUN_08002a30(1);
    FUN_080052bc((void *)0x20000100u);
    FUN_080055c8((void *)0x20000100u, 7, 0);
    for (;;) {
        switch (ST) {
        case 0:
            FUN_080020b4();
            ST = 1;
            break;
        case 1:
            if (MSG == 0x68009u && Q[0] == 12) {
                OUT = 0x60012u;
                F0[0] = 1;
                F0[1] = 0;
                F0[2] = 0;
                FUN_0800215c(3);
                ST = 2;
            }
            break;
        case 2:
            if (MSG == 0x68009u && Q[0] == 1) {
                FUN_08005fa0((void *)0x48000000u, 0x1000, 1);
                ST = 3;
            }
            break;
        case 3:
            if (MSG == 0x68009u && Q[0] == 11) {
                OUT = 0x60012u;
                F0[0] = 1;
                F0[1] = 3;
                F0[2] = 0;
                FUN_0800215c(3);
                ST = 4;
            }
            break;
        case 4:
            if (MSG == 0x68009u && Q[0] == 3) {
                OUT = 0x60011u;
                F0[0] = 0x94;
                F0[1] = 0x11;
                F0[2] = 100;
                F0[3] = 0;
                F0[4] = 0;
                F0[5] = 0;
                F0[6] = 0;
                F0[7] = 0;
                FUN_0800215c(8);
                OUT = 0x60012u;
                F0[0] = 1;
                F0[1] = 7;
                F0[2] = 0;
                FUN_0800215c(3);
                FLAG = 1;
                FUN_08009288((void *)0x20000260u);
                SHI = 0;
                SLO = 0;
                ST = 5;
            }
            break;
        case 5:
            if (MSG == 0x68009u && Q[0] == 4) {
                ST = 6;
            }
            break;
        case 6:
            if (MSG == 0x68002u) {
                SW1 = SH16(1, 0);
                SHI = SW1;
                SLO = 0;
                ST = 7;
            }
            break;
        case 7:
            if (MSG == 0x68002u && (SW1 = SH16(1, 0), SW1 == 0)) {
                SHI = SW1;
                ST = 8;
            }
            break;
        case 8:
            if (MSG == 0x68005u) {
                SW1 = SH16(1, 0);
                SW2 = SH16(3, 2);
                if (SW1 == 0 && SW2 == 0) {
                    ST = 9;
                }
            }
            break;
        case 9:
            if (MSG == 0x68009u && Q[0] == 5) {
                ST = 10;
            }
            break;
        case 10:
            if (MSG == 0x68003u) {
                SW1 = SH16(1, 0);
                SW3 = (unsigned short)FUN_080009b4((int64_t)FUN_08000224((int64_t)FUN_08000590(FUN_080004bc(SW1),
                        0x3FD48438088509C0ULL), 0x4025BBE76C8B4396ULL));
                ST = 11;
            }
            break;
        case 11:
            FUN_08005fa0((void *)0x48000400u, 0x10, 1);
            FUN_08003308((void *)0x20000094u);
            PW1 = (unsigned short)FUN_0800385e((void *)0x20000094u);
            FUN_080034d0((void *)0x20000094u);
            FW1.f = (float)PW1;
            FW1.u = FUN_080009f4((int64_t)FUN_080007e4(FUN_080004bc(PW1 * 10 - 109), 0x400999999999999AULL));
            SHI = (unsigned short)(unsigned int)FW1.f;
            if (PW1 >= SW3) {
                FUN_08005fa0((void *)0x48000400u, 0x10, 0);
                ST = 12;
            }
            break;
        case 12:
            if (MSG == 0x68009u && Q[0] == 7) {
                MSG = 0;
                ST = 13;
            }
            break;
        case 13:
            if (MSG == 0x68005u) {
                MSG = 0;
                SW1 = SH16(1, 0);
                SW2 = SH16(3, 2);
                SHI = SW1;
                SLO = SW2;
                FW2.f = (float)SW1;
                FW2.u = FUN_080009f4((int64_t)FUN_08000224((int64_t)FUN_08000590(FUN_080004e0(FW2.u),
                        0x3FD47AE147AE147BULL), 0x4025CCCCCCCCCCCDULL));
                FW3.f = (float)SW2;
                FW3.u = FUN_080009f4((int64_t)FUN_08000224((int64_t)FUN_08000590(FUN_080004e0(FW3.u),
                        0x402399999999999AULL), 0x4079980000000000ULL));
                PW2 = (unsigned short)(unsigned int)FW2.f;
                PW3 = (unsigned short)(unsigned int)FW3.f;
                if (PW2 > 1293u) {
                    PW2 = 1293u;
                }
                if (PW3 > 1392u) {
                    PW3 = 1392u;
                }
                delta = FUN_080009b4((int64_t)FUN_08000590(FUN_080004bc(PW3 - 410),
                        0x3FB999999999999AULL));
                PW4 = 410;
                FUN_08001ff0();
                for (loop = 0; loop < 10; loop++) {
                    PW4 = (unsigned short)(PW4 + delta);
                    FUN_08002a30(1);
                }
                PW4 = PW3;
                ST = 14;
            }
            break;
        case 14:
            if (MSG == 0x68005u) {
                MSG = 0;
                SW1 = SH16(1, 0);
                SW2 = SH16(3, 2);
                FW2.f = (float)SW1;
                FW2.u = FUN_080009f4((int64_t)FUN_08000224((int64_t)FUN_08000590(FUN_080004e0(FW2.u),
                        0x3FD47AE147AE147BULL), 0x4025CCCCCCCCCCCDULL));
                FW3.f = (float)SW2;
                FW3.u = FUN_080009f4((int64_t)FUN_08000224((int64_t)FUN_08000590(FUN_080004e0(FW3.u),
                        0x402399999999999AULL), 0x4079980000000000ULL));
                PW2 = (unsigned short)(unsigned int)FW2.f;
                PW4 = (unsigned short)(unsigned int)FW3.f;
                if (PW2 > 1293u) {
                    PW2 = 1293u;
                }
                if (PW4 > 1392u) {
                    PW4 = 1392u;
                }
                FW4.f = (float)PW5;
                FW1.f = (float)PW1;
                FW4.u = FUN_080009f4((int64_t)FUN_08000220((int64_t)FUN_08000590(FUN_080004e0(FW4.u),
                        0x3FB999999999999AULL), 0x4044D9999999999AULL));
                FW1.u = FUN_080009f4((int64_t)FUN_08000220((int64_t)FUN_08000590(FUN_080004e0(FW1.u),
                        0x4008CCCCCCCCCCCDULL), 0x40410CCCCCCCCCCDULL));
                SHI = (unsigned short)(unsigned int)FW1.f;
                SLO = (unsigned short)(unsigned int)FW4.f;
            }
            if (MSG == 0x68009u && Q[0] == 7) {
                MSG = 0;
                FUN_08005fd0((void *)0x48000000u, 0x1000);
            }
            if (MSG == 0x68006u) {
                MSG = 0;
                ST = 15;
                break;
            }
            if (MSG == 0x68004u && Q[0] == 0) {
                MSG = 0;
                ST = 16;
            }
            if (SHI > 0x1194u) {
                ST = 15;
                break;
            }
            if (SW1 <= 0x9c3u) {
                ST = 15;
                break;
            }
            if (SLO > 250u) {
                ST = 15;
                break;
            }
            break;
        case 15:
            FUN_080020b4();
            FUN_08005fa0((void *)0x48000000u, 0x1000, 0);
            if (Q[0] == 1) {
                FUN_08005fa0((void *)0x48000000u, 0x8000, 1);
            }
            if (Q[0] == 3) {
                FUN_08005fa0((void *)0x48000000u, 0x8000, 1);
                FUN_08005fa0((void *)0x48000000u, 0x1000, 1);
            }
            FLAG = 0;
            FUN_08009378((void *)0x20000260u);
            FUN_080037e8((void *)0x20000028u);
            FUN_080037e8((void *)0x20000094u);
            while (1) {
                continue;
            }
        case 16:
            FUN_080020b4();
            FUN_08005fa0((void *)0x48000000u, 0x1000, 0);
            FUN_08005fa0((void *)0x48000000u, 0x8000, 0);
            FLAG = 0;
            FUN_08009378((void *)0x20000260u);
            FUN_080037e8((void *)0x20000028u);
            FUN_080037e8((void *)0x20000094u);
            while (1) {
                FUN_08005fd0((void *)0x48000000u, 0x1000);
                FUN_08005fd0((void *)0x48000000u, 0x8000);
                FUN_08002a30(1000);
                continue;
            }
            break;
        default:
            break;
        }
    }
}
