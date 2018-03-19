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

CY_ISR_PROTO(LevelCheck);
static uint16 levelCounter = 0;
static uint8 zeroCount = 0; 
static uint8 oneCount = 0; 
//static uint8 messageBit = 0; 
static uint8 currentBit = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    BPF_Comp_Start();
    ShiftReg_Start();
    Ref_OpAmp_Start();
    PGA_Start() ; 
    OutComp_Start();
    LevelCount_Start();
    LeveCountISR_StartEx(LevelCheck);
    
    HighF_BPF_Comp_Start();
    HighF_ShiftReg_Start();
    HighF_Ref_OpAmp_Start();
    HighF_PGA_Start() ; 
    HighF_OutComp_Start();
    HighF_LevelCount_Start();
    //LeveCountISR_StartEx(LevelCheck);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        
        /* Place your application code here. */
    }
}
//Bit length = 0.5s
//counter period = 0.05s
//will check bit 10 times, to debounce
//will set bit after 0.4s (8 checks) 
CY_ISR(LevelCheck){
    levelCounter++;
    
    if(OutComp_GetCompare() != 0){
        oneCount++;
    }else{
        zeroCount++;
    }
    
    //debouncing every 0.4s, with a check of 7/8 hits 
    if(levelCounter == 8){
        if(oneCount >= 7){
            currentBit = 1;
            oneCount = 1;
        
        }if(zeroCount >= 7){
            currentBit = 0; 
            zeroCount = 0; 
        }
    
    }

}

/* [] END OF FILE */
