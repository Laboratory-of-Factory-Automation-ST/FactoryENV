/**
  ******************************************************************************
  * @file           : app_ips_switch.c
  * @author         : AMS IPC Application Team
  * @brief          : Example application code
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "app_ips_switch.h"

/** @addtogroup OUT_16_Example OUT_16_Example
  * @{
  */

/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

/** @addtogroup OUT_16_Example_Functions_Definition OUT_16_Example Functions Definition
  * @{
  */

/**
  * @brief IPS Initialization Function
  * @retval None
  */
void MX_ips_switch_Init(void)
{
  custom_app_init();
}

/**
  * @brief IPS operations execution function
  * @retval None
  */
void MX_ips_switch_Process(void)
{
  custom_app_process();
}

uint32_t getTimerClk(TIM_TypeDef *tim)
{
  uint32_t timer_clock = 0;
  uint32_t bus_clock_timer = 0;

  if ((getTimerClkSrc(tim)) == 1) {bus_clock_timer = HAL_RCC_GetPCLK1Freq();}
  else if ((getTimerClkSrc(tim)) == 2) {bus_clock_timer = HAL_RCC_GetPCLK2Freq();}

  if (bus_clock_timer == HAL_RCC_GetHCLKFreq()) {timer_clock = bus_clock_timer;}
  else {timer_clock = 2 * bus_clock_timer;}

  return timer_clock;
}

/**
  * @brief  This function return the timer clock source.
  * @param  tim: timer instance
  * @retval 1 = PCLK1 or 2 = PCLK2
  */
uint8_t getTimerClkSrc(TIM_TypeDef *tim)
{
  uint8_t clkSrc = 0;

#if defined(STM32F0xx) || defined(STM32G0xx)
  /* TIMx source CLK is PCKL1 */
  clkSrc = 1;
#else
  {
    /* Get source clock depending on TIM instance */
    switch ((uint32_t)tim)
    {
#if defined(TIM2_BASE)
      case (uint32_t)TIM2:
#endif /* #if defined(TIM2_BASE) */
#if defined(TIM3_BASE)
      case (uint32_t)TIM3:
#endif /* #if defined(TIM3_BASE) */
#if defined(TIM4_BASE)
      case (uint32_t)TIM4:
#endif /* #if defined(TIM4_BASE) */
#if defined(TIM5_BASE)
      case (uint32_t)TIM5:
#endif /* #if defined(TIM5_BASE) */
#if defined(TIM6_BASE)
      case (uint32_t)TIM6:
#endif /* #if defined(TIM6_BASE) */
#if defined(TIM7_BASE)
      case (uint32_t)TIM7:
#endif /* #if defined(TIM7_BASE) */
#if defined(TIM12_BASE)
      case (uint32_t)TIM12:
#endif /* #if defined(TIM12_BASE) */
#if defined(TIM13_BASE)
      case (uint32_t)TIM13:
#endif /* #if defined(TIM13_BASE) */
#if defined(TIM14_BASE)
      case (uint32_t)TIM14:
#endif /* #if defined(TIM14_BASE) */
#if defined(TIM18_BASE)
      case (uint32_t)TIM18:
#endif /* #if defined(TIM18_BASE) */
        clkSrc = 1;
        break;
#if defined(TIM1_BASE)
      case (uint32_t)TIM1:
#endif /* #if defined(TIM1_BASE) */
#if defined(TIM8_BASE)
      case (uint32_t)TIM8:
#endif /* #if defined(TIM8_BASE) */
#if defined(TIM9_BASE)
      case (uint32_t)TIM9:
#endif /* #if defined(TIM9_BASE) */
#if defined(TIM10_BASE)
      case (uint32_t)TIM10:
#endif /* #if defined(TIM10_BASE) */
#if defined(TIM11_BASE)
      case (uint32_t)TIM11:
#endif /* #if defined(TIM11_BASE) */
#if defined(TIM15_BASE)
      case (uint32_t)TIM15:
#endif /* #if defined(TIM15_BASE) */
#if defined(TIM16_BASE)
      case (uint32_t)TIM16:
#endif /* #if defined(TIM16_BASE) */
#if defined(TIM17_BASE)
      case (uint32_t)TIM17:
#endif /* #if defined(TIM17_BASE) */
#if defined(TIM19_BASE)
      case (uint32_t)TIM19:
#endif /* #if defined(TIM19_BASE) */
#if defined(TIM20_BASE)
      case (uint32_t)TIM20:
#endif /* #if defined(TIM20_BASE) */
#if defined(TIM21_BASE)
      case (uint32_t)TIM21:
#endif /* #if defined(TIM21_BASE */
#if defined(TIM22_BASE)
      case (uint32_t)TIM22:
#endif /* #if defined(TIM22_BASE) */
        clkSrc = 2;
        break;
      default:

        break;
    }
  }
#endif /* #if defined(STM32F0xx) || defined(STM32G0xx) */
  return clkSrc;
}

/**
  * @}
  */

/**
  * @}
  */
