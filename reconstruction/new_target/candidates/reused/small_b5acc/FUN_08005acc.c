#include <stdint.h>

typedef struct {
    volatile uint32_t pad00[0x20];  /* 0x00-0x7f */
    volatile uint32_t CR80;         /* 0x80 */
} Inst_TypeDef;

typedef struct {
    Inst_TypeDef *Instance;  /* 0x00 */
    uint32_t pad04[0x0c];    /* 0x04-0x33 */
    uint32_t f34;            /* 0x34 */
    uint32_t f38;            /* 0x38 */
    uint32_t pad3c;          /* 0x3c */
    uint32_t *f40;           /* 0x40 */
    uint32_t *f44;           /* 0x44 */
    uint32_t *f48;           /* 0x48 */
    uint32_t *f4c;           /* 0x4c */
    uint32_t *f50;           /* 0x50 */
    uint32_t *f54;           /* 0x54 */
} Cfg_TypeDef;

void FUN_08005acc(Cfg_TypeDef *cfg)
{
    uint32_t *p;
    uint32_t *base = (uint32_t *)0x4000a400u;

    if (cfg->Instance == (Inst_TypeDef *)0x40006800u) {
        base += 0x350 / 4;
    }
    if (cfg->Instance == (Inst_TypeDef *)0x40006c00u) {
        base += 0x6a0 / 4;
    }
    cfg->f40 = base;
    cfg->Instance->CR80 = (cfg->Instance->CR80 & 0xFFE0FFFFu) | (cfg->f34 << 16);
    cfg->f44 = base + 0x70 / 4;
    cfg->Instance->CR80 = (cfg->Instance->CR80 & 0xF0FFFFFFu) | (cfg->f38 << 24);
    cfg->f48 = base + 0xb0 / 4;
    cfg->f4c = base + 0x188 / 4;
    cfg->f50 = base + 0x260 / 4;
    cfg->f54 = base + 0x278 / 4;
    for (p = base; p < base + 0x350 / 4; p++) {
        *p = 0u;
    }
}
