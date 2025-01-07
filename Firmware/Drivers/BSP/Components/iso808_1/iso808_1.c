/**
  ******************************************************************************
  * @file    iso808_1.c
  * @author  AMS IPC Application Team
  * @brief   ISO808-1 (Galvanic isolated octal high-side smart power solid
  *          state-relay) driver
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
#include "iso808_1.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */

/** @addtogroup ISO808_1 ISO808_1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup ISO808_1_Global_Variables ISO808_1 Global Variables
  * @{
  */

/** Common driver structure which lists ISO808_1 functions */
ISO808_1_CommonDrv_t ISO808_1_COMMON_Driver =
{
  ISO808_1_Init,
  ISO808_1_DeInit,
  ISO808_1_ReadID,
  ISO808_1_GetCapabilities,
  ISO808_1_GetFaultStatus,
  ISO808_1_GetChannelStatus,
  ISO808_1_SetChannelStatus,
  ISO808_1_GetAllChannelStatus,
  ISO808_1_SetAllChannelStatus,
  ISO808_1_GetChannelFreq,
  ISO808_1_SetChannelFreq,
  ISO808_1_GetChannelDc,
  ISO808_1_SetChannelDc,
  ISO808_1_GetPwmEnable,
  ISO808_1_SetPwmEnable,
  ISO808_1_PwmTick,
  ISO808_1_GetCtrlPinStatus,
  ISO808_1_SetCtrlPinStatus,
  ISO808_1_SetOperatingMode
};

/* Global system PWM enable bitmap (it takes in count which boards have PWM enabled) */
uint8_t SWITCH_System_PWMEnable_bitmap;

/** Instance counter  */
uint8_t IPS_NbInstances;

/** Device counter  */
uint8_t IPS_NbDevices;

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/** @defgroup ISO808_1_Private_Function_Prototypes ISO808_1 Private Function Prototypes
  * @{
  */

static int32_t ISO808_1_Initialize(ISO808_1_Object_t *pObj);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup ISO808_1_Functions_Definition ISO808_1 Functions Definition
  * @{
  */

/**
  * @brief  Register Component Bus IO operations
  * @param  pObj pointer to the device object
  * @param  pIO  pointer to the IO functions structure
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_RegisterBusIO(ISO808_1_Object_t *pObj, ISO808_1_IO_t *pIO)
{
  int32_t ret;

  if (pObj == NULL)
  {
    ret = IPS_SWITCH_ERROR;
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
      ret = IPS_SWITCH_ERROR;
    }
  }
  return ret;
}

/**
  * @brief  Initialize the ISO808_1 switch
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_Init(ISO808_1_Object_t *pObj)
{
  int32_t status = IPS_SWITCH_OK;

  if (pObj->is_initialized == 0U)
  {
    if (ISO808_1_Initialize(pObj) != IPS_SWITCH_OK)
    {
      status = IPS_SWITCH_ERROR;
    }
    else
    {
      IPS_NbInstances++;
      if (IPS_NbInstances > ISO808_1_INSTANCES_NBR)
      {
        status = IPS_SWITCH_ERROR;
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
  * @brief  Deinitialize the ISO808_1 switch
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_DeInit(ISO808_1_Object_t *pObj)
{
  int8_t loop;
  if (pObj->is_initialized == 1U)
  {
    /* Stop PWM */
    for (loop = (int8_t)pObj->nbChannels - 1; loop >= 0; loop--)
    {
      (void)ISO808_1_SetPwmEnable(pObj, (uint8_t)loop, 0U);
    }

     /* Disable all channels */
    (void)ISO808_1_SetAllChannelStatus(pObj, 0U);

    IPS_NbInstances--;
  }

  pObj->is_initialized = 0;

  return IPS_SWITCH_OK;
}

