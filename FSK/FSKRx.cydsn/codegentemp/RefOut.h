/*******************************************************************************
* File Name: RefOut.h  
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

#if !defined(CY_PINS_RefOut_H) /* Pins RefOut_H */
#define CY_PINS_RefOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RefOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RefOut__PORT == 15 && ((RefOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RefOut_Write(uint8 value);
void    RefOut_SetDriveMode(uint8 mode);
uint8   RefOut_ReadDataReg(void);
uint8   RefOut_Read(void);
void    RefOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   RefOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RefOut_SetDriveMode() function.
     *  @{
     */
        #define RefOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RefOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RefOut_DM_RES_UP          PIN_DM_RES_UP
        #define RefOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define RefOut_DM_OD_LO           PIN_DM_OD_LO
        #define RefOut_DM_OD_HI           PIN_DM_OD_HI
        #define RefOut_DM_STRONG          PIN_DM_STRONG
        #define RefOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RefOut_MASK               RefOut__MASK
#define RefOut_SHIFT              RefOut__SHIFT
#define RefOut_WIDTH              1u

/* Interrupt constants */
#if defined(RefOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RefOut_SetInterruptMode() function.
     *  @{
     */
        #define RefOut_INTR_NONE      (uint16)(0x0000u)
        #define RefOut_INTR_RISING    (uint16)(0x0001u)
        #define RefOut_INTR_FALLING   (uint16)(0x0002u)
        #define RefOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RefOut_INTR_MASK      (0x01u) 
#endif /* (RefOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RefOut_PS                     (* (reg8 *) RefOut__PS)
/* Data Register */
#define RefOut_DR                     (* (reg8 *) RefOut__DR)
/* Port Number */
#define RefOut_PRT_NUM                (* (reg8 *) RefOut__PRT) 
/* Connect to Analog Globals */                                                  
#define RefOut_AG                     (* (reg8 *) RefOut__AG)                       
/* Analog MUX bux enable */
#define RefOut_AMUX                   (* (reg8 *) RefOut__AMUX) 
/* Bidirectional Enable */                                                        
#define RefOut_BIE                    (* (reg8 *) RefOut__BIE)
/* Bit-mask for Aliased Register Access */
#define RefOut_BIT_MASK               (* (reg8 *) RefOut__BIT_MASK)
/* Bypass Enable */
#define RefOut_BYP                    (* (reg8 *) RefOut__BYP)
/* Port wide control signals */                                                   
#define RefOut_CTL                    (* (reg8 *) RefOut__CTL)
/* Drive Modes */
#define RefOut_DM0                    (* (reg8 *) RefOut__DM0) 
#define RefOut_DM1                    (* (reg8 *) RefOut__DM1)
#define RefOut_DM2                    (* (reg8 *) RefOut__DM2) 
/* Input Buffer Disable Override */
#define RefOut_INP_DIS                (* (reg8 *) RefOut__INP_DIS)
/* LCD Common or Segment Drive */
#define RefOut_LCD_COM_SEG            (* (reg8 *) RefOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define RefOut_LCD_EN                 (* (reg8 *) RefOut__LCD_EN)
/* Slew Rate Control */
#define RefOut_SLW                    (* (reg8 *) RefOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RefOut_PRTDSI__CAPS_SEL       (* (reg8 *) RefOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RefOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RefOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RefOut_PRTDSI__OE_SEL0        (* (reg8 *) RefOut__PRTDSI__OE_SEL0) 
#define RefOut_PRTDSI__OE_SEL1        (* (reg8 *) RefOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RefOut_PRTDSI__OUT_SEL0       (* (reg8 *) RefOut__PRTDSI__OUT_SEL0) 
#define RefOut_PRTDSI__OUT_SEL1       (* (reg8 *) RefOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RefOut_PRTDSI__SYNC_OUT       (* (reg8 *) RefOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RefOut__SIO_CFG)
    #define RefOut_SIO_HYST_EN        (* (reg8 *) RefOut__SIO_HYST_EN)
    #define RefOut_SIO_REG_HIFREQ     (* (reg8 *) RefOut__SIO_REG_HIFREQ)
    #define RefOut_SIO_CFG            (* (reg8 *) RefOut__SIO_CFG)
    #define RefOut_SIO_DIFF           (* (reg8 *) RefOut__SIO_DIFF)
#endif /* (RefOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(RefOut__INTSTAT)
    #define RefOut_INTSTAT            (* (reg8 *) RefOut__INTSTAT)
    #define RefOut_SNAP               (* (reg8 *) RefOut__SNAP)
    
	#define RefOut_0_INTTYPE_REG 		(* (reg8 *) RefOut__0__INTTYPE)
#endif /* (RefOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RefOut_H */


/* [] END OF FILE */
