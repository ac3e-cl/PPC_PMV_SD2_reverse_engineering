#include <stdint.h>
typedef struct { uint32_t a,b,c,d; uint8_t pad[112]; } Row;
typedef struct { uint8_t pad[0xbc]; Row rows[]; } Block;
typedef struct { uint32_t value; uint8_t pad[124]; } ConfigRow;
struct ConfigBlock { uint8_t pad[0xe4]; ConfigRow rows[]; };
typedef struct { uint32_t a,b,c,d,e,f,g,h; } Source;

void FUN_08007f3c(Block **param_1, int param_2, uint32_t param_3, Source *param_4)
{
    uint32_t e4;
    uint32_t shift;
    uint32_t b8;

    shift = 0;
    e4 = *(uint32_t *)(*(int *)param_1 + param_2 * 0x80 + 0xe4);
    b8 = *(uint32_t *)(*(int *)param_1 + param_2 * 0x80 + 0xb8);
    switch (param_3) {
    case 1: case 4: case 16: case 0x40: case 0x100: case 0x400:
        (*param_1)->rows[param_2].a = param_4->b;
        (*param_1)->rows[param_2].b = param_4->c;
        break;
    case 2: case 8: case 32: case 0x80: case 0x200: case 0x800:
        (*param_1)->rows[param_2].c = param_4->b;
        (*param_1)->rows[param_2].d = param_4->c;
        shift = 0x10u;
        break;
    default:
        break;
    }
    e4 = ~(0xFEu << shift) & e4;
    e4 = (param_4->a << shift) | e4;
    e4 = (param_4->d << shift) | e4;
    e4 = (param_4->e << shift) | e4;
    e4 = (param_4->f << shift) | e4;
    e4 = (param_4->g << shift) | e4;
    if (param_4->e == 8 && (b8 & 0x200) == 0 && (b8 & 0x2000000) == 0) {
        e4 = (param_4->h << shift) | e4;
    }
    ((struct ConfigBlock *)*param_1)->rows[param_2].value = e4;
}
