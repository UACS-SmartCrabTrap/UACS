/*******************************************************************************
* File Name: shift2.h
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

#if !defined(CY_CLOCK_shift2_H)
#define CY_CLOCK_shift2_H

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

void shift2_Start(void) ;
void shift2_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void shift2_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void shift2_StandbyPower(uint8 state) ;
void shift2_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 shift2_GetDividerRegister(void) ;
void shift2_SetModeRegister(uint8 modeBitMask) ;
void shift2_ClearModeRegister(uint8 modeBitMask) ;
uint8 shift2_GetModeRegister(void) ;
void shift2_SetSourceRegister(uint8 clkSource) ;
uint8 shift2_GetSourceRegister(void) ;
#if defined(shift2__CFG3)
void shift2_SetPhaseRegister(uint8 clkPhase) ;
uint8 shift2_GetPhaseRegister(void) ;
#endif /* defined(shift2__CFG3) */

#define shift2_Enable()                       shift2_Start()
#define shift2_Disable()                      shift2_Stop()
#define shift2_SetDivider(clkDivider)         shift2_SetDividerRegister(clkDivider, 1u)
#define shift2_SetDividerValue(clkDivider)    shift2_SetDividerRegister((clkDivider) - 1u, 1u)
#define shift2_SetMode(clkMode)               shift2_SetModeRegister(clkMode)
#define shift2_SetSource(clkSource)           shift2_SetSourceRegister(clkSource)
#if defined(shift2__CFG3)
#define shift2_SetPhase(clkPhase)             shift2_SetPhaseRegister(clkPhase)
#define shift2_SetPhaseValue(clkPhase)        shift2_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(shift2__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define shift2_CLKEN              (* (reg8 *) shift2__PM_ACT_CFG)
#define shift2_CLKEN_PTR          ((reg8 *) shift2__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define shift2_CLKSTBY            (* (reg8 *) shift2__PM_STBY_CFG)
#define shift2_CLKSTBY_PTR        ((reg8 *) shift2__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define shift2_DIV_LSB            (* (reg8 *) shift2__CFG0)
#define shift2_DIV_LSB_PTR        ((reg8 *) shift2__CFG0)
#define shift2_DIV_PTR            ((reg16 *) shift2__CFG0)

/* Clock MSB divider configuration register. */
#define shift2_DIV_MSB            (* (reg8 *) shift2__CFG1)
#define shift2_DIV_MSB_PTR        ((reg8 *) shift2__CFG1)

/* Mode and source configuration register */
#define shift2_MOD_SRC            (* (reg8 *) shift2__CFG2)
#define shift2_MOD_SRC_PTR        ((reg8 *) shift2__CFG2)

#if defined(shift2__CFG3)
/* Analog clock phase configuration register */
#define shift2_PHASE              (* (reg8 *) shift2__CFG3)
#define shift2_PHASE_PTR          ((reg8 *) shift2__CFG3)
#endif /* defined(shift2__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define shift2_CLKEN_MASK         shift2__PM_ACT_MSK
#define shift2_CLKSTBY_MASK       shift2__PM_STBY_MSK

/* CFG2 field masks */
#define shift2_SRC_SEL_MSK        shift2__CFG2_SRC_SEL_MASK
#define shift2_MODE_MASK          (~(shift2_SRC_SEL_MSK))

#if defined(shift2__CFG3)
/* CFG3 phase mask */
#define shift2_PHASE_MASK         shift2__CFG3_PHASE_DLY_MASK
#endif /* defined(shift2__CFG3) */

#endif /* CY_CLOCK_shift2_H */


/* [] END OF FILE */
