/*******************************************************************************
* File Name: LowFHigh.h
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

#if !defined(CY_CLOCK_LowFHigh_H)
#define CY_CLOCK_LowFHigh_H

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

void LowFHigh_Start(void) ;
void LowFHigh_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void LowFHigh_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void LowFHigh_StandbyPower(uint8 state) ;
void LowFHigh_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 LowFHigh_GetDividerRegister(void) ;
void LowFHigh_SetModeRegister(uint8 modeBitMask) ;
void LowFHigh_ClearModeRegister(uint8 modeBitMask) ;
uint8 LowFHigh_GetModeRegister(void) ;
void LowFHigh_SetSourceRegister(uint8 clkSource) ;
uint8 LowFHigh_GetSourceRegister(void) ;
#if defined(LowFHigh__CFG3)
void LowFHigh_SetPhaseRegister(uint8 clkPhase) ;
uint8 LowFHigh_GetPhaseRegister(void) ;
#endif /* defined(LowFHigh__CFG3) */

#define LowFHigh_Enable()                       LowFHigh_Start()
#define LowFHigh_Disable()                      LowFHigh_Stop()
#define LowFHigh_SetDivider(clkDivider)         LowFHigh_SetDividerRegister(clkDivider, 1u)
#define LowFHigh_SetDividerValue(clkDivider)    LowFHigh_SetDividerRegister((clkDivider) - 1u, 1u)
#define LowFHigh_SetMode(clkMode)               LowFHigh_SetModeRegister(clkMode)
#define LowFHigh_SetSource(clkSource)           LowFHigh_SetSourceRegister(clkSource)
#if defined(LowFHigh__CFG3)
#define LowFHigh_SetPhase(clkPhase)             LowFHigh_SetPhaseRegister(clkPhase)
#define LowFHigh_SetPhaseValue(clkPhase)        LowFHigh_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(LowFHigh__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define LowFHigh_CLKEN              (* (reg8 *) LowFHigh__PM_ACT_CFG)
#define LowFHigh_CLKEN_PTR          ((reg8 *) LowFHigh__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define LowFHigh_CLKSTBY            (* (reg8 *) LowFHigh__PM_STBY_CFG)
#define LowFHigh_CLKSTBY_PTR        ((reg8 *) LowFHigh__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define LowFHigh_DIV_LSB            (* (reg8 *) LowFHigh__CFG0)
#define LowFHigh_DIV_LSB_PTR        ((reg8 *) LowFHigh__CFG0)
#define LowFHigh_DIV_PTR            ((reg16 *) LowFHigh__CFG0)

/* Clock MSB divider configuration register. */
#define LowFHigh_DIV_MSB            (* (reg8 *) LowFHigh__CFG1)
#define LowFHigh_DIV_MSB_PTR        ((reg8 *) LowFHigh__CFG1)

/* Mode and source configuration register */
#define LowFHigh_MOD_SRC            (* (reg8 *) LowFHigh__CFG2)
#define LowFHigh_MOD_SRC_PTR        ((reg8 *) LowFHigh__CFG2)

#if defined(LowFHigh__CFG3)
/* Analog clock phase configuration register */
#define LowFHigh_PHASE              (* (reg8 *) LowFHigh__CFG3)
#define LowFHigh_PHASE_PTR          ((reg8 *) LowFHigh__CFG3)
#endif /* defined(LowFHigh__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define LowFHigh_CLKEN_MASK         LowFHigh__PM_ACT_MSK
#define LowFHigh_CLKSTBY_MASK       LowFHigh__PM_STBY_MSK

/* CFG2 field masks */
#define LowFHigh_SRC_SEL_MSK        LowFHigh__CFG2_SRC_SEL_MASK
#define LowFHigh_MODE_MASK          (~(LowFHigh_SRC_SEL_MSK))

#if defined(LowFHigh__CFG3)
/* CFG3 phase mask */
#define LowFHigh_PHASE_MASK         LowFHigh__CFG3_PHASE_DLY_MASK
#endif /* defined(LowFHigh__CFG3) */

#endif /* CY_CLOCK_LowFHigh_H */


/* [] END OF FILE */
