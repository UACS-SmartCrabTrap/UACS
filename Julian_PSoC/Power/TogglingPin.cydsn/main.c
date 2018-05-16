/* 
 * File: main.c
 * Project: TogglingPin
 * Workspace: Power
 * Author: Julian Salazar
 * Date: 5/10/18
 * Purpose: The purpose of this project is to simply toggle a pin on and off.
 *     The pin will connect to the base of a NPN transistor which will serve as
 *     a switch to turn the analog circuitry off and on.
 * Edits:
 *      - Sleep current too high. Adjusted to have sleep current of .24mA.(JS)
 * 
 */

/******************************************************************************
 * Included Header Files
 *****************************************************************************/
#include "project.h"

/******************************************************************************
 * Definitions
 *****************************************************************************/
#define ON  1
#define OFF 0

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/
CY_ISR_PROTO(WakeupIsr);

/*
 * function: main()
 * parameters: none
 * returns: int (Should never return)
 * description: toggles a pin off and on every four seconds and sends a 40k PWM
 *      signal 
 */
int main(void)
{
    /* Enable global interrupts */
    CyGlobalIntEnable;
    
    /* Initialize hardware blocks */
    Sleep_ISR_StartEx(WakeupIsr);
    SleepTimer_Start();
    PWM_40k_Start();
    
    while(1) {
        // After the sleep timer ISR activates and turns on a pin, it will stay
        // on for 4s before sleeping again.
        CyDelay(4000);
        
        // Prepares hardware for 
        Toggle_Pin_Write(OFF);
        PWM_40k_Stop();
        PWM_40k_Sleep();
        
        // PSoC Sleep command. To adjust sleep time, change in the hardware
        //  block. No sleep time parameters taken in PSoC5LP.
        //  PM_SLEEP_TIME_NONE is a relic of PSoC3
        CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_CTW);
        
        // Reactivatespwm hardware blocks from sleep
        PWM_40k_Wakeup();
        
        CyDelay(5); // Allow voltage booster to charge before sending signal
        PWM_40k_Start();
        
    }//end while(1)
    
} //end main

CY_ISR(WakeupIsr)
{
    SleepTimer_GetStatus(); // Clears the sleep timer interrupt
    Toggle_Pin_Write(ON); //Turns pin on upon waking up.
} // end CY_ISR(WakeupIsr)