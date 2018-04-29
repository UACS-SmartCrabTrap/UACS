/*******************************************************************************
* File Name: HighF_LevelCountISR.h
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
#if !defined(CY_ISR_HighF_LevelCountISR_H)
#define CY_ISR_HighF_LevelCountISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void HighF_LevelCountISR_Start(void);
void HighF_LevelCountISR_StartEx(cyisraddress address);
void HighF_LevelCountISR_Stop(void);

CY_ISR_PROTO(HighF_LevelCountISR_Interrupt);

void HighF_LevelCountISR_SetVector(cyisraddress address);
cyisraddress HighF_LevelCountISR_GetVector(void);

void HighF_LevelCountISR_SetPriority(uint8 priority);
uint8 HighF_LevelCountISR_GetPriority(void);

void HighF_LevelCountISR_Enable(void);
uint8 HighF_LevelCountISR_GetState(void);
void HighF_LevelCountISR_Disable(void);

void HighF_LevelCountISR_SetPending(void);
void HighF_LevelCountISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the HighF_LevelCountISR ISR. */
#define HighF_LevelCountISR_INTC_VECTOR            ((reg32 *) HighF_LevelCountISR__INTC_VECT)

/* Address of the HighF_LevelCountISR ISR priority. */
#define HighF_LevelCountISR_INTC_PRIOR             ((reg8 *) HighF_LevelCountISR__INTC_PRIOR_REG)

/* Priority of the HighF_LevelCountISR interrupt. */
#define HighF_LevelCountISR_INTC_PRIOR_NUMBER      HighF_LevelCountISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable HighF_LevelCountISR interrupt. */
#define HighF_LevelCountISR_INTC_SET_EN            ((reg32 *) HighF_LevelCountISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the HighF_LevelCountISR interrupt. */
#define HighF_LevelCountISR_INTC_CLR_EN            ((reg32 *) HighF_LevelCountISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the HighF_LevelCountISR interrupt state to pending. */
#define HighF_LevelCountISR_INTC_SET_PD            ((reg32 *) HighF_LevelCountISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the HighF_LevelCountISR interrupt. */
#define HighF_LevelCountISR_INTC_CLR_PD            ((reg32 *) HighF_LevelCountISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_HighF_LevelCountISR_H */


/* [] END OF FILE */
