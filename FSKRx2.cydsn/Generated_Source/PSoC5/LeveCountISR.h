/*******************************************************************************
* File Name: LeveCountISR.h
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
#if !defined(CY_ISR_LeveCountISR_H)
#define CY_ISR_LeveCountISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void LeveCountISR_Start(void);
void LeveCountISR_StartEx(cyisraddress address);
void LeveCountISR_Stop(void);

CY_ISR_PROTO(LeveCountISR_Interrupt);

void LeveCountISR_SetVector(cyisraddress address);
cyisraddress LeveCountISR_GetVector(void);

void LeveCountISR_SetPriority(uint8 priority);
uint8 LeveCountISR_GetPriority(void);

void LeveCountISR_Enable(void);
uint8 LeveCountISR_GetState(void);
void LeveCountISR_Disable(void);

void LeveCountISR_SetPending(void);
void LeveCountISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LeveCountISR ISR. */
#define LeveCountISR_INTC_VECTOR            ((reg32 *) LeveCountISR__INTC_VECT)

/* Address of the LeveCountISR ISR priority. */
#define LeveCountISR_INTC_PRIOR             ((reg8 *) LeveCountISR__INTC_PRIOR_REG)

/* Priority of the LeveCountISR interrupt. */
#define LeveCountISR_INTC_PRIOR_NUMBER      LeveCountISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LeveCountISR interrupt. */
#define LeveCountISR_INTC_SET_EN            ((reg32 *) LeveCountISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LeveCountISR interrupt. */
#define LeveCountISR_INTC_CLR_EN            ((reg32 *) LeveCountISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LeveCountISR interrupt state to pending. */
#define LeveCountISR_INTC_SET_PD            ((reg32 *) LeveCountISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LeveCountISR interrupt. */
#define LeveCountISR_INTC_CLR_PD            ((reg32 *) LeveCountISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_LeveCountISR_H */


/* [] END OF FILE */
