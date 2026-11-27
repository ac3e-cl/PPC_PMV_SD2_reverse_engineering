#include <stdint.h>

typedef union {
    const void *stack;
    void (*handler)(void);
} vector_entry_t;

extern char __initial_sp;
extern void Reset_Handler(void);
extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);
extern void IRQ_18(void);
extern void IRQ_86(void);
extern void Default_Handler(void);

__attribute__((used, section(".isr_vector"), aligned(4)))
const vector_entry_t g_pfnVectors[118] = {
    [0] = {.stack = &__initial_sp},
    [1] = {.handler = Reset_Handler},
    [2] = {.handler = NMI_Handler},
    [3] = {.handler = HardFault_Handler},
    [4] = {.handler = MemManage_Handler},
    [5] = {.handler = BusFault_Handler},
    [6] = {.handler = UsageFault_Handler},
    [7 ... 10] = {.stack = 0},
    [11] = {.handler = SVC_Handler},
    [12] = {.handler = DebugMon_Handler},
    [13] = {.stack = 0},
    [14] = {.handler = PendSV_Handler},
    [15] = {.handler = SysTick_Handler},
    [16 ... 33] = {.handler = Default_Handler},
    [34] = {.handler = IRQ_18},
    [35 ... 100] = {.handler = Default_Handler},
    [101] = {.stack = 0},
    [102] = {.handler = IRQ_86},
    [103 ... 117] = {.handler = Default_Handler},
};

_Static_assert(sizeof(vector_entry_t) == sizeof(uint32_t), "vector entry must be one word");
_Static_assert(sizeof(g_pfnVectors) == 472, "STM32G474 vector table must be 118 words");
