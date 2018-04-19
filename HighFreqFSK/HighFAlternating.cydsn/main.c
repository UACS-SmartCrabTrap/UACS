/*Included header files*/
#include "project.h"

/*Definitions*/
#define CLOCK_FREQ 1000000 //Adjust this to match PWM_Clock in top design
#define ONE_FREQ 45000 //Frequency sent to give logic 1 (in Hz)
#define ZERO_FREQ 30000 //Frequency sent to give logic 0 (in Hz)
#define FREQ(x) (CLOCK_FREQ/x)-1 //Converts frequency x to value needed by pwm
                                 //block to output at frequency x


#define ZERO 0x0
#define ONE  0x1
#define DELAY_TIME  1000 //Change this value to adjust delay time between signal
                         //transmissions. Currently set to 5 seconds.

/*Global Variables*/
static int bitTime = 0;

int main(void)
{
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    
    /*Block initializations*/
    PWM_Modulator_Start();
    PWM_1_Start();
    PWM_2_Start();
    PWM_Switch_Timer_Start();
   
    
    for(;;)
    {
        /*Alternate between high and low frequency for 1 ms*/
        PWM_Modulator_WritePeriod(FREQ(ONE_FREQ));
        PWM_Modulator_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width to half
        CyDelay(1);
        PWM_Modulator_WritePeriod(FREQ(ZERO_FREQ));
        PWM_Modulator_WriteCompare((FREQ(ZERO_FREQ))/2); // Sets pulse width to half
        CyDelay(1);
        
        
    }//end for(;;)
    
}//end main()


