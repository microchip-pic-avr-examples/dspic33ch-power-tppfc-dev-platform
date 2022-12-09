/**
  SLAVE1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    slave1.h

  @Summary
    This is the generated header file for the SLAVE1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for SLAVE1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CH512MP506
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

#ifndef SLAVE1_H
#define SLAVE1_H

/**
 Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "slave_typedef.h"

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Data Type Definitions
*/

/** 
   ProtocolA data structure

  @Summary
    Defines the data structure for ProtocolA.

  @Description
    This structure defines the data for ProtocolA.
*/

typedef struct ProtocolA_DATA_STRUCT
{
    uint16_t    ProtocolA[5];

} ProtocolA_DATA; 
/** 
   ProtocolB data structure

  @Summary
    Defines the data structure for ProtocolB.

  @Description
    This structure defines the data for ProtocolB.
*/

typedef struct ProtocolB_DATA_STRUCT
{
    uint16_t    ProtocolB[7];

} ProtocolB_DATA; 
        
/**
 Section: Interface Routines
*/

/**
  @Summary
    Initializes the MSI master.

  @Description
    This routine initializes the MSI driver.

    This routine must be called before any other MSI routine is called.
    This routine should only be called once during system initialization.
 
  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // initialize the MSI Master
    SLAVE1_Initialize();
 
    //Program and enable slave
    _program_slave(1,0,slave); 
    SLAVE1_Start();
    
    PROTOCOLA_DATA dataSend;
    PROTOCOLB_DATA dataReceive;
    uint16_t fifoSend[5], fifoReceive[5],sendCount = 5,receiveCount = 5;
    int i,statusMailbox=true,statusFifo=true;
    
    for(i=0;i<5;i++)
    {
        dataSend.protocolA[i]=i;
        dataReceive.protocolB[i]=0;
        fifoSend[i]=i;
        fifoReceive[i]=0;
    }

    //Mailbox write
    SLAVE1_PROTOCOLAWrite((PROTOCOLA_DATA*)&dataSend);
    
    //Issue interrupt to slave
    SLAVE1_InterruptRequestGenerate();
    while(!SLAVE1_IsInterruptRequestAcknowledged());
    SLAVE1_InterruptRequestComplete();
    while(SLAVE1_IsInterruptRequestAcknowledged());

    //Wait for interrupt from slave
    while(!SLAVE1_IsInterruptRequested());
    SLAVE1_InterruptRequestAcknowledge();
    while(SLAVE1_IsInterruptRequested());
    SLAVE1_InterruptRequestAcknowledgeComplete();
    
    //Mailbox read
    SLAVE1_PROTOCOLBRead((PROTOCOLB_DATA*)&dataReceive);
    
    //Fifo write
    SLAVE1_Write((uint16_t*)fifoSend, sendCount);

    //Issue interrupt to slave
    SLAVE1_InterruptRequestGenerate();
    while(!SLAVE1_IsInterruptRequestAcknowledged());
    SLAVE1_InterruptRequestComplete();
    while(SLAVE1_IsInterruptRequestAcknowledged());

    //Wait for interrupt from slave
    while(!SLAVE1_IsInterruptRequested());
    SLAVE1_InterruptRequestAcknowledge();
    while(SLAVE1_IsInterruptRequested());
    SLAVE1_InterruptRequestAcknowledgeComplete();

    //Fifo read  
    SLAVE1_Read((uint16_t*)fifoReceive, receiveCount);

    //Verify data sent and received
    for(i=0;i<5;i++)
    {
        if(dataSend.protocolA[i] != dataReceive.protocolB[i])
        {
            statusMailbox = false;
        }
        if(fifoSend[i] != fifoReceive[i])
        {
            statusFifo = false;
        }
    }

    while (1);  
    </code>
*/

void SLAVE1_Initialize(void);

/**
  @Summary
    Enables slave.

  @Description
    This routine enables slave core.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
void SLAVE1_Start(void);

/**
  @Summary
    Program slave.

  @Description
    This routine programs slave core.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to SLAVE1_Initialize() for an example     
*/
        
void SLAVE1_Program(void);

