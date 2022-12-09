/**
  Summary:
  This header file was created using Microchip Digital Compensator Design Tool (DCDT)
  and includes system summary and digital compensator coefficients. This file
  should be included in the MPLAB X project directory.

  File Name:     vcomp3ph_dcdt.h
  Project Name:  vcomp3ph
  Date:          12/1/2022
  Time:          18:04.14

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
#ifndef _VCOMP3PH_DCDT_DEFINES_H
#define _VCOMP3PH_DCDT_DEFINES_H

/**
  Compensator Type:  2P2Z
      Entry                Value  
    ---------            ---------
  Pole 0                 4.0000e+01 Hz
  Pole 2                 6.0000e+01 Hz
  Zero 1                 3.0000e+00 Hz
  Gain(Kdc)              2.000
  Warp                   false
  PWM Frequency          1.0000e+05
  PWM Sampling Ratio     333
  Sampling Frequency     3.0030e+02
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
  Bits of Resolution    23.667
  Gain                  7.508e-08


  s-domain transfer function

               Wp0   Wp2(Wz1 + s)
  H(s) = Kdc X --- X ------------
                s    Wz1(Wp2 + s)

                  2.51e+02   3.77e+02(1.88e+01 + s)
  H(s) = 2.000 X -------- X ----------------------
                     s       1.88e+01(3.77e+02 + s)



  Digital Compensator Coefficients

  Name    Value     Normalized    Q15      Hex
  ----    -----     ----------    ---      ---
  a1      1.229     0.116         3795     0x0ED3
  a2      -0.229    -0.022        -706     0xFD3E
  b0      10.606    1.000         32764    0x7FFC
  b1      0.645     0.061         1994     0x07CA
  b2      -9.961    -0.939        -30770   0x87CE


  z-domain transfer function

         u(z)  B0 + B1z^(-1) + B2z^(-2)
  H(z) = --- = ------------------------
         e(z)  A0 - A1z^(-1) - A2z^(-2)

          (10.606) + (0.645)z^(-1) + (-9.961)z^(-2)
  H(z) = ---------------------------------------------
          1 - (1.229)z^(-1) - (-0.229)z^(-2)

**/


// Compensator Coefficient Defines
#define VCOMP3PH_COMP_2P2Z_COEFF_A1      0x0ED3
#define VCOMP3PH_COMP_2P2Z_COEFF_A2      0xFD3E
#define VCOMP3PH_COMP_2P2Z_COEFF_B0      0x7FFC
#define VCOMP3PH_COMP_2P2Z_COEFF_B1      0x07CA
#define VCOMP3PH_COMP_2P2Z_COEFF_B2      0x87CE
#define VCOMP3PH_COMP_2P2Z_POSTSCALER    0x54DB
#define VCOMP3PH_COMP_2P2Z_POSTSHIFT     0xFFFC
#define VCOMP3PH_COMP_2P2Z_PRESHIFT      0x0000


// Compensator Clamp Limits
#define VCOMP3PH_COMP_2P2Z_MIN_CLAMP    0x0000
#define VCOMP3PH_COMP_2P2Z_MAX_CLAMP    0x7D00


#endif
