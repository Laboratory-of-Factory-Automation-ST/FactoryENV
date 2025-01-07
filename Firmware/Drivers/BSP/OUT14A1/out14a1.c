/**
  ******************************************************************************
  * @file    out14a1.c
  * @author  AMS IPC Application Team
  * @brief   This file provides BSP driver functions for Galvanic Isolated Octal
  *          High-Side Power Solid State Relay with SPI interface for high
  *          inductive loads available on the following expansion board
  *           - X-NUCLEO-OUT14A1
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

/* Includes ------------------------------------------------------------------*/
#include "out14a1.h"
#include "out14_error_code.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT14A1 OUT14A1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT14A1_Global_Variables OUT14A1 Global Variables
  * @{
  */

/** Relay component object */
void *RELAY_CompObj[OUT14_RELAY_INSTANCES_NBR];

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/

/** @defgroup OUT14A1_Private_Typedef OUT14A1 Private Typedef
  * @{
  */

typedef struct {
  EXTI_HandleTypeDef *p_status;
  EXTI_HandleTypeDef *p_pgood;
} EXTI_board_t;

/**
  * @}
  */

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @defgroup OUT14A1_Private_Macros  OUT14A1 Private Macros
  * @{
  */

#ifdef USE_BOARD_0
EXTI_HandleTypeDef H_EXTI_STATUS = {.Line = H_EXTI_LINE_STATUS};
EXTI_HandleTypeDef H_EXTI_PGOOD = {.Line = H_EXTI_LINE_PGOOD};
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
EXTI_HandleTypeDef H_EXTI_STATUS_Alt1 = {.Line = H_EXTI_LINE_STATUS_Alt1};
EXTI_HandleTypeDef H_EXTI_PGOOD_Alt1 = {.Line = H_EXTI_LINE_PGOOD_Alt1};
#endif /* #ifdef USE_BOARD_1 */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup OUT14A1_Private_Variables  OUT14A1 Private Variables
  * @{
  */

static RELAY_CommonDrv_t *RELAY_Drv[OUT14_RELAY_INSTANCES_NBR];
extern EXTI_board_t exti_board[OUT14_RELAY_INSTANCES_NBR];
EXTI_board_t exti_board[OUT14_RELAY_INSTANCES_NBR] = {
	    {
#ifdef USE_BOARD_0
	      .p_status = &H_EXTI_STATUS,
	      .p_pgood = &H_EXTI_PGOOD
#else
		  .p_status = NULL,
		  .p_pgood = NULL
#endif /* #ifdef USE_BOARD_0 */
	    }

    ,{
#ifdef USE_BOARD_1
      .p_status = &H_EXTI_STATUS_Alt1,
      .p_pgood = &H_EXTI_PGOOD_Alt1
#else
		  .p_status = NULL,
		  .p_pgood = NULL
#endif /* #ifdef USE_BOARD_1 */
    }
};

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup OUT14A1_Private_Function_Prototypes OUT14A1 Private Function Prototypes
  * @{
  */

static int32_t ISO808A_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, uint8_t opMode, OUT14_RELAY_Init_Parameters_t *pInitParam);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT14A1_Functions_Definition OUT14A1 Functions Definition
  * @{
  */

/**
  * @brief  Provide Register callback parameters for the specific board used.
  * @param  Instance  Specific board used identifier.
  *         This parameter can be one of the following values:
  *           @arg OUT14_BOARD_0: Board 0 selected
  *           @arg OUT14_BOARD_1: Board 1 selected
  * @param  status_isr  First function pointer to provide to the register callback.
  * @param  pgood_isr  Second function pointer to provide to the register callback.
  * @retval 0 value if success else fail.
  */
int32_t OUT14_RELAY_RegisterCallBack(uint8_t Instance, void (*status_isr)(void), void (*pgood_isr)(void))
{
	if (Instance < OUT14_RELAY_INSTANCES_NBR)
  {
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_status, HAL_EXTI_COMMON_CB_ID, status_isr);
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_pgood, HAL_EXTI_COMMON_CB_ID, pgood_isr);
		return 0;
  }
  else
  {
    return 1;
  }
}

/**
  * @brief  Initializes the power relay
  * @param  Instance relay instance to be used
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  opMode Operating Mode (PIND or DC)
  * @param  pInitParam pointer to the init parameters structure
  * @retval BSP status
  */
int32_t OUT14_RELAY_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, uint8_t opMode, OUT14_RELAY_Init_Parameters_t *pInitParam)
{
  int32_t ret = OUT14_ERROR_NONE;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else if ((NbDevices == 0U) || (NbDevices > OUT14_RELAY_DEVICES_NBR))
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else if ((opMode != (uint8_t)OUT14_RELAY_PAR_IND_MODE) && (opMode != (uint8_t)OUT14_RELAY_DAISY_CHAIN_MODE))
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    switch (ChipId)
    {
      case OUT14_RELAY_CHIP_ID:
        if (ISO808A_1_Register_Instance(Instance, ChipId, NbDevices, opMode, pInitParam) != OUT14_ERROR_NONE)
        {
          ret =  OUT14_ERROR_NO_INIT;
        }
        break;

      default:
        ret = OUT14_ERROR_WRONG_PARAM;
        break;
    }
  }

  return ret;
}

