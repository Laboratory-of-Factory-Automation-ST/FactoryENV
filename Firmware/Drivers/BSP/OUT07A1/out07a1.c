/**
  ******************************************************************************
  * @file    out07a1.c
  * @author  AMS IPC Application Team
  * @brief   This file provides BSP driver functions for IPS device on
  *          the following expansion board
  *           - X-NUCLEO-OUT07A1
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

/* Includes ------------------------------------------------------------------*/
#include "out07a1.h"
#include "out07_error_code.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT07A1 OUT07A1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT07A1_Global_Variables OUT07A1 Global Variables
  * @{
  */

/** Switch component object */
void *SWITCH_CompObj[OUT07_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/

/** @defgroup OUT07A1_Private_Typedef OUT07A1 Private Typedef
  * @{
  */

typedef struct {
  EXTI_HandleTypeDef *p_fault;
  EXTI_HandleTypeDef *p_ol;
  EXTI_HandleTypeDef *p_diag1;
  EXTI_HandleTypeDef *p_diag2;
  EXTI_HandleTypeDef *p_diag3;
  EXTI_HandleTypeDef *p_diag4;
} EXTI_board_t;

/**
  * @}
  */

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @defgroup OUT07A1_Private_Macros  OUT07A1 Private Macros
  * @{
  */

EXTI_HandleTypeDef H_EXTI_FLT_L = {.Line = H_EXTI_LINE_FLT_L};
EXTI_HandleTypeDef H_EXTI_OL_L = {.Line = H_EXTI_LINE_OL_L};
EXTI_HandleTypeDef H_EXTI_DIAG1_L = {.Line = H_EXTI_LINE_DIAG1_L};
EXTI_HandleTypeDef H_EXTI_DIAG2_L = {.Line = H_EXTI_LINE_DIAG2_L};
EXTI_HandleTypeDef H_EXTI_DIAG3_L = {.Line = H_EXTI_LINE_DIAG3_L};
EXTI_HandleTypeDef H_EXTI_DIAG4_L = {.Line = H_EXTI_LINE_DIAG4_L};

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup OUT07A1_Private_Variables OUT07A1 Private Variables
  * @{
  */

static SWITCH_CommonDrv_t *SWITCH_Drv[OUT07_SWITCH_INSTANCES_NBR];

extern EXTI_board_t exti_board[OUT07_SWITCH_INSTANCES_NBR];
EXTI_board_t exti_board[OUT07_SWITCH_INSTANCES_NBR] = {
  {
#ifdef USE_BOARD_0
    .p_fault = &H_EXTI_FLT_L,
    .p_ol = &H_EXTI_OL_L,
    .p_diag1 = &H_EXTI_DIAG1_L,
    .p_diag2 = &H_EXTI_DIAG2_L,
    .p_diag3 = &H_EXTI_DIAG3_L,
    .p_diag4 = &H_EXTI_DIAG4_L
#else
    .p_fault = NULL,
    .p_ol = NULL,
    .p_diag1 = NULL,
    .p_diag2 = NULL,
    .p_diag3 = NULL,
    .p_diag4 = NULL
#endif /* #ifdef USE_BOARD_0 */
  }
};

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup OUT07A1_Private_Function_Prototypes OUT07A1 Private Function Prototypes
  * @{
  */

static int32_t IPS4260L_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT07_SWITCH_Init_Parameters_t *pInitParam);
static int32_t OUT07_Init(void);
static int32_t OUT07_DeInit(void);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT07A1_Functions_Definition OUT07A1 Functions Definition
  * @{
  */

/**
  * @brief  Provide Register callback parameters for the specific board used.
  * @param  Instance  Specific board used identifier.
  *         This parameter can be one of the following values:
  *           @arg OUT07_BOARD_0: Board 0 selected
  * @param  fault_isr   First function pointer to provide to the register callback.
  * @param  ol_isr      Second function pointer to provide to the register callback.
  * @param  diag1_isr   Third function pointer to provide to the register callback.
  * @param  diag2_isr   Fourth function pointer to provide to the register callback.
  * @param  diag3_isr   Fifth function pointer to provide to the register callback.
  * @param  diag4_isr   Sixth function pointer to provide to the register callback.
  * @retval 0 value if success else fail.
  */
int32_t OUT07_SWITCH_RegisterCallBack(uint8_t Instance, void (*fault_isr)(void), void (*ol_isr)(void), void (*diag1_isr)(void), void (*diag2_isr)(void), void (*diag3_isr)(void), void (*diag4_isr)(void))
{
	if (Instance < OUT07_SWITCH_INSTANCES_NBR)
  {
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_fault, HAL_EXTI_COMMON_CB_ID, fault_isr);
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_ol, HAL_EXTI_COMMON_CB_ID, ol_isr);
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_diag1, HAL_EXTI_COMMON_CB_ID, diag1_isr);
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_diag2, HAL_EXTI_COMMON_CB_ID, diag2_isr);
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_diag3, HAL_EXTI_COMMON_CB_ID, diag3_isr);
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_diag4, HAL_EXTI_COMMON_CB_ID, diag4_isr);
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
int32_t OUT07_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT07_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret = OUT07_ERROR_NONE;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else if ((NbDevices == 0U) || (NbDevices > OUT07_SWITCH_DEVICES_NBR))
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    switch (ChipId)
    {
      case OUT07_SWITCH_CHIP_ID:
        if (IPS4260L_Register_Instance(Instance, ChipId, NbDevices, pInitParam) != OUT07_ERROR_NONE)
        {
          ret =  OUT07_ERROR_NO_INIT;
        }
        break;

      default:
        ret = OUT07_ERROR_WRONG_PARAM;
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
int32_t OUT07_SWITCH_DeInit(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->DeInit(SWITCH_CompObj[Instance]) != OUT07_ERROR_NONE)
  {
    ret = OUT07_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT07_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get power switch instance capabilities
  * @param  Instance Power switch instance
  * @param  pCapabilities pointer to capabilities
  * @retval BSP status
  */
int32_t OUT07_SWITCH_GetCapabilities(uint8_t Instance, OUT07_SWITCH_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->GetCapabilities(SWITCH_CompObj[Instance], pCapabilities) != OUT07_ERROR_NONE)
  {
    ret = OUT07_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT07_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get Chip Id value
  * @param  Instance Power switch instance
  * @param  pId pointer to the chip Id
  * @retval BSP status
  */
int32_t OUT07_SWITCH_ReadID(uint8_t Instance, uint16_t *pId)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->ReadID(SWITCH_CompObj[Instance], pId) != OUT07_ERROR_NONE)
  {
    ret = OUT07_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelDc(SWITCH_CompObj[Instance], ChanId, pChanDc) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelFreq(SWITCH_CompObj[Instance], ChanId, pChanFreq) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelStatus(SWITCH_CompObj[Instance], ChanId, pChanStatus) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get Fault status
  * @param  Instance Power switch instance
  * @param  pFaultStatus pointer to the fault channel status bitmap (LSB) and input channel status bitmap (MSB)
  * @retval BSP status
  */
int32_t OUT07_SWITCH_GetFaultStatus(uint8_t Instance, uint16_t *pFaultStatus)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetFaultStatus(SWITCH_CompObj[Instance], pFaultStatus) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetPwmEnable(SWITCH_CompObj[Instance], ChanId, pPwmEnable) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick
  * @param  Instance Power switch instance
  * @retval BSP status
  */
int32_t OUT07_SWITCH_PwmTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->PwmTick(SWITCH_CompObj[Instance]) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc)
{
   int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelDc(SWITCH_CompObj[Instance], ChanId, ChanDc) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq)
{
   int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelFreq(SWITCH_CompObj[Instance], ChanId, ChanFreq) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelStatus(SWITCH_CompObj[Instance], ChanId, ChanStatus) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetAllChannelStatus(SWITCH_CompObj[Instance], pChanStatusBitmap) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
   int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetAllChannelStatus(SWITCH_CompObj[Instance], ChanStatusBitmap) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
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
int32_t OUT07_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable)
{
   int32_t ret;

  if (Instance >= OUT07_SWITCH_INSTANCES_NBR)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetPwmEnable(SWITCH_CompObj[Instance], ChanId, pwmEnable) != OUT07_ERROR_NONE)
    {
      ret = OUT07_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT07_ERROR_NONE;
    }
  }
  return ret;
}

/******************************************************//**
 * @brief This function enable the interruptions
 * @retval None
 **********************************************************/
void OUT07_EnableIrq(void)
{
  __enable_irq();
}

/******************************************************//**
 * @brief This function disable the interruptions
 * @retval None
 **********************************************************/
void OUT07_DisableIrq(void)
{
  __disable_irq();
}


/**
  * @}
  */

/** @defgroup OUT07A1_Private_Functions OUT07A1 Private Functions
  * @{
  */

static int32_t OUT07_Init(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT07_ERROR_NONE;
}

static int32_t OUT07_DeInit(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT07_ERROR_NONE;
}

/**
  * @brief  Register Bus IOs for instance 0 if component ID is OK
  * @param  Instance Power switch instance
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam Pointer to initial Parameters structure
  * @retval BSP status
  */
static int32_t IPS4260L_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT07_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret;
  IPS4260L_IO_t io_ctx;
  IPS4260L_Capabilities_t cap;
  static IPS4260L_Object_t ips4260l_obj[OUT07_SWITCH_INSTANCES_NBR];

  /* Configure the switch driver */
  io_ctx.Init         = OUT07_Init;
  io_ctx.DeInit       = OUT07_DeInit;
  io_ctx.GetTick      = OUT07_GetTick;
  io_ctx.ReadFault    = OUT07_ReadFault;
  io_ctx.WriteChan    = OUT07_WriteChan;
  io_ctx.ReadChan     = OUT07_ReadChan;
  io_ctx.WriteAllChan = OUT07_WriteAllChan;
  io_ctx.ReadAllChan  = OUT07_ReadAllChan;
  io_ctx.SetPwm       = OUT07_SetPwm;
  io_ctx.EnableIrq    = OUT07_EnableIrq;
  io_ctx.DisableIrq   = OUT07_DisableIrq;

  ret = OUT07_ERROR_NONE;
  if (pInitParam == NULL)
  {
    ret = OUT07_ERROR_WRONG_PARAM;
  }
  else
  {
    ips4260l_obj[Instance].pwmFreq = pInitParam->pwmFreq;
    if (IPS4260L_RegisterBusIO(&ips4260l_obj[Instance], &io_ctx) != IPS_SWITCH_OK)
    {
      ret = OUT07_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      int32_t loop;
      ips4260l_obj[Instance].chipId = ChipId;
      ips4260l_obj[Instance].Instance = Instance;
      ips4260l_obj[Instance].isPresent = 1;
      ips4260l_obj[Instance].nbDevices = NbDevices;

      (void)IPS4260L_GetCapabilities(&ips4260l_obj[Instance], &cap);
      ips4260l_obj[Instance].nbChannels = cap.nbChannels;

      ips4260l_obj[Instance].isPwmEnabled = 0;
      ips4260l_obj[Instance].chanEnBitmap = 0;
      ips4260l_obj[Instance].ChanSteadyStateBitmap = 0;
      ips4260l_obj[Instance].nextChanEnBitmap = 0;
      for (loop = (int32_t)ips4260l_obj[Instance].nbChannels - 1; loop >= 0; loop--)
      {
        ips4260l_obj[Instance].channelFreq[loop] = 0;
        ips4260l_obj[Instance].channelDc[loop] = 0;
      }

      switch (Instance)
      {
        case 0:
          ips4260l_obj[Instance].Pin.IN1_GPort = OUT07_SWITCH_0_IN1_GPIO_PORT;
          ips4260l_obj[Instance].Pin.IN1_GPin = OUT07_SWITCH_0_IN1_GPIO_PIN;
          ips4260l_obj[Instance].Pin.IN2_GPort = OUT07_SWITCH_0_IN2_GPIO_PORT;
          ips4260l_obj[Instance].Pin.IN2_GPin = OUT07_SWITCH_0_IN2_GPIO_PIN;
          ips4260l_obj[Instance].Pin.IN3_GPort = OUT07_SWITCH_0_IN3_GPIO_PORT;
          ips4260l_obj[Instance].Pin.IN3_GPin = OUT07_SWITCH_0_IN3_GPIO_PIN;
          ips4260l_obj[Instance].Pin.IN4_GPort = OUT07_SWITCH_0_IN4_GPIO_PORT;
          ips4260l_obj[Instance].Pin.IN4_GPin = OUT07_SWITCH_0_IN4_GPIO_PIN;
          ips4260l_obj[Instance].Pin.FLT_L_GPort = OUT07_SWITCH_0_FLT_L_GPIO_PORT;
          ips4260l_obj[Instance].Pin.FLT_L_GPin = OUT07_SWITCH_0_FLT_L_GPIO_PIN;
          ips4260l_obj[Instance].Pin.OL_L_GPort = OUT07_SWITCH_0_OL_L_GPIO_PORT;
          ips4260l_obj[Instance].Pin.OL_L_GPin = OUT07_SWITCH_0_OL_L_GPIO_PIN;
          ips4260l_obj[Instance].Pin.DIAG1_L_GPort = OUT07_SWITCH_0_DIAG1_L_GPIO_PORT;
          ips4260l_obj[Instance].Pin.DIAG1_L_GPin = OUT07_SWITCH_0_DIAG1_L_GPIO_PIN;
          ips4260l_obj[Instance].Pin.DIAG2_L_GPort = OUT07_SWITCH_0_DIAG2_L_GPIO_PORT;
          ips4260l_obj[Instance].Pin.DIAG2_L_GPin = OUT07_SWITCH_0_DIAG2_L_GPIO_PIN;
          ips4260l_obj[Instance].Pin.DIAG3_L_GPort = OUT07_SWITCH_0_DIAG3_L_GPIO_PORT;
          ips4260l_obj[Instance].Pin.DIAG3_L_GPin = OUT07_SWITCH_0_DIAG3_L_GPIO_PIN;
          ips4260l_obj[Instance].Pin.DIAG4_L_GPort = OUT07_SWITCH_0_DIAG4_L_GPIO_PORT;
          ips4260l_obj[Instance].Pin.DIAG4_L_GPin = OUT07_SWITCH_0_DIAG4_L_GPIO_PIN;
          break;

        default:
          ret = OUT07_ERROR_WRONG_PARAM;
          break;
      }

      if (ret == OUT07_ERROR_NONE)
      {
        SWITCH_CompObj[Instance] = &ips4260l_obj[Instance];
        /* The second cast (void *) is added to bypass Misra R11.3 rule */
        SWITCH_Drv[Instance] = (SWITCH_CommonDrv_t *)(void *)&IPS4260L_COMMON_Driver;

        if (SWITCH_Drv[Instance]->Init(SWITCH_CompObj[Instance]) != IPS_SWITCH_OK)
        {
          ret = OUT07_ERROR_UNKNOWN_FAILURE;
        }
        else
        {
          ret = OUT07_ERROR_NONE;
        }
      }
    }
  }
  return ret;
}

__weak int32_t OUT07_SetTimerForPwm(uint8_t pwmEnable)
{
  int32_t ret = OUT07_ERROR_NONE;
  
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
