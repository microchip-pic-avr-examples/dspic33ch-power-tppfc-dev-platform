/**
  Summary:
  This header file was created using Microchip Digital Compensator Design Tool (DCDT)
  and includes system summary and digital compensator coefficients. This file
  should be included in the MPLAB X project directory.

  File Name:     icomp3lv_dcdt.h
  Project Name:  icomp3lv
  Date:          12/1/2022
  Time:          15:58.14

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
#ifndef _ICOMP3LV_DCDT_DEFINES_H
#define _ICOMP3LV_DCDT_DEFINES_H

/**
  Compensator Type:  2P2Z
      Entry                Value  
    ---------            ---------
  Pole 0                 1.5000e+03 Hz
  Pole 2                 5.0000e+04 Hz
  Zero 1                 6.0000e+02 Hz
  Gain(Kdc)              1.000
  Warp                   false
  PWM Frequency          1.0000e+05
  PWM Sampling Ratio     1
  Sampling Frequency     1.0000e+05
  PWM Max Resolution     2.5000e-10
  Computational Delay    1.0000e-06
  Gate Drive Delay       5.0000e-08
  Control Output Min.    0
  Control Output Max.    19200


  PWM Calculations
      Name                Value  
    ---------           ---------
  Bits of Resolution    15.288
  Gain                  2.500e-05


  s-domain transfer function

               Wp0   Wp2(Wz1 + s)
  H(s) = Kdc X --- X ------------
                s    Wz1(Wp2 + s)

                  9.42e+03   3.14e+05(3.77e+03 + s)
  H(s) = 1.000 X -------- X ----------------------
                     s       3.77e+03(3.14e+05 + s)



  Digital Compensator Coefficients

  Name    Value     Normalized    Q15      Hex
  ----    -----     ----------    ---      ---
  a1      0.778     0.500         16378    0x3FFA
  a2      0.222     0.143         4674     0x1242
  b0      1.556     1.000         32764    0x7FFC
  b1      0.058     0.037         1212     0x04BC
  b2      -1.499    -0.963        -31552   0x84C0


  z-domain transfer function

         u(z)  B0 + B1z^(-1) + B2z^(-2)
  H(z) = --- = ------------------------
         e(z)  A0 - A1z^(-1) - A2z^(-2)

          (1.556) + (0.058)z^(-1) + (-1.499)z^(-2)
  H(z) = ---------------------------------------------
          1 - (0.778)z^(-1) - (0.222)z^(-2)

**/


// Compensator Coefficient Defines
#define ICOMP3LV_COMP_2P2Z_COEFF_A1      0x3FFA
#define ICOMP3LV_COMP_2P2Z_COEFF_A2      0x1242
#define ICOMP3LV_COMP_2P2Z_COEFF_B0      0x7FFC
#define ICOMP3LV_COMP_2P2Z_COEFF_B1      0x04BC
#define ICOMP3LV_COMP_2P2Z_COEFF_B2      0x84C0
#define ICOMP3LV_COMP_2P2Z_POSTSCALER    0x639D
#define ICOMP3LV_COMP_2P2Z_POSTSHIFT     0xFFFF
#define ICOMP3LV_COMP_2P2Z_PRESHIFT      0x0000


// Compensator Clamp Limits
#define ICOMP3LV_COMP_2P2Z_MIN_CLAMP    0x0000
#define ICOMP3LV_COMP_2P2Z_MAX_CLAMP    0x4B00


#endif
