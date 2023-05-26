/**
  @Company
    Microchip Technology Inc.

  @File Name
    Controller_pwrctrl_TPBLPFC.h

  @Summary
    This is the generated driver implementation file using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides Controller settings for average current mode and voltage mode controller.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.167.0
        Device            :  dsPIC33CK256MP506      
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
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

#include "drv_controller_TPBLPFC.h"
#include "drv_usersetup_TPBLPFC.h" 

SMPS_2P2Z_T VMC_2p2z;
SMPS_2P2Z_T PHx_AVG_CM2p2z[4];

//======================================================================================================================
//@brief SMPS_2P2Z_T AVG_CM2p2z //typedef from smps_control.h to var
//======================================================================================================================

int16_t   PH1_AVG_CM2p2zErrorHistory[3] __attribute__((space(ymemory), far));
int16_t   PH1_AVG_CM2p2zACoefficients[2]__attribute__((space(xmemory)));
int16_t   PH1_AVG_CM2p2zControlHistory[2] __attribute__((space(ymemory), far));
int16_t   PH1_AVG_CM2p2zBCoefficients[3] __attribute__((space(xmemory)));
uint16_t  PH1_AVG_CM2p2zReferenceSet;

int16_t   PH2_AVG_CM2p2zErrorHistory[3] __attribute__((space(ymemory), far));
int16_t   PH2_AVG_CM2p2zACoefficients[2]__attribute__((space(xmemory)));
int16_t   PH2_AVG_CM2p2zControlHistory[2] __attribute__((space(ymemory), far));
int16_t   PH2_AVG_CM2p2zBCoefficients[3] __attribute__((space(xmemory)));
uint16_t  PH2_AVG_CM2p2zReferenceSet;

int16_t   PH3_AVG_CM2p2zErrorHistory[3] __attribute__((space(ymemory), far));
int16_t   PH3_AVG_CM2p2zACoefficients[2]__attribute__((space(xmemory)));
int16_t   PH3_AVG_CM2p2zControlHistory[2] __attribute__((space(ymemory), far));
int16_t   PH3_AVG_CM2p2zBCoefficients[3] __attribute__((space(xmemory)));
uint16_t  PH3_AVG_CM2p2zReferenceSet;

//======================================================================================================================
//@brief SMPS_2P2Z_T VMC_2p2z //typedef from smps_control.h to var
//======================================================================================================================

int16_t   VMC_2p2zErrorHistory[3] __attribute__((space(ymemory), far));
int16_t   VMC_2p2zACoefficients[2]__attribute__((space(xmemory)));
int16_t   VMC_2p2zControlHistory[2] __attribute__((space(ymemory), far));
int16_t   VMC_2p2zBCoefficients[3] __attribute__((space(xmemory)));
uint16_t  VMC_2p2zReferenceSet;

/*******************************************************************************
 * @fn        current loop compensator setup based on mode    
 * @brief      
 * @param     none
 * @return    none
 * @details    
 *             
 *              
 *             
 *******************************************************************************/
  
