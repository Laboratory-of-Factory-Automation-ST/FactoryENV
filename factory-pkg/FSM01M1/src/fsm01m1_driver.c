/**
  ******************************************************************************
  * @file    fsm01m1_driver.c
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
#include <stdlib.h>
#include <string.h>
#include "fsm01m1_driver.h"
#include "fsm01m1_base_driver.h"
#include "fsm01m1_pulse_driver.h"
#include "nucleo_usart_driver.h"
//#include "../../NUCLEO/inc/nucleo_usart_driver.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum CTRL_IO_t {
	all,
	vccx,
	outx,
	vcc,
	vcc1,
	vcc1_dsc,
	vcc2,
	vcc2_dsc,
	out1,
	out1_dsc,
	out2,
	out2_dsc,
	in1,
	in2,
	coff1,
	coff2,
	tp1,
	tp2
} CTRL_IOTypeDef;

typedef enum CTRL_Action_t {
	on,
	off,
	state,
	states,
	level,
	levels
} CTRL_ActionTypeDef;

typedef enum USART_Format_t {
	numerical,
	logical
} CTRL_FormatTypeDef;

/* Private variables ---------------------------------------------------------*/

/* buffer for command tokenization */
static char * token_ctx;

/* Private function prototypes -----------------------------------------------*/
void FSM01M1_CTRL_splash_msg();
void FSM01M1_CTRL_read(CTRL_IOTypeDef dev, CTRL_FormatTypeDef fmt);
void FSM01M1_CTRL_reset_devices();
void FSM01M1_CTRL_switch(CTRL_IOTypeDef dev, CTRL_ActionTypeDef act);
void FSM01M1_CTRL_levels();
void FSM01M1_CTRL_states();
void FSM01M1_CTRL_help();
void FSM01M1_CTRL_list_devices();
void FSM01M1_CTRL_list_actions();
void FSM01M1_CTRL_pulse(CTRL_IOTypeDef dev, char * config_str);
void FSM01M1_CTRL_single_pulse(CTRL_IOTypeDef dev, uint32_t duration);
void FSM01M1_CTRL_resolve(char * cmd, CTRL_IOTypeDef target);

/* Exported functions --------------------------------------------------------*/

/**
 * @brief Handles messages routed to the board
 * @param msg: message
 * @retval None
 */
void FSM01M1_CTRL_Handle(USART_MessageTypeDef * msg) {
	FSM01M1_CTRL_resolve(msg->data, all);
}

/**
 * @brief Provides command resolution services
 * @param cmd: command
 * @param target: device
 * @retval None
 */
