#include <stdint.h>

typedef struct { volatile uint32_t field[4]; } HrtimCtl;
extern volatile HrtimCtl HRTIM_CTL;            /* = 0x20000164 */
#define PERIPH_BASE 0x40016800u                /* non-encodable imm: stays in literal pool */

extern int  FUN_08006004(volatile uint32_t *);
extern int  FUN_080061a4(volatile uint32_t *, uint32_t);
extern int  FUN_08006254(volatile uint32_t *, uint32_t);
extern int  FUN_0800668c(volatile uint32_t *, uint32_t);
extern int  FUN_080068d8(volatile uint32_t *, uint32_t, volatile uint32_t *);
extern int  FUN_08006700(volatile uint32_t *, uint32_t, volatile uint32_t *);
extern int  FUN_0800630c(volatile uint32_t *, uint32_t, volatile uint32_t *);
extern void FUN_08006ac8(volatile uint32_t *, uint32_t, uint32_t);
extern int  FUN_08006bcc(volatile uint32_t *, uint32_t, volatile uint32_t *);
extern int  FUN_08006fa4(volatile uint32_t *, uint32_t, uint32_t);
extern int  FUN_080062bc(volatile uint32_t *, uint32_t, volatile uint32_t *);
extern int  FUN_08007238(volatile uint32_t *, uint32_t, volatile uint32_t *);
extern int  FUN_080074b8(volatile uint32_t *, uint32_t, uint32_t, volatile uint32_t *);
extern int  FUN_08007352(volatile uint32_t *, uint32_t, volatile uint32_t *);
extern int  FUN_080073b8(volatile uint32_t *, uint32_t, volatile uint32_t *);
extern int  FUN_08007794(volatile uint32_t *, uint32_t, uint32_t, volatile uint32_t *);
extern void FUN_08002550(volatile uint32_t *);
extern void FUN_08002244(void);

