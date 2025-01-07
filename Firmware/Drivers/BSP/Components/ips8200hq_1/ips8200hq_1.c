/**
  ******************************************************************************
  * @file    ips8200hq_1.c
  * @author  AMS IPC Application Team
  * @brief   IPS8200HQ-1 driver
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
#include "ips8200hq_1.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */

/** @addtogroup IPS8200HQ_1 IPS8200HQ_1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup IPS8200HQ_1_Global_Variables IPS8200HQ_1 Global Variables
  * @{
  */

/** Instance counter  */
uint8_t IPS_NbInstances;

/** Device counter  */
uint8_t IPS_NbDevices;

/* Global system configuration mode */
uint8_t Device_System_CtrlMode[IPS8200HQ_1_SPI_DC_INSTANCES_NBR];

/* Global system watchdog mode */
uint8_t Device_System_WdMode[IPS8200HQ_1_SPI_DC_INSTANCES_NBR];

/* Global system configuration mode */
uint8_t Device_System_ChipType = 0U;

/* Global system PWM enable bitmap (it takes in count which boards have PWM enabled) */
uint8_t Device_System_PWMEnable_bitmap;

/* Global system activation state */
uint8_t Device_System_State_bitmap;

#ifdef APP_PAR_IFC
/** Common driver structure which lists IPS8200HQ functions */
IPS8200HQ_1_CommonDrv_t IPS8200HQ_1_COMMON_Driver =
{
  IPS8200HQ_1_Init,
  IPS8200HQ_1_DeInit,
  IPS8200HQ_1_ReadID,
  IPS8200HQ_1_GetCapabilities,
  IPS8200HQ_1_GetFaultStatus,
  IPS8200HQ_1_GetChannelStatus,
  IPS8200HQ_1_SetChannelStatus,
  IPS8200HQ_1_GetAllChannelStatus,
  IPS8200HQ_1_SetAllChannelStatus,
  IPS8200HQ_1_GetChannelFreq,
  IPS8200HQ_1_SetChannelFreq,
  IPS8200HQ_1_GetChannelDc,
  IPS8200HQ_1_SetChannelDc,
  IPS8200HQ_1_GetPwmEnable,
  IPS8200HQ_1_SetPwmEnable,
  IPS8200HQ_1_PwmTick,
  IPS8200HQ_1_GetCtrlPinStatus,
  IPS8200HQ_1_SetCtrlPinStatus,
  IPS8200HQ_1_SetOperatingMode,
  IPS8200HQ_1_GetChipType
};

#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
extern void *RELAY_CompObj[IPS8200HQ_1_INSTANCES_NBR];

/** Common driver structure which lists IPS8200HQ-1 functions */
IPS8200HQ_1_CommonDrv_t IPS8200HQ_1_COMMON_Driver =
{
  IPS8200HQ_1_Init,
  IPS8200HQ_1_DeInit,
  IPS8200HQ_1_ReadID,
  IPS8200HQ_1_GetCapabilities,
  IPS8200HQ_1_GetFaultStatus,
  IPS8200HQ_1_GetFaultRegister,
  IPS8200HQ_1_GetChannelStatus,
  IPS8200HQ_1_SetChannelStatus,
  IPS8200HQ_1_GetCtrlPinStatus,
  IPS8200HQ_1_SetCtrlPinStatus,
  IPS8200HQ_1_GetAllChannelStatus,
  IPS8200HQ_1_SetAllChannelStatus,
  IPS8200HQ_1_GetChannelFreq,
  IPS8200HQ_1_SetChannelFreq,
  IPS8200HQ_1_GetChannelDc,
  IPS8200HQ_1_SetChannelDc,
  IPS8200HQ_1_GetPwmEnable,
  IPS8200HQ_1_SetPwmEnable,
  IPS8200HQ_1_PwmTick,
  IPS8200HQ_1_GuardTimerTick,
  IPS8200HQ_1_WatchdogTimerTick,
  IPS8200HQ_1_QueueChannelStatus,
  IPS8200HQ_1_QueueAllChannelStatus,
  IPS8200HQ_1_SendQueuedChannelStatus,
  IPS8200HQ_1_GetFaultRegister_DaisyChain,
  IPS8200HQ_1_PwmTick_DaisyChain,
  IPS8200HQ_1_GuardTimerTick_DaisyChain,
  IPS8200HQ_1_SetOperatingMode,
  IPS8200HQ_1_GetChipType,
  IPS8200HQ_1_EnableDaisyChain
};

/** SPI Lock time in us between two consecutive SPI access */
int16_t spiLockTime;

/** Watchdog time (tWM) in us between two consecutive device watchdog timer reset */
int32_t watchdogTime;

/** Watchdog hold time (tWD) in us duration needed for a device watchdog timer reset */
int32_t watchdogHoldTime;
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup IPS8200HQ_1_Private_Variables IPS8200HQ_1 Private Variables
  * @{
  */

#ifdef APP_SPI_IFC
/** queuedBitmap flag which is set when a new channel bitmap has to be applied in daisy chaining mode */
static uint8_t queuedBitmap = FALSE;

/** queuedPwmBitmap flag which is set when a new channel Pwm bitmap has to be applied in daisy chaining mode during Pwm operation */
static uint8_t queuedPwmBitmap = FALSE;

/** SPI preemption flag : set when an SPI access occurs under ISR */
uint8_t spiPreemptionByIsr;

/** ISR flag : set when code an ISR is running */
uint8_t isrFlag;

/** SPI Transmit buffer */
static uint8_t aSpiTxBuffer[IPS8200HQ_1_SPI_TX_MAX_NB_BYTES];

/** SPI Receive buffer */
static uint8_t aSpiRxBuffer[IPS8200HQ_1_SPI_RX_MAX_NB_BYTES];
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup IPS8200HQ_1_Private_Function_Prototypes IPS8200HQ_1 Private Function Prototypes
  * @{
  */

static int32_t IPS8200HQ_1_Initialize(IPS8200HQ_1_Object_t *pObj);

#ifdef APP_SPI_IFC
int32_t IPS8200HQ_1_WriteBytes(IPS8200HQ_1_Object_t *pObj, uint8_t *pByteToTransmit, uint8_t *pReceivedByte, uint8_t nbDevices);
#endif /* #ifdef APP_SPI_IFC */

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup IPS8200HQ_1_Functions_Definition IPS8200HQ_1 Functions Definition
  * @{
  */

#ifdef APP_PAR_IFC
/**
  * @brief  Register Component Bus IO operations
  * @param  pObj pointer to the device object
  * @param  pIO  pointer to the IO functions structure
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_RegisterBusIO(IPS8200HQ_1_Object_t *pObj, IPS8200HQ_1_IO_t *pIO)
{
  int32_t ret;

  if (pObj == NULL)
  {
    ret = IPS_DEVICE_ERROR;
  }
  else
  {
    pObj->IO.Init          = pIO->Init;
    pObj->IO.DeInit        = pIO->DeInit;
    pObj->IO.GetTick       = pIO->GetTick;
    pObj->IO.ReadFault     = pIO->ReadFault;
    pObj->IO.WritePin      = pIO->WritePin;
    pObj->IO.ReadPin       = pIO->ReadPin;
    pObj->IO.WriteChan     = pIO->WriteChan;
    pObj->IO.ReadChan      = pIO->ReadChan;
    pObj->IO.WriteAllChan  = pIO->WriteAllChan;
    pObj->IO.ReadAllChan   = pIO->ReadAllChan;
    pObj->IO.SetPwm        = pIO->SetPwm;

    if (pObj->IO.Init != NULL)
    {
      ret = pObj->IO.Init();
    }
    else
    {
      ret = IPS_DEVICE_ERROR;
    }
  }
  return ret;
}

/**
  * @brief  Initialize the IPS8200HQ-1 switch
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_Init(IPS8200HQ_1_Object_t *pObj)
{
  int32_t status = IPS_DEVICE_OK;

  if (pObj->is_initialized == 0U)
  {
    if (IPS8200HQ_1_Initialize(pObj) != IPS_DEVICE_OK)
    {
      status = IPS_DEVICE_ERROR;
    }
    else
    {
      IPS_NbInstances++;
      if (IPS_NbInstances > IPS8200HQ_1_INSTANCES_NBR)
      {
        status = IPS_DEVICE_ERROR;
      }
      else
      {
        pObj->is_initialized = 1;
      }
    }
  }
  return status;
}

/**
  * @brief  Deinitialize the IPS8200HQ-1 switch
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_DeInit(IPS8200HQ_1_Object_t *pObj)
{
  int8_t loop;
  if (pObj->is_initialized == 1U)
  {
    /* Stop PWM */
    for (loop = (int8_t)pObj->nbChannels - 1; loop >= 0; loop--)
    {
      (void)IPS8200HQ_1_SetPwmEnable(pObj, (uint8_t)loop, 0U);
    }

     /* Disable all channels */
    (void)IPS8200HQ_1_SetAllChannelStatus(pObj, 0U);

    IPS_NbInstances--;
  }

  pObj->is_initialized = 0;

  return IPS_DEVICE_OK;
}

/**
  * @brief  Get the status of the specified channel
  * @param  pObj pointer to the device object
  * @param  pChanStatusBitmap pointer to the channel status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetAllChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t* pChanStatusBitmap)
{
  int32_t status = IPS_DEVICE_OK;
  *pChanStatusBitmap = pObj->ChanSteadyStateBitmap;
  return status;
}

/**
  * @brief  Get IPS8200HQ-1 switch capabilities
  * @param  pObj pointer to the device object
  * @param  pCapabilities pointer to the capabilities
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetCapabilities(IPS8200HQ_1_Object_t *pObj, IPS8200HQ_1_Capabilities_t *pCapabilities)
{
  int32_t status = IPS_DEVICE_OK;

  if (pObj->chipId == IPS8200HQ_1_CHIP_ID)
  {
    pCapabilities->nbChannels = IPS8200HQ_1_MAX_NB_CHANNELS;
    pCapabilities->nbCtrlPins = IPS8200HQ_1_MAX_NB_CONTROLS;
    pCapabilities->firstCtrlPin = IPS8200HQ_1_0_FIRST_CONTROL;
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }

  return status;
}

/**
  * @brief  Get the duty cycle of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  pChanDc pointer to the channel duty cycle
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetChannelDc(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t status = IPS_DEVICE_OK;
  if (ChanId < pObj->nbChannels)
  {
    *pChanDc = pObj->channelDc[ChanId];
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  Get the frequency of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  pChanFreq pointer to the channel frequency in in 1/10Hz (from 0 to 1000)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetChannelFreq(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t status = IPS_DEVICE_OK;
  if (ChanId < pObj->nbChannels)
  {
    *pChanFreq = pObj->channelFreq[ChanId];
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  Get the status of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  pChanStatus pointer to the channel status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t status = IPS_DEVICE_OK;

  if (ChanId < pObj->nbChannels)
  {
    *pChanStatus = (pObj->ChanSteadyStateBitmap >> ChanId) & 0x1U;
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  Get the status of a control pin
  * @param  pObj pointer to the device object
  * @param  CtrlPinId Control Pin Id
  * @param  pCtrlPinStatus Pointer to the Control Pin Status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetCtrlPinStatus(IPS8200HQ_1_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus)
{
  int32_t status;
  uint8_t pinState;

  if ((CtrlPinId >= pObj->firstCtrl) && (CtrlPinId < (pObj->firstCtrl + pObj->nbCtrls)))
  {
    status = pObj->IO.ReadPin(&pObj->Pin, CtrlPinId - pObj->firstCtrl, &pinState);
    if (pinState != 0U)
    {
        pObj->ControlPinsBitmap |= (0x1U << (CtrlPinId - pObj->firstCtrl));
    }
    else
    {
        pObj->ControlPinsBitmap &= ~(0x1U << (CtrlPinId - pObj->firstCtrl));
    }
    *pCtrlPinStatus = (pObj->ControlPinsBitmap >> (CtrlPinId - pObj->firstCtrl)) & 0x1U;
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  Get the fault status
  * @param  pObj pointer to the device object
  * @param  pFaultStatus pointer to the fault status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetFaultStatus(IPS8200HQ_1_Object_t *pObj, uint8_t *pFaultStatus)
{
  int32_t status;
  status = pObj->IO.ReadFault(&pObj->Pin, pFaultStatus);
  return status;
}

/**
  * @brief  Get the PWM enable state
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  pPwmEnabled pointer to the PWM enable state
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetPwmEnable(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled)
{
  int32_t status = IPS_DEVICE_OK;

  if (ChanId < pObj->nbChannels)
  {
    *pPwmEnabled = ((pObj->isPwmEnabled >> ChanId) & 0x1U);
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  PWM tick
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_PwmTick(IPS8200HQ_1_Object_t *pObj)
{
  int32_t status = IPS_DEVICE_OK;
  int32_t ret;

  if (pObj->isPwmEnabled != 0U)
  {
    int8_t chanId;
    uint8_t newChanBitMap;

#ifdef IPS_DEBUG
/*    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); */
#endif /* #ifdef IPS_DEBUG */

    /*  Update channels first to minimize latency */
    pObj->chanEnBitmap = pObj->nextChanEnBitmap;

    /*  Load the current bitmap of the corresponding device */
    newChanBitMap =  pObj->chanEnBitmap;

    for (chanId = (int8_t)(pObj->nbChannels) - 1; chanId >= 0; chanId--)
    {
      /* Update channels first to minimize latency */
      if ((pObj->isPwmEnabled & (0x1U << (uint8_t)chanId)) != 0U)
      {
        ret = pObj->IO.WriteChan(&pObj->Pin, chanId, (pObj->nextChanEnBitmap & (0x1U << (uint8_t)chanId)));
        if (ret != IPS_DEVICE_OK)
        {
          status = IPS_DEVICE_ERROR;
        }
      }

      /* Then prepare next tick updates */
      if ((pObj->pwmTimTickCnt[chanId] == pObj->chanPwmTimActionTable[chanId]) || (pObj->forcePwmResync[chanId] != FALSE))
      {
        pObj->forcePwmResync[chanId] = FALSE;

        if ((pObj->isPwmEnabled & (0x1U << (uint8_t)chanId)) == 0U)
        {
          continue;
        }

        /* check if the channel has to be updated */
        if (pObj->pwmTimTickCnt[chanId] == pObj->chanPwmTimActionTable[chanId])
        {
          if (pObj->chanPwmTimPeriodHigh[chanId] == 0U)
          {
            /* clear the channel */
            newChanBitMap &= ~(0x1U <<(uint8_t)chanId);
          }
          else if (pObj->chanPwmTimPeriodLow[chanId] == 0U)
          {
            /* Set the channel */
            newChanBitMap |= (0x1U <<(uint8_t)chanId);
          }
          else
          {
            /* Toggle the channel */
            newChanBitMap ^= (0x1U <<(uint8_t)chanId);
          }
          /* Compute the tick of the next action on this channel */
          if ((newChanBitMap & (0x1U <<(uint8_t)chanId)) != 0U)
          {
            pObj->chanPwmTimActionTable[chanId] += pObj->chanPwmTimPeriodHigh[chanId];
          }
          else
          {
            pObj->chanPwmTimActionTable[chanId] += pObj->chanPwmTimPeriodLow[chanId];
          }
        }
      } /* end if prepare next tick update */

      /*  Increment tick */
      pObj->pwmTimTickCnt[chanId]++;
    } /* end for */

    pObj->nextChanEnBitmap = (newChanBitMap & pObj->isPwmEnabled);

#ifdef IPS_DEBUG
/*    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); */
#endif /* #ifdef IPS_DEBUG */
  }
  return (status);
}

