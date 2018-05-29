/*******************************************************************************
* File Name: RxWakeUp.h
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
#if !defined(CY_ISR_RxWakeUp_H)
#define CY_ISR_RxWakeUp_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void RxWakeUp_Start(void);
void RxWakeUp_StartEx(cyisraddress address);
void RxWakeUp_Stop(void);

CY_ISR_PROTO(RxWakeUp_Interrupt);

void RxWakeUp_SetVector(cyisraddress address);
cyisraddress RxWakeUp_GetVector(void);

void RxWakeUp_SetPriority(uint8 priority);
uint8 RxWakeUp_GetPriority(void);

void RxWakeUp_Enable(void);
uint8 RxWakeUp_GetState(void);
void RxWakeUp_Disable(void);

void RxWakeUp_SetPending(void);
void RxWakeUp_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RxWakeUp ISR. */
#define RxWakeUp_INTC_VECTOR            ((reg32 *) RxWakeUp__INTC_VECT)

/* Address of the RxWakeUp ISR priority. */
#define RxWakeUp_INTC_PRIOR             ((reg8 *) RxWakeUp__INTC_PRIOR_REG)

/* Priority of the RxWakeUp interrupt. */
#define RxWakeUp_INTC_PRIOR_NUMBER      RxWakeUp__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RxWakeUp interrupt. */
#define RxWakeUp_INTC_SET_EN            ((reg32 *) RxWakeUp__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RxWakeUp interrupt. */
#define RxWakeUp_INTC_CLR_EN            ((reg32 *) RxWakeUp__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RxWakeUp interrupt state to pending. */
#define RxWakeUp_INTC_SET_PD            ((reg32 *) RxWakeUp__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RxWakeUp interrupt. */
#define RxWakeUp_INTC_CLR_PD            ((reg32 *) RxWakeUp__INTC_CLR_PD_REG)


#endif /* CY_ISR_RxWakeUp_H */


/* [] END OF FILE */
