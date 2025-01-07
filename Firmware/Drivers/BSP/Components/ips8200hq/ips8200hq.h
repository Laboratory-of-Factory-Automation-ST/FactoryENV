/**
  ******************************************************************************
  * @file    ips8200hq.h
  * @author  AMS IPC Application Team
  * @brief   Header for ips8200hq.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IPS8200HQ_H
#define IPS8200HQ_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include "ips8200hq_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */

/** @addtogroup IPS8200HQ IPS8200HQ
  * @{
  */

/* Exported Constants --------------------------------------------------------*/

/** @defgroup IPS8200HQ_Exported_Constants IPS8200HQ Exported Constants
  * @{
  */

/* Return codes */
/** IPS8200HQ Ok codes */
#define IPS_DEVICE_OK (0)

/** IPS8200HQ Error code */
#define IPS_DEVICE_ERROR (-1)

/** IPS8200HQ ID */
#define IPS8200HQ_CHIP_ID (8200U)

/** Maximum number of devices supported */
#define IPS8200HQ_DEVICES_NBR (1U)

/** Maximum number of instances supported in Parallel control mode */
#define IPS8200HQ_PAR_INSTANCES_NBR (1U)

/** Maximum number of instances supported in SPI control mode (Regular) */
#define IPS8200HQ_SPI_INSTANCES_NBR (1U)

/** Maximum number of instances supported in SPI control mode (Daisy Chain) */
#define IPS8200HQ_SPI_DC_INSTANCES_NBR (2U)

#ifdef APP_PAR_IFC
/* Dev capabilities for IPS8200HQ (Parallel Interface) */

/** Maximum channel frequency in tenth of Hz */
#define IPS8200HQ_MAX_CHAN_FREQ (1000U)

/** Max number of channels by switch IPS8200HQ (Parallel Interface) */
#define IPS8200HQ_MAX_NB_CHANNELS (8U)

/** First control pin by switch IPS8200HQ (Parallel Interface) board 0 */
#define IPS8200HQ_0_FIRST_CONTROL (0U)

/** Max number of control pins by switch IPS8200HQ (Parallel Interface) */
#define IPS8200HQ_MAX_NB_CONTROLS (4U)

/* Dev pins for IPS8200HQ (Parallel Interface) */
/* Board 0 */
/** Input Pin: IN1 */
#define IPS8200HQ_0_IN1 (0U)
/** Input Pin: IN2 */
#define IPS8200HQ_0_IN2 (1U)
/** Input Pin: IN3 */
#define IPS8200HQ_0_IN3 (2U)
/** Input Pin: IN4 */
#define IPS8200HQ_0_IN4 (3U)
/** Input Pin: IN5 */
#define IPS8200HQ_0_IN5 (4U)
/** Input Pin: IN6 */
#define IPS8200HQ_0_IN6 (5U)
/** Input Pin: IN7 */
#define IPS8200HQ_0_IN7 (6U)
/** Input Pin: IN8 */
#define IPS8200HQ_0_IN8 (7U)

/** Control Pin: SEL2_L */
#define IPS8200HQ_0_SEL2_L (0U)
/** Control Pin: SEL1 */
#define IPS8200HQ_0_SEL1 (1U)
/** Control Pin: WD */
#define IPS8200HQ_0_WD (2U)
/** Control Pin: WDEN */
#define IPS8200HQ_0_WDEN (3U)

/** IN1 Port 0 */
#define IPS8200HQ_0_IN1_GPIO_PORT IN1_GPIO_Port
/** IN1 Pin 0 */
#define IPS8200HQ_0_IN1_GPIO_PIN IN1_Pin
/** IN2 Port 0 */
#define IPS8200HQ_0_IN2_GPIO_PORT IN2_GPIO_Port
/** IN2 Pin 0 */
#define IPS8200HQ_0_IN2_GPIO_PIN IN2_Pin
/** IN3 Port 0 */
#define IPS8200HQ_0_IN3_GPIO_PORT IN3_GPIO_Port
/** IN3 Pin 0 */
#define IPS8200HQ_0_IN3_GPIO_PIN IN3_Pin
/** IN4 Port 0 */
#define IPS8200HQ_0_IN4_GPIO_PORT IN4_GPIO_Port
/** IN4 Pin 0 */
#define IPS8200HQ_0_IN4_GPIO_PIN IN4_Pin
/** IN5 Port 0 */
#define IPS8200HQ_0_IN5_GPIO_PORT IN5_GPIO_Port
/** IN5 Pin 0 */
#define IPS8200HQ_0_IN5_GPIO_PIN IN5_Pin
/** IN6 Port 0 */
#define IPS8200HQ_0_IN6_GPIO_PORT IN6_GPIO_Port
/** IN6 Pin 0 */
#define IPS8200HQ_0_IN6_GPIO_PIN IN6_Pin
/** IN7 Port 0 */
#define IPS8200HQ_0_IN7_GPIO_PORT IN7_GPIO_Port
/** IN7 Pin 0 */
#define IPS8200HQ_0_IN7_GPIO_PIN IN7_Pin
/** IN8 Port 0 */
#define IPS8200HQ_0_IN8_GPIO_PORT IN8_GPIO_Port
/** IN8 Pin 0 */
#define IPS8200HQ_0_IN8_GPIO_PIN IN8_Pin

/** SEL2_L Port 0 */
#define IPS8200HQ_0_SEL2_L_GPIO_PORT SEL2_L_GPIO_Port
/** SEL2_L Pin 0 */
#define IPS8200HQ_0_SEL2_L_GPIO_PIN SEL2_L_Pin
/** SEL1 Port 0 */
#define IPS8200HQ_0_SEL1_GPIO_PORT SEL1_GPIO_Port
/** SEL1 Pin 0 */
#define IPS8200HQ_0_SEL1_GPIO_PIN SEL1_Pin

