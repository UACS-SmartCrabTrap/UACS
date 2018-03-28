/*******************************************************************************
* File Name: ShiftOut.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ShiftOut_H) /* Pins ShiftOut_H */
#define CY_PINS_ShiftOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ShiftOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ShiftOut__PORT == 15 && ((ShiftOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ShiftOut_Write(uint8 value);
void    ShiftOut_SetDriveMode(uint8 mode);
uint8   ShiftOut_ReadDataReg(void);
uint8   ShiftOut_Read(void);
void    ShiftOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   ShiftOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ShiftOut_SetDriveMode() function.
     *  @{
     */
        #define ShiftOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ShiftOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ShiftOut_DM_RES_UP          PIN_DM_RES_UP
        #define ShiftOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define ShiftOut_DM_OD_LO           PIN_DM_OD_LO
        #define ShiftOut_DM_OD_HI           PIN_DM_OD_HI
        #define ShiftOut_DM_STRONG          PIN_DM_STRONG
        #define ShiftOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ShiftOut_MASK               ShiftOut__MASK
#define ShiftOut_SHIFT              ShiftOut__SHIFT
#define ShiftOut_WIDTH              1u

/* Interrupt constants */
#if defined(ShiftOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ShiftOut_SetInterruptMode() function.
     *  @{
     */
        #define ShiftOut_INTR_NONE      (uint16)(0x0000u)
        #define ShiftOut_INTR_RISING    (uint16)(0x0001u)
        #define ShiftOut_INTR_FALLING   (uint16)(0x0002u)
        #define ShiftOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ShiftOut_INTR_MASK      (0x01u) 
#endif /* (ShiftOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ShiftOut_PS                     (* (reg8 *) ShiftOut__PS)
/* Data Register */
#define ShiftOut_DR                     (* (reg8 *) ShiftOut__DR)
/* Port Number */
#define ShiftOut_PRT_NUM                (* (reg8 *) ShiftOut__PRT) 
/* Connect to Analog Globals */                                                  
#define ShiftOut_AG                     (* (reg8 *) ShiftOut__AG)                       
/* Analog MUX bux enable */
#define ShiftOut_AMUX                   (* (reg8 *) ShiftOut__AMUX) 
/* Bidirectional Enable */                                                        
#define ShiftOut_BIE                    (* (reg8 *) ShiftOut__BIE)
/* Bit-mask for Aliased Register Access */
#define ShiftOut_BIT_MASK               (* (reg8 *) ShiftOut__BIT_MASK)
/* Bypass Enable */
#define ShiftOut_BYP                    (* (reg8 *) ShiftOut__BYP)
/* Port wide control signals */                                                   
#define ShiftOut_CTL                    (* (reg8 *) ShiftOut__CTL)
/* Drive Modes */
#define ShiftOut_DM0                    (* (reg8 *) ShiftOut__DM0) 
#define ShiftOut_DM1                    (* (reg8 *) ShiftOut__DM1)
#define ShiftOut_DM2                    (* (reg8 *) ShiftOut__DM2) 
/* Input Buffer Disable Override */
#define ShiftOut_INP_DIS                (* (reg8 *) ShiftOut__INP_DIS)
/* LCD Common or Segment Drive */
#define ShiftOut_LCD_COM_SEG            (* (reg8 *) ShiftOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define ShiftOut_LCD_EN                 (* (reg8 *) ShiftOut__LCD_EN)
/* Slew Rate Control */
#define ShiftOut_SLW                    (* (reg8 *) ShiftOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ShiftOut_PRTDSI__CAPS_SEL       (* (reg8 *) ShiftOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ShiftOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ShiftOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ShiftOut_PRTDSI__OE_SEL0        (* (reg8 *) ShiftOut__PRTDSI__OE_SEL0) 
#define ShiftOut_PRTDSI__OE_SEL1        (* (reg8 *) ShiftOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ShiftOut_PRTDSI__OUT_SEL0       (* (reg8 *) ShiftOut__PRTDSI__OUT_SEL0) 
#define ShiftOut_PRTDSI__OUT_SEL1       (* (reg8 *) ShiftOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ShiftOut_PRTDSI__SYNC_OUT       (* (reg8 *) ShiftOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ShiftOut__SIO_CFG)
    #define ShiftOut_SIO_HYST_EN        (* (reg8 *) ShiftOut__SIO_HYST_EN)
    #define ShiftOut_SIO_REG_HIFREQ     (* (reg8 *) ShiftOut__SIO_REG_HIFREQ)
    #define ShiftOut_SIO_CFG            (* (reg8 *) ShiftOut__SIO_CFG)
    #define ShiftOut_SIO_DIFF           (* (reg8 *) ShiftOut__SIO_DIFF)
#endif /* (ShiftOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(ShiftOut__INTSTAT)
    #define ShiftOut_INTSTAT            (* (reg8 *) ShiftOut__INTSTAT)
    #define ShiftOut_SNAP               (* (reg8 *) ShiftOut__SNAP)
    
	#define ShiftOut_0_INTTYPE_REG 		(* (reg8 *) ShiftOut__0__INTTYPE)
#endif /* (ShiftOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ShiftOut_H */


/* [] END OF FILE */
