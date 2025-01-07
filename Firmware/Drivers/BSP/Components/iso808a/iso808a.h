/**
  ******************************************************************************
  * @file    iso808a.h
  * @author  AMS IPC Application Team
  * @brief   Header for iso808a.c module
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
#ifndef ISO808A_H
#define ISO808A_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include "iso808a_conf.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */

/** @addtogroup ISO808A ISO808A
  * @{
  */

/* Exported Constants --------------------------------------------------------*/

/** ISO808A device pin structure */
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

  /** STATUS GPIO Port definition */
  GPIO_TypeDef *STATUS_GPort;
  /** STATUS GPIO Pin definition */
  uint16_t STATUS_GPin;
  /** PGOOD GPIO Port definition */
  GPIO_TypeDef *PGOOD_GPort;
  /** PGOOD GPIO Pin definition */
  uint16_t PGOOD_GPin;
} IPS_RELAY_Pins_t;

/** @defgroup ISO808A_Exported_Constants ISO808A Exported Constants
  * @{
  */

/* Dev capabilities for ISO808A */
/** ISO808A ID  */
#define ISO808A_CHIP_ID (808U)

/** Maximum channel frequency in tenth of Hz */
#define ISO808A_MAX_CHAN_FREQ (1000U)

/** Max number of channels by switch ISO808A */
#define ISO808A_MAX_NB_CHANNELS (8U)

/** First control pin by switch ISO808A board 0 */
#define ISO808A_0_FIRST_CONTROL (0U)

/** First control pin by switch ISO808A board 1 */
#define ISO808A_1_FIRST_CONTROL (2U)

/** Max number of control pins by switch ISO808A */
#define ISO808A_MAX_NB_CONTROLS (2U)

/** Guard Timer tick in us */
#define ISO808A_GUARD_TIMER_TICK_IN_US (1000000U/(uint8_t)(GUARD_TIMER_FREQ))

/* Dev pins for ISO808A */
/* Board 0 */
/** Device Chan: IN1 */
#define ISO808A_0_IN1 (0U)
/** Device Chan: IN2 */
#define ISO808A_0_IN2 (1U)
/** Device Chan: IN3 */
#define ISO808A_0_IN3 (2U)
/** Device Chan: IN4 */
#define ISO808A_0_IN4 (3U)
/** Device Chan: IN5 */
#define ISO808A_0_IN5 (4U)
/** Device Chan: IN6 */
#define ISO808A_0_IN6 (5U)
/** Device Chan: IN7 */
#define ISO808A_0_IN7 (6U)
/** Device Chan: IN8 */
#define ISO808A_0_IN8 (7U)

/** Input Pin: SPI_CLK */
#define ISO808A_0_SPI_CLK (0U)
/** Input Pin: SPI_MISO */
#define ISO808A_0_SPI_MISO (1U)
/** Input Pin: SPI_MOSI */
#define ISO808A_0_SPI_MOSI (2U)

/** Control Pin: SPI_SS */
#define ISO808A_0_SPI_SS (0U)
/** Control Pin: OUT_EN */
#define ISO808A_0_OUT_EN (1U)


/** SPI_SS Port 0 */
#define ISO808A_0_SPI_SS_GPIO_PORT SPI_SS_GPIO_Port
/** SPI_SS Pin 0 */
#define ISO808A_0_SPI_SS_GPIO_PIN SPI_SS_Pin
/** OUT_EN Port 0 */
#define ISO808A_0_OUT_EN_GPIO_PORT OUT_EN_GPIO_Port
/** OUT_EN Pin 0 */
#define ISO808A_0_OUT_EN_GPIO_PIN OUT_EN_Pin

/** STATUS Port 0 */
#define ISO808A_0_STATUS_GPIO_PORT STATUS_GPIO_Port
/** STATUS Pin 0 */
#define ISO808A_0_STATUS_GPIO_PIN STATUS_Pin
/** PGOOD Port 0 */
#define ISO808A_0_PGOOD_GPIO_PORT PGOOD_GPIO_Port
/** PGOOD Pin 0 */
#define ISO808A_0_PGOOD_GPIO_PIN PGOOD_Pin

/* Board 1 */
/** Device Chan: IN1 */
#define ISO808A_1_IN1 (0U)
/** Device Chan: IN2 */
#define ISO808A_1_IN2 (1U)
/** Device Chan: IN3 */
#define ISO808A_1_IN3 (2U)
/** Device Chan: IN4 */
#define ISO808A_1_IN4 (3U)
/** Device Chan: IN5 */
#define ISO808A_1_IN5 (4U)
/** Device Chan: IN6 */
#define ISO808A_1_IN6 (5U)
/** Device Chan: IN7 */
#define ISO808A_1_IN7 (6U)
/** Device Chan: IN8 */
#define ISO808A_1_IN8 (7U)

