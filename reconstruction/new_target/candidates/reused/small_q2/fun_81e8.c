/* FUN_080081e8: PWR2 mode request: 0 = drop+wait, 0x200 = set+wait,
 * other = force 0x400. Timeout = (u64)0x431bde83*(w[0x20000000]*50)>>50+1. */
#include <stdint.h>

typedef struct {
    volatile uint32_t CR0;   /* +0x00 */
    uint32_t pad04[4];
    volatile uint32_t SR;    /* +0x14 */
    uint32_t pad18[26];
    volatile uint32_t CR1;   /* +0x80 */
} PWR2_Type;

#define PWR2 ((PWR2_Type *)0x40007000u)

/* extern symbol, defsym'd to 0x20000000: forces pool ldr (a literal cast
 * would fold to mov.w and drop the pool word). */
extern volatile uint32_t REG;

uint32_t FUN_080081e8(int param_1)
{
    int local_c;

    if (param_1 == 0) {
        if ((PWR2->CR0 & 0x600u) == 0x400u) {
            PWR2->CR1 = PWR2->CR1 & ~0x100u;
            PWR2->CR0 = (PWR2->CR0 & ~0x600u) | 0x200u;
            for (local_c = (int)(REG * 50u / 1000000u) + 1;
                 (PWR2->SR & 0x400u) == 0x400u && local_c != 0; local_c--) {
            }
            if ((PWR2->SR & 0x400u) == 0x400u) {
                return 3;
            }
        } else {
            PWR2->CR1 = PWR2->CR1 & ~0x100u;
        }
    } else if (param_1 == 0x200) {
        if ((PWR2->CR0 & 0x600u) == 0x400u) {
            PWR2->CR1 = PWR2->CR1 | 0x100u;
            PWR2->CR0 = (PWR2->CR0 & ~0x600u) | 0x200u;
            for (local_c = (int)(REG * 50u / 1000000u) + 1;
                 (PWR2->SR & 0x400u) == 0x400u && local_c != 0; local_c--) {
            }
            if ((PWR2->SR & 0x400u) == 0x400u) {
                return 3;
            }
        } else {
            PWR2->CR1 = PWR2->CR1 | 0x100u;
        }
    } else {
        PWR2->CR0 = (PWR2->CR0 & ~0x600u) | 0x400u;
    }
    return 0;
}
