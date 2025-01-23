/*
 * nucleo_usart_handler.h
 *
 *  Created on: Jan 6, 2025
 *      Author: marek novotny
 */

#ifndef __NUCLEO_USART_PROCESS_H
#define __NUCLEO_USART_PROCESS_H

#include "main.h"

HAL_StatusTypeDef NUCLEO_USART_ProcessInit(UART_HandleTypeDef *huart/*,
		DMA_HandleTypeDef *hdmarx, DMA_HandleTypeDef *hdmatx*/);
HAL_StatusTypeDef NUCLEO_USART_Process(UART_HandleTypeDef *huart);


#endif /* __NUCLEO_USART_PROCESS_H */
