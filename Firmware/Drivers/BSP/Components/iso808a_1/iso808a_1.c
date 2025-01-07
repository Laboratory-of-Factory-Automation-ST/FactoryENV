/**
  ******************************************************************************
  * @file    iso808a_1.c
  * @author  AMS IPC Application Team
  * @brief   ISO808A-1 driver
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
#include "iso808a_1.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup COMPONENTS COMPONENTS
  * @{
  */

/** @addtogroup ISO808A_1 ISO808A_1
  * @{
  */

/* Global variables ----------------------------------------------------------*/

/** @defgroup ISO808A_1_Global_Variables ISO808A_1 Global Variables
  * @{
  */

extern void *RELAY_CompObj[ISO808A_1_INSTANCES_NBR];

/** Common driver structure which lists ISO808A_1 functions */
ISO808A_1_CommonDrv_t ISO808A_1_COMMON_Driver =
{
  ISO808A_1_Init,
  ISO808A_1_DeInit,
  ISO808A_1_ReadID,
  ISO808A_1_GetCapabilities,
  ISO808A_1_GetFaultStatus,
  ISO808A_1_GetFaultRegister,
  ISO808A_1_GetChannelStatus,
  ISO808A_1_SetChannelStatus,
  ISO808A_1_GetCtrlPinStatus,
  ISO808A_1_SetCtrlPinStatus,
  ISO808A_1_GetAllChannelStatus,
  ISO808A_1_SetAllChannelStatus,
  ISO808A_1_GetChannelFreq,
  ISO808A_1_SetChannelFreq,
  ISO808A_1_GetChannelDc,
  ISO808A_1_SetChannelDc,
  ISO808A_1_GetPwmEnable,
  ISO808A_1_SetPwmEnable,
  ISO808A_1_PwmTick,
  ISO808A_1_GuardTimerTick,
  ISO808A_1_QueueChannelStatus,
  ISO808A_1_QueueAllChannelStatus,
  ISO808A_1_SendQueuedChannelStatus,
  ISO808A_1_GetFaultRegister_DaisyChain,
  ISO808A_1_PwmTick_DaisyChain,
  ISO808A_1_GuardTimerTick_DaisyChain
};

/* Global system PWM enable bitmap (it takes in count which boards have PWM enabled) */
uint8_t RELAY_System_PWMEnable_bitmap;

/* Global system configuration mode (Parallel Independent or Daisy Chain Mode) */
uint8_t RELAY_System_OpMode;

/* Global system activation state */
uint8_t RELAY_System_State_bitmap;

/** Instance counter  */
uint8_t IPS_NbInstances;

/** Device counter  */
uint8_t IPS_NbDevices;

/** SPI Lock time in us between two consecutive SPI access */
int16_t spiLockTime;

/**
  * @}
  */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup ISO808A_1_Private_Variables ISO808A_1 Private Variables
  * @{
  */

/** queuedBitmap flag which is set when a new channel bitmap has to be applied in daisy chaining mode */
static uint8_t queuedBitmap = FALSE;

/** queuedPwmBitmap flag which is set when a new channel Pwm bitmap has to be applied in daisy chaining mode during Pwm operation */
static uint8_t queuedPwmBitmap = FALSE;

/** SPI preemption flag : set when an SPI access occurs under ISR */
uint8_t spiPreemptionByIsr;

/** ISR flag : set when code an ISR is running */
uint8_t isrFlag;

/** SPI Transmit buffer */
static uint8_t aSpiTxBuffer[SPI_TX_MAX_NB_BYTES];

/** SPI Receive buffer */
static uint8_t aSpiRxBuffer[SPI_RX_MAX_NB_BYTES];

/** SPI Transmit buffer in Pwm in Daisy Chain mode */
static uint8_t aSpiTxBufferPwm[SPI_TX_MAX_NB_BYTES];

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/

/** @defgroup ISO808A_1_Private_Function_Prototypes ISO808A_1 Private Function Prototypes
  * @{
  */

static int32_t ISO808A_1_Initialize(ISO808A_1_Object_t *pObj);
int32_t ISO808A_1_WriteBytes(ISO808A_1_Object_t *pObj, uint8_t *pByteToTransmit, uint8_t *pReceivedByte, uint8_t nbDevices);

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/

/** @defgroup ISO808A_1_Functions_Definition ISO808A_1 Functions Definition
  * @{
  */

/**
  * @brief  Register Component Bus IO operations
  * @param  pObj pointer to the device object
  * @param  pIO  pointer to the IO functions structure
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_RegisterBusIO(ISO808A_1_Object_t *pObj, ISO808A_1_IO_t *pIO)
{
  int32_t ret;

  if (pObj == NULL)
  {
    ret = IPS_RELAY_ERROR;
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
      ret = IPS_RELAY_ERROR;
    }
  }
  return ret;
}

/**
  * @brief  Initialize the ISO808A_1 relay
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_Init(ISO808A_1_Object_t *pObj)
{
  int32_t status = IPS_RELAY_OK;

  if (pObj->is_initialized == 0U)
  {
    if (ISO808A_1_Initialize(pObj) != IPS_RELAY_OK)
    {
      status = IPS_RELAY_ERROR;
    }
    else
    {
      IPS_NbInstances++;
      if (IPS_NbInstances > ISO808A_1_INSTANCES_NBR)
      {
        status = IPS_RELAY_ERROR;
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
  * @brief  Deinitialize the ISO808A_1 relay
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_DeInit(ISO808A_1_Object_t *pObj)
{
  if (pObj->is_initialized == 1U)
  {
    /* Disable PWM */
    pObj->isPwmEnabled = 0;

     /* Disable all channels */
    (void)ISO808A_1_SetAllChannelStatus(pObj, 0U);

    IPS_NbInstances--;
  }

  pObj->is_initialized = 0;

  return IPS_RELAY_OK;
}

