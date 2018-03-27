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
#include "LCD_Char.h"

//isr prototype
CY_ISR_PROTO(LevelCount);

static uint16 levelCounter = 0;
static uint8 zeroCount = 0; 
static uint8 oneCount = 0; 
static uint8 currentBit = 0;
static uint8 dataCount = 0;
static uint8 data = 0;
static uint8 crabs = 0;


//FLAGS
static uint8 lcdFlagEncode = 0;
static uint8 lcdFlagData = 0;
static uint8 lcdFlagDecode = 0;
static uint8 dataFlag = 0;
static uint8 decodeFlag = 0;
static uint8 decodeWrong = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    HighF_BPF_Comp_Start();
    HighF_ShiftReg_Start();
    HighF_Ref_OpAmp_Start();
    HighF_PGA_Start() ; 
    HighF_OutComp_Start();
    HighF_LevelCountISR_StartEx(HighF_LevelCount);
    LCD_Char_Start();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    char OutputString[12];
    char display[12];
    sprintf(display, "counting crabs...");
    LCD_Char_Position(0u,0u);
    LCD_Char_PrintString(display);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}


//Bit length = 0.5s
//timer period = 0.05s
//will check bit 10 times, to debounce
//will set bit after 0.4s (8 checks) 
CY_ISR(HighF_LevelCount){
    levelCounter++;
    
    if(OutComp_GetCompare() != 0){
        oneCount++;
    }else{
        zeroCount++;
    }
    
    //debouncing every 0.4s, with a check of 7/8 hits 
    if(levelCounter == 10){
        if(oneCount >= 7){
            currentBit = 0x01;
            oneCount = 0;
        
        }else{
            currentBit = 0x00; 
            zeroCount = 0; 
        }
        dataCount++;
        levelCounter = 0;
        //CountOut_Write(currentBit);
        
        //Look for pre-fix
        data = data << 1;
        data = data | currentBit;
        if((data == 0xff) && (dataFlag == 0) && (decodeFlag == 0)){
            CountOut_Write(1);
            dataCount = 0;
            data = 0x00;
            dataFlag = 1; //Start looking for data
            lcdFlagEncode = 1; //Display pre-fix on lcd

        
        // Look for data
        }else if((dataFlag == 1) && (dataCount > 3)){
            crabs = data;
            data = 0; //Restart data for decode
            dataCount = 0; 
            lcdFlagEncode = 0; //Turn off encode message
            lcdFlagData = 1; //Display data
            decodeFlag = 1; //Now go to decode stage
        }
        
        if(decodeFlag == 1 && (dataCount > 7)){
            if(data == 0x01){
             lcdFlagDecode = 1;
            }else{
                decodeWrong = 1;
            }
            decodeFlag = 0;
            dataFlag = 0; //Don't want to check for data anymore
        }
    }
}
/* [] END OF FILE */
