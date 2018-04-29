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
#define ZERO_FREQ_1 30000 //Frequency sent to give logic 0 (in Hz)
#define ZERO_FREQ_2 30000 //Frequency sent to give logic 0 (in Hz)
#define ZERO_FREQ_3 38000 //Frequency sent to give logic 0 (in Hz)
#define FREQ(x) (CLOCK_FREQ/x)-1 //Converts frequency x to value needed by pwm
                                 //block to output at frequency x


#define ZERO 0x0
#define ONE  0x1
#define DELAY_TIME  10 //Change this value to adjust delay time between signal
                         //transmissions. Currently set to 10ms seconds.

CY_ISR_PROTO(isr_msec); // High F  Alternating Interrupts

// Set alternating frequency
static int alternating = 1;

int main(void)
{
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    
    /*Block initializations*/
    PWM_Alternating_1_Start();
    PWM_Alternating_2_Start();
    PWM_Alternating_3_Start();
    Audible_Frequency_Start();
    PWM_Alternating_Timer_Start();
    
    isr_msec_StartEx(isr_msec);
    
    // Pin 1.6 PWM
    PWM_Alternating_3_WritePeriod(FREQ(ONE_FREQ));
    PWM_Alternating_3_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width to half
    
    for(;;)
    {
        if(alternating == 1){
            /*Alternate between high and low frequency for 10 ms*/
            // Pin 1.2 PWM
            PWM_Alternating_1_WritePeriod(FREQ(ONE_FREQ));
            PWM_Alternating_1_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width to half
            // Pin 1.4 PWM
            PWM_Alternating_2_Start();
            PWM_Alternating_2_WritePeriod(FREQ(ONE_FREQ));
            PWM_Alternating_2_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width to half
            

        }else if(alternating == 2 || alternating == 4){
            PWM_Alternating_2_Stop();
        }else if(alternating == 3){
            // Pin 1.2 PWM
            PWM_Alternating_1_WritePeriod(FREQ(ZERO_FREQ_1));
            PWM_Alternating_1_WriteCompare((FREQ(ZERO_FREQ_1))/2); // Sets pulse width to half
            // Pin 1.4 PWM
            PWM_Alternating_2_Start();
            PWM_Alternating_2_WritePeriod(FREQ(ZERO_FREQ_2));
            PWM_Alternating_2_WriteCompare((FREQ(ZERO_FREQ_2))/2); // Sets pulse width to half
            // Pin 1.6 PWM
//            PWM_Alternating_3_WritePeriod(FREQ(ZERO_FREQ_3));
//            PWM_Alternating_3_WriteCompare((FREQ(ZERO_FREQ_3))/2); // Sets pulse width to half
        }
            
    }//end for(;;)
    
}//end main()

// Interrupt triggered on a 10 ms timer timeout
// Will change between 30k and 45k every 10 ms
CY_ISR(isr_msec)
{
    if(alternating == 1){
        alternating++;
    }else if(alternating == 2){
        alternating++;
    }else if(alternating == 3){
        alternating++;
    }else if(alternating == 4){
        alternating = 1;
    }

}//end CY_ISR(isr_msec)


