/*******************************************************************************
* File Name: ZeroInt.h
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
#if !defined(CY_ISR_ZeroInt_H)
#define CY_ISR_ZeroInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ZeroInt_Start(void);
void ZeroInt_StartEx(cyisraddress address);
void ZeroInt_Stop(void);

CY_ISR_PROTO(ZeroInt_Interrupt);

void ZeroInt_SetVector(cyisraddress address);
cyisraddress ZeroInt_GetVector(void);

void ZeroInt_SetPriority(uint8 priority);
uint8 ZeroInt_GetPriority(void);

void ZeroInt_Enable(void);
uint8 ZeroInt_GetState(void);
void ZeroInt_Disable(void);

void ZeroInt_SetPending(void);
void ZeroInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ZeroInt ISR. */
#define ZeroInt_INTC_VECTOR            ((reg32 *) ZeroInt__INTC_VECT)

/* Address of the ZeroInt ISR priority. */
#define ZeroInt_INTC_PRIOR             ((reg8 *) ZeroInt__INTC_PRIOR_REG)

/* Priority of the ZeroInt interrupt. */
#define ZeroInt_INTC_PRIOR_NUMBER      ZeroInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ZeroInt interrupt. */
#define ZeroInt_INTC_SET_EN            ((reg32 *) ZeroInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ZeroInt interrupt. */
#define ZeroInt_INTC_CLR_EN            ((reg32 *) ZeroInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ZeroInt interrupt state to pending. */
#define ZeroInt_INTC_SET_PD            ((reg32 *) ZeroInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ZeroInt interrupt. */
#define ZeroInt_INTC_CLR_PD            ((reg32 *) ZeroInt__INTC_CLR_PD_REG)


#endif /* CY_ISR_ZeroInt_H */


/* [] END OF FILE */