/**
  * @brief  Get the status of the specified channel
  * @param  pObj pointer to the device object
  * @param  pChanStatusBitmap pointer to the channel status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_GetAllChannelStatus(ISO808A_1_Object_t *pObj, uint8_t* pChanStatusBitmap)
{
  int32_t status = IPS_RELAY_OK;
  *pChanStatusBitmap = pObj->ChanSteadyStateBitmap;
  return status;
}

/**
  * @brief  Get ISO808A_1 relay capabilities
  * @param  pObj pointer to the device object
  * @param  pCapabilities pointer to the capabilities
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_GetCapabilities(ISO808A_1_Object_t *pObj, ISO808A_1_Capabilities_t *pCapabilities)
{
  int32_t status = IPS_RELAY_OK;

  if (pObj->chipId == ISO808A_1_CHIP_ID)
  {
    pCapabilities->nbChannels = ISO808A_1_MAX_NB_CHANNELS;
    switch(pObj->Instance)
    {
      case 0U:
        pCapabilities->firstCtrlPin = ISO808A_1_0_FIRST_CONTROL;
        break;

      case 1U:
        pCapabilities->firstCtrlPin = ISO808A_1_1_FIRST_CONTROL;
        break;

      default:
        status = IPS_RELAY_ERROR;
        break;
    }
    pCapabilities->nbCtrlPins = ISO808A_1_MAX_NB_CONTROLS;
  }
  else
  {
    status = IPS_RELAY_ERROR;
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
int32_t ISO808A_1_GetChannelStatus(ISO808A_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanStatus)
{
  int32_t status = IPS_RELAY_OK;

  if (ChanId < pObj->nbChannels)
  {
    *pChanStatus = (pObj->ChanSteadyStateBitmap >> ChanId) & 0x1U;
  }
  else
  {
    status = IPS_RELAY_ERROR;
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
int32_t ISO808A_1_GetCtrlPinStatus(ISO808A_1_Object_t *pObj, uint8_t CtrlPinId, uint8_t *pCtrlPinStatus)
{
  int32_t status = IPS_RELAY_OK;

  if ((CtrlPinId >= pObj->firstCtrl) && (CtrlPinId < (pObj->firstCtrl + pObj->nbCtrls)))
  {
    *pCtrlPinStatus = (pObj->ControlPinsBitmap >> (CtrlPinId - pObj->firstCtrl)) & 0x1U;
  }
  else
  {
    status = IPS_RELAY_ERROR;
  }
  return status;
}

/**
  * @brief  Get the fault status
  * @param  pObj pointer to the device object
  * @param  pFaultStatus pointer to the fault status
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_GetFaultStatus(ISO808A_1_Object_t *pObj, uint8_t *pFaultStatus)
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
int32_t ISO808A_1_ReadID(ISO808A_1_Object_t *pObj, uint32_t *pId)
{
  *pId = pObj->chipId;
  return IPS_RELAY_OK;
}

/**
  * @brief  Get the fault register for all input channels of a single board
  * @param  pObj pointer to the device object
  * @param  pFaultRegister pointer to the Fault Register value (1 byte)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_GetFaultRegister(ISO808A_1_Object_t *pObj, uint8_t *pFaultRegister)
{
  int32_t status;
  uint8_t itDisable = FALSE;

  *pFaultRegister = 0xFFU;
  if (pObj->isPwmEnabled == 0U)
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

      aSpiTxBuffer[0] = pObj->ChanSteadyStateBitmap;

      /* Wait for the SPI lock time is elapsed before sending a new request */
      while (spiLockTime > 0)
      {
      }

      /* Disable interruption before checking */
      /* pre-emption by ISR and SPI transfers */
      pObj->IO.DisableIrq();
      itDisable = TRUE;
    } while (spiPreemptionByIsr != FALSE); /* check pre-emption by ISR */

    status = ISO808A_1_WriteBytes(pObj, &aSpiTxBuffer[0], &aSpiRxBuffer[0], 1U);
    *pFaultRegister = aSpiRxBuffer[0];

    /* re-enable Irq after SPI transfers */
    pObj->IO.EnableIrq();
  }
  else
  {
    status = IPS_RELAY_ERROR;
  }

  return status;
}

