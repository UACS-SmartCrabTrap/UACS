/*******************************************************************************
* File Name: Parity.h  
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

#if !defined(CY_PINS_Parity_H) /* Pins Parity_H */
#define CY_PINS_Parity_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Parity_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Parity__PORT == 15 && ((Parity__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Parity_Write(uint8 value);
void    Parity_SetDriveMode(uint8 mode);
uint8   Parity_ReadDataReg(void);
uint8   Parity_Read(void);
void    Parity_SetInterruptMode(uint16 position, uint16 mode);
uint8   Parity_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Parity_SetDriveMode() function.
     *  @{
     */
        #define Parity_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Parity_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Parity_DM_RES_UP          PIN_DM_RES_UP
        #define Parity_DM_RES_DWN         PIN_DM_RES_DWN
        #define Parity_DM_OD_LO           PIN_DM_OD_LO
        #define Parity_DM_OD_HI           PIN_DM_OD_HI
        #define Parity_DM_STRONG          PIN_DM_STRONG
        #define Parity_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Parity_MASK               Parity__MASK
#define Parity_SHIFT              Parity__SHIFT
#define Parity_WIDTH              1u

/* Interrupt constants */
#if defined(Parity__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Parity_SetInterruptMode() function.
     *  @{
     */
        #define Parity_INTR_NONE      (uint16)(0x0000u)
        #define Parity_INTR_RISING    (uint16)(0x0001u)
        #define Parity_INTR_FALLING   (uint16)(0x0002u)
        #define Parity_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Parity_INTR_MASK      (0x01u) 
#endif /* (Parity__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Parity_PS                     (* (reg8 *) Parity__PS)
/* Data Register */
#define Parity_DR                     (* (reg8 *) Parity__DR)
/* Port Number */
#define Parity_PRT_NUM                (* (reg8 *) Parity__PRT) 
/* Connect to Analog Globals */                                                  
#define Parity_AG                     (* (reg8 *) Parity__AG)                       
/* Analog MUX bux enable */
#define Parity_AMUX                   (* (reg8 *) Parity__AMUX) 
/* Bidirectional Enable */                                                        
#define Parity_BIE                    (* (reg8 *) Parity__BIE)
/* Bit-mask for Aliased Register Access */
#define Parity_BIT_MASK               (* (reg8 *) Parity__BIT_MASK)
/* Bypass Enable */
#define Parity_BYP                    (* (reg8 *) Parity__BYP)
/* Port wide control signals */                                                   
#define Parity_CTL                    (* (reg8 *) Parity__CTL)
/* Drive Modes */
#define Parity_DM0                    (* (reg8 *) Parity__DM0) 
#define Parity_DM1                    (* (reg8 *) Parity__DM1)
#define Parity_DM2                    (* (reg8 *) Parity__DM2) 
/* Input Buffer Disable Override */
#define Parity_INP_DIS                (* (reg8 *) Parity__INP_DIS)
/* LCD Common or Segment Drive */
#define Parity_LCD_COM_SEG            (* (reg8 *) Parity__LCD_COM_SEG)
/* Enable Segment LCD */
#define Parity_LCD_EN                 (* (reg8 *) Parity__LCD_EN)
/* Slew Rate Control */
#define Parity_SLW                    (* (reg8 *) Parity__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Parity_PRTDSI__CAPS_SEL       (* (reg8 *) Parity__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Parity_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Parity__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Parity_PRTDSI__OE_SEL0        (* (reg8 *) Parity__PRTDSI__OE_SEL0) 
#define Parity_PRTDSI__OE_SEL1        (* (reg8 *) Parity__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Parity_PRTDSI__OUT_SEL0       (* (reg8 *) Parity__PRTDSI__OUT_SEL0) 
#define Parity_PRTDSI__OUT_SEL1       (* (reg8 *) Parity__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Parity_PRTDSI__SYNC_OUT       (* (reg8 *) Parity__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Parity__SIO_CFG)
    #define Parity_SIO_HYST_EN        (* (reg8 *) Parity__SIO_HYST_EN)
    #define Parity_SIO_REG_HIFREQ     (* (reg8 *) Parity__SIO_REG_HIFREQ)
    #define Parity_SIO_CFG            (* (reg8 *) Parity__SIO_CFG)
    #define Parity_SIO_DIFF           (* (reg8 *) Parity__SIO_DIFF)
#endif /* (Parity__SIO_CFG) */

/* Interrupt Registers */
#if defined(Parity__INTSTAT)
    #define Parity_INTSTAT            (* (reg8 *) Parity__INTSTAT)
    #define Parity_SNAP               (* (reg8 *) Parity__SNAP)
    
	#define Parity_0_INTTYPE_REG 		(* (reg8 *) Parity__0__INTTYPE)
#endif /* (Parity__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Parity_H */


/* [] END OF FILE */
