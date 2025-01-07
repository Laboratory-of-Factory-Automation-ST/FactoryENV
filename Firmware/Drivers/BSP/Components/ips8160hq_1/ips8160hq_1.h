/**
  ******************************************************************************
  * @file    ips8160hq_1.h
  * @author  AMS IPC Application Team
  * @brief   Header for ips8160hq_1.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IPS8160HQ_1_H
#define IPS8160HQ_1_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include "ips8160hq_1_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */


/** @addtogroup IPS8160HQ_1 IPS8160HQ_1
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @addtogroup IPS8160HQ_1_Exported_Types IPS8160HQ_1 Exported Types
  * @{
  */

/** IPS8160HQ_1 device pin structure */
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

  /** STATUS GPIO Port definition */
  GPIO_TypeDef *STATUS_GPort;
  /** STATUS GPIO Pin definition */
  uint16_t STATUS_GPin;
} IPS_SWITCH_Pins_t;

/**
  * @}
  */

/* Exported Constants --------------------------------------------------------*/

/** @defgroup IPS8160HQ_1_Exported_Constants IPS8160HQ_1 Exported Constants
  * @{
  */

/* Dev capabilities for IPS8160HQ_1 */
/** IPS8160HQ_1 ID  */
#define IPS8160HQ_1_CHIP_ID (8160U)

/** Maximum number of devices supported */
#define IPS8160HQ_1_DEVICES_NBR (1U)

/** Maximum channel frequency in tenth of Hz */
#define IPS8160HQ_1_MAX_CHAN_FREQ (1000U)

/** Max number of channels by switch IPS8160HQ_1 */
#define IPS8160HQ_1_MAX_NB_CHANNELS (8U)

/* Dev pins for IPS8160HQ_1 */
/* Board 0 */
/** Input Pin: IN1 */
#define IPS8160HQ_1_0_IN1 (0U)
/** Input Pin: IN2 */
#define IPS8160HQ_1_0_IN2 (1U)
/** Input Pin: IN3 */
#define IPS8160HQ_1_0_IN3 (2U)
/** Input Pin: IN4 */
#define IPS8160HQ_1_0_IN4 (3U)
/** Input Pin: IN5 */
#define IPS8160HQ_1_0_IN5 (4U)
/** Input Pin: IN6 */
#define IPS8160HQ_1_0_IN6 (5U)
/** Input Pin: IN7 */
#define IPS8160HQ_1_0_IN7 (6U)
/** Input Pin: IN8 */
#define IPS8160HQ_1_0_IN8 (7U)

/** IN1 Port 0 */
#define IPS8160HQ_1_0_IN1_GPIO_PORT IN1_GPIO_Port
/** IN1 Pin 0 */
#define IPS8160HQ_1_0_IN1_GPIO_PIN IN1_Pin
/** IN2 Port 0 */
#define IPS8160HQ_1_0_IN2_GPIO_PORT IN2_GPIO_Port
/** IN2 Pin 0 */
#define IPS8160HQ_1_0_IN2_GPIO_PIN IN2_Pin
/** IN3 Port 0 */
#define IPS8160HQ_1_0_IN3_GPIO_PORT IN3_GPIO_Port
/** IN3 Pin 0 */
#define IPS8160HQ_1_0_IN3_GPIO_PIN IN3_Pin
/** IN4 Port 0 */
#define IPS8160HQ_1_0_IN4_GPIO_PORT IN4_GPIO_Port
/** IN4 Pin 0 */
#define IPS8160HQ_1_0_IN4_GPIO_PIN IN4_Pin
/** IN5 Port 0 */
#define IPS8160HQ_1_0_IN5_GPIO_PORT IN5_GPIO_Port
/** IN5 Pin 0 */
#define IPS8160HQ_1_0_IN5_GPIO_PIN IN5_Pin
/** IN6 Port 0 */
#define IPS8160HQ_1_0_IN6_GPIO_PORT IN6_GPIO_Port
/** IN6 Pin 0 */
#define IPS8160HQ_1_0_IN6_GPIO_PIN IN6_Pin
/** IN7 Port 0 */
#define IPS8160HQ_1_0_IN7_GPIO_PORT IN7_GPIO_Port
/** IN7 Pin 0 */
#define IPS8160HQ_1_0_IN7_GPIO_PIN IN7_Pin
/** IN8 Port 0 */
#define IPS8160HQ_1_0_IN8_GPIO_PORT IN8_GPIO_Port
/** IN8 Pin 0 */
#define IPS8160HQ_1_0_IN8_GPIO_PIN IN8_Pin