/**
  * @brief  Get the fault register for all input channels of two boards connected in Daisy Chain
  * @param  pFaultRegister pointer to the Fault Register value (2 bytes)
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_GetFaultRegister_DaisyChain(uint16_t *pFaultRegister)
{
  int32_t status = IPS_RELAY_OK;
  uint8_t itDisable = FALSE;
  ISO808A_1_Object_t *pObj;
  uint8_t SpiTxRxBytes;
  uint8_t Instance;
  uint16_t FaultRegVal;

  *pFaultRegister = 0xFFFFU;
  if (queuedBitmap != FALSE)
  {
    status = IPS_RELAY_ERROR;
  }

  if (status == IPS_RELAY_OK)
  {
    /* If at least one of the two boards is in PWM, return FAIL status */
    for (Instance=0; Instance < ISO808A_1_INSTANCES_NBR; Instance++)
    {
      pObj = (ISO808A_1_Object_t*)RELAY_CompObj[Instance];

      if (pObj->isPwmEnabled != 0U)
      {
        status = IPS_RELAY_ERROR;
      }
    }
  }

  if (status == IPS_RELAY_OK)
  {
    /* Load SPI Tx Buffer with 2-bytes data to be written */
    for (Instance=0; Instance < ISO808A_1_INSTANCES_NBR; Instance++)
    {
      pObj = (ISO808A_1_Object_t*)RELAY_CompObj[Instance];
      aSpiTxBuffer[ISO808A_1_INSTANCES_NBR - 1U - Instance] = pObj->ChanSteadyStateBitmap;
    }

    pObj = (ISO808A_1_Object_t*)RELAY_CompObj[0];
    SpiTxRxBytes = 2U;
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

    status = ISO808A_1_WriteBytes(pObj, &aSpiTxBuffer[0], &aSpiRxBuffer[0], SpiTxRxBytes);

    /* Get 2-bytes Fault Register data from SPI Rx Buffer */
    FaultRegVal = 0U;
    for (Instance=0; Instance < ISO808A_1_INSTANCES_NBR; Instance++)
    {
      FaultRegVal |= ((uint16_t)(aSpiRxBuffer[ISO808A_1_INSTANCES_NBR - 1U - Instance]) << (8U*Instance));
    }
    *pFaultRegister = FaultRegVal;

    /* re-enable Irq after SPI transfers */
    pObj->IO.EnableIrq();
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
int32_t ISO808A_1_GetChannelDc(ISO808A_1_Object_t *pObj, uint8_t ChanId, uint8_t *pChanDc)
{
  int32_t status = IPS_RELAY_OK;
  if (ChanId < pObj->nbChannels)
  {
    *pChanDc = pObj->channelDc[ChanId];
  }
  else
  {
    status = IPS_RELAY_ERROR;
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
int32_t ISO808A_1_GetChannelFreq(ISO808A_1_Object_t *pObj, uint8_t ChanId, uint16_t *pChanFreq)
{
  int32_t status = IPS_RELAY_OK;
  if (ChanId < pObj->nbChannels)
  {
    *pChanFreq = pObj->channelFreq[ChanId];
  }
  else
  {
    status = IPS_RELAY_ERROR;
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
int32_t ISO808A_1_GetPwmEnable(ISO808A_1_Object_t *pObj, uint8_t ChanId, uint8_t *pPwmEnabled)
{
  int32_t status = IPS_RELAY_OK;

  if (ChanId < pObj->nbChannels)
  {
    *pPwmEnabled = ((pObj->isPwmEnabled >> ChanId) & 0x1U);
  }
  else
  {
    status = IPS_RELAY_ERROR;
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
int32_t ISO808A_1_SetChannelDc(ISO808A_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanDc)
{
  int32_t status = IPS_RELAY_OK;
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
    status = IPS_RELAY_ERROR;
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
int32_t ISO808A_1_SetChannelFreq(ISO808A_1_Object_t *pObj, uint8_t ChanId, uint16_t ChanFreq)
{
  int32_t status = IPS_RELAY_OK;
  if (ChanId < pObj->nbChannels)
  {
    uint16_t newFreq;
    if (ChanFreq > ISO808A_1_MAX_CHAN_FREQ)
    {
       newFreq = ISO808A_1_MAX_CHAN_FREQ;
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
    status = IPS_RELAY_ERROR;
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
int32_t ISO808A_1_SetPwmEnable(ISO808A_1_Object_t *pObj, uint8_t ChanId, uint8_t EnablePwm)
{
  int32_t status;

  status = IPS_RELAY_OK;
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
    }
    else
    {
        pObj->isPwmEnabled &= ~(0x1U << ChanId);
    }
    if (pObj->isPwmEnabled != 0U)
    {
      RELAY_System_PWMEnable_bitmap |= (0x1U << pObj->Instance);
    }
    else
    {
      RELAY_System_PWMEnable_bitmap &= ~(0x1U << pObj->Instance);
    }
    pObj->IO.SetPwm(RELAY_System_PWMEnable_bitmap);
  }
  else
  {
    status = IPS_RELAY_ERROR;
  }
  return status;
}

/**
  * @brief  PWM tick
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_PwmTick(ISO808A_1_Object_t *pObj)
{
  int32_t status = IPS_RELAY_OK;

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
    status = ISO808A_1_SetAllChannelPwmStatus(pObj,  pObj->nextChanEnBitmap | pObj->ChanSteadyStateBitmap);
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
      } // end if prepare next tick update

      /*  Increment tick */
      pObj->pwmTimTickCnt[chanId]++;
    } // end for

    pObj->nextChanEnBitmap = (newChanBitMap & pObj->isPwmEnabled);

    /* Reset isr flag */
    isrFlag = FALSE;
  }
  return status;
}

/**
  * @brief  PWM tick for Daisy Chain conf
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_PwmTick_DaisyChain(void)
{
  int32_t status = IPS_RELAY_OK;

  if (RELAY_System_PWMEnable_bitmap != 0U)
  {
    uint8_t Instance;
    ISO808A_1_Object_t *pObj;

    /* Set isr flag */
    isrFlag = TRUE;

    /*  Update channels first to minimize latency */
    (void)ISO808A_1_SendQueuedPwmChannelStatus();

    for (Instance=0; Instance < ISO808A_1_INSTANCES_NBR; Instance++)
    {
      pObj = (ISO808A_1_Object_t*)RELAY_CompObj[Instance];
      if (pObj->isPwmEnabled != 0U)
      {
        int8_t chanId;
        uint8_t newChanBitMap;

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
          } // end if prepare next tick update

          /*  Increment tick */
          pObj->pwmTimTickCnt[chanId]++;
        } // end for

        pObj->nextChanEnBitmap = (newChanBitMap & pObj->isPwmEnabled);
        if (pObj->newChanSteadyStateBitmap == FALSE)
        {
          status = ISO808A_1_QueueAllChannelPwmStatus(pObj, pObj->nextChanEnBitmap);
        }
        else
        {
          status = ISO808A_1_QueueAllChannelPwmStatus(pObj, pObj->nextChanEnBitmap | pObj->ChanSteadyStatePwmBitmap);
        }
      }
      else
      {
        status = ISO808A_1_QueueAllChannelPwmStatus(pObj, pObj->ChanSteadyStatePwmBitmap);
      }
    }

    /* Reset isr flag */
    isrFlag = FALSE;
  }
  return status;
}

/******************************************************//**
  * @brief  Guard Timer tick for parallel independent conf
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
 **********************************************************/
int32_t ISO808A_1_GuardTimerTick(ISO808A_1_Object_t *pObj)
{
  int32_t status = IPS_RELAY_OK;

#ifdef IPS_DEBUG
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
#endif /* #ifdef IPS_DEBUG */

  if (spiLockTime > 0)
  {
    spiLockTime -= (int16_t)(ISO808A_1_GUARD_TIMER_TICK_IN_US*5U);
  }
  else
  {
    status = pObj->IO.StopGuardTimer();
  }

#ifdef IPS_DEBUG
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
#endif /* #ifdef IPS_DEBUG */
  return status;
}

/******************************************************//**
  * @brief  Guard Timer tick for Daisy Chain conf
  * @retval 0 in case of success, an error code otherwise
 **********************************************************/
int32_t ISO808A_1_GuardTimerTick_DaisyChain(void)
{
  int32_t status = IPS_RELAY_OK;

#ifdef IPS_DEBUG
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
#endif /* #ifdef IPS_DEBUG */

  if (spiLockTime > 0)
  {
    spiLockTime -= (int16_t)(ISO808A_1_GUARD_TIMER_TICK_IN_US*5U);
  }
  else
  {
    ISO808A_1_Object_t *pObj;

    pObj = (ISO808A_1_Object_t*)RELAY_CompObj[0];
    status = pObj->IO.StopGuardTimer();
  }

#ifdef IPS_DEBUG
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
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
int32_t ISO808A_1_SetCtrlPinStatus(ISO808A_1_Object_t *pObj, uint8_t CtrlPinId, uint8_t CtrlPinStatus)
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
    status = IPS_RELAY_ERROR;
  }
  return status;
}

/**
  * @brief  Set the status of all channels for PWM via a bitmap
  * @param  pObj pointer to the device object
  * @param  ChanStatusBitmap the channel status bitmap to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_SetAllChannelPwmStatus(ISO808A_1_Object_t *pObj, uint8_t ChanStatusBitmap)
{
  int32_t status;
  uint8_t SpiTxRxBytes;

  if (ChanStatusBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_RELAY_ERROR;
  }
  else
  {
    uint8_t deviceId;
    deviceId = pObj->Instance;
    aSpiTxBuffer[deviceId] = ChanStatusBitmap;
    if (RELAY_System_OpMode == (uint8_t)ISO808A_1_DCM)
    {
      SpiTxRxBytes = 2U;
    }
    else
    {
      SpiTxRxBytes = 1U;
    }
    status = pObj->IO.SpiWrite(deviceId, &aSpiTxBuffer[deviceId], &aSpiRxBuffer[deviceId], SpiTxRxBytes);
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
int32_t ISO808A_1_SetChannelStatus(ISO808A_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus)
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
      status = ISO808A_1_SetAllChannelPwmStatus(pObj,  pObj->ChanSteadyStateBitmap);
    }
    else
    {
      status = ISO808A_1_SetAllChannelStatus(pObj,  pObj->ChanSteadyStateBitmap);
    }
  }
  else
  {
    status = IPS_RELAY_ERROR;
  }
  return status;
}

/**
  * @brief  Set the status of all channels via a bitmap
  * @param  pObj pointer to the device object
  * @param  ChanStatusBitmap the channel status bitmap to be set
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_SetAllChannelStatus(ISO808A_1_Object_t *pObj, uint8_t ChanStatusBitmap)
{
  int32_t status;
  uint8_t itDisable = FALSE;

  if (ChanStatusBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_RELAY_ERROR;
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

    do
    {
      spiPreemptionByIsr = FALSE;
      if (itDisable != FALSE)
      {
        /* re-enable Irq if disabled in previous iteration */
        pObj->IO.EnableIrq();
        itDisable = FALSE;
      }

      aSpiTxBuffer[0] = ChanStatusBitmap;

      /* Wait for the SPI lock time is elapsed before sending a new request */
      while (spiLockTime > 0)
      {
      }

      /* Disable interruption before checking */
      /* pre-emption by ISR and SPI transfers */
      pObj->IO.DisableIrq();
      itDisable = TRUE;
    } while (spiPreemptionByIsr != FALSE); /* check pre-emption by ISR */

    status = ISO808A_1_WriteBytes(pObj, &aSpiTxBuffer[0], &aSpiRxBuffer[0], 1U);

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

  return status;
}

