/**
  DMA Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    dma.c

  @Summary
    This is the generated driver implementation file for the DMA driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for DMA.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CH512MP506
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
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

/**
  Section: Included Files
*/

#include "dma.h"

/**
  Prototype:        void DMA_Initialize(void)
  Input:            none
  Output:           none
  Description:      DMA_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            DMA_Initialize();
 */
void DMA_Initialize(void) 
{ 
    // DMAEN enabled; PRSSEL Fixed priority; 
    DMACON = (0x8000 | 0x01) & 0x7FFF; //Enable DMA later
    // LADDR 6144; 
    DMAL= 0x1800;
    // HADDR 20479; 
    DMAH= 0x4FFF;

    // CHEN disabled; DAMODE Incremented; TRMODE One-Shot; CHREQ disabled; RELOAD enabled; SIZE 16 bit; NULLW disabled; SAMODE Unchanged; 
    DMACH0 = 0x210 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF enabled; OVRUNIF disabled; CHSEL SPI1 RX; HIGHIF disabled; 
    DMAINT0= 0x220;
    // SADDR 696; 
    DMASRC0= 0x2B8;
    // DADDR 0; 
    DMADST0= 0x00;
    // CNT 4; 
    DMACNT0= 0x04;
    // Clearing Channel 0 Interrupt Flag;
    IFS0bits.DMA0IF = false;
    // Enabling Channel 0 Interrupt
    IEC0bits.DMA0IE = true;

    // CHEN disabled; SAMODE Unchanged; SIZE 16 bit; DAMODE Unchanged; CHREQ disabled; RELOAD disabled; TRMODE One-Shot; NULLW disabled; 
    DMACH1 = 0x00 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL INT0; 
    DMAINT1= 0x00;
    // SADDR 0; 
    DMASRC1= 0x00;
    // DADDR 0; 
    DMADST1= 0x00;
    // CNT 0; 
    DMACNT1= 0x00;
    // Clearing Channel 1 Interrupt Flag;
    IFS0bits.DMA1IF = false;

    // SAMODE Unchanged; CHEN disabled; SIZE 16 bit; DAMODE Unchanged; CHREQ disabled; RELOAD disabled; NULLW disabled; TRMODE One-Shot; 
    DMACH2 = 0x00 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL INT0; 
    DMAINT2= 0x00;
    // SADDR 0; 
    DMASRC2= 0x00;
    // DADDR 0; 
    DMADST2= 0x00;
    // CNT 0; 
    DMACNT2= 0x00;
    // Clearing Channel 2 Interrupt Flag;
    IFS1bits.DMA2IF = false;

    // SAMODE Unchanged; CHEN disabled; SIZE 16 bit; DAMODE Unchanged; TRMODE One-Shot; NULLW disabled; CHREQ disabled; RELOAD disabled; 
    DMACH3 = 0x00 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; CHSEL INT0; HIGHIF disabled; 
    DMAINT3= 0x00;
    // SADDR 0; 
    DMASRC3= 0x00;
    // DADDR 0; 
    DMADST3= 0x00;
    // CNT 0; 
    DMACNT3= 0x00;
    // Clearing Channel 3 Interrupt Flag;
    IFS1bits.DMA3IF = false;

    // DAMODE Unchanged; SAMODE Unchanged; CHEN disabled; SIZE 16 bit; TRMODE One-Shot; CHREQ disabled; RELOAD disabled; NULLW disabled; 
    DMACH4 = 0x00 & 0xFFFE; //Enable DMA Channel later;
    // HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; CHSEL INT0; 
    DMAINT4= 0x00;
    // SADDR 0; 
    DMASRC4= 0x00;
    // DADDR 0; 
    DMADST4= 0x00;
    // CNT 0; 
    DMACNT4= 0x00;
    // Clearing Channel 4 Interrupt Flag;
    IFS1bits.DMA4IF = false;

    // SIZE 16 bit; DAMODE Unchanged; CHEN disabled; SAMODE Unchanged; CHREQ disabled; RELOAD disabled; TRMODE One-Shot; NULLW disabled; 
    DMACH5 = 0x00 & 0xFFFE; //Enable DMA Channel later;
    // CHSEL INT0; HALFIF disabled; LOWIF disabled; HALFEN disabled; DONEIF disabled; OVRUNIF disabled; HIGHIF disabled; 
    DMAINT5= 0x00;
    // SADDR 0; 
    DMASRC5= 0x00;
    // DADDR 0; 
    DMADST5= 0x00;
    // CNT 0; 
    DMACNT5= 0x00;
    // Clearing Channel 5 Interrupt Flag;
    IFS2bits.DMA5IF = false;
    
    //Enable DMA
    DMACONbits.DMAEN = 1; 
    
}

