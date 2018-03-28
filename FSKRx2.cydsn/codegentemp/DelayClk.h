/*******************************************************************************
* File Name: DelayClk.h
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

#if !defined(CY_CLOCK_DelayClk_H)
#define CY_CLOCK_DelayClk_H

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

void DelayClk_Start(void) ;
void DelayClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void DelayClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void DelayClk_StandbyPower(uint8 state) ;
void DelayClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 DelayClk_GetDividerRegister(void) ;
void DelayClk_SetModeRegister(uint8 modeBitMask) ;
void DelayClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 DelayClk_GetModeRegister(void) ;
void DelayClk_SetSourceRegister(uint8 clkSource) ;
uint8 DelayClk_GetSourceRegister(void) ;
#if defined(DelayClk__CFG3)
void DelayClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 DelayClk_GetPhaseRegister(void) ;
#endif /* defined(DelayClk__CFG3) */

#define DelayClk_Enable()                       DelayClk_Start()
#define DelayClk_Disable()                      DelayClk_Stop()
#define DelayClk_SetDivider(clkDivider)         DelayClk_SetDividerRegister(clkDivider, 1u)
#define DelayClk_SetDividerValue(clkDivider)    DelayClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define DelayClk_SetMode(clkMode)               DelayClk_SetModeRegister(clkMode)
#define DelayClk_SetSource(clkSource)           DelayClk_SetSourceRegister(clkSource)
#if defined(DelayClk__CFG3)
#define DelayClk_SetPhase(clkPhase)             DelayClk_SetPhaseRegister(clkPhase)
#define DelayClk_SetPhaseValue(clkPhase)        DelayClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(DelayClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define DelayClk_CLKEN              (* (reg8 *) DelayClk__PM_ACT_CFG)
#define DelayClk_CLKEN_PTR          ((reg8 *) DelayClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define DelayClk_CLKSTBY            (* (reg8 *) DelayClk__PM_STBY_CFG)
#define DelayClk_CLKSTBY_PTR        ((reg8 *) DelayClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define DelayClk_DIV_LSB            (* (reg8 *) DelayClk__CFG0)
#define DelayClk_DIV_LSB_PTR        ((reg8 *) DelayClk__CFG0)
#define DelayClk_DIV_PTR            ((reg16 *) DelayClk__CFG0)

/* Clock MSB divider configuration register. */
#define DelayClk_DIV_MSB            (* (reg8 *) DelayClk__CFG1)
#define DelayClk_DIV_MSB_PTR        ((reg8 *) DelayClk__CFG1)

/* Mode and source configuration register */
#define DelayClk_MOD_SRC            (* (reg8 *) DelayClk__CFG2)
#define DelayClk_MOD_SRC_PTR        ((reg8 *) DelayClk__CFG2)

#if defined(DelayClk__CFG3)
/* Analog clock phase configuration register */
#define DelayClk_PHASE              (* (reg8 *) DelayClk__CFG3)
#define DelayClk_PHASE_PTR          ((reg8 *) DelayClk__CFG3)
#endif /* defined(DelayClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define DelayClk_CLKEN_MASK         DelayClk__PM_ACT_MSK
#define DelayClk_CLKSTBY_MASK       DelayClk__PM_STBY_MSK

/* CFG2 field masks */
#define DelayClk_SRC_SEL_MSK        DelayClk__CFG2_SRC_SEL_MASK
#define DelayClk_MODE_MASK          (~(DelayClk_SRC_SEL_MSK))

#if defined(DelayClk__CFG3)
/* CFG3 phase mask */
#define DelayClk_PHASE_MASK         DelayClk__CFG3_PHASE_DLY_MASK
#endif /* defined(DelayClk__CFG3) */

#endif /* CY_CLOCK_DelayClk_H */


/* [] END OF FILE */
