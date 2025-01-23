/**
  ******************************************************************************
  * @file    fsm01m1_driver.h
  * @author  ST Power Application Laboratory
  * @version V1.0.0
  * @brief   Provides functions for interactive board control and measurement
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSM01M1_DRIVER_H
#define __FSM01M1_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../../NUCLEO/inc/nucleo_usart_driver.h"
#include "stdbool.h"


/* Exported types ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
void FSM01M1_CTRL_Handle(USART_MessageTypeDef * msg);

#ifdef	 __cplusplus
}
#endif

#endif /* __FSM01M1_DRIVER_H */
