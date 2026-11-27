/* FUN_08003538: SPI-like handle suspend/reconfigure, reconstructed from
 * disassembly at 0x08003538 (body 08003538-08003797 + literal pool
 * 08003798-080037ab + cold tail 080037ac-080037e5). */
#include <stdint.h>

/* Peripheral register view. */
typedef struct {
    volatile uint32_t cr1;  /* 0x00 */
    volatile uint32_t cr2;  /* 0x04 */
    volatile uint32_t r08;  /* 0x08 */
    volatile uint32_t sr;   /* 0x0c */
} spi_t;

/* RAM handle; base is a pointer member so the reload-per-access -O0 shapes
 * (each access re-reads h->base) match the firmware. */
typedef struct {
    spi_t *base;               /* 0x00 */
    uint32_t r04;              /* 0x04 */
    uint32_t r08;              /* 0x08 */
    uint32_t r0c;              /* 0x0c */
    uint32_t r10;              /* 0x10 */
    uint32_t r14;              /* 0x14 */
    uint32_t mode;             /* 0x18 */
    uint32_t r1c[8];           /* 0x1c - 0x38 */
    uint32_t r3c;              /* 0x3c */
    uint32_t r40[6];           /* 0x40 - 0x54 */
    uint8_t busy;              /* 0x58 */
    uint8_t pad59[3];
    uint32_t ctrl;             /* 0x5c */
    uint32_t crcl;             /* 0x60 */
} spi_handle;

extern uint32_t FUN_08002d5c(uint32_t base);
extern uint32_t FUN_08002f1c(uint32_t base);
extern uint8_t FUN_0800476c(spi_handle *h);
extern void FUN_08002ecc(uint32_t base);

uint8_t FUN_08003538(spi_handle *h)
{
    uint8_t ret;
    uint32_t st;
    spi_t *mapped;

    st = FUN_08002d5c((uintptr_t)h->base == 0x50000000UL || (uintptr_t)h->base == 0x50000100UL
                          ? 0x50000300UL
                          : 0x50000700UL);
    if (FUN_08002f1c((uintptr_t)h->base) == 0) {
        if (h->busy == 1) {
            return 2;
        }
        h->busy = 1;
        ret = FUN_0800476c(h);
        if (ret == 0) {
            h->ctrl = (h->ctrl & 0xfffff0feUL) | 0x100UL;
            if (((uintptr_t)h->base == 0x50000100UL
                     ? 0x50000000UL
                     : ((uintptr_t)h->base == 0x50000500UL ? 0x50000400UL
                                                           : (uintptr_t)h->base)) == (uintptr_t)h->base ||
                st == 0) {
                h->ctrl &= 0xffefffffUL;
            }
            if ((h->ctrl & 0x1000UL) != 0) {
                h->crcl = h->crcl & 0xfffffff9UL;
            } else {
                h->crcl = 0;
            }
            h->base->cr1 = 0x1cUL;
            h->busy = 0;
            h->base->cr2 = h->base->cr2 & 0xffffffe3UL;
            switch (h->mode) {
            case 8u:
                h->base->cr2 = h->base->cr2 | 8UL;
                break;
            default:
                h->base->cr2 = h->base->cr2 | 4UL;
                break;
            }
            if (h->r3c == 0) {
                h->base->cr2 = h->base->cr2 | 0x10UL;
            }
            if (((uintptr_t)h->base == 0x50000100UL
                     ? 0x50000000UL
                     : ((uintptr_t)h->base == 0x50000500UL ? 0x50000400UL
                                                           : (uintptr_t)h->base)) == (uintptr_t)h->base ||
                st == 0 || st == 5 || st == 9) {
                if ((h->base->sr & 0x2000000UL) != 0) {
                    h->ctrl = (h->ctrl & 0xffffcfffUL) | 0x1000UL;
                    switch (h->mode) {
                    case 8u:
                        h->base->cr2 = h->base->cr2 & 0xffffffdfUL;
                        h->base->cr2 = h->base->cr2 | 0x40UL;
                        break;
                    default:
                        h->base->cr2 = h->base->cr2 & 0xffffffbfUL;
                        h->base->cr2 = h->base->cr2 | 0x20UL;
                        break;
                    }
                }
                FUN_08002ecc((uintptr_t)h->base);
            } else {
                h->ctrl |= 0x100000UL;
                mapped = (uintptr_t)h->base == 0x50000100UL
                             ? (spi_t *)0x50000000UL
                             : ((uintptr_t)h->base == 0x50000500UL
                                    ? (spi_t *)0x50000400UL
                                    : h->base);
                if ((mapped->sr & 0x2000000UL) != 0) {
                    h->ctrl = (h->ctrl & 0xffffcfffUL) | 0x1000UL;
                    switch (h->mode) {
                    case 8u:
                        h->base->cr2 = h->base->cr2 & 0xffffffdfUL;
                        h->base->cr2 = h->base->cr2 | 0x40UL;
                        break;
                    default:
                        h->base->cr2 = h->base->cr2 & 0xffffffbfUL;
                        h->base->cr2 = h->base->cr2 | 0x20UL;
                        break;
                    }
                }
            }
        } else {
            h->busy = 0;
        }
    } else {
        ret = 2;
    }
    return ret;
}
