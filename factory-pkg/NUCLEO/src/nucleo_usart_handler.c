/*
 * nucleo_usart_handler.c
 *
 *  Created on: Jan 3, 2025
 *      Author: marek novotny
 */

#include <string.h>
#include "nucleo_usart_handler.h"
#include "stest01a1_control_driver.h"
#include "do41a1_control_driver.h"

/**
 * TODO deprecated function
 * @brief Scans for serial input
 * @param huart: uart handle
 * @retval None
 */
void NUCLEO_USART_vCOM_Scan(UART_HandleTypeDef * huart) {
	if (uart_handle == NULL) {
		NUCLEO_USART_vCOM_Config(huart);
		cmd = NUCLEO_USART_vCOM_CreateMessage();
		msg = NUCLEO_USART_vCOM_CreateMessage();

		msg.Reset(&msg);
		msg.AppendStr("***** IPS EVALUATION DIAGNOSTIC TOOL *****\n", &msg);
		msg.AppendStr("* Type help for usage information", &msg);
		NUCLEO_USART_vCOM_WriteLine(&msg);
		NUCLEO_USART_vCOM_WriteChar('\n');
	}

	if (cmd.flag == idle) NUCLEO_USART_vCOM_ReadLine(&cmd);
}

/**
 * @brief Routes received message to correct board resolver
 * @param msg: command message
 * @retval None
 */
void NUCLEO_USART_vCOM_Route(USART_MessageTypeDef * msg) {
	char * raw = &(msg->data[0]);
	if (raw[0] == '\r' || raw[0] == '\n') raw = raw + 1;
	if (strlen(raw) > 0) {
		if (strcmp(raw, "clear") == 0) NUCLEO_USART_vCOM_Clear();
//		else if (strncmp(raw, "fsm01m1.", 8) == 0) FSM01M1_CTRL_Handle(msg);
		else if (strncmp(raw, "stest01a1.", 10) == 0) STEST01A1_CTRL_Handle(msg);
		else if (strncmp(raw, "do41a1.", 7) == 0) DO41A1_CTRL_Handle(msg);
		else NUCLEO_USART_vCOM_QuickWriteLine("Device not found");
	}

	msg->Reset(msg);
	msg->flag = idle;
}

/**
 * @brief Overrides HAL_UARTEx_RxEventCallback
 * @param huart: uart handle
 * @param Size: size of received data
 * @retval None
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	if (huart == uart_handle) {
		cmd.AppendStr(rx_buffer, &cmd);
		memset(rx_buffer, 0, USART_MAX_MSG_LEN);

		switch (cmd.flag) {
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
		}
	}
}
