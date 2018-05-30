/*******************************************************************************
* File Name: common.h
*
* Updated: 5/22/18
*
* Description:
*  Contains the function prototypes and constants available to the code 
*  project.
*
*******************************************************************************/

#include "cytypes.h"

#define ENABLED                     (1u)
#define DISABLED                    (0u)


/***************************************
* Conditional Compilation Parameters
***************************************/
#define UART_PRINTF_ENABLED         ENABLED
#define INTERRUPT_CODE_ENABLED      ENABLED
#define UART                        ENABLED


/***************************************
*           API Constants
***************************************/

#if(CY_PSOC4)
    #define LED_ON                      (0u)
    #define LED_OFF                     (1u)
#else   /* PSoC 3/PSoC 5LP: The LED is connected to the GND instead of Vdd. */
    #define LED_ON                      (1u)
    #define LED_OFF                     (0u)
#endif /* (CY_PSOC4) */

/* [] END OF FILE */
