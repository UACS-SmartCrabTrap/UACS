/*******************************************************************************
* File Name: watchDogCheck.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_watchDogCheck_H)
#define CY_ISR_watchDogCheck_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void watchDogCheck_Start(void);
void watchDogCheck_StartEx(cyisraddress address);
void watchDogCheck_Stop(void);

CY_ISR_PROTO(watchDogCheck_Interrupt);

void watchDogCheck_SetVector(cyisraddress address);
cyisraddress watchDogCheck_GetVector(void);

void watchDogCheck_SetPriority(uint8 priority);
uint8 watchDogCheck_GetPriority(void);

void watchDogCheck_Enable(void);
uint8 watchDogCheck_GetState(void);
void watchDogCheck_Disable(void);

void watchDogCheck_SetPending(void);
void watchDogCheck_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the watchDogCheck ISR. */
#define watchDogCheck_INTC_VECTOR            ((reg32 *) watchDogCheck__INTC_VECT)

/* Address of the watchDogCheck ISR priority. */
#define watchDogCheck_INTC_PRIOR             ((reg8 *) watchDogCheck__INTC_PRIOR_REG)

/* Priority of the watchDogCheck interrupt. */
#define watchDogCheck_INTC_PRIOR_NUMBER      watchDogCheck__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable watchDogCheck interrupt. */
#define watchDogCheck_INTC_SET_EN            ((reg32 *) watchDogCheck__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the watchDogCheck interrupt. */
#define watchDogCheck_INTC_CLR_EN            ((reg32 *) watchDogCheck__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the watchDogCheck interrupt state to pending. */
#define watchDogCheck_INTC_SET_PD            ((reg32 *) watchDogCheck__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the watchDogCheck interrupt. */
#define watchDogCheck_INTC_CLR_PD            ((reg32 *) watchDogCheck__INTC_CLR_PD_REG)


#endif /* CY_ISR_watchDogCheck_H */


/* [] END OF FILE */
