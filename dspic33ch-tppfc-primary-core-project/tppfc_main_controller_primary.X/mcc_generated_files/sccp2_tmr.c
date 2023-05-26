/**
  SCCP2 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    sccp2.c

  @Summary
    This is the generated driver implementation file for the SCCP2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for SCCP2. 
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

/**
  Section: Included Files
*/

#include "sccp2_tmr.h"

/**
  Section: Data Type Definitions
*/

/**
  SCCP2 Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

*/
typedef struct _SCCP2_TMR_OBJ_STRUCT
{

    /* Timer Elapsed */
    bool                                                    primaryTimer16Elapsed;
    bool                                                    secondaryTimer16Elapsed;
    bool                                                    Timer32Elapsed;
} SCCP2_TMR_OBJ;

static SCCP2_TMR_OBJ sccp2_timer_obj;
void SCCP2_TMR_Initialize(void)
{
    // CCPON disabled; MOD 16-Bit/32-Bit Timer; CCSEL disabled; CCPSIDL disabled; T32 16 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL FOSC/2; TMRSYNC disabled; 
    CCP2CON1L = (0x00 & 0x7FFF); //Disabling CCPON bit
    //RTRGEN disabled; ALTSYNC disabled; ONESHOT disabled; TRIGEN disabled; OPS Each Time Base Period Match; SYNC None; OPSSRC Timer Interrupt Event; 
    CCP2CON1H = 0x00;
    //ASDGM disabled; SSDG disabled; ASDG 0; PWMRSEN disabled; 
    CCP2CON2L = 0x00;
    //ICGSM Level-Sensitive mode; ICSEL IC2; AUXOUT Disabled; OCAEN disabled; OENSYNC disabled; 
    CCP2CON2H = 0x00;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP2CON3H = 0x00;
    //ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; ICGARM disabled; TRCLR disabled; 
    CCP2STATL = 0x00;
    //TMR 0; 
    CCP2TMRL = 0x00;
    //TMR 0; 
    CCP2TMRH = 0x00;
    //PR 3600; 
    CCP2PRL = 0xE10;
    //PR 0; 
    CCP2PRH = 0x00;
    //CMP 0; 
    CCP2RA = 0x00;
    //CMP 0; 
    CCP2RB = 0x00;
    //BUF 0; 
    CCP2BUFL = 0x00;
    //BUF 0; 
    CCP2BUFH = 0x00;


    IFS1bits.CCP2IF = 0;

    IFS1bits.CCT2IF = 0;
      


}

void SCCP2_TMR_Start( void )
{
    /* Reset the status information */
    sccp2_timer_obj.primaryTimer16Elapsed = false;
    sccp2_timer_obj.secondaryTimer16Elapsed = false;
    sccp2_timer_obj.Timer32Elapsed = false;

    /* Start the Timer */
    CCP2CON1Lbits.CCPON = true;
}

void SCCP2_TMR_Stop( void )
{
    /* Stop the Timer */
    CCP2CON1Lbits.CCPON = false;
}

void __attribute__ ((weak)) SCCP2_TMR_PrimaryTimerCallBack(void)
{
    // Add your custom callback code here
}

void SCCP2_TMR_PrimaryTimerTasks( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if(IFS1bits.CCT2IF)
    {
		// SCCP2 Primary Timer callback function 
		SCCP2_TMR_PrimaryTimerCallBack();
		
        sccp2_timer_obj.primaryTimer16Elapsed = true;
        IFS1bits.CCT2IF = 0;
    }
}


void __attribute__ ((weak)) SCCP2_TMR_SecondaryTimerCallBack(void)
{
    // Add your custom callback code here
}

void SCCP2_TMR_SecondaryTimerTasks( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if(IFS1bits.CCP2IF)
    {
		// SCCP2 Secondary Timer callback function 
		SCCP2_TMR_SecondaryTimerCallBack();
        sccp2_timer_obj.secondaryTimer16Elapsed = true;
        IFS1bits.CCP2IF = 0;
    }
}

void SCCP2_TMR_Period16BitPrimarySet( uint16_t value )
{
    /* Update the counter values */
    CCP2PRL = value;

    /* Reset the status information */
    sccp2_timer_obj.primaryTimer16Elapsed = false;
}

void SCCP2_TMR_Period16BitSecondarySet( uint16_t value )
{
    /* Update the counter values */
    CCP2PRH = value;

    /* Reset the status information */
    sccp2_timer_obj.secondaryTimer16Elapsed = false;
}

uint16_t SCCP2_TMR_Period16BitPrimaryGet( void )
{
    return( CCP2PRL );
}
uint16_t SCCP2_TMR_Period16BitSecondaryGet( void )
{
    return( CCP2PRH );
}

void SCCP2_TMR_Counter16BitPrimarySet ( uint16_t value )
{
    /* Update the counter values */
    CCP2PRL = value;
    /* Reset the status information */
    sccp2_timer_obj.primaryTimer16Elapsed = false;
}

void SCCP2_TMR_Counter16BitSecondarySet ( uint16_t value )
{
    /* Update the counter values */
    CCP2PRH = value;
    /* Reset the status information */
    sccp2_timer_obj.secondaryTimer16Elapsed = false;
}

uint16_t SCCP2_TMR_Counter16BitPrimaryGet( void )
{
    return( CCP2TMRL );
}

uint16_t SCCP2_TMR_Counter16BitSecondaryGet( void )
{
    return( CCP2TMRH );
}

bool SCCP2_TMR_PrimaryTimer16ElapsedThenClear(void)
{
    bool status;
    
    status = sccp2_timer_obj.primaryTimer16Elapsed ;
    
    if(status == true)
    {
        sccp2_timer_obj.primaryTimer16Elapsed = false;
    }
    return status;
}

bool SCCP2_TMR_SecondaryTimer16ElapsedThenClear(void)
{
    bool status;
    
    status = sccp2_timer_obj.secondaryTimer16Elapsed ;
    
    if(status == true)
    {
        sccp2_timer_obj.secondaryTimer16Elapsed = false;
    }
    return status;
}

/**
 End of File
*/