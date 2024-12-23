/**
  * TCB0 Generated Driver File
  *
  * @file tcb0.c
  *
  * @ingroup tcb0
  *
  * @brief This file contains the API implementation for the TCB0 module driver.
  *
  * @version TCB0 Driver Version 1.1.5
*/
/*
� [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../tcb0.h"

const struct TMR_INTERFACE TCB0_Interface = {
    .Initialize = TCB0_Initialize,
    .Start = TCB0_Start,
    .Stop = TCB0_Stop,
    .PeriodCountSet = TCB0_Write,
    .TimeoutCallbackRegister = NULL,
    .Tasks = TCB0_Tasks
};

void (*TCB0_OVF_isr_cb)(void) = NULL;
void (*TCB0_CAPT_isr_cb)(void) = NULL;


void TCB0_Initialize(void)
{
    // CCMP 1000; 
    TCB0.CCMP = 0x3E8;

    // CNT undefined; 
    TCB0.CNT = 0x0;

    //ASYNC disabled; CCMPEN disabled; CCMPINIT disabled; CNTMODE SINGLE; 
    TCB0.CTRLB = 0x6;
    
    //DBGRUN disabled; 
    TCB0.DBGCTRL = 0x0;

    //CAPTEI disabled; EDGE disabled; FILTER disabled; 
    TCB0.EVCTRL = 0x0;

    //CAPT disabled; 
    TCB0.INTCTRL = 0x0;

    //CAPT disabled; 
    TCB0.INTFLAGS = 0x0;

    //Temporary Value
    TCB0.TEMP = 0x0;

    //CLKSEL CLKDIV2; ENABLE enabled; RUNSTDBY disabled; SYNCUPD disabled; 
    TCB0.CTRLA = 0x3;

}

void TCB0_Start(void)
{
    TCB0.CTRLA |= TCB_ENABLE_bm; /* Start Timer */
}

void TCB0_Stop(void)
{
    TCB0.CTRLA &= ~TCB_ENABLE_bm; /* Stop Timer */
}

void TCB0_Write(uint16_t timerVal)
{
    TCB0.CNT = timerVal;
}

uint16_t TCB0_Read(void)
{
    uint16_t readVal;

    readVal = TCB0.CNT;

    return readVal;
}

void TCB0_EnableCaptInterrupt(void)
{
    TCB0.INTCTRL |= TCB_CAPT_bm; /* Capture or Timeout: enabled */
}


void TCB0_DisableCaptInterrupt(void)
{
    TCB0.INTCTRL &= ~TCB_CAPT_bm; /* Capture or Timeout: disabled */
}

inline void TCB0_ClearCaptInterruptFlag(void)
{
    TCB0.INTFLAGS |= TCB_CAPT_bm;
}

inline bool TCB0_IsCaptInterruptFlag(void)
{
	return TCB0.INTFLAGS & TCB_CAPT_bm;

}

inline bool TCB0_IsCaptInterruptEnabled(void)
{
    return ((TCB0.INTCTRL & TCB_CAPT_bm) > 0);
}


void TCB0_Tasks(void)
{
	/**
	 * The interrupt flag is cleared by writing 1 to it, or when the Capture register
	 * is read in Capture mode
	 */
	if(TCB0.INTFLAGS & TCB_CAPT_bm)
    {
        if (TCB0_CAPT_isr_cb != NULL)
        {
            (*TCB0_CAPT_isr_cb)();
        }

        TCB0.INTFLAGS = TCB_CAPT_bm;
    }
}
