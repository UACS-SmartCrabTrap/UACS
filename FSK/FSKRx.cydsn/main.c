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

CY_ISR_PROTO(LevelCount);
static uint16 levelCounter = 0;
static uint8 zeroCount = 0; 
static uint8 oneCount = 0; 
//static uint8 messageBit = 0; 
static uint8 currentBit = 0;
static uint8 dataCount = 0;
static uint8 data = 0;
static uint8 dataFlag = 0;
static uint8 lcdFlag = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    BPF_Comp_Start();
    ShiftReg_Start();
    Ref_OpAmp_Start();
    PGA_Start() ; 
    OutComp_Start();
    LevelCount_Start();
    LevelCountISR_StartEx(LevelCount);
    
    HighF_BPF_Comp_Start();
    HighF_ShiftReg_Start();
    HighF_Ref_OpAmp_Start();
    HighF_PGA_Start() ; 
    HighF_OutComp_Start();
    HighF_LevelCount_Start();
    LCD_Char_Start();
    //LeveCountISR_StartEx(LevelCheck);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        
        /* Place your application code here. */
        if(lcdFlag == 1){

        char OutputString[12];

        sprintf(OutputString, "%i", data);
        LCD_Char_Position(0u,0u);
        LCD_Char_PrintString(OutputString);
        }
    }
}
//Bit length = 0.5s
//counter period = 0.05s
//will check bit 10 times, to debounce
//will set bit after 0.4s (8 checks) 
CY_ISR(LevelCount){
    levelCounter++;
    
    if(OutComp_GetCompare() != 0){
        oneCount++;
    }else{
        zeroCount++;
    }
    
    //debouncing every 0.4s, with a check of 7/8 hits 
    if(levelCounter == 8){
        if(oneCount >= 7){
            currentBit = 0x01;
            oneCount = 0;
        
        }if(zeroCount >= 7){
            currentBit = 0x00; 
            zeroCount = 0; 
        }
        dataCount++;
        levelCounter = 0;
        //CountOut_Write(currentBit);
        
        //Look for pre-fix
        data = data << 1;
        data = data | currentBit;
        if((data == 0xff) && (dataFlag == 0)){
            CountOut_Write(1);
            dataCount = 0;
            data = 0x00;
            dataFlag = 1;
        // Look for data
        }else if ((dataFlag == 1) && (dataCount < 4)){
            dataCount++;
        }else if((dataFlag == 1) && (dataCount > 4)){
            dataCount = 0;
            dataFlag = 0;
            lcdFlag = 1;
        }
    }
}

/* [] END OF FILE */
