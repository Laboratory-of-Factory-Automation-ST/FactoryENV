/**
  ******************************************************************************
  * @file    do41a1_control_driver.c
  * @brief   This file implements interfaces for control of
  *			 X-NUCLEO-DO41A1 board.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "do41a1_control_driver.h"
#include "nucleo_tim_driver.h"
#include "do41a1_mapping.h"
#include "nucleo_gpio_driver.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum CTRL_IO_t {
	all,
	out1,
	out2,
	out3,
	out4,
	outx,
	status1,
	status2,
	status3,
	status4
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
_Bool DO41A1_STATUS1 = 0;
_Bool DO41A1_STATUS2 = 0;
_Bool DO41A1_STATUS3 = 0;
_Bool DO41A1_STATUS4 = 0;

/* buffer for command tokenization */
static char * token_ctx;

/* Private function prototypes -----------------------------------------------*/
void DO41A1_CTRL_splash_msg();
void DO41A1_CTRL_read(CTRL_IOTypeDef dev, CTRL_FormatTypeDef fmt);
void DO41A1_CTRL_reset_io();
void DO41A1_CTRL_switch(CTRL_IOTypeDef dev, CTRL_ActionTypeDef act);
void DO41A1_CTRL_resolve(char * cmd, CTRL_IOTypeDef target);
void DO41A1_CTRL_levels();
void DO41A1_CTRL_states();
void DO41A1_CTRL_help();
void DO41A1_CTRL_list_io();
void DO41A1_CTRL_list_actions();
void DO41A1_CTRL_single_pulse(CTRL_IOTypeDef dev, uint32_t duration);
void DO41A1_CTRL_demag_stat();
void DO41A1_CTRL_PWM_Config(CTRL_IOTypeDef io, char * cfg);
void DO41A1_CTRL_PWM_Run(CTRL_IOTypeDef io);

/* Exported constants --------------------------------------------------------*/
const struct DO41A1_IO do41a1_io = {
	all,
	out1,
	out2,
	out3,
	out4,
	outx,
	status1,
	status2,
	status3,
	status4
};

/* Exported functions --------------------------------------------------------*/

/**
 * @brief Handles messages routed to the board
 * @param msg: message
 * @retval None
 */
void DO41A1_CTRL_Handle(USART_MessageTypeDef * msg) {
	DO41A1_CTRL_resolve(msg->data, all);
}

/**
 * @brief Provides command resolution services
 * @param cmd: command
 * @param target: io
 * @retval None
 */
