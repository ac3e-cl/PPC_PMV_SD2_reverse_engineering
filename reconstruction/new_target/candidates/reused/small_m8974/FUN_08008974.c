/* FUN_08008974: system clock switch with flash-latency arbitration.
 * param_2 is the requested latency; cfg selects source/dividers. */
#include <stdint.h>

typedef struct {
    volatile uint32_t f00;
    volatile uint32_t f04;
    volatile uint32_t f08;
    volatile uint32_t f0c;
    volatile uint32_t f10;
} cfg_t;

/* 0x40022000: latency field at +0x00. */
typedef struct { volatile uint32_t f00; } lat_t;
/* 0x40021000: ready/status field at +0x00, config field at +0x08. */
typedef struct { volatile uint32_t f00; uint32_t pad04; volatile uint32_t f08; } rcc_t;

#define LAT ((lat_t *)0x40022000u)
#define RCC ((rcc_t *)0x40021000u)

extern const uint8_t CLOCK_TBL[];
extern volatile uint32_t TIMER;
extern volatile uint32_t STATE;

extern uint32_t FUN_08002a18(void);
extern uint32_t FUN_08008bec(void);
extern uint32_t FUN_08008cb0(void);
extern uint32_t FUN_08002980(uint32_t);

uint32_t FUN_08008974(cfg_t *cfg, uint32_t val)
{
    uint32_t flag;
    uint32_t u;
    uint32_t t0;
    uint32_t now;

    flag = 0;
    if (cfg == 0) {
        return 1;
    }
    if ((LAT->f00 & 0xfu) < val) {
        LAT->f00 = (LAT->f00 & ~0xfu) | val;
        if ((LAT->f00 & 0xfu) != val) {
            return 1;
        }
    }
    if ((cfg->f00 & 1u) != 0) {
        if (cfg->f04 == 3u) {
            if ((RCC->f00 & 0x2000000u) == 0) {
                return 1;
            }
            u = FUN_08008cb0();
            if (u > 0x4c4b400u &&
                ((RCC->f08 & 0xf0u) == 0 ||
                 ((cfg->f00 & 2u) != 0 && cfg->f08 == 0))) {
                RCC->f08 = (RCC->f08 & ~0xf0u) | 0x80u;
                flag = 0x80u;
            }
        } else {
            if (cfg->f04 == 2u) {
                if ((RCC->f00 & 0x20000u) == 0) {
                    return 1;
                }
            } else {
                if ((RCC->f00 & 0x400u) == 0) {
                    return 1;
                }
            }
            u = FUN_08008bec();
            if (u > 0x4c4b400u) {
                RCC->f08 = (RCC->f08 & ~0xf0u) | 0x80u;
                flag = 0x80u;
            }
        }
        RCC->f08 = (RCC->f08 & ~3u) | cfg->f04;
        t0 = FUN_08002a18();
        while ((RCC->f08 & 0xcu) != (cfg->f04 << 2)) {
            if (FUN_08002a18() - t0 >= 5001u) {
                return 3;
            }
        }
    }
    if ((cfg->f00 & 2u) != 0) {
        if ((cfg->f00 & 4u) != 0) {
            RCC->f08 = RCC->f08 | 0x700u;
        }
        if ((cfg->f00 & 8u) != 0) {
            RCC->f08 = (RCC->f08 & ~0x3f00u) | 0x700u;
        }
        RCC->f08 = (RCC->f08 & ~0xf0u) | cfg->f08;
    } else {
        if (flag == 0x80u) {
            RCC->f08 = RCC->f08 & ~0xf0u;
        }
    }
    if (val < (LAT->f00 & 0xfu)) {
        LAT->f00 = (LAT->f00 & ~0xfu) | val;
        t0 = FUN_08002a18();
        while ((LAT->f00 & 0xfu) != val) {
            if (FUN_08002a18() - t0 >= 5001u) {
                return 3;
            }
        }
    }
    if ((cfg->f00 & 4u) != 0) {
        RCC->f08 = (RCC->f08 & ~0x700u) | cfg->f0c;
    }
    if ((cfg->f00 & 8u) != 0) {
        RCC->f08 = (RCC->f08 & ~0x3800u) | (cfg->f10 << 3);
    }
    TIMER = FUN_08008bec() >> (CLOCK_TBL[(RCC->f08 >> 4) & 0xfu] & 0x1fu);
    return FUN_08002980(STATE);
}
