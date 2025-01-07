/**
  ******************************************************************************
  * @file    out11a1.c
  * @author  AMS IPC Application Team
  * @brief   This file provides BSP driver functions for IPS device on
  *          the following expansion board
  *           - X-NUCLEO-OUT11A1
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
#include "out11a1.h"
#include "out11_error_code.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT11A1 OUT11A1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT11A1_Global_Variables OUT11A1 Global Variables
  * @{
  */

EXTI_HandleTypeDef H_EXTI_STATUS = {.Line = H_EXTI_LINE_STATUS};

/** Switch component object */
void *SWITCH_CompObj[OUT11_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup OUT11A1_Private_Variables OUT11A1 Private Variables
  * @{
  */

static SWITCH_CommonDrv_t *SWITCH_Drv[OUT11_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup OUT11A1_Private_Function_Prototypes OUT11A1 Private Function Prototypes
  * @{
  */

static int32_t ISO808_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT11_SWITCH_Init_Parameters_t *pInitParam);
static int32_t OUT11_Init(void);
static int32_t OUT11_DeInit(void);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT11A1_Functions_Definition OUT11A1 Functions Definition
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
int32_t OUT11_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT11_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret = OUT11_ERROR_NONE;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else if ((NbDevices == 0U) || (NbDevices > OUT11_SWITCH_DEVICES_NBR))
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    switch (ChipId)
    {
      case OUT11_SWITCH_CHIP_ID:
        if (ISO808_Register_Instance(Instance, ChipId, NbDevices, pInitParam) != OUT11_ERROR_NONE)
        {
          ret =  OUT11_ERROR_NO_INIT;
        }
        break;

      default:
        ret = OUT11_ERROR_WRONG_PARAM;
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
int32_t OUT11_SWITCH_DeInit(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->DeInit(SWITCH_CompObj[Instance]) != OUT11_ERROR_NONE)
  {
    ret = OUT11_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT11_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get power switch instance capabilities
  * @param  Instance Power switch instance
  * @param  pCapabilities pointer to capabilities
  * @retval BSP status
  */
int32_t OUT11_SWITCH_GetCapabilities(uint8_t Instance, OUT11_SWITCH_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->GetCapabilities(SWITCH_CompObj[Instance], pCapabilities) != OUT11_ERROR_NONE)
  {
    ret = OUT11_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT11_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get Chip Id value
  * @param  Instance Power switch instance
  * @param  pId pointer to the chip Id
  * @retval BSP status
  */
int32_t OUT11_SWITCH_ReadID(uint8_t Instance, uint16_t *pId)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->ReadID(SWITCH_CompObj[Instance], pId) != OUT11_ERROR_NONE)
  {
    ret = OUT11_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelDc(SWITCH_CompObj[Instance], ChanId, pChanDc) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelFreq(SWITCH_CompObj[Instance], ChanId, pChanFreq) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelStatus(SWITCH_CompObj[Instance], ChanId, pChanStatus) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetCtrlPinStatus(SWITCH_CompObj[Instance], CtrlPinId, pCtrlPinStatus) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetFaultStatus(SWITCH_CompObj[Instance], pFaultStatus) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetPwmEnable(SWITCH_CompObj[Instance], ChanId, pPwmEnable) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick
  * @param  Instance Power switch instance
  * @retval BSP status
  */
int32_t OUT11_SWITCH_PwmTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->PwmTick(SWITCH_CompObj[Instance]) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc)
{
   int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelDc(SWITCH_CompObj[Instance], ChanId, ChanDc) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq)
{
   int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelFreq(SWITCH_CompObj[Instance], ChanId, ChanFreq) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelStatus(SWITCH_CompObj[Instance], ChanId, ChanStatus) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetAllChannelStatus(SWITCH_CompObj[Instance], pChanStatusBitmap) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
   int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetAllChannelStatus(SWITCH_CompObj[Instance], ChanStatusBitmap) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetCtrlPinStatus(SWITCH_CompObj[Instance], CtrlPinId, CtrlPinStatus) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_SetOperatingMode(uint8_t Instance, uint8_t opMode)
{
  int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetOperatingMode(SWITCH_CompObj[Instance], opMode) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
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
int32_t OUT11_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable)
{
   int32_t ret;

  if (Instance >= OUT11_SWITCH_INSTANCES_NBR)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetPwmEnable(SWITCH_CompObj[Instance], ChanId, pwmEnable) != OUT11_ERROR_NONE)
    {
      ret = OUT11_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT11_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @}
  */

/** @defgroup OUT11A1_Private_Functions OUT11A1 Private Functions
  * @{
  */

static int32_t OUT11_Init(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT11_ERROR_NONE;
}

static int32_t OUT11_DeInit(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT11_ERROR_NONE;
}

/**
  * @brief  Register Bus IOs for instance 0 if component ID is OK
  * @param  Instance Power switch instance
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam Pointer to initial Parameters structure
  * @retval BSP status
  */
static int32_t ISO808_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT11_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret;
  ISO808_IO_t io_ctx;
  ISO808_Capabilities_t cap;
  static ISO808_Object_t iso808_obj[OUT11_SWITCH_INSTANCES_NBR];

  /* Configure the switch driver */
  io_ctx.Init         = OUT11_Init;
  io_ctx.DeInit       = OUT11_DeInit;
  io_ctx.GetTick      = OUT11_GetTick;
  io_ctx.ReadFault    = OUT11_ReadFault;
  io_ctx.WritePin     = OUT11_WritePin;
  io_ctx.ReadPin      = OUT11_ReadPin;
  io_ctx.WriteChan    = OUT11_WriteChan;
  io_ctx.ReadChan     = OUT11_ReadChan;
  io_ctx.WriteAllChan = OUT11_WriteAllChan;
  io_ctx.ReadAllChan  = OUT11_ReadAllChan;
  io_ctx.SetPwm       = OUT11_SetPwm;

  ret = OUT11_ERROR_NONE;
  if (pInitParam == NULL)
  {
    ret = OUT11_ERROR_WRONG_PARAM;
  }
  else
  {
    iso808_obj[Instance].pwmFreq = pInitParam->pwmFreq;
    if (ISO808_RegisterBusIO(&iso808_obj[Instance], &io_ctx) != IPS_SWITCH_OK)
    {
      ret = OUT11_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      int32_t loop;
      iso808_obj[Instance].chipId = ChipId;
      iso808_obj[Instance].Instance = Instance;
      iso808_obj[Instance].isPresent = 1;
      iso808_obj[Instance].nbDevices = NbDevices;

      (void)ISO808_GetCapabilities(&iso808_obj[Instance], &cap);
      iso808_obj[Instance].nbChannels = cap.nbChannels;
      iso808_obj[Instance].firstCtrl = cap.firstCtrlPin;
      iso808_obj[Instance].nbCtrls = cap.nbCtrlPins;

      iso808_obj[Instance].isPwmEnabled = 0;
      iso808_obj[Instance].chanEnBitmap = 0;
      iso808_obj[Instance].ChanSteadyStateBitmap = 0;
      iso808_obj[Instance].nextChanEnBitmap = 0;
      iso808_obj[Instance].ControlPinsBitmap = 0;
      for (loop = (int32_t)iso808_obj[Instance].nbChannels - 1; loop >= 0; loop--)
      {
        iso808_obj[Instance].channelFreq[loop] = 0;
        iso808_obj[Instance].channelDc[loop] = 0;
      }
      iso808_obj[Instance].ctrlMode = (uint8_t)ISO808_SCM;

      switch (Instance)
      {
        case 0:
          iso808_obj[Instance].Pin.IN1_GPort = OUT11_SWITCH_0_IN1_GPIO_PORT;
          iso808_obj[Instance].Pin.IN1_GPin = OUT11_SWITCH_0_IN1_GPIO_PIN;
          iso808_obj[Instance].Pin.IN2_GPort = OUT11_SWITCH_0_IN2_GPIO_PORT;
          iso808_obj[Instance].Pin.IN2_GPin = OUT11_SWITCH_0_IN2_GPIO_PIN;
          iso808_obj[Instance].Pin.IN3_GPort = OUT11_SWITCH_0_IN3_GPIO_PORT;
          iso808_obj[Instance].Pin.IN3_GPin = OUT11_SWITCH_0_IN3_GPIO_PIN;
          iso808_obj[Instance].Pin.IN4_GPort = OUT11_SWITCH_0_IN4_GPIO_PORT;
          iso808_obj[Instance].Pin.IN4_GPin = OUT11_SWITCH_0_IN4_GPIO_PIN;
          iso808_obj[Instance].Pin.IN5_GPort = OUT11_SWITCH_0_IN5_GPIO_PORT;
          iso808_obj[Instance].Pin.IN5_GPin = OUT11_SWITCH_0_IN5_GPIO_PIN;
          iso808_obj[Instance].Pin.IN6_GPort = OUT11_SWITCH_0_IN6_GPIO_PORT;
          iso808_obj[Instance].Pin.IN6_GPin = OUT11_SWITCH_0_IN6_GPIO_PIN;
          iso808_obj[Instance].Pin.IN7_GPort = OUT11_SWITCH_0_IN7_GPIO_PORT;
          iso808_obj[Instance].Pin.IN7_GPin = OUT11_SWITCH_0_IN7_GPIO_PIN;
          iso808_obj[Instance].Pin.IN8_GPort = OUT11_SWITCH_0_IN8_GPIO_PORT;
          iso808_obj[Instance].Pin.IN8_GPin = OUT11_SWITCH_0_IN8_GPIO_PIN;
          iso808_obj[Instance].Pin.LOAD_GPort = OUT11_SWITCH_0_LOAD_GPIO_PORT;
          iso808_obj[Instance].Pin.LOAD_GPin = OUT11_SWITCH_0_LOAD_GPIO_PIN;
          iso808_obj[Instance].Pin.OUT_EN_GPort = OUT11_SWITCH_0_OUT_EN_GPIO_PORT;
          iso808_obj[Instance].Pin.OUT_EN_GPin = OUT11_SWITCH_0_OUT_EN_GPIO_PIN;
          iso808_obj[Instance].Pin.SYNCH_GPort = OUT11_SWITCH_0_SYNCH_GPIO_PORT;
          iso808_obj[Instance].Pin.SYNCH_GPin = OUT11_SWITCH_0_SYNCH_GPIO_PIN;
          iso808_obj[Instance].Pin.STATUS_GPort = OUT11_SWITCH_0_STATUS_GPIO_PORT;
          iso808_obj[Instance].Pin.STATUS_GPin = OUT11_SWITCH_0_STATUS_GPIO_PIN;
          break;

        default:
          ret = OUT11_ERROR_WRONG_PARAM;
          break;
      }

      if (ret == OUT11_ERROR_NONE)
      {
        SWITCH_CompObj[Instance] = &iso808_obj[Instance];
        /* The second cast (void *) is added to bypass Misra R11.3 rule */
        SWITCH_Drv[Instance] = (SWITCH_CommonDrv_t *)(void *)&ISO808_COMMON_Driver;

        if (SWITCH_Drv[Instance]->Init(SWITCH_CompObj[Instance]) != IPS_SWITCH_OK)
        {
          ret = OUT11_ERROR_UNKNOWN_FAILURE;
        }
        else
        {
          ret = OUT11_ERROR_NONE;
        }
      }
    }
  }
  return ret;
}

__weak int32_t OUT11_SetTimerForPwm(uint8_t pwmEnable)
{
  int32_t ret = OUT11_ERROR_NONE;
  
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
