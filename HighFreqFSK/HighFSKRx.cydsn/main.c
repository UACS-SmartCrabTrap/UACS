/* =============================================================================
 * Smart Crab Trap
 * FSK RX 
 * Edited by: Stephanie Salazar
 * Revision: 5/10/18
 * Function: This project takes in a signal from an outside source
 * and reads the data within the signal. This code waits for a pre-fix
 * of 0xFF and then reads the next 4 bits as the data and confirms
 * the message with a post-fix of 0x01. The data is displayed on an LCD display.
 * =============================================================================
*/

#include "project.h"
#include <stdio.h>
#include "LCD_Char.h"

#define ARRAY_SIZE        12
#define COUNT             100
#define PREFIX_ACCURACY   70
#define DATA_ACCURACY     70
#define DATA_LENGTH       7
#define BIT_0_MASK        0x1
#define SUCCESS           0x1
#define FAILURE           0x0
#define FiveSecs          5000

/*Function Prototypes*/
void Display(void);
int CheckParity(int);
void LEDSOn(int,int);

// Interrupt for switching bits 5 ms
CY_ISR_PROTO(Bit_Timer);
CY_ISR_PROTO(watchDogCheck);

// Global Variables
static uint16 levelCounter = 0; // Timer counter to debounce bit
static uint16 zeroCount = 0; // 0 count used in timer counter debounce
static uint16 oneCount = 0; // 1 count used in timer counter debounce
static uint16 currentBit = 0; // x/10 bit decision for 500 ms bit
static uint16 dataCount = 0; // which bit of data we are looking at
static uint16 data = 0; // byte bits of data
static uint16 crabs = 0; // byte of data transferred from data variable
static uint8 dataFlag = 0; // Flag to start looking for data
static uint8 decodeFlag = 0; // Flag to start looking for post-fix
static int paritySuccess = 0;

// LCD String Variables
char OutputString[ARRAY_SIZE];
char display[ARRAY_SIZE];

// FLAGS for turning on messages on LCD screen
static uint8 lcdFlagEncode = 0; // Turns on pre-fix message
static uint8 lcdFlagData = 0; // Displays data 
static uint8 lcdFlagDecode = 0; // good or bad postfix
static uint8 decodeWrong = 0;


int main(void)
{
    /* Enable global interrupts. */
    LCD_Char_Start();
    sprintf(display, "Starting Module!");
    LCD_Char_Position(0u,0u); // Resets cursor to top of LCD Screen
    LCD_Char_PrintString(display);
    CyDelay(FiveSecs);
    
    LCD_Char_ClearDisplay();
    
    CyGlobalIntEnable; 
    
//    // Start timer to clear watch dog
//    checkWatchDogTimer_Start();
//    watchDogCheck_StartEx(watchDogCheck);
    
//    // Start watch dog timer to check for blocks in code
//    CyWdtStart(CYWDT_2_TICKS, CYWDT_LPMODE_NOCHANGE);

    /* initialization/startup code here */
    PWM_Recon_Start();
    Shift_Reg_Start();
    Out_Comp_Start();
    Bit_Timer_Start();
    Timer_ISR_StartEx(Bit_Timer);

    // Displays Loading Message before receiving pre-fix=
    sprintf(display, "counting crabs...");
    LCD_Char_Position(0u,0u); // Resets cursor to top of LCD Screen
    LCD_Char_PrintString(display);

    for(;;)
    {
        //Display();
        LEDSOn(crabs,paritySuccess);
    } // end of for(;;)
} // end of main()


