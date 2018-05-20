/*******************************************************************************
* File Name: HighVoltage.h  
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

#if !defined(CY_PINS_HighVoltage_H) /* Pins HighVoltage_H */
#define CY_PINS_HighVoltage_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HighVoltage_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HighVoltage__PORT == 15 && ((HighVoltage__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HighVoltage_Write(uint8 value);
void    HighVoltage_SetDriveMode(uint8 mode);
uint8   HighVoltage_ReadDataReg(void);
uint8   HighVoltage_Read(void);
void    HighVoltage_SetInterruptMode(uint16 position, uint16 mode);
uint8   HighVoltage_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HighVoltage_SetDriveMode() function.
     *  @{
     */
        #define HighVoltage_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HighVoltage_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HighVoltage_DM_RES_UP          PIN_DM_RES_UP
        #define HighVoltage_DM_RES_DWN         PIN_DM_RES_DWN
        #define HighVoltage_DM_OD_LO           PIN_DM_OD_LO
        #define HighVoltage_DM_OD_HI           PIN_DM_OD_HI
        #define HighVoltage_DM_STRONG          PIN_DM_STRONG
        #define HighVoltage_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HighVoltage_MASK               HighVoltage__MASK
#define HighVoltage_SHIFT              HighVoltage__SHIFT
#define HighVoltage_WIDTH              1u

/* Interrupt constants */
#if defined(HighVoltage__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HighVoltage_SetInterruptMode() function.
     *  @{
     */
        #define HighVoltage_INTR_NONE      (uint16)(0x0000u)
        #define HighVoltage_INTR_RISING    (uint16)(0x0001u)
        #define HighVoltage_INTR_FALLING   (uint16)(0x0002u)
        #define HighVoltage_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HighVoltage_INTR_MASK      (0x01u) 
#endif /* (HighVoltage__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HighVoltage_PS                     (* (reg8 *) HighVoltage__PS)
/* Data Register */
#define HighVoltage_DR                     (* (reg8 *) HighVoltage__DR)
/* Port Number */
#define HighVoltage_PRT_NUM                (* (reg8 *) HighVoltage__PRT) 
/* Connect to Analog Globals */                                                  
#define HighVoltage_AG                     (* (reg8 *) HighVoltage__AG)                       
/* Analog MUX bux enable */
#define HighVoltage_AMUX                   (* (reg8 *) HighVoltage__AMUX) 
/* Bidirectional Enable */                                                        
#define HighVoltage_BIE                    (* (reg8 *) HighVoltage__BIE)
/* Bit-mask for Aliased Register Access */
#define HighVoltage_BIT_MASK               (* (reg8 *) HighVoltage__BIT_MASK)
/* Bypass Enable */
#define HighVoltage_BYP                    (* (reg8 *) HighVoltage__BYP)
/* Port wide control signals */                                                   
#define HighVoltage_CTL                    (* (reg8 *) HighVoltage__CTL)
/* Drive Modes */
#define HighVoltage_DM0                    (* (reg8 *) HighVoltage__DM0) 
#define HighVoltage_DM1                    (* (reg8 *) HighVoltage__DM1)
#define HighVoltage_DM2                    (* (reg8 *) HighVoltage__DM2) 
/* Input Buffer Disable Override */
#define HighVoltage_INP_DIS                (* (reg8 *) HighVoltage__INP_DIS)
/* LCD Common or Segment Drive */
#define HighVoltage_LCD_COM_SEG            (* (reg8 *) HighVoltage__LCD_COM_SEG)
/* Enable Segment LCD */
#define HighVoltage_LCD_EN                 (* (reg8 *) HighVoltage__LCD_EN)
/* Slew Rate Control */
#define HighVoltage_SLW                    (* (reg8 *) HighVoltage__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HighVoltage_PRTDSI__CAPS_SEL       (* (reg8 *) HighVoltage__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HighVoltage_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HighVoltage__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HighVoltage_PRTDSI__OE_SEL0        (* (reg8 *) HighVoltage__PRTDSI__OE_SEL0) 
#define HighVoltage_PRTDSI__OE_SEL1        (* (reg8 *) HighVoltage__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HighVoltage_PRTDSI__OUT_SEL0       (* (reg8 *) HighVoltage__PRTDSI__OUT_SEL0) 
#define HighVoltage_PRTDSI__OUT_SEL1       (* (reg8 *) HighVoltage__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HighVoltage_PRTDSI__SYNC_OUT       (* (reg8 *) HighVoltage__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HighVoltage__SIO_CFG)
    #define HighVoltage_SIO_HYST_EN        (* (reg8 *) HighVoltage__SIO_HYST_EN)
    #define HighVoltage_SIO_REG_HIFREQ     (* (reg8 *) HighVoltage__SIO_REG_HIFREQ)
    #define HighVoltage_SIO_CFG            (* (reg8 *) HighVoltage__SIO_CFG)
    #define HighVoltage_SIO_DIFF           (* (reg8 *) HighVoltage__SIO_DIFF)
#endif /* (HighVoltage__SIO_CFG) */

/* Interrupt Registers */
#if defined(HighVoltage__INTSTAT)
    #define HighVoltage_INTSTAT            (* (reg8 *) HighVoltage__INTSTAT)
    #define HighVoltage_SNAP               (* (reg8 *) HighVoltage__SNAP)
    
	#define HighVoltage_0_INTTYPE_REG 		(* (reg8 *) HighVoltage__0__INTTYPE)
#endif /* (HighVoltage__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HighVoltage_H */


/* [] END OF FILE */
