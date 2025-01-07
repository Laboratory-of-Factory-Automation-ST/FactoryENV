/*
 * nucleo_gpio_driver.h
 *
 *  Created on: Dec 6, 2024
 *      Author: marek novotny
 */

#ifndef DRIVERS_BSP_NUCLEO_INC_NUCLEO_GPIO_DRIVER_H_
#define DRIVERS_BSP_NUCLEO_INC_NUCLEO_GPIO_DRIVER_H_

#include "main.h"

GPIO_TypeDef * NUCLEO_GPIO_GetPortHandle(char * GPIO_HandleString);
uint16_t NUCLEO_GPIO_GetPinHandle(char * GPIO_HandleString);
void NUCLEO_GPIO_ActivatePin(char * GPIO_HandleString);
void NUCLEO_GPIO_DeactivatePin(char * GPIO_HandleString);
GPIO_PinState NUCLEO_GPIO_Read(char * GPIO_HandleString);

#endif /* DRIVERS_BSP_NUCLEO_INC_NUCLEO_GPIO_DRIVER_H_ */
