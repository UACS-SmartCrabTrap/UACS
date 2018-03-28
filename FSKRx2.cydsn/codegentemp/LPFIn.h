/*******************************************************************************
* File Name: LPFIn.h  
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

#if !defined(CY_PINS_LPFIn_H) /* Pins LPFIn_H */
#define CY_PINS_LPFIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LPFIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LPFIn__PORT == 15 && ((LPFIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LPFIn_Write(uint8 value);
void    LPFIn_SetDriveMode(uint8 mode);
uint8   LPFIn_ReadDataReg(void);
uint8   LPFIn_Read(void);
void    LPFIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   LPFIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LPFIn_SetDriveMode() function.
     *  @{
     */
        #define LPFIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LPFIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LPFIn_DM_RES_UP          PIN_DM_RES_UP
        #define LPFIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define LPFIn_DM_OD_LO           PIN_DM_OD_LO
        #define LPFIn_DM_OD_HI           PIN_DM_OD_HI
        #define LPFIn_DM_STRONG          PIN_DM_STRONG
        #define LPFIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LPFIn_MASK               LPFIn__MASK
#define LPFIn_SHIFT              LPFIn__SHIFT
#define LPFIn_WIDTH              1u

/* Interrupt constants */
#if defined(LPFIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LPFIn_SetInterruptMode() function.
     *  @{
     */
        #define LPFIn_INTR_NONE      (uint16)(0x0000u)
        #define LPFIn_INTR_RISING    (uint16)(0x0001u)
        #define LPFIn_INTR_FALLING   (uint16)(0x0002u)
        #define LPFIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LPFIn_INTR_MASK      (0x01u) 
#endif /* (LPFIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LPFIn_PS                     (* (reg8 *) LPFIn__PS)
/* Data Register */
#define LPFIn_DR                     (* (reg8 *) LPFIn__DR)
/* Port Number */
#define LPFIn_PRT_NUM                (* (reg8 *) LPFIn__PRT) 
/* Connect to Analog Globals */                                                  
#define LPFIn_AG                     (* (reg8 *) LPFIn__AG)                       
/* Analog MUX bux enable */
#define LPFIn_AMUX                   (* (reg8 *) LPFIn__AMUX) 
/* Bidirectional Enable */                                                        
#define LPFIn_BIE                    (* (reg8 *) LPFIn__BIE)
/* Bit-mask for Aliased Register Access */
#define LPFIn_BIT_MASK               (* (reg8 *) LPFIn__BIT_MASK)
/* Bypass Enable */
#define LPFIn_BYP                    (* (reg8 *) LPFIn__BYP)
/* Port wide control signals */                                                   
#define LPFIn_CTL                    (* (reg8 *) LPFIn__CTL)
/* Drive Modes */
#define LPFIn_DM0                    (* (reg8 *) LPFIn__DM0) 
#define LPFIn_DM1                    (* (reg8 *) LPFIn__DM1)
#define LPFIn_DM2                    (* (reg8 *) LPFIn__DM2) 
/* Input Buffer Disable Override */
#define LPFIn_INP_DIS                (* (reg8 *) LPFIn__INP_DIS)
/* LCD Common or Segment Drive */
#define LPFIn_LCD_COM_SEG            (* (reg8 *) LPFIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define LPFIn_LCD_EN                 (* (reg8 *) LPFIn__LCD_EN)
/* Slew Rate Control */
#define LPFIn_SLW                    (* (reg8 *) LPFIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LPFIn_PRTDSI__CAPS_SEL       (* (reg8 *) LPFIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LPFIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LPFIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LPFIn_PRTDSI__OE_SEL0        (* (reg8 *) LPFIn__PRTDSI__OE_SEL0) 
#define LPFIn_PRTDSI__OE_SEL1        (* (reg8 *) LPFIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LPFIn_PRTDSI__OUT_SEL0       (* (reg8 *) LPFIn__PRTDSI__OUT_SEL0) 
#define LPFIn_PRTDSI__OUT_SEL1       (* (reg8 *) LPFIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LPFIn_PRTDSI__SYNC_OUT       (* (reg8 *) LPFIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LPFIn__SIO_CFG)
    #define LPFIn_SIO_HYST_EN        (* (reg8 *) LPFIn__SIO_HYST_EN)
    #define LPFIn_SIO_REG_HIFREQ     (* (reg8 *) LPFIn__SIO_REG_HIFREQ)
    #define LPFIn_SIO_CFG            (* (reg8 *) LPFIn__SIO_CFG)
    #define LPFIn_SIO_DIFF           (* (reg8 *) LPFIn__SIO_DIFF)
#endif /* (LPFIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(LPFIn__INTSTAT)
    #define LPFIn_INTSTAT            (* (reg8 *) LPFIn__INTSTAT)
    #define LPFIn_SNAP               (* (reg8 *) LPFIn__SNAP)
    
	#define LPFIn_0_INTTYPE_REG 		(* (reg8 *) LPFIn__0__INTTYPE)
#endif /* (LPFIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LPFIn_H */


/* [] END OF FILE */
