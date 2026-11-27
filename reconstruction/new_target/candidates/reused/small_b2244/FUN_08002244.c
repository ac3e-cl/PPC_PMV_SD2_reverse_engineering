/* Fatal init-error halt (0x08002244): disable IRQs, then spin with NOPs.
 * Equivalent to CMSIS __disable_irq(); __NOP(); while(1){ __NOP(); }. */
void FUN_08002244(void)
{
    __asm volatile("cpsid i" : : : "memory");
    __asm volatile("nop" : : : "memory");
    while (1) {
        __asm volatile("nop" : : : "memory");
    }
}