/**
  * @brief  Get chip Id
  * @param  pObj pointer to the device object
  * @param  pId the WHO_AM_I value
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_ReadID(IPS8200HQ_1_Object_t *pObj, uint32_t *pId)
{
  *pId = pObj->chipId;
  return IPS_DEVICE_OK;
}

/**
  * @brief  Set the status of all channels via a bitmap
  * @param  pObj pointer to the device object
  * @param  ChanStatusBitmap the channel status bitmap to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetAllChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t ChanStatusBitmap)
{
  int32_t status = IPS_DEVICE_OK;
  int32_t ret;

  if (ChanStatusBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_DEVICE_ERROR;
  }
  else
  {
    int8_t loop;

    for (loop = (int8_t)pObj->nbChannels - 1; loop >= 0; loop--)
    {
      if ((pObj->isPwmEnabled & (0x1U << (uint8_t)loop)) != 0U)
      {
        /* Disable PWM for the channel if it was enabled */
        pObj->isPwmEnabled &= ~(0x1U << (uint8_t)loop);
      }

      /* If the PWM mode is disabled, directly set the channel */
      if ((ChanStatusBitmap & (0x1U << (uint8_t)loop)) != 0U)
      {
        pObj->ChanSteadyStateBitmap |= (0x1U << (uint8_t)loop);
      }
      else
      {
        pObj->ChanSteadyStateBitmap &= ~(0x1U << (uint8_t)loop);
      }
      ret = pObj->IO.WriteChan(&pObj->Pin, (uint8_t)loop, (ChanStatusBitmap >> (uint8_t)loop) & 0x1U);
      if (ret != IPS_DEVICE_OK)
      {
        status = IPS_DEVICE_ERROR;
      }
    }
  }

  return status;
}

