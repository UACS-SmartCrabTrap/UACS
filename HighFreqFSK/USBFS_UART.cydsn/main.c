/*******************************************************************************
* File Name: main.c
* Editer: Stephanie Salazar
* Revision: 5/14/18
*
* Description:
*   The component is enumerated as a Virtual Com port. Receives data from the 
*   hyper terminal, then sends back the received data.
*   The LCD Display shows the number of crabs sent
*/


#include <project.h>
#include "stdio.h"
#include "stdlib.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow usage of the floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

#define USBFS_DEVICE    (0u)

/* The buffer size is equal to the maximum packet size of the IN and OUT bulk
* endpoints.
*/
#define USBUART_BUFFER_SIZE (64u)
#define LINE_STR_LENGTH     (20u)
#define DATA_SIZE           (7u)
#define ERROR               (333u)
#define MAX_CRABS           (15)

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
#define DATA_LENGTH 4
#define DECODE_VALUE 0x01
//
#define PREFIX_BIT_LENGTH 6
#define PREFIX_MESSAGE 0xFF

/*Function Prototypes*/
int GetCrabs(void);
int CalculateCrabs(void);
void DisplayCrabs(int);

/*Function Prototypes*/
int Data(unsigned int hex_value, int bT);
int Decode(unsigned int hex_value, int bT);
int PreFix(unsigned int hex_value, int prefixCount);
CY_ISR_PROTO(isr_halfsec); // High F Interrupt

/*Global Variables*/
int prompt = 1;
int endFlag = 0;
int oneDigit = 0;
int twoDigit = 0;
int error = 0;
int i = 2; // to iterate through data array
uint16 count;
char8 lineStr[LINE_STR_LENGTH];
uint8 buffer[USBUART_BUFFER_SIZE];
uint8 data[3] = {0};

/*Global Variables*/
static int bitTime = 0;
static int prefixTime = 0;
static int alternating = 0;



/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  The main function performs the following actions:
*   1. Waits until VBUS becomes valid and starts the USBFS component which is
*      enumerated as virtual Com port.
*   2. Waits until the device is enumerated by the host.
*   3. Waits for data coming from the hyper terminal and sends it back.
*   4. the LCD shows the amount of crabs
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
  
    int crabs = 0;
    int gettingData = 1;
    /* Initialize LCD Screen */
    LCD_Start();

    CyGlobalIntEnable; /* Enable global interrupts. */
    /*Block initializations*/
    PWM_Modulator_Start();
    
    isr_halfsec_StartEx(isr_halfsec);
    
    /*Variable initializations*/
    int bitCase = 0;
    int data_turn = 0;
    unsigned int data_to_be_sent = ONE;

    /* Start USBFS operation with 5-V operation. */
    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);

    /* Clear LCD line. */
    LCD_Position(0u, 0u);
    LCD_PrintString("                    ");

    /* Output string on LCD. */
    LCD_Position(0u, 0u);
    LCD_PrintString("Hello");
    
    /* Start UART interface and fill array with 3 parameters until valid */
    while(gettingData){
        while(0u == GetCrabs()){
        };
        crabs = CalculateCrabs();
        if(crabs != ERROR){
            DisplayCrabs(crabs);
            gettingData = 0;
        }
    }
    /* Start Timer after interface to start at case 0 */
    PWM_Switch_Timer_Start();
   
    for(;;)
    {
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
                bitCase = Data(crabs, bitTime); 
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
                //encode used to transmit 7 1's for the prefix 
                //reset here to be ready for case 0 
                prefixTime = 0;
                data_turn++;
                if (data_turn == DATA_LENGTH) {
                    data_turn = 0;
                }
                PWM_Modulator_Stop();
                PWM_Switch_Timer_Stop();
                
                gettingData = 1;
                /* Start UART interface and fill array with 3 parameters until valid */
                while(gettingData){
                    while(0u == GetCrabs()){
                    };
                    crabs = CalculateCrabs();
                    if(crabs != ERROR){
                        DisplayCrabs(crabs);
                        gettingData = 0;
                    }
                }
                bitTime = 0;
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
        
       
    } // end for(;;)
} // end main


/*
 * function: int GetCrabs()
 * parameters: hex_value - an 8 bit (1 byte) value specifying what data you want to send
 *             bT - the current bit time
 * returns: bitCase - a high or low signal to be sent to an output pin
 * description: This function starts UART interface and waits for a valid amount of crabs
 * entered by user
 */
