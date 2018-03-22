/*Included header files*/
#include "project.h"

/*Definitions*/
#define CLOCK_FREQ 500000
#define FREQ(x) CLOCK_FREQ/x
#define MAX_FREQ 1000
#define MIN_FREQ 100
#define DEFAULT_FREQ MIN_FREQ
#define INCREMENTATION 300

/*Function Prototypes*/
//CY_ISR_PROTO(Increment_Button_ISR);
//CY_ISR_PROTO(Decrement_Button_ISR);
//CY_ISR_PROTO(Reset_Button_ISR);

/*Global Variables*/
unsigned int Freq = DEFAULT_FREQ;

int main(void)
{
    CyGlobalIntEnable;
    
    PWM_1_Start();
    PWM_2_Start();
    PWM_3_Start();
    
    //Increment_Button_ISR_StartEx(Increment_Button_ISR);
    //Decrement_Button_ISR_StartEx(Decrement_Button_ISR);
    //Reset_Button_ISR_StartEx(Reset_Button_ISR);
    
    //unsigned int ADCValue;
    while (1) {
        
        PWM_1_WritePeriod(FREQ(100));
        PWM_1_WriteCompare((FREQ(100))/2); // Sets pulse width
        CyDelay(500);
        PWM_1_WritePeriod(FREQ(85));
        PWM_1_WriteCompare((FREQ(85))/2); // Sets pulse width
        CyDelay(500);
//        PWM_2_WritePeriod(74);
//        PWM_2_WriteCompare(37);
        
    }//end while(1)
    
}//end main()

/***********************************
CY_ISR(Increment_Button_ISR){
    if(Freq < MAX_FREQ){
        Freq += INCREMENTATION;
    }
}

CY_ISR(Decrement_Button_ISR){
    if(Freq > MIN_FREQ){
        Freq -= INCREMENTATION;
    }
}

CY_ISR(Reset_Button_ISR){
    Freq = DEFAULT_FREQ;
}
**********************************/