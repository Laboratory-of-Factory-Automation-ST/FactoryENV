/**
  ******************************************************************************
  * @file    nucleo_usart_driver.h
  * @author  ST Power Application Laboratory
  * @version V1.0.0
  * @brief   Provides functions for serial ST-LINK communication
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
/* TODO follow naming convention (ref. template.h) */
#ifndef __NUCLEO_USART_DRIVER_H
#define __NUCLEO_USART_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported constants --------------------------------------------------------*/
#define USART_COM_TIMEOUT 	100
#define USART_MSG_MAX_LEN 	255
#define USART_EOL_LEN		2

/* COM port parameters */
#define NUCLEO_USART_BAUDRATE 		115200
#define NUCLEO_USART_WORLDLENGTH 	UART_WORDLENGTH_8B
#define NUCLEO_USART_STOPBITS 		UART_STOPBITS_1
#define NUCLEO_USART_PARITY			UART_PARITY_NONE
#define NUCLEO_USART_HWCONTROL		UART_HWCONTROL_NONE

/* Exported types ------------------------------------------------------------*/
typedef enum USART_MsgFlag_t {
	ready,
	wait,
	write,
	flush_write,
} USART_MsgFlagTypeDef;

typedef struct USART_Message_t {
	char data[USART_MSG_MAX_LEN];
	int length;
	USART_MsgFlagTypeDef flag;

	// aliases to common functions
	void (* AppendInt)(struct USART_Message_t * msg, int i);
	void (* AppendFloat)(struct USART_Message_t * msg, float f);
	void (* AppendStr)(struct USART_Message_t * msg, char * str);
	void (* Reset)(struct USART_Message_t * msg);
} USART_MessageTypeDef;

/* Exported vars -------------------------------------------------------------*/
// TODO: Possible race condition hazard, think about more enclosed solution
extern UART_HandleTypeDef *uart_handle;
extern char rx_buffer[USART_MSG_MAX_LEN];
extern USART_MessageTypeDef msg;
extern USART_MessageTypeDef cmd;

/* Exported functions --------------------------------------------------------*/
USART_MessageTypeDef NUCLEO_USART_vCOM_CreateMessage();
void NUCLEO_USART_vCOM_AppendInt(USART_MessageTypeDef * self, int i);
void NUCLEO_USART_vCOM_AppendFloat(USART_MessageTypeDef * self, float f);
void NUCLEO_USART_vCOM_AppendDouble(USART_MessageTypeDef * self, double d);
void NUCLEO_USART_vCOM_AppendStr(USART_MessageTypeDef * self, char * str);
void NUCLEO_USART_vCOM_Reset(USART_MessageTypeDef * self);
HAL_StatusTypeDef NUCLEO_USART_vCOM_Clear();
HAL_StatusTypeDef NUCLEO_USART_vCOM_Write(USART_MessageTypeDef * msg);
HAL_StatusTypeDef NUCLEO_USART_vCOM_FlushWrite(USART_MessageTypeDef * msg);
HAL_StatusTypeDef NUCLEO_USART_vCOM_FlushWriteLine(USART_MessageTypeDef * msg);
HAL_StatusTypeDef NUCLEO_USART_vCOM_WriteLine(USART_MessageTypeDef * msg);
HAL_StatusTypeDef NUCLEO_USART_vCOM_WriteChar(char c);
HAL_StatusTypeDef NUCLEO_USART_WriteString(char *str);
HAL_StatusTypeDef NUCLEO_USART_WriteStringLine(char *str);
//HAL_StatusTypeDef NUCLEO_USART_vCOM_QuickWrite(char * fmt_str);
HAL_StatusTypeDef NUCLEO_USART_vCOM_QuickWriteLine(char * fmt_str);
HAL_StatusTypeDef NUCLEO_USART_vCOM_Status();
HAL_StatusTypeDef NUCLEO_USART_ReadLine(USART_MessageTypeDef * msg);

#ifdef	 __cplusplus
}
#endif

#endif /* __NUCLEO_USART_DRIVER_H */
