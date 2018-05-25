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

#define ARRAY_SIZE 12
#define COUNT      100
#define ACCURACY   70

/*Function Prototypes*/
void Display(void);

// Interrupt for switching bits 5 ms
CY_ISR_PROTO(Bit_Timer);

// Global Variables
static uint16 levelCounter = 0; // Timer counter to debounce bit
static uint8 zeroCount = 0; // 0 count used in timer counter debounce
static uint16 oneCount = 0; // 1 count used in timer counter debounce
static uint8 currentBit = 0; // x/10 bit decision for 500 ms bit
static uint8 dataCount = 0; // which bit of data we are looking at
static uint8 data = 0; // 4 bits of data
static uint8 crabs = 0; // 4 bits of data transferred from data variable
static uint8 dataFlag = 0; // Flag to start looking for data
static uint8 decodeFlag = 0; // Flag to start looking for post-fix

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
    CyGlobalIntEnable; 

    /* initialization/startup code here */
    PWM_Recon_Start();
    Shift_Reg_Start();
    Out_Comp_Start();
    Bit_Timer_Start();
    Timer_ISR_StartEx(Bit_Timer);
    LCD_Char_Start();

    // Displays Loading Message before receiving pre-fix=
    sprintf(display, "counting crabs...");
    LCD_Char_Position(0u,0u); // Resets cursor to top of LCD Screen
    LCD_Char_PrintString(display);

    for(;;)
    {
        Display();
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
        if(oneCount >= ACCURACY){ // 1 bit must be 7/10 = 1 
            currentBit = 0x01;
            oneCount = 0;
        
        }else{ // if oneCount <= 7, bit is 0
            currentBit = 0x00; 
            zeroCount = 0; 
        }
        dataCount++; // Keep track of what bit we are on
        levelCounter = 0; // Reset timer bit debouncer  
        
        //Look for pre-fix
        data = data << 1; // Shift data over to store next bit
        data = data | currentBit;
        // Check if data is prefix(oxFF) but we are not looking for data or decode
        if((data == 0xff) && (dataFlag == 0) && (decodeFlag == 0)){ 
            Count_Out_Write(1);
            dataCount = 0;
            data = 0x00;
            dataFlag = 1; //Start looking for data
            lcdFlagEncode = 1; //Display pre-fix on lcd

        
        // Look for 4 bits of data
        }else if((dataFlag == 1) && (dataCount > 3)){
            crabs = data;
            data = 0; //Restart data for decode
            dataCount = 0; 
            lcdFlagEncode = 0; //Turn off encode message
            lcdFlagData = 1; //Display data
            decodeFlag = 1; //Now go to decode stage
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
    // When 4 bits are received, data will display at top of screen
    }else if(lcdFlagData == 1){
        sprintf(OutputString, "%i", crabs);
        LCD_Char_ClearDisplay();
        LCD_Char_Position(0u,0u);
        LCD_Char_PrintString(OutputString);
        LCD_Char_PrintString(" crabs");
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
    

/* [] END OF FILE */
