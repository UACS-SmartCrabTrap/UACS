/*******************************************************************************
* File Name: CountOut.h  
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

#if !defined(CY_PINS_CountOut_H) /* Pins CountOut_H */
#define CY_PINS_CountOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CountOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CountOut__PORT == 15 && ((CountOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CountOut_Write(uint8 value);
void    CountOut_SetDriveMode(uint8 mode);
uint8   CountOut_ReadDataReg(void);
uint8   CountOut_Read(void);
void    CountOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   CountOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CountOut_SetDriveMode() function.
     *  @{
     */
        #define CountOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CountOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CountOut_DM_RES_UP          PIN_DM_RES_UP
        #define CountOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define CountOut_DM_OD_LO           PIN_DM_OD_LO
        #define CountOut_DM_OD_HI           PIN_DM_OD_HI
        #define CountOut_DM_STRONG          PIN_DM_STRONG
        #define CountOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CountOut_MASK               CountOut__MASK
#define CountOut_SHIFT              CountOut__SHIFT
#define CountOut_WIDTH              1u

/* Interrupt constants */
#if defined(CountOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CountOut_SetInterruptMode() function.
     *  @{
     */
        #define CountOut_INTR_NONE      (uint16)(0x0000u)
        #define CountOut_INTR_RISING    (uint16)(0x0001u)
        #define CountOut_INTR_FALLING   (uint16)(0x0002u)
        #define CountOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CountOut_INTR_MASK      (0x01u) 
#endif /* (CountOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CountOut_PS                     (* (reg8 *) CountOut__PS)
/* Data Register */
#define CountOut_DR                     (* (reg8 *) CountOut__DR)
/* Port Number */
#define CountOut_PRT_NUM                (* (reg8 *) CountOut__PRT) 
/* Connect to Analog Globals */                                                  
#define CountOut_AG                     (* (reg8 *) CountOut__AG)                       
/* Analog MUX bux enable */
#define CountOut_AMUX                   (* (reg8 *) CountOut__AMUX) 
/* Bidirectional Enable */                                                        
#define CountOut_BIE                    (* (reg8 *) CountOut__BIE)
/* Bit-mask for Aliased Register Access */
#define CountOut_BIT_MASK               (* (reg8 *) CountOut__BIT_MASK)
/* Bypass Enable */
#define CountOut_BYP                    (* (reg8 *) CountOut__BYP)
/* Port wide control signals */                                                   
#define CountOut_CTL                    (* (reg8 *) CountOut__CTL)
/* Drive Modes */
#define CountOut_DM0                    (* (reg8 *) CountOut__DM0) 
#define CountOut_DM1                    (* (reg8 *) CountOut__DM1)
#define CountOut_DM2                    (* (reg8 *) CountOut__DM2) 
/* Input Buffer Disable Override */
#define CountOut_INP_DIS                (* (reg8 *) CountOut__INP_DIS)
/* LCD Common or Segment Drive */
#define CountOut_LCD_COM_SEG            (* (reg8 *) CountOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define CountOut_LCD_EN                 (* (reg8 *) CountOut__LCD_EN)
/* Slew Rate Control */
#define CountOut_SLW                    (* (reg8 *) CountOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CountOut_PRTDSI__CAPS_SEL       (* (reg8 *) CountOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CountOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CountOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CountOut_PRTDSI__OE_SEL0        (* (reg8 *) CountOut__PRTDSI__OE_SEL0) 
#define CountOut_PRTDSI__OE_SEL1        (* (reg8 *) CountOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CountOut_PRTDSI__OUT_SEL0       (* (reg8 *) CountOut__PRTDSI__OUT_SEL0) 
#define CountOut_PRTDSI__OUT_SEL1       (* (reg8 *) CountOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CountOut_PRTDSI__SYNC_OUT       (* (reg8 *) CountOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CountOut__SIO_CFG)
    #define CountOut_SIO_HYST_EN        (* (reg8 *) CountOut__SIO_HYST_EN)
    #define CountOut_SIO_REG_HIFREQ     (* (reg8 *) CountOut__SIO_REG_HIFREQ)
    #define CountOut_SIO_CFG            (* (reg8 *) CountOut__SIO_CFG)
    #define CountOut_SIO_DIFF           (* (reg8 *) CountOut__SIO_DIFF)
#endif /* (CountOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(CountOut__INTSTAT)
    #define CountOut_INTSTAT            (* (reg8 *) CountOut__INTSTAT)
    #define CountOut_SNAP               (* (reg8 *) CountOut__SNAP)
    
	#define CountOut_0_INTTYPE_REG 		(* (reg8 *) CountOut__0__INTTYPE)
#endif /* (CountOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CountOut_H */


/* [] END OF FILE */
