#include <stdint.h>

typedef struct {
    uint32_t Instance;
    uint8_t reserved[0xd8];
    uint8_t busy;
    volatile uint8_t state;
} Handle;

extern void FUN_08007a36(void *, int *);
extern void FUN_08007b70(void *, int, int *);
extern void FUN_0800810c(void *, int);

typedef struct { volatile uint32_t value; uint8_t pad[124]; } Row;
typedef struct { uint8_t pad[128]; Row rows[]; } RegBlock;
typedef struct { int f[24]; } Conf;
typedef struct { int prefix[8]; int rows[6][7]; } HandleRows;
int FUN_08007238(RegBlock **param_1, int param_2, Conf *c)
{
  if (((Handle *)param_1)->state == 2) return 2;
  if (((Handle *)param_1)->busy == 1) return 2;
  ((Handle *)param_1)->busy = 1;
  ((Handle *)param_1)->state = 2;
  if (param_2 == 6) FUN_08007a36(param_1, (int *)c);
  else FUN_08007b70(param_1, param_2, (int *)c);
  ((HandleRows *)param_1)->rows[param_2][0] = c->f[0];
  ((HandleRows *)param_1)->rows[param_2][1] = c->f[1];
  ((HandleRows *)param_1)->rows[param_2][2] = c->f[2];
  ((HandleRows *)param_1)->rows[param_2][3] = c->f[3];
  ((HandleRows *)param_1)->rows[param_2][4] = c->f[4];
  FUN_0800810c(param_1, param_2);
  if (param_2 != 6 && c->f[11] == 0) {
    (*param_1)->rows[param_2].value =
      ((*param_1)->rows[param_2].value & 0xfffffdffu) | (c->f[0x17] << 9);
  }
  ((Handle *)param_1)->state = 1;
  ((Handle *)param_1)->busy = 0;
  return 0;
}
