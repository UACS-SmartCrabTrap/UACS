/* ========================================
 * Smart Crab Trap
 * FSK RX 
 * Edited by: Stephanie Salazar
 * Revision: 4/18/18
 *
 * ========================================
*/

#include "project.h"
#include <stdio.h>
#include "LCD_Char.h"

// Interrupt for switching bits 500 ms
CY_ISR_PROTO(HighF_LevelCount);

// Global Variables
static uint16 levelCounter = 0; // Timer counter to debounce bit
static uint8 zeroCount = 0; // 0 count used in timer counter debounce
static uint8 oneCount = 0; // 1 count used in timer counter debounce
static uint8 currentBit = 0; // x/10 bit decision for 500 ms bit
static uint8 dataCount = 0; // which bit of data we are looking at
static uint8 data = 0; // 4 bits of data
static uint8 crabs = 0; // 4 bits of data transferred from data variable
static uint8 dataFlag = 0; // Flag to start looking for data
static uint8 decodeFlag = 0; // Flag to start looking for post-fix


//FLAGS for turning on messages on LCD screen
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
    HighF_BPF_Comp_Start();
    HighF_ShiftReg2_Start();
    HighF_PGA_Start() ; 
    HighF_OutComp_Start();
    HighF_LevelCount_Start();
    HighF_LevelCountISR_StartEx(HighF_LevelCount);
    LCD_Char_Start();
    PGA_1_Start();

    // Displays Loading Message before receiving pre-fix
    char OutputString[12];
    char display[12];
    sprintf(display, "counting crabs...");
    LCD_Char_Position(0u,0u); // Resets cursor to top of LCD Screen
    LCD_Char_PrintString(display);

    for(;;)
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
    } // end of for(;;)
} // end of main()
    

//Bit length = 500 ms
//timer period = 50 ms
//will check bit 10 times, to debounce
CY_ISR(HighF_LevelCount){
    levelCounter++;
    
    // Count whether bit is currently 1 or 0
    if(HighF_OutComp_GetCompare() != 0){
        oneCount++;
    }else{
        zeroCount++;
    }
    
    // Debouncing
    if(levelCounter == 10){
        if(oneCount >= 7){ // 1 bit must be 7/10 = 1 
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
            HighF_CountOut_Write(1);
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
    } // end of if(levelCounter == 10)
} // end of CY_ISR(HighF_LevelCount)

/* [] END OF FILE */
