/**
  ******************************************************************************
  * @file    ips1025h_32.h
  * @author  AMS IPC Application Team
  * @brief   Header for ips1025h_32.c module
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
#ifndef IPS1025H_32_H
#define IPS1025H_32_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include "ips1025h_32_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */


/** @addtogroup IPS1025H_32 IPS1025H_32
  * @{
  */

/* Exported Constants --------------------------------------------------------*/

/** @defgroup IPS1025H_32_Exported_Constants IPS1025H_32 Exported Constants
  * @{
  */

/* Dev capabilities for IPS1025H_32 */
/** IPS1025H_32 ID  */
#define IPS1025H_32_CHIP_ID (1025U)

/** Maximum number of devices supported */
#define IPS1025H_32_DEVICES_NBR (1U)

/** Maximum channel frequency in tenth of Hz */
#define IPS1025H_32_MAX_CHAN_FREQ (1000U)

/** Max number of channels by switch IPS1025H_32 */
#define IPS1025H_32_MAX_NB_CHANNELS (1U)

/* Dev pins for IPS1025H_32 */
/* Board 0 */
/** IN1 Port 0 */
#define IPS1025H_32_0_IN1_GPIO_PORT IN1_GPIO_Port
/** IN1 Pin 0 */
#define IPS1025H_32_0_IN1_GPIO_PIN IN1_Pin
/** FLT1 Port 0 */
#define IPS1025H_32_0_FLT1_GPIO_PORT FLT1_GPIO_Port
/** FLT1 Pin 0 */
#define IPS1025H_32_0_FLT1_GPIO_PIN FLT1_Pin
/** FLT2 Port 0 */
#define IPS1025H_32_0_FLT2_GPIO_PORT FLT2_GPIO_Port
/** FLT2 Pin 0 */
#define IPS1025H_32_0_FLT2_GPIO_PIN FLT2_Pin

/* Board 1 */
/** IN1 Port 1 */
#define IPS1025H_32_1_IN1_GPIO_PORT IN1_Alt1_GPIO_Port
/** IN1 Pin 1 */
#define IPS1025H_32_1_IN1_GPIO_PIN IN1_Alt1_Pin
/** FLT1 Port 1 */
#define IPS1025H_32_1_FLT1_GPIO_PORT FLT1_Alt1_GPIO_Port
/** FLT1 Pin 1 */
#define IPS1025H_32_1_FLT1_GPIO_PIN FLT1_Alt1_Pin
/** FLT2 Port 1 */
#define IPS1025H_32_1_FLT2_GPIO_PORT FLT2_Alt1_GPIO_Port
/** FLT2 Pin 1 */
#define IPS1025H_32_1_FLT2_GPIO_PIN FLT2_Alt1_Pin

/* Board 2 */
/** IN1 Port 2 */
#define IPS1025H_32_2_IN1_GPIO_PORT IN1_Alt2_GPIO_Port
/** IN1 Pin 2 */
#define IPS1025H_32_2_IN1_GPIO_PIN IN1_Alt2_Pin
/** FLT1 Port 2 */
#define IPS1025H_32_2_FLT1_GPIO_PORT FLT1_Alt2_GPIO_Port
/** FLT1 Pin 2 */
#define IPS1025H_32_2_FLT1_GPIO_PIN FLT1_Alt2_Pin
/** FLT2 Port 2 */
#define IPS1025H_32_2_FLT2_GPIO_PORT FLT2_Alt2_GPIO_Port
/** FLT2 Pin 2 */
#define IPS1025H_32_2_FLT2_GPIO_PIN FLT2_Alt2_Pin

/* Board 3 */
/** IN1 Port 3 */
#define IPS1025H_32_3_IN1_GPIO_PORT IN1_Alt3_GPIO_Port
/** IN1 Pin 3 */
#define IPS1025H_32_3_IN1_GPIO_PIN IN1_Alt3_Pin
/** FLT1 Port 3 */
#define IPS1025H_32_3_FLT1_GPIO_PORT FLT1_Alt3_GPIO_Port
#/** FLT1 Pin 3 */
#define IPS1025H_32_3_FLT1_GPIO_PIN FLT1_Alt3_Pin
/** FLT2 Port 3 */
#define IPS1025H_32_3_FLT2_GPIO_PORT FLT2_Alt3_GPIO_Port
/** FLT2 Pin 3 */
#define IPS1025H_32_3_FLT2_GPIO_PIN FLT2_Alt3_Pin

/* Return codes */
/** IPS1025H_32 Ok codes  */
#define IPS_SWITCH_OK (0)

/** IPS1025H_32 Error code  */
#define IPS_SWITCH_ERROR (-1)

