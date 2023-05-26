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

#include "main.h"

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/slave1.h"
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/i2c2.h"
#include "sources/driver/i2c/drv_i2c.h"

#include "sources/driver/spi/drv_spi.h"
#include "can/drv_can.h"
#include "mcc_generated_files/dma.h"
#include "mcc_generated_files/tmr1.h"
#include "sources/driver/vac_monitor/vac_monitor.h"
#include "sources/driver/dma/drv_dma.h"
#include "watchdog.h"

//------------------------------------------------------------------------------
// Main Application
//------------------------------------------------------------------------------

int main(void)
{
  // initialize the primary core peripherals
  SYSTEM_Initialize();
  
  // enable watchdog timer
  WATCHDOG_TimerSoftwareEnable();
  
  // ensure that DMA channel 0 is disabled until we have sync'd to SPI bus
  // (channel 0 should already be disabled via MCC settings, but just in case)
  // see SPI_Synchronize() in drv_spi.c for more details on enabling DMA 
  // between SPI messages
  DMA_ChannelDisable(0);

  // initialize secondary core
  SLAVE1_Program();
  SLAVE1_Start();
  
  // initialize CAN transmit object
  CAN_TX_Obj_Init();
  
  // initialize DMA data Object
  DRV_DMA_init();

  // initialize FIFO that is used to send data from secondary core to primary core
  MSI1FIFOCSbits.RFEN = 1;
  MSI1FIFOCSbits.WFEN = 0;

  // preset SPI timeout counter
  Drv_SPI_Reset_Timeout_Counter(SPI_TIMEOUT_IN_100us_TICKS);    
  
  while (1)
  {
    Tasks_Background();

    // simple 100us task driven by timer 1 (setup in MCC to expire after 100us)
    // this process is polled, not interrupt driven
    if (IFS0bits.T1IF)
    {
      Tasks_100us();
      IFS0bits.T1IF = 0; // clear timer 1 flag 
    }
  }
  return 1;
} // end of main()

