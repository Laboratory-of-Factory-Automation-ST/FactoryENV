/**
  ******************************************************************************
  * @file    out03a1.c
  * @author  AMS IPC Application Team
  * @brief   This file provides BSP driver functions for IPS device on
  *          the following expansion board
  *           - X-NUCLEO-OUT03A1
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
#include "out03a1.h"
#include "out03_error_code.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT03A1 OUT03A1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT03A1_Global_Variables OUT03A1 Global Variables
  * @{
  */

/** Switch component object */
void *SWITCH_CompObj[OUT03_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/

/** @defgroup OUT03A1_Private_Typedef OUT03A1 Private Typedef
  * @{
  */

typedef struct {
  EXTI_HandleTypeDef *p_flt1;
  EXTI_HandleTypeDef *p_flt2;
} EXTI_board_t;

/**
  * @}
  */

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @defgroup OUT03A1_Private_Macros OUT03A1 Private Macros
  * @{
  */

#ifdef USE_BOARD_0
EXTI_HandleTypeDef H_EXTI_FLT1 = {.Line = H_EXTI_LINE_FLT1};
EXTI_HandleTypeDef H_EXTI_FLT2 = {.Line = H_EXTI_LINE_FLT2};
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
EXTI_HandleTypeDef H_EXTI_FLT1_Alt1 = {.Line = H_EXTI_LINE_FLT1_Alt1};
EXTI_HandleTypeDef H_EXTI_FLT2_Alt1 = {.Line = H_EXTI_LINE_FLT2_Alt1};
#endif /* #ifdef USE_BOARD_1 */
#ifdef USE_BOARD_2
EXTI_HandleTypeDef H_EXTI_FLT1_Alt2 = {.Line = H_EXTI_LINE_FLT1_Alt2};
EXTI_HandleTypeDef H_EXTI_FLT2_Alt2 = {.Line = H_EXTI_LINE_FLT2_Alt2};
#endif /* #ifdef USE_BOARD_2 */
#ifdef USE_BOARD_3
EXTI_HandleTypeDef H_EXTI_FLT1_Alt3 = {.Line = H_EXTI_LINE_FLT1_Alt3};
EXTI_HandleTypeDef H_EXTI_FLT2_Alt3 = {.Line = H_EXTI_LINE_FLT2_Alt3};
#endif /* #ifdef USE_BOARD_3 */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup OUT03A1_Private_Variables OUT03A1 Private Variables
  * @{
  */

static SWITCH_CommonDrv_t *SWITCH_Drv[OUT03_SWITCH_INSTANCES_NBR];
extern EXTI_board_t exti_board[OUT03_SWITCH_INSTANCES_NBR];
EXTI_board_t exti_board[OUT03_SWITCH_INSTANCES_NBR] = {
	    {
#ifdef USE_BOARD_0
	      .p_flt1 = &H_EXTI_FLT1,
	      .p_flt2 = &H_EXTI_FLT2
#else
		  .p_flt1 = NULL,
		  .p_flt2 = NULL
#endif /* #ifdef USE_BOARD_0 */
	    }

    ,{
#ifdef USE_BOARD_1
      .p_flt1 = &H_EXTI_FLT1_Alt1,
      .p_flt2 = &H_EXTI_FLT2_Alt1
#else
		  .p_flt1 = NULL,
		  .p_flt2 = NULL
#endif /* #ifdef USE_BOARD_1 */
    }

    ,{
#ifdef USE_BOARD_2
      .p_flt1 = &H_EXTI_FLT1_Alt2,
      .p_flt2 = &H_EXTI_FLT2_Alt2
#else
		  .p_flt1 = NULL,
		  .p_flt2 = NULL
#endif /* #ifdef USE_BOARD_2 */
    }

    ,{
#ifdef USE_BOARD_3
    		.p_flt1 = &H_EXTI_FLT1_Alt3,
			.p_flt2 = &H_EXTI_FLT2_Alt3
#else
		  .p_flt1 = NULL,
		  .p_flt2 = NULL
#endif /* #ifdef USE_BOARD_3 */
    }
};

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup OUT03A1_Private_Function_Prototypes OUT03A1 Private Function Prototypes
  * @{
  */

static int32_t IPS2050H_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT03_SWITCH_Init_Parameters_t *pInitParam);
static int32_t OUT03_Init(void);
static int32_t OUT03_DeInit(void);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT03A1_Functions_Definition OUT03A1 Functions Definition
  * @{
  */

/**
  * @brief  Provide Register callback parameters for the specific board used.
  * @param  Instance  Specific board used identifier.
  *         This parameter can be one of the following values:
  *           @arg OUT03_BOARD_0: Board 0 selected
  *           @arg OUT03_BOARD_1: Board 1 selected
  *           @arg OUT03_BOARD_2: Board 2 selected
  *           @arg OUT03_BOARD_3: Board 3 selected
  * @param  fault1_isr  First function pointer to provide to the register callback.
  * @param  fault2_isr  Second function pointer to provide to the register callback.
  * @retval 0 value if success else fail.
  */

int32_t OUT03_SWITCH_RegisterCallBack(uint8_t Instance, void (*fault1_isr)(void), void (*fault2_isr)(void))
{
  if (Instance < OUT03_SWITCH_INSTANCES_NBR)
  {
    (void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_flt1, HAL_EXTI_COMMON_CB_ID, fault1_isr);
    (void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_flt2, HAL_EXTI_COMMON_CB_ID, fault2_isr);
    return 0;
  }
  else
  {
    return 1;
  }
}

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
int32_t OUT03_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT03_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret = OUT03_ERROR_NONE;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else if ((NbDevices == 0U) || (NbDevices > OUT03_SWITCH_DEVICES_NBR))
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    switch (ChipId)
    {
      case OUT03_SWITCH_CHIP_ID:
        if (IPS2050H_Register_Instance(Instance, ChipId, NbDevices, pInitParam) != OUT03_ERROR_NONE)
        {
          ret =  OUT03_ERROR_NO_INIT;
        }
        break;

      default:
        ret = OUT03_ERROR_WRONG_PARAM;
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
int32_t OUT03_SWITCH_DeInit(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->DeInit(SWITCH_CompObj[Instance]) != OUT03_ERROR_NONE)
  {
    ret = OUT03_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT03_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get power switch instance capabilities
  * @param  Instance Power switch instance
  * @param  pCapabilities pointer to capabilities
  * @retval BSP status
  */
int32_t OUT03_SWITCH_GetCapabilities(uint8_t Instance, OUT03_SWITCH_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->GetCapabilities(SWITCH_CompObj[Instance], pCapabilities) != OUT03_ERROR_NONE)
  {
    ret = OUT03_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT03_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get Chip Id value
  * @param  Instance Power switch instance
  * @param  pId pointer to the chip Id
  * @retval BSP status
  */
int32_t OUT03_SWITCH_ReadID(uint8_t Instance, uint16_t *pId)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->ReadID(SWITCH_CompObj[Instance], pId) != OUT03_ERROR_NONE)
  {
    ret = OUT03_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelDc(SWITCH_CompObj[Instance], ChanId, pChanDc) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelFreq(SWITCH_CompObj[Instance], ChanId, pChanFreq) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelStatus(SWITCH_CompObj[Instance], ChanId, pChanStatus) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetFaultStatus(SWITCH_CompObj[Instance], pFaultStatus) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetPwmEnable(SWITCH_CompObj[Instance], ChanId, pPwmEnable) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick
  * @param  Instance Power switch instance
  * @retval BSP status
  */
int32_t OUT03_SWITCH_PwmTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->PwmTick(SWITCH_CompObj[Instance]) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc)
{
   int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelDc(SWITCH_CompObj[Instance], ChanId, ChanDc) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq)
{
   int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelFreq(SWITCH_CompObj[Instance], ChanId, ChanFreq) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelStatus(SWITCH_CompObj[Instance], ChanId, ChanStatus) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetAllChannelStatus(SWITCH_CompObj[Instance], pChanStatusBitmap) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
   int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetAllChannelStatus(SWITCH_CompObj[Instance], ChanStatusBitmap) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
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
int32_t OUT03_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable)
{
   int32_t ret;

  if (Instance >= OUT03_SWITCH_INSTANCES_NBR)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetPwmEnable(SWITCH_CompObj[Instance], ChanId, pwmEnable) != OUT03_ERROR_NONE)
    {
      ret = OUT03_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT03_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @}
  */

/** @defgroup OUT03A1_Private_Functions OUT03A1 Private Functions
  * @{
  */

static int32_t OUT03_Init(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT03_ERROR_NONE;
}

static int32_t OUT03_DeInit(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT03_ERROR_NONE;
}

/**
  * @brief  Register Bus IOs for instance 0 if component ID is OK
  * @param  Instance Power switch instance
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam Pointer to initial Parameters structure
  * @retval BSP status
  */
static int32_t IPS2050H_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT03_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret;
  IPS2050H_IO_t io_ctx;
  IPS2050H_Capabilities_t cap;
  static IPS2050H_Object_t ips2050h_obj[OUT03_SWITCH_INSTANCES_NBR];

  /* Configure the switch driver */
  io_ctx.Init         = OUT03_Init;
  io_ctx.DeInit       = OUT03_DeInit;
  io_ctx.GetTick      = OUT03_GetTick;
  io_ctx.ReadFault    = OUT03_ReadFault;
  io_ctx.WriteChan    = OUT03_WriteChan;
  io_ctx.ReadChan     = OUT03_ReadChan;
  io_ctx.WriteAllChan = OUT03_WriteAllChan;
  io_ctx.ReadAllChan  = OUT03_ReadAllChan;
  io_ctx.SetPwm       = OUT03_SetPwm;

  ret = OUT03_ERROR_NONE;
  if (pInitParam == NULL)
  {
    ret = OUT03_ERROR_WRONG_PARAM;
  }
  else
  {
    ips2050h_obj[Instance].pwmFreq = pInitParam->pwmFreq;
    if (IPS2050H_RegisterBusIO(&ips2050h_obj[Instance], &io_ctx) != IPS_SWITCH_OK)
    {
      ret = OUT03_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      int32_t loop;
      ips2050h_obj[Instance].chipId = ChipId;
      ips2050h_obj[Instance].Instance = Instance;
      ips2050h_obj[Instance].isPresent = 1;
      ips2050h_obj[Instance].nbDevices = NbDevices;

      (void)IPS2050H_GetCapabilities(&ips2050h_obj[Instance], &cap);
      ips2050h_obj[Instance].nbChannels = cap.nbChannels;

      ips2050h_obj[Instance].isPwmEnabled = 0;
      ips2050h_obj[Instance].chanEnBitmap = 0;
      ips2050h_obj[Instance].ChanSteadyStateBitmap = 0;
      ips2050h_obj[Instance].nextChanEnBitmap = 0;
      for (loop = (int32_t)ips2050h_obj[Instance].nbChannels - 1; loop >= 0; loop--)
      {
        ips2050h_obj[Instance].channelFreq[loop] = 0;
        ips2050h_obj[Instance].channelDc[loop] = 0;
      }

      switch (Instance)
      {
        case 0:
#ifdef USE_BOARD_0
          ips2050h_obj[Instance].Pin.IN1_GPort = OUT03_SWITCH_0_IN1_GPIO_PORT;
          ips2050h_obj[Instance].Pin.IN1_GPin = OUT03_SWITCH_0_IN1_GPIO_PIN;
          ips2050h_obj[Instance].Pin.IN2_GPort = OUT03_SWITCH_0_IN2_GPIO_PORT;
          ips2050h_obj[Instance].Pin.IN2_GPin = OUT03_SWITCH_0_IN2_GPIO_PIN;
          ips2050h_obj[Instance].Pin.FLT1_GPort = OUT03_SWITCH_0_FLT1_GPIO_PORT;
          ips2050h_obj[Instance].Pin.FLT1_GPin = OUT03_SWITCH_0_FLT1_GPIO_PIN;
          ips2050h_obj[Instance].Pin.FLT2_GPort = OUT03_SWITCH_0_FLT2_GPIO_PORT;
          ips2050h_obj[Instance].Pin.FLT2_GPin = OUT03_SWITCH_0_FLT2_GPIO_PIN;
#endif /* #ifdef USE_BOARD_0 */
          break;
#ifdef USE_BOARD_1
        case 1:
          ips2050h_obj[Instance].Pin.IN1_GPort = OUT03_SWITCH_1_IN1_GPIO_PORT;
          ips2050h_obj[Instance].Pin.IN1_GPin = OUT03_SWITCH_1_IN1_GPIO_PIN;
          ips2050h_obj[Instance].Pin.IN2_GPort = OUT03_SWITCH_1_IN2_GPIO_PORT;
          ips2050h_obj[Instance].Pin.IN2_GPin = OUT03_SWITCH_1_IN2_GPIO_PIN;
          ips2050h_obj[Instance].Pin.FLT1_GPort = OUT03_SWITCH_1_FLT1_GPIO_PORT;
          ips2050h_obj[Instance].Pin.FLT1_GPin = OUT03_SWITCH_1_FLT1_GPIO_PIN;
          ips2050h_obj[Instance].Pin.FLT2_GPort = OUT03_SWITCH_1_FLT2_GPIO_PORT;
          ips2050h_obj[Instance].Pin.FLT2_GPin = OUT03_SWITCH_1_FLT2_GPIO_PIN;
          break;
#endif /* #ifdef USE_BOARD_1 */

#ifdef USE_BOARD_2
        case 2:
          ips2050h_obj[Instance].Pin.IN1_GPort = OUT03_SWITCH_2_IN1_GPIO_PORT;
          ips2050h_obj[Instance].Pin.IN1_GPin = OUT03_SWITCH_2_IN1_GPIO_PIN;
          ips2050h_obj[Instance].Pin.IN2_GPort = OUT03_SWITCH_2_IN2_GPIO_PORT;
          ips2050h_obj[Instance].Pin.IN2_GPin = OUT03_SWITCH_2_IN2_GPIO_PIN;
          ips2050h_obj[Instance].Pin.FLT1_GPort = OUT03_SWITCH_2_FLT1_GPIO_PORT;
          ips2050h_obj[Instance].Pin.FLT1_GPin = OUT03_SWITCH_2_FLT1_GPIO_PIN;
          ips2050h_obj[Instance].Pin.FLT2_GPort = OUT03_SWITCH_2_FLT2_GPIO_PORT;
          ips2050h_obj[Instance].Pin.FLT2_GPin = OUT03_SWITCH_2_FLT2_GPIO_PIN;
          break;
#endif /* #ifdef USE_BOARD_2 */

#ifdef USE_BOARD_3
        case 3:
          ips2050h_obj[Instance].Pin.IN1_GPort = OUT03_SWITCH_3_IN1_GPIO_PORT;
          ips2050h_obj[Instance].Pin.IN1_GPin = OUT03_SWITCH_3_IN1_GPIO_PIN;
          ips2050h_obj[Instance].Pin.IN2_GPort = OUT03_SWITCH_3_IN2_GPIO_PORT;
          ips2050h_obj[Instance].Pin.IN2_GPin = OUT03_SWITCH_3_IN2_GPIO_PIN;
          ips2050h_obj[Instance].Pin.FLT1_GPort = OUT03_SWITCH_3_FLT1_GPIO_PORT;
          ips2050h_obj[Instance].Pin.FLT1_GPin = OUT03_SWITCH_3_FLT1_GPIO_PIN;
          ips2050h_obj[Instance].Pin.FLT2_GPort = OUT03_SWITCH_3_FLT2_GPIO_PORT;
          ips2050h_obj[Instance].Pin.FLT2_GPin = OUT03_SWITCH_3_FLT2_GPIO_PIN;
          break;
#endif /* #ifdef USE_BOARD_3 */

        default:
          ret = OUT03_ERROR_WRONG_PARAM;
          break;
      }

      if (ret == OUT03_ERROR_NONE)
      {
        SWITCH_CompObj[Instance] = &ips2050h_obj[Instance];
        /* The second cast (void *) is added to bypass Misra R11.3 rule */
        SWITCH_Drv[Instance] = (SWITCH_CommonDrv_t *)(void *)&IPS2050H_COMMON_Driver;

        if (SWITCH_Drv[Instance]->Init(SWITCH_CompObj[Instance]) != IPS_SWITCH_OK)
        {
          ret = OUT03_ERROR_UNKNOWN_FAILURE;
        }
        else
        {
          ret = OUT03_ERROR_NONE;
        }
      }
    }
  }
  return ret;
}

__weak int32_t OUT03_SetTimerForPwm(uint8_t pwmEnable)
{
  int32_t ret = OUT03_ERROR_NONE;
  
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
