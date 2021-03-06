/*Included header files*/
#include "project.h"

/*Definitions*/
#define CLOCK_FREQ 5000
#define FREQ(x) (CLOCK_FREQ/x)-1
#define ONE_FREQ 100
#define ZERO_FREQ 85
#define DEFAULT_FREQ MIN_FREQ

#define BIT_0_MASK 0x01
#define BIT_1_MASK 0x02
#define BIT_2_MASK 0x04
#define BIT_3_MASK 0x08
#define BIT_4_MASK 0x10
#define BIT_5_MASK 0x20
#define BIT_6_MASK 0x40
#define BIT_7_MASK 0x80

#define ZERO 0x0
#define ONE 0x1
#define DATA_LENGTH 4
#define DECODE_VALUE 0x01

/*Function Prototypes*/
int Data(unsigned int hex_value, int bT);
int Decode(unsigned int hex_value, int bT);
CY_ISR_PROTO(isr_halfsec); // Low F Interrupts

/*Global Variables*/
static int bitTime = 0;
static int encode = 0;

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
        switch(bitTime){
            // ENCODE
            case 0:
                bitCase = ONE;
                break; 
            // DATA
            case 1:
            case 2:
            case 3:
            case 4:
                bitCase = Data(data_to_be_sent, bitTime); 
                break; 
            // DECODE
            case 5:    
            case 6:
            case 7:    
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
                bitCase = Decode(DECODE_VALUE, bitTime);
                break;
            case 13:
                bitTime = 0;
                encode = 0;
                data_turn++;
                data_to_be_sent <<= 1;
                //Once data to be sent can't be contained in a nibble, reset to 0x1
                if (data_turn == DATA_LENGTH) {
                    data_turn = 0;
                    data_to_be_sent = ONE;
                }
                PWM_Modulator_Stop();
                PWM_Switch_Timer_Stop();
                CyDelay(3000);
                PWM_Modulator_Start();
                PWM_Switch_Timer_Start();
                break;
            default:
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

CY_ISR(isr_halfsec)
{
    if((bitTime == 0) && (encode < 7)){
        encode++;
    }
    else if(encode > 6){
        bitTime++;
    }
}//end CY_ISR(isr_halfsec)

/*
 * function: int Data(unsigned int hex_value, int bT)
 * parameters: hex_value - a four bit value specifying what data you want to send
 *             bT - the current bit time
 * returns: bitCase - a high or low signal to be sent to an output pin
 * description: This function takes in a hex value and sends it out a bit at a time as a high or
 *  low signal depending on the bit time. Used only to set desired data nibble.
 */
int Data(unsigned int hex_value, int bT)
{
    int bitCase;
    switch(bT){
        case 1:
            bitCase = (hex_value & BIT_3_MASK) >> 3;
            break; 
        case 2:
            bitCase = (hex_value & BIT_2_MASK) >> 2;
            break; 
        case 3:
            bitCase = (hex_value & BIT_1_MASK) >> 1;
            break; 
        case 4:
            bitCase = (hex_value & BIT_0_MASK);
            break;
        default:
            break;
    } //end switch(bT)
    return bitCase;
}//end Data()


/*
 * function: int Decode(unsigned int hex_value, int bT)
 * parameters: hex_value - a five bit value specifying what data you want to send
 *             bT - the current bit time
 * returns: bitCase - a high or low signal to be sent to an output pin
 * description: This function takes in a hex value and sends it out a bit at a time as a high or
 *  low signal depending on the bit time. Used only to set desired decode encryption.
 */
int Decode(unsigned int hex_value, int bT)
{
    int bitCase;
    switch(bT){
        case 5:
            bitCase = (hex_value & BIT_7_MASK) >> 7;
            break;
        case 6:
            bitCase = (hex_value & BIT_6_MASK) >> 6;
            break; 
        case 7:
            bitCase = (hex_value & BIT_5_MASK) >> 5;
            break; 
        case 8:
            bitCase = (hex_value & BIT_4_MASK) >> 4;
            break;
        case 9:
            bitCase = (hex_value & BIT_3_MASK) >> 3;
            break; 
        case 10:
            bitCase = (hex_value & BIT_2_MASK) >> 2;
            break; 
        case 11:
            bitCase = (hex_value & BIT_1_MASK) >> 1;
            break; 
        case 12:
            bitCase = (hex_value & BIT_0_MASK);
            break;
        default:
            break;
    } //end switch(bT)
    return bitCase;
}//end Decode()