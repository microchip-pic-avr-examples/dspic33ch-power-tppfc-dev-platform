/**
  Generated drv_pwrctrl_app_TPBLPFC.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    drv_pwrctrl_app_TPBLPFC.c

  @Summary
    This is the generated using PIC24 / dsPIC33 / PIC32MM MCUs.

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

#include "drv_controller_TPBLPFC.h"
#include "../../devices/dev_TPBLPFC_typedef.h"
#include "../../../mcc_generated_files/pwm.h"
#include "drv_usersetup_TPBLPFC.h"
#include "../../../mcc_generated_files/pin_manager.h"
#include "../../misc/MCC_add_on.h"
#include "drv_pwrctrl_app_TPBLPFC.h"
#include "../../PowerSmart/PowerSmart.h"

static void VOUTaverging(void);

static void ZeroCross_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr);
static void SoftstartAfterZC_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr);
static void CCM_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr);
static void DutyCycleFeedForward_PHx(struct PHASE_VALUES_s* PhaseX);
static void ACDrop_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr);

static void Handler_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr);

/*******************************************************************************
 * @fn         
 * @brief      
 * @param      none
 * @return     none
 * @details    
 *             
 *              
 *             
 *******************************************************************************/
//------------------------------------------------------------------------------
// << ISR handler for switch control PH1, PH2, PH3 time optimized 3PH mode
//------------------------------------------------------------------------------

void PWM_handler_PH123(void)
{

  //  TP35_RB14_SetHigh();
  VOUTaverging();
  //  TP35_RB14_SetLow();
  //<<<<<<<<<<<  PHASE #1  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //  TP35_RB14_SetHigh();
  Handler_PHx(&Phase_Values_PH1, 1);
  //  TP35_RB14_SetLow();
  
#ifdef ThreePhase
  //<<<<<<<<<<<  PHASE #3  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //  TP35_RB14_SetHigh();
  Handler_PHx(&Phase_Values_PH2, 2);
  //  TP35_RB14_SetLow();
#endif 
  
#if defined DualPhase1_3 || defined ThreePhase 
  //<<<<<<<<<<<  PHASE #2  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //  TP35_RB14_SetHigh();
  Handler_PHx(&Phase_Values_PH3, 3);
  //   TP35_RB14_SetLow();
#endif

}

/*******************************************************************************
 * @fn         Handler_PHx
 * @brief      
 * @param      struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr
 * @return     none
 * @details    
 *             
 *              
 *             
 *******************************************************************************/