/**
  * @brief  Deinitialize the power relay
  * @param  Instance relay instance to be used
  * @retval BSP status
  */
int32_t OUT14_RELAY_DeInit(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else if (RELAY_Drv[Instance]->DeInit(RELAY_CompObj[Instance]) != OUT14_ERROR_NONE)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    RELAY_System_State_bitmap &= ~(0x1U << Instance);
    if (RELAY_System_State_bitmap == 0U)
    {
      RELAY_System_OpMode = (uint8_t)OUT14_RELAY_UNDEF_MODE;
    }
    ret = OUT14_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get power relay instance capabilities
  * @param  Instance Power relay instance
  * @param  pCapabilities pointer to capabilities
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetCapabilities(uint8_t Instance, OUT14_RELAY_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else if (RELAY_Drv[Instance]->GetCapabilities(RELAY_CompObj[Instance], pCapabilities) != OUT14_ERROR_NONE)
  {
    ret = OUT14_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT14_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get Chip Id value
  * @param  Instance Power relay instance
  * @param  pId pointer to the chip Id
  * @retval BSP status
  */
int32_t OUT14_RELAY_ReadID(uint8_t Instance, uint16_t *pId)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else if (RELAY_Drv[Instance]->ReadID(RELAY_CompObj[Instance], pId) != OUT14_ERROR_NONE)
  {
    ret = OUT14_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT14_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get the duty cycle of the given Power Relay Channel
  * @param  Instance Power relay instance
  * @param  ChanId Channel Id
  * @param  pChanDc pointer to the channel duty cycle
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetChannelDc(RELAY_CompObj[Instance], ChanId, pChanDc) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get frequency of the given Power Relay Channel
  * @param  Instance Power relay instance
  * @param  ChanId Channel Id
  * @param  pChanFreq pointer to the channel frequency
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetChannelFreq(RELAY_CompObj[Instance], ChanId, pChanFreq) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get status of the given Power Relay Channel
  * @param  Instance Power relay instance
  * @param  ChanId Channel Id
  * @param  pChanStatus pointer to the channel status
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetChannelStatus(RELAY_CompObj[Instance], ChanId, pChanStatus) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get status of all Power Relay Channels
  * @param  Instance Power relay instance
  * @param  pChanStatusBitmap pointer to the channel status bitmap
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetAllChannelStatus(RELAY_CompObj[Instance], pChanStatusBitmap) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get status of the given Power Relay Control Pin
  * @param  Instance Power relay instance
  * @param  CtrlPinId Control Pin Id
  * @param  pPinStatus pointer to the pin status
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pPinStatus)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetCtrlPinStatus(RELAY_CompObj[Instance], CtrlPinId, pPinStatus) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get Fault status
  * @param  Instance Power relay instance
  * @param  pFaultStatus pointer to the channel status
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetFaultStatus(RELAY_CompObj[Instance], pFaultStatus) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get Fault Register
  * @param  Instance Power relay instance
  * @param  pFaultRegister pointer to the device fault register
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetFaultRegister(uint8_t Instance, uint8_t *pFaultRegister)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetFaultRegister(RELAY_CompObj[Instance], pFaultRegister) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set status of the given Power Relay Channel
  * @param  Instance Power relay instance
  * @param  ChanId Channel Id
  * @param  ChanStatus Channel Status
  * @retval BSP status
  */
int32_t OUT14_RELAY_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetChannelStatus(RELAY_CompObj[Instance], ChanId, ChanStatus) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set status of all Power Relay Channels
  * @param  Instance Power relay instance
  * @param  ChanStatusBitmap Channel Status Bitmap
  * @retval BSP status
  */
int32_t OUT14_RELAY_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
   int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetAllChannelStatus(RELAY_CompObj[Instance], ChanStatusBitmap) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set status of a control pin
  * @param  Instance Power relay instance
  * @param  CtrlPinId Control Pin Id
  * @param  CtrlPinStatus Control Pin Status
  * @retval BSP status
  */
int32_t OUT14_RELAY_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
{
   int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if ((RELAY_System_OpMode == (uint8_t)OUT14_RELAY_DAISY_CHAIN_MODE) && (Instance == 1U))
    {
      if (RELAY_Drv[0]->SetCtrlPinStatus(RELAY_CompObj[0], (CtrlPinId - 2U), CtrlPinStatus) != OUT14_ERROR_NONE)
      {
        ret = OUT14_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = OUT14_ERROR_NONE;
      }
    }
    else
    {
      if (RELAY_Drv[Instance]->SetCtrlPinStatus(RELAY_CompObj[Instance], CtrlPinId, CtrlPinStatus) != OUT14_ERROR_NONE)
      {
        ret = OUT14_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = OUT14_ERROR_NONE;
      }
    }
  }
  return ret;
}

/**
  * @brief  Set status of the given Power Relay Channel
  * @param  Instance Power relay instance
  * @param  ChanId Channel Id
  * @param  ChanDc Channel duty cycle
  * @retval BSP status
  */
int32_t OUT14_RELAY_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc)
{
   int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetChannelDc(RELAY_CompObj[Instance], ChanId, ChanDc) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set status of the given Power Relay Channel
  * @param  Instance Power relay instance
  * @param  ChanId Channel Id
  * @param  ChanFreq Channel frequency
  * @retval BSP status
  */
int32_t OUT14_RELAY_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq)
{
   int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetChannelFreq(RELAY_CompObj[Instance], ChanId, ChanFreq) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get the PWM enable  state
  * @param  Instance Power relay instance
  * @param  ChanId Channel Id
  * @param  pPwmEnable pointer to the PWM enable
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetPwmEnable(RELAY_CompObj[Instance], ChanId, pPwmEnable) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Enable or disable PWM mode
  * @param  Instance Power relay instance
  * @param  ChanId Channel Id
  * @param  pwmEnable enable or disable
  * @retval BSP status
  */
int32_t OUT14_RELAY_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable)
{
   int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetPwmEnable(RELAY_CompObj[Instance], ChanId, pwmEnable) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick for parallel independent conf
  * @param  Instance Power relay instance
  * @retval BSP status
  */
int32_t OUT14_RELAY_PwmTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->PwmTick(RELAY_CompObj[Instance]) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Guard Timer Tick for parallel independent conf
  * @param  Instance Power relay instance
  * @retval BSP status
  */
int32_t OUT14_RELAY_GuardTimerTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GuardTimerTick(RELAY_CompObj[Instance]) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick for Daisy Chain conf
  * @retval BSP status
  */
int32_t OUT14_RELAY_PwmTick_DaisyChain(void)
{
  int32_t ret;

  if (ISO808A_1_PwmTick_DaisyChain() != OUT14_ERROR_NONE)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT14_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Guard Timer Tick for Daisy Chain conf
  * @retval BSP status
  */
int32_t OUT14_RELAY_GuardTimerTick_DaisyChain(void)
{
  int32_t ret;

  if (ISO808A_1_GuardTimerTick_DaisyChain() != OUT14_ERROR_NONE)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT14_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Add status of the given Power Relay Channel and device to the SPI write queue
  * @param  Instance Power relay instance
  * @param  ChanId Channel Id
  * @param  ChanStatus Channel Status
  * @retval BSP status
  */
int32_t OUT14_RELAY_QueueChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else if (RELAY_System_OpMode != (uint8_t)OUT14_RELAY_DAISY_CHAIN_MODE)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else if (RELAY_System_State_bitmap != (uint8_t)OUT14_RELAY_DAISY_CHAIN_FULLSYS)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    if (RELAY_Drv[Instance]->QueueChannelStatus(RELAY_CompObj[Instance], ChanId, ChanStatus) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Add status of all Power Relay Channels of the given device to the SPI write queue
  * @param  Instance Power relay instance
  * @param  ChanStatusBitmap Channel Status Bitmap
  * @retval BSP status
  */
int32_t OUT14_RELAY_QueueAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else if (RELAY_System_OpMode != (uint8_t)OUT14_RELAY_DAISY_CHAIN_MODE)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else if (RELAY_System_State_bitmap != (uint8_t)OUT14_RELAY_DAISY_CHAIN_FULLSYS)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    if (RELAY_Drv[Instance]->QueueAllChannelStatus(RELAY_CompObj[Instance], ChanStatusBitmap) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Send the SPI write queue to the daisy chain
  * @param  Instance Power relay instance
  * @retval BSP status
  */
int32_t OUT14_RELAY_SendQueuedChannelStatus(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else if (RELAY_System_OpMode != (uint8_t)OUT14_RELAY_DAISY_CHAIN_MODE)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else if (RELAY_System_State_bitmap != (uint8_t)OUT14_RELAY_DAISY_CHAIN_FULLSYS)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else
  {
     if (RELAY_Drv[Instance]->SendQueuedChannelStatus() != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }

  return ret;
}

/**
  * @brief  Get Fault Register in Daisy Chain mode
  * @param  Instance Power relay instance
  * @param  pFaultRegister pointer to the device fault register
  * @retval BSP status
  */
int32_t OUT14_RELAY_GetFaultRegister_DaisyChain(uint8_t Instance, uint16_t *pFaultRegister)
{
  int32_t ret;

  if (Instance >= OUT14_RELAY_INSTANCES_NBR)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else if (RELAY_System_OpMode != (uint8_t)OUT14_RELAY_DAISY_CHAIN_MODE)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else if (RELAY_System_State_bitmap != (uint8_t)OUT14_RELAY_DAISY_CHAIN_FULLSYS)
  {
    ret = OUT14_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetFaultRegister_DaisyChain(pFaultRegister) != OUT14_ERROR_NONE)
    {
      ret = OUT14_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT14_ERROR_NONE;
    }
  }

  return ret;
}

/******************************************************//**
 * @brief This function enable the interruptions
 * @retval None
 **********************************************************/
void OUT14_EnableIrq(void)
{
  __enable_irq();
}

/******************************************************//**
 * @brief This function disable the interruptions
 * @retval None
 **********************************************************/
void OUT14_DisableIrq(void)
{
  __disable_irq();
}

/**
  * @brief  Register Bus IOs for instance 0 if component ID is OK
  * @param  Instance Power relay instance
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  opMode Operating mode (Parallel independent, default, or Daisy chain)
  * @param  pInitParam Pointer to initial Parameters structure
  * @retval BSP status
  */
static int32_t ISO808A_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, uint8_t opMode, OUT14_RELAY_Init_Parameters_t *pInitParam)
{
  int32_t ret;
  ISO808A_1_IO_t io_ctx;
  ISO808A_1_Capabilities_t cap;
  static ISO808A_1_Object_t iso808a_1_obj[OUT14_RELAY_INSTANCES_NBR];

  /* Configure the relay driver */
  io_ctx.Init             = OUT14_SpiInit;
  io_ctx.DeInit           = OUT14_SpiDeInit;
  io_ctx.SpiWrite         = OUT14_SpiWrite;

  io_ctx.GetTick          = OUT14_GetTick;
  io_ctx.ReadFault        = OUT14_ReadFault;
  io_ctx.WritePin         = OUT14_WritePin;
  io_ctx.ReadPin          = OUT14_ReadPin;
  io_ctx.SetPwm           = OUT14_SetPwm;
  io_ctx.StartGuardTimer  = OUT14_GuardTimerEnable;
  io_ctx.StopGuardTimer   = OUT14_GuardTimerDisable;
  io_ctx.EnableIrq        = OUT14_EnableIrq;
  io_ctx.DisableIrq       = OUT14_DisableIrq;

  ret = OUT14_ERROR_NONE;
  if (pInitParam == NULL)
  {
    ret = OUT14_ERROR_WRONG_PARAM;
  }
  else
  {
    iso808a_1_obj[Instance].pwmFreq = pInitParam->pwmFreq;
    iso808a_1_obj[Instance].spiFreq = pInitParam->spiFreq;
    iso808a_1_obj[Instance].timingTcss = pInitParam->timingTcss;
    if (ISO808A_1_RegisterBusIO(&iso808a_1_obj[Instance], &io_ctx) != IPS_RELAY_OK)
    {
      ret = OUT14_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      int32_t loop;

      iso808a_1_obj[Instance].chipId = ChipId;
      iso808a_1_obj[Instance].Instance = Instance;
      iso808a_1_obj[Instance].isPresent = 1U;
      iso808a_1_obj[Instance].nbDevices = NbDevices;

      (void)ISO808A_1_GetCapabilities(&iso808a_1_obj[Instance], &cap);
      iso808a_1_obj[Instance].nbChannels = cap.nbChannels;
      iso808a_1_obj[Instance].firstCtrl = cap.firstCtrlPin;
      iso808a_1_obj[Instance].nbCtrls = cap.nbCtrlPins;

      iso808a_1_obj[Instance].isPwmEnabled = 0U;
      iso808a_1_obj[Instance].chanEnBitmap = 0U;
      iso808a_1_obj[Instance].ChanSteadyStateBitmap = 0U;
      iso808a_1_obj[Instance].ChanSteadyStatePwmBitmap = 0U;
      iso808a_1_obj[Instance].newChanSteadyStateBitmap = FALSE;
      iso808a_1_obj[Instance].nextChanEnBitmap = 0U;
      for (loop = (int32_t)iso808a_1_obj[Instance].nbChannels - 1; loop >= 0; loop--)
      {
        iso808a_1_obj[Instance].channelFreq[loop] = 0U;
        iso808a_1_obj[Instance].channelDc[loop] = 0U;
      }
      iso808a_1_obj[Instance].OpMode = opMode;
      RELAY_System_OpMode = opMode;
      RELAY_System_State_bitmap |= (0x1U << Instance);

      switch (Instance)
      {
        case 0:
#ifdef USE_BOARD_0
          iso808a_1_obj[Instance].Pin.SPI_SS_GPort = OUT14_RELAY_0_SPI_SS_GPIO_PORT;
          iso808a_1_obj[Instance].Pin.SPI_SS_GPin = OUT14_RELAY_0_SPI_SS_GPIO_PIN;
          iso808a_1_obj[Instance].Pin.OUT_EN_GPort = OUT14_RELAY_0_OUT_EN_GPIO_PORT;
          iso808a_1_obj[Instance].Pin.OUT_EN_GPin = OUT14_RELAY_0_OUT_EN_GPIO_PIN;
          iso808a_1_obj[Instance].Pin.STATUS_GPort = OUT14_RELAY_0_STATUS_GPIO_PORT;
          iso808a_1_obj[Instance].Pin.STATUS_GPin = OUT14_RELAY_0_STATUS_GPIO_PIN;
          iso808a_1_obj[Instance].Pin.PGOOD_GPort = OUT14_RELAY_0_PGOOD_GPIO_PORT;
          iso808a_1_obj[Instance].Pin.PGOOD_GPin = OUT14_RELAY_0_PGOOD_GPIO_PIN;
#endif /* #ifdef USE_BOARD_0 */
          break;

        case 1:
#ifdef USE_BOARD_1
          iso808a_1_obj[Instance].Pin.SPI_SS_GPort = OUT14_RELAY_1_SPI_SS_GPIO_PORT;
          iso808a_1_obj[Instance].Pin.SPI_SS_GPin = OUT14_RELAY_1_SPI_SS_GPIO_PIN;
          iso808a_1_obj[Instance].Pin.OUT_EN_GPort = OUT14_RELAY_1_OUT_EN_GPIO_PORT;
          iso808a_1_obj[Instance].Pin.OUT_EN_GPin = OUT14_RELAY_1_OUT_EN_GPIO_PIN;
          iso808a_1_obj[Instance].Pin.STATUS_GPort = OUT14_RELAY_1_STATUS_GPIO_PORT;
          iso808a_1_obj[Instance].Pin.STATUS_GPin = OUT14_RELAY_1_STATUS_GPIO_PIN;
          iso808a_1_obj[Instance].Pin.PGOOD_GPort = OUT14_RELAY_1_PGOOD_GPIO_PORT;
          iso808a_1_obj[Instance].Pin.PGOOD_GPin = OUT14_RELAY_1_PGOOD_GPIO_PIN;
#endif /* #ifdef USE_BOARD_1 */
          break;

        default:
          ret = OUT14_ERROR_WRONG_PARAM;
          break;
      }

      if (ret == OUT14_ERROR_NONE)
      {
        RELAY_CompObj[Instance] = &iso808a_1_obj[Instance];

        /* The second cast (void *) is added to bypass Misra R11.3 rule */
        RELAY_Drv[Instance] = (RELAY_CommonDrv_t *)(void *)&ISO808A_1_COMMON_Driver;

        if (RELAY_Drv[Instance]->Init(RELAY_CompObj[Instance]) != IPS_RELAY_OK)
        {
          ret = OUT14_ERROR_UNKNOWN_FAILURE;
        }
        else
        {
          ret = OUT14_ERROR_NONE;
        }
      }
    }
  }
  return ret;
}

__weak int32_t OUT14_SetTimerForPwm(uint8_t pwmEnable)
{
  int32_t ret = OUT14_ERROR_NONE;
  
  UNUSED(pwmEnable);

  return ret;
}

__weak int32_t OUT14_GuardTimerStart(void)
{
  int32_t ret = OUT14_ERROR_NONE;

  return ret;
}

__weak int32_t OUT14_GuardTimerStop(void)
{
  int32_t ret = OUT14_ERROR_NONE;

  return ret;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
