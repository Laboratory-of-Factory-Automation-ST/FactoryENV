/**
  ******************************************************************************
  * @file    ips4260l.c
  * @author  AMS IPC Application Team
  * @brief   IPS4260L driver
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
#include "ips4260l.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */

/** @addtogroup IPS4260L IPS4260L
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup IPS4260L_Global_Variables IPS4260L Global Variables
  * @{
  */

/** Common driver structure which lists IPS4260L functions */
IPS4260L_CommonDrv_t IPS4260L_COMMON_Driver =
{
  IPS4260L_Init,
  IPS4260L_DeInit,
  IPS4260L_ReadID,
  IPS4260L_GetCapabilities,
  IPS4260L_GetFaultStatus,
  IPS4260L_GetChannelStatus,
  IPS4260L_SetChannelStatus,
  IPS4260L_GetAllChannelStatus,
  IPS4260L_SetAllChannelStatus,
  IPS4260L_GetChannelFreq,
  IPS4260L_SetChannelFreq,
  IPS4260L_GetChannelDc,
  IPS4260L_SetChannelDc,
  IPS4260L_GetPwmEnable,
  IPS4260L_SetPwmEnable,
  IPS4260L_PwmTick
};

/* Global system PWM enable bitmap (it takes in count which boards have PWM enabled) */
uint8_t SWITCH_System_PWMEnable_bitmap;

/** Instance counter  */
uint8_t IPS_NbInstances;

/** Device counter  */
uint8_t IPS_NbDevices;

/** Global IRQ disable bitmap */
uint8_t itDisableBitmap = 0U;