static void __inline__ Handler_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr)
{
  //  static uint16_t Irect_;

  if (PhaseX->ACcontrol_Status_Flags_perPhase.bits.VAC_OK)
  {
    //<<ZC range detection and handling << polarity change check----------------
    ZeroCross_PHx(PhaseX, PWMnr);

    if (PhaseX->Control_Status_Flags.bits.Relay)
    {
      SoftstartAfterZC_PHx(PhaseX, PWMnr);
      //<< open loop softstart after ZC event ----------------------------------
#ifdef Reverse
      PhaseX->Control_Status_Flags.bits.Soft_Start_Zero_Cross = 0;
#endif
      //<< synch switch handling based on polarity -----------------------------
      if ((!PhaseX->Control_Status_Flags.bits.Soft_Start_Zero_Cross) && (!PhaseX->ACcontrol_Status_Flags_perPhase.bits.Zero_Cross_Range) &&
        ((pwr_ctrl_state > PCS_SOFT_START) || PhaseX->Control_Status_Flags.bits.Reference_Changed))
      {
        CCM_PHx(PhaseX, PWMnr); //comment out for diode mode and DC mode
      }
      //<< duty cycle handling open and closed loop ---------------------------- 
    }

#ifdef OuterVloop
    if ((Vout_Control.Vout.FilterCounter < 1) && (PWMnr == 1))
    {
      //<< outer voltage loop
      TP33_RD5_SetHigh();

#if defined Use_PS && defined SinglePhase1
      VCOMP_Update(&VCOMP);
#else
      SMPS_Controller2P2ZUpdate(&VMC_2p2z, &Vout_Control.Vout.Filtered, Vout_Control.Reference.Reference_Internal,
        &Vout_Control.Reference.Voltage_Loop_Output);
#endif      

      TP33_RD5_SetLow();
    }
#endif

    if ((!PhaseX->ACcontrol_Status_Flags_perPhase.bits.Zero_Cross_Range))
    {
#ifdef OuterVloop
      PhaseX->Controller_Values.IAC_Reference_l = (__builtin_mulss((Vout_Control.Reference.Voltage_Loop_Output), (PhaseX->Phase_Voltage.Vin_div_Averaged2)));
#else
      PhaseX->Controller_Values.IAC_Reference_l = (__builtin_mulss((Vout_Control.Reference.Reference_Internal << 3), PhaseX->Phase_Voltage.Vin_div_Averaged2)); // comment out for V loop#endif
#endif

      PhaseX->Controller_Values.IAC_Reference = (PhaseX->Controller_Values.IAC_Reference_l >> 15); //shift only 15 because of 2 signed bits in mulss
      
      
      
      
      //Current clamp option
//      if(PhaseX->Controller_Values.IAC_Reference > I_INCLAMP) 
//      {
//        PhaseX->Controller_Values.IAC_Reference = I_INCLAMP;
//      }
#ifndef OuterVloop
      if(PhaseX->ACcontrol_Status_Flags_perPhase.bits.VDC_Input_Voltage)
      {
        PhaseX->Controller_Values.IAC_Reference = (Vout_Control.Reference.Reference_Internal << 1);
      }
 #endif     
      
      
      
      
      PhaseX->Phase_Current.Rectified_Shift = (uint16_t) (PhaseX->Phase_Current.Rectified << 4); //3/4/5??? je mehr left shift je mehr gain, je unruhiger, aber THD wird immer besser

      //<< inner current loop
      //      TP33_RD5_SetHigh();

#if defined Use_PS && defined SinglePhase1
      ICOMP_Update(&ICOMP);
#else
      SMPS_Controller2P2ZUpdate(&PHx_AVG_CM2p2z[PWMnr], &PhaseX->Phase_Current.Rectified_Shift, PhaseX->Controller_Values.IAC_Reference,
        &(PhaseX->Controller_Values.Duty_Cycle_Set_Value));
#endif

      //      TP33_RD5_SetLow();

      //<< DC ff
#ifdef dffMode      
      //      TP31_RD6_SetHigh();
      DutyCycleFeedForward_PHx(PhaseX);
      //      TP31_RD6_SetLow();
#endif

      if (PhaseX->Controller_Values.Duty_Cycle_Set_Value < DCMIN) PhaseX->Controller_Values.Duty_Cycle_Set_Value = DCMIN;
      if (PhaseX->Controller_Values.Duty_Cycle_Set_Value > DCMAX) PhaseX->Controller_Values.Duty_Cycle_Set_Value = DCMAX;

      PWM_DutyCycleSet(PWMnr, PhaseX->Controller_Values.Duty_Cycle_Set_Value);
    }

    PhaseX->Control_Status_Flags.bits.VAC_Polarity_last = PhaseX->ACcontrol_Status_Flags_perPhase.bits.VAC_Polarity;
  }
}

/*******************************************************************************
 * @fn         VOUTaverging
 * @brief      Average value calculations
 * @param      none
 * @return     none
 * @details    Averaging of Vout, filter Vout, (Iin) 
 *             from ZC to ZC whatever phase
 *              
 *             
 *******************************************************************************/

