/**
  SCCP1 Generated Driver API Header File 

  @Company
    Microchip Technology Inc.

  @File Name
    sccp1.h

  @Summary
    This is the generated header file for the SCCP1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for SCCP1. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CH512MP506
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
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

#ifndef _SCCP1_TMR_H
#define _SCCP1_TMR_H

/**
  Section: Included Files
*/

#include <xc.h> 
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
/**
  Section: Interface Routines
*/
/**
  @Summary
    Initializes hardware and data for the given instance of the TMR module

  @Description
    This routine initializes hardware for the instance of the TMR module,
    using the hardware initialization given data.  It also initializes all
    necessary internal data.

  @Param
    None.

  @Returns
    None

  @Comment

 
  @Example
    <code>
    bool statusTimer1;
    uint16_t period;
    uint16_t value;

    period = 0x20;

    SCCP1_TMR_Initializer();

    SCCP1_TMR_Period16BitSet(period);

    if((value = SCCP1_TMR_Period16BitGet())== period)
    {
        SCCP1_TMR_Start();
    }

    while(1)
    {
        SCCP1_TMR_Tasks();
        if( (statusTimer1 = SCCP1_TMR_IsElapsed()) == true)
        {
            SCCP1_TMR_Stop();
        }
    }
    </code>
*/
void SCCP1_TMR_Initialize (void);

/**
  @Summary
    Starts the TMR

  @Description
    This routine starts the TMR

  @Param
    None.

  @Returns
    None

  @Example
    Refer to the example of SCCP1_Initializer();
*/

void SCCP1_TMR_Start( void );
/**
  @Summary
    Stops the TMR

  @Description
    This routine stops the TMR

  @Param
    None.

  @Returns
    None

  @Example
    Refer to the example of SCCP1_Initializer();
*/

void SCCP1_TMR_Stop( void );

/**
  @Summary
    Callback for SCCP1 Primary Timer.

  @Description
    This routine is callback for SCCP1 Primary Timer

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to SCCP1_Initialize(); for an example
*/
void SCCP1_TMR_PrimaryTimerCallBack(void);

/**
  void SCCP1_TMR_PrimaryTimerTasks( void )
 
  @Summary
    Maintains the driver's primary timer state machine in a polled manner

  @Description
    This routine is used to maintain the driver's internal primary timer state
    machine.This routine is called when the state of the primary timer needs to be
    maintained in a polled manner.

  @Param
    None.

  @Returns
    None
 */
void SCCP1_TMR_PrimaryTimerTasks( void );

/**
  @Summary
    Callback for SCCP1 Secondary Timer.

  @Description
    This routine is callback for SCCP1 Secondary Timer

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to SCCP1_Initialize(); for an example
*/
void SCCP1_TMR_SecondaryTimerCallBack(void);

/**
    void SCCP1_TMR_SecondaryTimerTasks ( void )

  @Summary
    Maintains the driver's secondary timer state machine in a polled manner

  @Description
    This routine is used to maintain the driver's internal secondary timer state
    machine.This routine is called when the state of the secondary timer needs to be
    maintained in a polled manner.

  @Param
    None.

  @Returns
    None

*/
void SCCP1_TMR_SecondaryTimerTasks( void );

/**
  @Summary
    Updates 16-bit mccp value

  @Description
    This routine updates 16-bit mccp value

  @Param
    None.

  @Returns
    None

  @Example
    Refer to the example of SCCP1_Initializer();
*/

void SCCP1_TMR_Period16BitPrimarySet( uint16_t value );
/**
  @Summary
    Updates 16-bit mccp value

  @Description
    This routine updates 16-bit mccp value

  @Param
    None.

  @Returns
    None

  @Example
    Refer to the example of SCCP1_TMR_Initializer();
*/
void SCCP1_TMR_Period16BitSecondarySet( uint16_t value );
/**
  @Summary
    Provides the mccp 16-bit period value

  @Description
    This routine provides the mccp 16-bit period value

  @Param
    None.

  @Returns
    Timer 16-bit period value

  @Example
    Refer to the example of SCCP1_TMR_Initializer();
*/

uint16_t SCCP1_TMR_Period16BitPrimaryGet( void );
/**
  @Summary
    Provides the mccp 16-bit period value

  @Description
    This routine provides the mccp 16-bit period value

  @Param
    None.

  @Returns
    Timer 16-bit period value

  @Example
    Refer to the example of SCCP1_TMR_Initializer();
*/
uint16_t SCCP1_TMR_Period16BitSecondaryGet( void );
/**
  @Summary
    Updates the mccp's 16-bit value

  @Description
    This routine updates the mccp's 16-bit value

  @Param
    None.

  @Returns
    None  

  @Example
    <code>
    uint16_t value=0xF0F0;

    SCCP1_TMR_Counter16BitSet(value));

    while(1)
    {
        SCCP1_TMR_Tasks();
        if( (value == SCCP1_TMR_Counter16BitGet()))
        {
            SCCP1_TMR_Stop();
        }
    }
    </code>
*/

void SCCP1_TMR_Counter16BitPrimarySet ( uint16_t value );
/**
  @Summary
    Updates the mccp's 16-bit value

  @Description
    This routine updates the mccp's 16-bit value

  @Param
    None.

  @Returns
    None  

  @Example
    <code>
    uint16_t value=0xF0F0;

    SCCP1_TMR_Counter16BitSet(value));

    while(1)
    {
        SCCP1_TMR_Tasks();
        if( (value == SCCP1_TMR_Counter16BitGet()))
        {
            SCCP1_TMR_Stop();
        }
    }
    </code>
*/

void SCCP1_TMR_Counter16BitSecondarySet( uint16_t value );
/**
  @Summary
    Provides 16-bit current counter value

  @Description
    This routine provides 16-bit current counter value

  @Param
    None.

  @Returns
    16-bit current counter value

  @Example
    Refer to the example of SCCP1_TMR_Counter16BitSet();
*/

uint16_t SCCP1_TMR_Counter16BitPrimaryGet( void );
/**
  @Summary
    Provides 16-bit current counter value

  @Description
    This routine provides 16-bit current counter value

  @Param
    None.

  @Returns
    16-bit current counter value

  @Example
    Refer to the example of SCCP1_TMR_Counter16BitSet();
*/
uint16_t SCCP1_TMR_Counter16BitSecondaryGet( void );
/**
  @Summary
    Returns the elapsed status of the mccp

  @Description
    This routine returns the elapsed status of the mccp

  @Param
    None.

  @Returns
    bool - Elapsed status of the mccp.

  @Example
    Refer to the example of SCCP1_TMR_Initializer();
*/

bool SCCP1_TMR_PrimaryTimer16ElapsedThenClear(void);
/**
  @Summary
    Returns the elapsed status of the mccp

  @Description
    This routine returns the elapsed status of the mccp

  @Param
    None.

  @Returns
    bool - Elapsed status of the mccp.

  @Example
    Refer to the example of SCCP1_TMR_Initializer();
*/
bool SCCP1_TMR_SecondaryTimer16ElapsedThenClear(void);


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_SCCP1_H

/**
 End of File
*/
