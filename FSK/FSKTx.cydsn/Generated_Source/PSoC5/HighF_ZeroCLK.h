/*******************************************************************************
* File Name: HighF_ZeroCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_HighF_ZeroCLK_H)
#define CY_CLOCK_HighF_ZeroCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void HighF_ZeroCLK_Start(void) ;
void HighF_ZeroCLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void HighF_ZeroCLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void HighF_ZeroCLK_StandbyPower(uint8 state) ;
void HighF_ZeroCLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 HighF_ZeroCLK_GetDividerRegister(void) ;
void HighF_ZeroCLK_SetModeRegister(uint8 modeBitMask) ;
void HighF_ZeroCLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 HighF_ZeroCLK_GetModeRegister(void) ;
void HighF_ZeroCLK_SetSourceRegister(uint8 clkSource) ;
uint8 HighF_ZeroCLK_GetSourceRegister(void) ;
#if defined(HighF_ZeroCLK__CFG3)
void HighF_ZeroCLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 HighF_ZeroCLK_GetPhaseRegister(void) ;
#endif /* defined(HighF_ZeroCLK__CFG3) */

#define HighF_ZeroCLK_Enable()                       HighF_ZeroCLK_Start()
#define HighF_ZeroCLK_Disable()                      HighF_ZeroCLK_Stop()
#define HighF_ZeroCLK_SetDivider(clkDivider)         HighF_ZeroCLK_SetDividerRegister(clkDivider, 1u)
#define HighF_ZeroCLK_SetDividerValue(clkDivider)    HighF_ZeroCLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define HighF_ZeroCLK_SetMode(clkMode)               HighF_ZeroCLK_SetModeRegister(clkMode)
#define HighF_ZeroCLK_SetSource(clkSource)           HighF_ZeroCLK_SetSourceRegister(clkSource)
#if defined(HighF_ZeroCLK__CFG3)
#define HighF_ZeroCLK_SetPhase(clkPhase)             HighF_ZeroCLK_SetPhaseRegister(clkPhase)
#define HighF_ZeroCLK_SetPhaseValue(clkPhase)        HighF_ZeroCLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(HighF_ZeroCLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define HighF_ZeroCLK_CLKEN              (* (reg8 *) HighF_ZeroCLK__PM_ACT_CFG)
#define HighF_ZeroCLK_CLKEN_PTR          ((reg8 *) HighF_ZeroCLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define HighF_ZeroCLK_CLKSTBY            (* (reg8 *) HighF_ZeroCLK__PM_STBY_CFG)
#define HighF_ZeroCLK_CLKSTBY_PTR        ((reg8 *) HighF_ZeroCLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define HighF_ZeroCLK_DIV_LSB            (* (reg8 *) HighF_ZeroCLK__CFG0)
#define HighF_ZeroCLK_DIV_LSB_PTR        ((reg8 *) HighF_ZeroCLK__CFG0)
#define HighF_ZeroCLK_DIV_PTR            ((reg16 *) HighF_ZeroCLK__CFG0)

/* Clock MSB divider configuration register. */
#define HighF_ZeroCLK_DIV_MSB            (* (reg8 *) HighF_ZeroCLK__CFG1)
#define HighF_ZeroCLK_DIV_MSB_PTR        ((reg8 *) HighF_ZeroCLK__CFG1)

/* Mode and source configuration register */
#define HighF_ZeroCLK_MOD_SRC            (* (reg8 *) HighF_ZeroCLK__CFG2)
#define HighF_ZeroCLK_MOD_SRC_PTR        ((reg8 *) HighF_ZeroCLK__CFG2)

#if defined(HighF_ZeroCLK__CFG3)
/* Analog clock phase configuration register */
#define HighF_ZeroCLK_PHASE              (* (reg8 *) HighF_ZeroCLK__CFG3)
#define HighF_ZeroCLK_PHASE_PTR          ((reg8 *) HighF_ZeroCLK__CFG3)
#endif /* defined(HighF_ZeroCLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define HighF_ZeroCLK_CLKEN_MASK         HighF_ZeroCLK__PM_ACT_MSK
#define HighF_ZeroCLK_CLKSTBY_MASK       HighF_ZeroCLK__PM_STBY_MSK

/* CFG2 field masks */
#define HighF_ZeroCLK_SRC_SEL_MSK        HighF_ZeroCLK__CFG2_SRC_SEL_MASK
#define HighF_ZeroCLK_MODE_MASK          (~(HighF_ZeroCLK_SRC_SEL_MSK))

#if defined(HighF_ZeroCLK__CFG3)
/* CFG3 phase mask */
#define HighF_ZeroCLK_PHASE_MASK         HighF_ZeroCLK__CFG3_PHASE_DLY_MASK
#endif /* defined(HighF_ZeroCLK__CFG3) */

#endif /* CY_CLOCK_HighF_ZeroCLK_H */


/* [] END OF FILE */
