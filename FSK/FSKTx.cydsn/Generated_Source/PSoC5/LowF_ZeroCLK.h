/*******************************************************************************
* File Name: LowF_ZeroCLK.h
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

#if !defined(CY_CLOCK_LowF_ZeroCLK_H)
#define CY_CLOCK_LowF_ZeroCLK_H

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

void LowF_ZeroCLK_Start(void) ;
void LowF_ZeroCLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void LowF_ZeroCLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void LowF_ZeroCLK_StandbyPower(uint8 state) ;
void LowF_ZeroCLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 LowF_ZeroCLK_GetDividerRegister(void) ;
void LowF_ZeroCLK_SetModeRegister(uint8 modeBitMask) ;
void LowF_ZeroCLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 LowF_ZeroCLK_GetModeRegister(void) ;
void LowF_ZeroCLK_SetSourceRegister(uint8 clkSource) ;
uint8 LowF_ZeroCLK_GetSourceRegister(void) ;
#if defined(LowF_ZeroCLK__CFG3)
void LowF_ZeroCLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 LowF_ZeroCLK_GetPhaseRegister(void) ;
#endif /* defined(LowF_ZeroCLK__CFG3) */

#define LowF_ZeroCLK_Enable()                       LowF_ZeroCLK_Start()
#define LowF_ZeroCLK_Disable()                      LowF_ZeroCLK_Stop()
#define LowF_ZeroCLK_SetDivider(clkDivider)         LowF_ZeroCLK_SetDividerRegister(clkDivider, 1u)
#define LowF_ZeroCLK_SetDividerValue(clkDivider)    LowF_ZeroCLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define LowF_ZeroCLK_SetMode(clkMode)               LowF_ZeroCLK_SetModeRegister(clkMode)
#define LowF_ZeroCLK_SetSource(clkSource)           LowF_ZeroCLK_SetSourceRegister(clkSource)
#if defined(LowF_ZeroCLK__CFG3)
#define LowF_ZeroCLK_SetPhase(clkPhase)             LowF_ZeroCLK_SetPhaseRegister(clkPhase)
#define LowF_ZeroCLK_SetPhaseValue(clkPhase)        LowF_ZeroCLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(LowF_ZeroCLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define LowF_ZeroCLK_CLKEN              (* (reg8 *) LowF_ZeroCLK__PM_ACT_CFG)
#define LowF_ZeroCLK_CLKEN_PTR          ((reg8 *) LowF_ZeroCLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define LowF_ZeroCLK_CLKSTBY            (* (reg8 *) LowF_ZeroCLK__PM_STBY_CFG)
#define LowF_ZeroCLK_CLKSTBY_PTR        ((reg8 *) LowF_ZeroCLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define LowF_ZeroCLK_DIV_LSB            (* (reg8 *) LowF_ZeroCLK__CFG0)
#define LowF_ZeroCLK_DIV_LSB_PTR        ((reg8 *) LowF_ZeroCLK__CFG0)
#define LowF_ZeroCLK_DIV_PTR            ((reg16 *) LowF_ZeroCLK__CFG0)

/* Clock MSB divider configuration register. */
#define LowF_ZeroCLK_DIV_MSB            (* (reg8 *) LowF_ZeroCLK__CFG1)
#define LowF_ZeroCLK_DIV_MSB_PTR        ((reg8 *) LowF_ZeroCLK__CFG1)

/* Mode and source configuration register */
#define LowF_ZeroCLK_MOD_SRC            (* (reg8 *) LowF_ZeroCLK__CFG2)
#define LowF_ZeroCLK_MOD_SRC_PTR        ((reg8 *) LowF_ZeroCLK__CFG2)

#if defined(LowF_ZeroCLK__CFG3)
/* Analog clock phase configuration register */
#define LowF_ZeroCLK_PHASE              (* (reg8 *) LowF_ZeroCLK__CFG3)
#define LowF_ZeroCLK_PHASE_PTR          ((reg8 *) LowF_ZeroCLK__CFG3)
#endif /* defined(LowF_ZeroCLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define LowF_ZeroCLK_CLKEN_MASK         LowF_ZeroCLK__PM_ACT_MSK
#define LowF_ZeroCLK_CLKSTBY_MASK       LowF_ZeroCLK__PM_STBY_MSK

/* CFG2 field masks */
#define LowF_ZeroCLK_SRC_SEL_MSK        LowF_ZeroCLK__CFG2_SRC_SEL_MASK
#define LowF_ZeroCLK_MODE_MASK          (~(LowF_ZeroCLK_SRC_SEL_MSK))

#if defined(LowF_ZeroCLK__CFG3)
/* CFG3 phase mask */
#define LowF_ZeroCLK_PHASE_MASK         LowF_ZeroCLK__CFG3_PHASE_DLY_MASK
#endif /* defined(LowF_ZeroCLK__CFG3) */

#endif /* CY_CLOCK_LowF_ZeroCLK_H */


/* [] END OF FILE */