/**
  * @brief  Get the status of the specified channel
  * @param  pObj pointer to the device object
  * @param  pChanStatusBitmap pointer to the channel status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_GetAllChannelStatus(ISO808_1_Object_t *pObj, uint8_t* pChanStatusBitmap)
{
  int32_t status = IPS_SWITCH_OK;
  *pChanStatusBitmap = pObj->ChanSteadyStateBitmap;
  return status;
}

/**
  * @brief  Get ISO808_1 switch capabilities
  * @param  pObj pointer to the device object
  * @param  pCapabilities pointer to the capabilities
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_GetCapabilities(ISO808_1_Object_t *pObj, ISO808_1_Capabilities_t *pCapabilities)
{
  int32_t status = IPS_SWITCH_OK;

  if (pObj->chipId == ISO808_1_CHIP_ID)
  {
    pCapabilities->nbChannels = ISO808_1_MAX_NB_CHANNELS;
    pCapabilities->nbCtrlPins = ISO808_1_MAX_NB_CONTROLS;
    pCapabilities->firstCtrlPin = ISO808_1_0_FIRST_CONTROL;
  }
  else
  {
    status = IPS_SWITCH_ERROR;
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
int32_t ISO808_1_GetChannelDc(ISO808_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t status = IPS_SWITCH_OK;
  if (ChanId < pObj->nbChannels)
  {
    *pChanDc = pObj->channelDc[ChanId];
  }
  else
  {
    status = IPS_SWITCH_ERROR;
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
int32_t ISO808_1_GetChannelFreq(ISO808_1_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t status = IPS_SWITCH_OK;
  if (ChanId < pObj->nbChannels)
  {
    *pChanFreq = pObj->channelFreq[ChanId];
  }
  else
  {
    status = IPS_SWITCH_ERROR;
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
int32_t ISO808_1_GetChannelStatus(ISO808_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t status = IPS_SWITCH_OK;

  if (ChanId < pObj->nbChannels)
  {
    *pChanStatus = (pObj->ChanSteadyStateBitmap >> ChanId) & 0x1U;
  }
  else
  {
    status = IPS_SWITCH_ERROR;
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
int32_t ISO808_1_GetCtrlPinStatus(ISO808_1_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus)
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
    status = IPS_SWITCH_ERROR;
  }
  return status;
}

/**
  * @brief  Get the fault status
  * @param  pObj pointer to the device object
  * @param  pFaultStatus pointer to the fault status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_GetFaultStatus(ISO808_1_Object_t *pObj, uint8_t *pFaultStatus)
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
int32_t ISO808_1_GetPwmEnable(ISO808_1_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled)
{
  int32_t status = IPS_SWITCH_OK;

  if (ChanId < pObj->nbChannels)
  {
    *pPwmEnabled = ((pObj->isPwmEnabled >> ChanId) & 0x1U);
  }
  else
  {
    status = IPS_SWITCH_ERROR;
  }
  return (status);
}

/**
  * @brief  PWM tick
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_PwmTick(ISO808_1_Object_t *pObj)
{
  int32_t status = IPS_SWITCH_OK;
  int32_t ret;
  uint8_t flagToBeChanged = 0U;
  static uint8_t chanEnBitmapChangeFlag = 0U;

  if (pObj->isPwmEnabled != 0U)
  {
    int8_t chanId;
    uint8_t newChanBitMap;

#ifdef IPS_DEBUG
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
#endif /* #ifdef IPS_DEBUG */

    if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
    {
      flagToBeChanged = 0U;
    }

    /*  Update channels first to minimize latency */
    pObj->chanEnBitmap = pObj->nextChanEnBitmap;

    /*  Load the current bitmap of the corresponding device */
    newChanBitMap =  pObj->chanEnBitmap;

    if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
    {
      if (chanEnBitmapChangeFlag != 0U)
      {
        uint8_t loop;

        /* Synchronous Control Mode management */
        /* LOAD low (Preparing to latch input states) */
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 1U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 1U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
        for (loop = 0U; loop < ISO808_1_TW_LOAD_WIDTH; loop++)
        {
          /* Loop needed to match tW(LOAD) */
          ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 0U);
          if (ret != IPS_SWITCH_OK)
          {
            status = IPS_SWITCH_ERROR;
          }
        }
      }
    }
    for (chanId = (int8_t)(pObj->nbChannels) - 1; chanId >= 0; chanId--)
    {
      /* Update channels first to minimize latency */
      if ((pObj->isPwmEnabled & (0x1U << (uint8_t)chanId)) != 0U)
      {
        ret = pObj->IO.WriteChan(&pObj->Pin, chanId, (pObj->nextChanEnBitmap & (0x1U << (uint8_t)chanId)));
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
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
          if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
          {
            flagToBeChanged = 1U;
          }
        }
      } // end if prepare next tick update

      /*  Increment tick */
      pObj->pwmTimTickCnt[chanId]++;
    } // end for
    if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
    {
      if (chanEnBitmapChangeFlag != 0U)
      {
        uint8_t loop;

        /* Synchronous Control Mode management */
        /* LOAD high (latching input states) */
        /* SYNCH low (Preparing to transfer to output stage) */
        /* SYNCH high (Effective transfer to output stage) */
        for (loop = 0U; loop < ISO808_1_TSU_LOAD_WIDTH; loop++)
        {
          /* Loop needed to match tSU(LOAD) */
          ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 1U);
          if (ret != IPS_SWITCH_OK)
          {
            status = IPS_SWITCH_ERROR;
          }
        }
        for (loop = 0U; loop < ISO808_1_TW_SYNC_WIDTH; loop++)
        {
          /* Loop needed to keep SYNC low for more than 20 us, that is tw(SYNC) */
          ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 0U);
          if (ret != IPS_SWITCH_OK)
          {
            status = IPS_SWITCH_ERROR;
          }
        }
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 1U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
        chanEnBitmapChangeFlag = 0U;
      }
    }

    pObj->nextChanEnBitmap = (newChanBitMap & pObj->isPwmEnabled);
    if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
    {
      if (flagToBeChanged == 1U)
      {
        chanEnBitmapChangeFlag = 1U;
      }
    }

