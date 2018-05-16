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

/*Function Prototypes*/
int GetCrabs(void);
int CalculateCrabs(void);
void DisplayCrabs(int);

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

    
    CyGlobalIntEnable;

    /* Start USBFS operation with 5-V operation. */
    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);

    /* Clear LCD line. */
    LCD_Position(0u, 0u);
    LCD_PrintString("                    ");

    /* Output string on LCD. */
    LCD_Position(0u, 0u);
    LCD_PrintString("Hello");
    
   
    for(;;)
    {
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
    if(crabs > 127){
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


/* [] END OF FILE */