int GetCrabs()
{
    uint16 crabs = 0;
    /* Host can send double SET_INTERFACE request. */
    if (0u != USBUART_IsConfigurationChanged())
    {
        /* Initialize IN endpoints when device is configured. */
        if (0u != USBUART_GetConfiguration())
        {
            /* Enumeration is done, enable OUT endpoint to receive data 
            * from host. */
            USBUART_CDC_Init();
            }
        }
        
        /* Service USB CDC when device is configured. */
        if (0u != USBUART_GetConfiguration())
        {
            /* Wait until component is ready to send data to host. */
            while (0u == USBUART_CDCIsReady())
                {
                }
                if(prompt == 1){
                    USBUART_PutString("Hello. Please enter amount of crabs (up to 127). Terminates with carriage return or third character. Any non-integer will be interpreted as a 0.");
                }
            /* Wait until component is ready to send data to host. */
            while (0u == USBUART_CDCIsReady())
                {
                }
                if(prompt == 1){
                    USBUART_PutCRLF();
                    prompt = 0;
                }
                
            /* Check for input data from host. */
            if (0u != USBUART_DataIsReady())
            {
                /* Read received data and re-enable OUT endpoint. */
                count = USBUART_GetAll(buffer);
    
                if (strncmp (buffer,"0",1) == 0){
                    //USBUART_PutString("True Zero");
                }
                if (strncmp (buffer,"\r",1) == 0){
                    //USBUART_PutString("Carriage Return");

                    if(i == 1){
                        oneDigit = 1;
                    }else if(i == 0){
                        twoDigit = 1;
                    }
                    endFlag = 1; // set flag to add numbers
                }else{
                    // Convert string to int
                    data[i] = (uint8)atoi(buffer);
                }
                
                /* Make sure data array stays in bounds (size = 3) */
                if(i == 0){
                    i = 2;
                    endFlag = 1; // 3 characters have been entered
                }else{
                    i--;
                }
                
                 if (0u != count)
                {
                    /* Wait until component is ready to send data to host. */
                    while (0u == USBUART_CDCIsReady())
                    {
                    }

                    /* Send data back to host. */
                    USBUART_PutData(buffer, count);


                    /* If the last sent packet is exactly the maximum packet 
                    *  size, it is followed by a zero-length packet to assure
                    *  that the end of the segment is properly identified by 
                    *  the terminal.
                    */
                    if (USBUART_BUFFER_SIZE == count)
                    {
                        /* Wait until component is ready to send data to PC. */
                        while (0u == USBUART_CDCIsReady())
                        {
                        }

                        /* Send zero-length packet to PC. */
                        USBUART_PutData(NULL, 0u);
                    }
                }
            } // end (0u != USBUART_DataIsReady())
        } // end (0u != USBUART_GetConfiguration())
        if(endFlag == 1){
            return 1;
        }else{
            return 0;
        }
}//end Decode()

/*
 * function: int CalculateCrabs()
 * parameters: none
 * returns: int crabs - amount of crabs from user input 
 * description: This function takes an array of size three and converts
 * to a single number
 */
int CalculateCrabs()
{
    int crabs;
    /* Wait until component is ready to send data to host. */
    while (0u == USBUART_CDCIsReady())
    {
    }
    USBUART_PutCRLF();
    /* Shift data if carriage return was pressed */
    if(oneDigit == 1){
        //USBUART_PutString("one digit");
        data[0] = data[2];
        data[2] = 0;
        oneDigit = 0;
    }else if(twoDigit == 1){
        //USBUART_PutString("two digits");
        data[0] = data[1];
        data[1] = data[2];
        data[2] = 0;
        twoDigit = 0;
    }
    /* Apply digit place to integer */
    data[0] = data[0] * 1;
    data[1] = data[1] * 10;
    data[2] = data[2] * 100;
    crabs = data[0] + data[1] + data[2];
    if(crabs > MAX_CRABS){
        crabs = 0;
        error = 1;
        /* Wait until component is ready to send data to host. */
        while (0u == USBUART_CDCIsReady())
        {
        }
        USBUART_PutString("Error. Please enter a number UP TO 127");
        /* Wait until component is ready to send data to host. */
        while (0u == USBUART_CDCIsReady())
        {
        }
        USBUART_PutCRLF();
    }
    /* reset array */
    data[0] = 0; 
    data[1] = 0;
    data[2] = 0;
    i = 2; // reset indexing for array
    endFlag = 0; // reset endFlag for gathering new data
                    
    if(error == 1){
        error = 0; // reset error checking
        return ERROR;

    }else{
        prompt = 1;
        return crabs;
    }
} /* END OF CalculateCrabs() */

/*
 * function: void DisplayCrabs()
 * parameters: int crabs
 * returns: void
 * description: Displays the number of crabs on LCD Display
 */
void DisplayCrabs(int crabs){
    /* Clear LCD line. */
    LCD_Position(0u, 0u);
    LCD_PrintString("           ");
    /* Reset LCD line position. */
    LCD_Position(0u, 0u);
    /* Store int crabs into a string to print to LCD */
    sprintf(lineStr,"Crabs: %d", crabs);
    LCD_PrintString(lineStr);
}

// Interrupt triggered on a 0.1s timer timeout
// Will increment prefixTime counter for the 1st 8 bits
// Then move on to incrementing the message bit counter
CY_ISR(isr_halfsec)
{
    if((bitTime == 0) && (prefixTime <= PREFIX_BIT_LENGTH)){
        prefixTime++;
    }
    else if(prefixTime > PREFIX_BIT_LENGTH){
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
