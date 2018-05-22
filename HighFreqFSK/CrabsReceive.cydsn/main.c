/* ========================================
 * Smart Crab Trap
 * FSK RX 
 * Edited by: Stephanie Salazar
 * Revision: 5/10/18
 * Function: This project takes in a signal from an outside source
 * and reads the data within the signal. This code waits for a pre-fix
 * of 0xFF and then reads the next 4 bits as the data and confirms
 * the message with a post-fix of 0x01. The data is display on an LCD display.
 * ========================================
*/

#include "project.h"
#include <stdio.h>
#include "LCD_Char.h"

#define ARRAY_SIZE 12
#define CRAB_TIME 50 //1 crab per CRAB_TIME
#define DEBOUNCE_TIME CRAB_TIME/10

// Interrupt for checking bit
CY_ISR_PROTO(Bit_Timer);

// Global Variables
static uint8 crabs = 0; // 4 bits of data transferred from data variable
static uint8 oldCrabs = 0;
static uint8 levelCounter = 0;
static uint8 currentBit = 0x0;
static uint8 oneCount = 0;
static uint8 stopCount = 0;


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
    
    //Bit_Timer_WritePeriod(DEBOUNCE_TIME); 

    // Displays Loading Message before receiving pre-fix
    char OutputString[ARRAY_SIZE];
    char display[ARRAY_SIZE];
    sprintf(display, "counting crabs...");
    LCD_Char_Position(0u,0u); // Resets cursor to top of LCD Screen
    LCD_Char_PrintString(display);

    for(;;)
    {
    // Debouncing
    // If levelCounter is 10, we have checked a whole bitTime
    if(levelCounter == 10){
        
        if(oneCount >= 9){ // 1 bit must be 7/10 = 1 
            // Reset crab count if previously not counting crabs
            currentBit = 0x01;
            crabs = currentBit + crabs;
            stopCount = 0; 
        }else{ // if oneCount <= 7, bit is 0
            currentBit = 0x00; 
            stopCount = 1; 
        }
        oneCount = 0;
        levelCounter = 0; // Reset timer bit debouncer  
        
    }

    if(stopCount == 1 && (crabs!= 0)){
        oldCrabs = crabs;
        crabs = 0;
        stopCount = 0;
        sprintf(OutputString, "%i", oldCrabs);
        LCD_Char_ClearDisplay();
        LCD_Char_Position(0u,0u);
        LCD_Char_PrintString(OutputString);
        LCD_Char_PrintString(" crabs");
        oldCrabs = crabs;
    }

    } // end of for(;;)
} // end of main()
    

//will check bit 10 times, to debounce
CY_ISR(Bit_Timer){
    levelCounter++;
    
    // Count whether bit is currently 1 or 0
    if(Out_Comp_GetCompare() != 0){
        oneCount++;
    } // end of if
} // end of CY_ISR(HighF_LevelCount)

/* [] END OF FILE */
