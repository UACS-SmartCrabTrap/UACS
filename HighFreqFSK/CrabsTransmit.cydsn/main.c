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

/*PWM Frequencies*/
#define ONE_FREQ 42000
#define ZERO_FREQ 37000
#define ONE 1
#define ZERO 0

CY_ISR_PROTO(isr_sec); // High F Interrupt


/*Global Variables*/
int stop = ZERO;
uint8 newDataflag = 0;
uint8 errorStatus = 0u;
uint8 rxData = 0;
int crabs = 0; // How many crabs are in the trap?
int dataCount = 0;

CY_ISR(RxIsr)
{
    uint8 rxStatus;  

    do
    {
        /* Read receiver status register */
        rxStatus = UART_RXSTATUS_REG;

        if((rxStatus & (UART_RX_STS_BREAK      | UART_RX_STS_PAR_ERROR |
                        UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN)) != 0u)
        {
            /* ERROR handling. */
            errorStatus |= rxStatus & ( UART_RX_STS_BREAK      | UART_RX_STS_PAR_ERROR | 
                                        UART_RX_STS_STOP_ERROR | UART_RX_STS_OVERRUN);
        }
        
        if((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u){
            /* Read data from the RX data register */
            rxData = UART_RXDATA_REG;
            if(errorStatus == 0u){
                /* Send data backward */
                UART_TXDATA_REG = rxData;
                crabs = rxData;
                newDataflag = 1;
            }
        }
        
    }while((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u);
}

// Interrupt triggered on a CRAB_TIME timer timeout
// This will turn PWM signal off
CY_ISR(isr_sec)
{
    stop = ONE;
    
}//end CY_ISR(isr_sec)

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */


    /*Block initializations*/
    UART_Start();           /* Start communication component */
    PWM_Modulator_Start();
    PWM_Modulator_WritePeriod(FREQ(ONE_FREQ));
    PWM_Modulator_WriteCompare((FREQ(ONE_FREQ))/2); // Sets pulse width
    PWM_Switch_Timer_Start();
    
    isr_sec_StartEx(isr_sec);
    isr_rx_StartEx(RxIsr);

    for(;;)
    {
        if(errorStatus != 0u){
            /* Clear error status */
            errorStatus = 0u;
        }

        if(newDataflag == 1){
            stop = ZERO;
            PWM_Modulator_Start();
            PWM_Switch_Timer_Start();
            PWM_Switch_Timer_WritePeriod(CRAB_TIME*rxData); 
            newDataflag = 0; // Reset flag to 0, no new data
        }else if(stop == ONE){
            PWM_Modulator_Stop();
            PWM_Switch_Timer_Stop();
        }
    } /* [] END OF for(;;) */
} /* [] END OF main */

/* [] END OF FILE */





