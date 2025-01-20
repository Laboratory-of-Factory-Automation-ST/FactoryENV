/*
 * nucleo_usart_handler.h
 *
 *  Created on: Jan 6, 2025
 *      Author: marek novotny
 */

#ifndef NUCLEO_USART_HANDLER_H_
#define DNUCLEO_USART_HANDLER_H_

#include "nucleo_usart_driver.h"

HAL_StatusTypeDef NUCLEO_USART_ProcessInit(UART_HandleTypeDef *huart/*,
		DMA_HandleTypeDef *hdmarx, DMA_HandleTypeDef *hdmatx*/);
HAL_StatusTypeDef NUCLEO_USART_Process(UART_HandleTypeDef *huart);
HAL_StatusTypeDef NUCLEO_USART_ReadLine(USART_MessageTypeDef * msg);

#endif /* NUCLEO_USART_HANDLER_H_ */
