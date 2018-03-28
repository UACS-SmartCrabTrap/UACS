/*******************************************************************************
* File Name: CompOut.h  
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

#if !defined(CY_PINS_CompOut_H) /* Pins CompOut_H */
#define CY_PINS_CompOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "CompOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 CompOut__PORT == 15 && ((CompOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    CompOut_Write(uint8 value);
void    CompOut_SetDriveMode(uint8 mode);
uint8   CompOut_ReadDataReg(void);
uint8   CompOut_Read(void);
void    CompOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   CompOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the CompOut_SetDriveMode() function.
     *  @{
     */
        #define CompOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define CompOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define CompOut_DM_RES_UP          PIN_DM_RES_UP
        #define CompOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define CompOut_DM_OD_LO           PIN_DM_OD_LO
        #define CompOut_DM_OD_HI           PIN_DM_OD_HI
        #define CompOut_DM_STRONG          PIN_DM_STRONG
        #define CompOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define CompOut_MASK               CompOut__MASK
#define CompOut_SHIFT              CompOut__SHIFT
#define CompOut_WIDTH              1u

/* Interrupt constants */
#if defined(CompOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CompOut_SetInterruptMode() function.
     *  @{
     */
        #define CompOut_INTR_NONE      (uint16)(0x0000u)
        #define CompOut_INTR_RISING    (uint16)(0x0001u)
        #define CompOut_INTR_FALLING   (uint16)(0x0002u)
        #define CompOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define CompOut_INTR_MASK      (0x01u) 
#endif /* (CompOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CompOut_PS                     (* (reg8 *) CompOut__PS)
/* Data Register */
#define CompOut_DR                     (* (reg8 *) CompOut__DR)
/* Port Number */
#define CompOut_PRT_NUM                (* (reg8 *) CompOut__PRT) 
/* Connect to Analog Globals */                                                  
#define CompOut_AG                     (* (reg8 *) CompOut__AG)                       
/* Analog MUX bux enable */
#define CompOut_AMUX                   (* (reg8 *) CompOut__AMUX) 
/* Bidirectional Enable */                                                        
#define CompOut_BIE                    (* (reg8 *) CompOut__BIE)
/* Bit-mask for Aliased Register Access */
#define CompOut_BIT_MASK               (* (reg8 *) CompOut__BIT_MASK)
/* Bypass Enable */
#define CompOut_BYP                    (* (reg8 *) CompOut__BYP)
/* Port wide control signals */                                                   
#define CompOut_CTL                    (* (reg8 *) CompOut__CTL)
/* Drive Modes */
#define CompOut_DM0                    (* (reg8 *) CompOut__DM0) 
#define CompOut_DM1                    (* (reg8 *) CompOut__DM1)
#define CompOut_DM2                    (* (reg8 *) CompOut__DM2) 
/* Input Buffer Disable Override */
#define CompOut_INP_DIS                (* (reg8 *) CompOut__INP_DIS)
/* LCD Common or Segment Drive */
#define CompOut_LCD_COM_SEG            (* (reg8 *) CompOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define CompOut_LCD_EN                 (* (reg8 *) CompOut__LCD_EN)
/* Slew Rate Control */
#define CompOut_SLW                    (* (reg8 *) CompOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define CompOut_PRTDSI__CAPS_SEL       (* (reg8 *) CompOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define CompOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) CompOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define CompOut_PRTDSI__OE_SEL0        (* (reg8 *) CompOut__PRTDSI__OE_SEL0) 
#define CompOut_PRTDSI__OE_SEL1        (* (reg8 *) CompOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define CompOut_PRTDSI__OUT_SEL0       (* (reg8 *) CompOut__PRTDSI__OUT_SEL0) 
#define CompOut_PRTDSI__OUT_SEL1       (* (reg8 *) CompOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define CompOut_PRTDSI__SYNC_OUT       (* (reg8 *) CompOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(CompOut__SIO_CFG)
    #define CompOut_SIO_HYST_EN        (* (reg8 *) CompOut__SIO_HYST_EN)
    #define CompOut_SIO_REG_HIFREQ     (* (reg8 *) CompOut__SIO_REG_HIFREQ)
    #define CompOut_SIO_CFG            (* (reg8 *) CompOut__SIO_CFG)
    #define CompOut_SIO_DIFF           (* (reg8 *) CompOut__SIO_DIFF)
#endif /* (CompOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(CompOut__INTSTAT)
    #define CompOut_INTSTAT            (* (reg8 *) CompOut__INTSTAT)
    #define CompOut_SNAP               (* (reg8 *) CompOut__SNAP)
    
	#define CompOut_0_INTTYPE_REG 		(* (reg8 *) CompOut__0__INTTYPE)
#endif /* (CompOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_CompOut_H */


/* [] END OF FILE */