static void __inline__ VOUTaverging(void)
{
  static uint32_t VoutAVGsum, PH1AVGCurrentsum, PH2AVGCurrentsum, PH3AVGCurrentsum;
  static uint32_t PH1AVGCurrentOffset, PH2AVGCurrentOffset, PH3AVGCurrentOffset;
  static uint16_t vac_pol_changed_counter;
  static uint16_t PH1vac_pol_changed_counter, PH2vac_pol_changed_counter, PH3vac_pol_changed_counter;

  Vout_Control.Vout.FilterCounter++;
  Phase_Values_PH1.Phase_Current.FilterCounter++;
  Phase_Values_PH2.Phase_Current.FilterCounter++;
  Phase_Values_PH3.Phase_Current.FilterCounter++;

  VoutAVGsum += Vout_Control.Vout.Raw;

  //  PH1AVGCurrentsum += Phase_Values_PH1.Phase_Current.Rectified;
  //  PH2AVGCurrentsum += Phase_Values_PH2.Phase_Current.Rectified;
  //  PH3AVGCurrentsum += Phase_Values_PH3.Phase_Current.Rectified;

  if ((Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity_Changed)
    && (!Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity_Changed_last))
  {
    vac_pol_changed_counter++;
    PH1vac_pol_changed_counter++;
  }

  //3PHonly  
#ifdef ThreePhase 
  if ((Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity_Changed)
    && (!Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity_Changed_last))
  {
    vac_pol_changed_counter++;
    PH2vac_pol_changed_counter++;
  }

  if ((Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity_Changed)
    && (!Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity_Changed_last))
  {
    vac_pol_changed_counter++;
    PH3vac_pol_changed_counter++;
  }
#endif  

  if (((vac_pol_changed_counter > 0) && (Vout_Control.Vout.FilterCounter > 1))
    || (Vout_Control.Vout.FilterCounter > 8000))
  {
    Vout_Control.Vout.Filtered = (uint16_t) (__builtin_divud(VoutAVGsum, Vout_Control.Vout.FilterCounter - 1));
    VoutAVGsum = 0;

    vac_pol_changed_counter = 0;
    Vout_Control.Vout.FilterCounter = 0;
  }

  // after power up during initialization the current sensor calibration is done
  if (pwr_ctrl_state == PCS_INIT)
  {
    PH1AVGCurrentOffset += Phase_Values_PH1.Phase_Current.Raw;
    PH2AVGCurrentOffset += Phase_Values_PH2.Phase_Current.Raw;
    PH3AVGCurrentOffset += Phase_Values_PH3.Phase_Current.Raw;

    //28_07_2022 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (((PH1vac_pol_changed_counter > 1) && (Phase_Values_PH1.Phase_Current.FilterCounter > 1))
      || (Phase_Values_PH1.Phase_Current.FilterCounter > 4000)) //4000=40ms/10us
    {
      //    Phase_Values_PH1.Phase_Current.Filtered = (uint16_t) (__builtin_divud(PH1AVGCurrentsum, Phase_Values_PH1.Phase_Current.FilterCounter - 1));
      Phase_Values_PH1.Phase_Current.Offset = (uint16_t) (__builtin_divud(PH1AVGCurrentOffset, Phase_Values_PH1.Phase_Current.FilterCounter - 1));
      PH1AVGCurrentsum = 0;
      PH1AVGCurrentOffset = 0;
      PH1vac_pol_changed_counter = 0;
      Phase_Values_PH1.Phase_Current.FilterCounter = 0;
    }
    if (((PH2vac_pol_changed_counter > 1) && (Phase_Values_PH2.Phase_Current.FilterCounter > 1)) || (Phase_Values_PH2.Phase_Current.FilterCounter > 4000)) //4000=40ms/10us
    {
      //    Phase_Values_PH2.Phase_Current.Filtered = (uint16_t) (__builtin_divud(PH2AVGCurrentsum, Phase_Values_PH2.Phase_Current.FilterCounter - 1));
      Phase_Values_PH2.Phase_Current.Offset = (uint16_t) (__builtin_divud(PH2AVGCurrentOffset, Phase_Values_PH2.Phase_Current.FilterCounter - 1));
      PH2AVGCurrentsum = 0;
      PH2AVGCurrentOffset = 0;
      PH2vac_pol_changed_counter = 0;
      Phase_Values_PH2.Phase_Current.FilterCounter = 0;
    }
    if (((PH3vac_pol_changed_counter > 1) && (Phase_Values_PH3.Phase_Current.FilterCounter > 1)) || (Phase_Values_PH3.Phase_Current.FilterCounter > 4000)) //4000=40ms/10us
    {
      //    Phase_Values_PH3.Phase_Current.Filtered = (uint16_t) (__builtin_divud(PH3AVGCurrentsum, Phase_Values_PH3.Phase_Current.FilterCounter - 1));
      Phase_Values_PH3.Phase_Current.Offset = (uint16_t) (__builtin_divud(PH3AVGCurrentOffset, Phase_Values_PH3.Phase_Current.FilterCounter - 1));
      PH3AVGCurrentsum = 0;
      PH3AVGCurrentOffset = 0;
      PH3vac_pol_changed_counter = 0;
      Phase_Values_PH3.Phase_Current.FilterCounter = 0;
    }
  }

  /*  
    if (pwr_ctrl_state == PCS_UP_AND_RUNNING)
    {
      if (((PH1vac_pol_changed_counter > 1) && (Phase_Values_PH1.Phase_Current.FilterCounter > 1)) || (Phase_Values_PH1.Phase_Current.FilterCounter > 4000)) //4000=40ms/10us
      {
        Phase_Values_PH1.Phase_Current.Filtered = (uint16_t) (__builtin_divud(PH1AVGCurrentsum, Phase_Values_PH1.Phase_Current.FilterCounter - 1));
        PH1AVGCurrentsum = 0;
        PH1AVGCurrentOffset = 0;
        PH1vac_pol_changed_counter = 0;
        Phase_Values_PH1.Phase_Current.FilterCounter = 0;
      }
      if (((PH2vac_pol_changed_counter > 1) && (Phase_Values_PH2.Phase_Current.FilterCounter > 1)) || (Phase_Values_PH2.Phase_Current.FilterCounter > 4000)) //4000=40ms/10us
      {
        Phase_Values_PH2.Phase_Current.Filtered = (uint16_t) (__builtin_divud(PH2AVGCurrentsum, Phase_Values_PH2.Phase_Current.FilterCounter - 1));
        PH2AVGCurrentsum = 0;
        PH2AVGCurrentOffset = 0;
        PH2vac_pol_changed_counter = 0;
        Phase_Values_PH2.Phase_Current.FilterCounter = 0;
      }
      if (((PH3vac_pol_changed_counter > 1) && (Phase_Values_PH3.Phase_Current.FilterCounter > 1)) || (Phase_Values_PH3.Phase_Current.FilterCounter > 4000)) //4000=40ms/10us
      {
        Phase_Values_PH3.Phase_Current.Filtered = (uint16_t) (__builtin_divud(PH3AVGCurrentsum, Phase_Values_PH3.Phase_Current.FilterCounter - 1));
        PH3AVGCurrentsum = 0;
        PH3AVGCurrentOffset = 0;
        PH3vac_pol_changed_counter = 0;
        Phase_Values_PH3.Phase_Current.FilterCounter = 0;
      }
    }
   */

  Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity_Changed_last = Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity_Changed;
  Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity_Changed_last = Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity_Changed;
  Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity_Changed_last = Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity_Changed;

}

