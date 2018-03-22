/*******************************************************************************
* File Name: HighF_OneCLK.h
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

#if !defined(CY_CLOCK_HighF_OneCLK_H)
#define CY_CLOCK_HighF_OneCLK_H

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

void HighF_OneCLK_Start(void) ;
void HighF_OneCLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void HighF_OneCLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void HighF_OneCLK_StandbyPower(uint8 state) ;
void HighF_OneCLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 HighF_OneCLK_GetDividerRegister(void) ;
void HighF_OneCLK_SetModeRegister(uint8 modeBitMask) ;
void HighF_OneCLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 HighF_OneCLK_GetModeRegister(void) ;
void HighF_OneCLK_SetSourceRegister(uint8 clkSource) ;
uint8 HighF_OneCLK_GetSourceRegister(void) ;
#if defined(HighF_OneCLK__CFG3)
void HighF_OneCLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 HighF_OneCLK_GetPhaseRegister(void) ;
#endif /* defined(HighF_OneCLK__CFG3) */

#define HighF_OneCLK_Enable()                       HighF_OneCLK_Start()
#define HighF_OneCLK_Disable()                      HighF_OneCLK_Stop()
#define HighF_OneCLK_SetDivider(clkDivider)         HighF_OneCLK_SetDividerRegister(clkDivider, 1u)
#define HighF_OneCLK_SetDividerValue(clkDivider)    HighF_OneCLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define HighF_OneCLK_SetMode(clkMode)               HighF_OneCLK_SetModeRegister(clkMode)
#define HighF_OneCLK_SetSource(clkSource)           HighF_OneCLK_SetSourceRegister(clkSource)
#if defined(HighF_OneCLK__CFG3)
#define HighF_OneCLK_SetPhase(clkPhase)             HighF_OneCLK_SetPhaseRegister(clkPhase)
#define HighF_OneCLK_SetPhaseValue(clkPhase)        HighF_OneCLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(HighF_OneCLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define HighF_OneCLK_CLKEN              (* (reg8 *) HighF_OneCLK__PM_ACT_CFG)
#define HighF_OneCLK_CLKEN_PTR          ((reg8 *) HighF_OneCLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define HighF_OneCLK_CLKSTBY            (* (reg8 *) HighF_OneCLK__PM_STBY_CFG)
#define HighF_OneCLK_CLKSTBY_PTR        ((reg8 *) HighF_OneCLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define HighF_OneCLK_DIV_LSB            (* (reg8 *) HighF_OneCLK__CFG0)
#define HighF_OneCLK_DIV_LSB_PTR        ((reg8 *) HighF_OneCLK__CFG0)
#define HighF_OneCLK_DIV_PTR            ((reg16 *) HighF_OneCLK__CFG0)

/* Clock MSB divider configuration register. */
#define HighF_OneCLK_DIV_MSB            (* (reg8 *) HighF_OneCLK__CFG1)
#define HighF_OneCLK_DIV_MSB_PTR        ((reg8 *) HighF_OneCLK__CFG1)

/* Mode and source configuration register */
#define HighF_OneCLK_MOD_SRC            (* (reg8 *) HighF_OneCLK__CFG2)
#define HighF_OneCLK_MOD_SRC_PTR        ((reg8 *) HighF_OneCLK__CFG2)

#if defined(HighF_OneCLK__CFG3)
/* Analog clock phase configuration register */
#define HighF_OneCLK_PHASE              (* (reg8 *) HighF_OneCLK__CFG3)
#define HighF_OneCLK_PHASE_PTR          ((reg8 *) HighF_OneCLK__CFG3)
#endif /* defined(HighF_OneCLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define HighF_OneCLK_CLKEN_MASK         HighF_OneCLK__PM_ACT_MSK
#define HighF_OneCLK_CLKSTBY_MASK       HighF_OneCLK__PM_STBY_MSK

/* CFG2 field masks */
#define HighF_OneCLK_SRC_SEL_MSK        HighF_OneCLK__CFG2_SRC_SEL_MASK
#define HighF_OneCLK_MODE_MASK          (~(HighF_OneCLK_SRC_SEL_MSK))

#if defined(HighF_OneCLK__CFG3)
/* CFG3 phase mask */
#define HighF_OneCLK_PHASE_MASK         HighF_OneCLK__CFG3_PHASE_DLY_MASK
#endif /* defined(HighF_OneCLK__CFG3) */

#endif /* CY_CLOCK_HighF_OneCLK_H */


/* [] END OF FILE */
