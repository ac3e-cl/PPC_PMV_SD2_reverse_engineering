#include <stdint.h>

typedef struct {
  volatile uint32_t CR1;   /* 0x00 */
  volatile uint32_t CR2;   /* 0x04 */
  volatile uint32_t SMCR;  /* 0x08 */
  volatile uint32_t DIER;  /* 0x0C */
  volatile uint32_t SR;    /* 0x10 */
  volatile uint32_t EGR;   /* 0x14 */
  volatile uint32_t CCMR1; /* 0x18 */
  volatile uint32_t CCMR2; /* 0x1C */
  volatile uint32_t CCER;  /* 0x20 */
} TIM_TypeDef;

typedef struct {
  TIM_TypeDef *Instance;   /* 0x00 */
  uint8_t reserved[0x39];
  volatile uint8_t state;  /* 0x3D */
} TimerHandle;

uint32_t FUN_08009288(TimerHandle *handle) {
  if (handle->state != 1) {
    return 1;
  }
  handle->state = 2;
  handle->Instance->DIER |= 1u;
  if (handle->Instance == (TIM_TypeDef *)0x40012c00u ||
      handle->Instance == (TIM_TypeDef *)0x40000000u ||
      handle->Instance == (TIM_TypeDef *)0x40000400u ||
      handle->Instance == (TIM_TypeDef *)0x40000800u ||
      handle->Instance == (TIM_TypeDef *)0x40000c00u ||
      handle->Instance == (TIM_TypeDef *)0x40013400u ||
      handle->Instance == (TIM_TypeDef *)0x40014000u ||
      handle->Instance == (TIM_TypeDef *)0x40015000u) {
    uint32_t mode = handle->Instance->SMCR & 0x10007u;
    if (mode != 6u && mode != 0x10000u) {
      handle->Instance->CR1 |= 1u;
    }
  } else {
    handle->Instance->CR1 |= 1u;
  }
  return 0;
}
