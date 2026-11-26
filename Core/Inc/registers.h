#include <stdint.h>
typedef struct {
    volatile uint32_t ISR, IER, CR, CFGR, CFGR2, SMPR1, SMPR2;
    uint32_t reserved1[5];
    volatile uint32_t SQR1;
    uint32_t reserved2[6];
    volatile uint32_t JSQR;
    uint32_t reserved3[4];
    volatile uint32_t OFR[4];
    uint32_t reserved4[16];
    volatile uint32_t AWD2CR;
} Registers;

#include <stddef.h>
_Static_assert(offsetof(Registers, CR) == 0x08, "CR offset");
_Static_assert(offsetof(Registers, SQR1) == 0x30, "SQR1 offset");
_Static_assert(offsetof(Registers, JSQR) == 0x4c, "JSQR offset");
_Static_assert(offsetof(Registers, OFR) == 0x60, "OFR offset");
_Static_assert(offsetof(Registers, AWD2CR) == 0xb0, "AWD2CR offset");
