/**
  ******************************************************************************
  * @file    out17a1.c
  * @author  AMS IPC Application Team
  * @brief   This file provides BSP driver functions for Octal High-Side Power
  *          Solid State Switch with both direct input control and SPI interface
  *          for high inductive loads available on the following expansion board
  *           - X-NUCLEO-OUT17A1
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "out17a1.h"
#include "out17_error_code.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup OUT17A1 OUT17A1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup OUT17A1_Global_Variables OUT17A1 Global Variables
  * @{
  */

#ifdef APP_PAR_IFC
/** Switch component object */
void *SWITCH_CompObj[OUT17_INSTANCES_NBR];
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
/** Relay component object */
void *RELAY_CompObj[OUT17_INSTANCES_NBR];
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/

/** @defgroup OUT17A1_Private_Typedef OUT17A1 Private Typedef
  * @{
  */

typedef struct {
  EXTI_HandleTypeDef *p_fault;
  EXTI_HandleTypeDef *p_pgood;
  EXTI_HandleTypeDef *p_twarn;
} EXTI_board_t;

/**
  * @}
  */

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @defgroup OUT17A1_Private_Macros  OUT17A1 Private Macros
  * @{
  */

EXTI_HandleTypeDef H_EXTI_FAULT_L = {.Line = H_EXTI_LINE_FAULT_L};
EXTI_HandleTypeDef H_EXTI_PGOOD_L = {.Line = H_EXTI_LINE_PGOOD_L};
EXTI_HandleTypeDef H_EXTI_TWARN_L = {.Line = H_EXTI_LINE_TWARN_L};

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup OUT17A1_Private_Variables  OUT17A1 Private Variables
  * @{
  */

#ifdef APP_PAR_IFC
static SWITCH_CommonDrv_t *SWITCH_Drv[OUT17_INSTANCES_NBR];
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
static RELAY_CommonDrv_t *RELAY_Drv[OUT17_INSTANCES_NBR];
#endif /* #ifdef APP_SPI_IFC */

extern EXTI_board_t exti_board[IPS8200HQ_1_SPI_DC_INSTANCES_NBR];
EXTI_board_t exti_board[IPS8200HQ_1_SPI_DC_INSTANCES_NBR] = {
  {
#ifdef USE_BOARD_0
    .p_fault = &H_EXTI_FAULT_L,
    .p_pgood = &H_EXTI_PGOOD_L,
    .p_twarn = &H_EXTI_TWARN_L
#else
    .p_fault = NULL,
    .p_pgood = NULL,
    .p_twarn = NULL
#endif /* #ifdef USE_BOARD_0 */
  }

  ,{
#ifdef USE_BOARD_1
    .p_fault = &H_EXTI_FAULT_L,
    .p_pgood = &H_EXTI_PGOOD_L,
    .p_twarn = &H_EXTI_TWARN_L
#else
    .p_fault = NULL,
    .p_pgood = NULL,
    .p_twarn = NULL
#endif /* #ifdef USE_BOARD_1 */
    }
};

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup OUT17A1_Private_Function_Prototypes OUT17A1 Private Function Prototypes
  * @{
  */

#ifdef APP_PAR_IFC
static int32_t IPS8200HQ_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT17_SWITCH_Init_Parameters_t *pInitParam);
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
static int32_t IPS8200HQ_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT17_RELAY_Init_Parameters_t *pInitParam);
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup OUT17A1_Functions_Definition OUT17A1 Functions Definition
  * @{
  */

/**
  * @brief  Provide Register callback parameters for the specific board used.
  * @param  Instance  Specific board used identifier.
  *         This parameter can be one of the following values:
  *           @arg OUT17_BOARD_0: Board 0 selected
  *           @arg OUT17_BOARD_1: Board 1 selected
  * @param  fault_isr  First function pointer to provide to the register callback.
  * @param  pgood_isr  Second function pointer to provide to the register callback.
  * @param  twarn_isr  Third function pointer to provide to the register callback.
  * @retval 0 value if success else fail.
  */
int32_t OUT17_RegisterCallBack(uint8_t Instance, void (*fault_isr)(void), void (*pgood_isr)(void), void (*twarn_isr)(void))
{
	if (Instance < OUT17_INSTANCES_NBR)
  {
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_fault, HAL_EXTI_COMMON_CB_ID, fault_isr);
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_pgood, HAL_EXTI_COMMON_CB_ID, pgood_isr);
		(void)HAL_EXTI_RegisterCallback(exti_board[Instance].p_twarn, HAL_EXTI_COMMON_CB_ID, twarn_isr);
		return 0;
  }
  else
  {
    return 1;
  }
}