/** Input Pin: SPI_CLK */
#define ISO808A_1_SPI_CLK (3U)
/** Input Pin: SPI_MISO */
#define ISO808A_1_SPI_MISO (4U)
/** Input Pin: SPI_MOSI */
#define ISO808A_1_SPI_MOSI (5U)

/** Control Pin: SPI_SS */
#define ISO808A_1_SPI_SS (2U)
/** Control Pin: OUT_EN */
#define ISO808A_1_OUT_EN (3U)


/** SPI_SS Port 1 */
#define ISO808A_1_SPI_SS_GPIO_PORT SPI_SS_Alt1_GPIO_Port
/** SPI_SS Pin 1 */
#define ISO808A_1_SPI_SS_GPIO_PIN SPI_SS_Alt1_Pin
/** OUT_EN Port 1 */
#define ISO808A_1_OUT_EN_GPIO_PORT OUT_EN_Alt1_GPIO_Port
/** OUT_EN Pin 1 */
#define ISO808A_1_OUT_EN_GPIO_PIN OUT_EN_Alt1_Pin

/** STATUS Port 1 */
#define ISO808A_1_STATUS_GPIO_PORT STATUS_Alt1_GPIO_Port
/** STATUS Pin 1 */
#define ISO808A_1_STATUS_GPIO_PIN STATUS_Alt1_Pin
/** PGOOD Port 1 */
#define ISO808A_1_PGOOD_GPIO_PORT PGOOD_Alt1_GPIO_Port
/** PGOOD Pin 1 */
#define ISO808A_1_PGOOD_GPIO_PIN PGOOD_Alt1_Pin

/* Return codes */
/** ISO808A Ok codes  */
#define IPS_RELAY_OK (0)

/** ISO808A Error code  */
#define IPS_RELAY_ERROR (-1)

typedef enum {
  /** ISO808A undefined Mode */
  ISO808A_NONE=0,
  /** ISO808A Parallel Independent Mode */
  ISO808A_PIM,
  /** ISO808A Daisy Chain Mode */
  ISO808A_DCM,
} IPS_OpMode_t;

/** Daisy chain: fully populated system */
#define ISO808A_DCM_FULLSYS (0x3U)

/**
  * @}
  */

/* Exported Types  -------------------------------------------------------*/

/** @defgroup ISO808A_Exported_Types ISO808A Exported Types
  * @{
  */

/** Initialisation function type */
typedef int32_t (*ISO808A_Init_Func_t)(void);
/** DeInitialisation function type */
typedef int32_t (*ISO808A_DeInit_Func_t)(void);
/** GetTick function type */
typedef int32_t (*ISO808A_GetTick_Func_t)(void);
/** Read fault function type */
typedef int32_t (*ISO808A_Read_Fault_Func_t)(IPS_RELAY_Pins_t *, uint8_t *);
/** Set SPI Freq function type*/
typedef uint8_t (*ISO808A_SetSpiFreq_Func_t)(uint32_t);
/** SPI Write input register function type */
typedef uint8_t (*ISO808A_SpiWrite_Func_t)(uint8_t, uint8_t *, uint8_t *, uint8_t);

/** Write Pin function type */
typedef int32_t (*ISO808A_Write_Pin_Func_t)(IPS_RELAY_Pins_t *, uint8_t , uint8_t);
/** Read Pin function type */
typedef int32_t (*ISO808A_Read_Pin_Func_t)(IPS_RELAY_Pins_t *, uint8_t , uint8_t *);
/** Set PWM function type */
typedef int32_t (*ISO808A_Set_Pwm_Func_t)(uint8_t);
/** Start Guard Timer */
typedef int32_t (*ISO808A_Start_GuardTimer_Func_t)(void);
/** Stop Guard Timer */
typedef int32_t (*ISO808A_Stop_GuardTimer_Func_t)(void);
/** Enable IRQ function */
typedef void (*ISO808A_EnableIrq_Func_t)(void);
/** Disable IRQ function */
typedef void (*ISO808A_DisableIrq_Func_t)(void);

/** ISO808A IO structure  */
typedef struct
{
  /** Initialisation function */
  ISO808A_Init_Func_t             Init;
  /** DeInitialisation function */
  ISO808A_DeInit_Func_t           DeInit;
  /** Get Tick function */
  ISO808A_GetTick_Func_t          GetTick;
  /** Read fault function */
  ISO808A_Read_Fault_Func_t       ReadFault;
  /** SPI Write Input register function */
  ISO808A_SpiWrite_Func_t         SpiWrite;
  /** Write Pin status function */
  ISO808A_Write_Pin_Func_t        WritePin;
  /** Read Pin status function */
  ISO808A_Read_Pin_Func_t         ReadPin;
  /** Set PWM */
  ISO808A_Set_Pwm_Func_t          SetPwm;
  /** Start Guard Timer */
  ISO808A_Start_GuardTimer_Func_t StartGuardTimer;
  /** Stop Guard Timer */
  ISO808A_Stop_GuardTimer_Func_t  StopGuardTimer;
  /** Enable IRQ function */
  ISO808A_EnableIrq_Func_t        EnableIrq;
  /** Disable IRQ function */
  ISO808A_DisableIrq_Func_t       DisableIrq;
} ISO808A_IO_t;

