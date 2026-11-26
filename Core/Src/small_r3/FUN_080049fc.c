/* FUN_080049fc: guarded ADC single conversion start + completion poll with timeout. */
#include <stdint.h>

typedef struct {
    uint32_t Instance;
    uint8_t pad[0x54];
    uint8_t ready;   /* busy flag at byte 0x58 */
    uint32_t status; /* SR word at 0x5c */
} AdcHandle;

extern char FUN_08004898(AdcHandle *);
extern void FUN_0800497c(uint32_t, uint32_t);
extern uint32_t FUN_080049ae(uint32_t);

char FUN_080049fc(AdcHandle *param_1, uint32_t param_2)
{
    char cVar1;
    volatile uint32_t i = 0u;

    if (param_1->ready == 1) {
        return 2;
    }
    param_1->ready = 1;
    cVar1 = FUN_08004898(param_1);
    if (cVar1 == 0) {
        param_1->status = (param_1->status & 0xffffeefd) | 2;
        FUN_0800497c(param_1->Instance, param_2);
        while (FUN_080049ae(param_1->Instance) != 0) {
            i = i + 1;
            if (i > 0x4de01u) {
                param_1->status = (param_1->status & 0xffffffed) | 0x10;
                param_1->ready = 0;
                return 1;
            }
        }
        param_1->status = (param_1->status & 0xfffffffc) | 1;
    } else {
        param_1->status = param_1->status | 0x10;
    }
    param_1->ready = 0;
    return cVar1;
}
