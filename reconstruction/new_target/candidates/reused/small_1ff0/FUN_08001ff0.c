/* FUN_08001ff0: DMA/peripheral bring-up, reconstructed from disassembly at 0x08001ff0. */
#include <stdint.h>

/* Bases are pool-resident absolute addresses; modeled as extern symbols (linked
 * via --defsym) so GCC keeps the +0x2c/+0x30 offsets in the store displacements. */
extern volatile uint32_t BASE_48000400;
extern volatile uint32_t BASE_48000800;
extern volatile uint32_t BASE_48000C00;
extern volatile uint32_t PARAM_BLOCK;
extern volatile uint32_t HANDLE_A[13];
extern volatile uint32_t HANDLE_B;

extern void FUN_08005fa0(volatile uint32_t *base, uint32_t channel, uint32_t state);
extern void FUN_08002a30(uint32_t ticks);
extern void FUN_080077f6(volatile uint32_t *handle, uint32_t mask);
extern void FUN_080078aa(volatile uint32_t *handle, uint32_t mask);
extern uint32_t FUN_08002f90(volatile uint32_t *handle);
extern void FUN_08002244(void);
extern void FUN_08003538(volatile uint32_t *handle);

void FUN_08001ff0(void)
{
    FUN_08005fa0(&BASE_48000400, 0x10, 0);
    FUN_08005fa0(&BASE_48000400, 0x8, 0);
    FUN_08005fa0(&BASE_48000800, 0x1000, 1);
    FUN_08005fa0(&BASE_48000C00, 0x4, 1);
    FUN_08002a30(1000);
    FUN_080077f6(&PARAM_BLOCK, 0x100);
    FUN_080077f6(&PARAM_BLOCK, 0x200);
    FUN_080077f6(&PARAM_BLOCK, 0x400);
    FUN_080077f6(&PARAM_BLOCK, 0x800);
    FUN_080078aa(&PARAM_BLOCK, 0x10000);
    FUN_080078aa(&PARAM_BLOCK, 0x200000);
    FUN_080078aa(&PARAM_BLOCK, 0x400000);
    HANDLE_A[0x2c / 4] = 0x6a0;
    HANDLE_A[0x30 / 4] = 0x400;
    if (FUN_08002f90(HANDLE_A) != 0) {
        FUN_08002244();
    }
    FUN_08003538(&HANDLE_B);
    FUN_08003538(HANDLE_A);
}
