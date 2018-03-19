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

#define Count4_Seconds 1 
#define CountHalf_Second 55
//count = 0.5s / T
#define ZeroHalf_Second 45
#define LED_ON  0xFF
#define LED_OFF 0 
#define oneByte 4 
#define twoByte 8
#define ZERO 0
#define ONE 0xFF

CY_ISR_PROTO(Prefix_Int);
CY_ISR_PROTO(Zero_Int);

//static int zeroCounter = 0; 
static uint8 testLEDStatus = LED_ON;
static int pwmCounter = 1;
static int zeroCounter = 1;
static uint8 bitCase = ZERO;
static uint8 messageBit = 0; 
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    //LowFLow_Start();
    //FSK_Start();
    LowFHigh_Start() ;
    //FSKOutput_Start();
    LowFPwm_Start(); 
    ZeroPwm_Start();
    ZeroPwm_Sleep();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    OneInt_StartEx(Prefix_Int);
    ZeroInt_StartEx(Zero_Int);
    //SleepTimer_Start() ;
    LEDTest_Write(testLEDStatus);
    //LowFPwm_WriteCompare(127);
    for(;;)
    {
        /* Place your application code here. */
        
        if((pwmCounter % CountHalf_Second) == 0){
            testLEDStatus = testLEDStatus ^ 0xFF; 
            LEDTest_Write(testLEDStatus); 
            //CyDelay(100);
            messageBit++;
            pwmCounter = 1;
            //can't reset to 0 due to mod operator, so reset to 1
        }
        
        if((zeroCounter % ZeroHalf_Second) == 0){
            testLEDStatus = testLEDStatus ^ 0xFF; 
            LEDTest_Write(testLEDStatus); 
            //CyDelay(100);
            messageBit++;
            zeroCounter = 1;
            //can't reset to 0 due to mod operator, so reset to 1
        }
        
        
        switch(messageBit){
        
            case 0:
                bitCase = ONE;
            
            break; 
            case 1:
                bitCase = ONE; 
            break;
            case 2:
                bitCase = ONE; 
            break;
            case 3:
                bitCase = ONE; 
            break;
            case 4:
                bitCase = ZERO; 
                LowFPwm_Sleep();
                ZeroPwm_Start();
                
            break; 
            case 5:
                bitCase = ZERO; 
                //CyDelay(50);
                //messageBit++;
                
            break; 
            case 6:
                bitCase = ONE; 
                //LowFPwm_Wakeup();
                //LowFPwm_Start();
                LowFPwm_Start();
                ZeroPwm_Sleep();
            break; 
            case 7:
                bitCase = ZERO; 
                //LowFPwm_Sleep();
                LowFPwm_Sleep();
                ZeroPwm_Start();
            break; 
            case 8:
                bitCase = ONE; 
                //LowFPwm_Wakeup();
                //LowFPwm_Start();
                LowFPwm_Start();
                ZeroPwm_Sleep();
            break;     
            case 9:
                bitCase = ONE; 
                //LowFPwm_Sleep();
            break;
            case 10:
                bitCase = ONE; 
                
            break;
            case 11:
                bitCase = ONE; 
                
            break;    
            
        default:
        break; 
  
        }
        
        //MuxSelect_Write(bitCase);
        MuxSelOut_Write(bitCase);
      
    }
}


CY_ISR(Prefix_Int){
    
    pwmCounter++;

    
    //SleepTimer_GetStatus() ;

}

CY_ISR(Zero_Int){
    
    zeroCounter++;

    
    //SleepTimer_GetStatus() ;

}

/* [] END OF FILE */

     