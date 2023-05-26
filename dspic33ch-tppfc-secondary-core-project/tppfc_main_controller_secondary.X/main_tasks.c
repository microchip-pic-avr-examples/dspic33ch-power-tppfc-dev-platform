/**
  Generated main_task.c file from MPLAB Code Configurator

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

#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "sources/driver/msi/drv_msi.h"
#include "sources/devices/dev_TPBLPFC_typedef.h"
#include "sources/driver/power_controller/drv_pwrctrl_app_misc_TPBLPFC.h"
#include "sources/driver/power_controller/smps_control.h"
#include "sources/driver/power_controller/drv_controller_TPBLPFC.h"
#include "sources/driver/power_controller/drv_usersetup_TPBLPFC.h"
#include "sources/PowerSmart/VCOMP.h"
#include "sources/PowerSmart/ICOMP.h"

/*******************************************************************************
 * @details static functions in main_task.c    
 *          functions are performance optimized inlined        
 *******************************************************************************/

static PWR_CTRL_STATE_e Init_StateHandler(void);
static PWR_CTRL_STATE_e WaitIfFaultActive_StateHandler(void);
static PWR_CTRL_STATE_e StandBy_StateHandler(void);
static PWR_CTRL_STATE_e VacOk_StateHandler(void);
static PWR_CTRL_STATE_e RelayOn_StateHandler(void);
static PWR_CTRL_STATE_e DelayAfterRelayOn_StateHandler(void);
static PWR_CTRL_STATE_e StartControl_StateHandler(void);
static PWR_CTRL_STATE_e SoftStart_StateHandler(void);
static PWR_CTRL_STATE_e UpAndRunning_StateHandler(void);
static PWR_CTRL_STATE_e VACOK_Check(void);

/*******************************************************************************
 * @details defines for time steps based on 100us scheduler steps   
 *           
 *******************************************************************************/

#define t2sec 20000 //100us steps for 2s
#define t1sec 10000 //100us steps for 1s
#define t20ms 200   //100us steps for 20ms
#define t50ms 500   //100us steps for 30ms
#define VoutStartUpVary 150 //Startup ramp accuracy range to ramp further
#define CurrentOffsetLowLimit 2020  //typ. ADC value is 2048
#define CurrentOffsetHighLimit 2070 //typ. ADC value is 2048

/*******************************************************************************
 * @details static variable   
 *                
 *******************************************************************************/

static uint16_t RelayTimeCounter = t2sec, RelayTimeCounterStart = t20ms;
static uint16_t CalibrationTimeCounter = t2sec;

/*******************************************************************************
 * @fn         void Tasks_100us()
 * @brief      100us scheduler task 
 * @param      none
 * @return     none
 * @details    100us easy performance optimized scheduler
 *             with power controller state machine to run the PFC in different 
 *             modes based on the configuration
 * 
 *******************************************************************************/

