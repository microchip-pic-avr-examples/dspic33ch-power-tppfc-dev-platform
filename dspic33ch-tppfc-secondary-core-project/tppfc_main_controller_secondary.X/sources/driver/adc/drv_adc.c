/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    drv_adc.c

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
#include <stdlib.h>
#include "drv_adc.h"
#include "../power_controller/drv_pwrctrl_app_misc_TPBLPFC.h"
#include "../../devices/dev_TPBLPFC_numberconnection_typedef.h"

#include "../../devices/dev_TPBLPFC_typedef.h"
#include "../power_controller/drv_pwrctrl_app_TPBLPFC.h"
#include "../power_controller/drv_usersetup_TPBLPFC.h"

#include "../../../mcc_generated_files/master.h"
#include "../../../mcc_generated_files/interrupt_manager.h"
#include "../../../mcc_generated_files/pin_manager.h"
#include "../../../sources/driver/power_controller/drv_controller_TPBLPFC.h"

//------------------------------------------------------------------------------
// << ADCcore 0 interrupt every PWM period, 100kHz
// check for current sensor: Allegro or LEM --> different offset
//------------------------------------------------------------------------------

void __attribute__((__interrupt__, auto_psv)) _ADCAN0Interrupt(void)
{
  TP4_DPPIM_RD13_SetHigh();
 
  ACmonitorTrigger_SetHigh();
  
  //<< Vout prestart next shared core input which is Vout
  //<< shared core I3 input is ready because of latency from trigger to here
  //<< from min. 500ns 
  ADCON3Lbits.CNVCHSEL = 10; // change ADC channel
  ADCON3Lbits.CNVRTCH = 1; // trigger conversion
  
  //<< I1
  Phase_Values_PH1.Phase_Current.Raw = (int16_t) ADCBUF0;
  Phase_Values_PH1.Phase_Current.Rectified = abs((int16_t)(Phase_Values_PH1.Phase_Current.Raw - Phase_Values_PH1.Phase_Current.Offset)); //phase voltage - offset=VCC/2
 
  ACmonitorTrigger_SetLow();
  
  if ((Phase_Values_PH1.Phase_Current.Rectified > IinOC) && (pwr_ctrl_state > PCS_RELAYON)) //new 06.09.2021
  {
    PFC_Flags.bits.OC_PH1 = 1;
    PFC_Flags.bits.Run = 0;
    PFC_Flags.bits.Stop = 1;

    Drv_PwrCtrl_TPBLPFC_Stop();
  }

  //<< I2
  Phase_Values_PH2.Phase_Current.Raw = ADCBUF1; //IL2
  Phase_Values_PH2.Phase_Current.Rectified = abs((int16_t)(Phase_Values_PH2.Phase_Current.Raw - Phase_Values_PH2.Phase_Current.Offset));

  if ((Phase_Values_PH2.Phase_Current.Rectified > IinOC) && (pwr_ctrl_state > PCS_RELAYON)) //new 06.09.2021
  {
    PFC_Flags.bits.OC_PH2 = 1;
    PFC_Flags.bits.Run = 0;
    PFC_Flags.bits.Stop = 1;

    Drv_PwrCtrl_TPBLPFC_Stop();
   }
 
  //<< shared core I3 input is ready, triggered by TRIGA
  Phase_Values_PH3.Phase_Current.Raw = ADCBUF17; //IL3
  Phase_Values_PH3.Phase_Current.Rectified = abs((int16_t)(Phase_Values_PH3.Phase_Current.Raw - Phase_Values_PH3.Phase_Current.Offset));
  
  if ((Phase_Values_PH3.Phase_Current.Rectified > IinOC) && (pwr_ctrl_state > PCS_RELAYON)) //new 06.09.2021
  {
    PFC_Flags.bits.OC_PH3 = 1;
    PFC_Flags.bits.Run = 0;
    PFC_Flags.bits.Stop = 1;

    Drv_PwrCtrl_TPBLPFC_Stop();
  }

   //<< shared core Vout input is ready because of latency from trigger to here
   //<< from min. 450ns (measured)), AD is 270ns
   Vout_Control.Vout.Raw = ADCBUF10; //VOUT
   
  ADCON3Lbits.CNVCHSEL = 17; // change ADC channel, triggered by TRIGA
  
  if ((Vout_Control.Vout.Raw > VoutOV)) //new 29.09.2021
  {
    PFC_Flags.bits.OV_Vout = 1;
    PFC_Flags.bits.Run = 0;
    PFC_Flags.bits.Stop = 1;

    Drv_PwrCtrl_TPBLPFC_Stop();
  }

  //<< get AC data
  if (MASTER_ProtocolBRead((ProtocolB_DATA *) spi_vac_values.Data))
  {
//    TP39_RD2_SetHigh();
    dev_connect_numbers();
    spi_vac_values.DataReceivedOK = 1;
//    TP39_RD2_SetLow();
  }

  //<< PFC handler
  PWM_handler_PH123();

  IFS5bits.ADCAN0IF = 0; //clear the channel_ANA0 interrupt flag

  TP4_DPPIM_RD13_SetLow();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 End of File
 */

