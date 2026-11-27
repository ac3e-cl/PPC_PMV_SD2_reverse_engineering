/* Names inferred from Cortex-M vectors; source reconstructed from instructions. */
#include <stdint.h>

extern void HAL_IncTick(void);
void NMI_Handler(void) { for (;;) {} }
void HardFault_Handler(void) { for (;;) {} }
void MemManage_Handler(void) { for (;;) {} }
void BusFault_Handler(void) { for (;;) {} }
void UsageFault_Handler(void) { for (;;) {} }
void SVC_Handler(void) {}
void DebugMon_Handler(void) {}
void PendSV_Handler(void) {}
void SysTick_Handler(void) { HAL_IncTick(); }

/* Callback signatures inferred from the stores of r0/r1 in the prologue. */
void FUN_08003d38(void *handle __attribute__((unused))) {}
void FUN_08003d4c(void *handle __attribute__((unused))) {}
void FUN_08003d60(void *handle __attribute__((unused))) {}
void FUN_08004ac0(void *handle __attribute__((unused))) {}
void FUN_08004ad4(void *handle __attribute__((unused))) {}
void FUN_08004ae8(void *handle __attribute__((unused))) {}
void FUN_08004afc(void *handle __attribute__((unused))) {}
void FUN_08004b10(void *handle __attribute__((unused))) {}
void FUN_080059fa(void *handle __attribute__((unused)), uint32_t value __attribute__((unused))) {}
void FUN_08005a10(void *handle __attribute__((unused)), uint32_t value __attribute__((unused))) {}
void FUN_08005a26(void *handle __attribute__((unused))) {}
void FUN_08005a3a(void *handle __attribute__((unused)), uint32_t value __attribute__((unused))) {}
void FUN_08005a50(void *handle __attribute__((unused)), uint32_t value __attribute__((unused))) {}
void FUN_08005a66(void *handle __attribute__((unused))) {}
void FUN_08005a7a(void *handle __attribute__((unused))) {}
void FUN_08005a8e(void *handle __attribute__((unused))) {}
void FUN_08005aa2(void *handle __attribute__((unused))) {}
void FUN_08005ab6(void *handle __attribute__((unused)), uint32_t value __attribute__((unused))) {}
void FUN_08009674(void *handle __attribute__((unused))) {}
void FUN_08009688(void *handle __attribute__((unused))) {}
void FUN_0800969c(void *handle __attribute__((unused))) {}
void FUN_080096b0(void *handle __attribute__((unused))) {}
void FUN_08009958(void *handle __attribute__((unused))) {}
void FUN_0800996c(void *handle __attribute__((unused))) {}
void FUN_08009980(void *handle __attribute__((unused))) {}
void FUN_08009994(void *handle __attribute__((unused))) {}
void FUN_080099a8(void *handle __attribute__((unused))) {}
void FUN_080099bc(void *handle __attribute__((unused))) {}
void FUN_080099d0(void *handle __attribute__((unused))) {}

extern volatile uint32_t uwTick;
extern uint32_t uwTickFreq;
void HAL_IncTick(void) { uwTick += uwTickFreq; }
uint32_t HAL_GetTick(void) { return uwTick; }
typedef struct { uint32_t reserved[16]; volatile uint32_t value; } ADC_Registers;
uint32_t FUN_0800385e(ADC_Registers **handle) { return (*handle)->value; }
typedef struct { uint32_t reserved0[3]; volatile uint32_t AIRCR; uint32_t reserved1[30]; volatile uint32_t CPACR; } SCB_Registers;
void FUN_080028d8(void) { ((SCB_Registers *)0xe000ed00u)->CPACR |= 0x00f00000u; }
uint32_t FUN_08004d7c(void) { return (((SCB_Registers *)0xe000ed00u)->AIRCR >> 8) & 7u; }
typedef struct { uint32_t reserved[2]; volatile uint32_t CR3; } PWR_Registers;
void FUN_08008330(void) { ((PWR_Registers *)0x40007000u)->CR3 |= 0x4000u; }

void HAL_Delay(uint32_t delay) {
    uint32_t start = HAL_GetTick();
    uint32_t wait = delay;
    if (wait != UINT32_MAX) wait += uwTickFreq;
    while (HAL_GetTick() - start < wait) {}
}
extern unsigned char timer_handle, fdcan_handle;
extern void TIM_IRQHandler(void *handle);
extern void FDCAN_IRQHandler(void *handle);
void IRQ_55(void) { TIM_IRQHandler(&timer_handle); }
void IRQ_86(void) { FDCAN_IRQHandler(&fdcan_handle); }
extern void NVIC_SetPriorityGrouping(uint32_t grouping);
extern void NVIC_EnableIRQ(int irq);
extern uint32_t SysTick_Config(uint32_t ticks);
void FUN_08004ed4(uint32_t grouping) { NVIC_SetPriorityGrouping(grouping); }
void FUN_08004f1e(int8_t irq) { NVIC_EnableIRQ(irq); }
uint32_t FUN_08004f3a(uint32_t ticks) { return SysTick_Config(ticks); }
typedef struct { uint32_t reserved[49]; volatile uint32_t TXFQS; } FDCAN_Registers;
uint32_t FUN_080055a4(FDCAN_Registers **handle) {
    uint32_t available = (*handle)->TXFQS & 7u;
    return available;
}
typedef struct { uint32_t reserved[2]; volatile uint32_t CR; } ADC_Control;
uint32_t FUN_08004956(ADC_Control *adc) { return (adc->CR & 1u) == 1u ? 1u : 0u; }
uint32_t FUN_080049ae(ADC_Control *adc) { return (adc->CR & 0x80000000u) == 0x80000000u ? 1u : 0u; }
uint32_t FUN_080049d6(ADC_Control *adc) { return (adc->CR & 4u) == 4u ? 1u : 0u; }
