/**
  ******************************************************************************
  * @file    ips4260l.h
  * @author  AMS IPC Application Team
  * @brief   Header for ips4260l.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IPS4260L_H
#define IPS4260L_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include "ips4260l_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */


/** @addtogroup IPS4260L IPS4260L
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @addtogroup IPS4260L_Exported_Types IPS4260L Exported Types
  * @{
  */

/** IPS4260L device pin structure */
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

  /** FLT_L GPIO Port definition */
  GPIO_TypeDef *FLT_L_GPort;
  /** FLT_L GPIO Pin definition */
  uint16_t FLT_L_GPin;
  /** OL_L GPIO Port definition */
  GPIO_TypeDef *OL_L_GPort;
  /** OL_L GPIO Pin definition */
  uint16_t OL_L_GPin;

  /** DIAG1_L GPIO Port definition */
  GPIO_TypeDef *DIAG1_L_GPort;
  /** DIAG1_L GPIO Pin definition */
  uint16_t DIAG1_L_GPin;
  /** DIAG2_L GPIO Port definition */
  GPIO_TypeDef *DIAG2_L_GPort;
  /** DIAG2_L GPIO Pin definition */
  uint16_t DIAG2_L_GPin;
  /** DIAG3_L GPIO Port definition */
  GPIO_TypeDef *DIAG3_L_GPort;
  /** DIAG3_L GPIO Pin definition */
  uint16_t DIAG3_L_GPin;
  /** DIAG4_L GPIO Port definition */
  GPIO_TypeDef *DIAG4_L_GPort;
  /** DIAG4_L GPIO Pin definition */
  uint16_t DIAG4_L_GPin;
} IPS_SWITCH_Pins_t;

/**
  * @}
  */

/* Exported Constants --------------------------------------------------------*/

/** @defgroup IPS4260L_Exported_Constants IPS4260L Exported Constants
  * @{
  */

/* Dev capabilities for IPS4260L */
/** IPS4260L ID  */
#define IPS4260L_CHIP_ID (4260U)

/** Maximum number of devices supported */
#define IPS4260L_DEVICES_NBR (1U)

/** Maximum channel frequency in tenth of Hz */
#define IPS4260L_MAX_CHAN_FREQ (1000U)

/** Max number of channels by switch IPS4260L */
#define IPS4260L_MAX_NB_CHANNELS (4U)

/* Dev pins for IPS4260L */
/* Board 0 */
/** Input Pin: IN1 */
#define IPS4260L_0_IN1 (0U)
/** Input Pin: IN2 */
#define IPS4260L_0_IN2 (1U)
/** Input Pin: IN3 */
#define IPS4260L_0_IN3 (2U)
/** Input Pin: IN4 */
#define IPS4260L_0_IN4 (3U)

/** IN1 Port 0 */
#define IPS4260L_0_IN1_GPIO_PORT IN1_GPIO_Port
/** IN1 Pin 0 */
#define IPS4260L_0_IN1_GPIO_PIN IN1_Pin
/** IN2 Port 0 */
#define IPS4260L_0_IN2_GPIO_PORT IN2_GPIO_Port
/** IN2 Pin 0 */
#define IPS4260L_0_IN2_GPIO_PIN IN2_Pin
/** IN3 Port 0 */
#define IPS4260L_0_IN3_GPIO_PORT IN3_GPIO_Port
/** IN3 Pin 0 */
#define IPS4260L_0_IN3_GPIO_PIN IN3_Pin
/** IN4 Port 0 */
#define IPS4260L_0_IN4_GPIO_PORT IN4_GPIO_Port
/** IN4 Pin 0 */
#define IPS4260L_0_IN4_GPIO_PIN IN4_Pin

/** FLT_L Port 0 */
#define IPS4260L_0_FLT_L_GPIO_PORT FLT_L_GPIO_Port
/** FLT_L Pin 0 */
#define IPS4260L_0_FLT_L_GPIO_PIN FLT_L_Pin
/** OL_L Port 0 */
#define IPS4260L_0_OL_L_GPIO_PORT OL_L_GPIO_Port
/** OL_L Pin 0 */
#define IPS4260L_0_OL_L_GPIO_PIN OL_L_Pin
/** DIAG1 Port 0 */
#define IPS4260L_0_DIAG1_L_GPIO_PORT DIAG1_L_GPIO_Port
/** DIAG1 Pin 0 */
#define IPS4260L_0_DIAG1_L_GPIO_PIN DIAG1_L_Pin
/** DIAG2 Port 0 */
#define IPS4260L_0_DIAG2_L_GPIO_PORT DIAG2_L_GPIO_Port
/** DIAG2 Pin 0 */
#define IPS4260L_0_DIAG2_L_GPIO_PIN DIAG2_L_Pin
/** DIAG3 Port 0 */
#define IPS4260L_0_DIAG3_L_GPIO_PORT DIAG3_L_GPIO_Port
/** DIAG3 Pin 0 */
#define IPS4260L_0_DIAG3_L_GPIO_PIN DIAG3_L_Pin
/** DIAG4 Port 0 */
#define IPS4260L_0_DIAG4_L_GPIO_PORT DIAG4_L_GPIO_Port
/** DIAG4 Pin 0 */
#define IPS4260L_0_DIAG4_L_GPIO_PIN DIAG4_L_Pin

