/**
  ******************************************************************************
  * @file    nucleo_usart_driver.c
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

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "nucleo_usart_driver.h"

/* Private constants ---------------------------------------------------------*/
#define USART_COM_TIMEOUT 100

/* Exported functions --------------------------------------------------------*/

/**
 * @brief Configuration of virtual COM
 * @param huart: initialized virtual COM Handle
 * @retval int
 */
int NUCLEO_USART_vCOM_Config(UART_HandleTypeDef * huart) {
	uart_handle = huart;
	uart_handle->Init.BaudRate = 115200;
	uart_handle->Init.WordLength = UART_WORDLENGTH_8B;
	uart_handle->Init.StopBits = UART_STOPBITS_1;
	uart_handle->Init.Parity = UART_PARITY_NONE;
	uart_handle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	if (HAL_UART_Init(uart_handle) != HAL_OK)
	{
		return 1;
	}
	return 0;
}

/**
 * @brief Initializes new USART message
 * @retval USART_MessageTypeDef
 */
USART_MessageTypeDef NUCLEO_USART_vCOM_CreateMessage() {
	USART_MessageTypeDef msg = {{0}, USART_MAX_MSG_LEN, idle, NUCLEO_USART_vCOM_AppendInt,
			NUCLEO_USART_vCOM_AppendFloat,
			NUCLEO_USART_vCOM_AppendStr,
			NUCLEO_USART_vCOM_Reset
	};

	return msg;
}

/**
 * @brief Append integer to a message
 * @param i: integer
 * @param msg: message
 * @retval None
 */
void NUCLEO_USART_vCOM_AppendInt(int i, USART_MessageTypeDef * msg) {
	char iStr[USART_MAX_MSG_LEN/2];
	int len = sprintf(iStr, "%d", i);

	strncat(msg->data, iStr, len);
}

/**
 * @brief Append float to a message
 * @param f: float
 * @param msg: message
 * @retval None
 */
void NUCLEO_USART_vCOM_AppendFloat(float f, USART_MessageTypeDef * msg) {
	char fStr[USART_MAX_MSG_LEN/2];
	int len = sprintf(fStr, "%0.2f", (double) f);

	strncat(msg->data, fStr, len);
}

/*
 * @brief Append string to a message
 * @param str: string
 * @param msg: message
 * @retval None
 */
void NUCLEO_USART_vCOM_AppendStr(char * str, USART_MessageTypeDef * msg) {
	int len = strlen(str);
	strncat(msg->data, str, len);
}

/*
 * @brief Clears message data
 * @param msg: message
 * @retval None
 */
void NUCLEO_USART_vCOM_Reset(USART_MessageTypeDef * msg) {
	memset(msg->data, 0, USART_MAX_MSG_LEN);
}

/*
 * @brief Clears console contents
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_Clear() {
	char * clr_str = "\x1b[2J\x1b[1;1H";
	int len = strlen(clr_str);
	HAL_StatusTypeDef status = HAL_UART_Transmit(uart_handle, (uint8_t *) clr_str, len, USART_COM_TIMEOUT);

	return status;
}

/*
 * @brief Write message to virtual COM port stream as is
 * @param msg: message
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_Write(USART_MessageTypeDef * msg) {
	HAL_StatusTypeDef status = HAL_UART_Transmit(uart_handle, (uint8_t *) msg->data, USART_MAX_MSG_LEN, USART_COM_TIMEOUT);

	return status;
}

/*
 * @brief Write newline terminated message to virtual COM port stream
 * param msg: message
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_WriteLine(USART_MessageTypeDef * msg) {
	char msg_ln[USART_MAX_MSG_LEN + 2];
	memcpy(msg_ln, msg->data, USART_MAX_MSG_LEN);
	strncat(msg_ln, "\n", 2);

	HAL_StatusTypeDef status = HAL_UART_Transmit(uart_handle, (uint8_t *) msg_ln, USART_MAX_MSG_LEN, USART_COM_TIMEOUT);

	return status;
}

/**
 * @brief Flush and write newline terminated message to virtual COM port stream
 * @param msg: message
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_FlushWriteLine(USART_MessageTypeDef * msg) {
	if (msg->flag == wait) {
		msg->flag = flush_write;
		return HAL_BUSY;
	}

	char msg_ln[USART_MAX_MSG_LEN + 2];
	memcpy(msg_ln, msg->data, USART_MAX_MSG_LEN);
	strncat(msg_ln, "\n", 2);

	HAL_StatusTypeDef status = HAL_UART_Transmit(uart_handle, (uint8_t *) msg_ln, USART_MAX_MSG_LEN, USART_COM_TIMEOUT);
	msg->Reset(msg);

	return status;
}

/**
 * @brief Write single character to virtual COM port stream
 * @param c: character
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_WriteChar(char c) {
	return HAL_UART_Transmit(uart_handle, (uint8_t *) &c, 1, USART_COM_TIMEOUT);
}

/**
 * @brief Performs a quick write to virtual COM stream
 * @param fmt_str: message content as formatted string
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_QuickWrite(char * fmt_str) {
	USART_MessageTypeDef tmp = NUCLEO_USART_vCOM_CreateMessage();
	tmp.AppendStr(fmt_str, &tmp);
	NUCLEO_USART_vCOM_FlushWrite(&tmp);
}

/**
 * @brief Performs a quick write line to virtual COM stream
 * @param fmt_str: message content as formatted string
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_QuickWriteLine(char * fmt_str) {
	USART_MessageTypeDef tmp = NUCLEO_USART_vCOM_CreateMessage();
	tmp.AppendStr(fmt_str, &tmp);
	NUCLEO_USART_vCOM_FlushWriteLine(&tmp);
}

/**
 * @brief Reads line of characters from virtual COM stream
 * @param msg: message
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_ReadLine(USART_MessageTypeDef * msg) {
	if (msg->flag == idle) msg->flag = wait;
	p_msg = msg;
	return HAL_UARTEx_ReceiveToIdle_IT(uart_handle, (uint8_t *) rx_buffer, USART_MAX_MSG_LEN);
}
