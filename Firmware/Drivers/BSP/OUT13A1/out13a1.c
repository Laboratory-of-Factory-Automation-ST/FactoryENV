/**
  ******************************************************************************
  * @file    out13a1.c
  * @author  AMS IPC Application Team
  * @brief   This file provides BSP driver functions for IPS device on
  *          the following expansion board
  *           - X-NUCLEO-OUT13A1
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
#include "out13a1.h"
#include "out13_error_code.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT13A1 OUT13A1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT13A1_Global_Variables OUT13A1 Global Variables
  * @{
  */

EXTI_HandleTypeDef H_EXTI_STATUS = {.Line = H_EXTI_LINE_STATUS};

/** Switch component object */
void *SWITCH_CompObj[OUT13_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup OUT13A1_Private_Variables OUT13A1 Private Variables
  * @{
  */

static SWITCH_CommonDrv_t *SWITCH_Drv[OUT13_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup OUT13A1_Private_Function_Prototypes OUT13A1 Private Function Prototypes
  * @{
  */

static int32_t ISO808_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT13_SWITCH_Init_Parameters_t *pInitParam);
static int32_t OUT13_Init(void);
static int32_t OUT13_DeInit(void);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT13A1_Functions_Definition OUT13A1 Functions Definition
  * @{
  */

/**
  * @brief  Return system tick in ms
  * @retval Current HAL time base time stamp
  */
int32_t BSP_GetTick(void) {
  return (int32_t)HAL_GetTick();
}

/**
  * @brief  Initializes the power switch
  * @param  Instance switch instance to be used
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam pointer to the init parameters structure
  * @retval BSP status
  */
int32_t OUT13_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT13_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret = OUT13_ERROR_NONE;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else if ((NbDevices == 0U) || (NbDevices > OUT13_SWITCH_DEVICES_NBR))
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    switch (ChipId)
    {
      case OUT13_SWITCH_CHIP_ID:
        if (ISO808_1_Register_Instance(Instance, ChipId, NbDevices, pInitParam) != OUT13_ERROR_NONE)
        {
          ret =  OUT13_ERROR_NO_INIT;
        }
        break;

      default:
        ret = OUT13_ERROR_WRONG_PARAM;
        break;
    }
  }

  return ret;
}

/**
  * @brief  Deinitialize the power switch
  * @param  Instance switch instance to be used
  * @retval BSP status
  */
int32_t OUT13_SWITCH_DeInit(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->DeInit(SWITCH_CompObj[Instance]) != OUT13_ERROR_NONE)
  {
    ret = OUT13_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT13_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get power switch instance capabilities
  * @param  Instance Power switch instance
  * @param  pCapabilities pointer to capabilities
  * @retval BSP status
  */
int32_t OUT13_SWITCH_GetCapabilities(uint8_t Instance, OUT13_SWITCH_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->GetCapabilities(SWITCH_CompObj[Instance], pCapabilities) != OUT13_ERROR_NONE)
  {
    ret = OUT13_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT13_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get Chip Id value
  * @param  Instance Power switch instance
  * @param  pId pointer to the chip Id
  * @retval BSP status
  */
int32_t OUT13_SWITCH_ReadID(uint8_t Instance, uint16_t *pId)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->ReadID(SWITCH_CompObj[Instance], pId) != OUT13_ERROR_NONE)
  {
    ret = OUT13_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT13_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get the duty cycle of the given Power Switch Channel
  * @param  Instance Power switch instance
  * @param  ChanId Channel Id
  * @param  pChanDc pointer to the channel duty cycle
  * @retval BSP status
  */
int32_t OUT13_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelDc(SWITCH_CompObj[Instance], ChanId, pChanDc) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get frequency of the given Power Switch Channel
  * @param  Instance Power switch instance
  * @param  ChanId Channel Id
  * @param  pChanFreq pointer to the channel frequency
  * @retval BSP status
  */
int32_t OUT13_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelFreq(SWITCH_CompObj[Instance], ChanId, pChanFreq) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get status of the given Power Switch Channel
  * @param  Instance Power switch instance
  * @param  ChanId Channel Id
  * @param  pChanStatus pointer to the channel status
  * @retval BSP status
  */
int32_t OUT13_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelStatus(SWITCH_CompObj[Instance], ChanId, pChanStatus) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get status of a control pin
  * @param  Instance Power switch instance
  * @param  CtrlPinId Control Pin Id
  * @param  pCtrlPinStatus Pointer to the Control Pin Status
  * @retval BSP status
  */
int32_t OUT13_SWITCH_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetCtrlPinStatus(SWITCH_CompObj[Instance], CtrlPinId, pCtrlPinStatus) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get Fault status
  * @param  Instance Power switch instance
  * @param  pFaultStatus pointer to the channel status
  * @retval BSP status
  */
int32_t OUT13_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetFaultStatus(SWITCH_CompObj[Instance], pFaultStatus) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get the PWM enable  state
  * @param  Instance Power switch instance
  * @param  ChanId Channel Id
  * @param  pPwmEnable pointer to the PWM enable
  * @retval BSP status
  */
int32_t OUT13_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetPwmEnable(SWITCH_CompObj[Instance], ChanId, pPwmEnable) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick
  * @param  Instance Power switch instance
  * @retval BSP status
  */
int32_t OUT13_SWITCH_PwmTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->PwmTick(SWITCH_CompObj[Instance]) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set status of the given Power Switch Channel
  * @param  Instance Power switch instance
  * @param  ChanId Channel Id
  * @param  ChanDc Channel duty cycle
  * @retval BSP status
  */
int32_t OUT13_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc)
{
   int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelDc(SWITCH_CompObj[Instance], ChanId, ChanDc) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set status of the given Power Switch Channel
  * @param  Instance Power switch instance
  * @param  ChanId Channel Id
  * @param  ChanFreq Channel frequency
  * @retval BSP status
  */
int32_t OUT13_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq)
{
   int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelFreq(SWITCH_CompObj[Instance], ChanId, ChanFreq) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set status of the given Power Switch Channel
  * @param  Instance Power switch instance
  * @param  ChanId Channel Id
  * @param  ChanStatus Channel Status
  * @retval BSP status
  */
int32_t OUT13_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelStatus(SWITCH_CompObj[Instance], ChanId, ChanStatus) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get status of all Power Switch Channels
  * @param  Instance Power switch instance
  * @param  pChanStatusBitmap pointer to the channel status bitmap
  * @retval BSP status
  */
int32_t OUT13_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetAllChannelStatus(SWITCH_CompObj[Instance], pChanStatusBitmap) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set status of all Power Switch Channels
  * @param  Instance Power switch instance
  * @param  ChanStatusBitmap Channel Status Bitmap
  * @retval BSP status
  */
int32_t OUT13_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
   int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetAllChannelStatus(SWITCH_CompObj[Instance], ChanStatusBitmap) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set status of a control pin
  * @param  Instance Power switch instance
  * @param  CtrlPinId Control Pin Id
  * @param  CtrlPinStatus Control Pin Status
  * @retval BSP status
  */
int32_t OUT13_SWITCH_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetCtrlPinStatus(SWITCH_CompObj[Instance], CtrlPinId, CtrlPinStatus) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set device operating mode (DCM or SCM)
  * @param  Instance Power switch instance
  * @param  opMode Operating Mode (SCM or DCM)
  * @retval BSP status
  */
int32_t OUT13_SWITCH_SetOperatingMode(uint8_t Instance, uint8_t opMode)
{
  int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetOperatingMode(SWITCH_CompObj[Instance], opMode) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Enable or disable PWM mode
  * @param  Instance Power switch instance
  * @param  ChanId Channel Id
  * @param  pwmEnable enable or disable
  * @retval BSP status
  */
int32_t OUT13_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable)
{
   int32_t ret;

  if (Instance >= OUT13_SWITCH_INSTANCES_NBR)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetPwmEnable(SWITCH_CompObj[Instance], ChanId, pwmEnable) != OUT13_ERROR_NONE)
    {
      ret = OUT13_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT13_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @}
  */

/** @defgroup OUT13A1_Private_Functions OUT13A1 Private Functions
  * @{
  */

static int32_t OUT13_Init(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT13_ERROR_NONE;
}

static int32_t OUT13_DeInit(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT13_ERROR_NONE;
}

/**
  * @brief  Register Bus IOs for instance 0 if component ID is OK
  * @param  Instance Power switch instance
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam Pointer to initial Parameters structure
  * @retval BSP status
  */
static int32_t ISO808_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT13_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret;
  ISO808_1_IO_t io_ctx;
  ISO808_1_Capabilities_t cap;
  static ISO808_1_Object_t iso808_1_obj[OUT13_SWITCH_INSTANCES_NBR];

  /* Configure the switch driver */
  io_ctx.Init         = OUT13_Init;
  io_ctx.DeInit       = OUT13_DeInit;
  io_ctx.GetTick      = OUT13_GetTick;
  io_ctx.ReadFault    = OUT13_ReadFault;
  io_ctx.WritePin     = OUT13_WritePin;
  io_ctx.ReadPin      = OUT13_ReadPin;
  io_ctx.WriteChan    = OUT13_WriteChan;
  io_ctx.ReadChan     = OUT13_ReadChan;
  io_ctx.WriteAllChan = OUT13_WriteAllChan;
  io_ctx.ReadAllChan  = OUT13_ReadAllChan;
  io_ctx.SetPwm       = OUT13_SetPwm;

  ret = OUT13_ERROR_NONE;
  if (pInitParam == NULL)
  {
    ret = OUT13_ERROR_WRONG_PARAM;
  }
  else
  {
    iso808_1_obj[Instance].pwmFreq = pInitParam->pwmFreq;
    if (ISO808_1_RegisterBusIO(&iso808_1_obj[Instance], &io_ctx) != IPS_SWITCH_OK)
    {
      ret = OUT13_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      int32_t loop;
      iso808_1_obj[Instance].chipId = ChipId;
      iso808_1_obj[Instance].Instance = Instance;
      iso808_1_obj[Instance].isPresent = 1;
      iso808_1_obj[Instance].nbDevices = NbDevices;

      (void)ISO808_1_GetCapabilities(&iso808_1_obj[Instance], &cap);
      iso808_1_obj[Instance].nbChannels = cap.nbChannels;
      iso808_1_obj[Instance].firstCtrl = cap.firstCtrlPin;
      iso808_1_obj[Instance].nbCtrls = cap.nbCtrlPins;

      iso808_1_obj[Instance].isPwmEnabled = 0;
      iso808_1_obj[Instance].chanEnBitmap = 0;
      iso808_1_obj[Instance].ChanSteadyStateBitmap = 0;
      iso808_1_obj[Instance].nextChanEnBitmap = 0;
      iso808_1_obj[Instance].ControlPinsBitmap = 0;
      for (loop = (int32_t)iso808_1_obj[Instance].nbChannels - 1; loop >= 0; loop--)
      {
        iso808_1_obj[Instance].channelFreq[loop] = 0;
        iso808_1_obj[Instance].channelDc[loop] = 0;
      }
      iso808_1_obj[Instance].ctrlMode = (uint8_t)ISO808_1_SCM;

      switch (Instance)
      {
        case 0:
          iso808_1_obj[Instance].Pin.IN1_GPort = OUT13_SWITCH_0_IN1_GPIO_PORT;
          iso808_1_obj[Instance].Pin.IN1_GPin = OUT13_SWITCH_0_IN1_GPIO_PIN;
          iso808_1_obj[Instance].Pin.IN2_GPort = OUT13_SWITCH_0_IN2_GPIO_PORT;
          iso808_1_obj[Instance].Pin.IN2_GPin = OUT13_SWITCH_0_IN2_GPIO_PIN;
          iso808_1_obj[Instance].Pin.IN3_GPort = OUT13_SWITCH_0_IN3_GPIO_PORT;
          iso808_1_obj[Instance].Pin.IN3_GPin = OUT13_SWITCH_0_IN3_GPIO_PIN;
          iso808_1_obj[Instance].Pin.IN4_GPort = OUT13_SWITCH_0_IN4_GPIO_PORT;
          iso808_1_obj[Instance].Pin.IN4_GPin = OUT13_SWITCH_0_IN4_GPIO_PIN;
          iso808_1_obj[Instance].Pin.IN5_GPort = OUT13_SWITCH_0_IN5_GPIO_PORT;
          iso808_1_obj[Instance].Pin.IN5_GPin = OUT13_SWITCH_0_IN5_GPIO_PIN;
          iso808_1_obj[Instance].Pin.IN6_GPort = OUT13_SWITCH_0_IN6_GPIO_PORT;
          iso808_1_obj[Instance].Pin.IN6_GPin = OUT13_SWITCH_0_IN6_GPIO_PIN;
          iso808_1_obj[Instance].Pin.IN7_GPort = OUT13_SWITCH_0_IN7_GPIO_PORT;
          iso808_1_obj[Instance].Pin.IN7_GPin = OUT13_SWITCH_0_IN7_GPIO_PIN;
          iso808_1_obj[Instance].Pin.IN8_GPort = OUT13_SWITCH_0_IN8_GPIO_PORT;
          iso808_1_obj[Instance].Pin.IN8_GPin = OUT13_SWITCH_0_IN8_GPIO_PIN;
          iso808_1_obj[Instance].Pin.LOAD_GPort = OUT13_SWITCH_0_LOAD_GPIO_PORT;
          iso808_1_obj[Instance].Pin.LOAD_GPin = OUT13_SWITCH_0_LOAD_GPIO_PIN;
          iso808_1_obj[Instance].Pin.OUT_EN_GPort = OUT13_SWITCH_0_OUT_EN_GPIO_PORT;
          iso808_1_obj[Instance].Pin.OUT_EN_GPin = OUT13_SWITCH_0_OUT_EN_GPIO_PIN;
          iso808_1_obj[Instance].Pin.SYNCH_GPort = OUT13_SWITCH_0_SYNCH_GPIO_PORT;
          iso808_1_obj[Instance].Pin.SYNCH_GPin = OUT13_SWITCH_0_SYNCH_GPIO_PIN;
          iso808_1_obj[Instance].Pin.STATUS_GPort = OUT13_SWITCH_0_STATUS_GPIO_PORT;
          iso808_1_obj[Instance].Pin.STATUS_GPin = OUT13_SWITCH_0_STATUS_GPIO_PIN;
          break;

        default:
          ret = OUT13_ERROR_WRONG_PARAM;
          break;
      }

      if (ret == OUT13_ERROR_NONE)
      {
        SWITCH_CompObj[Instance] = &iso808_1_obj[Instance];
        /* The second cast (void *) is added to bypass Misra R11.3 rule */
        SWITCH_Drv[Instance] = (SWITCH_CommonDrv_t *)(void *)&ISO808_1_COMMON_Driver;

        if (SWITCH_Drv[Instance]->Init(SWITCH_CompObj[Instance]) != IPS_SWITCH_OK)
        {
          ret = OUT13_ERROR_UNKNOWN_FAILURE;
        }
        else
        {
          ret = OUT13_ERROR_NONE;
        }
      }
    }
  }
  return ret;
}

__weak int32_t OUT13_SetTimerForPwm(uint8_t pwmEnable)
{
  int32_t ret = OUT13_ERROR_NONE;
  
  UNUSED(pwmEnable);

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