/*******************************************************************************
 * @fn         ZeroCross_PHx
 * @brief      check for zero cross range PH #X
 * @param      none
 * @return     none
 * @details    
 *             
 *              
 *             
 *******************************************************************************/

static void __inline__ ZeroCross_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr)
{
  //<< switch off main and synch switches at ZC area ---------------------------
  //  if (AC_Ctrl_Flags.bits.PH1_Zero_Cross_Range)
  if (PhaseX->ACcontrol_Status_Flags_perPhase.bits.Zero_Cross_Range)
  {
    PWM_OverrideHighEnable(PWMnr);
    PWM_OverrideLowEnable(PWMnr);
    PWM_H_N_SetLow(); //synch switch OFF
    PWM_L_N_SetLow(); //synch switch OFF

    PhaseX->Controller_Values.CCM_Counter = 1;
    //@ DCM_Counter used as hysteresis for fixed current set DCM
    //@ in reverse the DCM counter can be greater CCM level at end of half wave
    //@ at the begin of the next half wave after ZC range synch switch is enabled
    //@ because of DCM counter needs to be count down after ZC range
  }

  //<< polarity change check ---------------------------------------------------
  if (PhaseX->ACcontrol_Status_Flags_perPhase.bits.VAC_Polarity != PhaseX->Control_Status_Flags.bits.VAC_Polarity_last)
  {
    PhaseX->Control_Status_Flags.bits.VAC_Polarity_Changed = 1;
  }
}

/*******************************************************************************
 * @fn         SoftstartAfterZC_PHx
 * @brief      activate softstart after ZC PH #X
 * @param      none
 * @return     none
 * @details    
 *             
 *              
 *             
 *******************************************************************************/