void Tasks_100us(void)
{
  ReceiveMSIAMessage(); //<< check CAN receive on Byte 0

  //<< send data via CAN 
  if ((SI1FIFOCSbits.SWFEN) && (SI1FIFOCSbits.SWFEMPTY))
  {
    SendMSIFIFOMessage();
  }
  //<<----------------------------------------------------------------------

  switch (pwr_ctrl_state)
  {
      //<<--------------------------------------------------------------------
    case PCS_INIT:
      //wait for VACok and after 2sec check if calibration data are valid
      pwr_ctrl_state = Init_StateHandler();

      break;

      //<<--------------------------------------------------------------------
    case PCS_WAIT_IF_FAULT_ACTIVE:
      //stall when current sensor calibration fails
      Nop();
      break;

      //<<--------------------------------------------------------------------
    case PCS_STANDBY:

      pwr_ctrl_state = StandBy_StateHandler();
      RelayTimeCounter = t1sec;

      break;

      //<<--------------------------------------------------------------------
    case PCS_VACOK:
      if ((RelayTimeCounter--) == 0)
      {
        RelayTimeCounter = t50ms;
        pwr_ctrl_state = PCS_RELAYON;
      }

      break;

      //<<--------------------------------------------------------------------
    case PCS_RELAYON:

      RELAY_SetHigh(); //Relay ON

      pwr_ctrl_state = PCS_DELAY_AFTER_RELAYON;

      break;

      //<<--------------------------------------------------------------------
    case PCS_DELAY_AFTER_RELAYON:

      // wait 50ms delay after switch on to enable relay bits for Phase Handler
      if (((RelayTimeCounter--) == 0) && (!Phase_Values_PH1.Control_Status_Flags.bits.Relay))
      {
        Phase_Values_PH1.Control_Status_Flags.bits.Relay = 1;
        Phase_Values_PH2.Control_Status_Flags.bits.Relay = 1;
        Phase_Values_PH3.Control_Status_Flags.bits.Relay = 1;
        RelayTimeCounterStart = t50ms;

        pwr_ctrl_state = PCS_START_CONTROL;
      }

      break;

      //<<--------------------------------------------------------------------
    case PCS_START_CONTROL:

      // wait 50ms delay to initialize controller and Vout softstart reference based
      // on the actual Vout measurement 
      // delay is needed to be sure that Vout is ramped up after PWM started switching
      // 20ms before
      // during softstart Vout is checked if value is in the range of reference
      if (((RelayTimeCounterStart--) == 0) && (Phase_Values_PH1.Control_Status_Flags.bits.Relay))
      {
        pwr_ctrl_state = StartControl_StateHandler();
      }

#ifndef OuterVloop  //current mode only   
      Vout_Control.Reference.Reference_Internal = 0;
      pwr_ctrl_state = PCS_SOFT_START;
#endif

      break;

      //<<--------------------------------------------------------------------
    case PCS_SOFT_START:

      pwr_ctrl_state = SoftStart_StateHandler();

#ifdef OuterVloop
      if ((Vout_Control.Vout.Raw > (Vout_Control.Reference.Reference_Internal - VoutStartUpVary)) &&
        (Vout_Control.Vout.Raw < (Vout_Control.Reference.Reference_Internal + VoutStartUpVary)))
#endif
      {
        pwr_ctrl_state = Softstart_reference();
      }

      break;

      //<<--------------------------------------------------------------------
    case PCS_UP_AND_RUNNING:

      pwr_ctrl_state = UpAndRunning_StateHandler();

      break;

      //<<--------------------------------------------------------------------
    case PCS_STALL_DEBUG:
      //stall when VACOK is false whatever phase
      Nop();

      break;

      //<<--------------------------------------------------------------------
    default:

      break;
  }
  //<<----------------------------------------------------------------------

  pwr_ctrl_state = VACOK_Check();

}

