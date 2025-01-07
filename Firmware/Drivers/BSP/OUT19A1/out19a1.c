/**
  ******************************************************************************
  * @file    out19a1.c
  * @author  AMS IPC Application Team
  * @brief   This file provides BSP driver functions for IPS device on
  *          the following expansion boards
  *           - X-NUCLEO-OUT09A1
  *           - X-NUCLEO-OUT19A1
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
#include "out19a1.h"
#include "out19a1_bus.h"
#include "out19_error_code.h"


/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT19A1 OUT19A1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT19A1_Global_Variables OUT19A1 Global Variables
  * @{
  */

EXTI_HandleTypeDef H_EXTI_STATUS = {.Line = H_EXTI_LINE_STATUS};


/** Switch component object */
void *SWITCH_CompObj[OUT19_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup OUT19A1_Private_Variables OUT19A1 Private Variables
  * @{
  */

static SWITCH_CommonDrv_t *SWITCH_Drv[OUT19_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup OUT19A1_Private_Function_Prototypes OUT19A1 Private Function Prototypes
  * @{
  */

static int32_t IPS8160HQ_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT19_SWITCH_Init_Parameters_t *pInitParam);
static int32_t OUT19_Init(void);
static int32_t OUT19_DeInit(void);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT19A1_Functions_Definition OUT19A1 Functions Definition
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
int32_t OUT19_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT19_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret = OUT19_ERROR_NONE;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else if ((NbDevices == 0U) || (NbDevices > OUT19_SWITCH_DEVICES_NBR))
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    switch (ChipId)
    {
      case OUT19_SWITCH_CHIP_ID:
        if (IPS8160HQ_1_Register_Instance(Instance, ChipId, NbDevices, pInitParam) != OUT19_ERROR_NONE)
        {
          ret =  OUT19_ERROR_NO_INIT;
        }
        break;

      default:
        ret = OUT19_ERROR_WRONG_PARAM;
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
int32_t OUT19_SWITCH_DeInit(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->DeInit(SWITCH_CompObj[Instance]) != OUT19_ERROR_NONE)
  {
    ret = OUT19_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT19_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get power switch instance capabilities
  * @param  Instance Power switch instance
  * @param  pCapabilities pointer to capabilities
  * @retval BSP status
  */
int32_t OUT19_SWITCH_GetCapabilities(uint8_t Instance, OUT19_SWITCH_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->GetCapabilities(SWITCH_CompObj[Instance], pCapabilities) != OUT19_ERROR_NONE)
  {
    ret = OUT19_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT19_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get Chip Id value
  * @param  Instance Power switch instance
  * @param  pId pointer to the chip Id
  * @retval BSP status
  */
int32_t OUT19_SWITCH_ReadID(uint8_t Instance, uint16_t *pId)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->ReadID(SWITCH_CompObj[Instance], pId) != OUT19_ERROR_NONE)
  {
    ret = OUT19_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelDc(SWITCH_CompObj[Instance], ChanId, pChanDc) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelFreq(SWITCH_CompObj[Instance], ChanId, pChanFreq) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelStatus(SWITCH_CompObj[Instance], ChanId, pChanStatus) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetFaultStatus(SWITCH_CompObj[Instance], pFaultStatus) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetPwmEnable(SWITCH_CompObj[Instance], ChanId, pPwmEnable) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick
  * @param  Instance Power switch instance
  * @retval BSP status
  */
int32_t OUT19_SWITCH_PwmTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->PwmTick(SWITCH_CompObj[Instance]) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc)
{
   int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelDc(SWITCH_CompObj[Instance], ChanId, ChanDc) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq)
{
   int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelFreq(SWITCH_CompObj[Instance], ChanId, ChanFreq) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelStatus(SWITCH_CompObj[Instance], ChanId, ChanStatus) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetAllChannelStatus(SWITCH_CompObj[Instance], pChanStatusBitmap) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
   int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetAllChannelStatus(SWITCH_CompObj[Instance], ChanStatusBitmap) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
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
int32_t OUT19_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable)
{
   int32_t ret;

  if (Instance >= OUT19_SWITCH_INSTANCES_NBR)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetPwmEnable(SWITCH_CompObj[Instance], ChanId, pwmEnable) != OUT19_ERROR_NONE)
    {
      ret = OUT19_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT19_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @}
  */

/** @defgroup OUT19A1_Private_Functions OUT19A1 Private Functions
  * @{
  */

static int32_t OUT19_Init(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT19_ERROR_NONE;
}

static int32_t OUT19_DeInit(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT19_ERROR_NONE;
}

/**
  * @brief  Register Bus IOs for instance 0 if component ID is OK
  * @param  Instance Power switch instance
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam Pointer to initial Parameters structure
  * @retval BSP status
  */
static int32_t IPS8160HQ_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT19_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret;
  IPS8160HQ_1_IO_t io_ctx;
  IPS8160HQ_1_Capabilities_t cap;
  static IPS8160HQ_1_Object_t ips8160hq_1_obj[OUT19_SWITCH_INSTANCES_NBR];

  /* Configure the switch driver */
  io_ctx.Init         = OUT19_Init;
  io_ctx.DeInit       = OUT19_DeInit;
  io_ctx.GetTick      = OUT19_GetTick;
  io_ctx.ReadFault    = OUT19_ReadFault;
  io_ctx.WriteChan    = OUT19_WriteChan;
  io_ctx.ReadChan     = OUT19_ReadChan;
  io_ctx.WriteAllChan = OUT19_WriteAllChan;
  io_ctx.ReadAllChan  = OUT19_ReadAllChan;
  io_ctx.SetPwm       = OUT19_SetPwm;

  ret = OUT19_ERROR_NONE;
  if (pInitParam == NULL)
  {
    ret = OUT19_ERROR_WRONG_PARAM;
  }
  else
  {
    ips8160hq_1_obj[Instance].pwmFreq = pInitParam->pwmFreq;
    if (IPS8160HQ_1_RegisterBusIO(&ips8160hq_1_obj[Instance], &io_ctx) != IPS_SWITCH_OK)
    {
      ret = OUT19_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      int32_t loop;
      ips8160hq_1_obj[Instance].chipId = ChipId;
      ips8160hq_1_obj[Instance].Instance = Instance;
      ips8160hq_1_obj[Instance].isPresent = 1;
      ips8160hq_1_obj[Instance].nbDevices = NbDevices;

      (void)IPS8160HQ_1_GetCapabilities(&ips8160hq_1_obj[Instance], &cap);
      ips8160hq_1_obj[Instance].nbChannels = cap.nbChannels;

      ips8160hq_1_obj[Instance].isPwmEnabled = 0;
      ips8160hq_1_obj[Instance].chanEnBitmap = 0;
      ips8160hq_1_obj[Instance].ChanSteadyStateBitmap = 0;
      ips8160hq_1_obj[Instance].nextChanEnBitmap = 0;
      for (loop = (int32_t)ips8160hq_1_obj[Instance].nbChannels - 1; loop >= 0; loop--)
      {
        ips8160hq_1_obj[Instance].channelFreq[loop] = 0;
        ips8160hq_1_obj[Instance].channelDc[loop] = 0;
      }

      switch (Instance)
      {
        case 0:
          ips8160hq_1_obj[Instance].Pin.IN1_GPort = OUT19_SWITCH_0_IN1_GPIO_PORT;
          ips8160hq_1_obj[Instance].Pin.IN1_GPin = OUT19_SWITCH_0_IN1_GPIO_PIN;
          ips8160hq_1_obj[Instance].Pin.IN2_GPort = OUT19_SWITCH_0_IN2_GPIO_PORT;
          ips8160hq_1_obj[Instance].Pin.IN2_GPin = OUT19_SWITCH_0_IN2_GPIO_PIN;
          ips8160hq_1_obj[Instance].Pin.IN3_GPort = OUT19_SWITCH_0_IN3_GPIO_PORT;
          ips8160hq_1_obj[Instance].Pin.IN3_GPin = OUT19_SWITCH_0_IN3_GPIO_PIN;
          ips8160hq_1_obj[Instance].Pin.IN4_GPort = OUT19_SWITCH_0_IN4_GPIO_PORT;
          ips8160hq_1_obj[Instance].Pin.IN4_GPin = OUT19_SWITCH_0_IN4_GPIO_PIN;
          ips8160hq_1_obj[Instance].Pin.IN5_GPort = OUT19_SWITCH_0_IN5_GPIO_PORT;
          ips8160hq_1_obj[Instance].Pin.IN5_GPin = OUT19_SWITCH_0_IN5_GPIO_PIN;
          ips8160hq_1_obj[Instance].Pin.IN6_GPort = OUT19_SWITCH_0_IN6_GPIO_PORT;
          ips8160hq_1_obj[Instance].Pin.IN6_GPin = OUT19_SWITCH_0_IN6_GPIO_PIN;
          ips8160hq_1_obj[Instance].Pin.IN7_GPort = OUT19_SWITCH_0_IN7_GPIO_PORT;
          ips8160hq_1_obj[Instance].Pin.IN7_GPin = OUT19_SWITCH_0_IN7_GPIO_PIN;
          ips8160hq_1_obj[Instance].Pin.IN8_GPort = OUT19_SWITCH_0_IN8_GPIO_PORT;
          ips8160hq_1_obj[Instance].Pin.IN8_GPin = OUT19_SWITCH_0_IN8_GPIO_PIN;
          ips8160hq_1_obj[Instance].Pin.STATUS_GPort = OUT19_SWITCH_0_STATUS_GPIO_PORT;
          ips8160hq_1_obj[Instance].Pin.STATUS_GPin = OUT19_SWITCH_0_STATUS_GPIO_PIN;
          break;

        default:
          ret = OUT19_ERROR_WRONG_PARAM;
          break;
      }

      if (ret == OUT19_ERROR_NONE)
      {
        SWITCH_CompObj[Instance] = &ips8160hq_1_obj[Instance];
        /* The second cast (void *) is added to bypass Misra R11.3 rule */
        SWITCH_Drv[Instance] = (SWITCH_CommonDrv_t *)(void *)&IPS8160HQ_1_COMMON_Driver;

        if (SWITCH_Drv[Instance]->Init(SWITCH_CompObj[Instance]) != IPS_SWITCH_OK)
        {
          ret = OUT19_ERROR_UNKNOWN_FAILURE;
        }
        else
        {
          ret = OUT19_ERROR_NONE;
        }
      }
    }
  }
  return ret;
}

__weak int32_t OUT19_SetTimerForPwm(uint8_t pwmEnable)
{
  int32_t ret = OUT19_ERROR_NONE;
  
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