/**
  * @brief  Set the duty cycle of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  ChanDc the channel duty cycle  to set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetChannelDc(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc)
{
  int32_t status = IPS_DEVICE_OK;
  if (ChanId < pObj->nbChannels)
  {
    uint8_t newDc;

    if (ChanDc > 100U)
    {
      newDc = 100U;
    }
    else
    {
      newDc = ChanDc;
    }

    if (pObj->channelDc[ChanId] != newDc)
    {
      pObj->channelDc[ChanId] = newDc;
      if (pObj->channelFreq[ChanId] != 0U)
      {
        uint32_t period = (uint32_t)(pObj->pwmFreq * 10U) / pObj->channelFreq[ChanId];
        pObj->chanPwmTimPeriodHigh[ChanId] = period * newDc / 100U;
        pObj->chanPwmTimPeriodLow[ChanId] = period - pObj->chanPwmTimPeriodHigh[ChanId];
      }
      else
      {
        if (newDc == 100U)
        {
          pObj->chanPwmTimPeriodHigh[ChanId] =  0xFFFFFFFFU;
        }
        else
        {
          pObj->chanPwmTimPeriodHigh[ChanId] = 0;
        }
        pObj->chanPwmTimPeriodLow[ChanId] = 0;
        /* Force recynchronisation after 1 second delay*/
        if (pObj->channelFreq[ChanId] == 0U)
        {
          pObj->chanPwmTimActionTable[ChanId] = pObj->pwmTimTickCnt[ChanId] + pObj->pwmFreq;
          pObj->forcePwmResync[ChanId] = TRUE;
        }
      }
    }
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  Set the frequency of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  ChanFreq the channel frequency in 1/10Hz (from 0 to 1000)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetChannelFreq(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq)
{
  int32_t status = IPS_DEVICE_OK;
  if (ChanId < pObj->nbChannels)
  {
    uint16_t newFreq;
    if (ChanFreq > IPS8200HQ_1_MAX_CHAN_FREQ)
    {
       newFreq = IPS8200HQ_1_MAX_CHAN_FREQ;
    }
    else
    {
      newFreq = ChanFreq;
    }
    if (pObj->channelFreq[ChanId] != newFreq)
    {
      if (newFreq != 0U)
      {
        uint32_t period = (uint32_t)pObj->pwmFreq * 10U / newFreq;
        pObj->chanPwmTimPeriodHigh[ChanId] = period * pObj->channelDc[ChanId] / 100U;
        pObj->chanPwmTimPeriodLow[ChanId] = period - pObj->chanPwmTimPeriodHigh[ChanId];
        /* If old frequency was 0, force recynchronisation after 1 period delay */
        if (pObj->channelFreq[ChanId] == 0U)
        {
          pObj->chanPwmTimActionTable[ChanId] = pObj->pwmTimTickCnt[ChanId] + period;
          pObj->forcePwmResync[ChanId] = TRUE;
        }
      }
      else
      {
        if (pObj->channelDc[ChanId] == 100U)
        {
          pObj->chanPwmTimPeriodHigh[ChanId] = 0xFFFFFFFFU;
        }
        else
        {
          pObj->chanPwmTimPeriodHigh[ChanId] = 0;
        }
        pObj->chanPwmTimPeriodLow[ChanId] = 0;
      }
      /* Update frequency */
      pObj->channelFreq[ChanId] = newFreq;
    }
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  Set the status of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  ChanStatus the channel status to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus)
{
  int32_t status = IPS_DEVICE_OK;
  int32_t ret;

  if (ChanId < pObj->nbChannels)
  {
    if ((pObj->isPwmEnabled & (0x1U << ChanId)) != 0U)
    {
      /* Disable PWM for the channel if it was enabled */
      pObj->isPwmEnabled &= ~(0x1U << ChanId);
    }

    if (ChanStatus != 0U)
    {
      pObj->ChanSteadyStateBitmap |= (0x1U << ChanId);
    }
    else
    {
      pObj->ChanSteadyStateBitmap &= ~(0x1U << ChanId);
    }
    ret = pObj->IO.WriteChan(&pObj->Pin, ChanId, ChanStatus);
    if (ret != IPS_DEVICE_OK)
    {
      status = IPS_DEVICE_ERROR;
    }
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  Set the status of a control pin
  * @param  pObj pointer to the device object
  * @param  CtrlPinId Control Pin Id
  * @param  CtrlPinStatus Control pin status to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetCtrlPinStatus(IPS8200HQ_1_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
{
  int32_t status;

  if ((CtrlPinId >= pObj->firstCtrl) && (CtrlPinId < (pObj->firstCtrl + pObj->nbCtrls)))
  {
    if (CtrlPinStatus != 0U)
    {
        pObj->ControlPinsBitmap |= (0x1U << (CtrlPinId - pObj->firstCtrl));
    }
    else
    {
        pObj->ControlPinsBitmap &= ~(0x1U << (CtrlPinId - pObj->firstCtrl));
    }
    status = pObj->IO.WritePin(&pObj->Pin, CtrlPinId, CtrlPinStatus);
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  Set the PWM enable state
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  EnablePwm PWM enable state to set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetPwmEnable(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t EnablePwm)
{
  int32_t status = IPS_DEVICE_OK;

  if (ChanId < pObj->nbChannels)
  {
    /* Disable PWM timer to prevent concurrent access via the tick update */
    pObj->isPwmEnabled &= ~(0x1U << ChanId);
    pObj->IO.SetPwm(0U);
#ifdef IPS_DEBUG
/*    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); */
#endif /* #ifdef IPS_DEBUG */

    if (EnablePwm == 0U)
    {
      status = pObj->IO.WriteChan(&pObj->Pin, ChanId, EnablePwm);
      pObj->nextChanEnBitmap &= ~(0x1U << ChanId);
    }

    pObj->chanPwmTimActionTable[ChanId] = 0U;
    pObj->pwmTimTickCnt[ChanId] = 0U;

    if (EnablePwm != 0U)
    {
      pObj->isPwmEnabled |= (0x1U << ChanId);
      pObj->ChanSteadyStateBitmap &= ~(0x1U << ChanId);
    }
    else
    {
      pObj->isPwmEnabled &= ~(0x1U << ChanId);
    }
    if (pObj->isPwmEnabled != 0U)
    {
      Device_System_PWMEnable_bitmap |= (0x1U << pObj->Instance);
    }
    else
    {
      Device_System_PWMEnable_bitmap &= ~(0x1U << pObj->Instance);
    }
    pObj->IO.SetPwm(Device_System_PWMEnable_bitmap);
#ifdef IPS_DEBUG
/*
    if (Device_System_PWMEnable_bitmap != 0U)
    {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    }
*/
#endif /* #ifdef IPS_DEBUG */
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  Initialize the IPS8200HQ-1 switch
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
static int32_t IPS8200HQ_1_Initialize(IPS8200HQ_1_Object_t *pObj)
{
  int32_t ret;

  ret = IPS_DEVICE_OK;
  /* Power off the component. */
  if (IPS8200HQ_1_SetAllChannelStatus(pObj, 0U) != IPS_DEVICE_OK)
  {
    ret = IPS_DEVICE_ERROR;
  }
  return ret;
}
#endif /* #ifdef APP_PAR_IFC */

#ifdef APP_SPI_IFC
/**
  * @brief  Register Component Bus IO operations
  * @param  pObj pointer to the device object
  * @param  pIO  pointer to the IO functions structure
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_RegisterBusIO(IPS8200HQ_1_Object_t *pObj, IPS8200HQ_1_IO_t *pIO)
{
  int32_t ret;

  if (pObj == NULL)
  {
    ret = IPS_DEVICE_ERROR;
  }
  else
  {
    pObj->IO.Init             = pIO->Init;
    pObj->IO.DeInit           = pIO->DeInit;
    pObj->IO.GetTick          = pIO->GetTick;
    pObj->IO.SpiWrite         = pIO->SpiWrite;
    pObj->IO.ReadFault        = pIO->ReadFault;
    pObj->IO.WritePin         = pIO->WritePin;
    pObj->IO.ReadPin          = pIO->ReadPin;
    pObj->IO.SetPwm           = pIO->SetPwm;
    pObj->IO.StartGuardTimer  = pIO->StartGuardTimer;
    pObj->IO.StopGuardTimer   = pIO->StopGuardTimer;
    pObj->IO.EnableIrq        = pIO->EnableIrq;
    pObj->IO.DisableIrq       = pIO->DisableIrq;

    if (pObj->IO.Init != NULL)
    {
      ret = pObj->IO.Init();
    }
    else
    {
      ret = IPS_DEVICE_ERROR;
    }
  }
  return ret;
}

/**
  * @brief  Initialize the IPS8200HQ-1 relay
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_Init(IPS8200HQ_1_Object_t *pObj)
{
  int32_t status = IPS_DEVICE_OK;

  if (pObj->is_initialized == 0U)
  {
    if (IPS8200HQ_1_Initialize(pObj) != IPS_DEVICE_OK)
    {
      status = IPS_DEVICE_ERROR;
    }
    else
    {
      IPS_NbInstances++;
      if (IPS_NbInstances > IPS8200HQ_1_INSTANCES_NBR)
      {
        status = IPS_DEVICE_ERROR;
      }
      else
      {
        pObj->is_initialized = 1;
      }
    }
  }
  return status;
}

/**
  * @brief  Deinitialize the IPS8200HQ-1 relay
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_DeInit(IPS8200HQ_1_Object_t *pObj)
{
  if (pObj->is_initialized == 1U)
  {
    /* Disable PWM */
    pObj->isPwmEnabled = 0;

     /* Disable all channels */
    (void)IPS8200HQ_1_SetAllChannelStatus(pObj, 0U);

    IPS_NbInstances--;
  }

  pObj->is_initialized = 0;

  return IPS_DEVICE_OK;
}

/**
  * @brief  Get the status of the specified channel
  * @param  pObj pointer to the device object
  * @param  pChanStatusBitmap pointer to the channel status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetAllChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t* pChanStatusBitmap)
{
  int32_t status = IPS_DEVICE_OK;
  *pChanStatusBitmap = pObj->ChanSteadyStateBitmap;
  return status;
}

/**
  * @brief  Get IPS8200HQ-1 relay capabilities
  * @param  pObj pointer to the device object
  * @param  pCapabilities pointer to the capabilities
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetCapabilities(IPS8200HQ_1_Object_t *pObj, IPS8200HQ_1_Capabilities_t *pCapabilities)
{
  int32_t status = IPS_DEVICE_OK;

  if (pObj->chipId == IPS8200HQ_1_CHIP_ID)
  {
    pCapabilities->nbChannels = IPS8200HQ_1_MAX_NB_CHANNELS;
    switch(pObj->Instance)
    {
      case 0U:
        pCapabilities->firstCtrlPin = IPS8200HQ_1_0_FIRST_CONTROL;
        break;

      case 1U:
        pCapabilities->firstCtrlPin = IPS8200HQ_1_1_FIRST_CONTROL;
        break;

      default:
        status = IPS_DEVICE_ERROR;
        break;
    }
    pCapabilities->nbCtrlPins = IPS8200HQ_1_MAX_NB_CONTROLS;
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }

  return status;
}

/**
  * @brief  Get the status of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  pChanStatus pointer to the channel status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t status = IPS_DEVICE_OK;

  if (ChanId < pObj->nbChannels)
  {
    *pChanStatus = (pObj->ChanSteadyStateBitmap >> ChanId) & 0x1U;
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  Get the status of a control pin
  * @param  pObj pointer to the device object
  * @param  CtrlPinId Control Pin Id
  * @param  pCtrlPinStatus Pointer to the Control Pin Status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetCtrlPinStatus(IPS8200HQ_1_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus)
{
  int32_t status;
  uint8_t pinState = 0;

  if ((CtrlPinId >= pObj->firstCtrl) && (CtrlPinId < (pObj->firstCtrl + pObj->nbCtrls)))
  {
    status = pObj->IO.ReadPin(&pObj->Pin, CtrlPinId - pObj->firstCtrl, &pinState);
    if (pinState != 0U)
    {
        pObj->ControlPinsBitmap |= (0x1U << (CtrlPinId - pObj->firstCtrl));
    }
    else
    {
        pObj->ControlPinsBitmap &= ~(0x1U << (CtrlPinId - pObj->firstCtrl));
    }
    *pCtrlPinStatus = (pObj->ControlPinsBitmap >> (CtrlPinId - pObj->firstCtrl)) & 0x1U;
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  Get the fault status
  * @param  pObj pointer to the device object
  * @param  pFaultStatus pointer to the fault status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetFaultStatus(IPS8200HQ_1_Object_t *pObj, uint8_t *pFaultStatus)
{
  int32_t status;
  status = pObj->IO.ReadFault(&pObj->Pin, pFaultStatus);
  return status;
}

/**
  * @brief  Get chip Id
  * @param  pObj pointer to the device object
  * @param  pId the WHO_AM_I value
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_ReadID(IPS8200HQ_1_Object_t *pObj, uint32_t *pId)
{
  *pId = pObj->chipId;
  return IPS_DEVICE_OK;
}

/**
  * @brief  Calculate checksum to be sent from master to slave as LSByte in case of SPI 16 bit setting
  * @param  dataBitmap Data to be checksum'ed
  * @param  cksum pointer to the calculated checksum value
  * @retval 0 in case of success, an error code otherwise
  */
void CalcChecksum(uint8_t dataBitmap, uint8_t *cksum)
{
  uint8_t loop;
  uint8_t tmpVal;

  *cksum = 0U;
  tmpVal = 0U;

  /* P0 and nP0 */
  for (loop = 0U; loop < IPS8200HQ_1_MAX_NB_CHANNELS; loop++)
  {
    tmpVal ^= ((dataBitmap >> loop) & 0x1U);
  }
  *cksum ^= (~tmpVal) & 0x1U;
  *cksum ^= ((tmpVal & 0x1U) << 1U);
  /* P1 */
  tmpVal = 0U;
  for (loop = 1U; loop < IPS8200HQ_1_MAX_NB_CHANNELS; loop = loop + 2)
  {
    tmpVal ^= ((dataBitmap >> loop) & 0x1U);
  }
  *cksum ^= ((tmpVal & 0x1U) << 2U);
  /* P2 */
  tmpVal = 0U;
  for (loop = 0U; loop < IPS8200HQ_1_MAX_NB_CHANNELS; loop = loop + 2)
  {
    tmpVal ^= ((dataBitmap >> loop) & 0x1U);
  }
  *cksum ^= ((tmpVal & 0x1U) << 3U);
}

/**
  * @brief  Get the fault register for all input channels of a single board
  * @param  pObj pointer to the device object
  * @param  pFaultRegister pointer to the Fault Register value (SPI 8bit: 1 byte, SPI 16bit: 2 bytes)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetFaultRegister(IPS8200HQ_1_Object_t *pObj, uint16_t *pFaultRegister)
{
  int32_t status = IPS_DEVICE_OK;
  uint8_t itDisable = FALSE;
  uint8_t SpiTxRxBytes;
  uint8_t checksum;

  *pFaultRegister = 0xFFFFU;
  if (pObj->isPwmEnabled == 0U)
  {
    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      SpiTxRxBytes = 1U;
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      SpiTxRxBytes = 2U;
    }
    else
    {
      SpiTxRxBytes = 0U;
      status = IPS_DEVICE_ERROR;
    }
    
    if (status == IPS_DEVICE_OK)
    {
      do
      {
        spiPreemptionByIsr = FALSE;
        if (itDisable != FALSE)
        {
          /* re-enable Irq if disabled in previous iteration */
          pObj->IO.EnableIrq();
          itDisable = FALSE;
        }

        if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
        {
          aSpiTxBuffer[0] = pObj->ChanSteadyStateBitmap;
        }
        else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
        {
          aSpiTxBuffer[0] = pObj->ChanSteadyStateBitmap;
          CalcChecksum(aSpiTxBuffer[0], &checksum);
          aSpiTxBuffer[1] = checksum;
        }

        /* Wait for the SPI lock time is elapsed before sending a new request */
        while (spiLockTime > 0)
        {
        }

        /* Disable interruption before checking */
        /* pre-emption by ISR and SPI transfers */
        pObj->IO.DisableIrq();
        itDisable = TRUE;
      } while (spiPreemptionByIsr != FALSE); /* check pre-emption by ISR */

      status = IPS8200HQ_1_WriteBytes(pObj, &aSpiTxBuffer[0], &aSpiRxBuffer[0], SpiTxRxBytes);
      if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
      {
        *pFaultRegister = (uint16_t)aSpiRxBuffer[0];
      }
      else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
      {
        *pFaultRegister = (uint16_t)aSpiRxBuffer[1];
        *pFaultRegister |= (uint16_t)((uint16_t)(aSpiRxBuffer[0]) << 8U);
      }

      /* re-enable Irq after SPI transfers */
      pObj->IO.EnableIrq();
    }
  }
  else
  {
    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      *pFaultRegister = (uint16_t)aSpiRxBuffer[0];
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      *pFaultRegister = (uint16_t)aSpiRxBuffer[1];
      *pFaultRegister |= (uint16_t)((uint16_t)(aSpiRxBuffer[0]) << 8U);
    }
  }

  return status;
}

