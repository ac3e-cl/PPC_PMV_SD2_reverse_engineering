#include "stm32g4xx.h"

void HardFault_Handler(void) { for (;;) { __NOP(); } }
void MemManage_Handler(void) { for (;;) { __NOP(); } }
void BusFault_Handler(void) { for (;;) { __NOP(); } }
void UsageFault_Handler(void) { for (;;) { __NOP(); } }