/** STATUS Port 0 */
#define IPS8160HQ_1_0_STATUS_GPIO_PORT STATUS_GPIO_Port
/** STATUS Pin 0 */
#define IPS8160HQ_1_0_STATUS_GPIO_PIN STATUS_Pin

/* Return codes */
/** IPS8160HQ_1 Ok codes  */
#define IPS_SWITCH_OK (0)

/** IPS8160HQ_1 Error code  */
#define IPS_SWITCH_ERROR (-1)

/**
  * @}
  */

/* Exported Types  -------------------------------------------------------*/

/** @defgroup IPS8160HQ_1_Exported_Types IPS8160HQ_1 Exported Types
  * @{
  */

/** Initialisation function  type*/
typedef int32_t (*IPS8160HQ_1_Init_Func)(void);
/** DeInitialisation function  type*/
typedef int32_t (*IPS8160HQ_1_DeInit_Func)(void);
/** GetTick function  type*/
typedef int32_t (*IPS8160HQ_1_GetTick_Func)(void);
/** Read fault function  type*/
typedef int32_t (*IPS8160HQ_1_Read_Fault_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Write channel function  type*/
typedef int32_t (*IPS8160HQ_1_Write_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read channel function  type*/
typedef int32_t (*IPS8160HQ_1_Read_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);
/** Write all channels function  type*/
typedef int32_t (*IPS8160HQ_1_Write_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t);
/** Read all channels function  type*/
typedef int32_t (*IPS8160HQ_1_Read_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Set PWM function  type*/
typedef int32_t (*IPS8160HQ_1_Set_Pwm_Func)(uint8_t);

/** IPS8160HQ_1 IO structure  */
typedef struct
{
  /** Initialisation function */
  IPS8160HQ_1_Init_Func             Init;
  /** DeInitialisation function */
  IPS8160HQ_1_DeInit_Func           DeInit;
  /** Get Tick function */
  IPS8160HQ_1_GetTick_Func          GetTick;
  /** Read fault function */
  IPS8160HQ_1_Read_Fault_Func       ReadFault;
  /** Write Channel status function */
  IPS8160HQ_1_Write_Chan_Func       WriteChan;
  /** Read Channel status function */
  IPS8160HQ_1_Read_Chan_Func        ReadChan;
  /** Write All Channels status function */
  IPS8160HQ_1_Write_All_Chan_Func   WriteAllChan;
  /** Read All Channels status function */
  IPS8160HQ_1_Read_All_Chan_Func    ReadAllChan;
  /** Set PWM */
  IPS8160HQ_1_Set_Pwm_Func          SetPwm;
} IPS8160HQ_1_IO_t;

/** IPS8160HQ_1 component object structure  */
typedef struct
{
  /** IOs substructure */
  IPS8160HQ_1_IO_t IO;
  /** Pins substructure */
  IPS_SWITCH_Pins_t Pin;
  /** number of similar devices */
  uint8_t nbDevices;
  /** number of channels */
  uint8_t nbChannels;
  /** is component initialised?*/
  uint8_t is_initialized;
  /** channel Duty cycle*/
  uint8_t channelDc[IPS8160HQ_1_MAX_NB_CHANNELS];
  /** Is PWM mode enabled? */
  uint8_t isPwmEnabled;
  /** channel enable bitmap for PWM management */
  uint8_t chanEnBitmap;
  /** next channel enable bitmap for PWM management */
  uint8_t nextChanEnBitmap;
  /** force resynchronisation of the PWM */
  uint8_t forcePwmResync[IPS8160HQ_1_MAX_NB_CHANNELS];
  /** Channel frequency */
  uint16_t channelFreq[IPS8160HQ_1_MAX_NB_CHANNELS];
  /** ID of the chip */
  uint16_t chipId;
  /** Action Table for each channel: tick of the next level change*/
  uint32_t chanPwmTimActionTable[IPS8160HQ_1_MAX_NB_CHANNELS];
  /** period of low state for each channel */
  uint32_t chanPwmTimPeriodLow[IPS8160HQ_1_MAX_NB_CHANNELS];
  /** period of hihg state for each channel */
  uint32_t chanPwmTimPeriodHigh[IPS8160HQ_1_MAX_NB_CHANNELS];
  /** PWM frequency */
  uint32_t pwmFreq;
  /** PWM tick */
  uint32_t pwmTimTickCnt[IPS8160HQ_1_MAX_NB_CHANNELS];
  /** Tick where the next action in PWM mode has to be performed */
  uint32_t pwmTimNextAction;
  /** channel steady state bitmap */
  uint8_t ChanSteadyStateBitmap;
  /** Instance of the current object */
  uint8_t Instance;
  /** Board is present flag */
  uint8_t isPresent;
} IPS8160HQ_1_Object_t;

/** IPS8160HQ_1 component capabilities  */
typedef struct
{
  /** Number of channels */
  uint8_t nbChannels;
} IPS8160HQ_1_Capabilities_t;


/** IPS8160HQ_1 common driver functions */
typedef struct
{
  /** pointer to Init function */
  int32_t (*Init)(IPS8160HQ_1_Object_t *);
  /** pointer to DeInit function */
  int32_t (*DeInit)(IPS8160HQ_1_Object_t *);
  /** pointer to ReadId function */
  int32_t (*ReadID)(IPS8160HQ_1_Object_t *, uint32_t *);
  /** pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(IPS8160HQ_1_Object_t *, IPS8160HQ_1_Capabilities_t *);
  /** pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(IPS8160HQ_1_Object_t *, uint8_t *);
  /** pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(IPS8160HQ_1_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(IPS8160HQ_1_Object_t *, uint8_t, uint8_t);
  /** pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(IPS8160HQ_1_Object_t *, uint8_t *);
  /** pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(IPS8160HQ_1_Object_t *, uint8_t);
  /** pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(IPS8160HQ_1_Object_t *, uint8_t, uint16_t *);
  /** pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(IPS8160HQ_1_Object_t *, uint8_t, uint16_t);
  /** pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(IPS8160HQ_1_Object_t *, uint8_t, uint8_t *);
  /** pointer to GetChannelDc function */
  int32_t (*SetChannelDc)(IPS8160HQ_1_Object_t *, uint8_t, uint8_t);
  /** pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(IPS8160HQ_1_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(IPS8160HQ_1_Object_t *, uint8_t, uint8_t);
  /** pointer to PwmTick function */
  int32_t (*PwmTick)(IPS8160HQ_1_Object_t *);
} IPS8160HQ_1_CommonDrv_t;

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup IPS8160HQ_1_Exported_Variables IPS8160HQ_1 Exported Variables
  * @{
  */

extern IPS8160HQ_1_CommonDrv_t IPS8160HQ_1_COMMON_Driver;
extern uint8_t SWITCH_System_PWMEnable_bitmap;
extern uint8_t IPS_NbInstances;
extern uint8_t IPS_NbDevices;

/**
  * @}
  */

/* Exported macros --------------------------------------------------------*/

/** @defgroup IPS8160HQ_1_Exported_Macros IPS8160HQ_1 Exported Macros
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


/** @defgroup IPS8160HQ_1_Exported_Functions IPS8160HQ_1 Exported Functions
  * @{
  */
int32_t IPS8160HQ_1_GetAllChannelStatus(IPS8160HQ_1_Object_t *pObj, uint8_t *pChanStatusBitmap);
int32_t IPS8160HQ_1_GetCapabilities(IPS8160HQ_1_Object_t *pObj, IPS8160HQ_1_Capabilities_t *pCapabilities);
int32_t IPS8160HQ_1_GetChannelDc(IPS8160HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc);
int32_t IPS8160HQ_1_GetChannelFreq(IPS8160HQ_1_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq);
int32_t IPS8160HQ_1_GetChannelStatus(IPS8160HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus);
int32_t IPS8160HQ_1_GetFaultStatus(IPS8160HQ_1_Object_t *pObj, uint8_t *pFaultStatus);
int32_t IPS8160HQ_1_GetPwmEnable(IPS8160HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled);
int32_t IPS8160HQ_1_DeInit(IPS8160HQ_1_Object_t *pObj);
int32_t IPS8160HQ_1_Init(IPS8160HQ_1_Object_t *pObj);
int32_t IPS8160HQ_1_ReadID(IPS8160HQ_1_Object_t *pObj, uint32_t *pId);
int32_t IPS8160HQ_1_RegisterBusIO(IPS8160HQ_1_Object_t *pObj, IPS8160HQ_1_IO_t *pIO);
int32_t IPS8160HQ_1_SetAllChannelStatus(IPS8160HQ_1_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t IPS8160HQ_1_SetChannelDc(IPS8160HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc);
int32_t IPS8160HQ_1_SetChannelFreq(IPS8160HQ_1_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq);
int32_t IPS8160HQ_1_SetChannelStatus(IPS8160HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t IPS8160HQ_1_SetPwmEnable(IPS8160HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t PwmEnabled);
int32_t IPS8160HQ_1_PwmTick(IPS8160HQ_1_Object_t *pObj);

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

#endif /* #ifndef IPS8160HQ_1_H */
