#include "stm32g4xx.h"
void NMI_Handler(void) {
    for (;;) {
        __NOP();
    }
}