/*******************************************************************************
 * @fn         Init_StateHandler
 * @brief      power controller state PCS_INIT
 * @param      none
 * @return     none
 * @details    
 *             
 *             
 *             
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e Init_StateHandler(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

#ifdef ThreePhase 
  if ((Phase_Values_PH1.ACcontrol_Status_Flags_perPhase.bits.VAC_OK) && (Phase_Values_PH2.ACcontrol_Status_Flags_perPhase.bits.VAC_OK) && \
              (Phase_Values_PH3.ACcontrol_Status_Flags_perPhase.bits.VAC_OK))
  {
    //offset calibration current sensors to consider the 0A differences
    if ((CalibrationTimeCounter--) == 0)
    {
      if (((Phase_Values_PH1.Phase_Current.Offset > CurrentOffsetLowLimit) || (Phase_Values_PH1.Phase_Current.Offset < CurrentOffsetHighLimit)) &&
        ((Phase_Values_PH2.Phase_Current.Offset > CurrentOffsetLowLimit) || (Phase_Values_PH2.Phase_Current.Offset < CurrentOffsetHighLimit)) &&
        ((Phase_Values_PH3.Phase_Current.Offset > CurrentOffsetLowLimit) || (Phase_Values_PH3.Phase_Current.Offset < CurrentOffsetHighLimit)))
      {
        returnvalue = PCS_STANDBY;
      }
      else
        returnvalue = PCS_WAIT_IF_FAULT_ACTIVE;
    }
    else
      returnvalue = PCS_INIT;
  }
#else
  if (Phase_Values_PH1.ACcontrol_Status_Flags_perPhase.bits.VAC_OK)
  {
    if ((CalibrationTimeCounter--) == 0)
    {
      if ((Phase_Values_PH1.Phase_Current.Offset > 2020) || (Phase_Values_PH1.Phase_Current.Offset < 2070))
      {
        returnvalue = PCS_STANDBY;
      }
      else
        returnvalue = PCS_WAIT_IF_FAULT_ACTIVE;
    }
  }
#endif
  else
    returnvalue = PCS_INIT;

  return returnvalue;

}

/*******************************************************************************
 * @fn         WaitIfFaultActive_StateHandler
 * @brief      power controller state PCS_WAIT_IF_FAULT_ACTIVE
 * @param      none
 * @return     none
 * @details    
 *             
 *             
 *             
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e WaitIfFaultActive_StateHandler(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

  returnvalue = pwr_ctrl_state;

  return returnvalue;
}

/*******************************************************************************
 * @fn         StandBy_StateHandler
 * @brief      power controller state PCS_STANDBY
 * @param      none
 * @return     none
 * @details    
 *             
 *             
 *             
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e StandBy_StateHandler(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

#ifdef AutoOn
  if ((Phase_Values_PH1.ACcontrol_Status_Flags_perPhase.bits.VAC_OK)) //testsetup to startPFC automatic without CAN GUI
  {
    Vout_Control.Reference.Reference_Set = VoutRef;
#else          
  if (PFC_Flags.bits.Run)
  {
#endif
    PFC_Flags.bits.Run = 1;
    PFC_Flags.bits.Fault = 0;
    PFC_Flags.bits.OC_PH1 = 0;
    PFC_Flags.bits.OC_PH2 = 0;
    PFC_Flags.bits.OC_PH3 = 0;
    PFC_Flags.bits.Stop = 0;
    PFC_Flags.bits.OV_Vout = 0;

    Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity_last = Phase_Values_PH1.ACcontrol_Status_Flags_perPhase.bits.VAC_Polarity = 0; //<< DC test
    Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity_last = Phase_Values_PH2.ACcontrol_Status_Flags_perPhase.bits.VAC_Polarity = 0; //<< DC test
    Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity_last = Phase_Values_PH3.ACcontrol_Status_Flags_perPhase.bits.VAC_Polarity = 0; //<< DC test

    returnvalue = PCS_VACOK;
  }
  else
    returnvalue = PCS_STANDBY;

  return returnvalue;
}

/*******************************************************************************
 * @fn         VacOk_StateHandler
 * @brief      power controller state PCS_VACOK
 * @param      none
 * @return     none
 * @details    
 *             
 *             
 *             
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e VacOk_StateHandler(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

  returnvalue = pwr_ctrl_state;

  return returnvalue;
}

/*******************************************************************************
 * @fn         RelayOn_StateHandler
 * @brief      power controller state PCS_RELAYON
 * @param      none
 * @return     none
 * @details    
 *             
 *             
 *             
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e RelayOn_StateHandler(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

  returnvalue = pwr_ctrl_state;

  return returnvalue;
}

/*******************************************************************************
 * @fn         DelayAfterRelayOn_StateHandler
 * @brief      power controller state PCS_DELAY_AFTER_RELAYON
 * @param      none
 * @return     none
 * @details    
 *             
 *             
 *             
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e DelayAfterRelayOn_StateHandler(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

  returnvalue = pwr_ctrl_state;

  return returnvalue;
}

/*******************************************************************************
 * @fn         StartControl_StateHandler
 * @brief      power controller state PCS_START_CONTROL 
 * @param      none
 * @return     none
 * @details    
 *             
 *             
 *             
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e StartControl_StateHandler(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

  INTERRUPT_GlobalDisable();
  Phase_Values_PH1.Controller_Values.CCM_Counter = 1;
  Phase_Values_PH1.Control_Status_Flags.bits.CCM = 0;
  Phase_Values_PH2.Controller_Values.CCM_Counter = 1;
  Phase_Values_PH2.Control_Status_Flags.bits.CCM = 0;
  Phase_Values_PH3.Controller_Values.CCM_Counter = 1;
  Phase_Values_PH3.Control_Status_Flags.bits.CCM = 0;

  SMPS_Controller2P2ZInitialize(&PHx_AVG_CM2p2z[1]); // Clear histories
  SMPS_Controller2P2ZInitialize(&PHx_AVG_CM2p2z[2]); // Clear histories
  SMPS_Controller2P2ZInitialize(&PHx_AVG_CM2p2z[3]); // Clear histories

#ifdef Use_PS 
  VCOMP_Initialize(&VCOMP);
  ICOMP_Initialize(&ICOMP);
#else
  SMPS_Controller2P2ZInitialize(&VMC_2p2z); // Clear histories
#endif

  Vout_Control.Reference.Reference_Internal = Vout_Control.Vout.Filtered;

  INTERRUPT_GlobalEnable();

#ifdef Reverse              
  //<< initiate change bit to enable PWM in SoftstartAfterZC_PH1 for DC mode
  Phase_Values_PH1.Control_Status_Flags.bits.VAC_Polarity_Changed = 1; //<<reverseDCBuck
  Phase_Values_PH2.Control_Status_Flags.bits.VAC_Polarity_Changed = 1; //<<reverseDCBuck
  Phase_Values_PH3.Control_Status_Flags.bits.VAC_Polarity_Changed = 1; //<<reverseDCBuck
#endif              

  returnvalue = PCS_SOFT_START;

  return returnvalue;

}

/*******************************************************************************
 * @fn         SoftStart_StateHandler
 * @brief      power controller state PCS_SOFT_START
 * @param      none
 * @return     none
 * @details    
 *             
 *             
 *             
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e SoftStart_StateHandler(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

  if (!PFC_Flags.bits.Run)
  {
    Phase_Values_PH1.Control_Status_Flags.bits.Relay = 0;
    Phase_Values_PH2.Control_Status_Flags.bits.Relay = 0;
    Phase_Values_PH3.Control_Status_Flags.bits.Relay = 0;
    Drv_PwrCtrl_TPBLPFC_Stop();
    RELAY_SetLow(); //Relay OFF

    returnvalue = PCS_STANDBY;
  }
  else
    returnvalue = pwr_ctrl_state;

  return returnvalue;

}

/*******************************************************************************
 * @fn         UpAndRunning_StateHandler
 * @brief      power controller state PCS_UP_AND_RUNNING
 * @param      none
 * @return     none
 * @details    
 *             
 *             
 *             
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e UpAndRunning_StateHandler(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

  if (!PFC_Flags.bits.Run)
  {
    Phase_Values_PH1.Control_Status_Flags.bits.Relay = 0;
    Phase_Values_PH2.Control_Status_Flags.bits.Relay = 0;
    Phase_Values_PH3.Control_Status_Flags.bits.Relay = 0;
    Drv_PwrCtrl_TPBLPFC_Stop();
    RELAY_SetLow(); //Relay OFF

    returnvalue = PCS_STANDBY;
  }
  else if ((Vout_Control.Reference.Reference_Set > (Vout_Control.Reference.Reference_Internal + 20)) ||
    (Vout_Control.Reference.Reference_Set < (Vout_Control.Reference.Reference_Internal - 20)))
  {
    Phase_Values_PH1.Control_Status_Flags.bits.Reference_Changed = 1;
    Phase_Values_PH2.Control_Status_Flags.bits.Reference_Changed = 1;
    Phase_Values_PH3.Control_Status_Flags.bits.Reference_Changed = 1;
    returnvalue = PCS_SOFT_START;
  }
  else
    returnvalue = PCS_UP_AND_RUNNING;

  return returnvalue;
}

/*******************************************************************************
 * @fn         VACOK_Check
 * @brief      checks all phases for VACOK
 * @param      none
 * @return     none
 * @details    if there is no VACOK on one of the phases --> stops PFC
 *             and stuck in PCS_DEBUG_STALL
 *             power on reset needed
 *             that is for debug purpose, later it jumps to PCS_STANDBY
 *******************************************************************************/

static __inline__ PWR_CTRL_STATE_e VACOK_Check(void)
{
  static PWR_CTRL_STATE_e returnvalue = 1;

  if (pwr_ctrl_state > PCS_VACOK)
  {
#ifdef ThreePhase          
    if ((!Phase_Values_PH1.ACcontrol_Status_Flags_perPhase.bits.VAC_OK) ||
      (!Phase_Values_PH2.ACcontrol_Status_Flags_perPhase.bits.VAC_OK) ||
      (!Phase_Values_PH3.ACcontrol_Status_Flags_perPhase.bits.VAC_OK))
#else
    if ((!Phase_Values_PH1.ACcontrol_Status_Flags_perPhase.bits.VAC_OK))
#endif
    {
      RELAY_SetLow(); //Relay OFF
      Drv_PwrCtrl_TPBLPFC_Stop();
      //      return PCS_STANDBY;
      returnvalue = PCS_STALL_DEBUG;
      PFC_Flags.bits.Run = 0;
      PFC_Flags.bits.Stop = 1;
    }
    else
      returnvalue = pwr_ctrl_state;
  }
  else
    returnvalue = pwr_ctrl_state;

  return returnvalue;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


/**
 End of File
 */