/**
  * @brief      Put a channel status bitmap in queue before synchronous
  *             sending done by calling ISO808A_1_SendQueuedChannelStatus.
  *             Any call to functions that use the SPI between the calls of
  *             - ISO808A_1_QueueChannelStatus
  *             - ISO808A_1_QueueAllChannelStatus
  *             - ISO808A_1_SendQueuedChannelStatus
  *             will corrupt the queue.
  *             A command for each device of the daisy chain must be
  *             specified before calling ISO808A_1_SendQueuedChannelStatus.
  * @param      pObj pointer to the device object
  * @param      ChanId Id of the targeted channel
  * @param      ChanStatus the channel status to be set
  * @retval     0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_QueueChannelStatus(ISO808A_1_Object_t *pObj, uint8_t ChanId, uint8_t ChanStatus)
{
  int32_t status = IPS_RELAY_ERROR;
  uint8_t deviceId;

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

    aSpiTxBuffer[ISO808A_1_INSTANCES_NBR - 1U - deviceId] = pObj->ChanSteadyStateBitmap;

    queuedBitmap = TRUE;
    status = IPS_RELAY_OK;
  }

  return (status);
}

/**
  * @brief      Put a channel status bitmap in queue before synchronous
  *             sending done by calling ISO808A_1_SendQueuedChannelStatus.
  *             Any call to functions that use the SPI between the calls of
  *             - ISO808A_1_QueueChannelStatus
  *             - ISO808A_1_QueueAllChannelStatus
  *             - ISO808A_1_SendQueuedChannelStatus
  *             will corrupt the queue.
  *             A command for each device of the daisy chain must be
  *             specified before calling ISO808A_1_SendQueuedChannelStatus.
  *             NOTE: bitmap data are stored in aSpiTxBuffer in reversed order
  *             due to the daisy chain architecture
  * @param      pObj pointer to the device object
  * @param      newChanBitmap Channel status bitmap to queue
  * @retval     0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_QueueAllChannelStatus(ISO808A_1_Object_t *pObj, uint8_t newChanBitmap)
{
  int32_t status;
  uint8_t deviceId;

  deviceId = pObj->Instance;

  if (newChanBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_RELAY_ERROR;
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

    aSpiTxBuffer[ISO808A_1_INSTANCES_NBR - 1U - deviceId] = newChanBitmap;

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
    status = IPS_RELAY_OK;
  }

  return (status);
}

/**
  * @brief  Sends previously queued channel status bitmaps
  *         simultaneously to all devices
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_SendQueuedChannelStatus(void)
{
  int32_t status = IPS_RELAY_ERROR;
  ISO808A_1_Object_t *pObj;
  uint8_t SpiTxRxBytes;
  uint8_t Instance;

  if (queuedBitmap != FALSE)
  {
    /* Wait for the SPI lock time is elapsed before sending a new request */
    while (spiLockTime > 0)
    {
    }

    /* Assign device object to the board 0 component, so in Daisy chain correct SS pin is managed */
    pObj = (ISO808A_1_Object_t*)RELAY_CompObj[0];

    /* Disable interruption before SPI transfers */
    pObj->IO.DisableIrq();
    if (RELAY_System_OpMode == (uint8_t)ISO808A_1_DCM)
    {
      SpiTxRxBytes = 2U;
    }
    else
    {
      SpiTxRxBytes = 1U;
    }
    /* In Daisy chain SPI write is performed passing 2-byte data to make a one shot 16-bit write operation */
    /* using the shift byte feature available in ISO808A_1 (SDO-0 goes to SDI-1): first byte will be passed to */
    /* device 1, second byte will be used by device 0. Data in aSpiTxBuffer[] array have been already properly */
    /* swapped when queueing data */
    status = ISO808A_1_WriteBytes(pObj, &aSpiTxBuffer[0], &aSpiRxBuffer[0], SpiTxRxBytes);
    queuedBitmap = FALSE;

    /* re-enable Irq after SPI transfers */
    pObj->IO.EnableIrq();

    /* Transfer channel steady state bitmap into Pwm mirror bitmap */
    for (Instance=0; Instance < ISO808A_1_INSTANCES_NBR; Instance++)
    {
      pObj = (ISO808A_1_Object_t*)RELAY_CompObj[Instance];
      pObj->newChanSteadyStateBitmap = FALSE;
      pObj->ChanSteadyStatePwmBitmap = pObj->ChanSteadyStateBitmap;
      pObj->newChanSteadyStateBitmap = TRUE;
    }
  }

  return (status);
}

