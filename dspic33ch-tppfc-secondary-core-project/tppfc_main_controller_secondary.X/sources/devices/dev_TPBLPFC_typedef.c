/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    dev_TPBLPFC_typedef.c

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

#include "dev_TPBLPFC_typedef.h"
#include "../driver/power_controller/drv_usersetup_TPBLPFC.h"

//------------------------------------------------------------------------------

PHASE_VALUES_t Phase_Values_PH1, Phase_Values_PH2, Phase_Values_PH3 ;
VMC_VALUES_t Vout_Control;
PFC_FLAGS_t PFC_Flags;

PWR_CTRL_STATE_e pwr_ctrl_state = 1; //1 = PCS_INIT

SPI_Data_Handling spi_vac_values;

//------------------------------------------------------------------------------
//<< 
//------------------------------------------------------------------------------

void Init_pwr_ctrl (void)
{
  //Reference set potentiometer ------------------------------------------------
  Vout_Control.Poti.FilterCounter     = 0;
  Vout_Control.Poti.Filtered          = 0;
  Vout_Control.Poti.Raw               = 0;
  Vout_Control.Poti.Rectified         = 0;
  Vout_Control.Poti.Rectified_Shift   = 0;
  Vout_Control.Poti.Vin_div_Averaged2 = 0;
  
  //Vout -----------------------------------------------------------------------
  Vout_Control.Vout.FilterCounter     = 0;
  Vout_Control.Vout.Filtered          = 0;
  Vout_Control.Vout.Raw               = 0;
  Vout_Control.Vout.Rectified         = 0;
  Vout_Control.Vout.Rectified_Shift   = 0;
  Vout_Control.Vout.Vin_div_Averaged2 = 0;
  Vout_Control.Reference.Voltage_Loop_Output = 0;
  Vout_Control.Reference.Voltage_Loop_Slowdown_Counter = 0;
  
  //Control reference ----------------------------------------------------------
  Vout_Control.Reference.Reference_Set      = VoutRef; //preset reference to configured value
  Vout_Control.Reference.Reference_Internal = 0;
  
  //PH1 voltages ---------------------------------------------------------------
  Phase_Values_PH1.Phase_Voltage.FilterCounter      = 0;
  Phase_Values_PH1.Phase_Voltage.Filtered           = 0;
  Phase_Values_PH1.Phase_Voltage.Raw                = 0;
  Phase_Values_PH1.Phase_Voltage.Rectified          = 0;
  Phase_Values_PH1.Phase_Voltage.Rectified_Shift    = 0;
  Phase_Values_PH1.Phase_Voltage.Vin_div_Averaged2  = 0;
  
  //PH1 currents ---------------------------------------------------------------
  Phase_Values_PH1.Phase_Current.FilterCounter      = 0;
  Phase_Values_PH1.Phase_Current.Filtered           = 0;
  Phase_Values_PH1.Phase_Current.Raw                = 0;
  Phase_Values_PH1.Phase_Current.Rectified          = 0;
  Phase_Values_PH1.Phase_Current.Rectified_Shift    = 0;
  Phase_Values_PH1.Phase_Current.Vin_div_Averaged2  = 0;
  
  //PH1 flags ------------------------------------------------------------------
  Phase_Values_PH1.Control_Status_Flags.bits.Zero_Cross_Range          = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.Soft_Start_Zero_Cross     = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity              = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity_last         = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.Relay                     = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.Stop                      = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.Fault                     = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity_Changed      = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity_Changed_last = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.VAC_OK                    = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.CCM                       = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.VDC_Input_Voltage         = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.VACdrop                   = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.nu2                       = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.nu3                       = 0;
  Phase_Values_PH1.Control_Status_Flags.bits.Reference_Changed         = 0;
  
  //PH1 controller numbers -----------------------------------------------------
  Phase_Values_PH1.Controller_Values.PWM_Counter                    = 0;
  Phase_Values_PH1.Controller_Values.Duty_Cycle_Set_Value           = 0;
  Phase_Values_PH1.Controller_Values.CCM_Counter                    = 0;
  Phase_Values_PH1.Controller_Values.DFF_Value                      = 0;
  Phase_Values_PH1.Controller_Values.IAC_Reference_l                = 0;
  Phase_Values_PH1.Controller_Values.IAC_Reference                  = 0;
//  Phase_Values_PH1.Controller_Values.Voltage_Loop_Output            = 0;
//  Phase_Values_PH1.Controller_Values.Voltage_Loop_Slowdown_Counter  = 0;
  //----------------------------------------------------------------------------
  
  //PH2 voltages ---------------------------------------------------------------
  Phase_Values_PH2.Phase_Voltage.FilterCounter      = 0;
  Phase_Values_PH2.Phase_Voltage.Filtered           = 0;
  Phase_Values_PH2.Phase_Voltage.Raw                = 0;
  Phase_Values_PH2.Phase_Voltage.Rectified          = 0;
  Phase_Values_PH2.Phase_Voltage.Rectified_Shift    = 0;
  Phase_Values_PH2.Phase_Voltage.Vin_div_Averaged2  = 0;
  
  //PH2 currents ---------------------------------------------------------------
  Phase_Values_PH2.Phase_Current.FilterCounter      = 0;
  Phase_Values_PH2.Phase_Current.Filtered           = 0;
  Phase_Values_PH2.Phase_Current.Raw                = 0;
  Phase_Values_PH2.Phase_Current.Rectified          = 0;
  Phase_Values_PH2.Phase_Current.Rectified_Shift    = 0;
  Phase_Values_PH2.Phase_Current.Vin_div_Averaged2  = 0;
  
  //PH2 flags ------------------------------------------------------------------
  Phase_Values_PH2.Control_Status_Flags.bits.Zero_Cross_Range          = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.Soft_Start_Zero_Cross     = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity              = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity_last         = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.Relay                     = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.Stop                      = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.Fault                     = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity_Changed      = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity_Changed_last = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.VAC_OK                    = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.CCM                       = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.VDC_Input_Voltage         = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.VACdrop                   = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.nu2                       = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.nu3                       = 0;
  Phase_Values_PH2.Control_Status_Flags.bits.Reference_Changed         = 0;
  
  //PH2 controller numbers -----------------------------------------------------
  Phase_Values_PH2.Controller_Values.PWM_Counter                    = 0;
  Phase_Values_PH2.Controller_Values.Duty_Cycle_Set_Value           = 0;
  Phase_Values_PH2.Controller_Values.CCM_Counter                    = 0;
  Phase_Values_PH2.Controller_Values.DFF_Value                      = 0;
  Phase_Values_PH2.Controller_Values.IAC_Reference_l                = 0;
  Phase_Values_PH2.Controller_Values.IAC_Reference                  = 0;
//  Phase_Values_PH2.Controller_Values.Voltage_Loop_Output            = 0;
//  Phase_Values_PH2.Controller_Values.Voltage_Loop_Slowdown_Counter  = 0;
  //----------------------------------------------------------------------------

  //PH3 voltages ---------------------------------------------------------------
  Phase_Values_PH3.Phase_Voltage.FilterCounter      = 0;
  Phase_Values_PH3.Phase_Voltage.Filtered           = 0;
  Phase_Values_PH3.Phase_Voltage.Raw                = 0;
  Phase_Values_PH3.Phase_Voltage.Rectified          = 0;
  Phase_Values_PH3.Phase_Voltage.Rectified_Shift    = 0;
  Phase_Values_PH3.Phase_Voltage.Vin_div_Averaged2  = 0;
  
  //PH3 currents ---------------------------------------------------------------
  Phase_Values_PH3.Phase_Current.FilterCounter      = 0;
  Phase_Values_PH3.Phase_Current.Filtered           = 0;
  Phase_Values_PH3.Phase_Current.Raw                = 0;
  Phase_Values_PH3.Phase_Current.Rectified          = 0;
  Phase_Values_PH3.Phase_Current.Rectified_Shift    = 0;
  Phase_Values_PH3.Phase_Current.Vin_div_Averaged2  = 0;
  
  //PH3 flags ------------------------------------------------------------------
  Phase_Values_PH3.Control_Status_Flags.bits.Zero_Cross_Range          = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.Soft_Start_Zero_Cross     = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity              = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity_last         = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.Relay                     = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.Stop                      = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.Fault                     = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity_Changed      = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity_Changed_last = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.VAC_OK                    = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.CCM                       = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.VDC_Input_Voltage         = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.VACdrop                   = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.nu2                       = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.nu3                       = 0;
  Phase_Values_PH3.Control_Status_Flags.bits.Reference_Changed         = 0;
  
  //PH3 controller numbers -----------------------------------------------------
  Phase_Values_PH3.Controller_Values.PWM_Counter                    = 0;
  Phase_Values_PH3.Controller_Values.Duty_Cycle_Set_Value           = 0;
  Phase_Values_PH3.Controller_Values.CCM_Counter                    = 0;
  Phase_Values_PH3.Controller_Values.DFF_Value                      = 0;
  Phase_Values_PH3.Controller_Values.IAC_Reference_l                = 0;
  Phase_Values_PH3.Controller_Values.IAC_Reference                  = 0;
  
  //PFC common Flags
  PFC_Flags.value = 0x000;
  PFC_Flags.bits.Stop = 1;  
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 End of File
 */

