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

/* [] END OF FILE */
