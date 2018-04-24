/* ========================================
 * Smart Crab Trap
 * FSK RX 
 * Edited by: Stephanie Salazar
 * Revision: 4/23/18
 *
 * ========================================
*/

/*Included header files*/
#include "project.h"

/*Definitions*/
#define CLOCK_FREQ 1000000 //Adjust this to match PWM_Clock in top design
#define ONE_FREQ 45000 //Frequency sent to give logic 1 (in Hz)
#define ZERO_FREQ_1 32000 //Frequency sent to give logic 0 (in Hz)
#define ZERO_FREQ_2 35000 //Frequency sent to give logic 0 (in Hz)
#define ZERO_FREQ_3 38000 //Frequency sent to give logic 0 (in Hz)
#define FREQ(x) (CLOCK_FREQ/x)-1 //Converts frequency x to value needed by pwm
                                 //block to output at frequency x


#define ZERO 0x0
#define ONE  0x1
#define DELAY_TIME  10 //Change this value to adjust delay time between signal
                         //transmissions. Currently set to 10ms seconds.

int main(void)
{
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    
    /*Block initializations*/
    PWM_Alternating_1_Start();
    PWM_Alternating_2_Start();
    PWM_Alternating_3_Start();
    Audible_Frequency_Start();
   
    
    for(;;)
    {
        /*Alternate between high and low frequency for 1 ms*/
        // Pin 1.2 PWM
        PWM_Alternating_1_WritePeriod(FREQ(ONE_FREQ));
        PWM_Alternating_1_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width to half
        // Pin 1.4 PWM
        PWM_Alternating_2_WritePeriod(FREQ(ONE_FREQ));
        PWM_Alternating_2_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width to half
        // Pin 1.6 PWM
        PWM_Alternating_3_WritePeriod(FREQ(ONE_FREQ));
        PWM_Alternating_3_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width to half
        
        // Delay frequency 
        CyDelay(DELAY_TIME);
        
        // Pin 1.2 PWM
        PWM_Alternating_1_WritePeriod(FREQ(ZERO_FREQ_1));
        PWM_Alternating_1_WriteCompare((FREQ(ZERO_FREQ_1))/2); // Sets pulse width to half
        // Pin 1.4 PWM
        PWM_Alternating_2_WritePeriod(FREQ(ZERO_FREQ_2));
        PWM_Alternating_2_WriteCompare((FREQ(ZERO_FREQ_2))/2); // Sets pulse width to half
        // Pin 1.6 PWM
        PWM_Alternating_3_WritePeriod(FREQ(ZERO_FREQ_3));
        PWM_Alternating_3_WriteCompare((FREQ(ZERO_FREQ_3))/2); // Sets pulse width to half
        
        // Delay frequency 
        CyDelay(DELAY_TIME);
        
        
    }//end for(;;)
    
}//end main()