static void __inline__ SoftstartAfterZC_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr)
{
  //<< switch on main switches after polarity change and ZC range is over and before ZC startup 
  if (PhaseX->Control_Status_Flags.bits.VAC_Polarity_Changed &&
    (!PhaseX->Control_Status_Flags.bits.Soft_Start_Zero_Cross) &&
    (!PhaseX->ACcontrol_Status_Flags_perPhase.bits.Zero_Cross_Range))
  {

    if (PhaseX->ACcontrol_Status_Flags_perPhase.bits.VAC_Polarity) //<< DC modulated direct from VAC
    {
      PhaseX->Control_Status_Flags.bits.Soft_Start_Zero_Cross = 1;
      PhaseX->Controller_Values.PWM_Counter = 0;

#ifndef Reverse
      PWM_SwapEnable(PWMnr);
      PWM_OverrideLowDisable(PWMnr);
#else
      PWM_OverrideLowEnable(PWMnr);
      PWM_OverrideHighDisable(PWMnr);
      PWM_SwapDisable(PWMnr);
#ifdef SinglePhase1
      PWM_H_N_SetLow();
      while (_LATD1 == 1); //@??? does that help to prevent race conditions ?
      PWM_L_N_SetHigh();
      while (_LATD0 == 0); //synch switch ON
#endif
#endif
    }
    else
    {
      PhaseX->Control_Status_Flags.bits.Soft_Start_Zero_Cross = 1;
      PhaseX->Controller_Values.PWM_Counter = 0;
#ifndef Reverse   
      PWM_SwapDisable(PWMnr);
      PWM_OverrideHighDisable(PWMnr);
#else   
      PWM_OverrideHighEnable(PWMnr);
      PWM_OverrideLowDisable(PWMnr);
      PWM_SwapEnable(PWMnr);
#ifdef SinglePhase1
      PWM_L_N_SetLow();
      while (_LATD0 == 1); //@??? does that help to prevent race conditions ?
      PWM_H_N_SetHigh();
      while (_LATD1 == 0); //synch switch ON
#endif
#endif
    }
    PhaseX->Control_Status_Flags.bits.VAC_Polarity_Changed = 0;
  }

#ifndef Reverse  
  //<<<ISR_Startup_After_ZC_PG_PH1
  uint16_t pg1dc_;

  if (PhaseX->Control_Status_Flags.bits.Soft_Start_Zero_Cross)
  {
    if (++PhaseX->Controller_Values.PWM_Counter < OLStartupPulses)
    {
      pg1dc_ = (PhaseX->Controller_Values.PWM_Counter << OLPWMCounterShift);
      if (pg1dc_ > PhaseX->Controller_Values.Duty_Cycle_Set_Value)
      {
        PhaseX->Controller_Values.PWM_Counter = 30;
      }
      PWM_DutyCycleSet(PWMnr, pg1dc_);
    }
    else
    {
      PhaseX->Control_Status_Flags.bits.Soft_Start_Zero_Cross = 0; //check startup must be OFF 
    }
  }
#endif

}

/*******************************************************************************
 * @fn         CCM_PHx
 * @brief      CCM Mode check PH #X. If DCM run asynchron 
 * @param      none
 * @return     none
 * @details    
 *             
 *              
 *             
 *******************************************************************************/

