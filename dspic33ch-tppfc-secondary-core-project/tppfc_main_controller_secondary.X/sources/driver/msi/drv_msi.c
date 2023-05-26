/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    drv_msi.c

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

#include "../../../mcc_generated_files/master.h"
#include "../../driver/adc/drv_adc.h"
#include "../power_controller/drv_controller_TPBLPFC.h"

#include "../power_controller/../../devices/dev_TPBLPFC_typedef.h"

#include "../../../revision.h"
#include "../power_controller/drv_usersetup_TPBLPFC.h"

#if High_Voltage == 1
#define HIGHVOLTAGE   '1'
#else
#define HIGHVOLTAGE   '0'
#endif 
//------------------------------------------------------------------------------

uint16_t pMSIAdata[16];

void FIFOData_SendToPrim(void);
//------------------------------------------------------------------------------
//<< reveive message from primary core
//------------------------------------------------------------------------------

void ReceiveMSIAMessage(void)
{

  if (MASTER_ProtocolARead((ProtocolA_DATA*) & pMSIAdata))
  {
    uint8_t command_id = (uint8_t) ((pMSIAdata[0] & 0xFF00) >> 8);
    uint8_t control_byte = (uint8_t) (pMSIAdata[0] & 0x00FF);

    if (command_id == 0x55) // turn PFC stage on or off
    {
      if (control_byte == 0x00) // stop PFC
      {
        if (PFC_Flags.bits.Run)
        {
          PFC_Flags.bits.Run = 0;
          PFC_Flags.bits.Stop = 1;
        }
      }
      else if (control_byte) // 1 for single phase, 3 for 3 phase, TODO: implement this
      {
        if (!PFC_Flags.bits.Run)
        {
          PFC_Flags.bits.Run = 1;
          PFC_Flags.bits.Stop = 0;
        }
      }
      pMSIAdata[0] = 0;
    }
    else if (command_id == 0xEF) // change output voltage setpoint
    {
      Vout_Control.Reference.Reference_Set = pMSIAdata[1];
      if (Vout_Control.Reference.Reference_Set > 3500) Vout_Control.Reference.Reference_Set = 3500;

      pMSIAdata[0] = 0;
      pMSIAdata[1] = 0;
    }

  }
  
}

//------------------------------------------------------------------------------
//<< FIFO init write from sec to prim
//------------------------------------------------------------------------------

void SendMSIFIFOMessage(void)
{
  static uint16_t TickCounter_ = 0;

  if (++TickCounter_ > 50) // >1 is the absolut min which works; 50=5ms
  {
    FIFOData_SendToPrim();
    TickCounter_ = 0;
  }
}

//------------------------------------------------------------------------------

void __inline__ FIFOData_SendToPrim(void)
{
  static uint16_t i_;
  
  // duty cycle values for each phase
  SWMRFDATA = Phase_Values_PH1.Controller_Values.Duty_Cycle_Set_Value;  // word 0 (CAN word 7)
  SWMRFDATA = Phase_Values_PH2.Controller_Values.Duty_Cycle_Set_Value;  // word 1 
  SWMRFDATA = Phase_Values_PH3.Controller_Values.Duty_Cycle_Set_Value;  // word 2  

  // secondary core revision data
  SWMRFDATA = (uint16_t)((MAJOR << 8) + MINOR);                         // word 3
  SWMRFDATA = (uint16_t)((PATCH << 8) + HIGHVOLTAGE);                   // word 4   
  
  // current loop reference for each phase
  SWMRFDATA = Phase_Values_PH1.Controller_Values.IAC_Reference;         // word 5 
  
//  SWMRFDATA = Phase_Values_PH2.Controller_Values.IAC_Reference;         // word 6 
  SWMRFDATA = (Vout_Control.Reference.Reference_Internal-Vout_Control.Vout.Filtered);
  
//  SWMRFDATA = Phase_Values_PH3.Controller_Values.IAC_Reference;         // word 7 
  SWMRFDATA = Vout_Control.Reference.Voltage_Loop_Output;
  
  // state variable (de-coded for power board visualizer GUI)
  SWMRFDATA = (1 << ((uint16_t)pwr_ctrl_state-1));                      // word 8        
  
  // status flags
  SWMRFDATA = PFC_Flags.value;                                          // word 9 
  
  // voltage loop reference
  SWMRFDATA = Vout_Control.Reference.Reference_Internal;                // word 10
   
  // measured output voltage (filtered)
  SWMRFDATA = Vout_Control.Vout.Filtered;                               // word 11 
  
  // FIFO is 32 words wide, all words needs to be filled up to initiate transmission to primary core
  for(i_= 12; i_< 32; i_++)
  {    
    SWMRFDATA = i_;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 End of File
 */

