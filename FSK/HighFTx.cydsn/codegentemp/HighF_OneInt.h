/*******************************************************************************
* File Name: HighF_OneInt.h
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
#if !defined(CY_ISR_HighF_OneInt_H)
#define CY_ISR_HighF_OneInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void HighF_OneInt_Start(void);
void HighF_OneInt_StartEx(cyisraddress address);
void HighF_OneInt_Stop(void);

CY_ISR_PROTO(HighF_OneInt_Interrupt);

void HighF_OneInt_SetVector(cyisraddress address);
cyisraddress HighF_OneInt_GetVector(void);

void HighF_OneInt_SetPriority(uint8 priority);
uint8 HighF_OneInt_GetPriority(void);

void HighF_OneInt_Enable(void);
uint8 HighF_OneInt_GetState(void);
void HighF_OneInt_Disable(void);

void HighF_OneInt_SetPending(void);
void HighF_OneInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the HighF_OneInt ISR. */
#define HighF_OneInt_INTC_VECTOR            ((reg32 *) HighF_OneInt__INTC_VECT)

/* Address of the HighF_OneInt ISR priority. */
#define HighF_OneInt_INTC_PRIOR             ((reg8 *) HighF_OneInt__INTC_PRIOR_REG)

/* Priority of the HighF_OneInt interrupt. */
#define HighF_OneInt_INTC_PRIOR_NUMBER      HighF_OneInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable HighF_OneInt interrupt. */
#define HighF_OneInt_INTC_SET_EN            ((reg32 *) HighF_OneInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the HighF_OneInt interrupt. */
#define HighF_OneInt_INTC_CLR_EN            ((reg32 *) HighF_OneInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the HighF_OneInt interrupt state to pending. */
#define HighF_OneInt_INTC_SET_PD            ((reg32 *) HighF_OneInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the HighF_OneInt interrupt. */
#define HighF_OneInt_INTC_CLR_PD            ((reg32 *) HighF_OneInt__INTC_CLR_PD_REG)


#endif /* CY_ISR_HighF_OneInt_H */


/* [] END OF FILE */