/** FAULT_L Port 0 */
#define IPS8200HQ_0_FAULT_L_GPIO_PORT FAULT_L_GPIO_Port
/** FAULT_L Pin 0 */
#define IPS8200HQ_0_FAULT_L_GPIO_PIN FAULT_L_Pin
/** PGOOD_L Port 0 */
#define IPS8200HQ_0_PGOOD_L_GPIO_PORT PGOOD_L_GPIO_Port
/** PGOOD_L Pin 0 */
#define IPS8200HQ_0_PGOOD_L_GPIO_PIN PGOOD_L_Pin
/** TWARN_L Port 0 */
#define IPS8200HQ_0_TWARN_L_GPIO_PORT TWARN_L_GPIO_Port
/** TWARN_L Pin 0 */
#define IPS8200HQ_0_TWARN_L_GPIO_PIN TWARN_L_Pin
#endif /* #ifdef APP_PAR_IFC */

/** SPI: Watchdog Enable Mode */
#define IPS8200HQ_SPI_WD_MODE (3U)

#ifdef APP_SPI_IFC
/* Dev capabilities for IPS8200HQ (SPI Interface) */

/** Maximum channel frequency in tenth of Hz */
#define IPS8200HQ_MAX_CHAN_FREQ (1000U)

/** Max number of channels by switch IPS8200HQ (SPI Interface) */
#define IPS8200HQ_MAX_NB_CHANNELS (8U)

/** First control pin by switch IPS8200HQ (SPI Interface) board 0 */
#define IPS8200HQ_0_FIRST_CONTROL (0U)

/** First control pin by switch IPS8200HQ (SPI Interface) board 1 */
#define IPS8200HQ_1_FIRST_CONTROL (6U)

/** Max number of control pins by switch IPS8200HQ (SPI Interface) */
#define IPS8200HQ_MAX_NB_CONTROLS (6U)

/** Guard Timer tick in us */
#define IPS8200HQ_GUARD_TIMER_TICK_IN_US (1000000U/(uint32_t)(IPS8200HQ_GUARD_TIMER_FREQ))

/** Watchdog Timer tick in us */
#define IPS8200HQ_WATCHDOG_TIMER_TICK_IN_US (1000000U/(uint32_t)(IPS8200HQ_WATCHDOG_TIMER_FREQ))

/** Daisy chain: fully populated system */
#define IPS8200HQ_SPI_DC_FULLSYS (0x3U)

/* Dev pins for IPS8200HQ (SPI Interface) */
/* Board 0 */
/** Device Chan: IN1 */
#define IPS8200HQ_0_IN1 (0U)
/** Device Chan: IN2 */
#define IPS8200HQ_0_IN2 (1U)
/** Device Chan: IN3 */
#define IPS8200HQ_0_IN3 (2U)
/** Device Chan: IN4 */
#define IPS8200HQ_0_IN4 (3U)
/** Device Chan: IN5 */
#define IPS8200HQ_0_IN5 (4U)
/** Device Chan: IN6 */
#define IPS8200HQ_0_IN6 (5U)
/** Device Chan: IN7 */
#define IPS8200HQ_0_IN7 (6U)
/** Device Chan: IN8 */
#define IPS8200HQ_0_IN8 (7U)

/** Input Pin: SPI_CLK */
#define IPS8200HQ_0_SPI_CLK (0U)
/** Input Pin: SPI_MISO */
#define IPS8200HQ_0_SPI_MISO (1U)
/** Input Pin: SPI_MOSI */
#define IPS8200HQ_0_SPI_MOSI (2U)

/** Control Pin: SEL2_L */
#define IPS8200HQ_0_SEL2_L (0U)
/** Control Pin: SEL1 */
#define IPS8200HQ_0_SEL1 (1U)
/** Control Pin: SPI_SS */
#define IPS8200HQ_0_SPI_SS (2U)
/** Control Pin: OUT_EN */
#define IPS8200HQ_0_OUT_EN (3U)
/** Control Pin: WD */
#define IPS8200HQ_0_WD (4U)
/** Control Pin: WDEN */
#define IPS8200HQ_0_WDEN (5U)

/** SPI_SS Port 0 */
#define IPS8200HQ_0_SPI_SS_GPIO_PORT SPI_SS_GPIO_Port
/** SPI_SS Pin 0 */
#define IPS8200HQ_0_SPI_SS_GPIO_PIN SPI_SS_Pin
/** OUT_EN Port 0 */
#define IPS8200HQ_0_OUT_EN_GPIO_PORT OUT_EN_GPIO_Port
/** OUT_EN Pin 0 */
#define IPS8200HQ_0_OUT_EN_GPIO_PIN OUT_EN_Pin
/** WD Port 0 */
#define IPS8200HQ_0_WD_GPIO_PORT WD_GPIO_Port
/** WD Pin 0 */
#define IPS8200HQ_0_WD_GPIO_PIN WD_Pin

/** SEL2_L Port 0 */
#define IPS8200HQ_0_SEL2_L_GPIO_PORT SEL2_L_GPIO_Port
/** SEL2_L Pin 0 */
#define IPS8200HQ_0_SEL2_L_GPIO_PIN SEL2_L_Pin
/** SEL1 Port 0 */
#define IPS8200HQ_0_SEL1_GPIO_PORT SEL1_GPIO_Port
/** SEL1 Pin 0 */
#define IPS8200HQ_0_SEL1_GPIO_PIN SEL1_Pin
/** WDEN Port 0 */
#define IPS8200HQ_0_WDEN_GPIO_PORT WDEN_GPIO_Port
/** WDEN Pin 0 */
#define IPS8200HQ_0_WDEN_GPIO_PIN WDEN_Pin

