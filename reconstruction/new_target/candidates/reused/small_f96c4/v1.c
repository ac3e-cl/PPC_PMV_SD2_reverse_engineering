/* FUN_080096c4: patch dev control register from arg config block, gated by
 * dev being one of the known ADC/DAC/HRTIM-style peripheral bases.
 * 360-byte section: 322-byte body + 2B nop pad + 9-word literal pool. */
#include <stdint.h>

typedef struct {
    volatile uint32_t cr;    /* +0x00 */
    uint32_t pad0[3];
    volatile uint32_t o10;   /* +0x10 */
    volatile uint32_t o14;   /* +0x14 */
    uint32_t pad1[4];
    volatile uint32_t o28;   /* +0x28 */
    volatile uint32_t o2c;   /* +0x2c */
    volatile uint32_t o30;   /* +0x30 */
} dev_t;

typedef struct {
    uint32_t o00;
    uint32_t o04;
    uint32_t o08;
    uint32_t o0c;
    uint32_t o10;
    uint32_t o14;
} arg_t;

void FUN_080096c4(dev_t *param_1, arg_t *param_2)
{
    uint32_t local_c;

    local_c = param_1->cr;
    if (param_1 == (dev_t *)0x40012C00u || param_1 == (dev_t *)0x40000000u ||
        param_1 == (dev_t *)0x40000400u || param_1 == (dev_t *)0x40000800u ||
        param_1 == (dev_t *)0x40000C00u || param_1 == (dev_t *)0x40013400u ||
        param_1 == (dev_t *)0x40015000u) {
        local_c &= ~0x70u;
        local_c |= param_2->o04;
    }
    if (param_1 == (dev_t *)0x40012C00u || param_1 == (dev_t *)0x40000000u ||
        param_1 == (dev_t *)0x40000400u || param_1 == (dev_t *)0x40000800u ||
        param_1 == (dev_t *)0x40000C00u || param_1 == (dev_t *)0x40013400u ||
        param_1 == (dev_t *)0x40014000u || param_1 == (dev_t *)0x40014400u ||
        param_1 == (dev_t *)0x40014800u || param_1 == (dev_t *)0x40015000u) {
        local_c &= ~0x300u;
        local_c |= param_2->o0c;
    }
    local_c = (local_c & ~0x80u) | param_2->o14;
    param_1->cr = local_c;
    param_1->o2c = param_2->o08;
    param_1->o28 = param_2->o00;
    if (param_1 == (dev_t *)0x40012C00u || param_1 == (dev_t *)0x40013400u ||
        param_1 == (dev_t *)0x40014000u || param_1 == (dev_t *)0x40014400u ||
        param_1 == (dev_t *)0x40014800u || param_1 == (dev_t *)0x40015000u) {
        param_1->o30 = param_2->o10;
    }
    param_1->o14 = 1u;
    if ((param_1->o10 & 1u) == 1u) {
        param_1->o10 &= ~1u;
    }
}