/* Return codes */
/** IPS4260L Ok codes  */
#define IPS_SWITCH_OK (0)

/** IPS4260L Error code  */
#define IPS_SWITCH_ERROR (-1)

/**
  * @}
  */

/* Exported Types  -------------------------------------------------------*/

/** @defgroup IPS4260L_Exported_Types IPS4260L Exported Types
  * @{
  */

/** Initialisation function  type*/
typedef int32_t (*IPS4260L_Init_Func)(void);
/** DeInitialisation function  type*/
typedef int32_t (*IPS4260L_DeInit_Func)(void);
/** GetTick function  type*/
typedef int32_t (*IPS4260L_GetTick_Func)(void);
/** Read fault function  type*/
typedef int32_t (*IPS4260L_Read_Fault_Func)(IPS_SWITCH_Pins_t *, uint16_t *);
/** Write channel function  type*/
typedef int32_t (*IPS4260L_Write_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read channel function  type*/
typedef int32_t (*IPS4260L_Read_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);
/** Write all channels function  type*/
typedef int32_t (*IPS4260L_Write_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t);
/** Read all channels function  type*/
typedef int32_t (*IPS4260L_Read_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Set PWM function  type*/
typedef int32_t (*IPS4260L_Set_Pwm_Func)(uint8_t);
/** Enable IRQ function */
typedef void (*IPS4260L_EnableIrq_Func_t)(void);
/** Disable IRQ function */
typedef void (*IPS4260L_DisableIrq_Func_t)(void);

/** IPS4260L IO structure  */
typedef struct
{
  /** Initialisation function */
  IPS4260L_Init_Func             Init;
  /** DeInitialisation function */
  IPS4260L_DeInit_Func           DeInit;
  /** Get Tick function */
  IPS4260L_GetTick_Func          GetTick;
  /** Read fault function */
  IPS4260L_Read_Fault_Func       ReadFault;
  /** Write Channel status function */
  IPS4260L_Write_Chan_Func       WriteChan;
  /** Read Channel status function */
  IPS4260L_Read_Chan_Func        ReadChan;
  /** Write All Channels status function */
  IPS4260L_Write_All_Chan_Func   WriteAllChan;
  /** Read All Channels status function */
  IPS4260L_Read_All_Chan_Func    ReadAllChan;
  /** Set PWM */
  IPS4260L_Set_Pwm_Func          SetPwm;
  /** Enable IRQ function */
  IPS4260L_EnableIrq_Func_t        EnableIrq;
  /** Disable IRQ function */
  IPS4260L_DisableIrq_Func_t       DisableIrq;
} IPS4260L_IO_t;

/** IPS4260L component object structure  */
typedef struct
{
  /** IOs substructure */
  IPS4260L_IO_t IO;
  /** Pins substructure */
  IPS_SWITCH_Pins_t Pin;
  /** number of similar devices */
  uint8_t nbDevices;
  /** number of channels */
  uint8_t nbChannels;
  /** is component initialised?*/
  uint8_t is_initialized;
  /** channel Duty cycle*/
  uint8_t channelDc[IPS4260L_MAX_NB_CHANNELS];
  /** Is PWM mode enabled? */
  uint8_t isPwmEnabled;
  /** channel enable bitmap for PWM management */
  uint8_t chanEnBitmap;
  /** next channel enable bitmap for PWM management */
  uint8_t nextChanEnBitmap;
  /** force resynchronisation of the PWM */
  uint8_t forcePwmResync[IPS4260L_MAX_NB_CHANNELS];
  /** Channel frequency */
  uint16_t channelFreq[IPS4260L_MAX_NB_CHANNELS];
  /** ID of the chip */
  uint16_t chipId;
  /** Action Table for each channel: tick of the next level change*/
  uint32_t chanPwmTimActionTable[IPS4260L_MAX_NB_CHANNELS];
  /** period of low state for each channel */
  uint32_t chanPwmTimPeriodLow[IPS4260L_MAX_NB_CHANNELS];
  /** period of hihg state for each channel */
  uint32_t chanPwmTimPeriodHigh[IPS4260L_MAX_NB_CHANNELS];
  /** PWM frequency */
  uint32_t pwmFreq;
  /** PWM tick */
  uint32_t pwmTimTickCnt[IPS4260L_MAX_NB_CHANNELS];
  /** Tick where the next action in PWM mode has to be performed */
  uint32_t pwmTimNextAction;
  /** channel steady state bitmap */
  uint8_t ChanSteadyStateBitmap;
  /** Instance of the current object */
  uint8_t Instance;
  /** Board is present flag */
  uint8_t isPresent;
} IPS4260L_Object_t;

/** IPS4260L component capabilities  */
typedef struct
{
  /** Number of channels */
  uint8_t nbChannels;
} IPS4260L_Capabilities_t;


/** IPS4260L common driver functions */
typedef struct
{
  /** pointer to Init function */
  int32_t (*Init)(IPS4260L_Object_t *);
  /** pointer to DeInit function */
  int32_t (*DeInit)(IPS4260L_Object_t *);
  /** pointer to ReadId function */
  int32_t (*ReadID)(IPS4260L_Object_t *, uint32_t *);
  /** pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(IPS4260L_Object_t *, IPS4260L_Capabilities_t *);
  /** pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(IPS4260L_Object_t *, uint16_t *);
  /** pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(IPS4260L_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(IPS4260L_Object_t *, uint8_t, uint8_t);
  /** pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(IPS4260L_Object_t *, uint8_t *);
  /** pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(IPS4260L_Object_t *, uint8_t);
  /** pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(IPS4260L_Object_t *, uint8_t, uint16_t *);
  /** pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(IPS4260L_Object_t *, uint8_t, uint16_t);
  /** pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(IPS4260L_Object_t *, uint8_t, uint8_t *);
  /** pointer to GetChannelDc function */
  int32_t (*SetChannelDc)(IPS4260L_Object_t *, uint8_t, uint8_t);
  /** pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(IPS4260L_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(IPS4260L_Object_t *, uint8_t, uint8_t);
  /** pointer to PwmTick function */
  int32_t (*PwmTick)(IPS4260L_Object_t *);
} IPS4260L_CommonDrv_t;

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup IPS4260L_Exported_Variables IPS4260L Exported Variables
  * @{
  */

extern IPS4260L_CommonDrv_t IPS4260L_COMMON_Driver;
extern uint8_t SWITCH_System_PWMEnable_bitmap;
extern uint8_t IPS_NbInstances;
extern uint8_t IPS_NbDevices;
extern uint8_t itDisableBitmap;

/**
  * @}
  */

/* Exported macros --------------------------------------------------------*/

/** @defgroup IPS4260L_Exported_Macros IPS4260L Exported Macros
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


/** @defgroup IPS4260L_Exported_Functions IPS4260L Exported Functions
  * @{
  */
int32_t IPS4260L_GetAllChannelStatus(IPS4260L_Object_t *pObj, uint8_t *pChanStatusBitmap);
int32_t IPS4260L_GetCapabilities(IPS4260L_Object_t *pObj, IPS4260L_Capabilities_t *pCapabilities);
int32_t IPS4260L_GetChannelDc(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc);
int32_t IPS4260L_GetChannelFreq(IPS4260L_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq);
int32_t IPS4260L_GetChannelStatus(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus);
int32_t IPS4260L_GetFaultStatus(IPS4260L_Object_t *pObj, uint16_t *pFaultStatus);
int32_t IPS4260L_GetPwmEnable(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled);
int32_t IPS4260L_DeInit(IPS4260L_Object_t *pObj);
int32_t IPS4260L_Init(IPS4260L_Object_t *pObj);
int32_t IPS4260L_ReadID(IPS4260L_Object_t *pObj, uint32_t *pId);
int32_t IPS4260L_RegisterBusIO(IPS4260L_Object_t *pObj, IPS4260L_IO_t *pIO);
int32_t IPS4260L_SetAllChannelStatus(IPS4260L_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t IPS4260L_SetChannelDc(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc);
int32_t IPS4260L_SetChannelFreq(IPS4260L_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq);
int32_t IPS4260L_SetChannelStatus(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t IPS4260L_SetPwmEnable(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t PwmEnabled);
int32_t IPS4260L_PwmTick(IPS4260L_Object_t *pObj);

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

#endif /* #ifndef IPS4260L_H */
