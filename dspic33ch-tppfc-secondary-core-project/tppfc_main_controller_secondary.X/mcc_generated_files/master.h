/**
  MASTER Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    master.h

  @Summary
    This is the generated header file for the MASTER driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for MASTER.
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

#ifndef MASTER_H
#define MASTER_H

/**
 Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
     
/**
 Section: Data Type Definitions
*/
        
/**
  MSI Master Status Enumeration

  @Summary
    Defines the status enumeration of MSI Master.

  @Description
    This defines the status enumeration for MSI Master.
 */
typedef enum
{
    MASTER_SYSTEM_STATUS_NOT_IN_LOW_POWER_MODE,
    MASTER_SYSTEM_STATUS_SLEEP,
    MASTER_SYSTEM_STATUS_IDLE,
    MASTER_SYSTEM_STATUS_RUNNING,
    MASTER_SYSTEM_STATUS_IN_RESET
} MASTER_SYSTEM_STATUS;

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
    Initializes the MSI slave.

  @Description
    This routine initializes the MSI slave.

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
    // initialize the MSI Slave 
    MASTER_Initialize();
 
    PROTOCOLA_DATA dataReceive;
    PROTOCOLB_DATA dataSend;
    uint16_t fifoSend[5], fifoReceive[5],sendCount = 5,receiveCount = 5;
    int i;
    
    //Wait for interrupt from master    
    while(!MASTER_IsInterruptRequested());
    MASTER_InterruptRequestAcknowledge();
    while(MASTER_IsInterruptRequested());
    MASTER_InterruptRequestAcknowledgeComplete();

    //Mailbox read    
    MASTER_PROTOCOLARead((PROTOCOLA_DATA*)&dataReceive);  
    for(i=0;i<5;i++)
    {
        dataSend.protocolB[i]=dataReceive.protocolA[i];
    }
    //Mailbox write 
    MASTER_PROTOCOLBWrite((PROTOCOLB_DATA*)&dataSend);
    
    //Issue interrupt to master
    MASTER_InterruptRequestGenerate();
    while(!MASTER_IsInterruptRequestAcknowledged());
    MASTER_InterruptRequestComplete();
    while(MASTER_IsInterruptRequestAcknowledged());

    //Wait for interrupt from master    
    while(!MASTER_IsInterruptRequested());
    MASTER_InterruptRequestAcknowledge();
    while(MASTER_IsInterruptRequested());
    MASTER_InterruptRequestAcknowledgeComplete();
    
    //Fifo read     
    MASTER_Read((uint16_t*)fifoReceive,receiveCount);  
    for(i=0;i<5;i++)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
    {
        fifoSend[i]=fifoReceive[i];
    }
    //Fifo write 
    MASTER_Write((uint16_t*)fifoSend,sendCount);

    //Issue interrupt to master
    MASTER_InterruptRequestGenerate();
    while(!MASTER_IsInterruptRequestAcknowledged());
    MASTER_InterruptRequestComplete();
    while(MASTER_IsInterruptRequestAcknowledged());

    while (1);  
    </code>
*/

void MASTER_Initialize(void);

/**
  @Summary
    Generates interrupt to master.

  @Description
    This routine generates interrupt to master.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
void MASTER_InterruptRequestGenerate(void);

/**
  @Summary
    Returns the status of interrupt request acknowledge from the Master.

  @Description
    This routine returns the status of interrupt request acknowledge from the 
    Master.

  @Preconditions
    None.

  @Returns
    True  - when Master has acknowledged Master MSI interrupt request.
    False - when Master has not acknowledged Master MSI interrupt request.

  @Param
    None.

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
        
bool MASTER_IsInterruptRequestAcknowledged(void);	

/**
  @Summary
    Clears interrupt to master.

  @Description
    This routine clears interrupt to master.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
        
void MASTER_InterruptRequestComplete(void);	

/**
  @Summary
    Returns the status of interrupt request from the Master.

  @Description
    This routine returns the status of interrupt request from the 
    Master.

  @Preconditions
    None.

  @Returns
    True  - when Master has issued interrupt to Slave.
    False - when Master has not issued interrupt to Slave.

  @Param
    None.

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
        
bool MASTER_IsInterruptRequested(void);	

/**
  @Summary
    Acknowledges interrupt received from Master.

  @Description
    This routine acknowledges interrupt received from Master.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
        
void MASTER_InterruptRequestAcknowledge(void);	

/**
  @Summary
    Clears acknowledge for interrupt received from Master.

  @Description
    This routine clears acknowledge for interrupt received from Master.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
        
void MASTER_InterruptRequestAcknowledgeComplete(void);

/**
  @Summary
    Returns Master system status.

  @Description
    This routine returns Master system status.

  @Preconditions
    None.

  @Returns
    MASTER_SYSTEM_STATUS: Enum which provides the status of Master.

  @Param
    None.

  @Example 
    <code>

    MASTER_SYSTEM_STATUS systemStatus;
    systemStatus = MASTER_SystemStatusGet();
 
    </code>      
*/
        
MASTER_SYSTEM_STATUS MASTER_SystemStatusGet(void);	

/**
  @Summary
    Reads FIFO data.

  @Description
    This routine reads FIFO data sent from the Master.

  @Preconditions
    None.

  @Returns
    Number of words read.

  @Param
    *pData      - Pointer to an array to store the read data
    wordCount   - Number of words to be read.

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
        
uint16_t MASTER_Read(uint16_t *pData, uint16_t wordCount);	

/**
  @Summary
    Transfer FIFO data.

  @Description
    This routine transfers FIFO data to Master.

  @Preconditions
    None.

  @Returns
    Number of words transferred.

  @Param
    *pData      - Pointer to an array which has data for transmission.
    wordCount   - Number of words to be transfer.

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
        
uint16_t MASTER_Write(uint16_t *pData, uint16_t wordCount);

/**
  @Summary
    Reads data from mailbox.

  @Description
    This routine reads data from mailbox.

  @Preconditions
    None.

  @Returns
    Returns a boolean.
    true   -    successful read
    false  -    unsuccessful read

  @Param
    *pData      - Pointer to an structure to store the read data

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
        
bool MASTER_ProtocolARead(ProtocolA_DATA *pData);

/**
  @Summary
    Reads data from mailbox.

  @Description
    This routine reads data from mailbox.

  @Preconditions
    None.

  @Returns
    Returns a boolean.
    true   -    successful read
    false  -    unsuccessful read

  @Param
    *pData      - Pointer to an structure to store the read data

  @Example 
    Refer to MASTER_Initialize() for an example    
*/
        
bool MASTER_ProtocolBRead(ProtocolB_DATA *pData);








#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //MASTER_H

