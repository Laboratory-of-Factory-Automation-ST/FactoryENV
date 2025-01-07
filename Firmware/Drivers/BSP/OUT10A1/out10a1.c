/**
  ******************************************************************************
  * @file    out10a1.c
  * @author  AMS IPC Application Team
  * @brief   This file provides BSP driver functions for IPS device on
  *          the following expansion board
  *           - X-NUCLEO-OUT10A1
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "out10a1.h"
#include "out10_error_code.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT10A1 OUT10A1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT10A1_Global_Variables OUT10A1 Global Variables
  * @{
  */

/** Switch component object */
void *SWITCH_CompObj[OUT10_SWITCH_INSTANCES_NBR];

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/

/** @defgroup OUT10A1_Private_Typedef OUT10A1 Private Typedef
 * @{
 */

typedef struct {
  EXTI_HandleTypeDef *p_out_fb;
  EXTI_HandleTypeDef *p_diag;
} EXTI_board_t;

/**
  * @}
  */

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @defgroup OUT10A1_Private_Macros OUT10A1 Private Macros
 * @{
 */

#ifdef USE_BOARD_0
EXTI_HandleTypeDef H_EXTI_OUT_FB = {.Line = H_EXTI_LINE_OUT_FB};
EXTI_HandleTypeDef H_EXTI_DIAG = {.Line = H_EXTI_LINE_DIAG};
#endif /* #ifdef USE_BOARD_0 */
#ifdef USE_BOARD_1
EXTI_HandleTypeDef H_EXTI_OUT_FB_Alt1 = {.Line = H_EXTI_LINE_OUT_FB_Alt1};
EXTI_HandleTypeDef H_EXTI_DIAG_Alt1 = {.Line = H_EXTI_LINE_DIAG_Alt1};
#endif /* #ifdef USE_BOARD_1 */
#ifdef USE_BOARD_2
EXTI_HandleTypeDef H_EXTI_OUT_FB_Alt2 = {.Line = H_EXTI_LINE_OUT_FB_Alt2};
EXTI_HandleTypeDef H_EXTI_DIAG_Alt2 = {.Line = H_EXTI_LINE_DIAG_Alt2};
#endif /* #ifdef USE_BOARD_2 */
#ifdef USE_BOARD_3
EXTI_HandleTypeDef H_EXTI_OUT_FB_Alt3 = {.Line = H_EXTI_LINE_OUT_FB_Alt3};
EXTI_HandleTypeDef H_EXTI_DIAG_Alt3 = {.Line = H_EXTI_LINE_DIAG_Alt3};
#endif /* #ifdef USE_BOARD_3 */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup OUT10A1_Private_Variables OUT10A1 Private Variables
 * @{
 */

static SWITCH_CommonDrv_t *SWITCH_Drv[OUT10_SWITCH_INSTANCES_NBR];
extern EXTI_board_t exti_board[OUT10_SWITCH_INSTANCES_NBR];
EXTI_board_t exti_board[OUT10_SWITCH_INSTANCES_NBR] = {
	    {
#ifdef USE_BOARD_0
	      .p_out_fb = &H_EXTI_OUT_FB,
	      .p_diag = &H_EXTI_DIAG
#else
		  .p_out_fb = NULL,
		  .p_diag = NULL
#endif /* #ifdef USE_BOARD_0 */
	    }

    ,{
#ifdef USE_BOARD_1
      .p_out_fb = &H_EXTI_OUT_FB_Alt1,
      .p_diag = &H_EXTI_DIAG_Alt1
#else
		  .p_out_fb = NULL,
		  .p_diag = NULL
#endif /* #ifdef USE_BOARD_1 */
    }

    ,{
#ifdef USE_BOARD_2
      .p_out_fb = &H_EXTI_OUT_FB_Alt2,
      .p_diag = &H_EXTI_DIAG_Alt2
#else
		  .p_out_fb = NULL,
		  .p_diag = NULL
#endif /* #ifdef USE_BOARD_2 */
    }

    ,{
#ifdef USE_BOARD_3
    		.p_out_fb = &H_EXTI_OUT_FB_Alt3,
			.p_diag = &H_EXTI_DIAG_Alt3
#else
		  .p_out_fb = NULL,
		  .p_diag = NULL
#endif /* #ifdef USE_BOARD_3 */
    }
};

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup OUT10A1_Private_Function_Prototypes OUT10A1 Private Function Prototypes
  * @{
  */

static int32_t IPS161HF_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT10_SWITCH_Init_Parameters_t *pInitParam);
static int32_t OUT10_Init(void);
static int32_t OUT10_DeInit(void);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT10A1_Functions_Definition OUT10A1 Functions Definition
  * @{
  */

/**
  * @brief  Provide Register callback parameters for the specific board used.
  * @param  Instance  Specific board used identifier.
  *         This parameter can be one of the following values:
  *           @arg OUT10_BOARD_0: Board 0 selected
  *           @arg OUT10_BOARD_1: Board 1 selected
  *           @arg OUT10_BOARD_2: Board 2 selected
  *           @arg OUT10_BOARD_3: Board 3 selected
  * @param  out_fb_isr  First function pointer to provide to the register callback.
  * @param  diag_isr  Second function pointer to provide to the register callback.
  * @retval 0 value if success else fail.
  */

int32_t OUT10_SWITCH_RegisterCallBack(uint8_t Instance, void (*out_fb_isr)(void), void (*diag_isr)(void))
{
  if (Instance < OUT10_SWITCH_INSTANCES_NBR)
  {
    (void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_out_fb, HAL_EXTI_COMMON_CB_ID, out_fb_isr);
    (void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_diag, HAL_EXTI_COMMON_CB_ID, diag_isr);
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
int32_t OUT10_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT10_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret = OUT10_ERROR_NONE;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else if ((NbDevices == 0U) || (NbDevices > OUT10_SWITCH_DEVICES_NBR))
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    switch (ChipId)
    {
      case OUT10_SWITCH_CHIP_ID:
        if (IPS161HF_Register_Instance(Instance, ChipId, NbDevices, pInitParam) != OUT10_ERROR_NONE)
        {
          ret =  OUT10_ERROR_NO_INIT;
        }
        break;

      default:
        ret = OUT10_ERROR_WRONG_PARAM;
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
int32_t OUT10_SWITCH_DeInit(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->DeInit(SWITCH_CompObj[Instance]) != OUT10_ERROR_NONE)
  {
    ret = OUT10_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT10_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get power switch instance capabilities
  * @param  Instance Power switch instance
  * @param  pCapabilities pointer to capabilities
  * @retval BSP status
  */
int32_t OUT10_SWITCH_GetCapabilities(uint8_t Instance, OUT10_SWITCH_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->GetCapabilities(SWITCH_CompObj[Instance], pCapabilities) != OUT10_ERROR_NONE)
  {
    ret = OUT10_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT10_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get Chip Id value
  * @param  Instance Power switch instance
  * @param  pId pointer to the chip Id
  * @retval BSP status
  */
int32_t OUT10_SWITCH_ReadID(uint8_t Instance, uint16_t *pId)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->ReadID(SWITCH_CompObj[Instance], pId) != OUT10_ERROR_NONE)
  {
    ret = OUT10_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelDc(SWITCH_CompObj[Instance], ChanId, pChanDc) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelFreq(SWITCH_CompObj[Instance], ChanId, pChanFreq) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelStatus(SWITCH_CompObj[Instance], ChanId, pChanStatus) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetCtrlPinStatus(SWITCH_CompObj[Instance], CtrlPinId, pCtrlPinStatus) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetFaultStatus(SWITCH_CompObj[Instance], pFaultStatus) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetPwmEnable(SWITCH_CompObj[Instance], ChanId, pPwmEnable) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick
  * @param  Instance Power switch instance
  * @retval BSP status
  */
int32_t OUT10_SWITCH_PwmTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->PwmTick(SWITCH_CompObj[Instance]) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelDc(SWITCH_CompObj[Instance], ChanId, ChanDc) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelFreq(SWITCH_CompObj[Instance], ChanId, ChanFreq) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelStatus(SWITCH_CompObj[Instance], ChanId, ChanStatus) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetAllChannelStatus(SWITCH_CompObj[Instance], pChanStatusBitmap) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetAllChannelStatus(SWITCH_CompObj[Instance], ChanStatusBitmap) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetCtrlPinStatus(SWITCH_CompObj[Instance], CtrlPinId, CtrlPinStatus) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
    }
  }
  return ret;
}

/**
 * @brief  Enable or disable Nch-DRV sync with IN PWM mode
 * @param  Instance Power switch instance
 * @param  ChanId Input channel Id
 * @param  phase Delay before Nch-DRV goes ON after IN goes low. It's a percentage of IN OFF-period
 * @param  duty ON-period length for Nch-DRV. It's a percentage of IN OFF-period
 * @param  syncEnable Enable or disable
 * @retval BSP status
 */
int32_t OUT10_SWITCH_SetNchDrvSyncEnable(uint8_t Instance, uint8_t ChanId, uint8_t phase, uint8_t duty, uint8_t syncEnable)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetNchDrvSyncEnable(SWITCH_CompObj[Instance], ChanId, phase, duty, syncEnable) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
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
int32_t OUT10_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable)
{
  int32_t ret;

  if (Instance >= OUT10_SWITCH_INSTANCES_NBR)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetPwmEnable(SWITCH_CompObj[Instance], ChanId, pwmEnable) != OUT10_ERROR_NONE)
    {
      ret = OUT10_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT10_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @}
  */

/** @defgroup OUT10A1_Private_Functions OUT10A1 Private Functions
  * @{
  */

static int32_t OUT10_Init(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT10_ERROR_NONE;
}

static int32_t OUT10_DeInit(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT10_ERROR_NONE;
}

/**
  * @brief  Register Bus IOs for instance 0 if component ID is OK
  * @param  Instance Power switch instance
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam Pointer to initial Parameters structure
  * @retval BSP status
  */
static int32_t IPS161HF_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT10_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret;
  IPS161HF_IO_t io_ctx;
  IPS161HF_Capabilities_t cap;
  static IPS161HF_Object_t ips161hf_obj[OUT10_SWITCH_INSTANCES_NBR];

  /* Configure the switch driver */
  io_ctx.Init         = OUT10_Init;
  io_ctx.DeInit       = OUT10_DeInit;
  io_ctx.GetTick      = OUT10_GetTick;
  io_ctx.ReadFault    = OUT10_ReadFault;
  io_ctx.WritePin     = OUT10_WritePin;
  io_ctx.ReadPin      = OUT10_ReadPin;
  io_ctx.WriteChan    = OUT10_WriteChan;
  io_ctx.ReadChan     = OUT10_ReadChan;
  io_ctx.WriteAllChan = OUT10_WriteAllChan;
  io_ctx.ReadAllChan  = OUT10_ReadAllChan;
  io_ctx.SetPwm       = OUT10_SetPwm;

  ret = OUT10_ERROR_NONE;
  if (pInitParam == NULL)
  {
    ret = OUT10_ERROR_WRONG_PARAM;
  }
  else
  {
    ips161hf_obj[Instance].pwmFreq = pInitParam->pwmFreq;
    if (IPS161HF_RegisterBusIO(&ips161hf_obj[Instance], &io_ctx) != IPS_SWITCH_OK)
    {
      ret = OUT10_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      int32_t loop;
      ips161hf_obj[Instance].chipId = ChipId;
      ips161hf_obj[Instance].Instance = Instance;
      ips161hf_obj[Instance].isPresent = 1;
      ips161hf_obj[Instance].nbDevices = NbDevices;

      (void)IPS161HF_GetCapabilities(&ips161hf_obj[Instance], &cap);
      ips161hf_obj[Instance].nbChannels = cap.nbChannels;
      ips161hf_obj[Instance].firstCtrl = cap.firstCtrlPin;
      ips161hf_obj[Instance].nbCtrls = cap.nbCtrlPins;

      ips161hf_obj[Instance].isPwmEnabled = 0;
      ips161hf_obj[Instance].chanEnBitmap = 0;
      ips161hf_obj[Instance].ChanSteadyStateBitmap = 0;
      ips161hf_obj[Instance].nextChanEnBitmap = 0;
      ips161hf_obj[Instance].ControlPinsBitmap = 0;
      for (loop = (int32_t)ips161hf_obj[Instance].nbChannels - 1; loop >= 0; loop--)
      {
        ips161hf_obj[Instance].channelFreq[loop] = 0;
        ips161hf_obj[Instance].channelDc[loop] = 0;
      }

      switch (Instance)
      {
        case 0:
#ifdef USE_BOARD_0
          ips161hf_obj[Instance].Pin.IN1_GPort = OUT10_SWITCH_0_IN1_GPIO_PORT;
          ips161hf_obj[Instance].Pin.IN1_GPin = OUT10_SWITCH_0_IN1_GPIO_PIN;
          ips161hf_obj[Instance].Pin.DIAG_GPort = OUT10_SWITCH_0_DIAG_GPIO_PORT;
          ips161hf_obj[Instance].Pin.DIAG_GPin = OUT10_SWITCH_0_DIAG_GPIO_PIN;
          ips161hf_obj[Instance].Pin.Nch_DRV_GPort = OUT10_SWITCH_0_NCH_DRV_GPIO_PORT;
          ips161hf_obj[Instance].Pin.Nch_DRV_GPin = OUT10_SWITCH_0_NCH_DRV_GPIO_PIN;
          ips161hf_obj[Instance].Pin.OUT_FB_GPort = OUT10_SWITCH_0_OUT_FB_GPIO_PORT;
          ips161hf_obj[Instance].Pin.OUT_FB_GPin = OUT10_SWITCH_0_OUT_FB_GPIO_PIN;
#endif /* #ifdef USE_BOARD_0 */
          break;

        case 1:
#ifdef USE_BOARD_1
          ips161hf_obj[Instance].Pin.IN1_GPort = OUT10_SWITCH_1_IN1_GPIO_PORT;
          ips161hf_obj[Instance].Pin.IN1_GPin = OUT10_SWITCH_1_IN1_GPIO_PIN;
          ips161hf_obj[Instance].Pin.DIAG_GPort = OUT10_SWITCH_1_DIAG_GPIO_PORT;
          ips161hf_obj[Instance].Pin.DIAG_GPin = OUT10_SWITCH_1_DIAG_GPIO_PIN;
          ips161hf_obj[Instance].Pin.Nch_DRV_GPort = OUT10_SWITCH_1_NCH_DRV_GPIO_PORT;
          ips161hf_obj[Instance].Pin.Nch_DRV_GPin = OUT10_SWITCH_1_NCH_DRV_GPIO_PIN;
          ips161hf_obj[Instance].Pin.OUT_FB_GPort = OUT10_SWITCH_1_OUT_FB_GPIO_PORT;
          ips161hf_obj[Instance].Pin.OUT_FB_GPin = OUT10_SWITCH_1_OUT_FB_GPIO_PIN;
#endif /* #ifdef USE_BOARD_1 */
          break;

        case 2:
#ifdef USE_BOARD_2
          ips161hf_obj[Instance].Pin.IN1_GPort = OUT10_SWITCH_2_IN1_GPIO_PORT;
          ips161hf_obj[Instance].Pin.IN1_GPin = OUT10_SWITCH_2_IN1_GPIO_PIN;
          ips161hf_obj[Instance].Pin.DIAG_GPort = OUT10_SWITCH_2_DIAG_GPIO_PORT;
          ips161hf_obj[Instance].Pin.DIAG_GPin = OUT10_SWITCH_2_DIAG_GPIO_PIN;
          ips161hf_obj[Instance].Pin.Nch_DRV_GPort = OUT10_SWITCH_2_NCH_DRV_GPIO_PORT;
          ips161hf_obj[Instance].Pin.Nch_DRV_GPin = OUT10_SWITCH_2_NCH_DRV_GPIO_PIN;
          ips161hf_obj[Instance].Pin.OUT_FB_GPort = OUT10_SWITCH_2_OUT_FB_GPIO_PORT;
          ips161hf_obj[Instance].Pin.OUT_FB_GPin = OUT10_SWITCH_2_OUT_FB_GPIO_PIN;
#endif /* #ifdef USE_BOARD_2 */
          break;

        case 3:
#ifdef USE_BOARD_3
          ips161hf_obj[Instance].Pin.IN1_GPort = OUT10_SWITCH_3_IN1_GPIO_PORT;
          ips161hf_obj[Instance].Pin.IN1_GPin = OUT10_SWITCH_3_IN1_GPIO_PIN;
          ips161hf_obj[Instance].Pin.DIAG_GPort = OUT10_SWITCH_3_DIAG_GPIO_PORT;
          ips161hf_obj[Instance].Pin.DIAG_GPin = OUT10_SWITCH_3_DIAG_GPIO_PIN;
          ips161hf_obj[Instance].Pin.Nch_DRV_GPort = OUT10_SWITCH_3_NCH_DRV_GPIO_PORT;
          ips161hf_obj[Instance].Pin.Nch_DRV_GPin = OUT10_SWITCH_3_NCH_DRV_GPIO_PIN;
          ips161hf_obj[Instance].Pin.OUT_FB_GPort = OUT10_SWITCH_3_OUT_FB_GPIO_PORT;
          ips161hf_obj[Instance].Pin.OUT_FB_GPin = OUT10_SWITCH_3_OUT_FB_GPIO_PIN;
#endif /* #ifdef USE_BOARD_3 */
          break;

        default:
          ret = OUT10_ERROR_WRONG_PARAM;
          break;
      }

      if (ret == OUT10_ERROR_NONE)
      {
        SWITCH_CompObj[Instance] = &ips161hf_obj[Instance];
        /* The second cast (void *) is added to bypass Misra R11.3 rule */
        SWITCH_Drv[Instance] = (SWITCH_CommonDrv_t *)(void *)&IPS161HF_COMMON_Driver;

        if (SWITCH_Drv[Instance]->Init(SWITCH_CompObj[Instance]) != IPS_SWITCH_OK)
        {
          ret = OUT10_ERROR_UNKNOWN_FAILURE;
        }
        else
        {
          ret = OUT10_ERROR_NONE;
        }
      }
    }
  }
  return ret;
}

__weak int32_t OUT10_SetTimerForPwm(uint8_t pwmEnable)
{
  int32_t ret = OUT10_ERROR_NONE;
  
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
