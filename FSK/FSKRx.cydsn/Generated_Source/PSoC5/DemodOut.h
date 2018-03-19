/*******************************************************************************
* File Name: DemodOut.h  
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

#if !defined(CY_PINS_DemodOut_H) /* Pins DemodOut_H */
#define CY_PINS_DemodOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DemodOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DemodOut__PORT == 15 && ((DemodOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DemodOut_Write(uint8 value);
void    DemodOut_SetDriveMode(uint8 mode);
uint8   DemodOut_ReadDataReg(void);
uint8   DemodOut_Read(void);
void    DemodOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   DemodOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DemodOut_SetDriveMode() function.
     *  @{
     */
        #define DemodOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DemodOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DemodOut_DM_RES_UP          PIN_DM_RES_UP
        #define DemodOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define DemodOut_DM_OD_LO           PIN_DM_OD_LO
        #define DemodOut_DM_OD_HI           PIN_DM_OD_HI
        #define DemodOut_DM_STRONG          PIN_DM_STRONG
        #define DemodOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DemodOut_MASK               DemodOut__MASK
#define DemodOut_SHIFT              DemodOut__SHIFT
#define DemodOut_WIDTH              1u

/* Interrupt constants */
#if defined(DemodOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DemodOut_SetInterruptMode() function.
     *  @{
     */
        #define DemodOut_INTR_NONE      (uint16)(0x0000u)
        #define DemodOut_INTR_RISING    (uint16)(0x0001u)
        #define DemodOut_INTR_FALLING   (uint16)(0x0002u)
        #define DemodOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DemodOut_INTR_MASK      (0x01u) 
#endif /* (DemodOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DemodOut_PS                     (* (reg8 *) DemodOut__PS)
/* Data Register */
#define DemodOut_DR                     (* (reg8 *) DemodOut__DR)
/* Port Number */
#define DemodOut_PRT_NUM                (* (reg8 *) DemodOut__PRT) 
/* Connect to Analog Globals */                                                  
#define DemodOut_AG                     (* (reg8 *) DemodOut__AG)                       
/* Analog MUX bux enable */
#define DemodOut_AMUX                   (* (reg8 *) DemodOut__AMUX) 
/* Bidirectional Enable */                                                        
#define DemodOut_BIE                    (* (reg8 *) DemodOut__BIE)
/* Bit-mask for Aliased Register Access */
#define DemodOut_BIT_MASK               (* (reg8 *) DemodOut__BIT_MASK)
/* Bypass Enable */
#define DemodOut_BYP                    (* (reg8 *) DemodOut__BYP)
/* Port wide control signals */                                                   
#define DemodOut_CTL                    (* (reg8 *) DemodOut__CTL)
/* Drive Modes */
#define DemodOut_DM0                    (* (reg8 *) DemodOut__DM0) 
#define DemodOut_DM1                    (* (reg8 *) DemodOut__DM1)
#define DemodOut_DM2                    (* (reg8 *) DemodOut__DM2) 
/* Input Buffer Disable Override */
#define DemodOut_INP_DIS                (* (reg8 *) DemodOut__INP_DIS)
/* LCD Common or Segment Drive */
#define DemodOut_LCD_COM_SEG            (* (reg8 *) DemodOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define DemodOut_LCD_EN                 (* (reg8 *) DemodOut__LCD_EN)
/* Slew Rate Control */
#define DemodOut_SLW                    (* (reg8 *) DemodOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DemodOut_PRTDSI__CAPS_SEL       (* (reg8 *) DemodOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DemodOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DemodOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DemodOut_PRTDSI__OE_SEL0        (* (reg8 *) DemodOut__PRTDSI__OE_SEL0) 
#define DemodOut_PRTDSI__OE_SEL1        (* (reg8 *) DemodOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DemodOut_PRTDSI__OUT_SEL0       (* (reg8 *) DemodOut__PRTDSI__OUT_SEL0) 
#define DemodOut_PRTDSI__OUT_SEL1       (* (reg8 *) DemodOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DemodOut_PRTDSI__SYNC_OUT       (* (reg8 *) DemodOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DemodOut__SIO_CFG)
    #define DemodOut_SIO_HYST_EN        (* (reg8 *) DemodOut__SIO_HYST_EN)
    #define DemodOut_SIO_REG_HIFREQ     (* (reg8 *) DemodOut__SIO_REG_HIFREQ)
    #define DemodOut_SIO_CFG            (* (reg8 *) DemodOut__SIO_CFG)
    #define DemodOut_SIO_DIFF           (* (reg8 *) DemodOut__SIO_DIFF)
#endif /* (DemodOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(DemodOut__INTSTAT)
    #define DemodOut_INTSTAT            (* (reg8 *) DemodOut__INTSTAT)
    #define DemodOut_SNAP               (* (reg8 *) DemodOut__SNAP)
    
	#define DemodOut_0_INTTYPE_REG 		(* (reg8 *) DemodOut__0__INTTYPE)
#endif /* (DemodOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DemodOut_H */


/* [] END OF FILE */