/**
  * @brief  Get the fault register for all input channels of two boards connected in Daisy Chain
  * @param  pFaultRegister pointer to the Fault Register value (2 bytes)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetFaultRegister_DaisyChain(uint32_t *pFaultRegister)
{
  int32_t status = IPS_DEVICE_OK;
  uint8_t itDisable = FALSE;
  IPS8200HQ_1_Object_t *pObj;
  uint8_t SpiTxRxBytes;
  uint8_t Instance;
  uint32_t FaultRegVal;
  uint8_t checksum;
  uint8_t PwmRunningFlag = 0U;

  *pFaultRegister = 0xFFFFFFFFU;
  if (queuedBitmap != FALSE)
  {
    status = IPS_DEVICE_ERROR;
  }

  if (status == IPS_DEVICE_OK)
  {
    /* If at least one of the two boards is in PWM, return FAIL status */
    for (Instance=0; Instance < IPS8200HQ_1_SPI_DC_INSTANCES_NBR; Instance++)
    {
      pObj = (IPS8200HQ_1_Object_t*)RELAY_CompObj[Instance];

      if (pObj->isPwmEnabled != 0U)
      {
        PwmRunningFlag = 1U;
      }
    }
  }

  if (PwmRunningFlag == 0U)
  {
    if (queuedBitmap != FALSE)
    {
      status = IPS_DEVICE_ERROR;
    }
    else
    {
      if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
      {
        /* Load SPI Tx Buffer with 2-bytes data to be written */
        for (Instance=0; Instance < IPS8200HQ_1_SPI_DC_INSTANCES_NBR; Instance++)
        {
          pObj = (IPS8200HQ_1_Object_t*)RELAY_CompObj[Instance];
          aSpiTxBuffer[IPS8200HQ_1_SPI_DC_INSTANCES_NBR - 1U - Instance] = pObj->ChanSteadyStateBitmap;
        }
        SpiTxRxBytes = 2U;
      }
      else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
      {
        /* Load SPI Tx Buffer with 4-bytes data to be written */
        for (Instance=0; Instance < IPS8200HQ_1_SPI_DC_INSTANCES_NBR; Instance++)
        {
          pObj = (IPS8200HQ_1_Object_t*)RELAY_CompObj[Instance];
          aSpiTxBuffer[2U - 2U * Instance] = pObj->ChanSteadyStateBitmap;
          CalcChecksum(aSpiTxBuffer[2U - 2U * Instance], &checksum);
          aSpiTxBuffer[3U - 2U * Instance] = checksum;
        }
        SpiTxRxBytes = 4U;
      }
      else
      {
        SpiTxRxBytes = 0U;
        status = IPS_DEVICE_ERROR;
      }

      if (status == IPS_DEVICE_OK)
      {
        pObj = (IPS8200HQ_1_Object_t*)RELAY_CompObj[0];
        do
        {
          spiPreemptionByIsr = FALSE;
          if (itDisable != FALSE)
          {
            /* re-enable Irq if disabled in previous iteration */
            pObj->IO.EnableIrq();
            itDisable = FALSE;
          }

          /* Wait for the SPI lock time is elapsed before sending a new request */
          while (spiLockTime > 0)
          {
          }

          /* Disable interruption before checking */
          /* pre-emption by ISR and SPI transfers */
          pObj->IO.DisableIrq();
          itDisable = TRUE;
        } while (spiPreemptionByIsr != FALSE); /* check pre-emption by ISR */

        status = IPS8200HQ_1_WriteBytes(pObj, &aSpiTxBuffer[0], &aSpiRxBuffer[0], SpiTxRxBytes);

        FaultRegVal = 0U;
        if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
        {
          /* Get 2-bytes Fault Register data from SPI Rx Buffer   */
          /* aSpiRxBuffer[0] -> FaultRegVal[1] Fault Reg Board 1  */
          /* aSpiRxBuffer[1] -> FaultRegVal[0] Fault Reg Board 0  */
          for (Instance=0; Instance < IPS8200HQ_1_SPI_DC_INSTANCES_NBR; Instance++)
          {
            FaultRegVal |= ((uint16_t)(aSpiRxBuffer[IPS8200HQ_1_SPI_DC_INSTANCES_NBR - 1U - Instance]) << (8U*Instance));
          }
        }
        else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
        {
          /* Get 4-bytes Fault Register data from SPI DC Rx Buffer */
          /* aSpiRxBuffer[0] -> FaultRegVal[3] Fault Reg Board 1   */
          /* aSpiRxBuffer[1] -> FaultRegVal[2] Parity Board 1      */
          /* aSpiRxBuffer[2] -> FaultRegVal[1] Fault Reg Board 0   */
          /* aSpiRxBuffer[3] -> FaultRegVal[0] Parity Board 0      */
          for (Instance=0; Instance < IPS8200HQ_1_SPI_DC_INSTANCES_NBR; Instance++)
          {
            FaultRegVal |= ((uint32_t)((uint32_t)aSpiRxBuffer[3U - 2U * Instance]) << (8U*(2U * Instance)));
            FaultRegVal |= ((uint32_t)((uint32_t)aSpiRxBuffer[2U - 2U * Instance]) << (8U*(2U * Instance + 1U)));
          }
        }
        *pFaultRegister = FaultRegVal;

        /* re-enable Irq after SPI transfers */
        pObj->IO.EnableIrq();
      }
    }
  }
  else
  {
    FaultRegVal = 0U;
    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      /* Get 2-bytes Fault Register data from SPI Rx Buffer */
      for (Instance=0; Instance < IPS8200HQ_1_SPI_DC_INSTANCES_NBR; Instance++)
      {
        FaultRegVal |= ((uint16_t)(aSpiRxBuffer[IPS8200HQ_1_SPI_DC_INSTANCES_NBR - 1U - Instance]) << (8U*Instance));
      }
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      /* Get 4-bytes Fault Register data from SPI DC Rx Buffer */
      for (Instance=0; Instance < IPS8200HQ_1_SPI_DC_INSTANCES_NBR; Instance++)
      {
        FaultRegVal |= ((uint32_t)((uint32_t)aSpiRxBuffer[3U - 2U * Instance]) << (8U*(2U * Instance)));
        FaultRegVal |= ((uint32_t)((uint32_t)aSpiRxBuffer[2U - 2U * Instance]) << (8U*(2U * Instance + 1U)));
      }
    }
    *pFaultRegister = FaultRegVal;
  }

  return status;
}

