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

/*Definitions*/
#define CLOCK_FREQ 5000
#define FREQ(x) (CLOCK_FREQ/x)-1
#define ONE_FREQ 100
#define ZERO_FREQ 85
#define DEFAULT_FREQ MIN_FREQ
#define ZERO 0
#define ONE 1

//Low F Interrupts
CY_ISR_PROTO(isr_halfsec);

static int bitTime = 0;
static int encode = 0;
static int decode = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    PWM_Modulator_Start();
    PWM_Switch_Timer_Start();
    isr_halfsec_StartEx(isr_halfsec);
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int bitCase = 0;

    
    for(;;)
    {
        /* Place your application code here. */
        
        switch(bitTime){
        
            case 0:
                bitCase = ONE;
            break; 
            // DATA
            case 1:
                bitCase = ONE; 
            break; 
            case 2:
                bitCase = ONE; 
            break; 
            case 3:
                bitCase = ZERO; 
            break; 
            case 4:
                bitCase = ONE; 
            break; 
            // END OF DATA
            case 5:
                bitCase = ZERO; 
            break;     
            case 6:
                bitCase = ONE; 
            break;   
            case 7:
                bitCase = ZERO;
            break;
            case 8:
                bitCase = ZERO;
            break;
            case 9:
                bitCase = ZERO;
            break;
            case 10:
                bitTime = 0;
            break;
        default:
        break; 
         
        } //end of Switch 
        
        if(bitCase == 1){
            PWM_Modulator_WritePeriod(FREQ(ONE_FREQ));
            PWM_Modulator_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width
        }else if(bitCase == 0){
            PWM_Modulator_WritePeriod(FREQ(ZERO_FREQ));
            PWM_Modulator_WriteCompare((FREQ(ZERO_FREQ))/2); // Sets pulse width
        }
    }
}

CY_ISR(isr_halfsec){
    if((bitTime == 0) && (encode < 7)){
        encode++;
    }
    else if(bitTime == 5){
        decode++;
        if(decode > 6){
            bitTime++;
        }
    }
    else if((encode > 6) && (decode == 0)){
        bitTime++;
    }
    else{
        bitTime++;
        encode = 0;
        decode = 0;
    }
}

/* [] END OF FILE */
