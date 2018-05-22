/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

/*Definitions*/
#define CLOCK_FREQ 1000000
#define FREQ(x) (CLOCK_FREQ/x)-1
#define CRABS 10 //How many crabs are in the trap?
#define CRAB_TIME 100 //1 crab per CRAB_TIME
#define SEND_CRABS CRABS*CRAB_TIME //Total time PWM is high

/*PWM Frequencies*/
#define ONE_FREQ 42000
#define ZERO_FREQ 37000
#define ONE 1
#define ZERO 0

CY_ISR_PROTO(isr_sec); // High F Interrupt

/*Global Variables*/
int bitCase = ZERO;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /*Block initializations*/
    PWM_Modulator_Start();
    PWM_Switch_Timer_Start();
    isr_sec_StartEx(isr_sec);
    
    PWM_Switch_Timer_WritePeriod(SEND_CRABS); 
    
    PWM_Modulator_WritePeriod(FREQ(ONE_FREQ));
    PWM_Modulator_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        if(bitCase == ONE){
            PWM_Modulator_Start();
        }else if(bitCase == ZERO){
            PWM_Modulator_Stop();
        }
    }
}

/* [] END OF FILE */


// Interrupt triggered on a 0.1s timer timeout
// Will increment prefixTime counter for the 1st 8 bits
// Then move on to incrementing the message bit counter
CY_ISR(isr_sec)
{
    bitCase = 1 ^ bitCase;
    
}//end CY_ISR(isr_sec)
