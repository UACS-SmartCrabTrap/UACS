/*******************************************************************************
* File Name: LevelCountISR.h
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
#if !defined(CY_ISR_LevelCountISR_H)
#define CY_ISR_LevelCountISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void LevelCountISR_Start(void);
void LevelCountISR_StartEx(cyisraddress address);
void LevelCountISR_Stop(void);

CY_ISR_PROTO(LevelCountISR_Interrupt);

void LevelCountISR_SetVector(cyisraddress address);
cyisraddress LevelCountISR_GetVector(void);

void LevelCountISR_SetPriority(uint8 priority);
uint8 LevelCountISR_GetPriority(void);

void LevelCountISR_Enable(void);
uint8 LevelCountISR_GetState(void);
void LevelCountISR_Disable(void);

void LevelCountISR_SetPending(void);
void LevelCountISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LevelCountISR ISR. */
#define LevelCountISR_INTC_VECTOR            ((reg32 *) LevelCountISR__INTC_VECT)

/* Address of the LevelCountISR ISR priority. */
#define LevelCountISR_INTC_PRIOR             ((reg8 *) LevelCountISR__INTC_PRIOR_REG)

/* Priority of the LevelCountISR interrupt. */
#define LevelCountISR_INTC_PRIOR_NUMBER      LevelCountISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LevelCountISR interrupt. */
#define LevelCountISR_INTC_SET_EN            ((reg32 *) LevelCountISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LevelCountISR interrupt. */
#define LevelCountISR_INTC_CLR_EN            ((reg32 *) LevelCountISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LevelCountISR interrupt state to pending. */
#define LevelCountISR_INTC_SET_PD            ((reg32 *) LevelCountISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LevelCountISR interrupt. */
#define LevelCountISR_INTC_CLR_PD            ((reg32 *) LevelCountISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_LevelCountISR_H */


/* [] END OF FILE */
