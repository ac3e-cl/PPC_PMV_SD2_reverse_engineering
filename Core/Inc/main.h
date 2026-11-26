/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_HRTIM_MspPostInit(HRTIM_HandleTypeDef *hhrtim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define period 32*170e6/freq
#define freq 100000
#define alpha_initial 0.01

/* USER CODE BEGIN Private defines */

// parametros controlador de corriente
#define half_period 27200
#define post 23								// 2^(post)
//#define ka 0.0006							// ganancia proporcional. PI forma serie
//#define kb 510							// ganancia integral. PI forma serie
#define Ts 1e-5								// periodo de muestreo (s)
#define mul_by_ki_cc 0						// multiplica por ki_cc = 1
#define mul_by_kp_cc 6						// multiplica por kp_cc = 64
#define mul_by_kp_cv 9						// multiplica por kp_cv = 512
#define mul_by_ki_cv 0						// multiplica por ki_cv = 1
#define phase_shift_max 24480				// maxima actuacion
#define phase_shift_min 65					// minima actuacion
#define iL_oc 3358							// sobre corriente 30 A (98.28*30(A)+409.5)
#define offset 3000							// ticks a agregar para corregir muestreo de corriente
#define iL_zero 410							// equivale a 0 (A)
#define iL_ref_min 606						// equivale a 2 (A) (98.28*1(A)+409.5)
#define iL_ref_max 1392						// equivale a 10(A) (98.28*10(A)+409.5)
#define delta_vo 75							// 3.2057*20V + 10.867
#define vo_ref_min 652						// 3.2057*200V + 10.867
#define vo_ref_max 1293						// 3.2057*400V + 10.867

/* PROTECCIONES */
#define OVP	4500							// 450 V
#define UVP	2500							// 250 V
#define OCP	250								// 25 A

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
