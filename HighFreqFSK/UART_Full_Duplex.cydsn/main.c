/*****************************************************************************
* File Name: main.c
*
* Created: 5/16/18
* Revised: 5/17/18
* Revised by: Stephanie Salazar
*
* Description: 
*  This project communicates via UART in Full duplex mode. The UART has
* receiver(RX) and transmitter(TX)]. The data received by RX is used for
* FSK transmission. 
*
* Related Document: 
* CE210741_UART_Full_Duplex_and_printf_Support_with_PSoC_3_4_5LP.pdf
*
* Hardware Dependency: See 
* CE210741_UART_Full_Duplex_and_printf_Support_with_PSoC_3_4_5LP.pdf
*
*******************************************************************************
*/

#include <project.h>
#include <stdio.h>
#include "common.h"
#include "stdlib.h"

/* Character LCD String Length */
#define LINE_STR_LENGTH     (20u)

/* Global Variables */
uint8 errorStatus = 0u;
char8 data[LINE_STR_LENGTH];
uint8 rxData = 0;

/* The buffer size is equal to the maximum packet size of the IN and OUT bulk
* endpoints.
*/
#define USBUART_BUFFER_SIZE (64u)
#define LINE_STR_LENGTH     (20u)
/* Change data size for sending longer data (n-1) */
#define DATA_SIZE           (7u)
/* Change max crabs to correlate with data size 2^(n) - 1 */
#define MAX_CRABS           (15)
/* Error used for user error */
#define ERROR               (333u)


/*Definitions*/
#define CLOCK_FREQ 1000000
#define FREQ(x) (CLOCK_FREQ/x)-1

/*PWM Frequencies*/
#define ONE_FREQ 42000
#define ZERO_FREQ 37000
#define AUDIBLE_FREQ 12000

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
#define TRUE 0x1
#define FALSE 0x0
#define DATA_LENGTH 4
#define DECODE_VALUE 0x01
//
#define PREFIX_BIT_LENGTH 6
#define PREFIX_MESSAGE 0xFF


/*Function Prototypes*/
int Data(unsigned int hex_value, int bT);
int Decode(unsigned int hex_value, int bT);
int PreFix(unsigned int hex_value, int prefixCount);
CY_ISR_PROTO(isr_sec); // High F Interrupt

/*Global Variables*/
int prompt = 1;
int endFlag = 0; // flag for end of user input
int oneDigit = 0; // flag for end of input with one character
int twoDigit = 0; // flag for end of input with two characters
int error = 0; // flag for input error
int i = 2; // to iterate through data array
uint16 count;
char8 lineStr[LINE_STR_LENGTH];
uint8 buffer[USBUART_BUFFER_SIZE];
uint8 newDataflag = 0;

/*Global Variables*/
static int bitTime = 0;
static int prefixTime = 0;



