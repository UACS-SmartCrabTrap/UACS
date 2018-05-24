/* ========================================
 *
 * Created by: Stephanie Salazar
 * Created: 5/22/18
 * Project: CrabsTransmit
 * Description: Receives amount of crabs via UART and sends
 * amount by 1 crab per CRAB_TIME
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include "common.h"
#include "stdlib.h"

/* Character LCD String Length */
#define LINE_STR_LENGTH     (20u)

/*Definitions*/
#define CLOCK_FREQ 1000000
#define FREQ(x) (CLOCK_FREQ/x)-1
#define CRAB_TIME 50 //1 crab per CRAB_TIME
#define TEST_VALUE 42

/*PWM Frequencies*/
#define ONE_FREQ 42000
#define ZERO_FREQ 37000
#define AUDIBLE_FREQ 12000
#define ONE 1
#define ZERO 0

/* Function Prototypes */
CY_ISR_PROTO(isr_sec); // High F Interrupt
CY_ISR_PROTO(sleep_interrupt);

/*Global Variables*/
int stop = ONE;
uint8 newDataflag = 0;
uint8 errorStatus = 0u;
uint8 rxData = 0;
int crabs = 0; // How many crabs are in the trap?
int dataCount = 0;

/*
 * RxIsr interrupt
 * Interrupt triggered when rx 
 */
CY_ISR(RxIsr)
{
    uint8 rxStatus;  

    do
    {
        /* Read receiver status register */
        rxStatus = UART_RXSTATUS_REG;

        /* Check status for errors */
        if((rxStatus & (UART_RX_STS_BREAK      | UART_RX_STS_PAR_ERROR |
                        UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            errorStatus |= rxStatus & ( UART_RX_STS_BREAK      | UART_RX_STS_PAR_ERROR | 
                                        UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN);
        }
        /* If receiver status is not empty */
        if((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u){
            /* Read data from the RX data register */
            rxData = UART_RXDATA_REG;
            if(errorStatus == 0u){
                /* Send data backward */
                UART_TXDATA_REG = rxData;
                crabs = rxData; // put data in variable to send
                newDataflag = 1; //Set flag true to send data
            }
        }
        
    }while((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u); //read until empty
}

/*
 * isr_sec interrupt
 * Interrupt triggered on a CRAB_TIME timer timeout
 * This will turn PWM signal off
 */
CY_ISR(isr_sec)
{
#if(UART == ENABLED)
    stop = ONE;
#else 
    newDataflag = 1 ^ newDataflag;
#endif /* UART == ENABLED */
}//end CY_ISR(isr_sec)
                                                                                                                                                                                                                                                                                                                                                        
/*
 * isr_sec interrupt
 * Interrupt triggered on a CRAB_TIME timer timeout
 * This will turn PWM signal off
 */
CY_ISR(rx_test)
{
    HighVoltage_Write(1);
}//end CY_ISR(rx_test)

/*
 * WakeupIsr interrupt
 * PSoC turns on and checks for signal
 */
CY_ISR(sleep_interrupt)
{
    SleepTimer_GetStatus(); // Clears the sleep timer interrupt
} // end CY_ISR(WakeupIsr)
    

/*
 * function: main()
 * parameters: none
 * returns: int (Should never return)
 * description: toggles a pin off and on every four seconds and sends a 40k PWM
 *      signal 
 */
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */


    /*Block initializations*/
    //UART_Start();           /* Start communication component */
    PWM_Modulator_Start();
    PWM_Modulator_WritePeriod(FREQ(ONE_FREQ));
    PWM_Modulator_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width
    PWM_Switch_Timer_Start();
    PWM_Switch_Timer_WritePeriod(CRAB_TIME*42); 
    sleep_interrupt_StartEx(sleep_interrupt);
    SleepTimer_Start();
    // Testing PWMs
    PWM_1_Start();
    PWM_2_Start();
    PWM_3_Start();
    
    //Testing PWMS
    // Set PWM to AUDIBLE_FREQ
    PWM_1_WritePeriod(FREQ(AUDIBLE_FREQ));
    PWM_1_WriteCompare((FREQ(AUDIBLE_FREQ))/2); // Sets pulse width to half
    
    // Set PWM to ONE_FREQ
    PWM_2_WritePeriod(FREQ(ONE_FREQ));
    PWM_2_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width to half
    
    // Set PWM to ZERO_FREQ
    PWM_3_WritePeriod(FREQ(ZERO_FREQ));
    PWM_3_WriteCompare((FREQ(ZERO_FREQ))/2); // Sets pulse width to half
    
    /* Start interrupts */
    isr_sec_StartEx(isr_sec);
#if(INTERRUPT_CODE_ENABLED == ENABLED)
    isr_rx_StartEx(RxIsr);
#endif /* INTERRUPT_CODE_ENABLED == ENABLED */

    // PSoC Sleep command. To adjust sleep time, change in the hardware
    //  block. No sleep time parameters taken in PSoC5LP.
    //  PM_SLEEP_TIME_NONE is a relic of PSoC3
    CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_CTW);

    for(;;)
    {
        if(errorStatus != 0u){
            /* Clear error status */
            errorStatus = 0u;
        }
        
#if(UART == ENABLED)
        /* If new data is received from UART */
        if(newDataflag == 1){
            stop = ZERO;
            //HighVoltage_Write(1); //Turn boost converter on
            /* Need to turn PWM and timer on again to send data */
            PWM_Modulator_Wakeup();
            PWM_Switch_Timer_Wakeup();
            PWM_Modulator_Start();
            PWM_Switch_Timer_Start();
            PWM_Switch_Timer_WritePeriod(CRAB_TIME*crabs); //send over amount of crabs (1 crab = CRAB_TIME)
            newDataflag = 0; // Reset flag to 0, no new data
        /* If timer is done sending crabs */
        }else if(stop == ONE){
            PWM_Modulator_Stop(); //Turn PWM off
            PWM_Switch_Timer_Stop(); //Turn timer off until new data
            PWM_Modulator_Sleep(); //Turn PWM off
            PWM_Switch_Timer_Sleep(); //Turn timer off until new data
            //HighVoltage_Write(0); //Turn boost converter off
            CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_CTW); //Back to sleep mode
        }
        
#else   /* Testing mode */
        /* Timer will switch between 1 and 0 depending on TEST_VALUE */
        if(newDataflag == 1){
            HighVoltage_Write(1); //Turn boost converter on
            stop = ZERO;
            // Need to wakeup and start hardware blocks
            PWM_Modulator_Wakeup();
            PWM_Switch_Timer_Wakeup();
            PWM_Modulator_Start();
            PWM_Switch_Timer_WritePeriod(CRAB_TIME*TEST_VALUE); 
        }else if(newDataflag == 0){
            PWM_Modulator_Stop(); // Turn PWM off
            HighVoltage_Write(0); //Turn boost converter off
        }
#endif /* (UART) */


        
    } /* [] END OF for(;;) */
} /* [] END OF main */

/* [] END OF FILE */





