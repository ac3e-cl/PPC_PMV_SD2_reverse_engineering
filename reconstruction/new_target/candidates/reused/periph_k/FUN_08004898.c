#include <stdint.h>

typedef struct {
    volatile uint32_t reg0;
    volatile uint32_t reg4;
    volatile uint32_t reg8;
} Inst;

typedef struct {
    Inst *inst;
    volatile uint8_t reserved[0x58];
    volatile uint32_t status;   /* 0x5c */
    volatile uint32_t control;  /* 0x60 */
} Handle;

extern uint32_t FUN_08002a18(void);
extern void FUN_08002e58(Inst *in);
extern int FUN_08002e80(Inst *in);
extern int FUN_08002ea6(Inst *in);

int FUN_08004898(Handle *h)
{
    uint32_t tickstart;
    int err = FUN_08002ea6(h->inst);
    if (FUN_08002e80(h->inst) != 0 && err == 0) {
        if ((h->inst->reg8 & 0xDu) == 1u) {
            FUN_08002e58(h->inst);
            h->inst->reg0 = 3u;
            tickstart = FUN_08002a18();
        } else {
            h->status |= 0x10u;
            h->control |= 1u;
            return 1;
        }
        while ((h->inst->reg8 & 1u) != 0u) {
            if ((FUN_08002a18() - tickstart) > 2u) {
                if ((h->inst->reg8 & 1u) != 0u) {
                    h->status |= 0x10u;
                    h->control |= 1u;
                    return 1;
                }
            }
        }
    }
    return 0;
}
