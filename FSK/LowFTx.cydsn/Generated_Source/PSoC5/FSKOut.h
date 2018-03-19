/*******************************************************************************
* File Name: FSKOut.h  
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

#if !defined(CY_PINS_FSKOut_H) /* Pins FSKOut_H */
#define CY_PINS_FSKOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FSKOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FSKOut__PORT == 15 && ((FSKOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FSKOut_Write(uint8 value);
void    FSKOut_SetDriveMode(uint8 mode);
uint8   FSKOut_ReadDataReg(void);
uint8   FSKOut_Read(void);
void    FSKOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   FSKOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FSKOut_SetDriveMode() function.
     *  @{
     */
        #define FSKOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FSKOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FSKOut_DM_RES_UP          PIN_DM_RES_UP
        #define FSKOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define FSKOut_DM_OD_LO           PIN_DM_OD_LO
        #define FSKOut_DM_OD_HI           PIN_DM_OD_HI
        #define FSKOut_DM_STRONG          PIN_DM_STRONG
        #define FSKOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FSKOut_MASK               FSKOut__MASK
#define FSKOut_SHIFT              FSKOut__SHIFT
#define FSKOut_WIDTH              1u

/* Interrupt constants */
#if defined(FSKOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FSKOut_SetInterruptMode() function.
     *  @{
     */
        #define FSKOut_INTR_NONE      (uint16)(0x0000u)
        #define FSKOut_INTR_RISING    (uint16)(0x0001u)
        #define FSKOut_INTR_FALLING   (uint16)(0x0002u)
        #define FSKOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FSKOut_INTR_MASK      (0x01u) 
#endif /* (FSKOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FSKOut_PS                     (* (reg8 *) FSKOut__PS)
/* Data Register */
#define FSKOut_DR                     (* (reg8 *) FSKOut__DR)
/* Port Number */
#define FSKOut_PRT_NUM                (* (reg8 *) FSKOut__PRT) 
/* Connect to Analog Globals */                                                  
#define FSKOut_AG                     (* (reg8 *) FSKOut__AG)                       
/* Analog MUX bux enable */
#define FSKOut_AMUX                   (* (reg8 *) FSKOut__AMUX) 
/* Bidirectional Enable */                                                        
#define FSKOut_BIE                    (* (reg8 *) FSKOut__BIE)
/* Bit-mask for Aliased Register Access */
#define FSKOut_BIT_MASK               (* (reg8 *) FSKOut__BIT_MASK)
/* Bypass Enable */
#define FSKOut_BYP                    (* (reg8 *) FSKOut__BYP)
/* Port wide control signals */                                                   
#define FSKOut_CTL                    (* (reg8 *) FSKOut__CTL)
/* Drive Modes */
#define FSKOut_DM0                    (* (reg8 *) FSKOut__DM0) 
#define FSKOut_DM1                    (* (reg8 *) FSKOut__DM1)
#define FSKOut_DM2                    (* (reg8 *) FSKOut__DM2) 
/* Input Buffer Disable Override */
#define FSKOut_INP_DIS                (* (reg8 *) FSKOut__INP_DIS)
/* LCD Common or Segment Drive */
#define FSKOut_LCD_COM_SEG            (* (reg8 *) FSKOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define FSKOut_LCD_EN                 (* (reg8 *) FSKOut__LCD_EN)
/* Slew Rate Control */
#define FSKOut_SLW                    (* (reg8 *) FSKOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FSKOut_PRTDSI__CAPS_SEL       (* (reg8 *) FSKOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FSKOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FSKOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FSKOut_PRTDSI__OE_SEL0        (* (reg8 *) FSKOut__PRTDSI__OE_SEL0) 
#define FSKOut_PRTDSI__OE_SEL1        (* (reg8 *) FSKOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FSKOut_PRTDSI__OUT_SEL0       (* (reg8 *) FSKOut__PRTDSI__OUT_SEL0) 
#define FSKOut_PRTDSI__OUT_SEL1       (* (reg8 *) FSKOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FSKOut_PRTDSI__SYNC_OUT       (* (reg8 *) FSKOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FSKOut__SIO_CFG)
    #define FSKOut_SIO_HYST_EN        (* (reg8 *) FSKOut__SIO_HYST_EN)
    #define FSKOut_SIO_REG_HIFREQ     (* (reg8 *) FSKOut__SIO_REG_HIFREQ)
    #define FSKOut_SIO_CFG            (* (reg8 *) FSKOut__SIO_CFG)
    #define FSKOut_SIO_DIFF           (* (reg8 *) FSKOut__SIO_DIFF)
#endif /* (FSKOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(FSKOut__INTSTAT)
    #define FSKOut_INTSTAT            (* (reg8 *) FSKOut__INTSTAT)
    #define FSKOut_SNAP               (* (reg8 *) FSKOut__SNAP)
    
	#define FSKOut_0_INTTYPE_REG 		(* (reg8 *) FSKOut__0__INTTYPE)
#endif /* (FSKOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FSKOut_H */


/* [] END OF FILE */
