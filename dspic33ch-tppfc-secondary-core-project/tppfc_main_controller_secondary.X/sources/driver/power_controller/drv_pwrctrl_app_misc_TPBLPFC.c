/**
  @Company
    Microchip Technology Inc.

  @File Name
    drv_pwrctrl_app_misc_TPBLPFC.c

  @Summary
    This is the generated driver implementation file using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides all the function for the power controller to control and drive the power stage(s).
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.167.0
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

#include <xc.h>
#include <stdint.h>

#include "../../../mcc_generated_files/pwm.h"
#include "../../../mcc_generated_files/pin_manager.h"
#include "drv_controller_TPBLPFC.h"
#include "../../devices/dev_TPBLPFC_typedef.h"
#include "drv_usersetup_TPBLPFC.h"
#include "../../PowerSmart/PowerSmart.h"

/*******************************************************************************
* @fn         Drv_PwrCtrl_TPBLPFC_Init
* @brief      initialization of controller and switch ports
* @param      none
* @return     none
* @details    initialization of voltage and current controller, PWM's 
*             and synchronous rectifier port pins
*             for single phase and three phase based on mode setup 
*             
*******************************************************************************/

void Drv_PwrCtrl_TPBLPFC_Init(void)
{
  PowerSmartInit();
   
  CurrentController_PwrCtrl_TPBLPFC_Init();
  VoltageController_PwrCtrl_TPBLPFC_Init();

  PWM_DeadTimeHighSet(PH1_PWM, ModeDeadTime);
  PWM_DeadTimeLowSet(PH1_PWM, ModeDeadTime);
  PWM_GeneratorEnable(PH1_PWM);

#if defined DualPhase1_3 || defined ThreePhase 
  PWM_DeadTimeHighSet(PH3_PWM, ModeDeadTime);
  PWM_DeadTimeLowSet(PH3_PWM, ModeDeadTime);
  PWM_GeneratorEnable(PH3_PWM);  
#endif

#ifdef ThreePhase   
  PWM_DeadTimeHighSet(PH2_PWM, ModeDeadTime);
  PWM_DeadTimeLowSet(PH2_PWM, ModeDeadTime);
  PWM_GeneratorEnable(PH2_PWM);
#endif
  
  PWM_H_N_SetLow();
  PWM_L_N_SetLow();
  
  Vout_Control.Reference.Reference_Internal = 0;
}

/*******************************************************************************
* @fn         Drv_PwrCtrl_TPBLPFC_Stop
* @brief      disables PWMs (switch ports)
* @param      none
* @return     none
* @details    disables PWM's 
*             and synchronous rectivier port pins
*              
*             
*******************************************************************************/

void Drv_PwrCtrl_TPBLPFC_Stop(void)
{
  PWM_OverrideHighEnable(PH1_PWM); //disable PWM output on Buck-H
  PWM_OverrideLowEnable(PH1_PWM); //disable PWM output on Buck-L  
 
#if defined DualPhase1_3 || defined ThreePhase 
  PWM_OverrideHighEnable(PH3_PWM); //disable PWM output on Buck-H
  PWM_OverrideLowEnable(PH3_PWM); //disable PWM output on Buck-L
#endif
 
#ifdef ThreePhase 
  PWM_OverrideHighEnable(PH2_PWM); //disable PWM output on Buck-H
  PWM_OverrideLowEnable(PH2_PWM); //disable PWM output on Buck-L
#endif
  
  PWM_H_N_SetLow();
  PWM_L_N_SetLow();
  Vout_Control.Reference.Reference_Internal = 0; //new 06.09.2021
  Vout_Control.Vout.Filtered = 0;

}

/*******************************************************************************
* @fn         Softstart_reference
* @brief      softstart ramp for Vout
* @param      none
* @return     power controller state
* @details    ramps up Vout from actual value at start of ramp 
*             until reference
*              
*             
*******************************************************************************/

#define SOFT_START_RAMP_SPEED 1 //LV step is 26.9mV, HV step is 25.2mV
#define STEP_DELAY 30           //30*100us=3ms delay between one step of SOFT_START_RAMP_SPEED          

PWR_CTRL_STATE_e Softstart_reference(void)
{
  static uint16_t SoftstartCounter = 0; 
  static PWR_CTRL_STATE_e returnvalue = 1;

  TP39_RD2_SetHigh();
  
#ifdef OuterVloop
  if (++SoftstartCounter > STEP_DELAY)
#else
  if (++SoftstartCounter > 20) //20 // 2 faster for debug _xx
#endif    
  {
    if (Vout_Control.Reference.Reference_Internal <= Vout_Control.Reference.Reference_Set)
    {
      if (((Vout_Control.Reference.Reference_Internal + SOFT_START_RAMP_SPEED) < Vout_Control.Reference.Reference_Set)
        && ((Vout_Control.Reference.Reference_Internal + SOFT_START_RAMP_SPEED) >= SOFT_START_RAMP_SPEED))
      {
        Vout_Control.Reference.Reference_Internal += SOFT_START_RAMP_SPEED;
        returnvalue = pwr_ctrl_state;
      }
      else
      {
        returnvalue = PCS_UP_AND_RUNNING;
        Phase_Values_PH1.Control_Status_Flags.bits.Reference_Changed = 0;
        Phase_Values_PH2.Control_Status_Flags.bits.Reference_Changed = 0;
        Phase_Values_PH3.Control_Status_Flags.bits.Reference_Changed = 0;
      }
    }
    else
    {
      if (((Vout_Control.Reference.Reference_Internal + SOFT_START_RAMP_SPEED) > Vout_Control.Reference.Reference_Set)
        && ((Vout_Control.Reference.Reference_Internal + SOFT_START_RAMP_SPEED) >= SOFT_START_RAMP_SPEED))
      {
        Vout_Control.Reference.Reference_Internal -= SOFT_START_RAMP_SPEED;
        returnvalue = pwr_ctrl_state;
      }
      else
      {
        returnvalue = PCS_UP_AND_RUNNING;
        Phase_Values_PH1.Control_Status_Flags.bits.Reference_Changed = 0;
        Phase_Values_PH2.Control_Status_Flags.bits.Reference_Changed = 0;
        Phase_Values_PH3.Control_Status_Flags.bits.Reference_Changed = 0;
      }
    }

    SoftstartCounter = 0;
  }
  else
    returnvalue = pwr_ctrl_state;
  
  TP39_RD2_SetLow();
  
  return returnvalue;
}

//==============================================================================
//==============================================================================