/** FAULT_L Port 0 */
#define IPS8200HQ_0_FAULT_L_GPIO_PORT FAULT_L_GPIO_Port
/** FAULT_L Pin 0 */
#define IPS8200HQ_0_FAULT_L_GPIO_PIN FAULT_L_Pin
/** PGOOD_L Port 0 */
#define IPS8200HQ_0_PGOOD_L_GPIO_PORT PGOOD_L_GPIO_Port
/** PGOOD_L Pin 0 */
#define IPS8200HQ_0_PGOOD_L_GPIO_PIN PGOOD_L_Pin
/** TWARN_L Port 0 */
#define IPS8200HQ_0_TWARN_L_GPIO_PORT TWARN_L_GPIO_Port
/** TWARN_L Pin 0 */
#define IPS8200HQ_0_TWARN_L_GPIO_PIN TWARN_L_Pin

/* Board 1 */
/** Device Chan: IN1 */
#define IPS8200HQ_1_IN1 (0U)
/** Device Chan: IN2 */
#define IPS8200HQ_1_IN2 (1U)
/** Device Chan: IN3 */
#define IPS8200HQ_1_IN3 (2U)
/** Device Chan: IN4 */
#define IPS8200HQ_1_IN4 (3U)
/** Device Chan: IN5 */
#define IPS8200HQ_1_IN5 (4U)
/** Device Chan: IN6 */
#define IPS8200HQ_1_IN6 (5U)
/** Device Chan: IN7 */
#define IPS8200HQ_1_IN7 (6U)
/** Device Chan: IN8 */
#define IPS8200HQ_1_IN8 (7U)

/** Input Pin: SPI_CLK */
#define IPS8200HQ_1_SPI_CLK (3U)
/** Input Pin: SPI_MISO */
#define IPS8200HQ_1_SPI_MISO (4U)
/** Input Pin: SPI_MOSI */
#define IPS8200HQ_1_SPI_MOSI (5U)

/** Control Pin: SEL2_L */
#define IPS8200HQ_1_SEL2_L (6U)
/** Control Pin: SEL1 */
#define IPS8200HQ_1_SEL1 (7U)
/** Control Pin: SPI_SS */
#define IPS8200HQ_1_SPI_SS (8U)
/** Control Pin: OUT_EN */
#define IPS8200HQ_1_OUT_EN (9U)
/** Control Pin: WD */
#define IPS8200HQ_1_WD (10U)
/** Control Pin: WDEN */
#define IPS8200HQ_1_WDEN (11U)

/** SEL2_L Port 1 */
#define IPS8200HQ_1_SEL2_L_GPIO_PORT SEL2_L_GPIO_Port
/** SEL2_L Pin 1 */
#define IPS8200HQ_1_SEL2_L_GPIO_PIN SEL2_L_Pin
/** SEL1 Port 1 */
#define IPS8200HQ_1_SEL1_GPIO_PORT SEL1_GPIO_Port
/** SEL1 Pin 1 */
#define IPS8200HQ_1_SEL1_GPIO_PIN SEL1_Pin
/** WDEN Port 1 */
#define IPS8200HQ_1_WDEN_GPIO_PORT WDEN_GPIO_Port
/** WDEN Pin 1 */
#define IPS8200HQ_1_WDEN_GPIO_PIN WDEN_Pin
/** SPI_SS Port 1 */
#define IPS8200HQ_1_SPI_SS_GPIO_PORT SPI_SS_GPIO_Port
/** SPI_SS Pin 1 */
#define IPS8200HQ_1_SPI_SS_GPIO_PIN SPI_SS_Pin
/** OUT_EN Port 1 */
#define IPS8200HQ_1_OUT_EN_GPIO_PORT OUT_EN_GPIO_Port
/** OUT_EN Pin 1 */
#define IPS8200HQ_1_OUT_EN_GPIO_PIN OUT_EN_Pin
/** WD Port 1 */
#define IPS8200HQ_1_WD_GPIO_PORT WD_GPIO_Port
/** WD Pin 1 */
#define IPS8200HQ_1_WD_GPIO_PIN WD_Pin

/** FAULT_L Port 1 */
#define IPS8200HQ_1_FAULT_L_GPIO_PORT FAULT_L_GPIO_Port
/** FAULT_L Pin 1 */
#define IPS8200HQ_1_FAULT_L_GPIO_PIN FAULT_L_Pin
/** PGOOD Port 1 */
#define IPS8200HQ_1_PGOOD_L_GPIO_PORT PGOOD_L_GPIO_Port
/** PGOOD Pin 1 */
#define IPS8200HQ_1_PGOOD_L_GPIO_PIN PGOOD_L_Pin
/** TWARN_L Port 1 */
#define IPS8200HQ_1_TWARN_L_GPIO_PORT TWARN_L_GPIO_Port
/** TWARN_L Pin 1 */
#define IPS8200HQ_1_TWARN_L_GPIO_PIN TWARN_L_Pin
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Exported Types  -------------------------------------------------------*/

/** @defgroup IPS8200HQ_Exported_Types IPS8200HQ Exported Types
  * @{
  */

/** IPS8200HQ Chip Type structure */
typedef enum {
  /** IPS8200HQ Parallel Configuration Chip Type */
  IPS8200HQ_PAR_CHIP_TYPE = 2U,
  /** IPS8200HQ Regular SPI Configuration Chip Type */
  IPS8200HQ_SPI_CHIP_TYPE = 3U,
  /** IPS8200HQ Daisy Chain SPI Configuration Chip Type */
  IPS8200HQ_SPI_DC_CHIP_TYPE = 4U,
} IPS_ChipType_t;

