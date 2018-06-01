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

CY_ISR_PROTO(ADC_Output);
CY_ISR_PROTO(SAR_Output);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_DelSig_1_Start() ;
    ADC_DelSig_1_StartConvert() ;
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    
    VDAC8_DELSIG_Start();
    VDAC8_SAR_Start() ;
    
    Sar_ISR_StartEx(ADC_Output);
    ADC_ISR_StartEx(SAR_Output);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
CY_ISR_PROTO(ADC_Output){
    
    VDAC8_DELSIG_SetValue((uint8)ADC_DelSig_1_GetResult8()) ;

}
CY_ISR_PROTO(SAR_Output){

}