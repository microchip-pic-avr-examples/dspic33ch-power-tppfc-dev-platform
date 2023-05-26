/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CH512MP506S1
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v6.00
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

#include <p33CH512MP506S1.h>

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/tmr1.h"
#include "sources/driver/power_controller/drv_pwrctrl_app_misc_TPBLPFC.h"
#include "sources/devices/dev_TPBLPFC_typedef.h"
//#include "sources/PowerSmart/PowerSmart.h"
#include "sources/driver/power_controller/drv_usersetup_TPBLPFC.h"
#include "main.h"

/*******************************************************************************
 * @fn         int main
 * @brief      MAIN with 100us scheduler task 
 * @param      none
 * @return     1
 * @details    100us easy performance optimized scheduler
 *             with peripheral initialization
 *             with power controller state machine to run the PFC in different 
 *             modes based on the configuration
 *******************************************************************************/

int main(void)
{
  // initialize the device MCC based
  SYSTEM_Initialize();
  Init_pwr_ctrl();
  Drv_PwrCtrl_TPBLPFC_Init();

  //<<START>> Timer 1 for 100us task for state machine
  TMR1_Start();

  //<<<<<<<< Mode set by "11kW Totem-Pole PFC" Setup-Suite --------------------- 
#if defined SinglePhase1 && defined OuterVloop && !defined DualPhase1_3 
  PFC_Flags.bits.AC_PFC_1_PH = 1;
#endif

#if defined SinglePhase1 && !defined OuterVloop && !defined Reverse 
  PFC_Flags.bits.AC_AVGCM_no_VMC_1_PH = 1;
#endif

#if defined SinglePhase1 && defined Reverse  
  PFC_Flags.bits.AC_AVGCM_no_VMC_1_PH_reverse = 1;
#endif

#if defined ThreePhase && defined OuterVloop  
  PFC_Flags.bits.AC_PFC_3_PH = 1;
#endif

//#if defined ThreePhase && !defined OuterVloop  
//  PFC_Flags.bits.AC_PFC_3_PH = 1;
//  PFC_Flags.bits.AC_AVGCM_no_VMC_1_PH = 1;
//#endif

#if defined ThreePhase && defined Reverse  
  PFC_Flags.bits.AC_AVGCM_no_VMC_3_PH_reverse = 1;
#endif

#if defined SinglePhase1 && defined DualPhase1_3  
  PFC_Flags.bits.AC_PFC_2PH_1_PH = 1;
#endif
  //<<<<<<<< Mode set END ------------------------------------------------------

  while (1)
  {
    ////    __builtin_btg(&LATD, 13);
    
    //<< end 100us scheduler 
    if (IFS0bits.T1IF)
    {
      Tasks_100us();
      
      IFS0bits.T1IF = 0;

    } 

  }
  return 1;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 End of File
 */