/** IPS8200HQ Control Mode structure */
typedef enum {
  /** IPS8200HQ undefined Interface Control Mode */
  IPS8200HQ_UNDEF_CTRL_MODE=0U,
  /** IPS8200HQ Parallel Interface Control Mode */
  IPS8200HQ_PAR_CTRL_MODE,
  /** IPS8200HQ SPI Interface (Regular) Control Mode */
  IPS8200HQ_SPI_CTRL_MODE,
  /** IPS8200HQ SPI Interface (Daisy Chain) Control Mode */
  IPS8200HQ_SPI_DC_CTRL_MODE,
} IPS_CtrlMode_t;

/** IPS8200HQ SPI Width structure */
typedef enum {
  /** IPS8200HQ undefined SPI width Mode */
  IPS8200HQ_SPI_W_NONE=0U,
  /** IPS8200HQ SPI 8bit Width Mode */
  IPS8200HQ_SPI_W_8BIT,
  /** IPS8200HQ SPI 16bit Width Mode */
  IPS8200HQ_SPI_W_16BIT,
} IPS_SpiMode_t;

#ifdef APP_PAR_IFC
/** IPS8200HQ (Parallel Interface) device pin structure */
typedef struct
{
  /** IN1 GPIO Port definition */
  GPIO_TypeDef *IN1_GPort;
  /** IN1 GPIO Pin definition */
  uint16_t IN1_GPin;
  /** IN2 GPIO Port definition */
  GPIO_TypeDef *IN2_GPort;
  /** IN2 GPIO Pin definition */
  uint16_t IN2_GPin;
  /** IN3 GPIO Port definition */
  GPIO_TypeDef *IN3_GPort;
  /** IN3 GPIO Pin definition */
  uint16_t IN3_GPin;
  /** IN4 GPIO Port definition */
  GPIO_TypeDef *IN4_GPort;
  /** IN4 GPIO Pin definition */
  uint16_t IN4_GPin;
  /** IN5 GPIO Port definition */
  GPIO_TypeDef *IN5_GPort;
  /** IN5 GPIO Pin definition */
  uint16_t IN5_GPin;
  /** IN6 GPIO Port definition */
  GPIO_TypeDef *IN6_GPort;
  /** IN6 GPIO Pin definition */
  uint16_t IN6_GPin;
  /** IN7 GPIO Port definition */
  GPIO_TypeDef *IN7_GPort;
  /** IN7 GPIO Pin definition */
  uint16_t IN7_GPin;
  /** IN8 GPIO Port definition */
  GPIO_TypeDef *IN8_GPort;
  /** IN8 GPIO Pin definition */
  uint16_t IN8_GPin;

  /** SEL2_L GPIO Port definition */
  GPIO_TypeDef *SEL2_L_GPort;
  /** SEL2_L GPIO Pin definition */
  uint16_t SEL2_L_GPin;
  /** SEL1 GPIO Port definition */
  GPIO_TypeDef *SEL1_GPort;
  /** SEL1 GPIO Pin definition */
  uint16_t SEL1_GPin;

  /** FAULT_L GPIO Port definition */
  GPIO_TypeDef *FAULT_L_GPort;
  /** FAULT_L GPIO Pin definition */
  uint16_t FAULT_L_GPin;
  /** PGOOD_L GPIO Port definition */
  GPIO_TypeDef *PGOOD_L_GPort;
  /** PGOOD_L GPIO Pin definition */
  uint16_t PGOOD_L_GPin;
  /** TWARN_L GPIO Port definition */
  GPIO_TypeDef *TWARN_L_GPort;
  /** TWARN_L GPIO Pin definition */
  uint16_t TWARN_L_GPin;
} IPS_SWITCH_Pins_t;