/**
  * @brief      Put a channel status bitmap in queue during PWM operations before
  *             synchronous sending done by calling ISO808A_1_SendQueuedPwmChannelStatus.
  *             Any call to functions that use the SPI between the calls of
  *             - ISO808A_1_QueueAllChannelPwmStatus
  *             - ISO808A_1_SendQueuedChannelStatus
  *             will corrupt the queue.
  *             A command for each device of the daisy chain must be
  *             specified before calling ISO808A_1_SendQueuedChannelStatus.
  *             NOTE: bitmap data are stored in aSpiTxBuffer in reversed order
  *             due to the daisy chain architecture
  * @param      pObj pointer to the device object
  * @param      newChanBitmap Channel status bitmap to queue
  * @retval     0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_QueueAllChannelPwmStatus(ISO808A_1_Object_t *pObj, uint8_t newChanBitmap)
{
  int32_t status;
  uint8_t deviceId;

  deviceId = pObj->Instance;

  if (newChanBitmap > ((0x1U << pObj->nbChannels) - 1U))
  {
    status = IPS_RELAY_ERROR;
  }
  else
  {
    aSpiTxBufferPwm[ISO808A_1_INSTANCES_NBR - 1U - deviceId] = newChanBitmap;

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
    status = IPS_RELAY_OK;
  }

  return status;
}

/**
  * @brief  Sends previously queued channel status bitmaps, during a Pwm session,
  *         simultaneously to all devices
  * @retval 0 in case of success, an error code otherwise
  */
