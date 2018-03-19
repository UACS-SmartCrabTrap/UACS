/*******************************************************************************
* File Name: LowF_ZeroInt.h
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
#if !defined(CY_ISR_LowF_ZeroInt_H)
#define CY_ISR_LowF_ZeroInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void LowF_ZeroInt_Start(void);
void LowF_ZeroInt_StartEx(cyisraddress address);
void LowF_ZeroInt_Stop(void);

CY_ISR_PROTO(LowF_ZeroInt_Interrupt);

void LowF_ZeroInt_SetVector(cyisraddress address);
cyisraddress LowF_ZeroInt_GetVector(void);

void LowF_ZeroInt_SetPriority(uint8 priority);
uint8 LowF_ZeroInt_GetPriority(void);

void LowF_ZeroInt_Enable(void);
uint8 LowF_ZeroInt_GetState(void);
void LowF_ZeroInt_Disable(void);

void LowF_ZeroInt_SetPending(void);
void LowF_ZeroInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LowF_ZeroInt ISR. */
#define LowF_ZeroInt_INTC_VECTOR            ((reg32 *) LowF_ZeroInt__INTC_VECT)

/* Address of the LowF_ZeroInt ISR priority. */
#define LowF_ZeroInt_INTC_PRIOR             ((reg8 *) LowF_ZeroInt__INTC_PRIOR_REG)

/* Priority of the LowF_ZeroInt interrupt. */
#define LowF_ZeroInt_INTC_PRIOR_NUMBER      LowF_ZeroInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LowF_ZeroInt interrupt. */
#define LowF_ZeroInt_INTC_SET_EN            ((reg32 *) LowF_ZeroInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LowF_ZeroInt interrupt. */
#define LowF_ZeroInt_INTC_CLR_EN            ((reg32 *) LowF_ZeroInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LowF_ZeroInt interrupt state to pending. */
#define LowF_ZeroInt_INTC_SET_PD            ((reg32 *) LowF_ZeroInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LowF_ZeroInt interrupt. */
#define LowF_ZeroInt_INTC_CLR_PD            ((reg32 *) LowF_ZeroInt__INTC_CLR_PD_REG)


#endif /* CY_ISR_LowF_ZeroInt_H */


/* [] END OF FILE */
