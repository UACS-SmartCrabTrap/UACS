/*******************************************************************************
* File Name: HighF_LevelCountClk.h
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

#if !defined(CY_CLOCK_HighF_LevelCountClk_H)
#define CY_CLOCK_HighF_LevelCountClk_H

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

void HighF_LevelCountClk_Start(void) ;
void HighF_LevelCountClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void HighF_LevelCountClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void HighF_LevelCountClk_StandbyPower(uint8 state) ;
void HighF_LevelCountClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 HighF_LevelCountClk_GetDividerRegister(void) ;
void HighF_LevelCountClk_SetModeRegister(uint8 modeBitMask) ;
void HighF_LevelCountClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 HighF_LevelCountClk_GetModeRegister(void) ;
void HighF_LevelCountClk_SetSourceRegister(uint8 clkSource) ;
uint8 HighF_LevelCountClk_GetSourceRegister(void) ;
#if defined(HighF_LevelCountClk__CFG3)
void HighF_LevelCountClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 HighF_LevelCountClk_GetPhaseRegister(void) ;
#endif /* defined(HighF_LevelCountClk__CFG3) */

#define HighF_LevelCountClk_Enable()                       HighF_LevelCountClk_Start()
#define HighF_LevelCountClk_Disable()                      HighF_LevelCountClk_Stop()
#define HighF_LevelCountClk_SetDivider(clkDivider)         HighF_LevelCountClk_SetDividerRegister(clkDivider, 1u)
#define HighF_LevelCountClk_SetDividerValue(clkDivider)    HighF_LevelCountClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define HighF_LevelCountClk_SetMode(clkMode)               HighF_LevelCountClk_SetModeRegister(clkMode)
#define HighF_LevelCountClk_SetSource(clkSource)           HighF_LevelCountClk_SetSourceRegister(clkSource)
#if defined(HighF_LevelCountClk__CFG3)
#define HighF_LevelCountClk_SetPhase(clkPhase)             HighF_LevelCountClk_SetPhaseRegister(clkPhase)
#define HighF_LevelCountClk_SetPhaseValue(clkPhase)        HighF_LevelCountClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(HighF_LevelCountClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define HighF_LevelCountClk_CLKEN              (* (reg8 *) HighF_LevelCountClk__PM_ACT_CFG)
#define HighF_LevelCountClk_CLKEN_PTR          ((reg8 *) HighF_LevelCountClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define HighF_LevelCountClk_CLKSTBY            (* (reg8 *) HighF_LevelCountClk__PM_STBY_CFG)
#define HighF_LevelCountClk_CLKSTBY_PTR        ((reg8 *) HighF_LevelCountClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define HighF_LevelCountClk_DIV_LSB            (* (reg8 *) HighF_LevelCountClk__CFG0)
#define HighF_LevelCountClk_DIV_LSB_PTR        ((reg8 *) HighF_LevelCountClk__CFG0)
#define HighF_LevelCountClk_DIV_PTR            ((reg16 *) HighF_LevelCountClk__CFG0)

/* Clock MSB divider configuration register. */
#define HighF_LevelCountClk_DIV_MSB            (* (reg8 *) HighF_LevelCountClk__CFG1)
#define HighF_LevelCountClk_DIV_MSB_PTR        ((reg8 *) HighF_LevelCountClk__CFG1)

/* Mode and source configuration register */
#define HighF_LevelCountClk_MOD_SRC            (* (reg8 *) HighF_LevelCountClk__CFG2)
#define HighF_LevelCountClk_MOD_SRC_PTR        ((reg8 *) HighF_LevelCountClk__CFG2)

#if defined(HighF_LevelCountClk__CFG3)
/* Analog clock phase configuration register */
#define HighF_LevelCountClk_PHASE              (* (reg8 *) HighF_LevelCountClk__CFG3)
#define HighF_LevelCountClk_PHASE_PTR          ((reg8 *) HighF_LevelCountClk__CFG3)
#endif /* defined(HighF_LevelCountClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define HighF_LevelCountClk_CLKEN_MASK         HighF_LevelCountClk__PM_ACT_MSK
#define HighF_LevelCountClk_CLKSTBY_MASK       HighF_LevelCountClk__PM_STBY_MSK

/* CFG2 field masks */
#define HighF_LevelCountClk_SRC_SEL_MSK        HighF_LevelCountClk__CFG2_SRC_SEL_MASK
#define HighF_LevelCountClk_MODE_MASK          (~(HighF_LevelCountClk_SRC_SEL_MSK))

#if defined(HighF_LevelCountClk__CFG3)
/* CFG3 phase mask */
#define HighF_LevelCountClk_PHASE_MASK         HighF_LevelCountClk__CFG3_PHASE_DLY_MASK
#endif /* defined(HighF_LevelCountClk__CFG3) */

#endif /* CY_CLOCK_HighF_LevelCountClk_H */


/* [] END OF FILE */
