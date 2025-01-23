/**
  ******************************************************************************
  * @file    stest01a1_driver.c
  * @author  ST Power Application Laboratory
  * @version V1.0.0
  * @brief   Provides functions for interactive board control and measurement
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "stest01a1_driver.h"
#include "stest01a1_mapping.h"
#include "nucleo_tim_driver.h"
#include "nucleo_usart_driver.h"
#include "nucleo_gpio_driver.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum CTRL_IO_t {
	all,
	out,
	ipd,
	flt1,
	flt2
} CTRL_IOTypeDef;

typedef enum CTRL_Action_t {
	on,
	off,
	state,
	states,
	level,
	levels
} CTRL_ActionTypeDef;


typedef enum CTRL_Format_t {
	numerical,
	logical
} CTRL_FormatTypeDef;

/* Private variables ---------------------------------------------------------*/
_Bool STEST01A1_FLT1 = 0;
_Bool STEST01A1_FLT2 = 0;
double DEMAG_TICKS = 0;

/* buffer for command tokenization */
static char * token_ctx;

/* Private function prototypes -----------------------------------------------*/
void STEST01A1_CTRL_splash_msg();
void STEST01A1_CTRL_read(CTRL_IOTypeDef dev, CTRL_FormatTypeDef fmt);
void STEST01A1_CTRL_reset_devices();
void STEST01A1_CTRL_switch(CTRL_IOTypeDef dev, CTRL_ActionTypeDef act);
void STEST01A1_CTRL_resolve(char * cmd, CTRL_IOTypeDef target);
void STEST01A1_CTRL_levels();
void STEST01A1_CTRL_states();
void STEST01A1_CTRL_help();
void STEST01A1_CTRL_list_devices();
void STEST01A1_CTRL_list_actions();
void STEST01A1_CTRL_single_pulse(CTRL_IOTypeDef dev, uint32_t duration);
void STEST01A1_CTRL_demag_stat();
void STEST01A1_CTRL_PWM_Config(char * cfg);
void STEST01A1_CTRL_PWM_Run(char * cfg);

/* Exported functions --------------------------------------------------------*/

/**
 * @brief Handles messages routed to the board
 * @param msg: message
 * @retval None
 */
void STEST01A1_CTRL_Handle(USART_MessageTypeDef * msg) {
	STEST01A1_CTRL_resolve(msg->data, all);
}

/**
 * @brief Provides command resolution services
 * @param cmd: command
 * @param target: device
 * @retval None
 */
