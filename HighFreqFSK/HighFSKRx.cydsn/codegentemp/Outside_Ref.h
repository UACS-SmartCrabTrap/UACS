/*******************************************************************************
* File Name: Outside_Ref.h  
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

#if !defined(CY_PINS_Outside_Ref_H) /* Pins Outside_Ref_H */
#define CY_PINS_Outside_Ref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Outside_Ref_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Outside_Ref__PORT == 15 && ((Outside_Ref__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Outside_Ref_Write(uint8 value);
void    Outside_Ref_SetDriveMode(uint8 mode);
uint8   Outside_Ref_ReadDataReg(void);
uint8   Outside_Ref_Read(void);
void    Outside_Ref_SetInterruptMode(uint16 position, uint16 mode);
uint8   Outside_Ref_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Outside_Ref_SetDriveMode() function.
     *  @{
     */
        #define Outside_Ref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Outside_Ref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Outside_Ref_DM_RES_UP          PIN_DM_RES_UP
        #define Outside_Ref_DM_RES_DWN         PIN_DM_RES_DWN
        #define Outside_Ref_DM_OD_LO           PIN_DM_OD_LO
        #define Outside_Ref_DM_OD_HI           PIN_DM_OD_HI
        #define Outside_Ref_DM_STRONG          PIN_DM_STRONG
        #define Outside_Ref_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Outside_Ref_MASK               Outside_Ref__MASK
#define Outside_Ref_SHIFT              Outside_Ref__SHIFT
#define Outside_Ref_WIDTH              1u

/* Interrupt constants */
#if defined(Outside_Ref__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Outside_Ref_SetInterruptMode() function.
     *  @{
     */
        #define Outside_Ref_INTR_NONE      (uint16)(0x0000u)
        #define Outside_Ref_INTR_RISING    (uint16)(0x0001u)
        #define Outside_Ref_INTR_FALLING   (uint16)(0x0002u)
        #define Outside_Ref_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Outside_Ref_INTR_MASK      (0x01u) 
#endif /* (Outside_Ref__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Outside_Ref_PS                     (* (reg8 *) Outside_Ref__PS)
/* Data Register */
#define Outside_Ref_DR                     (* (reg8 *) Outside_Ref__DR)
/* Port Number */
#define Outside_Ref_PRT_NUM                (* (reg8 *) Outside_Ref__PRT) 
/* Connect to Analog Globals */                                                  
#define Outside_Ref_AG                     (* (reg8 *) Outside_Ref__AG)                       
/* Analog MUX bux enable */
#define Outside_Ref_AMUX                   (* (reg8 *) Outside_Ref__AMUX) 
/* Bidirectional Enable */                                                        
#define Outside_Ref_BIE                    (* (reg8 *) Outside_Ref__BIE)
/* Bit-mask for Aliased Register Access */
#define Outside_Ref_BIT_MASK               (* (reg8 *) Outside_Ref__BIT_MASK)
/* Bypass Enable */
#define Outside_Ref_BYP                    (* (reg8 *) Outside_Ref__BYP)
/* Port wide control signals */                                                   
#define Outside_Ref_CTL                    (* (reg8 *) Outside_Ref__CTL)
/* Drive Modes */
#define Outside_Ref_DM0                    (* (reg8 *) Outside_Ref__DM0) 
#define Outside_Ref_DM1                    (* (reg8 *) Outside_Ref__DM1)
#define Outside_Ref_DM2                    (* (reg8 *) Outside_Ref__DM2) 
/* Input Buffer Disable Override */
#define Outside_Ref_INP_DIS                (* (reg8 *) Outside_Ref__INP_DIS)
/* LCD Common or Segment Drive */
#define Outside_Ref_LCD_COM_SEG            (* (reg8 *) Outside_Ref__LCD_COM_SEG)
/* Enable Segment LCD */
#define Outside_Ref_LCD_EN                 (* (reg8 *) Outside_Ref__LCD_EN)
/* Slew Rate Control */
#define Outside_Ref_SLW                    (* (reg8 *) Outside_Ref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Outside_Ref_PRTDSI__CAPS_SEL       (* (reg8 *) Outside_Ref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Outside_Ref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Outside_Ref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Outside_Ref_PRTDSI__OE_SEL0        (* (reg8 *) Outside_Ref__PRTDSI__OE_SEL0) 
#define Outside_Ref_PRTDSI__OE_SEL1        (* (reg8 *) Outside_Ref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Outside_Ref_PRTDSI__OUT_SEL0       (* (reg8 *) Outside_Ref__PRTDSI__OUT_SEL0) 
#define Outside_Ref_PRTDSI__OUT_SEL1       (* (reg8 *) Outside_Ref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Outside_Ref_PRTDSI__SYNC_OUT       (* (reg8 *) Outside_Ref__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Outside_Ref__SIO_CFG)
    #define Outside_Ref_SIO_HYST_EN        (* (reg8 *) Outside_Ref__SIO_HYST_EN)
    #define Outside_Ref_SIO_REG_HIFREQ     (* (reg8 *) Outside_Ref__SIO_REG_HIFREQ)
    #define Outside_Ref_SIO_CFG            (* (reg8 *) Outside_Ref__SIO_CFG)
    #define Outside_Ref_SIO_DIFF           (* (reg8 *) Outside_Ref__SIO_DIFF)
#endif /* (Outside_Ref__SIO_CFG) */

/* Interrupt Registers */
#if defined(Outside_Ref__INTSTAT)
    #define Outside_Ref_INTSTAT            (* (reg8 *) Outside_Ref__INTSTAT)
    #define Outside_Ref_SNAP               (* (reg8 *) Outside_Ref__SNAP)
    
	#define Outside_Ref_0_INTTYPE_REG 		(* (reg8 *) Outside_Ref__0__INTTYPE)
#endif /* (Outside_Ref__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Outside_Ref_H */


/* [] END OF FILE */