/**
  * @brief  Get the duty cycle of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  pChanDc pointer to the channel duty cycle
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetChannelDc(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t status = IPS_DEVICE_OK;
  if (ChanId < pObj->nbChannels)
  {
    *pChanDc = pObj->channelDc[ChanId];
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  Get the frequency of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  pChanFreq pointer to the channel frequency in in 1/10Hz (from 0 to 1000)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetChannelFreq(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t status = IPS_DEVICE_OK;
  if (ChanId < pObj->nbChannels)
  {
    *pChanFreq = pObj->channelFreq[ChanId];
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  Get the PWM enable state
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  pPwmEnabled pointer to the PWM enable state
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetPwmEnable(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled)
{
  int32_t status = IPS_DEVICE_OK;

  if (ChanId < pObj->nbChannels)
  {
    *pPwmEnabled = ((pObj->isPwmEnabled >> ChanId) & 0x1U);
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  Set the duty cycle of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  ChanDc the channel duty cycle  to set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetChannelDc(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc)
{
  int32_t status = IPS_DEVICE_OK;
  if (ChanId < pObj->nbChannels)
  {
    uint8_t newDc;

    if (ChanDc > 100U)
    {
      newDc = 100U;
    }
    else
    {
      newDc = ChanDc;
    }

    if (pObj->channelDc[ChanId] != newDc)
    {
      pObj->channelDc[ChanId] = newDc;
      if (pObj->channelFreq[ChanId] != 0U)
      {
        uint32_t period = (uint32_t)(pObj->pwmFreq * 10U) / pObj->channelFreq[ChanId];
        pObj->chanPwmTimPeriodHigh[ChanId] = period * newDc / 100U;
        pObj->chanPwmTimPeriodLow[ChanId] = period - pObj->chanPwmTimPeriodHigh[ChanId];
      }
      else
      {
        if (newDc == 100U)
        {
          pObj->chanPwmTimPeriodHigh[ChanId] =  0xFFFFFFFFU;
        }
        else
        {
          pObj->chanPwmTimPeriodHigh[ChanId] = 0;
        }
        pObj->chanPwmTimPeriodLow[ChanId] = 0;
        /* Force recynchronisation after 1 second delay*/
        if (pObj->channelFreq[ChanId] == 0U)
        {
          pObj->chanPwmTimActionTable[ChanId] = pObj->pwmTimTickCnt[ChanId] + pObj->pwmFreq;
          pObj->forcePwmResync[ChanId] = TRUE;
        }
      }
    }
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  Set the frequency of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  ChanFreq the channel frequency in 1/10Hz (from 0 to 1000)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetChannelFreq(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq)
{
  int32_t status = IPS_DEVICE_OK;
  if (ChanId < pObj->nbChannels)
  {
    uint16_t newFreq;
    if (ChanFreq > IPS8200HQ_1_MAX_CHAN_FREQ)
    {
       newFreq = IPS8200HQ_1_MAX_CHAN_FREQ;
    }
    else
    {
      newFreq = ChanFreq;
    }
    if (pObj->channelFreq[ChanId] != newFreq)
    {
      if (newFreq != 0U)
      {
        uint32_t period = (uint32_t)pObj->pwmFreq * 10U / newFreq;
        pObj->chanPwmTimPeriodHigh[ChanId] = period * pObj->channelDc[ChanId] / 100U;
        pObj->chanPwmTimPeriodLow[ChanId] = period - pObj->chanPwmTimPeriodHigh[ChanId];
        /* If old frequency was 0, force recynchronisation after 1 period delay */
        if (pObj->channelFreq[ChanId] == 0U)
        {
          pObj->chanPwmTimActionTable[ChanId] = pObj->pwmTimTickCnt[ChanId] + period;
          pObj->forcePwmResync[ChanId] = TRUE;
        }
      }
      else
      {
        if (pObj->channelDc[ChanId] == 100U)
        {
          pObj->chanPwmTimPeriodHigh[ChanId] = 0xFFFFFFFFU;
        }
        else
        {
          pObj->chanPwmTimPeriodHigh[ChanId] = 0;
        }
        pObj->chanPwmTimPeriodLow[ChanId] = 0;
      }
      /* Update frequency */
      pObj->channelFreq[ChanId] = newFreq;
    }
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return (status);
}

/**
  * @brief  Set the PWM enable state
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  EnablePwm PWM enable state to set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetPwmEnable(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t EnablePwm)
{
  int32_t status;

  status = IPS_DEVICE_OK;
  if (ChanId < pObj->nbChannels)
  {
    /* Disable PWM timer to prevent concurrent access via the tick update */
    pObj->isPwmEnabled &= ~(0x1U << ChanId);
    pObj->IO.SetPwm(0U);

    if (EnablePwm == 0U)
    {
        pObj->nextChanEnBitmap &= ~(0x1U << ChanId);
    }

    pObj->chanPwmTimActionTable[ChanId] = 0;
    pObj->pwmTimTickCnt[ChanId] = 0;

    if (EnablePwm != 0U)
    {
        pObj->isPwmEnabled |= (0x1U << ChanId);
        pObj->ChanSteadyStateBitmap &= ~(0x1U << ChanId);
        pObj->ChanSteadyStatePwmBitmap &= ~(0x1U << ChanId);
    }
    else
    {
        pObj->isPwmEnabled &= ~(0x1U << ChanId);
    }
    if (pObj->isPwmEnabled != 0U)
    {
      Device_System_PWMEnable_bitmap |= (0x1U << pObj->Instance);
    }
    else
    {
      Device_System_PWMEnable_bitmap &= ~(0x1U << pObj->Instance);
    }
    pObj->IO.SetPwm(Device_System_PWMEnable_bitmap);
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  PWM tick
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_PwmTick(IPS8200HQ_1_Object_t *pObj)
{
  int32_t status = IPS_DEVICE_OK;

#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); */
#endif /* #ifdef IPS_DEBUG */
  if (pObj->isPwmEnabled != 0U)
  {
    int8_t chanId;
    uint8_t newChanBitMap;

    /* Set isr flag */
    isrFlag = TRUE;

    /*  Update channels first to minimize latency */
    pObj->chanEnBitmap = pObj->nextChanEnBitmap;

    /*  Load the current bitmap of the corresponding device */
    newChanBitMap =  pObj->chanEnBitmap;

    /*  Update channels first to minimize latency */
    status = IPS8200HQ_1_SetAllChannelPwmStatus(pObj,  pObj->nextChanEnBitmap | pObj->ChanSteadyStateBitmap);
    for (chanId = (int8_t)(pObj->nbChannels) - 1; chanId >= 0; chanId--)
    {
      /* Then prepare next tick updates */
      if ((pObj->pwmTimTickCnt[chanId] == pObj->chanPwmTimActionTable[chanId]) || (pObj->forcePwmResync[chanId] != FALSE))
      {
        pObj->forcePwmResync[chanId] = FALSE;

        if ((pObj->isPwmEnabled & (0x1U << (uint8_t)chanId)) == 0U)
        {
            continue;
        }

        /* check if the channel has to be updated */
        if (pObj->pwmTimTickCnt[chanId] == pObj->chanPwmTimActionTable[chanId])
        {
          if (pObj->chanPwmTimPeriodHigh[chanId] == 0U)
          {
            /* clear the channel */
            newChanBitMap &= ~(0x1U <<(uint8_t)chanId);
          }
          else if (pObj->chanPwmTimPeriodLow[chanId] == 0U)
          {
            /* Set the channel */
            newChanBitMap |= (0x1U <<(uint8_t)chanId);
          }
          else
          {
            /* Toggle the channel */
            newChanBitMap ^= (0x1U <<(uint8_t)chanId);
          }
          /* Compute the tick of the next action on this channel */
          if ((newChanBitMap & (0x1U <<(uint8_t)chanId)) != 0U)
          {
            pObj->chanPwmTimActionTable[chanId] += pObj->chanPwmTimPeriodHigh[chanId];
          }
          else
          {
            pObj->chanPwmTimActionTable[chanId] += pObj->chanPwmTimPeriodLow[chanId];
          }
        }
      } /* end if prepare next tick update */

      /*  Increment tick */
      pObj->pwmTimTickCnt[chanId]++;
    } /* end for */

    pObj->nextChanEnBitmap = (newChanBitMap & pObj->isPwmEnabled);

    /* Reset isr flag */
    isrFlag = FALSE;
  }
#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); */
#endif /* #ifdef IPS_DEBUG */
  return status;
}

/**
  * @brief  PWM tick for Daisy Chain conf
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_PwmTick_DaisyChain(void)
{
  int32_t status = IPS_DEVICE_OK;

#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); */
#endif /* #ifdef IPS_DEBUG */

  if (Device_System_PWMEnable_bitmap != 0U)
  {
    uint8_t Instance;
    uint8_t newChanBitMap;
    IPS8200HQ_1_Object_t *pObj;

    /* Set isr flag */
    isrFlag = TRUE;

    /*  Update channels first to minimize latency */
    (void)IPS8200HQ_1_SendQueuedPwmChannelStatus();

    for (Instance=0; Instance < IPS8200HQ_1_SPI_DC_INSTANCES_NBR; Instance++)
    {
      pObj = (IPS8200HQ_1_Object_t*)RELAY_CompObj[Instance];
      if (pObj->isPwmEnabled != 0U)
      {
        int8_t chanId;

        /*  Update channels first to minimize latency */
        pObj->chanEnBitmap = pObj->nextChanEnBitmap;

        /*  Load the current bitmap of the corresponding device */
        newChanBitMap =  pObj->chanEnBitmap;

        for (chanId = (int8_t)(pObj->nbChannels) - 1; chanId >= 0; chanId--)
        {
          /* Then prepare next tick updates */
          if ((pObj->pwmTimTickCnt[chanId] == pObj->chanPwmTimActionTable[chanId]) || (pObj->forcePwmResync[chanId] != FALSE))
          {
            pObj->forcePwmResync[chanId] = FALSE;

            if ((pObj->isPwmEnabled & (0x1U << (uint8_t)chanId)) == 0U)
            {
                continue;
            }

            /* check if the channel has to be updated */
            if (pObj->pwmTimTickCnt[chanId] == pObj->chanPwmTimActionTable[chanId])
            {
              if (pObj->chanPwmTimPeriodHigh[chanId] == 0U)
              {
                /* clear the channel */
                newChanBitMap &= ~(0x1U <<(uint8_t)chanId);
              }
              else if (pObj->chanPwmTimPeriodLow[chanId] == 0U)
              {
                /* Set the channel */
                newChanBitMap |= (0x1U <<(uint8_t)chanId);
              }
              else
              {
                /* Toggle the channel */
                newChanBitMap ^= (0x1U <<(uint8_t)chanId);
              }
              /* Compute the tick of the next action on this channel */
              if ((newChanBitMap & (0x1U <<(uint8_t)chanId)) != 0U)
              {
                pObj->chanPwmTimActionTable[chanId] += pObj->chanPwmTimPeriodHigh[chanId];
              }
              else
              {
                pObj->chanPwmTimActionTable[chanId] += pObj->chanPwmTimPeriodLow[chanId];
              }
            }
          } /* end if prepare next tick update */

          /*  Increment tick */
          pObj->pwmTimTickCnt[chanId]++;
        } /* end for */

        pObj->nextChanEnBitmap = (newChanBitMap & pObj->isPwmEnabled);
        if (pObj->newChanSteadyStateBitmap == FALSE)
        {
          status = IPS8200HQ_1_QueueAllChannelPwmStatus(pObj, pObj->nextChanEnBitmap);
        }
        else
        {
          status = IPS8200HQ_1_QueueAllChannelPwmStatus(pObj, pObj->nextChanEnBitmap | pObj->ChanSteadyStatePwmBitmap);
        }
      }
      else
      {
        status = IPS8200HQ_1_QueueAllChannelPwmStatus(pObj, pObj->ChanSteadyStatePwmBitmap);
      }
    }

    /* Reset isr flag */
    isrFlag = FALSE;
  }
#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); */
#endif /* #ifdef IPS_DEBUG */
  return status;
}

/**
  * @brief  Guard Timer tick for SPI conf
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GuardTimerTick(IPS8200HQ_1_Object_t *pObj)
{
  int32_t status = IPS_DEVICE_OK;

#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); */
#endif /* #ifdef IPS_DEBUG */

  if (spiLockTime > 0)
  {
    spiLockTime -= (int16_t)(IPS8200HQ_1_GUARD_TIMER_TICK_IN_US);
  }
  else
  {
    status = pObj->IO.StopGuardTimer();
  }

