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


/* Exported variables --------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/

/**
 * @brief Initializes new USART message
 * @retval USART_MessageTypeDef
 */
USART_MessageTypeDef NUCLEO_USART_vCOM_CreateMessage() {
	USART_MessageTypeDef msg = {{0}, USART_MSG_MAX_LEN, ready, NUCLEO_USART_vCOM_AppendInt,
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
void NUCLEO_USART_vCOM_AppendInt(int i, USART_MessageTypeDef * self) {
	char iStr[USART_MSG_MAX_LEN/2];
	int len = sprintf(iStr, "%d", i);

	strncat(self->data, iStr, len);
}

/**
 * @brief Append float to a message
 * @param f: float
 * @param msg: message
 * @retval None
 */
void NUCLEO_USART_vCOM_AppendFloat(float f, USART_MessageTypeDef * self) {
	char fStr[USART_MSG_MAX_LEN/2];
	int len = sprintf(fStr, "%0.2f", (double) f);

	strncat(self->data, fStr, len);
}

/*
 * @brief Append string to a message
 * @param str: string
 * @param msg: message
 * @retval None
 */
void NUCLEO_USART_vCOM_AppendStr(char * str, USART_MessageTypeDef * self) {
	int len = strlen(str);

	strncat(self->data, str, len);
}

/*
 * @brief Clears message data
 * @param msg: message
 * @retval None
 */
void NUCLEO_USART_vCOM_Reset(USART_MessageTypeDef * self) {
	memset(self->data, 0, USART_MSG_MAX_LEN);
	/*TODO might reset also all other data items to default? */
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
	HAL_StatusTypeDef status = HAL_UART_Transmit(uart_handle, (uint8_t *) msg->data, USART_MSG_MAX_LEN, USART_COM_TIMEOUT);
	return status;
}

/*
 * @brief Write newline terminated message to virtual COM port stream
 * param msg: message
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_WriteLine(USART_MessageTypeDef * msg) {
	char msg_ln[USART_MSG_MAX_LEN + USART_EOL_LEN];
	memcpy(msg_ln, msg->data, USART_MSG_MAX_LEN);
	strncat(msg_ln, "\n", USART_EOL_LEN);

	HAL_StatusTypeDef status = HAL_UART_Transmit(uart_handle, (uint8_t *) msg_ln, (USART_MSG_MAX_LEN + USART_EOL_LEN), USART_COM_TIMEOUT);
	return status;
}

/**
 * TODO Deprecated function - to be replaced with NUCLEO_USART_WriteStringLine
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
 * @brief Flush and write newline terminated message to virtual COM port stream
 * @param msg: message
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_FlushWriteLine(USART_MessageTypeDef * msg) {
	if (msg->flag == wait) {
		msg->flag = flush_write;
		/* TODO Problematic: flag goes to flush_write, but nothing is transmitted */
		return HAL_BUSY;
	}

	char msg_ln[USART_MSG_MAX_LEN + USART_EOL_LEN];
	memcpy(msg_ln, msg->data, USART_MSG_MAX_LEN);
	strncat(msg_ln, "\n", USART_EOL_LEN);

	HAL_StatusTypeDef status = HAL_UART_Transmit(uart_handle, (uint8_t *) msg_ln, USART_MSG_MAX_LEN, USART_COM_TIMEOUT);
	msg->Reset(msg);

	return status;
}

/**
 * @brief	Write single character to virtual COM port stream
 * @param	c: character
 * @retval	HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_vCOM_WriteChar(char c) {
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_UART_Transmit(uart_handle, (uint8_t *) &c, 1, USART_COM_TIMEOUT);
	return status;
}

/**
 * @brief	Write char string to virtual COM port stream
 * @param	str: pointer to string
 * @retval	HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_WriteString(char *str) {
	HAL_StatusTypeDef status = HAL_OK;
	int len = strlen(str);

	if (len > USART_MSG_MAX_LEN) {
		status = HAL_ERROR;
	} else {
		status = HAL_UART_Transmit(uart_handle, (uint8_t *) str, len,
				USART_COM_TIMEOUT);
	}
	return status;
}

/**
 * @brief	Write char string to virtual COM port stream
 * @param	str: pointer to string
 * @retval	HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_WriteStringLine(char *str) {
	HAL_StatusTypeDef status = HAL_OK;
	char str2send[USART_MSG_MAX_LEN];
	int len = strlen(str);

	if (len < (USART_MSG_MAX_LEN - USART_EOL_LEN)) {
		memcpy(str2send, str, USART_MSG_MAX_LEN);
		strncat(str2send, "\n", USART_EOL_LEN);
		status = NUCLEO_USART_WriteString(str2send);
	} else {
		status = HAL_ERROR;
	}
	return status;
}
/**
 * TODO is this function needed?
 * @brief Performs a quick write to virtual COM stream
 * @param fmt_str: message content as formatted string
 * @retval HAL_StatusTypeDef
 */
//HAL_StatusTypeDef NUCLEO_USART_vCOM_QuickWrite(char * fmt_str) {
//	USART_MessageTypeDef tmp = NUCLEO_USART_vCOM_CreateMessage();
//	tmp.AppendStr(fmt_str, &tmp);
//	NUCLEO_USART_vCOM_FlushWrite(&tmp);
//}

/**
 * @brief Reads a line of characters from virtual COM stream
 * @param msg: message
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef NUCLEO_USART_ReadLine(USART_MessageTypeDef * msg) {
	HAL_StatusTypeDef status = HAL_OK;

	if (msg->flag == ready) {
		status = HAL_UARTEx_ReceiveToIdle_IT(uart_handle, (uint8_t*) rx_buffer,
				USART_MSG_MAX_LEN);
	} else {
		status = HAL_BUSY;
	}
	return status;
}

