/*******************************************************************************
* File Name: Prefix.h
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
#if !defined(CY_ISR_Prefix_H)
#define CY_ISR_Prefix_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Prefix_Start(void);
void Prefix_StartEx(cyisraddress address);
void Prefix_Stop(void);

CY_ISR_PROTO(Prefix_Interrupt);

void Prefix_SetVector(cyisraddress address);
cyisraddress Prefix_GetVector(void);

void Prefix_SetPriority(uint8 priority);
uint8 Prefix_GetPriority(void);

void Prefix_Enable(void);
uint8 Prefix_GetState(void);
void Prefix_Disable(void);

void Prefix_SetPending(void);
void Prefix_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Prefix ISR. */
#define Prefix_INTC_VECTOR            ((reg32 *) Prefix__INTC_VECT)

/* Address of the Prefix ISR priority. */
#define Prefix_INTC_PRIOR             ((reg8 *) Prefix__INTC_PRIOR_REG)

/* Priority of the Prefix interrupt. */
#define Prefix_INTC_PRIOR_NUMBER      Prefix__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Prefix interrupt. */
#define Prefix_INTC_SET_EN            ((reg32 *) Prefix__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Prefix interrupt. */
#define Prefix_INTC_CLR_EN            ((reg32 *) Prefix__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Prefix interrupt state to pending. */
#define Prefix_INTC_SET_PD            ((reg32 *) Prefix__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Prefix interrupt. */
#define Prefix_INTC_CLR_PD            ((reg32 *) Prefix__INTC_CLR_PD_REG)


#endif /* CY_ISR_Prefix_H */


/* [] END OF FILE */