void __attribute__ ((weak)) DMA_Channel0_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _DMA0Interrupt( void )
{
	// DMA Channel0 callback function 
	DMA_Channel0_CallBack();
	
    IFS0bits.DMA0IF = 0;
}
void __attribute__ ((weak)) DMA_Channel1_CallBack(void)
{
    // Add your custom callback code here
}

void DMA__Channel1_Tasks( void )
{
	if(IFS0bits.DMA1IF)
	{
		// DMA Channel1 callback function 
		DMA_Channel1_CallBack();
		
		IFS0bits.DMA1IF = 0;
	}
}
void __attribute__ ((weak)) DMA_Channel2_CallBack(void)
{
    // Add your custom callback code here
}

void DMA__Channel2_Tasks( void )
{
	if(IFS1bits.DMA2IF)
	{
		// DMA Channel2 callback function 
		DMA_Channel2_CallBack();
		
		IFS1bits.DMA2IF = 0;
	}
}
void __attribute__ ((weak)) DMA_Channel3_CallBack(void)
{
    // Add your custom callback code here
}

void DMA__Channel3_Tasks( void )
{
	if(IFS1bits.DMA3IF)
	{
		// DMA Channel3 callback function 
		DMA_Channel3_CallBack();
		
		IFS1bits.DMA3IF = 0;
	}
}
void __attribute__ ((weak)) DMA_Channel4_CallBack(void)
{
    // Add your custom callback code here
}

void DMA__Channel4_Tasks( void )
{
	if(IFS1bits.DMA4IF)
	{
		// DMA Channel4 callback function 
		DMA_Channel4_CallBack();
		
		IFS1bits.DMA4IF = 0;
	}
}
void __attribute__ ((weak)) DMA_Channel5_CallBack(void)
{
    // Add your custom callback code here
}

void DMA__Channel5_Tasks( void )
{
	if(IFS2bits.DMA5IF)
	{
		// DMA Channel5 callback function 
		DMA_Channel5_CallBack();
		
		IFS2bits.DMA5IF = 0;
	}
}

void DMA_ChannelEnable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DMACH0bits.CHEN = 1;
                break; 
        case DMA_CHANNEL_1:
                DMACH1bits.CHEN = 1;
                break; 
        case DMA_CHANNEL_2:
                DMACH2bits.CHEN = 1;
                break; 
        case DMA_CHANNEL_3:
                DMACH3bits.CHEN = 1;
                break; 
        case DMA_CHANNEL_4:
                DMACH4bits.CHEN = 1;
                break; 
        case DMA_CHANNEL_5:
                DMACH5bits.CHEN = 1;
                break; 
        default: break;
    }
}
void DMA_ChannelDisable(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DMACH0bits.CHEN = 0;
                break;    
        case DMA_CHANNEL_1:
                DMACH1bits.CHEN = 0;
                break;    
        case DMA_CHANNEL_2:
                DMACH2bits.CHEN = 0;
                break;    
        case DMA_CHANNEL_3:
                DMACH3bits.CHEN = 0;
                break;    
        case DMA_CHANNEL_4:
                DMACH4bits.CHEN = 0;
                break;    
        case DMA_CHANNEL_5:
                DMACH5bits.CHEN = 0;
                break;    
        default: break;
    }
}
void DMA_TransferCountSet(DMA_CHANNEL channel, uint16_t transferCount)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DMACNT0 = transferCount;
                break;
        case DMA_CHANNEL_1:
                DMACNT1 = transferCount;
                break;
        case DMA_CHANNEL_2:
                DMACNT2 = transferCount;
                break;
        case DMA_CHANNEL_3:
                DMACNT3 = transferCount;
                break;
        case DMA_CHANNEL_4:
                DMACNT4 = transferCount;
                break;
        case DMA_CHANNEL_5:
                DMACNT5 = transferCount;
                break;
        default: break;
    }
}
uint16_t DMA_TransferCountGet(DMA_CHANNEL channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return (DMACNT0);
        case DMA_CHANNEL_1:
                return (DMACNT1);
        case DMA_CHANNEL_2:
                return (DMACNT2);
        case DMA_CHANNEL_3:
                return (DMACNT3);
        case DMA_CHANNEL_4:
                return (DMACNT4);
        case DMA_CHANNEL_5:
                return (DMACNT5);
        default: return 0;
    }
}
void DMA_SoftwareTriggerEnable(DMA_CHANNEL channel )
{
    switch(channel) {
        case DMA_CHANNEL_0:
                DMACH0bits.CHREQ = 1;
                break;
        case DMA_CHANNEL_1:
                DMACH1bits.CHREQ = 1;
                break;
        case DMA_CHANNEL_2:
                DMACH2bits.CHREQ = 1;
                break;
        case DMA_CHANNEL_3:
                DMACH3bits.CHREQ = 1;
                break;
        case DMA_CHANNEL_4:
                DMACH4bits.CHREQ = 1;
                break;
        case DMA_CHANNEL_5:
                DMACH5bits.CHREQ = 1;
                break;
        default: break;
    }
}