static void __inline__ CCM_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr)
{
  uint16_t var1_ui, var2_ui;

  // current fix for DCM;
  var1_ui = PhaseX->Phase_Current.Rectified;
  var2_ui = CCMCurrent;

  if (var1_ui > var2_ui)
  {
    PhaseX->Controller_Values.CCM_Counter++;
  }
  else if (var1_ui < var2_ui)
  {
    PhaseX->Controller_Values.CCM_Counter--;
  }

  if (PhaseX->Controller_Values.CCM_Counter > 6)
  {
    PhaseX->Controller_Values.CCM_Counter = 6;
    PhaseX->Control_Status_Flags.bits.CCM = 1;
  }
  if (PhaseX->Controller_Values.CCM_Counter < 1)
  {
    PhaseX->Controller_Values.CCM_Counter = 1;
    PhaseX->Control_Status_Flags.bits.CCM = 0;
  }

  if (PhaseX->Control_Status_Flags.bits.CCM)
  {
    if (PhaseX->ACcontrol_Status_Flags_perPhase.bits.VAC_Polarity)
    {
#ifndef Reverse        
      PWM_OverrideHighDisable(PWMnr); //PWM ON
#if defined RectifierSwitch && defined SinglePhase1
      PWM_L_N_SetHigh();
#endif
#else
      PWM_OverrideLowDisable(PWMnr); //PWM ON
#endif        
    }
    else
    {
#ifndef Reverse     
      PWM_OverrideLowDisable(PWMnr); //PWM ON
#if defined RectifierSwitch && defined SinglePhase1
      PWM_H_N_SetHigh();
#endif
#else
      PWM_OverrideHighDisable(PWMnr); //PWM ON
#endif        
    }
  }
  else
  {
    if (PhaseX->ACcontrol_Status_Flags_perPhase.bits.VAC_Polarity)
    {
#ifndef Reverse     
      PWM_OverrideHighEnable(PWMnr); //PWM OFF
#if defined RectifierSwitch && defined SinglePhase1      
      PWM_L_N_SetLow();
#endif
#else
      PWM_OverrideLowEnable(PWMnr); //PWM ON
#endif        
    }
    else
    {
#ifndef Reverse     
      PWM_OverrideLowEnable(PWMnr); //PWM OFF
#if defined RectifierSwitch && defined SinglePhase1
      PWM_H_N_SetLow();
#endif
#else
      PWM_OverrideHighEnable(PWMnr); //PWM ON
#endif        
    }
  }
}

/*******************************************************************************
 * @fn         DutyCycleFeedForward_PHx
 * @brief      Duty Cycle feedforward calculation
 * @param      none
 * @return     none
 * @details         
 *                  Vout - VAC
 *             d = ------------
 *                      Vout            
 *******************************************************************************/

static void __inline__ DutyCycleFeedForward_PHx(struct PHASE_VALUES_s* PhaseX)
{
  uint32_t var_ul;
  uint16_t var1_ui;

  if (Vout_Control.Vout.Filtered > PhaseX->Phase_Voltage.Rectified)
  {
    var1_ui = Vout_Control.Vout.Filtered - PhaseX->Phase_Voltage.Rectified; //Vout - Vin
    var_ul = (uint32_t) var1_ui * MPER;
    var1_ui = __builtin_divud(var_ul, Vout_Control.Vout.Filtered);
#ifdef ThreePhase  
    PhaseX->Controller_Values.Duty_Cycle_Set_Value = PhaseX->Controller_Values.Duty_Cycle_Set_Value + (var1_ui >> 4); //3
#else
    PhaseX->Controller_Values.Duty_Cycle_Set_Value = PhaseX->Controller_Values.Duty_Cycle_Set_Value + (var1_ui >> 2); //tests done with 2
#endif 
  }
}

/*******************************************************************************
 * @fn         ACDrop_PHx
 * @brief      check for AC drop NOT USED (for later investigations)
 * @param      none
 * @return     none
 * @details    
 *             
 *              
 *             
 *******************************************************************************/

static void __inline__ ACDrop_PHx(struct PHASE_VALUES_s* PhaseX, uint16_t PWMnr)
{
  //<< AC drop check ---------------------------------------------------
  if ((PhaseX->Phase_Voltage.Rectified & 0x0800) == 0x0800)
  {
    //    AC_Ctrl_Flags.bits.PH1_VACdrop = 1;
  }
  else
  {
    //    AC_Ctrl_Flags.bits.PH1_VACdrop = 0;
  }

  //  if (AC_Ctrl_Flags.bits.PH1_VACdrop)
  {
    PWM_OverrideHighEnable(PWMnr);
    PWM_OverrideLowEnable(PWMnr);
    PWM_H_N_SetLow(); //synch switch OFF
    PWM_L_N_SetLow(); //synch switch OFF

    PhaseX->Controller_Values.CCM_Counter = 1;
    //@ DCM_Counter used as hysteresis for fixed current set DCM
    //@ in reverse the DCM counter can be greater CCM level at end of half wave
    //@ at the begin of the next half wave after ZC range synch switch is enabled
    //@ because of DCM counter needs to be count down after ZC range
  }

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 End of File
 */