#ifdef IPS_DEBUG
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
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
int32_t ISO808_1_ReadID(ISO808_1_Object_t *pObj, uint32_t *pId)
{
  *pId = pObj->chipId;
  return IPS_SWITCH_OK;
}

/**
  * @brief  Set the status of all channels via a bitmap
  * @param  pObj pointer to the device object
  * @param  ChanStatusBitmap the channel status bitmap to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_SetAllChannelStatus(ISO808_1_Object_t *pObj, uint8_t ChanStatusBitmap)
{
  int32_t status = IPS_SWITCH_OK;
  int32_t ret;

  if (ChanStatusBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_SWITCH_ERROR;
  }
  else
  {
    int8_t loop;
    if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
    {
      uint8_t waitLoop;

      /* Synchronous Control Mode management */
      /* LOAD low (Preparing to latch input states) */
      ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 1U);
      if (ret != IPS_SWITCH_OK)
      {
        status = IPS_SWITCH_ERROR;
      }
      ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 1U);
      if (ret != IPS_SWITCH_OK)
      {
        status = IPS_SWITCH_ERROR;
      }
      for (waitLoop = 0U; waitLoop < ISO808_1_TW_LOAD_WIDTH; waitLoop++)
      {
        /* Loop needed to match tW(LOAD) */
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 0U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
      }
    }
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
      if (ret != IPS_SWITCH_OK)
      {
        status = IPS_SWITCH_ERROR;
      }
    }
    if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
    {
      uint8_t waitLoop;

      /* Synchronous Control Mode management */
      /* LOAD high (latching input states) */
      /* SYNCH low (Preparing to transfer to output stage) */
      /* SYNCH high (Effective transfer to output stage) */
      for (waitLoop = 0U; waitLoop < ISO808_1_TSU_LOAD_WIDTH; waitLoop++)
      {
        /* Loop needed to match tSU(LOAD) */
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 1U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
      }
      for (waitLoop = 0U; waitLoop < ISO808_1_TW_SYNC_WIDTH; waitLoop++)
      {
        /* Loop needed to keep SYNC low for more than 20 us, that is tw(SYNC) */
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 0U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
      }
      ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 1U);
      if (ret != IPS_SWITCH_OK)
      {
        status = IPS_SWITCH_ERROR;
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
int32_t ISO808_1_SetChannelDc(ISO808_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc)
{
  int32_t status = IPS_SWITCH_OK;
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
    status = IPS_SWITCH_ERROR;
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
int32_t ISO808_1_SetChannelFreq(ISO808_1_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq)
{
  int32_t status = IPS_SWITCH_OK;
  if (ChanId < pObj->nbChannels)
  {
    uint16_t newFreq;
    if (ChanFreq > ISO808_1_MAX_CHAN_FREQ)
    {
       newFreq = ISO808_1_MAX_CHAN_FREQ;
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
    status = IPS_SWITCH_ERROR;
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
int32_t ISO808_1_SetChannelStatus(ISO808_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus)
{
  int32_t status = IPS_SWITCH_OK;
  int32_t ret;

  if (ChanId < pObj->nbChannels)
  {
    if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
    {
      uint8_t waitLoop;

      /* Synchronous Control Mode management */
      /* LOAD low (Preparing to latch input states) */
      ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 1U);
      if (ret != IPS_SWITCH_OK)
      {
        status = IPS_SWITCH_ERROR;
      }
      ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 1U);
      if (ret != IPS_SWITCH_OK)
      {
        status = IPS_SWITCH_ERROR;
      }
      for (waitLoop = 0U; waitLoop < ISO808_1_TW_LOAD_WIDTH; waitLoop++)
      {
        /* Loop needed to match tW(LOAD) */
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 0U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
      }
    }
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
    if (ret != IPS_SWITCH_OK)
    {
      status = IPS_SWITCH_ERROR;
    }
    if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
    {
      uint8_t waitLoop;

      /* Synchronous Control Mode management */
      /* LOAD high (latching input states) */
      /* SYNCH low (Preparing to transfer to output stage) */
      /* SYNCH high (Effective transfer to output stage) */
      for (waitLoop = 0U; waitLoop < ISO808_1_TSU_LOAD_WIDTH; waitLoop++)
      {
        /* Loop needed to match tSU(LOAD) */
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 1U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
      }
      for (waitLoop = 0U; waitLoop < ISO808_1_TW_SYNC_WIDTH; waitLoop++)
      {
        /* Loop needed to keep SYNC low for more than 20 us, that is tw(SYNC) */
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 0U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
      }
      ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 1U);
      if (ret != IPS_SWITCH_OK)
      {
        status = IPS_SWITCH_ERROR;
      }
    }
  }
  else
  {
    status = IPS_SWITCH_ERROR;
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
int32_t ISO808_1_SetCtrlPinStatus(ISO808_1_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
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
    status = IPS_SWITCH_ERROR;
  }
  return status;
}

/**
  * @brief  Set the device operating mode (DCM or SCM)
  * @param  pObj pointer to the device object
  * @param  opMode Operating Mode (SCM or DCM)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_SetOperatingMode(ISO808_1_Object_t *pObj, uint8_t opMode)
{
  int32_t status = IPS_SWITCH_OK;
  int32_t ret;

  if (opMode == (uint8_t)ISO808_1_DCM)
  {
    /* LOAD and SYNCH level are kept both low: DCM (you can additionally force low these two signals in HW on the board keeping J1 and J2 both closed) */
    ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 0U);
    if (ret != IPS_SWITCH_OK)
    {
      status = IPS_SWITCH_ERROR;
    }
    pObj->ControlPinsBitmap &= ~(0x1U << (ISO808_1_0_CTRL_SYNCH - pObj->firstCtrl));
    ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 0U);
    if (ret != IPS_SWITCH_OK)
    {
      status = IPS_SWITCH_ERROR;
    }
    pObj->ControlPinsBitmap &= ~(0x1U << (ISO808_1_0_CTRL_LOAD - pObj->firstCtrl));

    pObj->ctrlMode = (uint8_t)ISO808_1_DCM;
  }
  else
  {
    /* LOAD and SYNCH level are controlled by the FW to sync output levels: SCM (J1 and J2 in HW on the board MUST be left open) */

    /* Reset high both signals level */
    ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 1U);
    if (ret != IPS_SWITCH_OK)
    {
      status = IPS_SWITCH_ERROR;
    }
    pObj->ControlPinsBitmap |= (0x1U << (ISO808_1_0_CTRL_LOAD- pObj->firstCtrl));
    ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 1U);
    if (ret != IPS_SWITCH_OK)
    {
      status = IPS_SWITCH_ERROR;
    }
    pObj->ControlPinsBitmap |= (0x1U << (ISO808_1_0_CTRL_SYNCH - pObj->firstCtrl));

    pObj->ctrlMode = (uint8_t)ISO808_1_SCM;
  }

  return status;
}

