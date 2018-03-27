/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

#define timerclk 80000
#define timercount 256
#define counterCount 254

CY_ISR_PROTO(TimerISR);
CY_ISR_PROTO(Frequency);

static int time = 0;
static int fullTimer = timercount/ (timerclk/1000) ;
//in  microseconds 
static int frequency2 = 7;
static uint8 printFlag = 0;
static int currentTime;
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    HighF_Comparator_Start()  ;
    RiseCount_Start() ;
    Timer_Start() ;
    Timing_StartEx(TimerISR);
    FreqCalc_StartEx(Frequency);
    LCD_Char_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   char OutputString[12]; 
//   sprintf(OutputString, "%i", frequency2);
//    LCD_Char_Position(0u,0u);
//    LCD_Char_PrintString(OutputString);
//    LCD_Char_PrintString(" pls?");

    for(;;)
    {
        /* Place your application code here. */
        if(printFlag == 1){
            
                sprintf(OutputString, "%i, %i, %i",currentTime, frequency2, ((currentTime) / counterCount) );
                LCD_Char_Position(0u,0u);
                LCD_Char_PrintString(OutputString);
                LCD_Char_PrintString(" pls?");
                printFlag = 0;
        
        }
        

    }
}

CY_ISR(TimerISR){
//80khz clk
//256
    time = time + fullTimer; 
    //in microseconds

}

CY_ISR_PROTO(Frequency){
//Triggered on TC of counter 
//clk = 12MHz
//count = 254
    
    //capture current timer value
    currentTime = (Timer_ReadCounter()/(timerclk/1000)) + time;
    //in microseconds
    //currentTime = currentTime * 1000;
    frequency2 = 1 /( (currentTime) / counterCount); 
    //frequency2 =frequency2 * 10000;
    time = 0;
    printFlag = 1;
    Timer_WriteCounter(0) ;
     RiseCount_WriteCounter(0); 
    
    
}

/* [] END OF FILE */
