/*****************************************************************************
* File Name: main.c
*
* Created: 5/16/18
* Revised: 5/17/18
* Revised by: Stephanie Salazar
*
* Description: 
*  This project communicates via UART in Full duplex mode. The UART has
* receiver(RX) and transmitter(TX)]. The data received by RX is used for
* FSK transmission. 
*
* Related Document: 
* CE210741_UART_Full_Duplex_and_printf_Support_with_PSoC_3_4_5LP.pdf
*
* Hardware Dependency: See 
* CE210741_UART_Full_Duplex_and_printf_Support_with_PSoC_3_4_5LP.pdf
*
*******************************************************************************
*/

#include <project.h>
#include <stdio.h>
#include "common.h"
#include "stdlib.h"

/* Character LCD String Length */
#define LINE_STR_LENGTH     (20u)

/* Global Variables */
uint8 errorStatus = 0u;
char8 data[LINE_STR_LENGTH];


/*******************************************************************************
* Function Name: RxIsr
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the UART
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
    uint8 rxStatus;         
    uint8 rxData;           
    
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
            rxData = UART_RXDATA_REG;
            if(errorStatus == 0u)
            {
                /* Send data backward */
                UART_TXDATA_REG = rxData;
                /* Clear LCD line. */
                LCD_Position(0u, 0u);
                sprintf(data,"Crabs: %d", rxData);
                LCD_PrintString("             ");

                /* Output string on LCD. */
                LCD_Position(0u, 0u);
                LCD_PrintString(data);
            }
        }
    }while((rxStatus & UART_RX_STS_FIFO_NOTEMPTY) != 0u);

}
    

/*******************************************************************************
* Function Name: main()
*******************************************************************************/
int main()
{
    UART_Start();           /* Start communication component */
    UART_PutString("UART Full Duplex and printf() support Code Example Project \r\n");

#if(INTERRUPT_CODE_ENABLED == ENABLED)
    isr_rx_StartEx(RxIsr);
#endif /* INTERRUPT_CODE_ENABLED == ENABLED */
    
    CyGlobalIntEnable;      /* Enable global interrupts. */
    /*Block initializations*/
    LCD_Start();
    
    /* Clear LCD line. */
    LCD_Position(0u, 0u);
    LCD_PrintString("                    ");

    /* Output string on LCD. */
    LCD_Position(0u, 0u);
    LCD_PrintString("Hello");

    

    for(;;)
    {
        if(errorStatus != 0u)
        {
            /* Clear error status */
            errorStatus = 0u;
        }
       
    }
}

/* [] END OF FILE */