void CurrentController_PwrCtrl_TPBLPFC_Init(void)
{
  uint16_t i_;
  
  PHx_AVG_CM2p2z[1].aCoefficients = &PH1_AVG_CM2p2zACoefficients[0]; // Set up pointer to derived coefficients
  PHx_AVG_CM2p2z[1].bCoefficients = &PH1_AVG_CM2p2zBCoefficients[0]; // Set up pointer to derived coefficients
  PHx_AVG_CM2p2z[1].controlHistory = &PH1_AVG_CM2p2zControlHistory[0]; // Set up pointer to controller history
  PHx_AVG_CM2p2z[1].errorHistory = &PH1_AVG_CM2p2zErrorHistory[0]; // Set up pointer to error history

  PHx_AVG_CM2p2z[2].aCoefficients = &PH2_AVG_CM2p2zACoefficients[0]; // Set up pointer to derived coefficients
  PHx_AVG_CM2p2z[2].bCoefficients = &PH2_AVG_CM2p2zBCoefficients[0]; // Set up pointer to derived coefficients
  PHx_AVG_CM2p2z[2].controlHistory = &PH2_AVG_CM2p2zControlHistory[0]; // Set up pointer to controller history
  PHx_AVG_CM2p2z[2].errorHistory = &PH2_AVG_CM2p2zErrorHistory[0]; // Set up pointer to error history

  PHx_AVG_CM2p2z[3].aCoefficients = &PH3_AVG_CM2p2zACoefficients[0]; // Set up pointer to derived coefficients
  PHx_AVG_CM2p2z[3].bCoefficients = &PH3_AVG_CM2p2zBCoefficients[0]; // Set up pointer to derived coefficients
  PHx_AVG_CM2p2z[3].controlHistory = &PH3_AVG_CM2p2zControlHistory[0]; // Set up pointer to controller history
  PHx_AVG_CM2p2z[3].errorHistory = &PH3_AVG_CM2p2zErrorHistory[0]; // Set up pointer to error history


#if defined ThreePhase==0 && High_Voltage==0
  for(i_=0; i_<4; i_++)
  {  
    PHx_AVG_CM2p2z[i_].preShift = ICOMP1LV_COMP_2P2Z_PRESHIFT;
    PHx_AVG_CM2p2z[i_].postScaler = ICOMP1LV_COMP_2P2Z_POSTSCALER;
    PHx_AVG_CM2p2z[i_].postShift = ICOMP1LV_COMP_2P2Z_POSTSHIFT;
    PHx_AVG_CM2p2z[i_].minOutput = ICOMP1LV_COMP_2P2Z_MIN_CLAMP;
    PHx_AVG_CM2p2z[i_].maxOutput = ICOMP1LV_COMP_2P2Z_MAX_CLAMP; 
  }
  //Set coefficients
  PH1_AVG_CM2p2zACoefficients[0] = ICOMP1LV_COMP_2P2Z_COEFF_A1;
  PH1_AVG_CM2p2zACoefficients[1] = ICOMP1LV_COMP_2P2Z_COEFF_A2;
  PH1_AVG_CM2p2zBCoefficients[0] = ICOMP1LV_COMP_2P2Z_COEFF_B0;
  PH1_AVG_CM2p2zBCoefficients[1] = ICOMP1LV_COMP_2P2Z_COEFF_B1;
  PH1_AVG_CM2p2zBCoefficients[2] = ICOMP1LV_COMP_2P2Z_COEFF_B2;
  
  PH2_AVG_CM2p2zACoefficients[0] = ICOMP1LV_COMP_2P2Z_COEFF_A1;
  PH2_AVG_CM2p2zACoefficients[1] = ICOMP1LV_COMP_2P2Z_COEFF_A2;
  PH2_AVG_CM2p2zBCoefficients[0] = ICOMP1LV_COMP_2P2Z_COEFF_B0;
  PH2_AVG_CM2p2zBCoefficients[1] = ICOMP1LV_COMP_2P2Z_COEFF_B1;
  PH2_AVG_CM2p2zBCoefficients[2] = ICOMP1LV_COMP_2P2Z_COEFF_B2;
  
  PH3_AVG_CM2p2zACoefficients[0] = ICOMP1LV_COMP_2P2Z_COEFF_A1;
  PH3_AVG_CM2p2zACoefficients[1] = ICOMP1LV_COMP_2P2Z_COEFF_A2;
  PH3_AVG_CM2p2zBCoefficients[0] = ICOMP1LV_COMP_2P2Z_COEFF_B0;
  PH3_AVG_CM2p2zBCoefficients[1] = ICOMP1LV_COMP_2P2Z_COEFF_B1;
  PH3_AVG_CM2p2zBCoefficients[2] = ICOMP1LV_COMP_2P2Z_COEFF_B2;
#endif 

#if defined Reverse==0 && defined ThreePhase==0 && High_Voltage==1
  for(i_=0; i_<4; i_++)
  {  
    PHx_AVG_CM2p2z[i_].preShift = ICOMP1HV_COMP_2P2Z_PRESHIFT;
    PHx_AVG_CM2p2z[i_].postScaler = ICOMP1HV_COMP_2P2Z_POSTSCALER;
    PHx_AVG_CM2p2z[i_].postShift = ICOMP1HV_COMP_2P2Z_POSTSHIFT;
    PHx_AVG_CM2p2z[i_].minOutput = ICOMP1HV_COMP_2P2Z_MIN_CLAMP;
    PHx_AVG_CM2p2z[i_].maxOutput = ICOMP1HV_COMP_2P2Z_MAX_CLAMP; 
  }
  //Set coefficients
  PH1_AVG_CM2p2zACoefficients[0] = ICOMP1HV_COMP_2P2Z_COEFF_A1;
  PH1_AVG_CM2p2zACoefficients[1] = ICOMP1HV_COMP_2P2Z_COEFF_A2;
  PH1_AVG_CM2p2zBCoefficients[0] = ICOMP1HV_COMP_2P2Z_COEFF_B0;
  PH1_AVG_CM2p2zBCoefficients[1] = ICOMP1HV_COMP_2P2Z_COEFF_B1;
  PH1_AVG_CM2p2zBCoefficients[2] = ICOMP1HV_COMP_2P2Z_COEFF_B2;
  
  PH2_AVG_CM2p2zACoefficients[0] = ICOMP1HV_COMP_2P2Z_COEFF_A1;
  PH2_AVG_CM2p2zACoefficients[1] = ICOMP1HV_COMP_2P2Z_COEFF_A2;
  PH2_AVG_CM2p2zBCoefficients[0] = ICOMP1HV_COMP_2P2Z_COEFF_B0;
  PH2_AVG_CM2p2zBCoefficients[1] = ICOMP1HV_COMP_2P2Z_COEFF_B1;
  PH2_AVG_CM2p2zBCoefficients[2] = ICOMP1HV_COMP_2P2Z_COEFF_B2;
  
  PH3_AVG_CM2p2zACoefficients[0] = ICOMP1HV_COMP_2P2Z_COEFF_A1;
  PH3_AVG_CM2p2zACoefficients[1] = ICOMP1HV_COMP_2P2Z_COEFF_A2;
  PH3_AVG_CM2p2zBCoefficients[0] = ICOMP1HV_COMP_2P2Z_COEFF_B0;
  PH3_AVG_CM2p2zBCoefficients[1] = ICOMP1HV_COMP_2P2Z_COEFF_B1;
  PH3_AVG_CM2p2zBCoefficients[2] = ICOMP1HV_COMP_2P2Z_COEFF_B2;
#endif 
  
#if defined ThreePhase==1 && High_Voltage==0
 for(i_=0; i_<4; i_++)
  {  
    PHx_AVG_CM2p2z[i_].preShift = ICOMP3LV_COMP_2P2Z_PRESHIFT;
    PHx_AVG_CM2p2z[i_].postScaler = ICOMP3LV_COMP_2P2Z_POSTSCALER;
    PHx_AVG_CM2p2z[i_].postShift = ICOMP3LV_COMP_2P2Z_POSTSHIFT;
    PHx_AVG_CM2p2z[i_].minOutput = ICOMP3LV_COMP_2P2Z_MIN_CLAMP;
    PHx_AVG_CM2p2z[i_].maxOutput = ICOMP3LV_COMP_2P2Z_MAX_CLAMP; 
  }
  //Set coefficients
  PH1_AVG_CM2p2zACoefficients[0] = ICOMP3LV_COMP_2P2Z_COEFF_A1;
  PH1_AVG_CM2p2zACoefficients[1] = ICOMP3LV_COMP_2P2Z_COEFF_A2;
  PH1_AVG_CM2p2zBCoefficients[0] = ICOMP3LV_COMP_2P2Z_COEFF_B0;
  PH1_AVG_CM2p2zBCoefficients[1] = ICOMP3LV_COMP_2P2Z_COEFF_B1;
  PH1_AVG_CM2p2zBCoefficients[2] = ICOMP3LV_COMP_2P2Z_COEFF_B2;
  
  PH2_AVG_CM2p2zACoefficients[0] = ICOMP3LV_COMP_2P2Z_COEFF_A1;
  PH2_AVG_CM2p2zACoefficients[1] = ICOMP3LV_COMP_2P2Z_COEFF_A2;
  PH2_AVG_CM2p2zBCoefficients[0] = ICOMP3LV_COMP_2P2Z_COEFF_B0;
  PH2_AVG_CM2p2zBCoefficients[1] = ICOMP3LV_COMP_2P2Z_COEFF_B1;
  PH2_AVG_CM2p2zBCoefficients[2] = ICOMP3LV_COMP_2P2Z_COEFF_B2;
  
  PH3_AVG_CM2p2zACoefficients[0] = ICOMP3LV_COMP_2P2Z_COEFF_A1;
  PH3_AVG_CM2p2zACoefficients[1] = ICOMP3LV_COMP_2P2Z_COEFF_A2;
  PH3_AVG_CM2p2zBCoefficients[0] = ICOMP3LV_COMP_2P2Z_COEFF_B0;
  PH3_AVG_CM2p2zBCoefficients[1] = ICOMP3LV_COMP_2P2Z_COEFF_B1;
  PH3_AVG_CM2p2zBCoefficients[2] = ICOMP3LV_COMP_2P2Z_COEFF_B2;
#endif
  
 #if defined Reverse==0 && defined ThreePhase==1 && High_Voltage==1
 for(i_=0; i_<4; i_++)
  {  
    PHx_AVG_CM2p2z[i_].preShift = ICOMP3HV_COMP_2P2Z_PRESHIFT;
    PHx_AVG_CM2p2z[i_].postScaler = ICOMP3HV_COMP_2P2Z_POSTSCALER;
    PHx_AVG_CM2p2z[i_].postShift = ICOMP3HV_COMP_2P2Z_POSTSHIFT;
    PHx_AVG_CM2p2z[i_].minOutput = ICOMP3HV_COMP_2P2Z_MIN_CLAMP;
    PHx_AVG_CM2p2z[i_].maxOutput = ICOMP3HV_COMP_2P2Z_MAX_CLAMP; 
  }
  //Set coefficients
  PH1_AVG_CM2p2zACoefficients[0] = ICOMP3HV_COMP_2P2Z_COEFF_A1;
  PH1_AVG_CM2p2zACoefficients[1] = ICOMP3HV_COMP_2P2Z_COEFF_A2;
  PH1_AVG_CM2p2zBCoefficients[0] = ICOMP3HV_COMP_2P2Z_COEFF_B0;
  PH1_AVG_CM2p2zBCoefficients[1] = ICOMP3HV_COMP_2P2Z_COEFF_B1;
  PH1_AVG_CM2p2zBCoefficients[2] = ICOMP3HV_COMP_2P2Z_COEFF_B2;
  
  PH2_AVG_CM2p2zACoefficients[0] = ICOMP3HV_COMP_2P2Z_COEFF_A1;
  PH2_AVG_CM2p2zACoefficients[1] = ICOMP3HV_COMP_2P2Z_COEFF_A2;
  PH2_AVG_CM2p2zBCoefficients[0] = ICOMP3HV_COMP_2P2Z_COEFF_B0;
  PH2_AVG_CM2p2zBCoefficients[1] = ICOMP3HV_COMP_2P2Z_COEFF_B1;
  PH2_AVG_CM2p2zBCoefficients[2] = ICOMP3HV_COMP_2P2Z_COEFF_B2;
  
  PH3_AVG_CM2p2zACoefficients[0] = ICOMP3HV_COMP_2P2Z_COEFF_A1;
  PH3_AVG_CM2p2zACoefficients[1] = ICOMP3HV_COMP_2P2Z_COEFF_A2;
  PH3_AVG_CM2p2zBCoefficients[0] = ICOMP3HV_COMP_2P2Z_COEFF_B0;
  PH3_AVG_CM2p2zBCoefficients[1] = ICOMP3HV_COMP_2P2Z_COEFF_B1;
  PH3_AVG_CM2p2zBCoefficients[2] = ICOMP3HV_COMP_2P2Z_COEFF_B2;
#endif
  
  PH1_AVG_CM2p2zReferenceSet = 0;
  PH2_AVG_CM2p2zReferenceSet = 0;
  PH3_AVG_CM2p2zReferenceSet = 0;
  
  SMPS_Controller2P2ZInitialize(&PHx_AVG_CM2p2z[1]); // Clear histories
  SMPS_Controller2P2ZInitialize(&PHx_AVG_CM2p2z[2]); // Clear histories
  SMPS_Controller2P2ZInitialize(&PHx_AVG_CM2p2z[3]); // Clear histories
  
}
/*******************************************************************************
 * @fn        voltage loop compensator setup based on mode    
 * @brief      
 * @param      none
 * @return     none
 * @details    
 *             
 *              
 *             
 *******************************************************************************/

