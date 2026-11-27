/* FUN_08008d3c: SD2 mux request driver (RCC/PWR bit-bang with tick timeouts).
 * param: flags word + 20 field values; returns 0 on success, 3 on timeout.
 */
#include <stdint.h>

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t ICSCR;
    volatile uint32_t CFGR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t r0[18];
    volatile uint32_t AHB3ENR;
    volatile uint32_t r2[11];
    volatile uint32_t SEL0;
    volatile uint32_t SEL1;
    volatile uint32_t MODE;
    volatile uint32_t r3[2];
    volatile uint32_t DAC;
} RCC_TypeDef;
#define RCC ((RCC_TypeDef *)0x40021000u)

typedef struct { volatile uint32_t CR; } PWR_TypeDef;
#define PWR ((PWR_TypeDef *)0x40007000u)

typedef struct {
    uint32_t flags;
    uint32_t field[20]; /* field[i] -> request word i+1 */
} Request;

extern uint32_t FUN_08002a18(void);

char FUN_08008d3c(Request *param_1)
{
    uint32_t chan;
    uint32_t t0;
    volatile uint32_t rd;
    char status;
    char result;
    char unlock;

    status = 0;
    result = 0;
    if ((param_1->flags & 0x80000u) != 0u) {
        unlock = 0;
        if ((RCC->AHB3ENR & 0x10000000u) == 0u) {
            RCC->AHB3ENR |= 0x10000000u;
            rd = RCC->AHB3ENR & 0x10000000u; /* ST-style dummy readback */
            unlock = (rd, 1u);
        }
        PWR->CR |= 0x100u;
        t0 = FUN_08002a18();
        while ((PWR->CR & 0x100u) == 0u) {
            if (FUN_08002a18() - t0 > 2u) {
                status = 3;
                break;
            }
        }
        if (status == 0) {
            chan = RCC->MODE & 0x300u;
            if ((chan != 0u) && (chan != param_1->field[19])) {
                chan = RCC->MODE & 0xfffffcffu;
                RCC->MODE |= 0x10000u;
                RCC->MODE &= 0xfffeffffu;
                RCC->MODE = chan;
            }
            if ((chan & 1u) != 0u) {
                t0 = FUN_08002a18();
                while ((RCC->MODE & 2u) == 0u) {
                    if (FUN_08002a18() - t0 > 0x1388u) {
                        status = 3;
                        break;
                    }
                }
            }
            if (status == 0) {
                RCC->MODE = (RCC->MODE & 0xfffffcffu) | param_1->field[19];
            } else {
                result = status;
            }
        } else {
            result = status;
        }
        if (unlock == 1) {
            RCC->AHB3ENR &= 0xefffffffu;
        }
    }
    if ((param_1->flags & 0x1u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xfffffffcu) | param_1->field[0];
    }
    if ((param_1->flags & 0x2u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xfffffff3u) | param_1->field[1];
    }
    if ((param_1->flags & 0x4u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xffffffcfu) | param_1->field[2];
    }
    if ((param_1->flags & 0x8u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xffffff3fu) | param_1->field[3];
    }
    if ((param_1->flags & 0x10u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xfffffcffu) | param_1->field[4];
    }
    if ((param_1->flags & 0x20u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xfffff3ffu) | param_1->field[5];
    }
    if ((param_1->flags & 0x40u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xffffcfffu) | param_1->field[6];
    }
    if ((param_1->flags & 0x80u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xffff3fffu) | param_1->field[7];
    }
    if ((param_1->flags & 0x100u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xfffcffffu) | param_1->field[8];
    }
    if ((param_1->flags & 0x20000u) != 0u) {
        RCC->DAC = (RCC->DAC & 0xfffffffcu) | param_1->field[9];
    }
    if ((param_1->flags & 0x200u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xfff3ffffu) | param_1->field[10];
    }
    if ((param_1->flags & 0x400u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xffcfffffu) | param_1->field[11];
        if (param_1->field[11] == 0x100000u) {
            RCC->PLLCFGR |= 0x100000u;
        }
    }
    if ((param_1->flags & 0x800u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xff3fffffu) | param_1->field[12];
        if (param_1->field[12] == 0x400000u) {
            RCC->PLLCFGR |= 0x100000u;
        }
    }
    if ((param_1->flags & 0x1000u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xfcffffffu) | param_1->field[13];
        if (param_1->field[13] == 0x1000000u) {
            RCC->PLLCFGR |= 0x100000u;
        }
    }
    if ((param_1->flags & 0x2000u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xf3ffffffu) | param_1->field[14];
        if (param_1->field[14] == 0x8000000u) {
            RCC->PLLCFGR |= 0x100000u;
        }
    }
    if ((param_1->flags & 0x4000u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xf3ffffffu) | param_1->field[15];
        if (param_1->field[15] == 0x8000000u) {
            RCC->PLLCFGR |= 0x100000u;
        }
    }
    if ((param_1->flags & 0x8000u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0xcfffffffu) | param_1->field[16];
        if (param_1->field[16] == 0x10000000u) {
            RCC->PLLCFGR |= 0x10000u;
        }
    }
    if ((param_1->flags & 0x10000u) != 0u) {
        RCC->SEL0 = (RCC->SEL0 & 0x3fffffffu) | param_1->field[17];
        if (param_1->field[17] == 0x40000000u) {
            RCC->PLLCFGR |= 0x10000u;
        }
    }
    if ((param_1->flags & 0x40000u) != 0u) {
        RCC->DAC = (RCC->DAC & 0xffcfffffu) | param_1->field[18];
        if (param_1->field[18] == 0x200000u) {
            RCC->PLLCFGR |= 0x100000u;
        }
    }
    return result;
}