int32_t ISO808A_1_SendQueuedPwmChannelStatus(void)
{
  int32_t status = IPS_RELAY_ERROR;
  ISO808A_1_Object_t *pObj;
  uint8_t SpiTxRxBytes;
  static uint8_t aSpiRxBufferPwm[SPI_RX_MAX_NB_BYTES];


  if (queuedPwmBitmap != FALSE)
  {
    /* Wait for the SPI lock time is elapsed before sending a new request */
    while (spiLockTime > 0)
    {
    }
    /* Disable interruption before SPI transfers */
    pObj = (ISO808A_1_Object_t*)RELAY_CompObj[0];
    pObj->IO.DisableIrq();
    if (RELAY_System_OpMode == (uint8_t)ISO808A_1_DCM)
    {
      SpiTxRxBytes = 2U;
    }
    else
    {
      SpiTxRxBytes = 1U;
    }
    status = ISO808A_1_WriteBytes(pObj, &aSpiTxBufferPwm[0], &aSpiRxBufferPwm[0], SpiTxRxBytes);
    queuedPwmBitmap = FALSE;

    /* re-enable Irq after SPI transfers */
    pObj->IO.EnableIrq();
  }

  return (status);
}

/**
  * @brief  Initialize the ISO808A_1 relay
  * @param  pObj pointer to the device object
  * @retval 0 in case of success, an error code otherwise
  */
