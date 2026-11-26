#include <stdint.h>

typedef struct {
    uint32_t f0, f1, f2, f3, f4, f5, f6, f7;
    uint32_t f8, f9, f10, f11, f12, f13;
} cfg_t;

typedef struct { volatile uint32_t r[40]; } RCC_TypeDef;
#define RCCREG ((RCC_TypeDef *)0x40021000u)
typedef struct { volatile uint32_t CR; } PWR_TypeDef;
#define PWRREG ((PWR_TypeDef *)0x40007000u)

extern volatile uint32_t VAR_B; /* 0x20000004 */

uint32_t FUN_08002980(uint32_t);
uint32_t FUN_08002a18(void);

uint32_t FUN_08008350(cfg_t *cfg)
{
    uint8_t b;
    uint32_t m, n2, t0;
    volatile uint32_t chk;

    if (cfg == 0) {
        return 1u;
    }
    if ((cfg->f0 & 1u) != 0u) {
        m = RCCREG->r[2] & 0xcu;
        n2 = RCCREG->r[3] & 3u;
        if ((m == 0xcu && n2 == 3u) || m == 8u) {
            if ((RCCREG->r[0] & 0x20000u) != 0u && cfg->f1 == 0u) {
                return 1u;
            }
        } else {
            if (cfg->f1 == 0x10000u) {
                RCCREG->r[0] |= 0x10000u;
            } else if (cfg->f1 == 0x50000u) {
                RCCREG->r[0] |= 0x40000u;
                RCCREG->r[0] |= 0x10000u;
            } else {
                RCCREG->r[0] &= ~0x10000u;
                RCCREG->r[0] &= ~0x40000u;
            }
            if (cfg->f1 != 0u) {
                t0 = FUN_08002a18();
                while ((RCCREG->r[0] & 0x20000u) == 0u) {
                    if (FUN_08002a18() - t0 > 100u) {
                        return 3u;
                    }
                }
            } else {
                t0 = FUN_08002a18();
                while ((RCCREG->r[0] & 0x20000u) != 0u) {
                    if (FUN_08002a18() - t0 > 100u) {
                        return 3u;
                    }
                }
            }
        }
    }
    if ((cfg->f0 & 2u) != 0u) {
        m = RCCREG->r[2] & 0xcu;
        n2 = RCCREG->r[3] & 3u;
        if ((m == 0xcu && n2 == 2u) || m == 4u) {
            if ((RCCREG->r[0] & 0x400u) != 0u && cfg->f3 == 0u) {
                return 1u;
            }
            RCCREG->r[1] = (RCCREG->r[1] & 0x80ffffffu) | (cfg->f4 << 0x18);
            if (FUN_08002980(VAR_B) != 0u) {
                return 1u;
            }
            (void)0;
        } else {
            if (cfg->f3 != 0u) {
                RCCREG->r[0] |= 0x100u;
                t0 = FUN_08002a18();
                while ((RCCREG->r[0] & 0x400u) == 0u) {
                    if (FUN_08002a18() - t0 > 2u) {
                        return 3u;
                    }
                }
                RCCREG->r[1] = (RCCREG->r[1] & 0x80ffffffu) | (cfg->f4 << 0x18);
            } else {
                RCCREG->r[0] &= ~0x100u;
                t0 = FUN_08002a18();
                while ((RCCREG->r[0] & 0x400u) != 0u) {
                    if (FUN_08002a18() - t0 > 2u) {
                        return 3u;
                    }
                }
            }
        }
    }
    if ((cfg->f0 & 8u) != 0u) {
        if (cfg->f5 != 0u) {
            RCCREG->r[37] |= 1u;
            t0 = FUN_08002a18();
            while ((RCCREG->r[37] & 2u) == 0u) {
                if (FUN_08002a18() - t0 > 2u) {
                    return 3u;
                }
            }
        } else {
            RCCREG->r[37] &= ~1u;
            t0 = FUN_08002a18();
            while ((RCCREG->r[37] & 2u) != 0u) {
                if (FUN_08002a18() - t0 > 2u) {
                    return 3u;
                }
            }
        }
    }
    if ((cfg->f0 & 4u) != 0u) {
        b = 0u;
        if ((((RCCREG->r[22] & 0x10000000u) == 0u) != 0u)) {
            RCCREG->r[22] |= 0x10000000u;
            chk = RCCREG->r[22] & 0x10000000u;
            b = (chk, 1u);
        }
        if ((PWRREG->CR & 0x100u) == 0u) {
            PWRREG->CR |= 0x100u;
            t0 = FUN_08002a18();
            while ((PWRREG->CR & 0x100u) == 0u) {
                if (FUN_08002a18() - t0 > 2u) {
                    return 3u;
                }
            }
        }
        if (cfg->f2 == 1u) {
            RCCREG->r[36] |= 1u;
        } else if (cfg->f2 == 5u) {
            RCCREG->r[36] |= 4u;
            RCCREG->r[36] |= 1u;
        } else {
            RCCREG->r[36] &= ~1u;
            RCCREG->r[36] &= ~4u;
        }
        if (cfg->f2 != 0u) {
            t0 = FUN_08002a18();
            while ((RCCREG->r[36] & 2u) == 0u) {
                if (FUN_08002a18() - t0 > 5000u) {
                    return 3u;
                }
            }
        } else {
            t0 = FUN_08002a18();
            while ((RCCREG->r[36] & 2u) != 0u) {
                if (FUN_08002a18() - t0 > 5000u) {
                    return 3u;
                }
            }
        }
        if (b == 1u) {
            RCCREG->r[22] &= ~0x10000000u;
        }
    }
    if ((cfg->f0 & 0x20u) != 0u) {
        if (cfg->f6 != 0u) {
            RCCREG->r[38] |= 1u;
            t0 = FUN_08002a18();
            while ((RCCREG->r[38] & 2u) == 0u) {
                if (FUN_08002a18() - t0 > 2u) {
                    return 3u;
                }
            }
        } else {
            RCCREG->r[38] &= ~1u;
            t0 = FUN_08002a18();
            while ((RCCREG->r[38] & 2u) != 0u) {
                if (FUN_08002a18() - t0 > 2u) {
                    return 3u;
                }
            }
        }
    }
    if (cfg->f7 != 0u) {
        if ((RCCREG->r[2] & 0xcu) != 0xcu) {
            if (cfg->f7 == 2u) {
                RCCREG->r[0] &= ~0x1000000u;
                t0 = FUN_08002a18();
                while ((RCCREG->r[0] & 0x2000000u) != 0u) {
                    if (FUN_08002a18() - t0 > 2u) {
                        return 3u;
                    }
                }
                RCCREG->r[3] = (RCCREG->r[3] & 0x019f800cu) |
                    (cfg->f8 | ((cfg->f9 - 1u) << 4) | (cfg->f10 << 8) |
                     (((cfg->f12 >> 1) - 1u) << 0x15) | (((cfg->f13 >> 1) - 1u) << 0x19) |
                     (cfg->f11 << 0x1b));
                RCCREG->r[0] |= 0x1000000u;
                RCCREG->r[3] |= 0x1000000u;
                t0 = FUN_08002a18();
                while ((RCCREG->r[0] & 0x2000000u) == 0u) {
                    if (FUN_08002a18() - t0 > 2u) {
                        return 3u;
                    }
                }
            } else {
                RCCREG->r[0] &= ~0x1000000u;
                t0 = FUN_08002a18();
                while ((RCCREG->r[0] & 0x2000000u) != 0u) {
                    if (FUN_08002a18() - t0 > 2u) {
                        return 3u;
                    }
                }
                RCCREG->r[3] = RCCREG->r[3] & 0xfeeefffcu;
            }
        } else {
            if (cfg->f7 == 1u) {
                return 1u;
            }
            n2 = RCCREG->r[3];
            if ((n2 & 3u) != cfg->f8 ||
                (n2 & 0xf0u) != (cfg->f9 - 1u) << 4 ||
                (n2 & 0x7f00u) != cfg->f10 << 8 ||
                (n2 & 0xf8000000u) != cfg->f11 << 0x1b ||
                (n2 & 0x600000u) != ((cfg->f12 >> 1) - 1u) << 0x15 ||
                (n2 & 0x6000000u) != ((cfg->f13 >> 1) - 1u) << 0x19) {
                return 1u;
            }
        }
    }
    return 0u;
}