/**
  * @brief  Set the PWM enable state
  * @param  pObj pointer to the device object
  * @param  ChanId Id of the targeted channel
  * @param  PwmEnabled PWM enable state to set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808_1_SetPwmEnable(ISO808_1_Object_t *pObj, uint8_t ChanId, uint8_t PwmEnabled)
{
  int32_t status = IPS_SWITCH_OK;
  int32_t ret;

  if (ChanId < pObj->nbChannels)
  {
    /* Disable PWM timer to prevent concurrent access via the tick update */
    pObj->isPwmEnabled &= ~(0x1U << ChanId);
    pObj->IO.SetPwm(0U);
#ifdef IPS_DEBUG
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
#endif /* #ifdef IPS_DEBUG */

    if (PwmEnabled == 0U)
    {
      /*
        We turn off the specific channel also in Steady State mode,
        properly managing the currently active operating mode
      */
      if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
      {
        uint8_t waitLoop;

        /* Synchronous Control Mode management */
        /* LOAD low (Preparing to latch input states) */
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 1U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 1U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
        for (waitLoop = 0U; waitLoop < ISO808_1_TW_LOAD_WIDTH; waitLoop++)
        {
          /* Loop needed to match tW(LOAD) */
          ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 0U);
          if (ret != IPS_SWITCH_OK)
          {
            status = IPS_SWITCH_ERROR;
          }
        }
      }
      ret = pObj->IO.WriteChan(&pObj->Pin, ChanId, PwmEnabled);
      pObj->nextChanEnBitmap &= ~(0x1U << ChanId);
      if (ret != IPS_SWITCH_OK)
      {
        status = IPS_SWITCH_ERROR;
      }
      if (pObj->ctrlMode == (uint8_t)ISO808_1_SCM)
      {
        uint8_t waitLoop;

        /* Synchronous Control Mode management */
        /* LOAD high (latching input states) */
        /* SYNCH low (Preparing to transfer to output stage) */
        /* SYNCH high (Effective transfer to output stage) */
        for (waitLoop = 0U; waitLoop < ISO808_1_TSU_LOAD_WIDTH; waitLoop++)
        {
          /* Loop needed to match tSU(LOAD) */
          ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_LOAD, 1U);
          if (ret != IPS_SWITCH_OK)
          {
            status = IPS_SWITCH_ERROR;
          }
        }
        for (waitLoop = 0U; waitLoop < ISO808_1_TW_SYNC_WIDTH; waitLoop++)
        {
          /* Loop needed to keep SYNC low for more than 20 us, that is tw(SYNC) */
          ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 0U);
          if (ret != IPS_SWITCH_OK)
          {
            status = IPS_SWITCH_ERROR;
          }
        }
        ret = pObj->IO.WritePin(&pObj->Pin, ISO808_1_0_CTRL_SYNCH, 1U);
        if (ret != IPS_SWITCH_OK)
        {
          status = IPS_SWITCH_ERROR;
        }
      }
    }

    pObj->chanPwmTimActionTable[ChanId] = 0U;
    pObj->pwmTimTickCnt[ChanId] = 0U;

    if (PwmEnabled != 0U)
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
      SWITCH_System_PWMEnable_bitmap |= (0x1U << pObj->Instance);
    }
    else
    {
      SWITCH_System_PWMEnable_bitmap &= ~(0x1U << pObj->Instance);
    }
    pObj->IO.SetPwm(SWITCH_System_PWMEnable_bitmap);
#ifdef IPS_DEBUG
    if (SWITCH_System_PWMEnable_bitmap != 0U)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    }
#endif /* #ifdef IPS_DEBUG */
  }
  else
  {
    status = IPS_SWITCH_ERROR;
  }
  return status;
}

/**
  * @brief  Initialize the ISO808_1 switch
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
static int32_t ISO808_1_Initialize(ISO808_1_Object_t *pObj)
{
  int32_t ret;

  ret = IPS_SWITCH_OK;
  /* Power off the component. */
  if (ISO808_1_SetAllChannelStatus(pObj, 0U) != IPS_SWITCH_OK)
  {
    ret = IPS_SWITCH_ERROR;
  }
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

/**
  * @}
  */
