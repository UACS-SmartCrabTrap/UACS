/*******************************************************************************
* File Name: Bit_Timer_Clk.h
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

#if !defined(CY_CLOCK_Bit_Timer_Clk_H)
#define CY_CLOCK_Bit_Timer_Clk_H

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

void Bit_Timer_Clk_Start(void) ;
void Bit_Timer_Clk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Bit_Timer_Clk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Bit_Timer_Clk_StandbyPower(uint8 state) ;
void Bit_Timer_Clk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Bit_Timer_Clk_GetDividerRegister(void) ;
void Bit_Timer_Clk_SetModeRegister(uint8 modeBitMask) ;
void Bit_Timer_Clk_ClearModeRegister(uint8 modeBitMask) ;
uint8 Bit_Timer_Clk_GetModeRegister(void) ;
void Bit_Timer_Clk_SetSourceRegister(uint8 clkSource) ;
uint8 Bit_Timer_Clk_GetSourceRegister(void) ;
#if defined(Bit_Timer_Clk__CFG3)
void Bit_Timer_Clk_SetPhaseRegister(uint8 clkPhase) ;
uint8 Bit_Timer_Clk_GetPhaseRegister(void) ;
#endif /* defined(Bit_Timer_Clk__CFG3) */

#define Bit_Timer_Clk_Enable()                       Bit_Timer_Clk_Start()
#define Bit_Timer_Clk_Disable()                      Bit_Timer_Clk_Stop()
#define Bit_Timer_Clk_SetDivider(clkDivider)         Bit_Timer_Clk_SetDividerRegister(clkDivider, 1u)
#define Bit_Timer_Clk_SetDividerValue(clkDivider)    Bit_Timer_Clk_SetDividerRegister((clkDivider) - 1u, 1u)
#define Bit_Timer_Clk_SetMode(clkMode)               Bit_Timer_Clk_SetModeRegister(clkMode)
#define Bit_Timer_Clk_SetSource(clkSource)           Bit_Timer_Clk_SetSourceRegister(clkSource)
#if defined(Bit_Timer_Clk__CFG3)
#define Bit_Timer_Clk_SetPhase(clkPhase)             Bit_Timer_Clk_SetPhaseRegister(clkPhase)
#define Bit_Timer_Clk_SetPhaseValue(clkPhase)        Bit_Timer_Clk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Bit_Timer_Clk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Bit_Timer_Clk_CLKEN              (* (reg8 *) Bit_Timer_Clk__PM_ACT_CFG)
#define Bit_Timer_Clk_CLKEN_PTR          ((reg8 *) Bit_Timer_Clk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Bit_Timer_Clk_CLKSTBY            (* (reg8 *) Bit_Timer_Clk__PM_STBY_CFG)
#define Bit_Timer_Clk_CLKSTBY_PTR        ((reg8 *) Bit_Timer_Clk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Bit_Timer_Clk_DIV_LSB            (* (reg8 *) Bit_Timer_Clk__CFG0)
#define Bit_Timer_Clk_DIV_LSB_PTR        ((reg8 *) Bit_Timer_Clk__CFG0)
#define Bit_Timer_Clk_DIV_PTR            ((reg16 *) Bit_Timer_Clk__CFG0)

/* Clock MSB divider configuration register. */
#define Bit_Timer_Clk_DIV_MSB            (* (reg8 *) Bit_Timer_Clk__CFG1)
#define Bit_Timer_Clk_DIV_MSB_PTR        ((reg8 *) Bit_Timer_Clk__CFG1)

/* Mode and source configuration register */
#define Bit_Timer_Clk_MOD_SRC            (* (reg8 *) Bit_Timer_Clk__CFG2)
#define Bit_Timer_Clk_MOD_SRC_PTR        ((reg8 *) Bit_Timer_Clk__CFG2)

#if defined(Bit_Timer_Clk__CFG3)
/* Analog clock phase configuration register */
#define Bit_Timer_Clk_PHASE              (* (reg8 *) Bit_Timer_Clk__CFG3)
#define Bit_Timer_Clk_PHASE_PTR          ((reg8 *) Bit_Timer_Clk__CFG3)
#endif /* defined(Bit_Timer_Clk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Bit_Timer_Clk_CLKEN_MASK         Bit_Timer_Clk__PM_ACT_MSK
#define Bit_Timer_Clk_CLKSTBY_MASK       Bit_Timer_Clk__PM_STBY_MSK

/* CFG2 field masks */
#define Bit_Timer_Clk_SRC_SEL_MSK        Bit_Timer_Clk__CFG2_SRC_SEL_MASK
#define Bit_Timer_Clk_MODE_MASK          (~(Bit_Timer_Clk_SRC_SEL_MSK))

#if defined(Bit_Timer_Clk__CFG3)
/* CFG3 phase mask */
#define Bit_Timer_Clk_PHASE_MASK         Bit_Timer_Clk__CFG3_PHASE_DLY_MASK
#endif /* defined(Bit_Timer_Clk__CFG3) */

#endif /* CY_CLOCK_Bit_Timer_Clk_H */


/* [] END OF FILE */
