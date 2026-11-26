#include <stdint.h>

typedef struct {
    uint32_t a;     /* 0x00 */
    uint32_t b;     /* 0x04 */
    uint32_t c;     /* 0x08 */
    uint32_t cur;   /* 0x0c */
    uint32_t req;   /* 0x10 */
    uint32_t r14;   /* 0x14 */
    uint32_t r18;   /* 0x18 */
    uint32_t r1c;   /* 0x1c */
} HW;

typedef struct {
    HW *hw;             /* 0x00 */
    uint8_t pad[0x18];  /* 0x04 */
    uint8_t flag;       /* 0x1c */
} Dev;

void FUN_08009688(Dev *);
void FUN_08009674(Dev *);
void FUN_0800969c(Dev *);
void FUN_080021d0(Dev *);
void FUN_0800996c(Dev *);
void FUN_08009980(Dev *);
void FUN_080096b0(Dev *);
void FUN_08009958(Dev *);
void FUN_08009994(Dev *);
void FUN_080099a8(Dev *);
void FUN_080099bc(Dev *);
void FUN_080099d0(Dev *);

void FUN_080093d6(Dev *param_1)
{
    uint32_t cur = param_1->hw->cur;
    uint32_t req = param_1->hw->req;

    if (((req & 2u) != 0) && ((cur & 2u) != 0)) {
        param_1->hw->req = 0xfffffffd;
        param_1->flag = 1;
        if ((param_1->hw->r18 & 3u) != 0) {
            FUN_08009688(param_1);
        } else {
            FUN_08009674(param_1);
            FUN_0800969c(param_1);
        }
        param_1->flag = 0;
    }
    if (((req & 4u) != 0) && ((cur & 4u) != 0)) {
        param_1->hw->req = 0xfffffffb;
        param_1->flag = 2;
        if ((param_1->hw->r18 & 0x300u) != 0) {
            FUN_08009688(param_1);
        } else {
            FUN_08009674(param_1);
            FUN_0800969c(param_1);
        }
        param_1->flag = 0;
    }
    if (((req & 8u) != 0) && ((cur & 8u) != 0)) {
        param_1->hw->req = 0xfffffff7;
        param_1->flag = 4;
        if ((param_1->hw->r1c & 3u) != 0) {
            FUN_08009688(param_1);
        } else {
            FUN_08009674(param_1);
            FUN_0800969c(param_1);
        }
        param_1->flag = 0;
    }
    if (((req & 0x10u) != 0) && ((cur & 0x10u) != 0)) {
        param_1->hw->req = 0xffffffef;
        param_1->flag = 8;
        if ((param_1->hw->r1c & 0x300u) != 0) {
            FUN_08009688(param_1);
        } else {
            FUN_08009674(param_1);
            FUN_0800969c(param_1);
        }
        param_1->flag = 0;
    }
    if (((req & 1u) != 0) && ((cur & 1u) != 0)) {
        param_1->hw->req = 0xfffffffe;
        FUN_080021d0(param_1);
    }
    if ((((req & 0x80u) != 0) || ((req & 0x2000u) != 0)) && ((cur & 0x80u) != 0)) {
        param_1->hw->req = 0xffffdf7f;
        FUN_0800996c(param_1);
    }
    if (((req & 0x100u) != 0) && ((cur & 0x80u) != 0)) {
        param_1->hw->req = 0xfffffeff;
        FUN_08009980(param_1);
    }
    if (((req & 0x40u) != 0) && ((cur & 0x40u) != 0)) {
        param_1->hw->req = 0xffffffbf;
        FUN_080096b0(param_1);
    }
    if (((req & 0x20u) != 0) && ((cur & 0x20u) != 0)) {
        param_1->hw->req = 0xffffffdf;
        FUN_08009958(param_1);
    }
    if (((req & 0x100000u) != 0) && ((cur & 0x100000u) != 0)) {
        param_1->hw->req = 0xffefffff;
        FUN_08009994(param_1);
    }
    if (((req & 0x200000u) != 0) && ((cur & 0x200000u) != 0)) {
        param_1->hw->req = 0xffdfffff;
        FUN_080099a8(param_1);
    }
    if (((req & 0x400000u) != 0) && ((cur & 0x400000u) != 0)) {
        param_1->hw->req = 0xffbfffff;
        FUN_080099bc(param_1);
    }
    if (((req & 0x800000u) != 0) && ((cur & 0x800000u) != 0)) {
        param_1->hw->req = 0xff7fffff;
        FUN_080099d0(param_1);
    }
}
