/*******************************************************************************
* File Name: SignalBase.h  
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

#if !defined(CY_PINS_SignalBase_H) /* Pins SignalBase_H */
#define CY_PINS_SignalBase_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SignalBase_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SignalBase__PORT == 15 && ((SignalBase__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SignalBase_Write(uint8 value);
void    SignalBase_SetDriveMode(uint8 mode);
uint8   SignalBase_ReadDataReg(void);
uint8   SignalBase_Read(void);
void    SignalBase_SetInterruptMode(uint16 position, uint16 mode);
uint8   SignalBase_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SignalBase_SetDriveMode() function.
     *  @{
     */
        #define SignalBase_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SignalBase_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SignalBase_DM_RES_UP          PIN_DM_RES_UP
        #define SignalBase_DM_RES_DWN         PIN_DM_RES_DWN
        #define SignalBase_DM_OD_LO           PIN_DM_OD_LO
        #define SignalBase_DM_OD_HI           PIN_DM_OD_HI
        #define SignalBase_DM_STRONG          PIN_DM_STRONG
        #define SignalBase_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SignalBase_MASK               SignalBase__MASK
#define SignalBase_SHIFT              SignalBase__SHIFT
#define SignalBase_WIDTH              1u

/* Interrupt constants */
#if defined(SignalBase__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SignalBase_SetInterruptMode() function.
     *  @{
     */
        #define SignalBase_INTR_NONE      (uint16)(0x0000u)
        #define SignalBase_INTR_RISING    (uint16)(0x0001u)
        #define SignalBase_INTR_FALLING   (uint16)(0x0002u)
        #define SignalBase_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SignalBase_INTR_MASK      (0x01u) 
#endif /* (SignalBase__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SignalBase_PS                     (* (reg8 *) SignalBase__PS)
/* Data Register */
#define SignalBase_DR                     (* (reg8 *) SignalBase__DR)
/* Port Number */
#define SignalBase_PRT_NUM                (* (reg8 *) SignalBase__PRT) 
/* Connect to Analog Globals */                                                  
#define SignalBase_AG                     (* (reg8 *) SignalBase__AG)                       
/* Analog MUX bux enable */
#define SignalBase_AMUX                   (* (reg8 *) SignalBase__AMUX) 
/* Bidirectional Enable */                                                        
#define SignalBase_BIE                    (* (reg8 *) SignalBase__BIE)
/* Bit-mask for Aliased Register Access */
#define SignalBase_BIT_MASK               (* (reg8 *) SignalBase__BIT_MASK)
/* Bypass Enable */
#define SignalBase_BYP                    (* (reg8 *) SignalBase__BYP)
/* Port wide control signals */                                                   
#define SignalBase_CTL                    (* (reg8 *) SignalBase__CTL)
/* Drive Modes */
#define SignalBase_DM0                    (* (reg8 *) SignalBase__DM0) 
#define SignalBase_DM1                    (* (reg8 *) SignalBase__DM1)
#define SignalBase_DM2                    (* (reg8 *) SignalBase__DM2) 
/* Input Buffer Disable Override */
#define SignalBase_INP_DIS                (* (reg8 *) SignalBase__INP_DIS)
/* LCD Common or Segment Drive */
#define SignalBase_LCD_COM_SEG            (* (reg8 *) SignalBase__LCD_COM_SEG)
/* Enable Segment LCD */
#define SignalBase_LCD_EN                 (* (reg8 *) SignalBase__LCD_EN)
/* Slew Rate Control */
#define SignalBase_SLW                    (* (reg8 *) SignalBase__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SignalBase_PRTDSI__CAPS_SEL       (* (reg8 *) SignalBase__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SignalBase_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SignalBase__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SignalBase_PRTDSI__OE_SEL0        (* (reg8 *) SignalBase__PRTDSI__OE_SEL0) 
#define SignalBase_PRTDSI__OE_SEL1        (* (reg8 *) SignalBase__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SignalBase_PRTDSI__OUT_SEL0       (* (reg8 *) SignalBase__PRTDSI__OUT_SEL0) 
#define SignalBase_PRTDSI__OUT_SEL1       (* (reg8 *) SignalBase__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SignalBase_PRTDSI__SYNC_OUT       (* (reg8 *) SignalBase__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SignalBase__SIO_CFG)
    #define SignalBase_SIO_HYST_EN        (* (reg8 *) SignalBase__SIO_HYST_EN)
    #define SignalBase_SIO_REG_HIFREQ     (* (reg8 *) SignalBase__SIO_REG_HIFREQ)
    #define SignalBase_SIO_CFG            (* (reg8 *) SignalBase__SIO_CFG)
    #define SignalBase_SIO_DIFF           (* (reg8 *) SignalBase__SIO_DIFF)
#endif /* (SignalBase__SIO_CFG) */

/* Interrupt Registers */
#if defined(SignalBase__INTSTAT)
    #define SignalBase_INTSTAT            (* (reg8 *) SignalBase__INTSTAT)
    #define SignalBase_SNAP               (* (reg8 *) SignalBase__SNAP)
    
	#define SignalBase_0_INTTYPE_REG 		(* (reg8 *) SignalBase__0__INTTYPE)
#endif /* (SignalBase__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SignalBase_H */


/* [] END OF FILE */
