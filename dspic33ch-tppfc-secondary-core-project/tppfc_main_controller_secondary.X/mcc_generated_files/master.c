/**
  MASTER Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    master.c

  @Summary
    This is the generated driver implementation file for the MASTER driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for MASTER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CH512MP506S1
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
 */

/*
    (c) 2022 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */

#include <xc.h>
#include "master.h"

#include "../sources/devices/dev_TPBLPFC_typedef.h"
#include "../sources/devices/dev_TPBLPFC_numberconnection_typedef.h"

inline static bool MASTER_ProtocolAIsFull();
inline static bool MASTER_ProtocolAIsEmpty();
inline static bool MASTER_ProtocolBIsFull();
inline static bool MASTER_ProtocolBIsEmpty();

/**
 Section: Driver Interface Function Definitions
 */

void MASTER_Initialize()
{
  //RFITSEL Trigger data valid interrupt when 1st FIFO entry is written by Slave; MTSIACK disabled; STMIRQ disabled; MRSTIE disabled; 
  SI1CON = 0x00;

    //ProtocolB Interrupt Flag Clear
    IFS8bits.MSIBIF = 0;	
    //ProtocolB Interrupt Enable
    IEC8bits.MSIBIE = 0;

}

void MASTER_InterruptRequestGenerate()
{
  SI1CONbits.STMIRQ = 1;
}

bool MASTER_IsInterruptRequestAcknowledged()
{
  return (SI1STATbits.STMIACK);

}

void MASTER_InterruptRequestComplete()
{
  SI1CONbits.STMIRQ = 0;
}

bool MASTER_IsInterruptRequested()
{
  return (SI1STATbits.MTSIRQ);
}

void MASTER_InterruptRequestAcknowledge()
{
  SI1CONbits.MTSIACK = 1;
}

void MASTER_InterruptRequestAcknowledgeComplete()
{
  SI1CONbits.MTSIACK = 0;
}

MASTER_SYSTEM_STATUS MASTER_SystemStatusGet()
{
  MASTER_SYSTEM_STATUS systemStatus = MASTER_SYSTEM_STATUS_RUNNING;


  if (SI1STATbits.MSTRST)
  {
    systemStatus = MASTER_SYSTEM_STATUS_IN_RESET;
  } else
  {
    switch (SI1STATbits.MSTPWR)
    {
      case 0: systemStatus = MASTER_SYSTEM_STATUS_NOT_IN_LOW_POWER_MODE;
        break;
      case 1: systemStatus = MASTER_SYSTEM_STATUS_IDLE;
        break;
      case 2: systemStatus = MASTER_SYSTEM_STATUS_SLEEP;
        break;
      default:systemStatus = MASTER_SYSTEM_STATUS_RUNNING;
        break;
    }
  }
  return systemStatus;
}

uint16_t MASTER_Read(uint16_t *pData, uint16_t wordCount)
{
  uint16_t readCountStatus = 0;

  while (wordCount)
  {
    if (SI1FIFOCSbits.SRFEMPTY != 1)
    {
      *pData++ = SRMWFDATA;
      wordCount--;
      readCountStatus++;
    } else
    {
      break;
    }
  }
  return readCountStatus;
}

uint16_t MASTER_Write(uint16_t *pData, uint16_t wordCount)
{
  uint16_t writeCountStatus = 0;

  while (wordCount)
  {
    if (SI1FIFOCSbits.SWFFULL != 1)
    {
      SWMRFDATA = *pData++;
      wordCount--;
      writeCountStatus++;
    } else
    {
      break;
    }
  }
  return writeCountStatus;
}

bool MASTER_ProtocolARead(ProtocolA_DATA *pData)
{
  bool status = false;
  if (MASTER_ProtocolAIsFull())
  {
    pData->ProtocolA[0] = SI1MBX0D;
    pData->ProtocolA[1] = SI1MBX1D;
    pData->ProtocolA[2] = SI1MBX2D;
    pData->ProtocolA[3] = SI1MBX3D;
    pData->ProtocolA[4] = SI1MBX4D;

    status = true;
  } else
  {
    status = false;
  }
  return status;
}

inline static bool MASTER_ProtocolAIsFull()
{
  return (SI1MBXSbits.DTRDYA);
}

inline static bool MASTER_ProtocolAIsEmpty()
{
  return (!SI1MBXSbits.DTRDYA);
}

bool MASTER_ProtocolBRead(ProtocolB_DATA *pData)
{
  bool status = false;
  if (MASTER_ProtocolBIsFull())
  {
    pData->ProtocolB[0] = SI1MBX5D;
    pData->ProtocolB[1] = SI1MBX6D;
    pData->ProtocolB[2] = SI1MBX7D;
    pData->ProtocolB[3] = SI1MBX8D;
    pData->ProtocolB[4] = SI1MBX9D;
    pData->ProtocolB[5] = SI1MBX10D;
    pData->ProtocolB[6] = SI1MBX11D;

    status = true;
  } else
  {
    status = false;
  }
  return status;
}

//void __attribute__((weak)) MASTER_ProtocolBCallBack(void)
//{
//  // Add your custom callback code here
////  //<<<<<<<<<<<<<<<<<<<<<<<<<
//  if (MASTER_ProtocolBRead((ProtocolB_DATA *) spi_vac_values.Data))
//  {
//    _LATD2 = 1;
//    dev_connect_numbers();
////    AC_Ctrl_Flags.value = (spi_vac_values.Data[6]);
//    _LATD2 = 0;
//  }
////  //<<<<<<<<<<<<<<<<<<<<<<<<<
//
//}

//void __attribute__((interrupt, no_auto_psv)) _MSIBInterrupt(void)
//{
//  MASTER_ProtocolBCallBack();
//  IFS8bits.MSIBIF = 0;
//}

inline static bool MASTER_ProtocolBIsFull()
{
  return (SI1MBXSbits.DTRDYB);
}

inline static bool MASTER_ProtocolBIsEmpty()
{
  return (!SI1MBXSbits.DTRDYB);
}







