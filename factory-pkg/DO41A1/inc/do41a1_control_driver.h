/**
  ******************************************************************************
  * @file    do41a1_control_driver.h
  * @brief   This file contains interfaces for control of X-NUCLEO-DO41A1 board.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FACTORY_PKG_DO41A1_INC_DO41A1_CONTROL_DRIVER_H_
#define FACTORY_PKG_DO41A1_INC_DO41A1_CONTROL_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
#include "nucleo_usart_driver.h"

/* Exported types ------------------------------------------------------------*/
typedef const unsigned int DO41A1_CTRL_IO;
typedef struct DO41A1_IO {
		DO41A1_CTRL_IO all,
		out1,
		out2,
		out3,
		out4,
		outx,
		status1,
		status2,
		status3,
		status4;
};
/* Exported constants --------------------------------------------------------*/
extern const struct DO41A1_IO do41a1_io;
/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void DO41A1_CTRL_Handle(USART_MessageTypeDef * msg);
void DO41A1_CTRL_ActivateOutput(DO41A1_CTRL_IO out_ctrl);
void DO41A1_CTRL_DeactivateOutput(DO41A1_CTRL_IO out_ctrl);
void DO41A1_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif
