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
//LowF Counts for 0.5s bit time
//count = 0.5s / T
#define L_OneHalf_Second 50
#define L_ZeroHalf_Second 43

#define H_OneHalf_Second 55
#define H_ZeroHalf_Second 45

#define LED_ON  0xFF
#define LED_OFF 0 
#define oneByte 4 
#define twoByte 8
#define ZERO 0
#define ONE 0xFF

//Low F Interrupts
CY_ISR_PROTO(LowF_Zero_Int);
CY_ISR_PROTO(LowF_One_Int);

CY_ISR_PROTO(HighF_Zero_Int);
CY_ISR_PROTO(HighF_One_Int);


//Static Variables
static int L_oneCounter = 1;
static int L_zeroCounter = 1;
static int H_oneCounter = 1;
static int H_zeroCounter = 1;
static uint8 L_messageBit = 0;    //Controls flow of bit 'state machine' 
static uint8 H_messageBit = 0;    //Controls flow of bit 'state machine' 
static uint8 bitCase = ZERO;    //Controls which bit (0 or 1) is being transmitted 
static uint8 testLEDStatus = LED_ON;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LowF_OnePWM_Start(); 
    //LowF_ZeroPWM_Start();
    LowF_ZeroPWM_Sleep();
    
    HighF_OnePWM_Start(); 
    //HighF_ZeroPWM_Start();
    HighF_ZeroPWM_Sleep();
    
    LEDTest_Write(testLEDStatus);
    
    //Low F Interrupts
    LowF_OneInt_StartEx(LowF_Zero_Int);
    LowF_ZeroInt_StartEx(LowF_One_Int);
    
    
   //High F Interrupts
    HighF_OneInt_StartEx(HighF_Zero_Int);
    HighF_ZeroInt_StartEx(HighF_One_Int);

    
    for(;;)
    {
        /* Place your application code here. */
        
        //When the counters are such that the bit has been held for 0.5s
        //Move all counters such that next bit is being transmitted 
        if((L_oneCounter % L_OneHalf_Second) == 0){
            testLEDStatus = testLEDStatus ^ 0xFF; 
            LEDTest_Write(testLEDStatus); 
            L_messageBit++;
            L_oneCounter = 1;
            //can't reset to 0 due to mod operator, so reset to 1
        }
        
        if((L_zeroCounter % L_ZeroHalf_Second) == 0){
            testLEDStatus = testLEDStatus ^ 0xFF; 
            LEDTest_Write(testLEDStatus); 
            L_messageBit++;
            L_zeroCounter = 1;
            //can't reset to 0 due to mod operator, so reset to 1
        }
        
        if((H_oneCounter % H_OneHalf_Second) == 0){
            testLEDStatus = testLEDStatus ^ 0xFF; 
            LEDTest_Write(testLEDStatus); 
            H_messageBit++;
            H_oneCounter = 1;
            //can't reset to 0 due to mod operator, so reset to 1
        }
        
        if((H_zeroCounter % H_ZeroHalf_Second) == 0){
            testLEDStatus = testLEDStatus ^ 0xFF; 
            LEDTest_Write(testLEDStatus); 
            H_messageBit++;
            H_zeroCounter = 1;
            //can't reset to 0 due to mod operator, so reset to 1
        }
        
        switch(L_messageBit){
        
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
                LowF_OnePWM_Sleep();
                LowF_ZeroPWM_Start();
                
            break; 
            case 5:
                bitCase = ZERO; 
              
            break; 
            case 6:
                bitCase = ONE; 
                LowF_ZeroPWM_Sleep();
                LowF_OnePWM_Start();
            break; 
            case 7:
                bitCase = ZERO; 
                LowF_OnePWM_Sleep();
                LowF_ZeroPWM_Start();
            break; 
            case 8:
                bitCase = ONE; 
                LowF_ZeroPWM_Sleep();
                LowF_OnePWM_Start();
            break;     
            case 9:
                bitCase = ONE; 
            break;
            case 10:
                bitCase = ONE; 
                
            break;
            case 11:
                bitCase = ONE; 
                L_messageBit = 0;
                
            break;    
            
        default:
        break; 
  
        }
        
        
        
        switch(H_messageBit){
        
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
                HighF_OnePWM_Sleep();
                HighF_ZeroPWM_Start();
                
            break; 
            case 5:
                bitCase = ZERO; 
              
            break; 
            case 6:
                bitCase = ONE; 
                HighF_ZeroPWM_Sleep();
                HighF_OnePWM_Start();
            break; 
            case 7:
                bitCase = ZERO; 
                HighF_OnePWM_Sleep();
                HighF_ZeroPWM_Start();
            break; 
            case 8:
                bitCase = ONE; 
                HighF_ZeroPWM_Sleep();
                HighF_OnePWM_Start();
            break;     
            case 9:
                bitCase = ONE; 
            break;
            case 10:
                bitCase = ONE; 
                
            break;
            case 11:
                bitCase = ONE; 
                H_messageBit = 0;
                
            break;    
            
        default:
        break; 
  
        }
        
        LowF_MuxSelOut_Write(bitCase);
        HighF_MuxSelOut_Write(bitCase);
    }
}

//Low F Interrupts
//Triggered on PWM TC
//Will increment counter, that will determine the bit time in main code
CY_ISR(LowF_Zero_Int){
   
   L_zeroCounter++;

}

CY_ISR(LowF_One_Int){
    
    L_oneCounter++;

}

CY_ISR_PROTO(HighF_Zero_Int){
   
    H_zeroCounter++;

}
CY_ISR_PROTO(HighF_One_Int){
    
    H_oneCounter++;

}
/* [] END OF FILE */
