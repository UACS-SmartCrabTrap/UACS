/*Included header files*/
#include "project.h"

/*Definitions*/
#define CLOCK_FREQ 1000000 //Adjust this to match PWM_Clock in top design
#define ONE_FREQ 45000 //Frequency sent to give logic 1 (in Hz)
#define ZERO_FREQ 30000 //Frequency sent to give logic 0 (in Hz)
#define FREQ(x) (CLOCK_FREQ/x)-1 //Converts frequency x to value needed by pwm
                                 //block to output at frequency x

#define ENCODING_BYTE1 0xFF //Change these values if you want to specify a
#define ENCODING_BYTE2 0xFF //different encoding or decoding. Currently set to
#define DECODING_BYTE1 0x00 //0b1111111111111111 for the encoding and
#define DECODING_BYTE2 0x01 //0b0000000000000001 for the decoding.

#define ZERO 0x0
#define ONE  0x1
#define DATA_LENGTH 7
#define DELAY_TIME  1000 //Change this value to adjust delay time between signal
                         //transmissions. Currently set to 5 seconds.

/*Global Variables*/
static int bitTime = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /*Block initializations*/
    PWM_Modulator_Start();
    PWM_1_Start();
    PWM_2_Start();
    PWM_Switch_Timer_Start();
    
    /*Variable initializations*/
    int bitCase = 0;
    int data_turn = 0;
    unsigned int data_to_be_sent = ONE;
    
    for(;;)
    {
        PWM_Modulator_WritePeriod(FREQ(ONE_FREQ));
        PWM_Modulator_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width
        CyDelay(1);
        PWM_Modulator_WritePeriod(FREQ(ZERO_FREQ));
        PWM_Modulator_WriteCompare((FREQ(ZERO_FREQ))/2); // Sets pulse width
        CyDelay(1);
        
        
    }//end for(;;)
    
}//end main()





/*
 * function: int Byte(unsigned int hex_value, int bT)
 * parameters: hex_value - a byte specifying what data you want to send
 *             bT - the current bit time
 * returns: bitCase - a high or low signal to be sent to an output pin
 * description: This function takes in a hex value and sends it out a bit at a
 *  time as a high or low signal depending on the bit time.
 */