#ifdef APP_PAR_IFC
/* ----------------------------- Parallel section --------------------------------- */

/* Following function definition is needed because in PAR IFC we don't include stm32f4xx_nucleo_bus.c in our project */
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
int32_t OUT17_SWITCH_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT17_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret = OUT17_ERROR_NONE;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if ((NbDevices == 0U) || (NbDevices > OUT17_SWITCH_DEVICES_NBR))
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    switch (ChipId)
    {
      case OUT17_SWITCH_CHIP_ID:
        if (IPS8200HQ_1_Register_Instance(Instance, ChipId, NbDevices, pInitParam) != OUT17_ERROR_NONE)
        {
          ret =  OUT17_ERROR_NO_INIT;
        }
        break;

      default:
        ret = OUT17_ERROR_WRONG_PARAM;
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
int32_t OUT17_SWITCH_DeInit(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->DeInit(SWITCH_CompObj[Instance]) != OUT17_ERROR_NONE)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    Device_System_State_bitmap &= ~(0x1U << Instance);
    if (Device_System_State_bitmap == 0U)
    {
      Device_System_CtrlMode[Instance] = (uint8_t)OUT17_UNDEF_CTRL_MODE;
    }
    ret = OUT17_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get power switch instance capabilities
  * @param  Instance Power switch instance
  * @param  pCapabilities pointer to capabilities
  * @retval BSP status
  */
int32_t OUT17_SWITCH_GetCapabilities(uint8_t Instance, OUT17_SWITCH_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->GetCapabilities(SWITCH_CompObj[Instance], pCapabilities) != OUT17_ERROR_NONE)
  {
    ret = OUT17_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT17_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get Chip Id value
  * @param  Instance Power switch instance
  * @param  pId pointer to the chip Id
  * @retval BSP status
  */
int32_t OUT17_SWITCH_ReadID(uint8_t Instance, uint16_t *pId)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if (SWITCH_Drv[Instance]->ReadID(SWITCH_CompObj[Instance], pId) != OUT17_ERROR_NONE)
  {
    ret = OUT17_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelDc(SWITCH_CompObj[Instance], ChanId, pChanDc) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelFreq(SWITCH_CompObj[Instance], ChanId, pChanFreq) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChannelStatus(SWITCH_CompObj[Instance], ChanId, pChanStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetCtrlPinStatus(SWITCH_CompObj[Instance], CtrlPinId, pCtrlPinStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetFaultStatus(SWITCH_CompObj[Instance], pFaultStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetPwmEnable(SWITCH_CompObj[Instance], ChanId, pPwmEnable) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick
  * @param  Instance Power switch instance
  * @retval BSP status
  */
int32_t OUT17_SWITCH_PwmTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->PwmTick(SWITCH_CompObj[Instance]) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelDc(SWITCH_CompObj[Instance], ChanId, ChanDc) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelFreq(SWITCH_CompObj[Instance], ChanId, ChanFreq) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetChannelStatus(SWITCH_CompObj[Instance], ChanId, ChanStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetAllChannelStatus(SWITCH_CompObj[Instance], pChanStatusBitmap) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetAllChannelStatus(SWITCH_CompObj[Instance], ChanStatusBitmap) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetCtrlPinStatus(SWITCH_CompObj[Instance], CtrlPinId, CtrlPinStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set device operating mode
  * @param  Instance Power switch instance
  * @param  pCtrlMode Pointer to Control Mode variable
  * @retval BSP status
  */
int32_t OUT17_SWITCH_SetOperatingMode(uint8_t Instance, uint8_t *pCtrlMode)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetOperatingMode(SWITCH_CompObj[Instance], pCtrlMode) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Get device operating mode (no impact on global system variables)
  * @param  Instance Power switch instance
  * @param  pChipType Pointer to Chip Type variable
  * @retval BSP status
  */
int32_t OUT17_SWITCH_GetChipType(uint8_t Instance, uint8_t *pChipType)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->GetChipType(SWITCH_CompObj[Instance], pChipType) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_SWITCH_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (SWITCH_Drv[Instance]->SetPwmEnable(SWITCH_CompObj[Instance], ChanId, pwmEnable) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @}
  */

/** @defgroup OUT17A1_Private_Functions OUT17A1 Private Functions
  * @{
  */

static int32_t OUT17_Init(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT17_ERROR_NONE;
}

static int32_t OUT17_DeInit(void)
{
  /* function does nothing as there is no bus */
  /* but kept to keep similar structure than other driver */
  return OUT17_ERROR_NONE;
}

/**
  * @brief  Register Bus IOs for instance 0 if component ID is OK
  * @param  Instance Power switch instance
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam Pointer to initial Parameters structure
  * @retval BSP status
  */
static int32_t IPS8200HQ_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT17_SWITCH_Init_Parameters_t *pInitParam)
{
  int32_t ret;
  IPS8200HQ_1_IO_t io_ctx;
  IPS8200HQ_1_Capabilities_t cap;
  static IPS8200HQ_1_Object_t ips8200hq_1_obj[OUT17_INSTANCES_NBR];

  /* Configure the switch driver */
  io_ctx.Init         = OUT17_Init;
  io_ctx.DeInit       = OUT17_DeInit;
  io_ctx.GetTick      = OUT17_GetTick;
  io_ctx.ReadFault    = OUT17_ReadFault;
  io_ctx.WritePin     = OUT17_WritePin;
  io_ctx.ReadPin      = OUT17_ReadPin;
  io_ctx.WriteChan    = OUT17_WriteChan;
  io_ctx.ReadChan     = OUT17_ReadChan;
  io_ctx.WriteAllChan = OUT17_WriteAllChan;
  io_ctx.ReadAllChan  = OUT17_ReadAllChan;
  io_ctx.SetPwm       = OUT17_SetPwm;

  ret = OUT17_ERROR_NONE;
  if (pInitParam == NULL)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    ips8200hq_1_obj[Instance].pwmFreq = pInitParam->pwmFreq;
    if (IPS8200HQ_1_RegisterBusIO(&ips8200hq_1_obj[Instance], &io_ctx) != IPS_DEVICE_OK)
    {
      ret = OUT17_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      int32_t loop;
      ips8200hq_1_obj[Instance].chipId = ChipId;
      ips8200hq_1_obj[Instance].Instance = Instance;
      ips8200hq_1_obj[Instance].isPresent = 1;
      ips8200hq_1_obj[Instance].nbDevices = NbDevices;

      (void)IPS8200HQ_1_GetCapabilities(&ips8200hq_1_obj[Instance], &cap);
      ips8200hq_1_obj[Instance].nbChannels = cap.nbChannels;
      ips8200hq_1_obj[Instance].firstCtrl = cap.firstCtrlPin;
      ips8200hq_1_obj[Instance].nbCtrls = cap.nbCtrlPins;

      ips8200hq_1_obj[Instance].isPwmEnabled = 0;
      ips8200hq_1_obj[Instance].chanEnBitmap = 0;
      ips8200hq_1_obj[Instance].ChanSteadyStateBitmap = 0;
      ips8200hq_1_obj[Instance].nextChanEnBitmap = 0;
      ips8200hq_1_obj[Instance].ControlPinsBitmap = 0;
      for (loop = (int32_t)ips8200hq_1_obj[Instance].nbChannels - 1; loop >= 0; loop--)
      {
        ips8200hq_1_obj[Instance].channelFreq[loop] = 0;
        ips8200hq_1_obj[Instance].channelDc[loop] = 0;
      }
      ips8200hq_1_obj[Instance].ctrlMode = (uint8_t)OUT17_UNDEF_CTRL_MODE;
      ips8200hq_1_obj[Instance].spiMode = (uint8_t)OUT17_SPI_W_NONE;
      Device_System_State_bitmap |= (0x1U << Instance);

      switch (Instance)
      {
        case 0:
          ips8200hq_1_obj[Instance].Pin.IN1_GPort = OUT17_SWITCH_0_IN1_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.IN1_GPin = OUT17_SWITCH_0_IN1_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.IN2_GPort = OUT17_SWITCH_0_IN2_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.IN2_GPin = OUT17_SWITCH_0_IN2_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.IN3_GPort = OUT17_SWITCH_0_IN3_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.IN3_GPin = OUT17_SWITCH_0_IN3_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.IN4_GPort = OUT17_SWITCH_0_IN4_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.IN4_GPin = OUT17_SWITCH_0_IN4_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.IN5_GPort = OUT17_SWITCH_0_IN5_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.IN5_GPin = OUT17_SWITCH_0_IN5_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.IN6_GPort = OUT17_SWITCH_0_IN6_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.IN6_GPin = OUT17_SWITCH_0_IN6_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.IN7_GPort = OUT17_SWITCH_0_IN7_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.IN7_GPin = OUT17_SWITCH_0_IN7_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.IN8_GPort = OUT17_SWITCH_0_IN8_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.IN8_GPin = OUT17_SWITCH_0_IN8_GPIO_PIN;

          ips8200hq_1_obj[Instance].Pin.SEL2_L_GPort = OUT17_SWITCH_0_SEL2_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.SEL2_L_GPin = OUT17_SWITCH_0_SEL2_L_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.SEL1_GPort = OUT17_SWITCH_0_SEL1_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.SEL1_GPin = OUT17_SWITCH_0_SEL1_GPIO_PIN;

          ips8200hq_1_obj[Instance].Pin.FAULT_L_GPort = OUT17_SWITCH_0_FAULT_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.FAULT_L_GPin = OUT17_SWITCH_0_FAULT_L_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.PGOOD_L_GPort = OUT17_SWITCH_0_PGOOD_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.PGOOD_L_GPin = OUT17_SWITCH_0_PGOOD_L_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.TWARN_L_GPort = OUT17_SWITCH_0_TWARN_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.TWARN_L_GPin = OUT17_SWITCH_0_TWARN_L_GPIO_PIN;
          break;

        default:
          ret = OUT17_ERROR_WRONG_PARAM;
          break;
      }

      if (ret == OUT17_ERROR_NONE)
      {
        SWITCH_CompObj[Instance] = &ips8200hq_1_obj[Instance];
        /* The second cast (void *) is added to bypass Misra R11.3 rule */
        SWITCH_Drv[Instance] = (SWITCH_CommonDrv_t *)(void *)&IPS8200HQ_1_COMMON_Driver;

        if (SWITCH_Drv[Instance]->Init(SWITCH_CompObj[Instance]) != IPS_DEVICE_OK)
        {
          ret = OUT17_ERROR_UNKNOWN_FAILURE;
        }
        else
        {
          ret = OUT17_ERROR_NONE;
        }
      }
    }
  }
  return ret;
}
__weak int32_t OUT17_SetTimerForPwm(uint8_t pwmEnable)
{
  int32_t ret = OUT17_ERROR_NONE;
  
  UNUSED(pwmEnable);

  return ret;
}
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
/* ------------------------------- SPI section ------------------------------------ */

/**
  * @brief  Initializes the power relay
  * @param  Instance relay instance to be used
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam pointer to the init parameters structure
  * @retval BSP status
  */
int32_t OUT17_RELAY_Init(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT17_RELAY_Init_Parameters_t *pInitParam)
{
  int32_t ret = OUT17_ERROR_NONE;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if ((NbDevices == 0U) || (NbDevices > OUT17_RELAY_DEVICES_NBR))
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    switch (ChipId)
    {
      case OUT17_RELAY_CHIP_ID:
        if (IPS8200HQ_1_Register_Instance(Instance, ChipId, NbDevices, pInitParam) != OUT17_ERROR_NONE)
        {
          ret =  OUT17_ERROR_NO_INIT;
        }
        break;

      default:
        ret = OUT17_ERROR_WRONG_PARAM;
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
int32_t OUT17_RELAY_DeInit(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if (RELAY_Drv[Instance]->DeInit(RELAY_CompObj[Instance]) != OUT17_ERROR_NONE)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    Device_System_State_bitmap &= ~(0x1U << Instance);
    if (Device_System_State_bitmap == 0U)
    {
      Device_System_CtrlMode[Instance] = (uint8_t)OUT17_UNDEF_CTRL_MODE;
    }
    ret = OUT17_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get power relay instance capabilities
  * @param  Instance Power relay instance
  * @param  pCapabilities pointer to capabilities
  * @retval BSP status
  */
int32_t OUT17_RELAY_GetCapabilities(uint8_t Instance, OUT17_RELAY_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if (RELAY_Drv[Instance]->GetCapabilities(RELAY_CompObj[Instance], pCapabilities) != OUT17_ERROR_NONE)
  {
    ret = OUT17_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT17_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Get Chip Id value
  * @param  Instance Power relay instance
  * @param  pId pointer to the chip Id
  * @retval BSP status
  */
int32_t OUT17_RELAY_ReadID(uint8_t Instance, uint16_t *pId)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if (RELAY_Drv[Instance]->ReadID(RELAY_CompObj[Instance], pId) != OUT17_ERROR_NONE)
  {
    ret = OUT17_ERROR_UNKNOWN_COMPONENT;
  }
  else
  {
    ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_GetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetChannelDc(RELAY_CompObj[Instance], ChanId, pChanDc) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_GetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetChannelFreq(RELAY_CompObj[Instance], ChanId, pChanFreq) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_GetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetChannelStatus(RELAY_CompObj[Instance], ChanId, pChanStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_GetAllChannelStatus(uint8_t Instance, uint8_t *pChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetAllChannelStatus(RELAY_CompObj[Instance], pChanStatusBitmap) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_GetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t *pPinStatus)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetCtrlPinStatus(RELAY_CompObj[Instance], CtrlPinId, pPinStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_GetFaultStatus(uint8_t Instance, uint8_t *pFaultStatus)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetFaultStatus(RELAY_CompObj[Instance], pFaultStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_GetFaultRegister(uint8_t Instance, uint16_t *pFaultRegister)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetFaultRegister(RELAY_CompObj[Instance], pFaultRegister) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_SetChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetChannelStatus(RELAY_CompObj[Instance], ChanId, ChanStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_SetAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetAllChannelStatus(RELAY_CompObj[Instance], ChanStatusBitmap) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_SetCtrlPinStatus(uint8_t Instance, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetCtrlPinStatus(RELAY_CompObj[Instance], CtrlPinId, CtrlPinStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_SetChannelDc(uint8_t Instance, uint8_t ChanId, uint8_t ChanDc)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetChannelDc(RELAY_CompObj[Instance], ChanId, ChanDc) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_SetChannelFreq(uint8_t Instance, uint8_t ChanId, uint16_t ChanFreq)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetChannelFreq(RELAY_CompObj[Instance], ChanId, ChanFreq) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_GetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t *pPwmEnable)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetPwmEnable(RELAY_CompObj[Instance], ChanId, pPwmEnable) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Set device operating mode
  * @param  Instance Power switch instance
  * @param  pCtrlMode Pointer to Control Mode variable
  * @retval BSP status
  */
int32_t OUT17_RELAY_SetOperatingMode(uint8_t Instance, uint8_t *pCtrlMode)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetOperatingMode(RELAY_CompObj[Instance], pCtrlMode) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Enables or disables Daisy Chain Mode (valid only if SPI HW conf has been detected)
  * @param  Instance Power switch instance
  * @param  DcEnable Logical flag used to enable (1) or disable (0) Daisy Chain Mode
  * @retval BSP status
  */
int32_t OUT17_RELAY_EnableDaisyChain(uint8_t Instance, uint8_t DcEnable)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->EnableDaisyChain(RELAY_CompObj[Instance], DcEnable) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_SetPwmEnable(uint8_t Instance, uint8_t ChanId, uint8_t pwmEnable)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->SetPwmEnable(RELAY_CompObj[Instance], ChanId, pwmEnable) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick for parallel independent conf
  * @param  Instance Power relay instance
  * @retval BSP status
  */
int32_t OUT17_RELAY_PwmTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->PwmTick(RELAY_CompObj[Instance]) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Guard Timer Tick for SPI conf
  * @param  Instance Power relay instance
  * @retval BSP status
  */
int32_t OUT17_RELAY_GuardTimerTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->GuardTimerTick(RELAY_CompObj[Instance]) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Watchdog Timer Tick for SPI conf
  * @param  Instance Power relay instance
  * @retval BSP status
  */
int32_t OUT17_RELAY_WatchdogTimerTick(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    if (RELAY_Drv[Instance]->WatchdogTimerTick(RELAY_CompObj[Instance]) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  PWM Tick for Daisy Chain conf
  * @retval BSP status
  */
int32_t OUT17_RELAY_PwmTick_DaisyChain(void)
{
  int32_t ret;

  if (IPS8200HQ_1_PwmTick_DaisyChain() != OUT17_ERROR_NONE)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT17_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief  Guard Timer Tick for Daisy Chain conf
  * @retval BSP status
  */
int32_t OUT17_RELAY_GuardTimerTick_DaisyChain(void)
{
  int32_t ret;

  if (IPS8200HQ_1_GuardTimerTick_DaisyChain() != OUT17_ERROR_NONE)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_QueueChannelStatus(uint8_t Instance, uint8_t ChanId, uint8_t ChanStatus)
{
   int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if ((Device_System_CtrlMode[Instance] & 0xF) != (uint8_t)OUT17_SPI_DC_CTRL_MODE)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else if (Device_System_State_bitmap != (uint8_t)OUT17_SPI_DC_FULLSYS)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    if (RELAY_Drv[Instance]->QueueChannelStatus(RELAY_CompObj[Instance], ChanId, ChanStatus) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_QueueAllChannelStatus(uint8_t Instance, uint8_t ChanStatusBitmap)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if ((Device_System_CtrlMode[Instance] & 0xF) != (uint8_t)OUT17_SPI_DC_CTRL_MODE)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else if (Device_System_State_bitmap != (uint8_t)OUT17_SPI_DC_FULLSYS)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    if (RELAY_Drv[Instance]->QueueAllChannelStatus(RELAY_CompObj[Instance], ChanStatusBitmap) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }
  return ret;
}

/**
  * @brief  Send the SPI write queue to the daisy chain
  * @param  Instance Power relay instance
  * @retval BSP status
  */
int32_t OUT17_RELAY_SendQueuedChannelStatus(uint8_t Instance)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if ((Device_System_CtrlMode[Instance] & 0xF) != (uint8_t)OUT17_SPI_DC_CTRL_MODE)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else if (Device_System_State_bitmap != (uint8_t)OUT17_SPI_DC_FULLSYS)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else
  {
     if (RELAY_Drv[Instance]->SendQueuedChannelStatus() != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
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
int32_t OUT17_RELAY_GetFaultRegister_DaisyChain(uint8_t Instance, uint32_t *pFaultRegister)
{
  int32_t ret;

  if (Instance >= OUT17_INSTANCES_NBR)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else if ((Device_System_CtrlMode[Instance] & 0xF) != (uint8_t)OUT17_SPI_DC_CTRL_MODE)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else if (Device_System_State_bitmap != (uint8_t)OUT17_SPI_DC_FULLSYS)
  {
    ret = OUT17_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    if (RELAY_Drv[Instance]->GetFaultRegister_DaisyChain(pFaultRegister) != OUT17_ERROR_NONE)
    {
      ret = OUT17_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = OUT17_ERROR_NONE;
    }
  }

  return ret;
}

/**
  * @brief This function enable the interruptions
  * @retval None
  */
void OUT17_EnableIrq(void)
{
  __enable_irq();
}

/**
  * @brief This function disable the interruptions
  * @retval None
  */
void OUT17_DisableIrq(void)
{
  __disable_irq();
}

/**
  * @brief  Register Bus IOs for instance 0 if component ID is OK
  * @param  Instance Power relay instance
  * @param  ChipId Id of the chip
  * @param  NbDevices Number of connected devices
  * @param  pInitParam Pointer to initial Parameters structure
  * @retval BSP status
  */
static int32_t IPS8200HQ_1_Register_Instance(uint8_t Instance, uint16_t ChipId, uint8_t NbDevices, OUT17_RELAY_Init_Parameters_t *pInitParam)
{
  int32_t ret;
  IPS8200HQ_1_IO_t io_ctx;
  IPS8200HQ_1_Capabilities_t cap;
  static IPS8200HQ_1_Object_t ips8200hq_1_obj[OUT17_INSTANCES_NBR];

  /* Configure the relay driver */
  io_ctx.Init             = OUT17_SpiInit;
  io_ctx.DeInit           = OUT17_SpiDeInit;
  io_ctx.SpiWrite         = OUT17_SpiWrite;

  io_ctx.GetTick          = OUT17_GetTick;
  io_ctx.ReadFault        = OUT17_ReadFault;
  io_ctx.WritePin         = OUT17_WritePin;
  io_ctx.ReadPin          = OUT17_ReadPin;
  io_ctx.SetPwm           = OUT17_SetPwm;
  io_ctx.StartGuardTimer  = OUT17_GuardTimerEnable;
  io_ctx.StopGuardTimer   = OUT17_GuardTimerDisable;
  io_ctx.EnableIrq        = OUT17_EnableIrq;
  io_ctx.DisableIrq       = OUT17_DisableIrq;

  ret = OUT17_ERROR_NONE;
  if (pInitParam == NULL)
  {
    ret = OUT17_ERROR_WRONG_PARAM;
  }
  else
  {
    ips8200hq_1_obj[Instance].pwmFreq = pInitParam->pwmFreq;
    ips8200hq_1_obj[Instance].spiFreq = pInitParam->spiFreq;
    ips8200hq_1_obj[Instance].timingTcss = pInitParam->timingTcss;
    ips8200hq_1_obj[Instance].timingTwd = pInitParam->timingTwd;
    ips8200hq_1_obj[Instance].timingTwm = pInitParam->timingTwm;
    if (IPS8200HQ_1_RegisterBusIO(&ips8200hq_1_obj[Instance], &io_ctx) != IPS_DEVICE_OK)
    {
      ret = OUT17_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      int32_t loop;

      ips8200hq_1_obj[Instance].chipId = ChipId;
      ips8200hq_1_obj[Instance].Instance = Instance;
      ips8200hq_1_obj[Instance].isPresent = 1U;
      ips8200hq_1_obj[Instance].nbDevices = NbDevices;

      (void)IPS8200HQ_1_GetCapabilities(&ips8200hq_1_obj[Instance], &cap);
      ips8200hq_1_obj[Instance].nbChannels = cap.nbChannels;
      ips8200hq_1_obj[Instance].firstCtrl = cap.firstCtrlPin;
      ips8200hq_1_obj[Instance].nbCtrls = cap.nbCtrlPins;

      ips8200hq_1_obj[Instance].isPwmEnabled = 0U;
      ips8200hq_1_obj[Instance].chanEnBitmap = 0U;
      ips8200hq_1_obj[Instance].ChanSteadyStateBitmap = 0U;
      ips8200hq_1_obj[Instance].ChanSteadyStatePwmBitmap = 0U;
      ips8200hq_1_obj[Instance].newChanSteadyStateBitmap = FALSE;
      ips8200hq_1_obj[Instance].nextChanEnBitmap = 0U;
      for (loop = (int32_t)ips8200hq_1_obj[Instance].nbChannels - 1; loop >= 0; loop--)
      {
        ips8200hq_1_obj[Instance].channelFreq[loop] = 0U;
        ips8200hq_1_obj[Instance].channelDc[loop] = 0U;
      }
      ips8200hq_1_obj[Instance].ctrlMode = OUT17_UNDEF_CTRL_MODE;
      ips8200hq_1_obj[Instance].spiMode = (uint8_t)OUT17_SPI_W_NONE;
      Device_System_State_bitmap |= (0x1U << Instance);

      switch (Instance)
      {
        case 0:
#ifdef USE_BOARD_0
          ips8200hq_1_obj[Instance].Pin.SPI_SS_GPort = OUT17_RELAY_0_SPI_SS_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.SPI_SS_GPin = OUT17_RELAY_0_SPI_SS_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.OUT_EN_GPort = OUT17_RELAY_0_OUT_EN_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.OUT_EN_GPin = OUT17_RELAY_0_OUT_EN_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.WD_GPort = OUT17_RELAY_0_WD_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.WD_GPin = OUT17_RELAY_0_WD_GPIO_PIN;

          ips8200hq_1_obj[Instance].Pin.SEL2_L_GPort = OUT17_RELAY_0_SEL2_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.SEL2_L_GPin = OUT17_RELAY_0_SEL2_L_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.SEL1_GPort = OUT17_RELAY_0_SEL1_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.SEL1_GPin = OUT17_RELAY_0_SEL1_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.WDEN_GPort = OUT17_RELAY_0_WDEN_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.WDEN_GPin = OUT17_RELAY_0_WDEN_GPIO_PIN;

          ips8200hq_1_obj[Instance].Pin.FAULT_L_GPort = OUT17_RELAY_0_FAULT_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.FAULT_L_GPin = OUT17_RELAY_0_FAULT_L_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.PGOOD_L_GPort = OUT17_RELAY_0_PGOOD_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.PGOOD_L_GPin = OUT17_RELAY_0_PGOOD_L_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.TWARN_L_GPort = OUT17_RELAY_0_TWARN_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.TWARN_L_GPin = OUT17_RELAY_0_TWARN_L_GPIO_PIN;
#endif /* #ifdef USE_BOARD_0 */
          break;

        case 1:
#ifdef USE_BOARD_1
          ips8200hq_1_obj[Instance].Pin.SPI_SS_GPort = OUT17_RELAY_1_SPI_SS_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.SPI_SS_GPin = OUT17_RELAY_1_SPI_SS_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.OUT_EN_GPort = OUT17_RELAY_1_OUT_EN_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.OUT_EN_GPin = OUT17_RELAY_1_OUT_EN_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.WD_GPort = OUT17_RELAY_1_WD_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.WD_GPin = OUT17_RELAY_1_WD_GPIO_PIN;

          ips8200hq_1_obj[Instance].Pin.SEL2_L_GPort = OUT17_RELAY_1_SEL2_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.SEL2_L_GPin = OUT17_RELAY_1_SEL2_L_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.SEL1_GPort = OUT17_RELAY_1_SEL1_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.SEL1_GPin = OUT17_RELAY_1_SEL1_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.WDEN_GPort = OUT17_RELAY_1_WDEN_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.WDEN_GPin = OUT17_RELAY_1_WDEN_GPIO_PIN;

          ips8200hq_1_obj[Instance].Pin.FAULT_L_GPort = OUT17_RELAY_1_FAULT_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.FAULT_L_GPin = OUT17_RELAY_1_FAULT_L_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.PGOOD_L_GPort = OUT17_RELAY_1_PGOOD_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.PGOOD_L_GPin = OUT17_RELAY_1_PGOOD_L_GPIO_PIN;
          ips8200hq_1_obj[Instance].Pin.TWARN_L_GPort = OUT17_RELAY_1_TWARN_L_GPIO_PORT;
          ips8200hq_1_obj[Instance].Pin.TWARN_L_GPin = OUT17_RELAY_1_TWARN_L_GPIO_PIN;
#endif /* #ifdef USE_BOARD_1 */
          break;

        default:
          ret = OUT17_ERROR_WRONG_PARAM;
          break;
      }

      if (ret == OUT17_ERROR_NONE)
      {
        RELAY_CompObj[Instance] = &ips8200hq_1_obj[Instance];

        /* The second cast (void *) is added to bypass Misra R11.3 rule */
        RELAY_Drv[Instance] = (RELAY_CommonDrv_t *)(void *)&IPS8200HQ_1_COMMON_Driver;

        if (RELAY_Drv[Instance]->Init(RELAY_CompObj[Instance]) != IPS_DEVICE_OK)
        {
          ret = OUT17_ERROR_UNKNOWN_FAILURE;
        }
        else
        {
          ret = OUT17_ERROR_NONE;
        }
      }
    }
  }
  return ret;
}

__weak int32_t OUT17_SetTimerForPwm(uint8_t pwmEnable)
{
  int32_t ret = OUT17_ERROR_NONE;
  
  UNUSED(pwmEnable);

  return ret;
}

__weak int32_t OUT17_GuardTimerStart(void)
{
  int32_t ret = OUT17_ERROR_NONE;

  return ret;
}

__weak int32_t OUT17_GuardTimerStop(void)
{
  int32_t ret = OUT17_ERROR_NONE;

  return ret;
}
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