void VoltageController_PwrCtrl_TPBLPFC_Init(void)
{
  VMC_2p2z.aCoefficients = &VMC_2p2zACoefficients[0]; // Set up pointer to derived coefficients
  VMC_2p2z.bCoefficients = &VMC_2p2zBCoefficients[0]; // Set up pointer to derived coefficients
  VMC_2p2z.controlHistory = &VMC_2p2zControlHistory[0]; // Set up pointer to controller history
  VMC_2p2z.errorHistory = &VMC_2p2zErrorHistory[0]; // Set up pointer to error history

#ifndef ThreePhase
  VMC_2p2z.preShift = VCOMP1PH_COMP_2P2Z_PRESHIFT;
  VMC_2p2z.postScaler = VCOMP1PH_COMP_2P2Z_POSTSCALER;
  VMC_2p2z.postShift = VCOMP1PH_COMP_2P2Z_POSTSHIFT;
  VMC_2p2z.minOutput = VCOMP1PH_COMP_2P2Z_MIN_CLAMP;
  VMC_2p2z.maxOutput = VCOMP1PH_COMP_2P2Z_MAX_CLAMP;
  //Set coefficients
  VMC_2p2zACoefficients[0] = VCOMP1PH_COMP_2P2Z_COEFF_A1;
  VMC_2p2zACoefficients[1] = VCOMP1PH_COMP_2P2Z_COEFF_A2;
  VMC_2p2zBCoefficients[0] = VCOMP1PH_COMP_2P2Z_COEFF_B0;
  VMC_2p2zBCoefficients[1] = VCOMP1PH_COMP_2P2Z_COEFF_B1;
  VMC_2p2zBCoefficients[2] = VCOMP1PH_COMP_2P2Z_COEFF_B2;
#else
  VMC_2p2z.preShift = VCOMP3PH_COMP_2P2Z_PRESHIFT; // Normalization shift for error amplifier results
  VMC_2p2z.postScaler = VCOMP3PH_COMP_2P2Z_POSTSCALER;
  VMC_2p2z.postShift = VCOMP3PH_COMP_2P2Z_POSTSHIFT; // Normalization shift for control loop results to peripheral
  VMC_2p2z.minOutput = VCOMP3PH_COMP_2P2Z_MIN_CLAMP; //;PG1DCmin;
  VMC_2p2z.maxOutput = VCOMP3PH_COMP_2P2Z_MAX_CLAMP; //PG1DCmax; 0;//FTX FTX
  //Set coefficients
  VMC_2p2zACoefficients[0] = VCOMP3PH_COMP_2P2Z_COEFF_A1;
  VMC_2p2zACoefficients[1] = VCOMP3PH_COMP_2P2Z_COEFF_A2;
  VMC_2p2zBCoefficients[0] = VCOMP3PH_COMP_2P2Z_COEFF_B0;
  VMC_2p2zBCoefficients[1] = VCOMP3PH_COMP_2P2Z_COEFF_B1;
  VMC_2p2zBCoefficients[2] = VCOMP3PH_COMP_2P2Z_COEFF_B2;
#endif  

  VMC_2p2zReferenceSet = 0;

  SMPS_Controller2P2ZInitialize(&VMC_2p2z); // Clear histories

}

//==============================================================================
//==============================================================================

