/*******************************************************************************
* File Name: LevelCountClk.h
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

#if !defined(CY_CLOCK_LevelCountClk_H)
#define CY_CLOCK_LevelCountClk_H

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

void LevelCountClk_Start(void) ;
void LevelCountClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void LevelCountClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void LevelCountClk_StandbyPower(uint8 state) ;
void LevelCountClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 LevelCountClk_GetDividerRegister(void) ;
void LevelCountClk_SetModeRegister(uint8 modeBitMask) ;
void LevelCountClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 LevelCountClk_GetModeRegister(void) ;
void LevelCountClk_SetSourceRegister(uint8 clkSource) ;
uint8 LevelCountClk_GetSourceRegister(void) ;
#if defined(LevelCountClk__CFG3)
void LevelCountClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 LevelCountClk_GetPhaseRegister(void) ;
#endif /* defined(LevelCountClk__CFG3) */

#define LevelCountClk_Enable()                       LevelCountClk_Start()
#define LevelCountClk_Disable()                      LevelCountClk_Stop()
#define LevelCountClk_SetDivider(clkDivider)         LevelCountClk_SetDividerRegister(clkDivider, 1u)
#define LevelCountClk_SetDividerValue(clkDivider)    LevelCountClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define LevelCountClk_SetMode(clkMode)               LevelCountClk_SetModeRegister(clkMode)
#define LevelCountClk_SetSource(clkSource)           LevelCountClk_SetSourceRegister(clkSource)
#if defined(LevelCountClk__CFG3)
#define LevelCountClk_SetPhase(clkPhase)             LevelCountClk_SetPhaseRegister(clkPhase)
#define LevelCountClk_SetPhaseValue(clkPhase)        LevelCountClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(LevelCountClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define LevelCountClk_CLKEN              (* (reg8 *) LevelCountClk__PM_ACT_CFG)
#define LevelCountClk_CLKEN_PTR          ((reg8 *) LevelCountClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define LevelCountClk_CLKSTBY            (* (reg8 *) LevelCountClk__PM_STBY_CFG)
#define LevelCountClk_CLKSTBY_PTR        ((reg8 *) LevelCountClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define LevelCountClk_DIV_LSB            (* (reg8 *) LevelCountClk__CFG0)
#define LevelCountClk_DIV_LSB_PTR        ((reg8 *) LevelCountClk__CFG0)
#define LevelCountClk_DIV_PTR            ((reg16 *) LevelCountClk__CFG0)

/* Clock MSB divider configuration register. */
#define LevelCountClk_DIV_MSB            (* (reg8 *) LevelCountClk__CFG1)
#define LevelCountClk_DIV_MSB_PTR        ((reg8 *) LevelCountClk__CFG1)

/* Mode and source configuration register */
#define LevelCountClk_MOD_SRC            (* (reg8 *) LevelCountClk__CFG2)
#define LevelCountClk_MOD_SRC_PTR        ((reg8 *) LevelCountClk__CFG2)

#if defined(LevelCountClk__CFG3)
/* Analog clock phase configuration register */
#define LevelCountClk_PHASE              (* (reg8 *) LevelCountClk__CFG3)
#define LevelCountClk_PHASE_PTR          ((reg8 *) LevelCountClk__CFG3)
#endif /* defined(LevelCountClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define LevelCountClk_CLKEN_MASK         LevelCountClk__PM_ACT_MSK
#define LevelCountClk_CLKSTBY_MASK       LevelCountClk__PM_STBY_MSK

/* CFG2 field masks */
#define LevelCountClk_SRC_SEL_MSK        LevelCountClk__CFG2_SRC_SEL_MASK
#define LevelCountClk_MODE_MASK          (~(LevelCountClk_SRC_SEL_MSK))

#if defined(LevelCountClk__CFG3)
/* CFG3 phase mask */
#define LevelCountClk_PHASE_MASK         LevelCountClk__CFG3_PHASE_DLY_MASK
#endif /* defined(LevelCountClk__CFG3) */

#endif /* CY_CLOCK_LevelCountClk_H */


/* [] END OF FILE */
