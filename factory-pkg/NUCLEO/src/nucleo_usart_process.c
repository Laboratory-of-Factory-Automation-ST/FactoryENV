/*
 * nucleo_usart_process.c
 *
 *  Created on: Jan 3, 2025
 *      Author: marek novotny
 */

#include <string.h>
#include "nucleo_usart_process.h"
#include "nucleo_usart_driver.h"
#include <do41a1_driver.h>
#include <stest01a1_driver.h>

/* Exported variables --------------------------------------------------------*/
UART_HandleTypeDef *uart_handle = NULL;
char rx_buffer[USART_MSG_MAX_LEN];
USART_MessageTypeDef msg;
USART_MessageTypeDef cmd;

/**
 * @brief	Nucleo UART state machine init
 * @param 	huart	Pointer to an initialized virtual COM Handle
 * @retval 	HAL status
 */
HAL_StatusTypeDef NUCLEO_USART_ProcessInit(UART_HandleTypeDef *huart/*,
		DMA_HandleTypeDef *hdmarx, DMA_HandleTypeDef *hdmatx*/) {

	HAL_StatusTypeDef status = HAL_OK;

	if(huart == NULL) {
		return HAL_ERROR;
	}
	else {

		/* TODO is uart_handle needed? */
		uart_handle = huart;
//		hdma_rx = hdmarx;
//		hdma_tx = hdmatx;

		cmd = NUCLEO_USART_CreateMessage();
		msg = NUCLEO_USART_CreateMessage();
		NUCLEO_USART_ClearScreen();

		msg.Reset(&msg);
		msg.AppendStr(&msg, "***** IPS EVALUATION DIAGNOSTIC TOOL *****\n");
		msg.AppendStr(&msg, "* Type 'help' for usage information");

		status = NUCLEO_USART_WriteLine(&msg);

		return status;
	}
}

/**
 * @brief	COM state machine process
 * @param	huart	related UART peripheral
 * @retval	HAL status
 */
HAL_StatusTypeDef NUCLEO_USART_Process(UART_HandleTypeDef * huart) {
	HAL_StatusTypeDef status = HAL_OK;

	status = NUCLEO_USART_ReadLine(&cmd);

	return status;
}

/**
 * @brief Routes received message to correct board resolver
 * @param msg: command message
 * @retval None
 */
void NUCLEO_USART_Route(USART_MessageTypeDef * msg) {
	char * raw = &(msg->data[0]);
	if (raw[0] == '\r' || raw[0] == '\n') raw = raw + 1;
	if (strlen(raw) > 0) {
		if (strcmp(raw, "clear") == 0) NUCLEO_USART_ClearScreen();
//		else if (strncmp(raw, "fsm01m1.", 8) == 0) FSM01M1_CTRL_Handle(msg);
		else if (strncmp(raw, "stest01a1.", 10) == 0) STEST01A1_CTRL_Handle(msg);
		else if (strncmp(raw, "do41a1.", 7) == 0) DO41A1_CTRL_Handle(msg);
		else NUCLEO_USART_WriteStringLine("Device not found");
	}

	msg->Reset(msg);
	msg->flag = ready;
}

/**
 * @brief Overrides HAL_UARTEx_RxEventCallback
 * @param huart: uart handle
 * @param Size: size of received data
 * @retval None
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	if (huart == uart_handle) {
		cmd.Reset(&cmd);
		cmd.AppendStr(&cmd, rx_buffer);
		memset(rx_buffer, 0, USART_MSG_MAX_LEN);

		NUCLEO_USART_Route(&cmd);

/* TODO consolidate state machine: to be related to resource (USART) instead of Message  */
/*		switch (cmd.flag) {
			case write:
				NUCLEO_USART_vCOM_Write(&cmd);
				break;
			case flush_write:
				NUCLEO_USART_vCOM_FlushWriteLine(&cmd);
				break;
			case wait:
				NUCLEO_USART_vCOM_Route(&cmd);
				break;
			case ready:
				break;
			default:
				break;
		}*/
	}
}
