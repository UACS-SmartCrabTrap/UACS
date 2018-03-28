/*******************************************************************************
* File Name: BPFIn.h  
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

#if !defined(CY_PINS_BPFIn_H) /* Pins BPFIn_H */
#define CY_PINS_BPFIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BPFIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BPFIn__PORT == 15 && ((BPFIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BPFIn_Write(uint8 value);
void    BPFIn_SetDriveMode(uint8 mode);
uint8   BPFIn_ReadDataReg(void);
uint8   BPFIn_Read(void);
void    BPFIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   BPFIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BPFIn_SetDriveMode() function.
     *  @{
     */
        #define BPFIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BPFIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BPFIn_DM_RES_UP          PIN_DM_RES_UP
        #define BPFIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define BPFIn_DM_OD_LO           PIN_DM_OD_LO
        #define BPFIn_DM_OD_HI           PIN_DM_OD_HI
        #define BPFIn_DM_STRONG          PIN_DM_STRONG
        #define BPFIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BPFIn_MASK               BPFIn__MASK
#define BPFIn_SHIFT              BPFIn__SHIFT
#define BPFIn_WIDTH              1u

/* Interrupt constants */
#if defined(BPFIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BPFIn_SetInterruptMode() function.
     *  @{
     */
        #define BPFIn_INTR_NONE      (uint16)(0x0000u)
        #define BPFIn_INTR_RISING    (uint16)(0x0001u)
        #define BPFIn_INTR_FALLING   (uint16)(0x0002u)
        #define BPFIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BPFIn_INTR_MASK      (0x01u) 
#endif /* (BPFIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BPFIn_PS                     (* (reg8 *) BPFIn__PS)
/* Data Register */
#define BPFIn_DR                     (* (reg8 *) BPFIn__DR)
/* Port Number */
#define BPFIn_PRT_NUM                (* (reg8 *) BPFIn__PRT) 
/* Connect to Analog Globals */                                                  
#define BPFIn_AG                     (* (reg8 *) BPFIn__AG)                       
/* Analog MUX bux enable */
#define BPFIn_AMUX                   (* (reg8 *) BPFIn__AMUX) 
/* Bidirectional Enable */                                                        
#define BPFIn_BIE                    (* (reg8 *) BPFIn__BIE)
/* Bit-mask for Aliased Register Access */
#define BPFIn_BIT_MASK               (* (reg8 *) BPFIn__BIT_MASK)
/* Bypass Enable */
#define BPFIn_BYP                    (* (reg8 *) BPFIn__BYP)
/* Port wide control signals */                                                   
#define BPFIn_CTL                    (* (reg8 *) BPFIn__CTL)
/* Drive Modes */
#define BPFIn_DM0                    (* (reg8 *) BPFIn__DM0) 
#define BPFIn_DM1                    (* (reg8 *) BPFIn__DM1)
#define BPFIn_DM2                    (* (reg8 *) BPFIn__DM2) 
/* Input Buffer Disable Override */
#define BPFIn_INP_DIS                (* (reg8 *) BPFIn__INP_DIS)
/* LCD Common or Segment Drive */
#define BPFIn_LCD_COM_SEG            (* (reg8 *) BPFIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define BPFIn_LCD_EN                 (* (reg8 *) BPFIn__LCD_EN)
/* Slew Rate Control */
#define BPFIn_SLW                    (* (reg8 *) BPFIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BPFIn_PRTDSI__CAPS_SEL       (* (reg8 *) BPFIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BPFIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BPFIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BPFIn_PRTDSI__OE_SEL0        (* (reg8 *) BPFIn__PRTDSI__OE_SEL0) 
#define BPFIn_PRTDSI__OE_SEL1        (* (reg8 *) BPFIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BPFIn_PRTDSI__OUT_SEL0       (* (reg8 *) BPFIn__PRTDSI__OUT_SEL0) 
#define BPFIn_PRTDSI__OUT_SEL1       (* (reg8 *) BPFIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BPFIn_PRTDSI__SYNC_OUT       (* (reg8 *) BPFIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BPFIn__SIO_CFG)
    #define BPFIn_SIO_HYST_EN        (* (reg8 *) BPFIn__SIO_HYST_EN)
    #define BPFIn_SIO_REG_HIFREQ     (* (reg8 *) BPFIn__SIO_REG_HIFREQ)
    #define BPFIn_SIO_CFG            (* (reg8 *) BPFIn__SIO_CFG)
    #define BPFIn_SIO_DIFF           (* (reg8 *) BPFIn__SIO_DIFF)
#endif /* (BPFIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(BPFIn__INTSTAT)
    #define BPFIn_INTSTAT            (* (reg8 *) BPFIn__INTSTAT)
    #define BPFIn_SNAP               (* (reg8 *) BPFIn__SNAP)
    
	#define BPFIn_0_INTTYPE_REG 		(* (reg8 *) BPFIn__0__INTTYPE)
#endif /* (BPFIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BPFIn_H */


/* [] END OF FILE */
