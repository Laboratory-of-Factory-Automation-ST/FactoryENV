/*
 * nucleo_gpio_driver.c
 *
 *  Created on: 18. 6. 2024
 *      Author: marek novotny
 */
#include <inttypes.h>
#include "nucleo_gpio_driver.h"
#include "stest01a1_control_driver.h"

GPIO_TypeDef * NUCLEO_GPIO_GetPortHandle(char * GPIO_HandleString) {
	char port_handle_str = GPIO_HandleString[1];

	GPIO_TypeDef * port_handle = NULL;
	switch(port_handle_str) {
		 case 'a':
		 case 'A':
			 port_handle = GPIOA;
			 break;
		 case 'b':
		 case 'B':
			 port_handle = GPIOB;
			 break;
		 case 'c':
		 case 'C':
			 port_handle = GPIOC;
			 break;
		 case 'd':
		 case 'D':
			 port_handle = GPIOD;
			 break;
		 case 'e':
		 case 'E':
			 port_handle = GPIOE;
			 break;
		 case 'h':
		 case 'H':
			 port_handle = GPIOH;
			 break;
		 default:
			 break;
	}

	return port_handle;
}

uint16_t NUCLEO_GPIO_GetPinHandle(char * GPIO_HandleString) {
	char pin_handle_str = GPIO_HandleString[2];

	char * ptr;
	uint16_t pin_handle = 1 << strtoumax(&pin_handle_str, &ptr, 10);
	return pin_handle;
}

void NUCLEO_GPIO_ActivatePin(char * GPIO_HandleString) {
	HAL_GPIO_WritePin(NUCLEO_GPIO_GetPortHandle(GPIO_HandleString), NUCLEO_GPIO_GetPinHandle(GPIO_HandleString), GPIO_PIN_SET);
}

void NUCLEO_GPIO_DeactivatePin(char * GPIO_HandleString) {
	HAL_GPIO_WritePin(NUCLEO_GPIO_GetPortHandle(GPIO_HandleString), NUCLEO_GPIO_GetPinHandle(GPIO_HandleString), GPIO_PIN_RESET);
}

GPIO_PinState NUCLEO_GPIO_Read(char * GPIO_HandleString) {
	return HAL_GPIO_ReadPin(NUCLEO_GPIO_GetPortHandle(GPIO_HandleString), NUCLEO_GPIO_GetPinHandle(GPIO_HandleString));
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	FSM01M1_GPIO_EXTI_Callback(GPIO_Pin);
	STEST01A1_GPIO_EXTI_Callback(GPIO_Pin);
}
