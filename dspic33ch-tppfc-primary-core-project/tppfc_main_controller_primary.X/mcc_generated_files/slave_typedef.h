/**
  SLAVE Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    slave_typedef.h

  @Summary
    This is the generated header file for the SLAVE driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides common enumerations for driver for SLAVE.
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

#ifndef SLAVE_TYPEDEF_H
#define SLAVE_TYPEDEF_H

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
 Section: Data Type Definitions
*/
        
/**
  MSI Slave Status Enumeration

  @Summary
    Defines the status enumeration of Slave core.

  @Description
    This enumeration defines the different operating modes of MSI Slave core.
 */
typedef enum
{  
    SLAVE_SYSTEM_STATUS_NOT_IN_LOW_POWER_MODE,
    SLAVE_SYSTEM_STATUS_DEEP_SLEEP,
    SLAVE_SYSTEM_STATUS_SLEEP,
    SLAVE_SYSTEM_STATUS_IDLE,
    SLAVE_SYSTEM_STATUS_RUNNING,
    SLAVE_SYSTEM_STATUS_IN_RESET
} SLAVE_SYSTEM_STATUS;

/**
  MSI Slave Reset Cause Enumeration

  @Summary
    Defines the slave reset cause enumeration.

  @Description
    This enumeration defines the causes resulting in the reset of the Slave
    core.
 */
typedef enum
{
    SLAVE_RESET_CAUSE_WATCHDOG,
    SLAVE_RESET_CAUSE_UNSPECIFIED
} SLAVE_RESET_CAUSE;

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //SLAVE_TYPEDEF_H