/**
  * @}
  */
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup IPS4260L_Private_Variables IPS4260L Private Variables
  * @{
  */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/


/** @defgroup IPS4260L_Private_Function_Prototypes IPS4260L Private Function Prototypes
  * @{
  */

static int32_t IPS4260L_Initialize(IPS4260L_Object_t *pObj);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup IPS4260L_Exported_Functions IPS4260L Exported Functions
  * @{
  */

/**
  * @brief  Register Component Bus IO operations
  * @param  pObj pointer to the device object
  * @param  pIO  pointer to the IO functions structure
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS4260L_RegisterBusIO(IPS4260L_Object_t *pObj, IPS4260L_IO_t *pIO)
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
    pObj->IO.WriteChan     = pIO->WriteChan;
    pObj->IO.ReadChan      = pIO->ReadChan;
    pObj->IO.WriteAllChan  = pIO->WriteAllChan;
    pObj->IO.ReadAllChan   = pIO->ReadAllChan;
    pObj->IO.SetPwm        = pIO->SetPwm;
    pObj->IO.EnableIrq     = pIO->EnableIrq;
    pObj->IO.DisableIrq    = pIO->DisableIrq;

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
  * @brief  Initialize the IPS4260L switch
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS4260L_Init(IPS4260L_Object_t *pObj)
{
  int32_t status = IPS_SWITCH_OK;

  if (pObj->is_initialized == 0U)
  {
    if (IPS4260L_Initialize(pObj) != IPS_SWITCH_OK)
    {
      status = IPS_SWITCH_ERROR;
    }
    else
    {
      IPS_NbInstances++;
      if (IPS_NbInstances > IPS4260L_INSTANCES_NBR)
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
  * @brief  Deinitialize the IPS4260L switch
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS4260L_DeInit(IPS4260L_Object_t *pObj)
{
  int8_t loop;
  if (pObj->is_initialized == 1U)
  {
    /* Stop PWM */
    for (loop = (int8_t)pObj->nbChannels - 1; loop >= 0; loop--)
    {
      (void)IPS4260L_SetPwmEnable(pObj, (uint8_t)loop, 0U);
    }

     /* Disable all channels */
    (void)IPS4260L_SetAllChannelStatus(pObj, 0U);

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
int32_t IPS4260L_GetAllChannelStatus(IPS4260L_Object_t *pObj, uint8_t* pChanStatusBitmap)
{
  int32_t status = IPS_SWITCH_OK;
  pObj->IO.ReadAllChan(&pObj->Pin, pChanStatusBitmap);

  return status;
}

/**
  * @brief  Get IPS4260L switch capabilities
  * @param  pObj pointer to the device object
  * @param  pCapabilities pointer to the capabilities
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS4260L_GetCapabilities(IPS4260L_Object_t *pObj, IPS4260L_Capabilities_t *pCapabilities)
{
  int32_t status = IPS_SWITCH_OK;

  if (pObj->chipId == IPS4260L_CHIP_ID)
  {
    pCapabilities->nbChannels = IPS4260L_MAX_NB_CHANNELS;
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
int32_t IPS4260L_GetChannelDc(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc)
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
int32_t IPS4260L_GetChannelFreq(IPS4260L_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq)
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
int32_t IPS4260L_GetChannelStatus(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t status = IPS_SWITCH_OK;

  if (ChanId < pObj->nbChannels)
  {
    pObj->IO.ReadChan(&pObj->Pin, ChanId, pChanStatus);
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
  * @param  pFaultStatus pointer to the fault status (LSB) and input status (MSB)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t IPS4260L_GetFaultStatus(IPS4260L_Object_t *pObj, uint16_t *pFaultStatus)
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
int32_t IPS4260L_GetPwmEnable(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled)
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
int32_t IPS4260L_PwmTick(IPS4260L_Object_t *pObj)
{
  int32_t status = IPS_SWITCH_OK;

  if (pObj->isPwmEnabled != 0U)
  {
    int8_t chanId;
    uint8_t newChanBitMap;
    uint8_t pinState;
    uint8_t currChanBitMap;

#ifdef IPS_DEBUG
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
#endif /* #ifdef IPS_DEBUG */

    /* Save current channel bitmap */
    currChanBitMap = pObj->chanEnBitmap;

    /*  Update channels first to minimize latency */
    pObj->chanEnBitmap = pObj->nextChanEnBitmap;

    /*  Load the current bitmap of the corresponding device */
    newChanBitMap =  pObj->chanEnBitmap;

    for (chanId = (int8_t)(pObj->nbChannels) - 1; chanId >= 0; chanId--)
    {
      /* Update channels first to minimize latency */
      if ((pObj->isPwmEnabled & (0x1U << (uint8_t)chanId)) != 0U)
      {
        if ((pObj->nextChanEnBitmap & (1U << (uint8_t)chanId)) == 0U)
        {
          /* Try to trigger a falling edge on input channel */
          pinState = (currChanBitMap >> (uint8_t)chanId) & 1U;
          if (pinState != 0U)
          {
            /* Disable interruption before setting low the output channel, */
            /* in order to avoid false falling edge detection on IN_DIAGx exti line */
            itDisableBitmap |= (1U << (uint8_t)chanId);
#ifdef IPS_DEBUG
            if ((uint8_t)chanId == 3U)
            {
              HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
            }
            else
            {
              HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
            }
#endif /* #ifdef IPS_DEBUG */
          }
        }
        status = pObj->IO.WriteChan(&pObj->Pin, chanId, (pObj->nextChanEnBitmap & (0x1U << (uint8_t)chanId)));
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
int32_t IPS4260L_ReadID(IPS4260L_Object_t *pObj, uint32_t *pId)
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
int32_t IPS4260L_SetAllChannelStatus(IPS4260L_Object_t *pObj, uint8_t ChanStatusBitmap)
{
  int32_t status = IPS_SWITCH_OK;

  if (ChanStatusBitmap > ((1U << pObj->nbChannels) - 1U))
  {
    status = IPS_SWITCH_ERROR;
  }
  else
  {
    int8_t loop;
    uint8_t pinState;

    for (loop = (int8_t)pObj->nbChannels - 1; loop >= 0; loop--)
    {
      if ((pObj->isPwmEnabled & (1U << (uint8_t)loop)) != 0U)
      {
        /* Disable PWM for the channel if it was enabled */
        pObj->isPwmEnabled &= ~(1U << (uint8_t)loop);
      }

      /* If the PWM mode is disabled, directly set the channel */
      if ((ChanStatusBitmap & (1U << (uint8_t)loop)) != 0U)
      {
        pObj->ChanSteadyStateBitmap |= (1U << (uint8_t)loop);
      }
      else
      {
        /* Try to trigger a falling edge on input channel */
        pinState = (pObj->ChanSteadyStateBitmap >> (uint8_t)loop) & 1U;
        if (pinState != 0U)
        {
          /* Disable interruption before setting low the output channel, */
          /* in order to avoid false falling edge detection on IN_DIAGx exti line */
          itDisableBitmap |= (1U << (uint8_t)loop);
#ifdef IPS_DEBUG
          if ((uint8_t)loop == 3U)
          {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
          }
          else
          {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
          }
#endif /* #ifdef IPS_DEBUG */
        }
        pObj->ChanSteadyStateBitmap &= ~(1U << (uint8_t)loop);
      }
      status = pObj->IO.WriteChan(&pObj->Pin, (uint8_t)loop, (ChanStatusBitmap >> (uint8_t)loop) & 1U);
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
int32_t IPS4260L_SetChannelDc(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc)
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
int32_t IPS4260L_SetChannelFreq(IPS4260L_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq)
{
  int32_t status = IPS_SWITCH_OK;
  if (ChanId < pObj->nbChannels)
  {
    uint16_t newFreq;
    if (ChanFreq > IPS4260L_MAX_CHAN_FREQ)
    {
       newFreq = IPS4260L_MAX_CHAN_FREQ;
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
int32_t IPS4260L_SetChannelStatus(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus)
{
  int32_t status;
  uint8_t pinState;

  if (ChanId < pObj->nbChannels)
  {
    if ((pObj->isPwmEnabled & (1U << ChanId)) != 0U)
    {
      /* Disable PWM for the channel if it was enabled */
      pObj->isPwmEnabled &= ~(1U << ChanId);
    }

    if (ChanStatus != 0U)
    {
      pObj->ChanSteadyStateBitmap |= (1U << ChanId);
    }
    else
    {
      /* Try to trigger a falling edge on input channel */
      pinState = (pObj->ChanSteadyStateBitmap >> ChanId) & 1U;
      if (pinState != 0U)
      {
        /* Disable interruption before setting low the output channel, */
        /* in order to avoid false falling edge detection on IN_DIAGx exti line */
        itDisableBitmap |= (1U << ChanId);
#ifdef IPS_DEBUG
        if (ChanId == 3U)
        {
          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
        }
        else
        {
          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        }
#endif /* #ifdef IPS_DEBUG */
      }
      pObj->ChanSteadyStateBitmap &= ~(1U << ChanId);
    }
    status = pObj->IO.WriteChan(&pObj->Pin, ChanId, ChanStatus);
  }
  else
  {
    status = IPS_SWITCH_ERROR;
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
int32_t IPS4260L_SetPwmEnable(IPS4260L_Object_t *pObj, uint8_t ChanId, uint8_t PwmEnabled)
{
  int32_t status = IPS_SWITCH_OK;
  uint8_t pinState;

  if (ChanId < pObj->nbChannels)
  {
    /* Disable PWM timer to prevent concurrent access via the tick update */
    pObj->isPwmEnabled &= ~(1U << ChanId);
    pObj->IO.SetPwm(0U);
#ifdef IPS_DEBUG
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
#endif /* #ifdef IPS_DEBUG */

    if (PwmEnabled == 0U)
    {
      /* Try to trigger a falling edge on input channel */
      pinState = (pObj->nextChanEnBitmap >> ChanId) & 1U;
      if (pinState != 0U)
      {
        /* Disable interruption before setting low the output channel, */
        /* in order to avoid false falling edge detection on IN_DIAGx exti line */
        itDisableBitmap |= (1U << ChanId);
#ifdef IPS_DEBUG
        if (ChanId == 3U)
        {
          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
        }
        else
        {
          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        }
#endif /* #ifdef IPS_DEBUG */
      }
      status = pObj->IO.WriteChan(&pObj->Pin, ChanId, PwmEnabled);
      pObj->nextChanEnBitmap &= ~(1U << ChanId);
    }

    pObj->chanPwmTimActionTable[ChanId] = 0U;
    pObj->pwmTimTickCnt[ChanId] = 0U;

    if (PwmEnabled != 0U)
    {
      pObj->isPwmEnabled |= (1U << ChanId);
      pObj->ChanSteadyStateBitmap &= ~(1U << ChanId);
    }
    else
    {
      pObj->isPwmEnabled &= ~(1U << ChanId);
    }
    if (pObj->isPwmEnabled != 0U)
    {
      SWITCH_System_PWMEnable_bitmap |= (1U << pObj->Instance);
    }
    else
    {
      SWITCH_System_PWMEnable_bitmap &= ~(1U << pObj->Instance);
    }
    pObj->IO.SetPwm(SWITCH_System_PWMEnable_bitmap);
#ifdef IPS_DEBUG
    if (SWITCH_System_PWMEnable_bitmap != 0U)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
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
  * @brief  Initialize the IPS4260L switch
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
static int32_t IPS4260L_Initialize(IPS4260L_Object_t *pObj)
{
  int32_t ret;

  ret = IPS_SWITCH_OK;
  /* Power off the component. */
  if (IPS4260L_SetAllChannelStatus(pObj, 0U) != IPS_SWITCH_OK)
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