void FUN_080018cc(void)
{
    uint32_t v1[3] = {0};                     /* r7+0xf4 */
    uint32_t v2[4] = {0};                     /* r7+0xe4 */
    uint32_t v3[2] = {0};                     /* r7+0xdc */
    uint32_t v4[4] = {0};                     /* r7+0xcc */
    uint32_t v5[24] = {0};                    /* r7+0x6c */
    uint32_t v6[3] = {0};                     /* r7+0x60 */
    uint32_t v7[7] = {0};                     /* r7+0x44 */
    uint32_t v8[9] = {0};                     /* r7+0x20 */
    uint32_t v9[8] = {0};                     /* r7+0x00 */

    HRTIM_CTL.field[0] = PERIPH_BASE;
    HRTIM_CTL.field[1] = 0;
    HRTIM_CTL.field[2] = 0;

    if (FUN_08006004(&HRTIM_CTL.field[0]) != 0) FUN_08002244();
    if (FUN_080061a4(&HRTIM_CTL.field[0], 0xc) != 0) FUN_08002244();
    if (FUN_08006254(&HRTIM_CTL.field[0], 0xa) != 0) FUN_08002244();
    if (FUN_0800668c(&HRTIM_CTL.field[0], 0) != 0) FUN_08002244();

    v1[0] = 0;
    v1[1] = 0;
    v1[2] = 1;
    if (FUN_080068d8(&HRTIM_CTL.field[0], 0x20, &v1[0]) != 0) FUN_08002244();
    if (FUN_08006700(&HRTIM_CTL.field[0], 0x20, &v1[0]) != 0) FUN_08002244();

    v2[0] = 0;
    v2[1] = 0;
    v2[2] = 0;
    v2[3] = 0;
    if (FUN_0800630c(&HRTIM_CTL.field[0], 0x20, &v2[0]) != 0) FUN_08002244();
    FUN_08006ac8(&HRTIM_CTL.field[0], 0x20, 1);

    v3[0] = 0;
    v3[1] = 8;
    if (FUN_08006bcc(&HRTIM_CTL.field[0], 1, &v3[0]) != 0) FUN_08002244();
    if (FUN_08006fa4(&HRTIM_CTL.field[0], 1, 0) != 0) FUN_08002244();
    v3[1] = 8;
    if (FUN_08006bcc(&HRTIM_CTL.field[0], 2, &v3[0]) != 0) FUN_08002244();
    if (FUN_08006fa4(&HRTIM_CTL.field[0], 2, 0) != 0) FUN_08002244();

    v4[0] = 0xd480;
    v4[1] = 0;
    v4[2] = 0;
    v4[3] = 8;
    if (FUN_080062bc(&HRTIM_CTL.field[0], 6, &v4[0]) != 0) FUN_08002244();

    v5[0] = 0;
    v5[1] = 0;
    v5[2] = 0;
    v5[3] = 0;
    v5[4] = 1;
    v5[5] = 0;
    v5[6] = 2;
    v5[7] = 0;
    v5[8] = 0;
    v5[9] = 0;
    v5[10] = 0x8000000;
    v5[11] = 0;
    v5[12] = 0;
    v5[13] = 0x20000000;
    v5[23] = 0;
    if (FUN_08007238(&HRTIM_CTL.field[0], 6, &v5[0]) != 0) FUN_08002244();

    v6[0] = 0x220;
    if (FUN_080074b8(&HRTIM_CTL.field[0], 6, 2, &v6[0]) != 0) FUN_08002244();
    v6[0] = 0x6c60;
    if (FUN_080074b8(&HRTIM_CTL.field[0], 6, 4, &v6[0]) != 0) FUN_08002244();
    v6[0] = 0x110;
    if (FUN_080074b8(&HRTIM_CTL.field[0], 6, 8, &v6[0]) != 0) FUN_08002244();

    v4[0] = 0xffdf;
    v4[1] = 0;
    if (FUN_080062bc(&HRTIM_CTL.field[0], 4, &v4[0]) != 0) FUN_08002244();

    v7[0] = 0;
    v7[6] = 0;
    if (FUN_08007352(&HRTIM_CTL.field[0], 4, &v7[0]) != 0) FUN_08002244();

    v5[0] = 0;
    v5[1] = 0;
    v5[6] = 0;
    v5[10] = 0;
    v5[13] = 0;
    v5[14] = 0;
    v5[15] = 0x20;
    v5[16] = 0;
    v5[17] = 0x100;
    v5[18] = 0;
    v5[20] = 0;
    v5[21] = 0;
    v5[22] = 0;
    if (FUN_08007238(&HRTIM_CTL.field[0], 4, &v5[0]) != 0) FUN_08002244();
    v5[18] = 0;
    if (FUN_08007238(&HRTIM_CTL.field[0], 5, &v5[0]) != 0) FUN_08002244();

    v8[0] = 0;
    v8[1] = 0x110;
    v8[2] = 0;
    v8[3] = 0x8000;
    v8[4] = 0x4000;
    v8[5] = 0x110;
    v8[6] = 0;
    v8[7] = 0x80000000;
    v8[8] = 0x40000000;
    if (FUN_080073b8(&HRTIM_CTL.field[0], 4, &v8[0]) != 0) FUN_08002244();
    if (FUN_080073b8(&HRTIM_CTL.field[0], 5, &v8[0]) != 0) FUN_08002244();

    v9[0] = 0;
    v9[1] = 0x80;
    v9[2] = 0x100;
    v9[3] = 0;
    v9[4] = 0;
    v9[5] = 0x20;
    v9[6] = 0;
    v9[7] = 0;
    if (FUN_08007794(&HRTIM_CTL.field[0], 4, 0x100, &v9[0]) != 0) FUN_08002244();
    v9[1] = 0x200;
    v9[2] = 0x400;
    if (FUN_08007794(&HRTIM_CTL.field[0], 5, 0x400, &v9[0]) != 0) FUN_08002244();
    v9[1] = 0;
    v9[2] = 0;
    if (FUN_08007794(&HRTIM_CTL.field[0], 4, 0x200, &v9[0]) != 0) FUN_08002244();
    if (FUN_08007794(&HRTIM_CTL.field[0], 5, 0x800, &v9[0]) != 0) FUN_08002244();
    if (FUN_080062bc(&HRTIM_CTL.field[0], 5, &v4[0]) != 0) FUN_08002244();
    if (FUN_08007352(&HRTIM_CTL.field[0], 5, &v7[0]) != 0) FUN_08002244();
    FUN_08002550(&HRTIM_CTL.field[0]);
}
