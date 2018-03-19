/*******************************************************************************
* File Name: muxSelect.h  
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

#if !defined(CY_PINS_muxSelect_H) /* Pins muxSelect_H */
#define CY_PINS_muxSelect_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "muxSelect_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 muxSelect__PORT == 15 && ((muxSelect__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    muxSelect_Write(uint8 value);
void    muxSelect_SetDriveMode(uint8 mode);
uint8   muxSelect_ReadDataReg(void);
uint8   muxSelect_Read(void);
void    muxSelect_SetInterruptMode(uint16 position, uint16 mode);
uint8   muxSelect_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the muxSelect_SetDriveMode() function.
     *  @{
     */
        #define muxSelect_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define muxSelect_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define muxSelect_DM_RES_UP          PIN_DM_RES_UP
        #define muxSelect_DM_RES_DWN         PIN_DM_RES_DWN
        #define muxSelect_DM_OD_LO           PIN_DM_OD_LO
        #define muxSelect_DM_OD_HI           PIN_DM_OD_HI
        #define muxSelect_DM_STRONG          PIN_DM_STRONG
        #define muxSelect_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define muxSelect_MASK               muxSelect__MASK
#define muxSelect_SHIFT              muxSelect__SHIFT
#define muxSelect_WIDTH              1u

/* Interrupt constants */
#if defined(muxSelect__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in muxSelect_SetInterruptMode() function.
     *  @{
     */
        #define muxSelect_INTR_NONE      (uint16)(0x0000u)
        #define muxSelect_INTR_RISING    (uint16)(0x0001u)
        #define muxSelect_INTR_FALLING   (uint16)(0x0002u)
        #define muxSelect_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define muxSelect_INTR_MASK      (0x01u) 
#endif /* (muxSelect__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define muxSelect_PS                     (* (reg8 *) muxSelect__PS)
/* Data Register */
#define muxSelect_DR                     (* (reg8 *) muxSelect__DR)
/* Port Number */
#define muxSelect_PRT_NUM                (* (reg8 *) muxSelect__PRT) 
/* Connect to Analog Globals */                                                  
#define muxSelect_AG                     (* (reg8 *) muxSelect__AG)                       
/* Analog MUX bux enable */
#define muxSelect_AMUX                   (* (reg8 *) muxSelect__AMUX) 
/* Bidirectional Enable */                                                        
#define muxSelect_BIE                    (* (reg8 *) muxSelect__BIE)
/* Bit-mask for Aliased Register Access */
#define muxSelect_BIT_MASK               (* (reg8 *) muxSelect__BIT_MASK)
/* Bypass Enable */
#define muxSelect_BYP                    (* (reg8 *) muxSelect__BYP)
/* Port wide control signals */                                                   
#define muxSelect_CTL                    (* (reg8 *) muxSelect__CTL)
/* Drive Modes */
#define muxSelect_DM0                    (* (reg8 *) muxSelect__DM0) 
#define muxSelect_DM1                    (* (reg8 *) muxSelect__DM1)
#define muxSelect_DM2                    (* (reg8 *) muxSelect__DM2) 
/* Input Buffer Disable Override */
#define muxSelect_INP_DIS                (* (reg8 *) muxSelect__INP_DIS)
/* LCD Common or Segment Drive */
#define muxSelect_LCD_COM_SEG            (* (reg8 *) muxSelect__LCD_COM_SEG)
/* Enable Segment LCD */
#define muxSelect_LCD_EN                 (* (reg8 *) muxSelect__LCD_EN)
/* Slew Rate Control */
#define muxSelect_SLW                    (* (reg8 *) muxSelect__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define muxSelect_PRTDSI__CAPS_SEL       (* (reg8 *) muxSelect__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define muxSelect_PRTDSI__DBL_SYNC_IN    (* (reg8 *) muxSelect__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define muxSelect_PRTDSI__OE_SEL0        (* (reg8 *) muxSelect__PRTDSI__OE_SEL0) 
#define muxSelect_PRTDSI__OE_SEL1        (* (reg8 *) muxSelect__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define muxSelect_PRTDSI__OUT_SEL0       (* (reg8 *) muxSelect__PRTDSI__OUT_SEL0) 
#define muxSelect_PRTDSI__OUT_SEL1       (* (reg8 *) muxSelect__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define muxSelect_PRTDSI__SYNC_OUT       (* (reg8 *) muxSelect__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(muxSelect__SIO_CFG)
    #define muxSelect_SIO_HYST_EN        (* (reg8 *) muxSelect__SIO_HYST_EN)
    #define muxSelect_SIO_REG_HIFREQ     (* (reg8 *) muxSelect__SIO_REG_HIFREQ)
    #define muxSelect_SIO_CFG            (* (reg8 *) muxSelect__SIO_CFG)
    #define muxSelect_SIO_DIFF           (* (reg8 *) muxSelect__SIO_DIFF)
#endif /* (muxSelect__SIO_CFG) */

/* Interrupt Registers */
#if defined(muxSelect__INTSTAT)
    #define muxSelect_INTSTAT            (* (reg8 *) muxSelect__INTSTAT)
    #define muxSelect_SNAP               (* (reg8 *) muxSelect__SNAP)
    
	#define muxSelect_0_INTTYPE_REG 		(* (reg8 *) muxSelect__0__INTTYPE)
#endif /* (muxSelect__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_muxSelect_H */


/* [] END OF FILE */