/** ISO808A component object structure  */
typedef struct
{
  /** IOs substructure */
  ISO808A_IO_t IO;
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
  uint8_t channelDc[ISO808A_MAX_NB_CHANNELS];
  /** Is PWM mode enabled? */
  uint8_t isPwmEnabled;
  /** channel enable bitmap for PWM management */
  uint8_t chanEnBitmap;
  /** next channel enable bitmap for PWM management */
  uint8_t nextChanEnBitmap;
  /** force resynchronisation of the PWM */
  uint8_t forcePwmResync[ISO808A_MAX_NB_CHANNELS];
  /** Channel frequency */
  uint16_t channelFreq[ISO808A_MAX_NB_CHANNELS];
  /** ID of the chip */
  uint16_t chipId;
  /** Action Table for each channel: tick of the next level change*/
  uint32_t chanPwmTimActionTable[ISO808A_MAX_NB_CHANNELS];
  /** period of low state for each channel */
  uint32_t chanPwmTimPeriodLow[ISO808A_MAX_NB_CHANNELS];
  /** period of hihg state for each channel */
  uint32_t chanPwmTimPeriodHigh[ISO808A_MAX_NB_CHANNELS];
  /** PWM frequency */
  uint32_t pwmFreq;
  /** PWM tick */
  uint32_t pwmTimTickCnt[ISO808A_MAX_NB_CHANNELS];
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
  /** Operating Mode flag (Parallel Independent or Daisy Chain) */
  uint8_t OpMode;
} ISO808A_Object_t;

/** ISO808A component capabilities  */
typedef struct
{
  /** Number of channels */
  uint8_t nbChannels;
  /** First control pin */
  uint8_t firstCtrlPin;
  /** Number of control pins */
  uint8_t nbCtrlPins;
} ISO808A_Capabilities_t;


