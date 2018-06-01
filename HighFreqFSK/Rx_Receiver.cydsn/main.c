/* ========================================
 *
 * UACS - Smart Crab Trap
 * Created by : Stephanie Salazar
 * Created : 5/31/18
 *
 * Description : This project uses a UART
 * to receive data from the Rx FSK Module.
 * It is output to an LCD screen.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include "stdlib.h"

CY_ISR_PROTO(RxIsr); // RX Interrupt

/* Character LCD String Length */
#define LINE_STR_LENGTH     (20u)  

char8 data[LINE_STR_LENGTH];
uint8 crabsReceived = 0;
uint8 errorStatus = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    LCD_Start();
    isr_rx_StartEx(RxIsr);
    
        /* Clear LCD line. */
    LCD_Position(0u, 0u);
    LCD_PrintString("                    ");

    /* Output string on LCD. */
    LCD_Position(0u, 0u);
    LCD_PrintString("Hello");

    for(;;)
    {
    }
}
/*******************************************************************************
* Function Name: RxIsr
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the UART taken from
*  example code and edited for storing data to send
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(RxIsr)
{
    
    //sleepToggle_Write(ON);
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
        
        if((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read data from the RX data register */
            //crabsToSend = UART_RXDATA_REG;
            crabsReceived =  UART_GetByte()  ;
            if(errorStatus == 0u)
            {
                /* Send data backward */
                UART_TXDATA_REG = crabsReceived;
                /* Clear LCD line. */
                LCD_Position(0u, 0u);
                sprintf(data,"Crabs: %d", crabsReceived);
                LCD_PrintString("             ");
                /* Output string on LCD. */
                LCD_Position(0u, 0u);
                LCD_PrintString(data);

            }else{
                isr_rx_SetPending();
                sprintf(data,"%d", errorStatus);
                LCD_PrintString(data);
            }

        }
    // Read FIFO until empty
    }while((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u);
    
    isr_rx_ClearPending();
    //sleepToggle_Write(OFF);
} //end CY_ISR(RxIsr)


/* [] END OF FILE */