void STEST01A1_CTRL_resolve(char * cmd, CTRL_IOTypeDef target) {
	if (cmd[0] == '\r' || cmd[0] == '\n') cmd = cmd + 1;
	char * arg = (char *) strtok_r(cmd, " ", &token_ctx);

	if (arg == NULL) return;
	arg[strcspn(arg, "\r\n")] = '\0';
	char * prefix = "stest01a1.";
	size_t shift = strstr(arg, prefix) ? strlen(prefix) : 0;
	arg = &arg[shift];

	if (arg[0] == '\0') return;
	else if (strcmp(arg, "out") == 0) STEST01A1_CTRL_resolve(NULL, out);
	else if (strcmp(strchr(arg, '.') + 1, "pwm") == 0) STEST01A1_CTRL_PWM_Config(arg);
	else if (strcmp(strchr(arg, '.') + 1, "pwm.on") == 0) STEST01A1_CTRL_PWM_Run(arg);
	else if (strcmp(arg, "flt1") == 0) STEST01A1_CTRL_resolve(NULL, flt1);
	else if (strcmp(arg, "flt2") == 0) STEST01A1_CTRL_resolve(NULL, flt2);
	else if (strcmp(arg, "demag_stat") == 0) STEST01A1_CTRL_demag_stat();
//	else if (strcmp(arg, "on") == 0) STEST01A1_PULSE_PulseGen_TIM_High(OUT_TMR);
//	else if (strcmp(arg, "off") == 0) STEST01A1_PULSE_PulseGen_TIM_Low(OUT_TMR);
	else if (strcmp(arg, "pulse") == 0) {
//		STEST01A1_PULSE_PulseGen_TIM_High(OUT_TMR);
//		HAL_Delay(1000);
//		STEST01A1_PULSE_PulseGen_TIM_Low(OUT_TMR);
	}
	else if (strcmp(arg, "pwm") == 0) {
		NUCLEO_TIM_PeriodicPulse_Config(STEST01A1_IN_Handle, STEST01A1_IN_TIMx, STEST01A1_IN_CHx, 1000, 500, 200);
		NUCLEO_TIM_PeriodicPulse_Start(STEST01A1_IN_Handle, STEST01A1_IN_CHx);
	}
	else if (strcmp(arg, "single") == 0) STEST01A1_CTRL_single_pulse(target, 1000);
	else if (strcmp(arg, "state") == 0) STEST01A1_CTRL_read(target, logical);
	else if (strcmp(arg, "level") == 0) STEST01A1_CTRL_read(target, numerical);
	else if (strcmp(arg, "levels") == 0) STEST01A1_CTRL_levels();
	else if (strcmp(arg, "states") == 0) STEST01A1_CTRL_states();
	else if (strcmp(arg, "help") == 0) STEST01A1_CTRL_help();
	else if (strcmp(arg, "functions") == 0) STEST01A1_CTRL_list_devices();
	else if (strcmp(arg, "actions") == 0) STEST01A1_CTRL_list_actions();
	else {
		msg.Reset(&msg);
		msg.AppendStr(&msg, "Invalid command, no actions performed");
		NUCLEO_USART_WriteLine(&msg);
	}
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief Prints help message
 * @retval None
 */
void STEST01A1_CTRL_help() {
	msg.Reset(&msg);
	msg.AppendStr(&msg, "[function] [action] - applies action to a function\n"
			"[global_action] - applies action to all functions\n"
			"- Type 'functions' for function list\n"
			"- Type 'actions' for action list\n"
			"- Type 'clear' to clear text from terminal\n"
			/*"- Use 'x' in device identifiers for numerical wildcard (e.g. outx selects all outputs)\n"*/);
	NUCLEO_USART_Write(&msg);
}

/**
 * @brief Prints list of devices
 * @retval None
 */
void STEST01A1_CTRL_list_devices() {

	msg.Reset(&msg);
	for (int i = out; i <= flt2; i += 1) {
		switch (i) {
			case out:
				msg.AppendStr(&msg, "out\n");
				break;
			case flt1:
				msg.AppendStr(&msg, "flt1\n");
				break;
			case flt2:
				msg.AppendStr(&msg, "flt2\n");
				break;
			default:
				break;
		}
	}

	NUCLEO_USART_Write(&msg);
}

/**
 * @brief Prints list of actions
 * @retval None
 */
void STEST01A1_CTRL_list_actions() {

	msg.Reset(&msg);
	for (int i = on; i <= levels; i += 1) {
		switch (i) {
			case on:
				msg.AppendStr(&msg, "on\n");
				break;
			case off:
				msg.AppendStr(&msg, "off\n");
				msg.AppendStr(&msg, "off [global]\n");
				break;
			case state:
				msg.AppendStr(&msg, "state - returns if function is on or off\n");
				break;
			case states:
				msg.AppendStr(&msg, "states [global]\n");
				break;
			case level:
				msg.AppendStr(&msg, "level - returns numeric representation of function state"
						"(integer 1 and 0 denote logical state, decimals denote physical state)\n");
				break;
			case levels:
				msg.AppendStr(&msg, "levels [global]\n");
				break;
			default:
				break;
		}
	}

	NUCLEO_USART_Write(&msg);
}

/**
 * @brief Provides device switching services
 * @param dev: device
 * @param act: action
 * @retval None
 */
void STEST01A1_CTRL_switch(CTRL_IOTypeDef dev, CTRL_ActionTypeDef act) {
	switch (dev) {
		case out:
			if (act == on) STEST01A1_CTRL_OUT_ON();
			else STEST01A1_CTRL_OUT_OFF();
			break;
		case all:
			if (act == off) STEST01A1_CTRL_OUT_OFF();
		default:
			break;
	}
}

/**
 * @brief Provides device single pulse services
 * @param dev: device
 * @param act: action
 * @retval None
 */
void STEST01A1_CTRL_single_pulse(CTRL_IOTypeDef dev, uint32_t duration) {
	switch (dev) {
		case out:
			STEST01A1_CTRL_OUT_ON();
			HAL_Delay(duration);
			STEST01A1_CTRL_OUT_OFF();
			break;
		default:
			break;
	}
}

/**
 * @brief Provides configuration for PWM timer
 * @param cfg: configuration string
 * @retval None
 */
void STEST01A1_CTRL_PWM_Config(char * cfg) {
//	strtok(cfg, ".");
	CTRL_IOTypeDef specifier = strcmp(strtok(cfg, "."), "out") == 0 ? out : all;
	char * remainder = strtok(NULL, " ");

	char * tick = strtok(NULL, " ");
	char * period = strtok(NULL, " ");
	char * pulse = strtok(NULL, " ");

	uint32_t tick_micros = atoi(tick);
	uint32_t period_ticks = atoi(period);
	uint32_t pulse_ticks = atoi(pulse);

	if (pulse_ticks > period_ticks) {
		NUCLEO_USART_WriteStringLine("Pulse cannot have longer duration than period");
		return;
	}

	switch (specifier) {
		case out:
			NUCLEO_TIM_PeriodicPulse_Config(STEST01A1_IN_Handle, STEST01A1_IN_TIMx, STEST01A1_IN_CHx, tick_micros, period_ticks, pulse_ticks);
			break;
		case all:
		default:
			break;
	}
}

/**
 * @brief Runs the configured PWM timer
 * @param cfg: configuration string
 * @retval None
 */
void STEST01A1_CTRL_PWM_Run(char * cfg) {
	strtok(cfg, ".");
	CTRL_IOTypeDef specifier = strcmp(strtok(NULL, "."), "out") == 0 ? out : all;

	switch (specifier) {
		case out:
			NUCLEO_TIM_PeriodicPulse_Start(STEST01A1_IN_Handle, STEST01A1_IN_CHx);
			break;
		case all:
		default:
			break;
	}
}

/**
 * @brief Provides device reading services
 * @param dev: device
 * @param fmt: reading formatting
 * @retval None
 */
void STEST01A1_CTRL_read(CTRL_IOTypeDef dev, CTRL_FormatTypeDef fmt) {
	msg.Reset(&msg);

	int logic = -1;
	float reading = -1.0;

	switch (dev) {
		case out:
			logic = (int) HAL_GPIO_ReadPin(STEST01A1_IN_GPIO_Port, STEST01A1_IN_GPIO_Pin);
			msg.AppendStr(&msg, "OUT \t\t = ");
			break;
		case flt1:
			logic = (int) STEST01A1_FLT1;
			STEST01A1_FLT1 = 0;
			msg.AppendStr(&msg, "FLT1 \t\t = ");
			break;
		case flt2:
			logic = (int) STEST01A1_FLT2;
			STEST01A1_FLT2 = 0;
			msg.AppendStr(&msg, "FLT2 \t\t = ");
			break;
		default:
			break;
	}

	if (fmt == numerical) {
		if (reading != -1.0f) msg.AppendFloat(&msg, reading);
		else if (logic != -1) msg.AppendInt(&msg, logic);
	}
	else if (fmt == logical) {
		if (reading >= NUCLEO_GPIO_NOMINAL_VOLTAGE_THRESHOLD || logic == 1) msg.AppendStr(&msg, "(on)");
		else if (reading <= NUCLEO_GPIO_ZERO_VOLTAGE_THRESHOLD || logic == 0) msg.AppendStr(&msg, "(off)");
		else msg.AppendStr(&msg, "(?)");
	}

	msg.AppendStr(&msg, "\n");
	NUCLEO_USART_Write(&msg);
}

/**
 * @brief Shows demagnetization statistics
 * @retval None
 */
void STEST01A1_CTRL_demag_stat() {
	double elapsed_time = DEMAG_TICKS / 16e6;
	double v_demag = 48;
	double v_init = 24;
	double r = 12;

	uint32_t inductance = elapsed_time * r / log((v_demag + v_init) / v_demag);

	msg.AppendStr(&msg, "Demagnetization duration: ");
	msg.AppendFloat(&msg, elapsed_time * 1000);
	msg.AppendStr(&msg, " ms, ");
	msg.AppendStr(&msg, "Inductance: ");
	msg.AppendFloat(&msg, inductance);
	msg.AppendStr(&msg, " H");
	NUCLEO_USART_WriteLine(&msg);
	msg.Reset(&msg);
	DEMAG_TICKS = 0;
}

/**
 * @brief Prints voltage and logical levels of all devices
 * @retval None
 */
void STEST01A1_CTRL_levels() {
	for(int i = flt1; i <= flt2; i += 1)
		STEST01A1_CTRL_read(i, numerical);
}

/**
 * @brief Prints switch states of all devices
 * @note '?' output symbol means switch state can not be determined
 * @retval None
 */
void STEST01A1_CTRL_states() {
	for(int i = flt1; i <= flt2; i += 1)
		STEST01A1_CTRL_read(i, logical);
}

void STEST01A1_CTRL_OUT_ON() {
	HAL_GPIO_WritePin(STEST01A1_IN_GPIO_Port, STEST01A1_IN_GPIO_Pin, GPIO_PIN_SET);
}

void STEST01A1_CTRL_OUT_OFF() {
	HAL_GPIO_WritePin(STEST01A1_IN_GPIO_Port, STEST01A1_IN_GPIO_Pin, GPIO_PIN_RESET);
}

void STEST01A1_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	STEST01A1_FLT1 = 0;
	STEST01A1_FLT2 = 0;
	if (GPIO_Pin == STEST01A1_FLT1_GPIO_Pin) {
		STEST01A1_FLT1 = 1;
	} else if (GPIO_Pin == STEST01A1_FLT2_GPIO_Pin) {
		STEST01A1_FLT2 = 1;
	}
}