/**
  @Summary
    Generates interrupt to SLAVE1.

  @Description
    This routine generates interrupt to SLAVE1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
void SLAVE1_InterruptRequestGenerate(void);

/**
  @Summary
    Returns the status of interrupt request acknowledge from the SLAVE1.

  @Description
    This routine returns the status of interrupt request acknowledge from the 
    SLAVE1.

  @Preconditions
    None.

  @Returns
    True  - when SLAVE1 has acknowledged Master MSI interrupt request.
    False - when SLAVE1 has not acknowledged Master MSI interrupt request.

  @Param
    None.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
bool SLAVE1_IsInterruptRequestAcknowledged(void);	

/**
  @Summary
    Clears interrupt to SLAVE1.

  @Description
    This routine clears interrupt to SLAVE1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
void SLAVE1_InterruptRequestComplete(void);	

/**
  @Summary
    Returns the status of interrupt request from the SLAVE1.

  @Description
    This routine returns the status of interrupt request from the 
    SLAVE1.

  @Preconditions
    None.

  @Returns
    True  - when SLAVE1 has issued interrupt to Master.
    False - when SLAVE1 has not issued interrupt to Master.

  @Param
    None.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
bool SLAVE1_IsInterruptRequested(void);	

/**
  @Summary
    Acknowledges interrupt received from SLAVE1.

  @Description
    This routine acknowledges interrupt received from SLAVE1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
void SLAVE1_InterruptRequestAcknowledge(void);	

/**
  @Summary
    Clears acknowledge for interrupt received from SLAVE1.

  @Description
    This routine clears acknowledge for interrupt received from SLAVE1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
void SLAVE1_InterruptRequestAcknowledgeComplete(void);

/**
  @Summary
    Returns the cause for SLAVE1 reset.

  @Description
    This routine returns the cause for SLAVE1 reset.

  @Preconditions
    None.

  @Returns
    SLAVE_RESET_CAUSE: Enum which provides the cause for SLAVE1 reset.

  @Param
    None.

  @Example 
    <code>

    SLAVE_RESET_CAUSE resetCause;
    resetCause = SLAVE1_GetResetCause(); 
 
    </code>   
 
*/

SLAVE_RESET_CAUSE SLAVE1_GetResetCause(void);	

/**
  @Summary
    Clears the cause for SLAVE1 reset.

  @Description
    This routine clears the cause for SLAVE1 reset.

  @Preconditions
    SLAVE_RESET_CAUSE: Enum which provides the cause for SLAVE1 reset.

  @Returns
    None.

  @Param
    None.

  @Example 
    <code>

    SLAVE_RESET_CAUSE resetCause;
    resetCause = SLAVE1_GetResetCause();
    SLAVE1_ResetCauseClear(resetCause); 
 
    </code>      
*/
        
void SLAVE1_ResetCauseClear(SLAVE_RESET_CAUSE resetCause);	

/**
  @Summary
    Returns SLAVE1 system status.

  @Description
    This routine returns SLAVE1 system status.

  @Preconditions
    None.

  @Returns
    SLAVE_SYSTEM_STATUS: Enum which provides the status of SLAVE1.

  @Param
    None.

  @Example 
    <code>

    SLAVE_SYSTEM_STATUS systemStatus;
    systemStatus = SLAVE1_SystemStatusGet();
 
    </code>     
*/
        
SLAVE_SYSTEM_STATUS SLAVE1_SystemStatusGet(void);	

/**
  @Summary
    Reads FIFO data.

  @Description
    This routine reads FIFO data sent from the SLAVE1.

  @Preconditions
    SLAVE1_Initialize() should be called before calling this routine.

  @Returns
    Number of words read.

  @Param
    *pData      - Pointer to an array to store the read data
    wordCount   - Number of words to be read.   

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
uint16_t SLAVE1_Read(uint16_t *pData, uint16_t wordCount);	

/**
  @Summary
    Transfer FIFO data.

  @Description
    This routine transfers FIFO data to SLAVE1.

  @Preconditions
    SLAVE1_Initialize() should be called before calling this routine.

  @Returns
    Number of words transferred.

  @Param
    *pData      - Pointer to an array which has data for transmission.
    wordCount   - Number of words to be transfer.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
uint16_t SLAVE1_Write(uint16_t *pData, uint16_t wordCount);

/**
  @Summary
    Writes data to mailbox.

  @Description
    This routine writes data to mailbox.

  @Preconditions
    None.

  @Returns
    Returns a boolean.
    true   -    successful write
    false  -    unsuccessful write

  @Param
    *pData      - Pointer to an structure which has data for transmission.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
bool SLAVE1_ProtocolAWrite(ProtocolA_DATA *pData);


/**
  @Summary
    Writes data to mailbox.

  @Description
    This routine writes data to mailbox.

  @Preconditions
    None.

  @Returns
    Returns a boolean.
    true   -    successful write
    false  -    unsuccessful write

  @Param
    *pData      - Pointer to an structure which has data for transmission.

  @Example 
    Refer to SLAVE1_Initialize() for an example    
*/
        
bool SLAVE1_ProtocolBWrite(ProtocolB_DATA *pData);









#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //SLAVE1_H