void DO41A1_CTRL_resolve(char * cmd, CTRL_IOTypeDef target) {
	if (cmd[0] == '\r' || cmd[0] == '\n') cmd = cmd + 1;
	char * arg = (char *) strtok_r(cmd, " ", &token_ctx);

	if (arg == NULL) return;
	arg[strcspn(arg, "\r\n")] = '\0';
	char * prefix = "do41a1.";
	size_t shift = strstr(arg, prefix) ? strlen(prefix) : 0;
	arg = &arg[shift];

	if (arg[0] == '\0') return;
	else if (strcmp(arg, "out1") == 0) DO41A1_CTRL_resolve(NULL, out1);
	else if (strcmp(arg, "out2") == 0) DO41A1_CTRL_resolve(NULL, out2);
	else if (strcmp(arg, "out3") == 0) DO41A1_CTRL_resolve(NULL, out3);
	else if (strcmp(arg, "out4") == 0) DO41A1_CTRL_resolve(NULL, out4);
	else if (strcmp(strchr(arg, '.') + 1, "pwm") == 0) DO41A1_CTRL_PWM_Config(target, arg);
	else if (strcmp(strchr(arg, '.') + 1, "pwm.on") == 0) DO41A1_CTRL_PWM_Run(target);
	else if (strcmp(arg, "status1") == 0) DO41A1_CTRL_resolve(NULL, status1);
	else if (strcmp(arg, "status2") == 0) DO41A1_CTRL_resolve(NULL, status2);
	else if (strcmp(arg, "status3") == 0) DO41A1_CTRL_resolve(NULL, status3);
	else if (strcmp(arg, "status4") == 0) DO41A1_CTRL_resolve(NULL, status4);
	else if (strcmp(arg, "on") == 0) DO41A1_CTRL_ActivateOutput(target);
	else if (strcmp(arg, "off") == 0) DO41A1_CTRL_DeactivateOutput(target);
	else if (strcmp(arg, "pulse") == 0) {
//		DO41A1_PULSE_PulseGen_TIM_High(OUT_TMR);
//		HAL_Delay(1000);
//		DO41A1_PULSE_PulseGen_TIM_Low(OUT_TMR);
	}
	else if (strcmp(arg, "pwm") == 0) {
//		NUCLEO_TIM_PeriodicPulse_Config(DO41A1_IN_Handle, DO41A1_IN_TIMx, DO41A1_IN_CHx, 1000, 500, 200);
//		NUCLEO_TIM_PeriodicPulse_Start(DO41A1_IN_Handle, DO41A1_IN_CHx);
	}
	else if (strcmp(arg, "single") == 0) DO41A1_CTRL_single_pulse(target, 1000);
	else if (strcmp(arg, "state") == 0) DO41A1_CTRL_read(target, logical);
	else if (strcmp(arg, "level") == 0) DO41A1_CTRL_read(target, numerical);
	else if (strcmp(arg, "levels") == 0) DO41A1_CTRL_levels();
	else if (strcmp(arg, "states") == 0) DO41A1_CTRL_states();
	else if (strcmp(arg, "help") == 0) DO41A1_CTRL_help();
	else if (strcmp(arg, "functions") == 0) DO41A1_CTRL_list_io();
	else if (strcmp(arg, "actions") == 0) DO41A1_CTRL_list_actions();
	else {
		msg.Reset(&msg);
		msg.AppendStr("Invalid command, no actions performed", &msg);
		NUCLEO_USART_vCOM_WriteLine(&msg);
	}
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief Prints help message
 * @retval None
 */
void DO41A1_CTRL_help() {
	msg.Reset(&msg);
	msg.AppendStr("[function] [action] - applies action to a function\n"
			"[global_action] - applies action to all functions\n"
			"- Type 'functions' for function list\n"
			"- Type 'actions' for action list\n"
			"- Type 'clear' to clear text from terminal\n"
			/*"- Use 'x' in io identifiers for numerical wildcard (e.g. outx selects all outputs)\n"*/, &msg);
	NUCLEO_USART_vCOM_Write(&msg);
}

/**
 * @brief Prints list of IOs
 * @retval None
 */
void DO41A1_CTRL_list_io() {

	msg.Reset(&msg);
	for (int i = out1; i <= status4; i += 1) {
		switch (i) {
			case out1:
				msg.AppendStr("out1\n", &msg);
				break;
			case out2:
				msg.AppendStr("out2\n", &msg);
				break;
			case out3:
				msg.AppendStr("out3\n", &msg);
				break;
			case out4:
				msg.AppendStr("out4\n", &msg);
				break;
			case status1:
				msg.AppendStr("status1\n", &msg);
				break;
			case status2:
				msg.AppendStr("status2\n", &msg);
				break;
			case status3:
				msg.AppendStr("status3\n", &msg);
				break;
			case status4:
				msg.AppendStr("status4\n", &msg);
				break;
			default:
				break;
		}
	}

	NUCLEO_USART_vCOM_Write(&msg);
}

/**
 * @brief Prints list of actions
 * @retval None
 */
void DO41A1_CTRL_list_actions() {

	msg.Reset(&msg);
	for (int i = on; i <= levels; i += 1) {
		switch (i) {
			case on:
				msg.AppendStr("on\n", &msg);
				break;
			case off:
				msg.AppendStr("off\n", &msg);
				msg.AppendStr("off [global]\n", &msg);
				break;
			case state:
				msg.AppendStr("state - returns if function is on or off\n", &msg);
				break;
			case states:
				msg.AppendStr("states [global]\n", &msg);
				break;
			case level:
				msg.AppendStr("level - returns numeric representation of function state"
						"(integer 1 and 0 denote logical state, decimals denote physical state)\n", &msg);
				break;
			case levels:
				msg.AppendStr("levels [global]\n", &msg);
				break;
			default:
				break;
		}
	}

	NUCLEO_USART_vCOM_Write(&msg);
}

/**
 * @brief Provides IO switching services
 * @param io: IO
 * @param act: action
 * @retval None
 */
void DO41A1_CTRL_switch(CTRL_IOTypeDef io, CTRL_ActionTypeDef act) {

}

/**
 * @brief Provides IO single pulse services
 * @param io: IO
 * @param act: action
 * @retval None
 */
void DO41A1_CTRL_single_pulse(CTRL_IOTypeDef io, uint32_t duration) {
	DO41A1_CTRL_ActivateOutput((DO41A1_CTRL_IO) io);
	HAL_Delay(duration);
	DO41A1_CTRL_DeactivateOutput((DO41A1_CTRL_IO) io);
}

/**
 * @brief Provides configuration for PWM timer
 * @param io: IO
 * @param cfg: configuration string
 * @retval None
 */
void DO41A1_CTRL_PWM_Config(CTRL_IOTypeDef io, char * cfg) {
	char * remainder = strtok(NULL, " ");

	char * tick = strtok(NULL, " ");
	char * period = strtok(NULL, " ");
	char * pulse = strtok(NULL, " ");

	uint32_t tick_micros = atoi(tick);
	uint32_t period_ticks = atoi(period);
	uint32_t pulse_ticks = atoi(pulse);

	if (pulse_ticks > period_ticks) {
		NUCLEO_USART_vCOM_QuickWriteLine("Pulse cannot have longer duration than period");
		return;
	}

	switch (io) {
		case out1:
			NUCLEO_TIM_PeriodicPulse_Config(DO41A1_IN1_TIM_Handle, DO41A1_IN1_TIMx, DO41A1_IN1_CHx, tick_micros, period_ticks, pulse_ticks);
			break;
		case out2:
			NUCLEO_TIM_PeriodicPulse_Config(DO41A1_IN2_TIM_Handle, DO41A1_IN2_TIMx, DO41A1_IN2_CHx, tick_micros, period_ticks, pulse_ticks);
			break;
		case out3:
			NUCLEO_TIM_PeriodicPulse_Config(DO41A1_IN3_TIM_Handle, DO41A1_IN3_TIMx, DO41A1_IN3_CHx, tick_micros, period_ticks, pulse_ticks);
			break;
		case out4:
			NUCLEO_TIM_PeriodicPulse_Config(DO41A1_IN4_TIM_Handle, DO41A1_IN4_TIMx, DO41A1_IN4_CHx, tick_micros, period_ticks, pulse_ticks);
			break;
		default:
			break;
	}
}

/**
 * @brief Runs the configured PWM timer
 * @param io: IO
 * @retval None
 */
void DO41A1_CTRL_PWM_Run(CTRL_IOTypeDef io) {

	switch (io) {
		case out1:
			NUCLEO_TIM_PeriodicPulse_Start(DO41A1_IN1_TIM_Handle, DO41A1_IN1_CHx);
			break;
		case out2:
			NUCLEO_TIM_PeriodicPulse_Start(DO41A1_IN2_TIM_Handle, DO41A1_IN1_CHx);
			break;
		case out3:
			NUCLEO_TIM_PeriodicPulse_Start(DO41A1_IN3_TIM_Handle, DO41A1_IN1_CHx);
			break;
		case out4:
			NUCLEO_TIM_PeriodicPulse_Start(DO41A1_IN4_TIM_Handle, DO41A1_IN1_CHx);
			break;
		default:
			break;
	}
}

/**
 * @brief Provides IO reading services
 * @param io: io
 * @param fmt: reading formatting
 * @retval None
 */
void DO41A1_CTRL_read(CTRL_IOTypeDef dev, CTRL_FormatTypeDef fmt) {
	msg.Reset(&msg);

	int logic = -1;
	float reading = -1.0;

	switch (dev) {
		case out1:
			logic = (int) HAL_GPIO_ReadPin(DO41A1_IN1_GPIO_Port, DO41A1_IN1_GPIO_Pin);
			msg.AppendStr("OUT1 \t\t = ", &msg);
			break;
		case out2:
			logic = (int) HAL_GPIO_ReadPin(DO41A1_IN2_GPIO_Port, DO41A1_IN2_GPIO_Pin);
			msg.AppendStr("OUT2 \t\t = ", &msg);
			break;
		case out3:
			logic = (int) HAL_GPIO_ReadPin(DO41A1_IN3_GPIO_Port, DO41A1_IN3_GPIO_Pin);
			msg.AppendStr("OUT3 \t\t = ", &msg);
			break;
		case out4:
			logic = (int) HAL_GPIO_ReadPin(DO41A1_IN4_GPIO_Port, DO41A1_IN4_GPIO_Pin);
			msg.AppendStr("OUT4 \t\t = ", &msg);
			break;
		case status1:
			logic = (int) DO41A1_STATUS1;
			DO41A1_STATUS1 = 0;
			msg.AppendStr("STATUS1 \t\t = ", &msg);
			break;
		case status2:
			logic = (int) DO41A1_STATUS2;
			DO41A1_STATUS2 = 0;
			msg.AppendStr("STATUS2 \t\t = ", &msg);
			break;
		case status3:
			logic = (int) DO41A1_STATUS3;
			DO41A1_STATUS3 = 0;
			msg.AppendStr("STATUS3 \t\t = ", &msg);
			break;
		case status4:
			logic = (int) DO41A1_STATUS4;
			DO41A1_STATUS4 = 0;
			msg.AppendStr("STATUS4 \t\t = ", &msg);
			break;
		default:
			break;
	}

	if (fmt == numerical) {
		if (reading != -1.0f) msg.AppendFloat(reading, &msg);
		else if (logic != -1) msg.AppendInt(logic, &msg);
	}
	else if (fmt == logical) {
		if (reading >= NUCLEO_GPIO_NOMINAL_VOLTAGE_THRESHOLD || logic == 1) msg.AppendStr("(on)", &msg);
		else if (reading <= NUCLEO_GPIO_ZERO_VOLTAGE_THRESHOLD || logic == 0) msg.AppendStr("(off)", &msg);
		else msg.AppendStr("(?)", &msg);
	}

	msg.AppendStr("\n", &msg);
	NUCLEO_USART_vCOM_Write(&msg);
}

/**
 * @brief Prints voltage and logical levels of all IOs
 * @retval None
 */
void DO41A1_CTRL_levels() {
	for(int i = out1; i <= status4; i += 1)
		DO41A1_CTRL_read(i, numerical);
}

/**
 * @brief Prints switch states of all IOs
 * @note '?' output symbol means switch state can not be determined
 * @retval None
 */
void DO41A1_CTRL_states() {
	for(int i = out1; i <= status4; i += 1)
		DO41A1_CTRL_read(i, logical);
}

void DO41A1_CTRL_ActivateOutput(DO41A1_CTRL_IO out_ctrl) {
	switch (out_ctrl) {
		case out1:
			HAL_GPIO_WritePin(DO41A1_IN1_GPIO_Port, DO41A1_IN1_GPIO_Pin, GPIO_PIN_SET);
			NUCLEO_TIM_PeriodicPulse_Start_IT(DO41A1_IN1_TIM_Handle, DO41A1_IN1_CHx);
			break;
		case out2:
			HAL_GPIO_WritePin(DO41A1_IN2_GPIO_Port, DO41A1_IN2_GPIO_Pin, GPIO_PIN_SET);
			NUCLEO_TIM_PeriodicPulse_Start_IT(DO41A1_IN2_TIM_Handle, DO41A1_IN2_CHx);
			break;
		case out3:
			HAL_GPIO_WritePin(DO41A1_IN3_GPIO_Port, DO41A1_IN3_GPIO_Pin, GPIO_PIN_SET);
			NUCLEO_TIM_PeriodicPulse_Start_IT(DO41A1_IN3_TIM_Handle, DO41A1_IN3_CHx);
			break;
		case out4:
			HAL_GPIO_WritePin(DO41A1_IN4_GPIO_Port, DO41A1_IN4_GPIO_Pin, GPIO_PIN_SET);
			NUCLEO_TIM_PeriodicPulse_Start_IT(DO41A1_IN4_TIM_Handle, DO41A1_IN4_CHx);
			break;
		case outx:
			for (int out = out1; out <= out4; out += 1) DO41A1_CTRL_ActivateOutput(out);
			break;
		default:
			// Print informative message
			break;
	}
}

void DO41A1_CTRL_DeactivateOutput(DO41A1_CTRL_IO out_ctrl) {
	switch (out_ctrl) {
		case out1:
			HAL_GPIO_WritePin(DO41A1_IN1_GPIO_Port, DO41A1_IN1_GPIO_Pin, GPIO_PIN_RESET);
			NUCLEO_TIM_PeriodicPulse_Stop_IT(DO41A1_IN1_TIM_Handle, DO41A1_IN1_CHx);
			break;
		case out2:
			HAL_GPIO_WritePin(DO41A1_IN2_GPIO_Port, DO41A1_IN2_GPIO_Pin, GPIO_PIN_RESET);
			NUCLEO_TIM_PeriodicPulse_Stop_IT(DO41A1_IN2_TIM_Handle, DO41A1_IN2_CHx);
			break;
		case out3:
			HAL_GPIO_WritePin(DO41A1_IN3_GPIO_Port, DO41A1_IN3_GPIO_Pin, GPIO_PIN_RESET);
			NUCLEO_TIM_PeriodicPulse_Stop_IT(DO41A1_IN3_TIM_Handle, DO41A1_IN3_CHx);
			break;
		case out4:
			HAL_GPIO_WritePin(DO41A1_IN4_GPIO_Port, DO41A1_IN4_GPIO_Pin, GPIO_PIN_RESET);
			NUCLEO_TIM_PeriodicPulse_Stop_IT(DO41A1_IN4_TIM_Handle, DO41A1_IN4_CHx);
			break;
		case outx:
			for (int out = out1; out <= out4; out += 1) DO41A1_CTRL_DeactivateOutput(out);
			break;
		default:
			// Print informative message
			break;
	}
}

void DO41A1_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	DO41A1_STATUS1 = 0;
	DO41A1_STATUS2 = 0;
	DO41A1_STATUS3 = 0;
	DO41A1_STATUS4 = 0;

	switch (GPIO_Pin) {
		case DO41A1_STATUS1_GPIO_Pin:
			DO41A1_STATUS1 = 1;
			break;
		case DO41A1_STATUS2_GPIO_Pin:
			DO41A1_STATUS2 = 1;
			break;
		case DO41A1_STATUS3_GPIO_Pin:
			DO41A1_STATUS3 = 1;
			break;
		case DO41A1_STATUS4_GPIO_Pin:
			DO41A1_STATUS4 = 1;
			break;
		default:
			break;
	}
}