void DMA_SourceAddressSet(DMA_CHANNEL  channel, uint16_t address) {
    switch(channel) {
        case DMA_CHANNEL_0:
                DMASRC0 = address;
                break;
        case DMA_CHANNEL_1:
                DMASRC1 = address;
                break;
        case DMA_CHANNEL_2:
                DMASRC2 = address;
                break;
        case DMA_CHANNEL_3:
                DMASRC3 = address;
                break;
        case DMA_CHANNEL_4:
                DMASRC4 = address;
                break;
        case DMA_CHANNEL_5:
                DMASRC5 = address;
                break;
        default: break;
    }    
}

void DMA_DestinationAddressSet(DMA_CHANNEL  channel, uint16_t address) {
    switch(channel) {
        case DMA_CHANNEL_0:
                DMADST0 = address;
                break;
        case DMA_CHANNEL_1:
                DMADST1 = address;
                break;
        case DMA_CHANNEL_2:
                DMADST2 = address;
                break;
        case DMA_CHANNEL_3:
                DMADST3 = address;
                break;
        case DMA_CHANNEL_4:
                DMADST4 = address;
                break;
        case DMA_CHANNEL_5:
                DMADST5 = address;
                break;
        default: break;
    }    
}

bool DMA_IsSoftwareRequestPending(DMA_CHANNEL  channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMACH0bits.CHREQ);
        case DMA_CHANNEL_1:
                return(DMACH1bits.CHREQ);
        case DMA_CHANNEL_2:
                return(DMACH2bits.CHREQ);
        case DMA_CHANNEL_3:
                return(DMACH3bits.CHREQ);
        case DMA_CHANNEL_4:
                return(DMACH4bits.CHREQ);
        case DMA_CHANNEL_5:
                return(DMACH5bits.CHREQ);
        default: return 0;
    }
}

bool DMA_IsBufferedWriteComplete(DMA_CHANNEL channel )
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.DBUFWF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.DBUFWF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.DBUFWF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.DBUFWF);
        case DMA_CHANNEL_4:
                return(DMAINT4bits.DBUFWF);
        case DMA_CHANNEL_5:
                return(DMAINT5bits.DBUFWF);
        default: return 0;
    }
}

bool DMA_IsHighAddressLimitFlagSet(DMA_CHANNEL channel )
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.HIGHIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.HIGHIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.HIGHIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.HIGHIF);
        case DMA_CHANNEL_4:
                return(DMAINT4bits.HIGHIF);
        case DMA_CHANNEL_5:
                return(DMAINT5bits.HIGHIF);
        default: return 0;
    }
}

bool DMA_IsLowAddressLimitFlagSet(DMA_CHANNEL channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.LOWIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.LOWIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.LOWIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.LOWIF);
        case DMA_CHANNEL_4:
                return(DMAINT4bits.LOWIF);
        case DMA_CHANNEL_5:
                return(DMAINT5bits.LOWIF);
        default: return 0;
    }
}

bool DMA_IsOperationDone(DMA_CHANNEL channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.DONEIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.DONEIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.DONEIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.DONEIF);
        case DMA_CHANNEL_4:
                return(DMAINT4bits.DONEIF);
        case DMA_CHANNEL_5:
                return(DMAINT5bits.DONEIF);
        default: return 0;
    }
}

bool DMA_IsOverrunFlagSet(DMA_CHANNEL channel )
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.OVRUNIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.OVRUNIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.OVRUNIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.OVRUNIF);
        case DMA_CHANNEL_4:
                return(DMAINT4bits.OVRUNIF);
        case DMA_CHANNEL_5:
                return(DMAINT5bits.OVRUNIF);
        default: return 0;
    }
}

bool DMA_IsOperationHalfComplete(DMA_CHANNEL channel)
{
    switch(channel) {
        case DMA_CHANNEL_0:
                return(DMAINT0bits.HALFIF);
        case DMA_CHANNEL_1:
                return(DMAINT1bits.HALFIF);
        case DMA_CHANNEL_2:
                return(DMAINT2bits.HALFIF);
        case DMA_CHANNEL_3:
                return(DMAINT3bits.HALFIF);
        case DMA_CHANNEL_4:
                return(DMAINT4bits.HALFIF);
        case DMA_CHANNEL_5:
                return(DMAINT5bits.HALFIF);
        default: return 0;
    }
}