#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); */
#endif /* #ifdef IPS_DEBUG */
  return status;
}

/**
  * @brief  Watchdog Timer tick for SPI conf
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_WatchdogTimerTick(IPS8200HQ_1_Object_t *pObj)
{
  int32_t status = IPS_DEVICE_OK;
  int32_t ret;
  uint8_t Instance;

#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); */
#endif /* #ifdef IPS_DEBUG */
  Instance = pObj->Instance;
  if (Device_System_WdMode[Instance] == 1U)
  {
    if (watchdogTime > 0)
    {
      watchdogTime -= (int32_t)(IPS8200HQ_1_WATCHDOG_TIMER_TICK_IN_US);
      ret = IPS8200HQ_1_SetCtrlPinStatus(pObj, IPS8200HQ_1_0_WD, 1U);
      if (ret != IPS_DEVICE_OK)
      {
        status = IPS_DEVICE_ERROR;
      }
    }
    else
    {
      if (watchdogHoldTime > 0)
      {
        watchdogHoldTime -= (int32_t)(IPS8200HQ_1_WATCHDOG_TIMER_TICK_IN_US);
        ret = IPS8200HQ_1_SetCtrlPinStatus(pObj, IPS8200HQ_1_0_WD, 0U);
        if (ret != IPS_DEVICE_OK)
        {
          status = IPS_DEVICE_ERROR;
        }
      }
      else
      {
        watchdogTime = (int32_t)pObj->timingTwm;
        watchdogHoldTime = (int32_t)pObj->timingTwd;
        ret = IPS8200HQ_1_SetCtrlPinStatus(pObj, IPS8200HQ_1_0_WD, 1U);
        if (ret != IPS_DEVICE_OK)
        {
          status = IPS_DEVICE_ERROR;
        }
      }
    }
  }
#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); */
#endif /* #ifdef IPS_DEBUG */

  return status;
}

/**
  * @brief  Guard Timer tick for Daisy Chain conf
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GuardTimerTick_DaisyChain(void)
{
  int32_t status = IPS_DEVICE_OK;

#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); */
#endif /* #ifdef IPS_DEBUG */

  if (spiLockTime > 0)
  {
    spiLockTime -= (int16_t)(IPS8200HQ_1_GUARD_TIMER_TICK_IN_US);
  }
  else
  {
    IPS8200HQ_1_Object_t *pObj;

    pObj = (IPS8200HQ_1_Object_t*)RELAY_CompObj[0];
    status = pObj->IO.StopGuardTimer();
  }

#ifdef IPS_DEBUG
/*  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); */
#endif /* #ifdef IPS_DEBUG */
  return status;
}

/**
  * @brief  Set the status of a control pin
  * @param  pObj pointer to the device object
  * @param  CtrlPinId Control Pin Id
  * @param  CtrlPinStatus Control pin status to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetCtrlPinStatus(IPS8200HQ_1_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
{
  int32_t status;

  if ((CtrlPinId >= pObj->firstCtrl) && (CtrlPinId < (pObj->firstCtrl + pObj->nbCtrls)))
  {
    if (CtrlPinStatus != 0U)
    {
        pObj->ControlPinsBitmap |= (0x1U << (CtrlPinId - pObj->firstCtrl));
    }
    else
    {
        pObj->ControlPinsBitmap &= ~(0x1U << (CtrlPinId - pObj->firstCtrl));
    }
    status = pObj->IO.WritePin(&pObj->Pin, CtrlPinId, CtrlPinStatus);
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  Set the status of all channels for PWM via a bitmap
  * @param  pObj pointer to the device object
  * @param  ChanStatusBitmap the channel status bitmap to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetAllChannelPwmStatus(IPS8200HQ_1_Object_t *pObj, uint8_t ChanStatusBitmap)
{
  int32_t status = IPS_DEVICE_OK;
  uint8_t SpiTxRxBytes;
  uint8_t checksum;

  if (ChanStatusBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_DEVICE_ERROR;
  }
  else
  {
    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      SpiTxRxBytes = 1U;
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      SpiTxRxBytes = 2U;
    }
    else
    {
      SpiTxRxBytes = 0U;
      status = IPS_DEVICE_ERROR;
    }

    if (status == IPS_DEVICE_OK)
    {
      if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
      {
        aSpiTxBuffer[0] = ChanStatusBitmap;
      }
      else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
      {
        aSpiTxBuffer[0] = ChanStatusBitmap;
        CalcChecksum(aSpiTxBuffer[0], &checksum);
        aSpiTxBuffer[1] = checksum;
      }

      status = pObj->IO.SpiWrite(0U, &aSpiTxBuffer[0], &aSpiRxBuffer[0], SpiTxRxBytes);
    }
  }

  return status;
}

/**
  * @brief  Set the status of the specified channel
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  ChanStatus the channel status to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus)
{
  int32_t status;

  if (ChanId < pObj->nbChannels)
  {
    /* Disable PWM for the selected channel */
    if ((pObj->isPwmEnabled & (0x1U << ChanId)) != 0U)
    {
        /* Disable PWM for the channel if it was enabled */
        pObj->isPwmEnabled &= ~(0x1U << ChanId);
    }
    /* Update Steady State Bitmap for the selected channel */
    if (ChanStatus != 0U)
    {
        pObj->ChanSteadyStateBitmap |= (0x1U << ChanId);
    }
    else
    {
        pObj->ChanSteadyStateBitmap &= ~(0x1U << ChanId);
    }

    /* If other channels are in PWM, we must use the PWM version of Set All Channel Status */
    if (pObj->isPwmEnabled != 0U)
    {
      status = IPS8200HQ_1_SetAllChannelPwmStatus(pObj,  pObj->ChanSteadyStateBitmap);
    }
    else
    {
      status = IPS8200HQ_1_SetAllChannelStatus(pObj,  pObj->ChanSteadyStateBitmap);
    }
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }
  return status;
}

/**
  * @brief  Set the status of all channels via a bitmap
  * @param  pObj pointer to the device object
  * @param  ChanStatusBitmap the channel status bitmap to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetAllChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t ChanStatusBitmap)
{
  int32_t status = IPS_DEVICE_OK;
  uint8_t itDisable = FALSE;
  uint8_t SpiTxRxBytes;
  uint8_t checksum;

  if (ChanStatusBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_DEVICE_ERROR;
  }
  else
  {
    int8_t loop;

    for (loop = (int8_t)pObj->nbChannels - 1; loop >= 0; loop--)
    {
      if ((pObj->isPwmEnabled & (0x1U << (uint8_t)loop)) != 0U)
      {
          /* Disable PWM for the channel if it was enabled */
          pObj->isPwmEnabled &= ~(0x1U << (uint8_t)loop);
      }
    }

    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      SpiTxRxBytes = 1U;
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      SpiTxRxBytes = 2U;
    }
    else
    {
      SpiTxRxBytes = 0U;
      status = IPS_DEVICE_ERROR;
    }

    if (status == IPS_DEVICE_OK)
    {
      do
      {
        spiPreemptionByIsr = FALSE;
        if (itDisable != FALSE)
        {
          /* re-enable Irq if disabled in previous iteration */
          pObj->IO.EnableIrq();
          itDisable = FALSE;
        }

        if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
        {
          aSpiTxBuffer[0] = ChanStatusBitmap;
        }
        else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
        {
          aSpiTxBuffer[0] = ChanStatusBitmap;
          CalcChecksum(aSpiTxBuffer[0], &checksum);
          aSpiTxBuffer[1] = checksum;
        }

        /* Wait for the SPI lock time is elapsed before sending a new request */
        while (spiLockTime > 0)
        {
        }

        /* Disable interruption before checking */
        /* pre-emption by ISR and SPI transfers */
        pObj->IO.DisableIrq();
        itDisable = TRUE;
      } while (spiPreemptionByIsr != FALSE); /* check pre-emption by ISR */

      status = IPS8200HQ_1_WriteBytes(pObj, &aSpiTxBuffer[0], &aSpiRxBuffer[0], SpiTxRxBytes);

      /* Update channel status bitmap, if needed */
      if (ChanStatusBitmap != pObj->ChanSteadyStateBitmap)
      {
        for (loop = (int8_t)pObj->nbChannels - 1; loop >= 0; loop--)
        {
          if ((ChanStatusBitmap & (0x1U << (uint8_t)loop)) != 0U)
          {
              pObj->ChanSteadyStateBitmap |= (0x1U << (uint8_t)loop);
          }
          else
          {
              pObj->ChanSteadyStateBitmap &= ~(0x1U << (uint8_t)loop);
          }
        }
      }
      /* re-enable Irq after SPI transfers */
      pObj->IO.EnableIrq();
    }
  }

  return status;
}

/**
  * @brief      Put a channel status bitmap in queue before synchronous
  *             sending done by calling IPS8200HQ_1_SendQueuedChannelStatus.
  *             Any call to functions that use the SPI between the calls of
  *             - IPS8200HQ_1_QueueChannelStatus
  *             - IPS8200HQ_1_QueueAllChannelStatus
  *             - IPS8200HQ_1_SendQueuedChannelStatus
  *             will corrupt the queue.
  *             A command for each device of the daisy chain must be
  *             specified before calling IPS8200HQ_1_SendQueuedChannelStatus.
  * @param      pObj pointer to the device object
  * @param      ChanId Id of the targeted channel
  * @param      ChanStatus the channel status to be set
  * @retval     0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_QueueChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus)
{
  int32_t status = IPS_DEVICE_OK;
  uint8_t deviceId;
  uint8_t checksum;

  deviceId = pObj->Instance;

  if (ChanId < pObj->nbChannels)
  {
    if ((pObj->isPwmEnabled & (0x1U << ChanId)) != 0U)
    {
      /* Disable PWM for the channel if it was enabled */
      pObj->isPwmEnabled &= ~(0x1U << ChanId);
    }

    if (ChanStatus != 0U)
    {
      pObj->ChanSteadyStateBitmap |= (0x1U << ChanId);
    }
    else
    {
      pObj->ChanSteadyStateBitmap &= ~(0x1U << ChanId);
    }

    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      aSpiTxBuffer[IPS8200HQ_1_SPI_DC_INSTANCES_NBR - 1U - deviceId] = pObj->ChanSteadyStateBitmap;
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      aSpiTxBuffer[2U - 2U * deviceId] = pObj->ChanSteadyStateBitmap;
      CalcChecksum(aSpiTxBuffer[2U - 2U * deviceId], &checksum);
      aSpiTxBuffer[3U - 2U * deviceId] = checksum;
    }
    else
    {
      status = IPS_DEVICE_ERROR;
    }
    if (status == IPS_DEVICE_OK)
    {
      queuedBitmap = TRUE;
    }
  }

  return (status);
}

