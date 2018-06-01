/*******************************************************************************
* File Name: sleepToggle.h  
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

#if !defined(CY_PINS_sleepToggle_H) /* Pins sleepToggle_H */
#define CY_PINS_sleepToggle_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sleepToggle_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sleepToggle__PORT == 15 && ((sleepToggle__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sleepToggle_Write(uint8 value);
void    sleepToggle_SetDriveMode(uint8 mode);
uint8   sleepToggle_ReadDataReg(void);
uint8   sleepToggle_Read(void);
void    sleepToggle_SetInterruptMode(uint16 position, uint16 mode);
uint8   sleepToggle_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sleepToggle_SetDriveMode() function.
     *  @{
     */
        #define sleepToggle_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sleepToggle_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sleepToggle_DM_RES_UP          PIN_DM_RES_UP
        #define sleepToggle_DM_RES_DWN         PIN_DM_RES_DWN
        #define sleepToggle_DM_OD_LO           PIN_DM_OD_LO
        #define sleepToggle_DM_OD_HI           PIN_DM_OD_HI
        #define sleepToggle_DM_STRONG          PIN_DM_STRONG
        #define sleepToggle_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sleepToggle_MASK               sleepToggle__MASK
#define sleepToggle_SHIFT              sleepToggle__SHIFT
#define sleepToggle_WIDTH              1u

/* Interrupt constants */
#if defined(sleepToggle__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sleepToggle_SetInterruptMode() function.
     *  @{
     */
        #define sleepToggle_INTR_NONE      (uint16)(0x0000u)
        #define sleepToggle_INTR_RISING    (uint16)(0x0001u)
        #define sleepToggle_INTR_FALLING   (uint16)(0x0002u)
        #define sleepToggle_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sleepToggle_INTR_MASK      (0x01u) 
#endif /* (sleepToggle__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sleepToggle_PS                     (* (reg8 *) sleepToggle__PS)
/* Data Register */
#define sleepToggle_DR                     (* (reg8 *) sleepToggle__DR)
/* Port Number */
#define sleepToggle_PRT_NUM                (* (reg8 *) sleepToggle__PRT) 
/* Connect to Analog Globals */                                                  
#define sleepToggle_AG                     (* (reg8 *) sleepToggle__AG)                       
/* Analog MUX bux enable */
#define sleepToggle_AMUX                   (* (reg8 *) sleepToggle__AMUX) 
/* Bidirectional Enable */                                                        
#define sleepToggle_BIE                    (* (reg8 *) sleepToggle__BIE)
/* Bit-mask for Aliased Register Access */
#define sleepToggle_BIT_MASK               (* (reg8 *) sleepToggle__BIT_MASK)
/* Bypass Enable */
#define sleepToggle_BYP                    (* (reg8 *) sleepToggle__BYP)
/* Port wide control signals */                                                   
#define sleepToggle_CTL                    (* (reg8 *) sleepToggle__CTL)
/* Drive Modes */
#define sleepToggle_DM0                    (* (reg8 *) sleepToggle__DM0) 
#define sleepToggle_DM1                    (* (reg8 *) sleepToggle__DM1)
#define sleepToggle_DM2                    (* (reg8 *) sleepToggle__DM2) 
/* Input Buffer Disable Override */
#define sleepToggle_INP_DIS                (* (reg8 *) sleepToggle__INP_DIS)
/* LCD Common or Segment Drive */
#define sleepToggle_LCD_COM_SEG            (* (reg8 *) sleepToggle__LCD_COM_SEG)
/* Enable Segment LCD */
#define sleepToggle_LCD_EN                 (* (reg8 *) sleepToggle__LCD_EN)
/* Slew Rate Control */
#define sleepToggle_SLW                    (* (reg8 *) sleepToggle__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sleepToggle_PRTDSI__CAPS_SEL       (* (reg8 *) sleepToggle__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sleepToggle_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sleepToggle__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sleepToggle_PRTDSI__OE_SEL0        (* (reg8 *) sleepToggle__PRTDSI__OE_SEL0) 
#define sleepToggle_PRTDSI__OE_SEL1        (* (reg8 *) sleepToggle__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sleepToggle_PRTDSI__OUT_SEL0       (* (reg8 *) sleepToggle__PRTDSI__OUT_SEL0) 
#define sleepToggle_PRTDSI__OUT_SEL1       (* (reg8 *) sleepToggle__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sleepToggle_PRTDSI__SYNC_OUT       (* (reg8 *) sleepToggle__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sleepToggle__SIO_CFG)
    #define sleepToggle_SIO_HYST_EN        (* (reg8 *) sleepToggle__SIO_HYST_EN)
    #define sleepToggle_SIO_REG_HIFREQ     (* (reg8 *) sleepToggle__SIO_REG_HIFREQ)
    #define sleepToggle_SIO_CFG            (* (reg8 *) sleepToggle__SIO_CFG)
    #define sleepToggle_SIO_DIFF           (* (reg8 *) sleepToggle__SIO_DIFF)
#endif /* (sleepToggle__SIO_CFG) */

/* Interrupt Registers */
#if defined(sleepToggle__INTSTAT)
    #define sleepToggle_INTSTAT            (* (reg8 *) sleepToggle__INTSTAT)
    #define sleepToggle_SNAP               (* (reg8 *) sleepToggle__SNAP)
    
	#define sleepToggle_0_INTTYPE_REG 		(* (reg8 *) sleepToggle__0__INTTYPE)
#endif /* (sleepToggle__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sleepToggle_H */


/* [] END OF FILE */