/*******************************************************************************
* Function Name: RxIsr
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the UART
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/

// Interrupt triggered on a 0.1s timer timeout
// Will increment prefixTime counter for the 1st 8 bits
// Then move on to incrementing the message bit counter
CY_ISR(isr_sec)
{
    if((bitTime == 0) && (prefixTime <= PREFIX_BIT_LENGTH)){
        prefixTime++;
    }
    else if(prefixTime > PREFIX_BIT_LENGTH){
        bitTime++;
    }
}//end CY_ISR(isr_sec)

CY_ISR(RxIsr)
{
    uint8 rxStatus;         
    newDataflag = 1;
    HighVoltage_Write(1);
    do
    {
        /* Read receiver status register */
        rxStatus = UART_RXSTATUS_REG;

        if((rxStatus & (UART_RX_STS_BREAK      | UART_RX_STS_PAR_ERROR |
                        UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            errorStatus |= rxStatus & ( UART_RX_STS_BREAK      | UART_RX_STS_PAR_ERROR | 
                                        UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN);
        }
        
        if((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read data from the RX data register */
            rxData = UART_RXDATA_REG;
            if(errorStatus == 0u)
            {
                /* Send data backward */
                UART_TXDATA_REG = rxData;
                /* Clear LCD line. */
                LCD_Position(0u, 0u);
                sprintf(data,"Crabs: %d", rxData);
                LCD_PrintString("             ");

                /* Output string on LCD. */
                LCD_Position(0u, 0u);
                LCD_PrintString(data);
            }
        }
    }while((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u);

}
    

/*******************************************************************************
* Function Name: main()
*******************************************************************************/
int main()
{
    /*Variable initializations*/
    int bitCase = 0;
    int data_turn = 0;
    unsigned int data_to_be_sent = ONE;
    
    UART_Start();           /* Start communication component */
    UART_PutString("UART Full Duplex and printf() support Code Example Project \r\n");

#if(INTERRUPT_CODE_ENABLED == ENABLED)
    isr_rx_StartEx(RxIsr);
#endif /* INTERRUPT_CODE_ENABLED == ENABLED */
    
    CyGlobalIntEnable;      /* Enable global interrupts. */
    /*Block initializations*/
    LCD_Start();
    
    /*Block initializations*/
    PWM_Modulator_Start();
    PWM_1_Start();
    PWM_2_Start();
    PWM_3_Start();
    PWM_Switch_Timer_Start();
    isr_sec_StartEx(isr_sec);
    
    // Set PWM to AUDIBLE_FREQ
    PWM_1_WritePeriod(FREQ(AUDIBLE_FREQ));
    PWM_1_WriteCompare((FREQ(AUDIBLE_FREQ))/2); // Sets pulse width to half
    
    // Set PWM to ONE_FREQ
    PWM_2_WritePeriod(FREQ(ONE_FREQ));
    PWM_2_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width to half
    
    // Set PWM to ZERO_FREQ
    PWM_3_WritePeriod(FREQ(ZERO_FREQ));
    PWM_3_WriteCompare((FREQ(ZERO_FREQ))/2); // Sets pulse width to half
    
    /* Clear LCD line. */
    LCD_Position(0u, 0u);
    LCD_PrintString("                    ");

    /* Output string on LCD. */
    LCD_Position(0u, 0u);
    LCD_PrintString("Hello");

    for(;;)
    {
        if(errorStatus != 0u)
        {
            /* Clear error status */
            errorStatus = 0u;
        }
        switch(bitTime){
            // ENCODE
            case 0:
                bitCase = PreFix(PREFIX_MESSAGE , prefixTime);
                break; 
            // DATA
            case 1:
            case 2:
            case 3:
            case 4:
                bitCase = Data(rxData, bitTime); 
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
                // Turn sending off until new data
                newDataflag = 0;
                //encode used to transmit 7 1's for the prefix 
                //reset here to be ready for case 0 
                prefixTime = 0;
                data_turn++;
                if (data_turn == DATA_LENGTH) {
                    data_turn = 0;
                }
                PWM_Modulator_Stop();
                // Turn High Voltage off while delaying
                PWM_Switch_Timer_Stop();
                // Turn High Voltage Back On

                HighVoltage_Write(0);
                CyDelay(20);
                SignalBase_Write(0);

                /* Wait for new data before sending out data */
                while(newDataflag == 0){
                }
                
                /* New data: Turn on circuitry and begin transmission */
                HighVoltage_Write(1);
                CyDelay(20); // Give voltage booster time to charge up
                SignalBase_Write(1);
                /* Reset PWM blocks and bitTime for new transmission */
                bitTime = 0; 
                PWM_Modulator_Start();
                PWM_Switch_Timer_Start();
                break;
            default:
                break; 
         } //end switch(bitTime) 
        
        /* Send out frequency depending on bit is 1 or 0 */
        if(bitCase == ONE){
            PWM_Modulator_WritePeriod(FREQ(ONE_FREQ));
            PWM_Modulator_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width
        }else if(bitCase == ZERO){
            PWM_Modulator_WritePeriod(FREQ(ZERO_FREQ));
            PWM_Modulator_WriteCompare((FREQ(ZERO_FREQ))/2); // Sets pulse width
        }
        
       
       
    }
}

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
 * parameters: hex_value - an 8 bit (1 byte) value specifying what data you want to send
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


/*
 * function: int PreFix(unsigned int hex_value, int bT)
 * parameters: hex_value - an 8 bit (1 byte) value specifying what data you want to send
 *             bT - the current bit time
 * returns: bitCase - a high or low signal to be sent to an output pin
 * description: This function takes in a hex value and sends it out a bit at a time as a high or
 *  low signal depending on the bit time. Used only to set desired decode encryption.
 */
int PreFix(unsigned int hex_value, int prefixCount)
{   
    int prefixBit;
    
    switch(prefixCount){
        case 0:
           prefixBit = (hex_value & BIT_7_MASK) >> 7;
            break;
        case 1:
            prefixBit = (hex_value & BIT_6_MASK) >> 6;
            break; 
        case 2:
            prefixBit = (hex_value & BIT_5_MASK) >> 5;
            break; 
        case 3:
            prefixBit = (hex_value & BIT_4_MASK) >> 4;
            break;
        case 4:
            prefixBit = (hex_value & BIT_3_MASK) >> 3;
            break; 
        case 5:
            prefixBit = (hex_value & BIT_2_MASK) >> 2;
            break; 
        case 6:
            prefixBit = (hex_value & BIT_1_MASK) >> 1;
            break; 
        case 7:
            prefixBit = (hex_value & BIT_0_MASK);
            break;
        default:
            break;
 
    }
    
    return prefixBit; 

}

/* [] END OF FILE */
