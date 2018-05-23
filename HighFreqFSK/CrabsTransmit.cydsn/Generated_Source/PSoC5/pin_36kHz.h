/*******************************************************************************
* File Name: pin_36kHz.h  
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

#if !defined(CY_PINS_pin_36kHz_H) /* Pins pin_36kHz_H */
#define CY_PINS_pin_36kHz_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_36kHz_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pin_36kHz__PORT == 15 && ((pin_36kHz__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pin_36kHz_Write(uint8 value);
void    pin_36kHz_SetDriveMode(uint8 mode);
uint8   pin_36kHz_ReadDataReg(void);
uint8   pin_36kHz_Read(void);
void    pin_36kHz_SetInterruptMode(uint16 position, uint16 mode);
uint8   pin_36kHz_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pin_36kHz_SetDriveMode() function.
     *  @{
     */
        #define pin_36kHz_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pin_36kHz_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pin_36kHz_DM_RES_UP          PIN_DM_RES_UP
        #define pin_36kHz_DM_RES_DWN         PIN_DM_RES_DWN
        #define pin_36kHz_DM_OD_LO           PIN_DM_OD_LO
        #define pin_36kHz_DM_OD_HI           PIN_DM_OD_HI
        #define pin_36kHz_DM_STRONG          PIN_DM_STRONG
        #define pin_36kHz_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pin_36kHz_MASK               pin_36kHz__MASK
#define pin_36kHz_SHIFT              pin_36kHz__SHIFT
#define pin_36kHz_WIDTH              1u

/* Interrupt constants */
#if defined(pin_36kHz__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pin_36kHz_SetInterruptMode() function.
     *  @{
     */
        #define pin_36kHz_INTR_NONE      (uint16)(0x0000u)
        #define pin_36kHz_INTR_RISING    (uint16)(0x0001u)
        #define pin_36kHz_INTR_FALLING   (uint16)(0x0002u)
        #define pin_36kHz_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pin_36kHz_INTR_MASK      (0x01u) 
#endif /* (pin_36kHz__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_36kHz_PS                     (* (reg8 *) pin_36kHz__PS)
/* Data Register */
#define pin_36kHz_DR                     (* (reg8 *) pin_36kHz__DR)
/* Port Number */
#define pin_36kHz_PRT_NUM                (* (reg8 *) pin_36kHz__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_36kHz_AG                     (* (reg8 *) pin_36kHz__AG)                       
/* Analog MUX bux enable */
#define pin_36kHz_AMUX                   (* (reg8 *) pin_36kHz__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_36kHz_BIE                    (* (reg8 *) pin_36kHz__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_36kHz_BIT_MASK               (* (reg8 *) pin_36kHz__BIT_MASK)
/* Bypass Enable */
#define pin_36kHz_BYP                    (* (reg8 *) pin_36kHz__BYP)
/* Port wide control signals */                                                   
#define pin_36kHz_CTL                    (* (reg8 *) pin_36kHz__CTL)
/* Drive Modes */
#define pin_36kHz_DM0                    (* (reg8 *) pin_36kHz__DM0) 
#define pin_36kHz_DM1                    (* (reg8 *) pin_36kHz__DM1)
#define pin_36kHz_DM2                    (* (reg8 *) pin_36kHz__DM2) 
/* Input Buffer Disable Override */
#define pin_36kHz_INP_DIS                (* (reg8 *) pin_36kHz__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_36kHz_LCD_COM_SEG            (* (reg8 *) pin_36kHz__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_36kHz_LCD_EN                 (* (reg8 *) pin_36kHz__LCD_EN)
/* Slew Rate Control */
#define pin_36kHz_SLW                    (* (reg8 *) pin_36kHz__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_36kHz_PRTDSI__CAPS_SEL       (* (reg8 *) pin_36kHz__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_36kHz_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_36kHz__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_36kHz_PRTDSI__OE_SEL0        (* (reg8 *) pin_36kHz__PRTDSI__OE_SEL0) 
#define pin_36kHz_PRTDSI__OE_SEL1        (* (reg8 *) pin_36kHz__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_36kHz_PRTDSI__OUT_SEL0       (* (reg8 *) pin_36kHz__PRTDSI__OUT_SEL0) 
#define pin_36kHz_PRTDSI__OUT_SEL1       (* (reg8 *) pin_36kHz__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_36kHz_PRTDSI__SYNC_OUT       (* (reg8 *) pin_36kHz__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pin_36kHz__SIO_CFG)
    #define pin_36kHz_SIO_HYST_EN        (* (reg8 *) pin_36kHz__SIO_HYST_EN)
    #define pin_36kHz_SIO_REG_HIFREQ     (* (reg8 *) pin_36kHz__SIO_REG_HIFREQ)
    #define pin_36kHz_SIO_CFG            (* (reg8 *) pin_36kHz__SIO_CFG)
    #define pin_36kHz_SIO_DIFF           (* (reg8 *) pin_36kHz__SIO_DIFF)
#endif /* (pin_36kHz__SIO_CFG) */

/* Interrupt Registers */
#if defined(pin_36kHz__INTSTAT)
    #define pin_36kHz_INTSTAT            (* (reg8 *) pin_36kHz__INTSTAT)
    #define pin_36kHz_SNAP               (* (reg8 *) pin_36kHz__SNAP)
    
	#define pin_36kHz_0_INTTYPE_REG 		(* (reg8 *) pin_36kHz__0__INTTYPE)
#endif /* (pin_36kHz__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pin_36kHz_H */


/* [] END OF FILE */