/**
  * @brief      Put a channel status bitmap in queue before synchronous
  *             sending done by calling IPS8200HQ_1_SendQueuedChannelStatus.
  *             Any call to functions that use the SPI between the calls of
  *             - IPS8200HQ_1_QueueChannelStatus
  *             - IPS8200HQ_1_QueueAllChannelStatus
  *             - IPS8200HQ_1_SendQueuedChannelStatus
  *             will corrupt the queue.
  *             A command for each device of the daisy chain must be
  *             specified before calling IPS8200HQ_1_SendQueuedChannelStatus.
  *             NOTE: bitmap data are stored in aSpiTxBuffer in reversed order
  *             due to the daisy chain architecture
  * @param      pObj pointer to the device object
  * @param      newChanBitmap Channel status bitmap to queue
  * @retval     0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_QueueAllChannelStatus(IPS8200HQ_1_Object_t *pObj, uint8_t newChanBitmap)
{
  int32_t status = IPS_DEVICE_OK;
  uint8_t deviceId;
  uint8_t checksum;

  deviceId = pObj->Instance;

  if (newChanBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_DEVICE_ERROR;
  }
  else
  {
    int8_t chanId;
    for (chanId = (int8_t)pObj->nbChannels - 1; chanId >= 0; chanId--)
    {
      if ((pObj->isPwmEnabled & (0x1U << (uint8_t)chanId)) != 0U)
      {
          /* Disable PWM for the channel if it was enabled */
          pObj->isPwmEnabled &= ~(0x1U << (uint8_t)chanId);
      }
    }

    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      aSpiTxBuffer[IPS8200HQ_1_SPI_DC_INSTANCES_NBR - 1U - deviceId] = newChanBitmap;
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      aSpiTxBuffer[2U - 2U * deviceId] = newChanBitmap;
      CalcChecksum(aSpiTxBuffer[2U - 2U * deviceId], &checksum);
      aSpiTxBuffer[3U - 2U * deviceId] = checksum;
    }
    else
    {
      status = IPS_DEVICE_ERROR;
    }

    if (status == IPS_DEVICE_OK)
    {
      if (newChanBitmap != pObj->ChanSteadyStateBitmap)
      {
        for (chanId = (int8_t)pObj->nbChannels - 1; chanId >= 0; chanId--)
        {
          if ((newChanBitmap & (0x1U << (uint8_t)chanId)) != 0U)
          {
              pObj->ChanSteadyStateBitmap |= (0x1U << (uint8_t)chanId);
          }
          else
          {
              pObj->ChanSteadyStateBitmap &= ~(0x1U << (uint8_t)chanId);
          }
        }
      }
      queuedBitmap = TRUE;
    }
  }

  return (status);
}

/**
  * @brief  Sends previously queued channel status bitmaps
  *         simultaneously to all devices
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SendQueuedChannelStatus(void)
{
  int32_t status = IPS_DEVICE_OK;
  IPS8200HQ_1_Object_t *pObj;
  uint8_t SpiTxRxBytes;
  uint8_t Instance;

  if (queuedBitmap != FALSE)
  {
    /* Wait for the SPI lock time is elapsed before sending a new request */
    while (spiLockTime > 0)
    {
    }

    /* Assign device object to the board 0 component, so in Daisy chain correct SS pin is managed */
    pObj = (IPS8200HQ_1_Object_t*)RELAY_CompObj[0];

    /* Disable interruption before SPI transfers */
    pObj->IO.DisableIrq();
    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      SpiTxRxBytes = 2U;
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      SpiTxRxBytes = 4U;
    }
    else
    {
      SpiTxRxBytes = 0U;
      status = IPS_DEVICE_ERROR;
    }
    if (status == IPS_DEVICE_OK)
    {
      /* In Daisy chain SPI write is performed passing 2-byte data to make a one shot 16-bit write operation */
      /* using the shift byte feature available in IPS8200HQ (SDO-0 goes to SDI-1): first byte will be passed to */
      /* device 1, second byte will be used by device 0. Data in aSpiTxBuffer[] array have been already properly */
      /* swapped when queueing data */
      status = IPS8200HQ_1_WriteBytes(pObj, &aSpiTxBuffer[0], &aSpiRxBuffer[0], SpiTxRxBytes);
      queuedBitmap = FALSE;

      /* re-enable Irq after SPI transfers */
      pObj->IO.EnableIrq();

      /* Transfer channel steady state bitmap into Pwm mirror bitmap */
      for (Instance=0; Instance < IPS8200HQ_1_SPI_DC_INSTANCES_NBR; Instance++)
      {
        pObj = (IPS8200HQ_1_Object_t*)RELAY_CompObj[Instance];
        pObj->newChanSteadyStateBitmap = FALSE;
        pObj->ChanSteadyStatePwmBitmap = pObj->ChanSteadyStateBitmap;
        pObj->newChanSteadyStateBitmap = TRUE;
      }
    }
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }

  return (status);
}

/**
  * @brief      Put a channel status bitmap in queue during PWM operations before
  *             synchronous sending done by calling IPS8200HQ_1_SendQueuedPwmChannelStatus.
  *             Any call to functions that use the SPI between the calls of
  *             - IPS8200HQ_1_QueueAllChannelPwmStatus
  *             - IPS8200HQ_1_SendQueuedChannelStatus
  *             will corrupt the queue.
  *             A command for each device of the daisy chain must be
  *             specified before calling IPS8200HQ_1_SendQueuedChannelStatus.
  *             NOTE: bitmap data are stored in aSpiTxBuffer in reversed order
  *             due to the daisy chain architecture
  * @param      pObj pointer to the device object
  * @param      newChanBitmap Channel status bitmap to queue
  * @retval     0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_QueueAllChannelPwmStatus(IPS8200HQ_1_Object_t *pObj, uint8_t newChanBitmap)
{
  int32_t status = IPS_DEVICE_OK;
  uint8_t deviceId;
  uint8_t checksum;

  deviceId = pObj->Instance;

  if (newChanBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_DEVICE_ERROR;
  }
  else
  {
    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      aSpiTxBuffer[IPS8200HQ_1_SPI_DC_INSTANCES_NBR - 1U - deviceId] = newChanBitmap;
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      aSpiTxBuffer[2U - 2U * deviceId] = newChanBitmap;
      CalcChecksum(aSpiTxBuffer[2U - 2U * deviceId], &checksum);
      aSpiTxBuffer[3U - 2U * deviceId] = checksum;
    }
    else
    {
      status = IPS_DEVICE_ERROR;
    }

    if (status == IPS_DEVICE_OK)
    {
      if (newChanBitmap != pObj->nextChanEnBitmap)
      {
        int8_t chanId;
        for (chanId = (int8_t)pObj->nbChannels - 1; chanId >= 0; chanId--)
        {
          if ((newChanBitmap & (0x1U << (uint8_t)chanId)) != 0U)
          {
            pObj->nextChanEnBitmap |= (0x1U << (uint8_t)chanId);
          }
          else
          {
            pObj->nextChanEnBitmap &= ~(0x1U << (uint8_t)chanId);
          }
        }
      }
      queuedPwmBitmap = TRUE;
    }
  }

  return status;
}

/**
  * @brief  Sends previously queued channel status bitmaps, during a Pwm session,
  *         simultaneously to all devices
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SendQueuedPwmChannelStatus(void)
{
  int32_t status = IPS_DEVICE_OK;
  IPS8200HQ_1_Object_t *pObj;
  uint8_t SpiTxRxBytes;

  if (queuedPwmBitmap != FALSE)
  {
    /* Wait for the SPI lock time is elapsed before sending a new request */
    while (spiLockTime > 0)
    {
    }
    /* Disable interruption before SPI transfers */
    pObj = (IPS8200HQ_1_Object_t*)RELAY_CompObj[0];
    pObj->IO.DisableIrq();
#ifdef IPS_DEBUG
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
#endif /* #ifdef IPS_DEBUG */
    if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_8BIT)
    {
      SpiTxRxBytes = 2U;
    }
    else if (((Device_System_CtrlMode[0] >> 4U) & 0xF) == (uint8_t)IPS8200HQ_1_SPI_W_16BIT)
    {
      SpiTxRxBytes = 4U;
    }
    else
    {
      SpiTxRxBytes = 0U;
      status = IPS_DEVICE_ERROR;
    }
    if (status == IPS_DEVICE_OK)
    {
      status = IPS8200HQ_1_WriteBytes(pObj, &aSpiTxBuffer[0], &aSpiRxBuffer[0], SpiTxRxBytes);
      queuedPwmBitmap = FALSE;

      /* re-enable Irq after SPI transfers */
      pObj->IO.EnableIrq();
#ifdef IPS_DEBUG
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
#endif /* #ifdef IPS_DEBUG */
    }
  }
  else
  {
    status = IPS_DEVICE_ERROR;
  }

  return (status);
}

/**
  * @brief  Initialize the IPS8200HQ-1 relay
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
static int32_t IPS8200HQ_1_Initialize(IPS8200HQ_1_Object_t *pObj)
{
  uint8_t ctrl_id;
  int32_t status;

  status = IPS_DEVICE_OK;

  /* Disable outputs */
  switch(pObj->Instance)
  {
    case 0U:
      ctrl_id = IPS8200HQ_1_0_OUT_EN;
      break;

    case 1U:
      ctrl_id = IPS8200HQ_1_1_OUT_EN;
      break;

    default:
      ctrl_id = 0U;
      status = IPS_DEVICE_ERROR;
      break;
  }
  if (status != IPS_DEVICE_ERROR)
  {
    status = IPS8200HQ_1_SetCtrlPinStatus(pObj, ctrl_id, 0U);
  }
  return status;
}

