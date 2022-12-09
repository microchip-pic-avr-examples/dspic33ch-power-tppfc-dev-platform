/**
  Summary:
  This header file was created using Microchip Digital Compensator Design Tool (DCDT)
  and includes system summary and digital compensator coefficients. This file
  should be included in the MPLAB X project directory.

  File Name:     vcomp1ph_dcdt.h
  Project Name:  vcomp1ph
  Date:          12/2/2022
  Time:          8:13.44

  Software License Agreement

  Copyright © 2022 Microchip Technology Inc.  All rights reserved.
  Microchip licenses to you the right to use, modify, copy and distribute
  Software only when embedded on a Microchip microcontroller or digital
  signal controller, which is integrated into your product or third party
  product (pursuant to the sublicense terms in the accompanying license
  agreement).

  You should refer to the license agreement accompanying this Software
  for additional information regarding your rights and obligations.

  SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
  OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
  PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
  OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
  BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
  DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
  INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
  CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
  OR OTHER SIMILAR COSTS.
 **/
#ifndef _VCOMP1PH_DCDT_DEFINES_H
#define _VCOMP1PH_DCDT_DEFINES_H

/**
  Compensator Type:  2P2Z
      Entry                Value  
    ---------            ---------
  Pole 0                 5.0000e+01 Hz
  Pole 2                 2.5000e+02 Hz
  Zero 1                 3.0000e+00 Hz
  Gain(Kdc)              2.000
  Warp                   false
  PWM Frequency          1.0000e+05
  PWM Sampling Ratio     1000
  Sampling Frequency     1.0000e+02
  PWM Max Resolution     2.5000e-10
  Computational Delay    1.0000e-06
  Gate Drive Delay       5.0000e-08
  Control Output Min.    0
  Control Output Max.    32000
  Kuc Gain               3.2234e+01
  Use Kuc Gain           false


  PWM Calculations
      Name                Value  
    ---------           ---------
  Bits of Resolution    25.253
  Gain                  2.500e-08


  s-domain transfer function

               Wp0   Wp2(Wz1 + s)
  H(s) = Kdc X --- X ------------
                s    Wz1(Wp2 + s)

                  3.14e+02   1.57e+03(1.88e+01 + s)
  H(s) = 2.000 X -------- X ----------------------
                     s       1.88e+01(1.57e+03 + s)



  Digital Compensator Coefficients

  Name    Value      Normalized    Q15      Hex
  ----    -----      ----------    ---      ---
  a1      0.226      0.007         228      0x00E4
  a2      0.774      0.024         783      0x030F
  b0      32.355     1.000         32764    0x7FFC
  b1      5.574      0.172         5644     0x160C
  b2      -26.782    -0.828        -27120   0x9610


  z-domain transfer function

         u(z)  B0 + B1z^(-1) + B2z^(-2)
  H(z) = --- = ------------------------
         e(z)  A0 - A1z^(-1) - A2z^(-2)

          (32.355) + (5.574)z^(-1) + (-26.782)z^(-2)
  H(z) = ---------------------------------------------
          1 - (0.226)z^(-1) - (0.774)z^(-2)

**/


// Compensator Coefficient Defines
#define VCOMP1PH_COMP_2P2Z_COEFF_A1      0x00E4
#define VCOMP1PH_COMP_2P2Z_COEFF_A2      0x030F
#define VCOMP1PH_COMP_2P2Z_COEFF_B0      0x7FFC
#define VCOMP1PH_COMP_2P2Z_COEFF_B1      0x160C
#define VCOMP1PH_COMP_2P2Z_COEFF_B2      0x9610
#define VCOMP1PH_COMP_2P2Z_POSTSCALER    0x40B7
#define VCOMP1PH_COMP_2P2Z_POSTSHIFT     0xFFFA
#define VCOMP1PH_COMP_2P2Z_PRESHIFT      0x0000


// Compensator Clamp Limits
#define VCOMP1PH_COMP_2P2Z_MIN_CLAMP    0x0000
#define VCOMP1PH_COMP_2P2Z_MAX_CLAMP    0x7D00


#endif