/** Initialisation function  type*/
typedef int32_t (*IPS8200HQ_Init_Func)(void);
/** DeInitialisation function  type*/
typedef int32_t (*IPS8200HQ_DeInit_Func)(void);
/** GetTick function  type*/
typedef int32_t (*IPS8200HQ_GetTick_Func)(void);
/** Read fault function  type*/
typedef int32_t (*IPS8200HQ_Read_Fault_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Write channel function  type*/
typedef int32_t (*IPS8200HQ_Write_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read channel function  type*/
typedef int32_t (*IPS8200HQ_Read_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);
/** Write all channels function  type*/
typedef int32_t (*IPS8200HQ_Write_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t);
/** Read all channels function  type*/
typedef int32_t (*IPS8200HQ_Read_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Set PWM function  type*/
typedef int32_t (*IPS8200HQ_Set_Pwm_Func)(uint8_t);
/** Write Pin function type */
typedef int32_t (*IPS8200HQ_Write_Pin_Func_t)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read Pin function type */
typedef int32_t (*IPS8200HQ_Read_Pin_Func_t)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);

/** IPS8200HQ (Parallel Interface) IO structure  */
typedef struct
{
  /** Initialisation function */
  IPS8200HQ_Init_Func             Init;
  /** DeInitialisation function */
  IPS8200HQ_DeInit_Func           DeInit;
  /** Get Tick function */
  IPS8200HQ_GetTick_Func          GetTick;
  /** Read fault function */
  IPS8200HQ_Read_Fault_Func       ReadFault;
  /** Write Pin status function */
  IPS8200HQ_Write_Pin_Func_t      WritePin;
  /** Read Pin status function */
  IPS8200HQ_Read_Pin_Func_t       ReadPin;
  /** Write Channel status function */
  IPS8200HQ_Write_Chan_Func       WriteChan;
  /** Read Channel status function */
  IPS8200HQ_Read_Chan_Func        ReadChan;
  /** Write All Channels status function */
  IPS8200HQ_Write_All_Chan_Func   WriteAllChan;
  /** Read All Channels status function */
  IPS8200HQ_Read_All_Chan_Func    ReadAllChan;
  /** Set PWM */
  IPS8200HQ_Set_Pwm_Func          SetPwm;
} IPS8200HQ_IO_t;

/** IPS8200HQ (Parallel Interface) component object structure  */
typedef struct
{
  /** IOs substructure */
  IPS8200HQ_IO_t IO;
  /** Pins substructure */
  IPS_SWITCH_Pins_t Pin;
  /** number of similar devices */
  uint8_t nbDevices;
  /** number of channels */
  uint8_t nbChannels;
  /** first control pin */
  uint8_t firstCtrl;
  /** number of control pins */
  uint8_t nbCtrls;
  /** is component initialised? */
  uint8_t is_initialized;
  /** channel Duty cycle */
  uint8_t channelDc[IPS8200HQ_MAX_NB_CHANNELS];
  /** Is PWM mode enabled? */
  uint8_t isPwmEnabled;
  /** channel enable bitmap for PWM management */
  uint8_t chanEnBitmap;
  /** next channel enable bitmap for PWM management */
  uint8_t nextChanEnBitmap;
  /** force resynchronisation of the PWM */
  uint8_t forcePwmResync[IPS8200HQ_MAX_NB_CHANNELS];
  /** Channel frequency */
  uint16_t channelFreq[IPS8200HQ_MAX_NB_CHANNELS];
  /** ID of the chip */
  uint16_t chipId;
  /** Action Table for each channel: tick of the next level change */
  uint32_t chanPwmTimActionTable[IPS8200HQ_MAX_NB_CHANNELS];
  /** period of low state for each channel */
  uint32_t chanPwmTimPeriodLow[IPS8200HQ_MAX_NB_CHANNELS];
  /** period of hihg state for each channel */
  uint32_t chanPwmTimPeriodHigh[IPS8200HQ_MAX_NB_CHANNELS];
  /** PWM frequency */
  uint32_t pwmFreq;
  /** PWM tick */
  uint32_t pwmTimTickCnt[IPS8200HQ_MAX_NB_CHANNELS];
  /** Tick where the next action in PWM mode has to be performed */
  uint32_t pwmTimNextAction;
  /** channel steady state bitmap */
  uint8_t ChanSteadyStateBitmap;
  /** controls steady state bitmap */
  uint8_t ControlPinsBitmap;
  /** Instance of the current object */
  uint8_t Instance;
  /** Board is present flag */
  uint8_t isPresent;
  /** Control Mode flag (Parallel, SPI Regular or Daisy Chain) */
  uint8_t ctrlMode;
  /** SPI Mode flag (8/16-bit) */
  uint8_t spiMode;
  } IPS8200HQ_Object_t;

/** IPS8200HQ (Parallel Interface) component capabilities  */
typedef struct
{
  /** Number of channels */
  uint8_t nbChannels;
  /** First control pin */
  uint8_t firstCtrlPin;
  /** Number of control pins */
  uint8_t nbCtrlPins;
} IPS8200HQ_Capabilities_t;

/** IPS8200HQ (Parallel Interface) common driver functions */
typedef struct
{
  /** pointer to Init function */
  int32_t (*Init)(IPS8200HQ_Object_t *);
  /** pointer to DeInit function */
  int32_t (*DeInit)(IPS8200HQ_Object_t *);
  /** pointer to ReadId function */
  int32_t (*ReadID)(IPS8200HQ_Object_t *, uint32_t *);
  /** pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(IPS8200HQ_Object_t *, IPS8200HQ_Capabilities_t *);
  /** pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(IPS8200HQ_Object_t *, uint8_t *);
  /** pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(IPS8200HQ_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(IPS8200HQ_Object_t *, uint8_t, uint8_t);
  /** pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(IPS8200HQ_Object_t *, uint8_t *);
  /** pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(IPS8200HQ_Object_t *, uint8_t);
  /** pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(IPS8200HQ_Object_t *, uint8_t, uint16_t *);
  /** pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(IPS8200HQ_Object_t *, uint8_t, uint16_t);
  /** pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(IPS8200HQ_Object_t *, uint8_t, uint8_t *);
  /** pointer to GetChannelDc function */
  int32_t (*SetChannelDc)(IPS8200HQ_Object_t *, uint8_t, uint8_t);
  /** pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(IPS8200HQ_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(IPS8200HQ_Object_t *, uint8_t, uint8_t);
  /** pointer to PwmTick function */
  int32_t (*PwmTick)(IPS8200HQ_Object_t *);
  /** pointer to GetCtrlPinStatus function */
  int32_t (*GetCtrlPinStatus)(IPS8200HQ_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetCtrlPinStatus function */
  int32_t (*SetCtrlPinStatus)(IPS8200HQ_Object_t *, uint8_t, uint8_t);
  /** pointer to SetOperatingMode function */
  int32_t (*SetOperatingMode)(IPS8200HQ_Object_t *, uint8_t *);
  /** pointer to GetChipType function */
  int32_t (*GetChipType)(IPS8200HQ_Object_t *, uint8_t *);
} IPS8200HQ_CommonDrv_t;
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC

/** IPS8200HQ (SPI Interface) device pin structure */
typedef struct
{
  /** SPI_SS GPIO Port definition */
  GPIO_TypeDef *SPI_SS_GPort;
  /** SPI_SS GPIO Pin definition */
  uint16_t SPI_SS_GPin;
  /** OUT_EN GPIO Port definition */
  GPIO_TypeDef *OUT_EN_GPort;
  /** OUT_EN GPIO Pin definition */
  uint16_t OUT_EN_GPin;
  /** WD GPIO Port definition */
  GPIO_TypeDef *WD_GPort;
  /** WD GPIO Pin definition */
  uint16_t WD_GPin;

  /** SEL2_L GPIO Port definition */
  GPIO_TypeDef *SEL2_L_GPort;
  /** SEL2_L GPIO Pin definition */
  uint16_t SEL2_L_GPin;
  /** SEL1 GPIO Port definition */
  GPIO_TypeDef *SEL1_GPort;
  /** SEL1 GPIO Pin definition */
  uint16_t SEL1_GPin;
  /** WDEN GPIO Port definition */
  GPIO_TypeDef *WDEN_GPort;
  /** WDEN GPIO Pin definition */
  uint16_t WDEN_GPin;

  /** FAULT_L GPIO Port definition */
  GPIO_TypeDef *FAULT_L_GPort;
  /** FAULT_L GPIO Pin definition */
  uint16_t FAULT_L_GPin;
  /** PGOOD_L GPIO Port definition */
  GPIO_TypeDef *PGOOD_L_GPort;
  /** PGOOD_L GPIO Pin definition */
  uint16_t PGOOD_L_GPin;
  /** TWARN_L GPIO Port definition */
  GPIO_TypeDef *TWARN_L_GPort;
  /** TWARN_L GPIO Pin definition */
  uint16_t TWARN_L_GPin;
} IPS_RELAY_Pins_t;

/** Initialisation function type */
typedef int32_t (*IPS8200HQ_Init_Func_t)(void);
/** DeInitialisation function type */
typedef int32_t (*IPS8200HQ_DeInit_Func_t)(void);
/** GetTick function type */
typedef int32_t (*IPS8200HQ_GetTick_Func_t)(void);
/** Read fault function type */
typedef int32_t (*IPS8200HQ_Read_Fault_Func_t)(IPS_RELAY_Pins_t *, uint8_t *);
/** Set SPI Freq function type*/
typedef uint8_t (*IPS8200HQ_SetSpiFreq_Func_t)(uint32_t);
/** SPI Write input register function type */
typedef uint8_t (*IPS8200HQ_SpiWrite_Func_t)(uint8_t, uint8_t *, uint8_t *, uint8_t);

/** Write Pin function type */
typedef int32_t (*IPS8200HQ_Write_Pin_Func_t)(IPS_RELAY_Pins_t *, uint8_t , uint8_t);
/** Read Pin function type */
typedef int32_t (*IPS8200HQ_Read_Pin_Func_t)(IPS_RELAY_Pins_t *, uint8_t , uint8_t *);
/** Set PWM function type */
typedef int32_t (*IPS8200HQ_Set_Pwm_Func_t)(uint8_t);
/** Start Guard Timer */
typedef int32_t (*IPS8200HQ_Start_GuardTimer_Func_t)(void);
/** Stop Guard Timer */
typedef int32_t (*IPS8200HQ_Stop_GuardTimer_Func_t)(void);
/** Enable IRQ function */
typedef void (*IPS8200HQ_EnableIrq_Func_t)(void);
/** Disable IRQ function */
typedef void (*IPS8200HQ_DisableIrq_Func_t)(void);

/** IPS8200HQ (SPI Interface) IO structure  */
typedef struct
{
  /** Initialisation function */
  IPS8200HQ_Init_Func_t             Init;
  /** DeInitialisation function */
  IPS8200HQ_DeInit_Func_t           DeInit;
  /** Get Tick function */
  IPS8200HQ_GetTick_Func_t          GetTick;
  /** Read fault function */
  IPS8200HQ_Read_Fault_Func_t       ReadFault;
  /** SPI Write Input register function */
  IPS8200HQ_SpiWrite_Func_t         SpiWrite;
  /** Write Pin status function */
  IPS8200HQ_Write_Pin_Func_t        WritePin;
  /** Read Pin status function */
  IPS8200HQ_Read_Pin_Func_t         ReadPin;
  /** Set PWM */
  IPS8200HQ_Set_Pwm_Func_t          SetPwm;
  /** Start Guard Timer */
  IPS8200HQ_Start_GuardTimer_Func_t StartGuardTimer;
  /** Stop Guard Timer */
  IPS8200HQ_Stop_GuardTimer_Func_t  StopGuardTimer;
  /** Enable IRQ function */
  IPS8200HQ_EnableIrq_Func_t        EnableIrq;
  /** Disable IRQ function */
  IPS8200HQ_DisableIrq_Func_t       DisableIrq;
} IPS8200HQ_IO_t;

/** IPS8200HQ (SPI Interface) component object structure  */
typedef struct
{
  /** IOs substructure */
  IPS8200HQ_IO_t IO;
  /** Pins substructure */
  IPS_RELAY_Pins_t Pin;
  /** number of similar devices */
  uint8_t nbDevices;
  /** number of channels */
  uint8_t nbChannels;
  /** first control pin */
  uint8_t firstCtrl;
  /** number of control pins */
  uint8_t nbCtrls;
  /** is component initialised?*/
  uint8_t is_initialized;
  /** channel Duty cycle*/
  uint8_t channelDc[IPS8200HQ_MAX_NB_CHANNELS];
  /** Is PWM mode enabled? */
  uint8_t isPwmEnabled;
  /** channel enable bitmap for PWM management */
  uint8_t chanEnBitmap;
  /** next channel enable bitmap for PWM management */
  uint8_t nextChanEnBitmap;
  /** force resynchronisation of the PWM */
  uint8_t forcePwmResync[IPS8200HQ_MAX_NB_CHANNELS];
  /** Channel frequency */
  uint16_t channelFreq[IPS8200HQ_MAX_NB_CHANNELS];
  /** ID of the chip */
  uint16_t chipId;
  /** Action Table for each channel: tick of the next level change*/
  uint32_t chanPwmTimActionTable[IPS8200HQ_MAX_NB_CHANNELS];
  /** period of low state for each channel */
  uint32_t chanPwmTimPeriodLow[IPS8200HQ_MAX_NB_CHANNELS];
  /** period of hihg state for each channel */
  uint32_t chanPwmTimPeriodHigh[IPS8200HQ_MAX_NB_CHANNELS];
  /** PWM frequency */
  uint32_t pwmFreq;
  /** PWM tick */
  uint32_t pwmTimTickCnt[IPS8200HQ_MAX_NB_CHANNELS];
  /** Tick where the next action in PWM mode has to be performed */
  uint32_t pwmTimNextAction;
  /** channel steady state bitmap */
  uint8_t ChanSteadyStateBitmap;
  /** new channel steady state bitmap flag */
  uint8_t newChanSteadyStateBitmap;
  /** channel steady state mirror bitmap for Pwm */
  uint8_t ChanSteadyStatePwmBitmap;
  /** controls steady state bitmap */
  uint8_t ControlPinsBitmap;
  /** Instance of the current object */
  uint8_t Instance;
  /** Board is present flag */
  uint8_t isPresent;
  /** SPI frequency in Hz */
  uint32_t spiFreq;
  /** Tcss delay in us */
  uint8_t timingTcss;
  /** Twd delay in us */
  uint32_t timingTwd;
  /** Twm delay in us */
  uint32_t timingTwm;
  /** Control Mode flag (Parallel, SPI Regular or Daisy Chain) */
  uint8_t ctrlMode;
  /** SPI Mode flag (8/16-bit) */
  uint8_t spiMode;
} IPS8200HQ_Object_t;

/** IPS8200HQ (SPI Interface) component capabilities  */
typedef struct
{
  /** Number of channels */
  uint8_t nbChannels;
  /** First control pin */
  uint8_t firstCtrlPin;
  /** Number of control pins */
  uint8_t nbCtrlPins;
} IPS8200HQ_Capabilities_t;


/** IPS8200HQ (SPI Interface) common driver functions */
typedef struct
{
  /** pointer to Init function */
  int32_t (*Init)(IPS8200HQ_Object_t *);
  /** pointer to DeInit function */
  int32_t (*DeInit)(IPS8200HQ_Object_t *);
  /** pointer to ReadId function */
  int32_t (*ReadID)(IPS8200HQ_Object_t *, uint32_t *);
  /** pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(IPS8200HQ_Object_t *, IPS8200HQ_Capabilities_t *);
  /** pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(IPS8200HQ_Object_t *, uint8_t *);
  /** pointer to GetFaultRegister function */
  int32_t (*GetFaultRegister)(IPS8200HQ_Object_t *, uint16_t *);
  /** pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(IPS8200HQ_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(IPS8200HQ_Object_t *, uint8_t, uint8_t);
  /** pointer to GetCtrlPinStatus function */
  int32_t (*GetCtrlPinStatus)(IPS8200HQ_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetCtrlPinStatus function */
  int32_t (*SetCtrlPinStatus)(IPS8200HQ_Object_t *, uint8_t, uint8_t);
  /** pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(IPS8200HQ_Object_t *, uint8_t *);
  /** pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(IPS8200HQ_Object_t *, uint8_t);
  /** pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(IPS8200HQ_Object_t *, uint8_t, uint16_t *);
  /** pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(IPS8200HQ_Object_t *, uint8_t, uint16_t);
  /** pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(IPS8200HQ_Object_t *, uint8_t, uint8_t *);
  /** pointer to GetChannelDc function */
  int32_t (*SetChannelDc)(IPS8200HQ_Object_t *, uint8_t, uint8_t);
  /** pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(IPS8200HQ_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(IPS8200HQ_Object_t *, uint8_t, uint8_t);
  /** pointer to PwmTick function */
  int32_t (*PwmTick)(IPS8200HQ_Object_t *);
  /** pointer to GuardTimerTick function */
  int32_t (*GuardTimerTick)(IPS8200HQ_Object_t *);
  /** pointer to WatchdogTimerTick function */
  int32_t (*WatchdogTimerTick)(IPS8200HQ_Object_t *);
  /** pointer to QueueChannelStatus function */
  int32_t (*QueueChannelStatus)(IPS8200HQ_Object_t *, uint8_t , uint8_t);
  /** pointer to QueueAllChannelStatus function */
  int32_t (*QueueAllChannelStatus)(IPS8200HQ_Object_t *, uint8_t);
  /** pointer to SendQueuedChannelStatus function */
  int32_t (*SendQueuedChannelStatus)(void);
  /** pointer to GetFaultRegister_DaisyChain function */
  int32_t (*GetFaultRegister_DaisyChain)(uint32_t *);
  /** pointer to PwmTick function */
  int32_t (*PwmTick_DaisyChain)(void);
  /** pointer to GuardTimerTick_DaisyChain function */
  int32_t (*GuardTimerTick_DaisyChain)(void);
  /** pointer to SetOperatingMode function */
  int32_t (*SetOperatingMode)(IPS8200HQ_Object_t *, uint8_t *);
  /** pointer to GetChipType function */
  int32_t (*GetChipType)(IPS8200HQ_Object_t *, uint8_t *);
  /** pointer to EnableDaisyChain function */
  int32_t (*EnableDaisyChain)(IPS8200HQ_Object_t *, uint8_t);
} IPS8200HQ_CommonDrv_t;
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup IPS8200HQ_Exported_Variables IPS8200HQ Exported Variables
  * @{
  */

extern uint8_t Device_System_CtrlMode[IPS8200HQ_SPI_DC_INSTANCES_NBR];
extern uint8_t Device_System_WdMode[IPS8200HQ_SPI_DC_INSTANCES_NBR];
extern uint8_t Device_System_ChipType;
extern uint8_t Device_System_PWMEnable_bitmap;
extern uint8_t Device_System_State_bitmap;
extern uint8_t IPS_NbInstances;
extern uint8_t IPS_NbDevices;
extern IPS8200HQ_CommonDrv_t IPS8200HQ_COMMON_Driver;

#ifdef APP_SPI_IFC
extern uint8_t spiPreemptionByIsr;
extern uint8_t isrFlag;
extern int16_t spiLockTime;
extern int32_t watchdogTime;
extern int32_t watchdogHoldTime;
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Exported macros --------------------------------------------------------*/

/** @defgroup IPS8200HQ_Exported_Macros IPS8200HQ Exported Macros
  * @{
  */

/** Define TRUE */
#ifndef TRUE
#define TRUE ((uint8_t) 1)
#endif /* #ifndef TRUE */

/** Define FALSE */
#ifndef FALSE
#define FALSE ((uint8_t) 0)
#endif /* #ifndef FALSE */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup IPS8200HQ_Exported_Functions IPS8200HQ Exported Functions
  * @{
  */

#ifdef APP_PAR_IFC
int32_t IPS8200HQ_GetAllChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t *pChanStatusBitmap);
int32_t IPS8200HQ_GetCapabilities(IPS8200HQ_Object_t *pObj, IPS8200HQ_Capabilities_t *pCapabilities);
int32_t IPS8200HQ_GetChannelDc(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc);
int32_t IPS8200HQ_GetChannelFreq(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq);
int32_t IPS8200HQ_GetChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus);
int32_t IPS8200HQ_GetFaultStatus(IPS8200HQ_Object_t *pObj, uint8_t *pFaultStatus);
int32_t IPS8200HQ_GetPwmEnable(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled);
int32_t IPS8200HQ_DeInit(IPS8200HQ_Object_t *pObj);
int32_t IPS8200HQ_Init(IPS8200HQ_Object_t *pObj);
int32_t IPS8200HQ_ReadID(IPS8200HQ_Object_t *pObj, uint32_t *pId);
int32_t IPS8200HQ_RegisterBusIO(IPS8200HQ_Object_t *pObj, IPS8200HQ_IO_t *pIO);
int32_t IPS8200HQ_SetAllChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t IPS8200HQ_SetChannelDc(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc);
int32_t IPS8200HQ_SetChannelFreq(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq);
int32_t IPS8200HQ_SetChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t IPS8200HQ_SetPwmEnable(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t EnablePwm);
int32_t IPS8200HQ_PwmTick(IPS8200HQ_Object_t *pObj);
int32_t IPS8200HQ_GetCtrlPinStatus(IPS8200HQ_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t IPS8200HQ_SetCtrlPinStatus(IPS8200HQ_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t IPS8200HQ_SetOperatingMode(IPS8200HQ_Object_t *pObj, uint8_t *pCtrlMode);
int32_t IPS8200HQ_GetChipType(IPS8200HQ_Object_t *pObj, uint8_t *pChipType);
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
int32_t IPS8200HQ_GetChannelFreq(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq);
int32_t IPS8200HQ_GetChannelDc(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc);
int32_t IPS8200HQ_GetPwmEnable(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled);
int32_t IPS8200HQ_SetChannelDc(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc);
int32_t IPS8200HQ_SetChannelFreq(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq);
int32_t IPS8200HQ_SetPwmEnable(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t EnablePwm);
int32_t IPS8200HQ_PwmTick(IPS8200HQ_Object_t *pObj);
int32_t IPS8200HQ_GuardTimerTick(IPS8200HQ_Object_t *pObj);
int32_t IPS8200HQ_WatchdogTimerTick(IPS8200HQ_Object_t *pObj);
int32_t IPS8200HQ_PwmTick_DaisyChain(void);
int32_t IPS8200HQ_GuardTimerTick_DaisyChain(void);
int32_t IPS8200HQ_GetChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus);
int32_t IPS8200HQ_GetAllChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t *pChanStatusBitmap);
int32_t IPS8200HQ_GetCapabilities(IPS8200HQ_Object_t *pObj, IPS8200HQ_Capabilities_t *pCapabilities);
int32_t IPS8200HQ_GetFaultStatus(IPS8200HQ_Object_t *pObj, uint8_t *pFaultStatus);
int32_t IPS8200HQ_GetFaultRegister(IPS8200HQ_Object_t *pObj, uint16_t *pFaultRegister);
int32_t IPS8200HQ_DeInit(IPS8200HQ_Object_t *pObj);
int32_t IPS8200HQ_Init(IPS8200HQ_Object_t *pObj);
int32_t IPS8200HQ_ReadID(IPS8200HQ_Object_t *pObj, uint32_t *pId);
int32_t IPS8200HQ_RegisterBusIO(IPS8200HQ_Object_t *pObj, IPS8200HQ_IO_t *pIO);
int32_t IPS8200HQ_SetAllChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t IPS8200HQ_SetChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t IPS8200HQ_GetCtrlPinStatus(IPS8200HQ_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t IPS8200HQ_SetCtrlPinStatus(IPS8200HQ_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t IPS8200HQ_QueueChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t IPS8200HQ_QueueAllChannelStatus(IPS8200HQ_Object_t *pObj, uint8_t newChanBitmap);
int32_t IPS8200HQ_SendQueuedChannelStatus(void);
int32_t IPS8200HQ_GetFaultRegister_DaisyChain(uint32_t *pFaultRegister);
int32_t IPS8200HQ_SetAllChannelPwmStatus(IPS8200HQ_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t IPS8200HQ_QueueAllChannelPwmStatus(IPS8200HQ_Object_t *pObj, uint8_t newChanBitmap);
int32_t IPS8200HQ_SendQueuedPwmChannelStatus(void);
int32_t IPS8200HQ_SetOperatingMode(IPS8200HQ_Object_t *pObj, uint8_t *pCtrlMode);
int32_t IPS8200HQ_GetChipType(IPS8200HQ_Object_t *pObj, uint8_t *pChipType);
int32_t IPS8200HQ_EnableDaisyChain(IPS8200HQ_Object_t *pObj, uint8_t DcEnable);
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* #ifndef IPS8200HQ_H */