/**
  * @brief    Write and receive a byte via SPI
  * @param    pObj pointer to the device object
  * @param    pByteToTransmit pointer to the byte to transmit
  * @param    pReceivedByte pointer to the received byte
  * @param    nbDevices number of devices in daisy chain, or 1U for standalone devices
  * @retval   0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_WriteBytes(IPS8200HQ_1_Object_t *pObj, uint8_t *pByteToTransmit, uint8_t *pReceivedByte, uint8_t nbDevices)
{
  int32_t status = IPS_DEVICE_OK;

  if (pObj->IO.SpiWrite(pObj->Instance, pByteToTransmit, pReceivedByte, nbDevices) != IPS_DEVICE_OK)
  {
    status = IPS_DEVICE_ERROR;
  }
  else
  {
    spiLockTime = (int16_t)pObj->timingTcss - (int16_t)(IPS8200HQ_1_GUARD_TIMER_TICK_IN_US*10U);
    if (spiLockTime > 0)
    {
      status = pObj->IO.StartGuardTimer();
    }
  }

  if (isrFlag != FALSE)
  {
    spiPreemptionByIsr = TRUE;
  }

  return status;
}

/**
  * @brief  Enables or disables Daisy Chain Mode (valid only if SPI HW conf has been detected)
  * @param  pObj pointer to the device object
  * @param  DcEnable Logical flag used to enable (1) or disable (0) Daisy Chain Mode
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_EnableDaisyChain(IPS8200HQ_1_Object_t *pObj, uint8_t DcEnable)
{
  int32_t status = IPS_DEVICE_OK;

  if (IPS_NbInstances < IPS8200HQ_1_SPI_DC_INSTANCES_NBR)
  {
    status = IPS_DEVICE_ERROR;
  }
  else
  {
    if (DcEnable != 0U)
    {
      if ((((Device_System_CtrlMode[0] & 0xF) == (uint8_t)IPS8200HQ_1_SPI_CTRL_MODE) &&
          ((Device_System_CtrlMode[1] & 0xF) == (uint8_t)IPS8200HQ_1_SPI_CTRL_MODE)) ||
          (((Device_System_CtrlMode[0] & 0xF) == (uint8_t)IPS8200HQ_1_SPI_DC_CTRL_MODE) &&
          ((Device_System_CtrlMode[1] & 0xF) == (uint8_t)IPS8200HQ_1_SPI_DC_CTRL_MODE)))
      {
        pObj->ctrlMode = (uint8_t)IPS8200HQ_1_SPI_DC_CTRL_MODE;
        Device_System_CtrlMode[0] &= 0xF0;
        Device_System_CtrlMode[0] |= (uint8_t)(IPS8200HQ_1_SPI_DC_CTRL_MODE & 0xF);
        Device_System_CtrlMode[1] &= 0xF0;
        Device_System_CtrlMode[1] |= (uint8_t)(IPS8200HQ_1_SPI_DC_CTRL_MODE & 0xF);
        Device_System_ChipType = (uint8_t)IPS8200HQ_1_SPI_DC_CHIP_TYPE;
        /* Dummy SPI DC write useful to reset false PC error due to SS rising edge in SPI HW setup */
        IPS8200HQ_1_QueueAllChannelStatus(pObj, 0U);
        IPS8200HQ_1_SendQueuedChannelStatus();
      }
      else
      {
        status = IPS_DEVICE_ERROR;
      }
    }
    else
    {
      if (((Device_System_CtrlMode[0] & 0xF) == (uint8_t)IPS8200HQ_1_SPI_DC_CTRL_MODE) &&
          ((Device_System_CtrlMode[1] & 0xF) == (uint8_t)IPS8200HQ_1_SPI_DC_CTRL_MODE))
      {
        pObj->ctrlMode = (uint8_t)IPS8200HQ_1_SPI_CTRL_MODE;
        Device_System_CtrlMode[0] &= 0xF0;
        Device_System_CtrlMode[0] |= (uint8_t)(IPS8200HQ_1_SPI_CTRL_MODE & 0xF);
        Device_System_CtrlMode[1] &= 0xF0;
        Device_System_CtrlMode[1] |= (uint8_t)(IPS8200HQ_1_SPI_CTRL_MODE & 0xF);
        Device_System_ChipType = (uint8_t)IPS8200HQ_1_SPI_CHIP_TYPE;
        IPS8200HQ_1_SetAllChannelStatus(pObj, 0U);
      }
      else
      {
        status = IPS_DEVICE_ERROR;
      }
    }
  }

  return status;
}
#endif /* #ifdef APP_SPI_IFC */

/**
  * @brief  Set the device operating mode
  * @param  pObj pointer to the device object
  * @param  pCtrlMode Pointer to the control mode value
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_SetOperatingMode(IPS8200HQ_1_Object_t *pObj, uint8_t *pCtrlMode)
{
  int32_t status = IPS_DEVICE_OK;
  uint8_t Sel_2_Status = 0;
  uint8_t Sel_1_Status = 0;
  uint8_t WdEn_Status = 0;
  uint8_t Instance;
  uint8_t sel2PinId;
  uint8_t sel1PinId;
  uint8_t wdenPinId;

  Instance = pObj->Instance;
  switch(Instance)
  {
    case 0U:
      sel2PinId = IPS8200HQ_1_0_SEL2_L;
      sel1PinId = IPS8200HQ_1_0_SEL1;
      wdenPinId = IPS8200HQ_1_0_WDEN;
      break;

#ifdef APP_SPI_IFC
    case 1U:
      sel2PinId = IPS8200HQ_1_1_SEL2_L;
      sel1PinId = IPS8200HQ_1_1_SEL1;
      wdenPinId = IPS8200HQ_1_1_WDEN;
      break;
#endif /* #ifdef APP_SPI_IFC */

    default:
      status = IPS_DEVICE_ERROR;
      break;
  }
  if ((status != IPS_DEVICE_ERROR) && (IPS8200HQ_1_GetCtrlPinStatus(pObj, sel2PinId, &Sel_2_Status) != IPS_DEVICE_ERROR))
  {
    if (Sel_2_Status != 0U)
    {
      /* SEL2_L level is high: SPI_IFC (JP21 closed) */
      pObj->ControlPinsBitmap |= (0x1U << (sel2PinId - pObj->firstCtrl));
      pObj->ctrlMode = (uint8_t)IPS8200HQ_1_SPI_CTRL_MODE;
      *pCtrlMode = (uint8_t)pObj->ctrlMode;
      Device_System_CtrlMode[Instance] = (uint8_t)IPS8200HQ_1_SPI_CTRL_MODE;
      Device_System_ChipType = (uint8_t)IPS8200HQ_1_SPI_CHIP_TYPE;

      /* SEL1 level must be checked to determine if 8-bit or 16-bit SPI opmode */
      if (IPS8200HQ_1_GetCtrlPinStatus(pObj, sel1PinId, &Sel_1_Status) != IPS_DEVICE_ERROR)
      {
        if (Sel_1_Status != 0U)
        {
          /* SEL1 high if SW20 closed 2-3 and JP22 closed: SPI 16-bit */
          pObj->ControlPinsBitmap |= (0x1U << (sel1PinId - pObj->firstCtrl));
          pObj->spiMode = (uint8_t)IPS8200HQ_1_SPI_W_16BIT;
          *pCtrlMode &= 0xF;
          *pCtrlMode |= (uint8_t)(IPS8200HQ_1_SPI_W_16BIT << 4U);
          Device_System_CtrlMode[Instance] &= 0xF;
          Device_System_CtrlMode[Instance] |= (uint8_t)(IPS8200HQ_1_SPI_W_16BIT << 4U);
        }
        else
        {
          /* SEL1 low (default) if SW20 closed 2-3 and JP22 open: SPI 8-bit */
          pObj->ControlPinsBitmap &= ~(0x1U << (sel1PinId - pObj->firstCtrl));
          pObj->spiMode = (uint8_t)IPS8200HQ_1_SPI_W_8BIT;
          *pCtrlMode &= 0xF;
          *pCtrlMode |= (uint8_t)(IPS8200HQ_1_SPI_W_8BIT << 4U);
          Device_System_CtrlMode[Instance] &= 0xF;
          Device_System_CtrlMode[Instance] |= (uint8_t)(IPS8200HQ_1_SPI_W_8BIT << 4U);
        }
      }
      else
      {
        pObj->spiMode = IPS8200HQ_1_SPI_W_NONE;
        *pCtrlMode &= 0xF;
        Device_System_CtrlMode[Instance] &= 0xF;
        status = IPS_DEVICE_ERROR;
      }
      
      /* Watchdog enable check */
      if (IPS8200HQ_1_GetCtrlPinStatus(pObj, wdenPinId, &WdEn_Status) != IPS_DEVICE_ERROR)
      {
        if (WdEn_Status != 0U)
        {
          /* WDEN high if SW3 closed 2-3: Watchdog timer enabled */
          Device_System_WdMode[Instance] = 1U;
          *pCtrlMode |= (uint8_t)(0x1U << IPS8200HQ_1_SPI_WD_MODE);
        }
        else
        {
          /* WDEN low if SW3 closed 1-2: Watchdog timer disabled */
          Device_System_WdMode[Instance] = 0U;
          *pCtrlMode &= (uint8_t)(~(0x1U << IPS8200HQ_1_SPI_WD_MODE));
        }
      }
      else
      {
        Device_System_WdMode[Instance] = 0U;
        status = IPS_DEVICE_ERROR;
      }
    }
    else
    {
      /* SEL2_L level is low (default): PAR_IFC (JP21 open) */
      pObj->ControlPinsBitmap &= ~(0x1U << (sel2PinId - pObj->firstCtrl));
      pObj->ctrlMode = (uint8_t)IPS8200HQ_1_PAR_CTRL_MODE;
      pObj->spiMode = (uint8_t)IPS8200HQ_1_SPI_W_NONE;
      *pCtrlMode = (uint8_t)pObj->ctrlMode;
      Device_System_CtrlMode[Instance] = (uint8_t)pObj->ctrlMode;
      Device_System_ChipType = (uint8_t)IPS8200HQ_1_PAR_CHIP_TYPE;
    }
  }
  else
  {
    pObj->ctrlMode = (uint8_t)IPS8200HQ_1_UNDEF_CTRL_MODE;
    pObj->spiMode = (uint8_t)IPS8200HQ_1_SPI_W_NONE;
    *pCtrlMode = (uint8_t)IPS8200HQ_1_UNDEF_CTRL_MODE;
    Device_System_CtrlMode[Instance] = (uint8_t)IPS8200HQ_1_UNDEF_CTRL_MODE;
    status = IPS_DEVICE_ERROR;
  }

  return status;
}

/**
  * @brief  Get the chip type
  * @param  pObj pointer to the device object
  * @param  pChipType Pointer to the chip type value
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS8200HQ_1_GetChipType(IPS8200HQ_1_Object_t *pObj, uint8_t *pChipType)
{
  int32_t status = IPS_DEVICE_OK;
  uint8_t Sel_2_Status = 0;

  if (IPS8200HQ_1_GetCtrlPinStatus(pObj, IPS8200HQ_1_0_SEL2_L, &Sel_2_Status) != IPS_DEVICE_ERROR)
  {
    if (Sel_2_Status != 0U)
    {
      /* SEL2_L level is high: SPI_IFC (JP21 closed) */
      *pChipType = (uint8_t)IPS8200HQ_1_SPI_CHIP_TYPE;
    }
    else
    {
      /* SEL2_L level is low (default): PAR_IFC (JP21 open) */
      *pChipType = (uint8_t)IPS8200HQ_1_PAR_CHIP_TYPE;
    }
  }
  else
  {
    *pChipType = 0U;
    status = IPS_DEVICE_ERROR;
  }

  return status;
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

/**
  * @}
  */
