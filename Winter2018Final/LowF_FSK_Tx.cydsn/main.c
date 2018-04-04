/*Included header files*/
#include "project.h"

/*Definitions*/
#define CLOCK_FREQ 5000 //Adjust this to match PWM_Clock in top design
#define ONE_FREQ 100 //Frequency sent to give logic 1 (in Hz)
#define ZERO_FREQ 85 //Frequency sent to give logic 0 (in Hz)
#define FREQ(x) (CLOCK_FREQ/x)-1 //Converts frequency x to value needed by pwm
                                 //block to output at frequency x

#define BIT_0_MASK  0x0001
#define BIT_1_MASK  0x0002
#define BIT_2_MASK  0x0004
#define BIT_3_MASK  0x0008
#define BIT_4_MASK  0x0010
#define BIT_5_MASK  0x0020
#define BIT_6_MASK  0x0040
#define BIT_7_MASK  0x0080

#define ENCODING_BYTE1 0xFF //Change these values if you want to specify a
#define ENCODING_BYTE2 0xFF //different encoding or decoding. Currently set to
#define DECODING_BYTE1 0x00 //0b1111111111111111 for the encoding and
#define DECODING_BYTE2 0x01 //0b0000000000000001 for the decoding.

#define ZERO 0x0
#define ONE  0x1
#define DATA_LENGTH 7
#define DELAY_TIME  5000 //Change this value to adjust delay time between signal
                         //transmissions. Currently set to 5 seconds.

/*Enumerations*/
enum state{
    Encoding_Byte1,
    Encoding_Byte2,
    Data,
    Decoding_Byte1,
    Decoding_Byte2
};

/*Function Prototypes*/
int Byte(unsigned int hex_value, int bT);
CY_ISR_PROTO(isr_halfsec); // Low F Interrupts

/*Global Variables*/
static int bitTime = 0;
static int currentByte = Encoding_Byte1;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /*Block initializations*/
    PWM_Modulator_Start();
    PWM_1_Start();
    PWM_2_Start();
    PWM_Switch_Timer_Start();
    isr_halfsec_StartEx(isr_halfsec);
    
    /*Variable initializations*/
    int bitCase = 0;
    int data_turn = 0;
    unsigned int data_to_be_sent = ONE;
    
    for(;;)
    {
        switch(currentByte){
            case Encoding_Byte1:
                bitCase = Byte(ENCODING_BYTE1, bitTime);
                break;
            case Encoding_Byte2:
                bitCase = Byte(ENCODING_BYTE2, bitTime);
                break;
            case Data:
                bitCase = Byte(data_to_be_sent, bitTime);
                break;
            case Decoding_Byte1:
                bitCase = Byte(DECODING_BYTE1, bitTime);
                break;
            case Decoding_Byte2:
                bitCase = Byte(DECODING_BYTE2, bitTime);
                break;
            default:
                data_turn++;
                data_to_be_sent <<= 1;
                //Once data to be sent exceeds 0x40, reset to 1
                if (data_turn == DATA_LENGTH) {
                    data_turn = 0;
                    data_to_be_sent = ONE;
                }
                PWM_Modulator_Stop();
                PWM_Switch_Timer_Stop();
                CyDelay(DELAY_TIME);
                PWM_Modulator_Start();
                PWM_Switch_Timer_Start();
                currentByte = Encoding_Byte1;
                break;
         } //end switch(bitTime) 
        
        if(bitCase == ONE){
            PWM_Modulator_WritePeriod(FREQ(ONE_FREQ));
            PWM_Modulator_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width
        }else if(bitCase == ZERO){
            PWM_Modulator_WritePeriod(FREQ(ZERO_FREQ));
            PWM_Modulator_WriteCompare((FREQ(ZERO_FREQ))/2); // Sets pulse width
        }
        
    }//end for(;;)
    
}//end main()


/* function: CY_ISR(isr_halfsec)
 * parameters: isr_halfsec - an interrupt tied to a Timer module
 * returns: none
 * description: This ISR will activate every half second and keep track of what
 *  current bit we are on within a byte. After every 8th bit, it resets and
 *  moves on to a new byte.
 */
CY_ISR(isr_halfsec)
{
    bitTime++;
    if (bitTime == 8){
        bitTime = 0;
        currentByte++;
    }
}//end CY_ISR(isr_halfsec)


/*
 * function: int Byte(unsigned int hex_value, int bT)
 * parameters: hex_value - a byte specifying what data you want to send
 *             bT - the current bit time
 * returns: bitCase - a high or low signal to be sent to an output pin
 * description: This function takes in a hex value and sends it out a bit at a
 *  time as a high or low signal depending on the bit time.
 */
int Byte(unsigned int hex_value, int bT)
{
    int bitCase;
    switch(bT){
        case 0:
            bitCase = (hex_value & BIT_7_MASK) >> 7;
            break;
        case 1:
            bitCase = (hex_value & BIT_6_MASK) >> 6;
            break; 
        case 2:
            bitCase = (hex_value & BIT_5_MASK) >> 5;
            break; 
        case 3:
            bitCase = (hex_value & BIT_4_MASK) >> 4;
            break;
        case 4:
            bitCase = (hex_value & BIT_3_MASK) >> 3;
            break; 
        case 5:
            bitCase = (hex_value & BIT_2_MASK) >> 2;
            break; 
        case 6:
            bitCase = (hex_value & BIT_1_MASK) >> 1;
            break; 
        case 7:
            bitCase = (hex_value & BIT_0_MASK);
            break;
        default:
            break;
    } //end switch(bT)
    return bitCase;
}//end Decode()