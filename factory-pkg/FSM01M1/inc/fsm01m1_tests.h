/**
 ******************************************************************************
 * @file    fsm01m1_tests.h
 * @author  ST Power Application Lab Prague
 * @version V1.0.0
 * @date    Jan 1, 2025
 * @brief   PCB test routines and procedures
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSM01M1_TESTS_H
#define __FSM01M1_TESTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdbool.h"

/* Exported Constants --------------------------------------------------------*/

/* Exported Types  -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* TEST_PROC procedures */
void FSM01M1_TEST_PROC_check_expected_voltages(bool * vcc, bool * vcc1, bool * out1, bool * vcc2, bool * out2);

/* TEST_CASE routines */
void FSM01M1_TEST_CASE_overcurrent_cutoff_test(void);
void FSM01M1_TEST_CASE_simultaneous_demagnetization(void);
void FSM01M1_TEST_CASE_SFTY_OFF(void);
void FSM01M1_TEST_CASE_loss_off_GND(void);
void FSM01M1_TEST_CASE_EMC_test_routine(void);
void FSM01M1_TEST_CASE_VCCx_test_pulse_routine(void);
void FSM01M1_TEST_CASE_expected_voltages_test(bool vcc, bool vcc1, bool out1, bool vcc2, bool out2);


#ifdef	 __cplusplus
}
#endif

#endif /* __FSM01M1_TESTS_H */


