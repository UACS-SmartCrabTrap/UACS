/*******************************************************************************
* File Name: OneInt.h
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
#if !defined(CY_ISR_OneInt_H)
#define CY_ISR_OneInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void OneInt_Start(void);
void OneInt_StartEx(cyisraddress address);
void OneInt_Stop(void);

CY_ISR_PROTO(OneInt_Interrupt);

void OneInt_SetVector(cyisraddress address);
cyisraddress OneInt_GetVector(void);

void OneInt_SetPriority(uint8 priority);
uint8 OneInt_GetPriority(void);

void OneInt_Enable(void);
uint8 OneInt_GetState(void);
void OneInt_Disable(void);

void OneInt_SetPending(void);
void OneInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the OneInt ISR. */
#define OneInt_INTC_VECTOR            ((reg32 *) OneInt__INTC_VECT)

/* Address of the OneInt ISR priority. */
#define OneInt_INTC_PRIOR             ((reg8 *) OneInt__INTC_PRIOR_REG)

/* Priority of the OneInt interrupt. */
#define OneInt_INTC_PRIOR_NUMBER      OneInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable OneInt interrupt. */
#define OneInt_INTC_SET_EN            ((reg32 *) OneInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the OneInt interrupt. */
#define OneInt_INTC_CLR_EN            ((reg32 *) OneInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the OneInt interrupt state to pending. */
#define OneInt_INTC_SET_PD            ((reg32 *) OneInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the OneInt interrupt. */
#define OneInt_INTC_CLR_PD            ((reg32 *) OneInt__INTC_CLR_PD_REG)


#endif /* CY_ISR_OneInt_H */


/* [] END OF FILE */