/** ISO808A common driver functions */
typedef struct
{
  /** pointer to Init function */
  int32_t (*Init)(ISO808A_Object_t *);
  /** pointer to DeInit function */
  int32_t (*DeInit)(ISO808A_Object_t *);
  /** pointer to ReadId function */
  int32_t (*ReadID)(ISO808A_Object_t *, uint32_t *);
  /** pointer to GetCapabilities function */
  int32_t (*GetCapabilities)(ISO808A_Object_t *, ISO808A_Capabilities_t *);
  /** pointer to GetFaultStatus function */
  int32_t (*GetFaultStatus)(ISO808A_Object_t *, uint8_t *);
  /** pointer to GetFaultRegister function */
  int32_t (*GetFaultRegister)(ISO808A_Object_t *, uint8_t *);
  /** pointer to GetChannelStatus function */
  int32_t (*GetChannelStatus)(ISO808A_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetChannelStatus function */
  int32_t (*SetChannelStatus)(ISO808A_Object_t *, uint8_t, uint8_t);
  /** pointer to GetCtrlPinStatus function */
  int32_t (*GetCtrlPinStatus)(ISO808A_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetCtrlPinStatus function */
  int32_t (*SetCtrlPinStatus)(ISO808A_Object_t *, uint8_t, uint8_t);
  /** pointer to GetAllChannelStatus function */
  int32_t (*GetAllChannelStatus)(ISO808A_Object_t *, uint8_t *);
  /** pointer to SetAllChannelStatus function */
  int32_t (*SetAllChannelStatus)(ISO808A_Object_t *, uint8_t);
  /** pointer to GetChannelFreq function */
  int32_t (*GetChannelFreq)(ISO808A_Object_t *, uint8_t, uint16_t *);
  /** pointer to SetChannelFreq function */
  int32_t (*SetChannelFreq)(ISO808A_Object_t *, uint8_t, uint16_t);
  /** pointer to GetChannelDc function */
  int32_t (*GetChannelDc)(ISO808A_Object_t *, uint8_t, uint8_t *);
  /** pointer to GetChannelDc function */
  int32_t (*SetChannelDc)(ISO808A_Object_t *, uint8_t, uint8_t);
  /** pointer to GetPwmEnable function */
  int32_t (*GetPwmEnable)(ISO808A_Object_t *, uint8_t, uint8_t *);
  /** pointer to SetPwmEnable function */
  int32_t (*SetPwmEnable)(ISO808A_Object_t *, uint8_t, uint8_t);
  /** pointer to PwmTick function */
  int32_t (*PwmTick)(ISO808A_Object_t *);
  /** pointer to GuardTimerTick function */
  int32_t (*GuardTimerTick)(ISO808A_Object_t *);
  /** pointer to QueueChannelStatus function */
  int32_t (*QueueChannelStatus)(ISO808A_Object_t *, uint8_t , uint8_t);
  /** pointer to QueueAllChannelStatus function */
  int32_t (*QueueAllChannelStatus)(ISO808A_Object_t *, uint8_t);
  /** pointer to SendQueuedChannelStatus function */
  int32_t (*SendQueuedChannelStatus)(void);
  /** pointer to GetFaultRegister function */
  int32_t (*GetFaultRegister_DaisyChain)(uint16_t *);
  /** pointer to PwmTick function */
  int32_t (*PwmTick_DaisyChain)(void);
  /** pointer to GuardTimerTick function */
  int32_t (*GuardTimerTick_DaisyChain)(void);
} ISO808A_CommonDrv_t;

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/** @defgroup ISO808A_Exported_Variables ISO808A Exported Variables
  * @{
  */

extern ISO808A_CommonDrv_t ISO808A_COMMON_Driver;
extern uint8_t RELAY_System_PWMEnable_bitmap;
extern uint8_t RELAY_System_State_bitmap;
extern uint8_t RELAY_System_OpMode;
extern uint8_t IPS_NbInstances;
extern uint8_t IPS_NbDevices;
extern uint8_t spiPreemptionByIsr;
extern uint8_t isrFlag;
extern int16_t spiLockTime;

/**
  * @}
  */

/* Exported macros --------------------------------------------------------*/

/** @defgroup ISO808A_Exported_Macros ISO808A Exported Macros
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

/** @defgroup ISO808A_Exported_Functions ISO808A Exported Functions
  * @{
  */

int32_t ISO808A_GetChannelFreq(ISO808A_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq);
int32_t ISO808A_GetChannelDc(ISO808A_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc);
int32_t ISO808A_GetPwmEnable(ISO808A_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled);
int32_t ISO808A_SetChannelDc(ISO808A_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc);
int32_t ISO808A_SetChannelFreq(ISO808A_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq);
int32_t ISO808A_SetPwmEnable(ISO808A_Object_t *pObj, uint8_t ChanId, uint8_t PwmEnabled);
int32_t ISO808A_PwmTick(ISO808A_Object_t *pObj);
int32_t ISO808A_GuardTimerTick(ISO808A_Object_t *pObj);
int32_t ISO808A_PwmTick_DaisyChain(void);
int32_t ISO808A_GuardTimerTick_DaisyChain(void);
int32_t ISO808A_GetChannelStatus(ISO808A_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus);
int32_t ISO808A_GetAllChannelStatus(ISO808A_Object_t *pObj, uint8_t *pChanStatusBitmap);
int32_t ISO808A_GetCapabilities(ISO808A_Object_t *pObj, ISO808A_Capabilities_t *pCapabilities);
int32_t ISO808A_GetFaultStatus(ISO808A_Object_t *pObj, uint8_t *pFaultStatus);
int32_t ISO808A_GetFaultRegister(ISO808A_Object_t *pObj, uint8_t *pFaultRegister);
int32_t ISO808A_DeInit(ISO808A_Object_t *pObj);
int32_t ISO808A_Init(ISO808A_Object_t *pObj);
int32_t ISO808A_ReadID(ISO808A_Object_t *pObj, uint32_t *pId);
int32_t ISO808A_RegisterBusIO(ISO808A_Object_t *pObj, ISO808A_IO_t *pIO);
int32_t ISO808A_SetAllChannelStatus(ISO808A_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t ISO808A_SetChannelStatus(ISO808A_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t ISO808A_GetCtrlPinStatus(ISO808A_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus);
int32_t ISO808A_SetCtrlPinStatus(ISO808A_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus);
int32_t ISO808A_QueueChannelStatus(ISO808A_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus);
int32_t ISO808A_QueueAllChannelStatus(ISO808A_Object_t *pObj, uint8_t newChanBitmap);
int32_t ISO808A_SendQueuedChannelStatus(void);
int32_t ISO808A_GetFaultRegister_DaisyChain(uint16_t *pFaultRegister);

int32_t ISO808A_SetAllChannelPwmStatus(ISO808A_Object_t *pObj, uint8_t ChanStatusBitmap);
int32_t ISO808A_QueueAllChannelPwmStatus(ISO808A_Object_t *pObj, uint8_t newChanBitmap);
int32_t ISO808A_SendQueuedPwmChannelStatus(void);

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

#endif /* #ifndef ISO808A_H */