//Bit length = 500 ms
//timer period = 5 ms
//will check bit COUNT times, to debounce
CY_ISR(Bit_Timer){
    levelCounter++;
    
    // Count whether bit is currently 1 or 0
    if(Out_Comp_GetCompare() != 0){
        oneCount++;
    }else{
        zeroCount++;
    }
    
    // Debouncing
    if(levelCounter == COUNT){
        if(dataFlag == 0){ //looking for prefix
            if(oneCount >= PREFIX_ACCURACY){ // 1 bit must be Accuracy/100 = 1 
                currentBit = 0x01;
                oneCount = 0;
                Count_Out_Write(1);
        
            }else{ // if oneCount <= 7, bit is 0
                currentBit = 0x00; 
                zeroCount = 0; 
                Count_Out_Write(0);
            
            }
        }else{ // looking for data bits, can have less accuracy
            if(oneCount >= DATA_ACCURACY){ // 1 bit must be Accuracy/100 = 1 
                currentBit = 0x01;
                oneCount = 0;
                Count_Out_Write(1);
        
            }else{ // if oneCount <= 7, bit is 0
                currentBit = 0x00; 
                zeroCount = 0; 
                Count_Out_Write(0);
            
            }
        }
        dataCount++; // Keep track of what bit we are on
        levelCounter = 0; // Reset timer bit debouncer  
        
        //Look for pre-fix
        data = data << 1; // Shift data over to store next bit
        data = data | currentBit;
        // Check if data is prefix(oxFF) but we are not looking for data or decode
        if((data == 0xff) && (dataFlag == 0) && (decodeFlag == 0)){ 
            
            dataCount = 0;
            data = 0x00;
            dataFlag = 1; //Start looking for data
            lcdFlagEncode = 1; //Display pre-fix on lcd
        
        //Check data by checking next 8 bits and parity (9 bits) after the encoding
        }else if((dataFlag == 1) && (dataCount > 8)){
            crabs = data;
            data = 0; //Restart data for decode
            dataCount = 0; 
            lcdFlagEncode = 0; //Turn off encode message
            lcdFlagData = 1; //Display data
            decodeFlag = 1;
        }
        
        // Check for 8 bits of post-fix
        if(decodeFlag == 1 && (dataCount > 7)){
            // Correct postfix is 0x01
            if(data == 0x01){
             lcdFlagDecode = 1; // lcd flag for "good" post-fix
            }else{
                decodeWrong = 1; // lcd flag for "bad" post-fix
            }
            decodeFlag = 0;
            dataFlag = 0; //Don't want to check for data anymore
        }
    } // end of if(levelCounter == COUNT)
} // end of CY_ISR(HighF_LevelCount)


/*
 * function: void Display(void)
 * parameters: void
 * returns: void
 * description: Displays current data on LCD display depending
 * on what flags are set
 */
void Display()
{
    // LCD Screen Messages
    // If encode is received, display message
    if(lcdFlagEncode == 1){
        LCD_Char_ClearDisplay();
        LCD_Char_PrintString("0xFF pre-fix");
        lcdFlagEncode = 0; 
    // When 9 bits are received, data will display at top of screen
    }else if(lcdFlagData == 1){
        paritySuccess = CheckParity(crabs);
        crabs = crabs >> 1;
        sprintf(OutputString, "Crabs:%i Err:%i",crabs, !paritySuccess);
        LCD_Char_ClearDisplay();
        LCD_Char_Position(0u,0u);
        LCD_Char_PrintString(OutputString);
        dataFlag = 0;
        lcdFlagData = 0;
    // Postfix will display good or bad below data on screen
    }else if(lcdFlagDecode == 1){
        LCD_Char_Position(1u,0u);
        char8 displayG[] = "good";
        LCD_Char_PrintString(displayG);
        dataFlag = 0;
        lcdFlagDecode = 0;
    }else if(decodeWrong == 1){
        LCD_Char_Position(1u,0u);
        char8 displayB[] = "bad";
        LCD_Char_PrintString(displayB);
        decodeWrong = 0;
    }
}//end Display()

/*
 * function: void CheckParity(void)
 * parameters: void
 * returns: void
 * description: XORs each bit of data to get even or odd parity for
 * error checking
 */
int CheckParity(crabs)
{
    int i = 0;
    int bitToCheck = crabs >> 1; // Remove parity from data
    int receivedParity = (crabs & BIT_0_MASK); //Save parity from data received
    int parity = bitToCheck & BIT_0_MASK; // Get first bit of data to XOR
    for(i = 0; i < DATA_LENGTH; i++){
        bitToCheck = bitToCheck >> 1; // shift mask over
        parity = (bitToCheck & BIT_0_MASK) ^ parity; // XOR new bit
    }
    if(parity == receivedParity){
        return SUCCESS;
    }else{
        return FAILURE;
    }
}   

/*
 * function: void LEDSOn(void)
 * parameters: void
 * returns: void
 * description: Turns on LED if bit is high
 */
void LEDSOn(data, paritySuccess)
{
    Control_Reg_Write(data);
    Parity_Write(paritySuccess);
}

//Clears watchdog timer to avoid reset unless timing has drifted
CY_ISR_PROTO(watchDogCheck){
    
    CyWdtClear(); 
        
}
    

/* [] END OF FILE */