/**
  * @}
  */

/* Exported Types  -------------------------------------------------------*/

/** @defgroup IPS1025H_32_Exported_Types IPS1025H_32 Exported Types
  * @{
  */

/** IPS1025H_32 device pin structure */
typedef struct
{
  /** IN1 GPIO Port definition */
  GPIO_TypeDef *IN1_GPort;
  /** IN1 GPIO Pin definition */
  uint16_t IN1_GPin;
  /** FLT1 GPIO Port definition */
  GPIO_TypeDef *FLT1_GPort;
  /** FLT1 GPIO Pin definition */
  uint16_t FLT1_GPin;
  /** FLT2 GPIO Port definition */
  GPIO_TypeDef *FLT2_GPort;
  /** FLT2 GPIO Pin definition */
  uint16_t FLT2_GPin;
} IPS_SWITCH_Pins_t;

/** Initialisation function  type*/
typedef int32_t (*IPS1025H_32_Init_Func)(void);
/** DeInitialisation function  type*/
typedef int32_t (*IPS1025H_32_DeInit_Func)(void);
/** GetTick function  type*/
typedef int32_t (*IPS1025H_32_GetTick_Func)(void);
/** Read fault function  type*/
typedef int32_t (*IPS1025H_32_Read_Fault_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Write channel function  type*/
typedef int32_t (*IPS1025H_32_Write_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t);
/** Read channel function  type*/
typedef int32_t (*IPS1025H_32_Read_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t , uint8_t *);
/** Write all channels function  type*/
typedef int32_t (*IPS1025H_32_Write_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t);
/** Read all channels function  type*/
typedef int32_t (*IPS1025H_32_Read_All_Chan_Func)(IPS_SWITCH_Pins_t *, uint8_t *);
/** Set PWM function  type*/
typedef int32_t (*IPS1025H_32_Set_Pwm_Func)(uint8_t);

/** IPS1025H_32 IO structure  */
typedef struct
{
  /** Initialisation function */
  IPS1025H_32_Init_Func             Init;
  /** DeInitialisation function */
  IPS1025H_32_DeInit_Func           DeInit;
  /** Get Tick function */
  IPS1025H_32_GetTick_Func          GetTick;
  /** Read fault function */
  IPS1025H_32_Read_Fault_Func       ReadFault;
  /** Write Channel status function */
  IPS1025H_32_Write_Chan_Func       WriteChan;
  /** Read Channel status function */
  IPS1025H_32_Read_Chan_Func        ReadChan;
  /** Write All Channels status function */
  IPS1025H_32_Write_All_Chan_Func   WriteAllChan;
  /** Read All Channels status function */
  IPS1025H_32_Read_All_Chan_Func    ReadAllChan;
  /** Set PWM function */
  IPS1025H_32_Set_Pwm_Func          SetPwm;
} IPS1025H_32_IO_t;

/** IPS1025H_32 component object structure */
typedef struct
{
  /** IOs substructure */
  IPS1025H_32_IO_t IO;
  /** Pins substructure */
  IPS_SWITCH_Pins_t Pin;
  /** number of similar devices */
  uint8_t nbDevices;
  /** number of channels */
  uint8_t nbChannels;
  /** is component initialised?*/
  uint8_t is_initialized;
  /** channel Duty cycle*/
  uint8_t channelDc[IPS1025H_32_MAX_NB_CHANNELS];
  /** Is PWM mode enabled? */
  uint8_t isPwmEnabled;
  /** channel enable bitmap for PWM management */
  uint8_t chanEnBitmap;
  /** next channel enable bitmap for PWM management */
  uint8_t nextChanEnBitmap;
  /** force resynchronisation of the PWM */
  uint8_t forcePwmResync[IPS1025H_32_MAX_NB_CHANNELS];
  /** Channel frequency */
  uint16_t channelFreq[IPS1025H_32_MAX_NB_CHANNELS];
  /** ID of the chip */
  uint16_t chipId;
  /** Action Table for each channel: tick of the next level change*/
  uint32_t chanPwmTimActionTable[IPS1025H_32_MAX_NB_CHANNELS];
  /** period of low state for each channel */
  uint32_t chanPwmTimPeriodLow[IPS1025H_32_MAX_NB_CHANNELS];
  /** period of hihg state for each channel */
  uint32_t chanPwmTimPeriodHigh[IPS1025H_32_MAX_NB_CHANNELS];
  /** PWM frequency */
  uint32_t pwmFreq;
  /** PWM tick */
  uint32_t pwmTimTickCnt[IPS1025H_32_MAX_NB_CHANNELS];
  /** Tick where the next action in PWM mode has to be performed */
  uint32_t pwmTimNextAction;
  /** channel steady state bitmap */
  uint8_t ChanSteadyStateBitmap;
  /** Instance of the current object */
  uint8_t Instance;
  /** Board is present flag */
  uint8_t isPresent;
} IPS1025H_32_Object_t;

/** IPS1025H_32 component capabilities  */
typedef struct
{
  /** Number of channels */
  uint8_t nbChannels;
} IPS1025H_32_Capabilities_t;


/** IPS1025H_32 common driver functions */
typedef struct
{
  /** pointer to Init function */
  int32_t (*Init)(IPS1025H_32_Object_t *);
  /** pointer to DeInit function */
  int32_t (*DeInit)(IPS1025H_32_Object_t *);
  /** pointer to ReadId function */
  int32_t (*ReadID)(IPS1025H_32_Object_t *, uint32_t *);
  /** pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(IPS1025H_32_Object_t *, IPS1025H_32_Capabilities_t *);
  /** pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(IPS1025H_32_Object_t *, uint8_t *);
  /** pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(IPS1025H_32_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(IPS1025H_32_Object_t *, uint8_t, uint8_t );
  /** pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(IPS1025H_32_Object_t *, uint8_t *);
  /** pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(IPS1025H_32_Object_t *, uint8_t);
  /** pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(IPS1025H_32_Object_t *, uint8_t, uint16_t *);
  /** pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(IPS1025H_32_Object_t *, uint8_t, uint16_t);
  /** pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(IPS1025H_32_Object_t *, uint8_t, uint8_t *);
  /** pointer to GetChannelDc function */
  int32_t (*SetChannelDc)(IPS1025H_32_Object_t *, uint8_t, uint8_t);
  /** pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(IPS1025H_32_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(IPS1025H_32_Object_t *, uint8_t, uint8_t);
  /** pointer to PwmTick function */
  int32_t (*PwmTick)(IPS1025H_32_Object_t *);
} IPS1025H_32_CommonDrv_t;

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @addtogroup IPS1025H_32_Exported_Variables IPS1025H_32 Exported Variables
  * @{
  */

extern IPS1025H_32_CommonDrv_t IPS1025H_32_COMMON_Driver;
extern uint8_t SWITCH_System_PWMEnable_bitmap;
extern uint8_t IPS_NbInstances;
extern uint8_t IPS_NbDevices;

/**
  * @}
  */

/* Exported macros --------------------------------------------------------*/

/** @addtogroup IPS1025H_32_Exported_Macros IPS1025H_32 Exported Macros
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

/** @defgroup IPS1025H_32_Exported_Functions IPS1025H_32 Exported Functions
  * @{
  */
int32_t IPS1025H_32_GetAllChannelStatus(IPS1025H_32_Object_t *pObj, uint8_t *pChanStatusBitmap);
int32_t IPS1025H_32_GetCapabilities(IPS1025H_32_Object_t *pObj, IPS1025H_32_Capabilities_t *pCapabilities);
int32_t IPS1025H_32_GetChannelDc(IPS1025H_32_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc);
int32_t IPS1025H_32_GetChannelFreq(IPS1025H_32_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq);
int32_t IPS1025H_32_GetChannelStatus(IPS1025H_32_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus);
int32_t IPS1025H_32_GetFaultStatus(IPS1025H_32_Object_t *pObj, uint8_t *pFaultStatus);
int32_t IPS1025H_32_GetPwmEnable(IPS1025H_32_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled);
int32_t IPS1025H_32_DeInit(IPS1025H_32_Object_t *pObj);
int32_t IPS1025H_32_Init(IPS1025H_32_Object_t *pObj);
int32_t IPS1025H_32_ReadID(IPS1025H_32_Object_t *pObj, uint32_t *pId);
int32_t IPS1025H_32_RegisterBusIO(IPS1025H_32_Object_t *pObj, IPS1025H_32_IO_t *pIO);
int32_t IPS1025H_32_SetAllChannelStatus(IPS1025H_32_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t IPS1025H_32_SetChannelDc(IPS1025H_32_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc);
int32_t IPS1025H_32_SetChannelFreq(IPS1025H_32_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq);
int32_t IPS1025H_32_SetChannelStatus(IPS1025H_32_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t IPS1025H_32_SetPwmEnable(IPS1025H_32_Object_t *pObj, uint8_t ChanId, uint8_t PwmEnabled);
int32_t IPS1025H_32_PwmTick(IPS1025H_32_Object_t *pObj);

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

#endif /* #ifndef IPS1025H_32_H */