void FSM01M1_CTRL_resolve(char * cmd, CTRL_IOTypeDef target) {
	if (cmd[0] == '\r' || cmd[0] == '\n') cmd = cmd + 1;
	char * arg = (char *) strtok_r(cmd, " ", &token_ctx);

	if (arg == NULL) return;
	arg[strcspn(arg, "\r\n")] = '\0';
	char * prefix = "fsm01m1.";
	size_t shift = strstr(arg, prefix) ? strlen(prefix) : 0;
	arg = &arg[shift];

	if (arg[0] == '\0') return;
	else if (strcmp(arg, "vcc") == 0) FSM01M1_CTRL_resolve(NULL, vcc);
	else if (strcmp(arg, "vcc1") == 0) FSM01M1_CTRL_resolve(NULL, vcc1);
	else if (strcmp(arg, "vcc1_dsc") == 0) FSM01M1_CTRL_resolve(NULL, vcc1_dsc);
	else if (strcmp(arg, "vcc2") == 0) FSM01M1_CTRL_resolve(NULL, vcc2);
	else if (strcmp(arg, "vcc2_dsc") == 0) FSM01M1_CTRL_resolve(NULL, vcc2_dsc);
	else if (strcmp(arg, "vccx") == 0) FSM01M1_CTRL_resolve(NULL, vccx);
	else if (strcmp(arg, "out1") == 0) FSM01M1_CTRL_resolve(NULL, out1);
	else if (strcmp(arg, "out1_dsc") == 0) FSM01M1_CTRL_resolve(NULL, out1_dsc);
	else if (strcmp(arg, "out2") == 0) FSM01M1_CTRL_resolve(NULL, out2);
	else if (strcmp(arg, "out2_dsc") == 0) FSM01M1_CTRL_resolve(NULL, out2_dsc);
	else if (strcmp(arg, "outx") == 0) FSM01M1_CTRL_resolve(NULL, outx);
	else if (strcmp(arg, "coff1") == 0) FSM01M1_CTRL_resolve(NULL, coff1);
	else if (strcmp(arg, "coff2") == 0) FSM01M1_CTRL_resolve(NULL, coff2);
	else if (strcmp(arg, "tp1") == 0) FSM01M1_CTRL_resolve(NULL, tp1);
	else if (strcmp(arg, "tp2") == 0) FSM01M1_CTRL_resolve(NULL, tp2);
	else if (strcmp(arg, "in1") == 0) FSM01M1_CTRL_resolve(NULL, in1);
	else if (strcmp(arg, "in2") == 0) FSM01M1_CTRL_resolve(NULL, in2);
	else if (strcmp(arg, "on") == 0) FSM01M1_CTRL_switch(target, on);
	else if (strcmp(arg, "off") == 0) FSM01M1_CTRL_switch(target, off);
//	else if (strcmp(arg, "set") == 0) FSM01M1_CTRL_set_pin(arg);
//	else if (strcmp(arg, "reset") == 0) FSM01M1_CTRL_reset_pin(arg);
	else if (strcmp(arg, "state") == 0) FSM01M1_CTRL_read(target, logical);
	else if (strcmp(arg, "level") == 0) FSM01M1_CTRL_read(target, numerical);
	else if (strcmp(arg, "levels") == 0) FSM01M1_CTRL_levels();
	else if (strcmp(arg, "states") == 0) FSM01M1_CTRL_states();
	else if (strcmp(arg, "help") == 0) FSM01M1_CTRL_help();
	else if (strcmp(arg, "functions") == 0) FSM01M1_CTRL_list_devices();
	else if (strcmp(arg, "actions") == 0) FSM01M1_CTRL_list_actions();
	else if (strcmp(arg, "pulse") == 0) {
//		FSM01M1_CTRL_pulse(target, cmd);
		FSM01M1_CTRL_single_pulse(out1, 1000);
	}
	else {
		msg.Reset(&msg);
		msg.AppendStr(&msg, "Invalid command, no actions performed");
		NUCLEO_USART_vCOM_WriteLine(&msg);
	}
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief Prints help message
 * @retval None
 */
void FSM01M1_CTRL_help() {
	msg.Reset(&msg);
	msg.AppendStr(&msg, "[function] [action] - applies action to a function\n"
			"[global_action] - applies action to all functions\n"
			"- Type 'functions' for function list\n"
			"- Type 'actions' for action list\n"
			"- Type 'clear' to clear text from terminal\n"
			/*"- Use 'x' in device identifiers for numerical wildcard (e.g. outx selects all outputs)\n"*/);
	NUCLEO_USART_vCOM_Write(&msg);
}

/**
 * @brief Prints list of devices
 * @retval None
 */
void FSM01M1_CTRL_list_devices() {
	msg.Reset(&msg);
	for (int i = vcc; i <= tp2; i += 1) {
		switch (i) {
			case vcc:
				msg.AppendStr(&msg, "vcc\n");
				break;
			case vcc1:
				msg.AppendStr(&msg, "vcc1\n");
				break;
			case vcc1_dsc:
				msg.AppendStr(&msg, "vcc1_dsc\n");
				break;
			case vcc2:
				msg.AppendStr(&msg, "vcc2\n");
				break;
			case vcc2_dsc:
				msg.AppendStr(&msg, "vcc2_dsc\n");
				break;
			case in1:
				msg.AppendStr(&msg, "in1\n");
				break;
			case in2:
				msg.AppendStr(&msg, "in2\n");
				break;
			case out1:
				msg.AppendStr(&msg, "out1\n");
				break;
			case out1_dsc:
				msg.AppendStr(&msg, "out1_dsc\n");
				break;
			case out2:
				msg.AppendStr(&msg, "out2\n");
				break;
			case out2_dsc:
				msg.AppendStr(&msg, "out2_dsc\n");
				break;
			case coff1:
				msg.AppendStr(&msg, "coff1\n");
				break;
			case coff2:
				msg.AppendStr(&msg, "coff2\n");
				break;
			case tp1:
				msg.AppendStr(&msg, "tp1\n");
				break;
			case tp2:
				msg.AppendStr(&msg, "tp2\n");
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
void FSM01M1_CTRL_list_actions() {
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

	NUCLEO_USART_vCOM_Write(&msg);
}

/**
 * @brief Provides device switching services
 * @param dev: device
 * @param act: action
 * @retval None
 */
void FSM01M1_CTRL_switch(CTRL_IOTypeDef dev, CTRL_ActionTypeDef act) {
	switch (dev) {
		case vcc1:
			if (act == on) FSM01M1_VCC1_ON();
			else FSM01M1_VCC1_OFF();
			break;
		case vcc1_dsc:
			if (act == on) FSM01M1_VCC1_DSC_ON();
			else FSM01M1_VCC1_DSC_OFF();
			break;
		case vcc2:
			if (act == on) FSM01M1_VCC2_ON();
			else FSM01M1_VCC2_OFF();
			break;
		case vcc2_dsc:
			if (act == on) FSM01M1_VCC2_DSC_ON();
			else FSM01M1_VCC2_DSC_OFF();
			break;
		case vccx:
			FSM01M1_CTRL_switch(vcc1, act);
			FSM01M1_CTRL_switch(vcc2, act);
			break;
		case out1:
			if (act == on) FSM01M1_OUT1_CTRL_ON();
			else FSM01M1_OUT1_CTRL_OFF();
			break;
		case out1_dsc:
			if (act == on) FSM01M1_OUT1_DSC_ON();
			else FSM01M1_OUT1_DSC_OFF();
			break;
		case out2:
			if (act == on) FSM01M1_OUT2_CTRL_ON();
			else FSM01M1_OUT2_CTRL_OFF();
			break;
		case out2_dsc:
			if (act == on) FSM01M1_OUT2_DSC_ON();
			else FSM01M1_OUT2_DSC_OFF();
			break;

		case outx:
			FSM01M1_CTRL_switch(out1, act);
			FSM01M1_CTRL_switch(out2, act);
			break;
		case coff1:
			if (act == on) FSM01M1_CUTOFF1_CTRL_ON();
			else FSM01M1_CUTOFF1_CTRL_OFF();
			break;
		case coff2:
			if (act == on) FSM01M1_CUTOFF2_CTRL_ON();
			else FSM01M1_CUTOFF2_CTRL_OFF();
			break;
		case tp1:
			if (act == on) FSM01M1_TP1_ON();
			else FSM01M1_TP1_OFF();
			break;
		case tp2:
			if (act == on) FSM01M1_TP2_ON();
			else FSM01M1_TP2_OFF();
			break;
		case all:
			if (act == off) FSM01M1_system_deactivation();
		default:
			break;
	}
}

//void FSM01M1_CTRL_set_pin(char * arg) {
//
//}
//
//void FSM01M1_CTRL_reset_pin(char * arg) {
//
//}

/**
 * @brief Provides device reading services
 * @param dev: device
 * @param fmt: reading formatting
 * @retval None
 */
void FSM01M1_CTRL_read(CTRL_IOTypeDef dev, CTRL_FormatTypeDef fmt) {
	msg.Reset(&msg);

	int logic = -1;
	float reading = -1.0;

	switch (dev) {
		case vcc:
			reading = FSM01M1_ADC120_read_single_node(&hspi2, VCC_ADC_CHANNEL_ID);
			msg.AppendStr(&msg, "VCC \t\t = ");
			break;
		case vcc1:
			reading = FSM01M1_ADC120_read_single_node(&hspi2, VCC1_ADC_CHANNEL_ID);
			msg.AppendStr(&msg, "VCC1 \t\t = ");
			break;
		case vcc1_dsc:
			logic = (int) HAL_GPIO_ReadPin(VCC1_DSC_GPIO_Port, VCC1_DSC_Pin);
			msg.AppendStr(&msg, "VCC1_DSC \t = ");
			break;
		case vcc2:
			reading = FSM01M1_ADC120_read_single_node(&hspi2, VCC2_ADC_CHANNEL_ID);
			msg.AppendStr(&msg, "VCC2 \t\t = ");
			break;
		case vcc2_dsc:
			logic = (int) HAL_GPIO_ReadPin(VCC2_DSC_GPIO_Port, VCC2_DSC_Pin);
			msg.AppendStr(&msg, "VCC2_DSC \t = ");
			break;
		case in1:
			logic = (int) HAL_GPIO_ReadPin(OUTP1_GPIO_Port, OUTP1_Pin);
			msg.AppendStr(&msg, "IN1 \t\t = ");
			break;
		case in2:
			logic = (int) HAL_GPIO_ReadPin(OUTP2_GPIO_Port, OUTP2_Pin);
			msg.AppendStr(&msg, "IN2 \t\t = ");
			break;
		case out1:
			reading = FSM01M1_ADC120_read_single_node(&hspi2, OUT1_ADC_CHANNEL_ID);
			msg.AppendStr(&msg, "OUT1 \t\t = ");
			break;
		case out1_dsc:
			logic = (int) HAL_GPIO_ReadPin(OUT1_DSC_GPIO_Port, OUT1_DSC_Pin);
			msg.AppendStr(&msg, "OUT1_DSC \t = ");
			break;
		case out2:
			reading = FSM01M1_ADC120_read_single_node(&hspi2, OUT2_ADC_CHANNEL_ID);
			msg.AppendStr(&msg, "OUT2 \t\t = ");
			break;
		case out2_dsc:
			logic = (int) HAL_GPIO_ReadPin(OUT2_DSC_GPIO_Port, OUT2_DSC_Pin);
			msg.AppendStr(&msg, "OUT2_DSC \t = ");
			break;
		case coff1:
			logic = (int) HAL_GPIO_ReadPin(COFF1_CTRL_GPIO_Port, COFF1_CTRL_Pin) == GPIO_PIN_RESET;
			msg.AppendStr(&msg, "COFF1 \t\t = ");
			break;
		case coff2:
			logic = (int) HAL_GPIO_ReadPin(COFF2_CTRL_GPIO_Port, COFF2_CTRL_Pin) == GPIO_PIN_RESET;
			msg.AppendStr(&msg, "COFF2 \t\t = ");
			break;
		case tp1:
			logic = (int) HAL_GPIO_ReadPin(TP1_CTRL_GPIO_Port, TP1_CTRL_Pin) == GPIO_PIN_RESET;
			msg.AppendStr(&msg, "TP1 \t\t = ");
			break;
		case tp2:
			logic = (int) HAL_GPIO_ReadPin(TP2_CTRL_GPIO_Port, TP2_CTRL_Pin) == GPIO_PIN_RESET;
			msg.AppendStr(&msg, "TP2 \t\t = ");
			break;
		default:
			break;
	}

	if (fmt == numerical) {
		if (reading != -1.0f) msg.AppendFloat(&msg, reading);
		else if (logic != -1) msg.AppendInt(&msg, logic);
	}
	else if (fmt == logical) {
		if (reading >= FSM01M1_NOMINAL_VOLTAGE_THRESHOLD || logic == 1) msg.AppendStr(&msg, "(on)");
		else if (reading <= FSM01M1_ZERO_VOLTAGE_THRESHOLD || logic == 0) msg.AppendStr(&msg, "(off)");
		else msg.AppendStr(&msg, "(?)");
	}

	msg.AppendStr(&msg, "\n");
	NUCLEO_USART_vCOM_Write(&msg);
}

/**
 * @brief Prints voltage and logical levels of all devices
 * @retval None
 */
void FSM01M1_CTRL_levels() {
	for(int i = vcc; i <= tp2; i += 1)
		FSM01M1_CTRL_read(i, numerical);
}

/**
 * @brief Prints switch states of all devices
 * @note '?' output symbol means switch state can not be determined
 * @retval None
 */
void FSM01M1_CTRL_states() {
	for(int i = vcc; i <= tp2 ; i += 1)
		FSM01M1_CTRL_read(i, logical);
}

/**
 * @brief Provides device single pulse services
 * @param dev: device
 * @param act: action
 * @retval None
 */
void FSM01M1_CTRL_single_pulse(CTRL_IOTypeDef dev, uint32_t duration) {
	switch (dev) {
		case out1:
			FSM01M1_OUT1_CTRL_ON();
			HAL_Delay(duration);
			FSM01M1_OUT1_CTRL_OFF();
			break;
		default:
			break;
	}
}

void FSM01M1_CTRL_pulse(CTRL_IOTypeDef dev, char * config_str) {
	char * pulse_params[2] = {0};
	for (unsigned int i = 0; i < 2; i += 1) {
		char ** param_ptr = &pulse_params[i];
		*param_ptr = (char *) strtok_r(config_str, ",", &token_ctx);
		uint32_t len = strcspn(*param_ptr, "\r\n");
		*param_ptr[len] = '\0';
	}

	switch (dev) {
		case out1:
			FSM01M1_PULSE_PulseGen_TIM_IT(OUT1_TIM_HANDLE, OUT1_TIM, OUT1_TIM_CHANNEL, 1, 65535, 25000);
			break;
		case out2:
			FSM01M1_PULSE_PulseGen_TIM_IT(OUT2_TIM_HANDLE, OUT2_TIM, OUT2_TIM_CHANNEL, 1, 65535, 25000);
			break;
		default:
			// print informative message
			break;
	}
}