static int32_t ISO808A_1_Initialize(ISO808A_1_Object_t *pObj)
{
  uint8_t ctrl_id;
  int32_t status;

  status = IPS_RELAY_OK;

  /* Disable outputs */
  switch(pObj->Instance)
  {
    case 0U:
      ctrl_id = ISO808A_1_0_OUT_EN;
      break;

    case 1U:
      ctrl_id = ISO808A_1_1_OUT_EN;
      break;

    default:
      ctrl_id = 0U;
      status = IPS_RELAY_ERROR;
      break;
  }
  if (status != IPS_RELAY_ERROR)
  {
    status = ISO808A_1_SetCtrlPinStatus(pObj, ctrl_id, 0U);
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
int32_t ISO808A_1_WriteBytes(ISO808A_1_Object_t *pObj, uint8_t *pByteToTransmit, uint8_t *pReceivedByte, uint8_t nbDevices)
{
  int32_t status;

  if (pObj->IO.SpiWrite(pObj->Instance, pByteToTransmit, pReceivedByte, nbDevices) != IPS_RELAY_OK)
  {
    status = IPS_RELAY_ERROR;
  }
  else
  {
    spiLockTime = (int16_t)pObj->timingTcss - (int16_t)(ISO808A_1_GUARD_TIMER_TICK_IN_US*5U);
    status = pObj->IO.StartGuardTimer();
  }

  if (isrFlag != FALSE)
  {
    spiPreemptionByIsr = TRUE;
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
