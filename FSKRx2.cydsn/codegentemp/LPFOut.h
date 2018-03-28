/*******************************************************************************
* File Name: LPFOut.h  
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

#if !defined(CY_PINS_LPFOut_H) /* Pins LPFOut_H */
#define CY_PINS_LPFOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LPFOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LPFOut__PORT == 15 && ((LPFOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LPFOut_Write(uint8 value);
void    LPFOut_SetDriveMode(uint8 mode);
uint8   LPFOut_ReadDataReg(void);
uint8   LPFOut_Read(void);
void    LPFOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   LPFOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LPFOut_SetDriveMode() function.
     *  @{
     */
        #define LPFOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LPFOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LPFOut_DM_RES_UP          PIN_DM_RES_UP
        #define LPFOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define LPFOut_DM_OD_LO           PIN_DM_OD_LO
        #define LPFOut_DM_OD_HI           PIN_DM_OD_HI
        #define LPFOut_DM_STRONG          PIN_DM_STRONG
        #define LPFOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LPFOut_MASK               LPFOut__MASK
#define LPFOut_SHIFT              LPFOut__SHIFT
#define LPFOut_WIDTH              1u

/* Interrupt constants */
#if defined(LPFOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LPFOut_SetInterruptMode() function.
     *  @{
     */
        #define LPFOut_INTR_NONE      (uint16)(0x0000u)
        #define LPFOut_INTR_RISING    (uint16)(0x0001u)
        #define LPFOut_INTR_FALLING   (uint16)(0x0002u)
        #define LPFOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LPFOut_INTR_MASK      (0x01u) 
#endif /* (LPFOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LPFOut_PS                     (* (reg8 *) LPFOut__PS)
/* Data Register */
#define LPFOut_DR                     (* (reg8 *) LPFOut__DR)
/* Port Number */
#define LPFOut_PRT_NUM                (* (reg8 *) LPFOut__PRT) 
/* Connect to Analog Globals */                                                  
#define LPFOut_AG                     (* (reg8 *) LPFOut__AG)                       
/* Analog MUX bux enable */
#define LPFOut_AMUX                   (* (reg8 *) LPFOut__AMUX) 
/* Bidirectional Enable */                                                        
#define LPFOut_BIE                    (* (reg8 *) LPFOut__BIE)
/* Bit-mask for Aliased Register Access */
#define LPFOut_BIT_MASK               (* (reg8 *) LPFOut__BIT_MASK)
/* Bypass Enable */
#define LPFOut_BYP                    (* (reg8 *) LPFOut__BYP)
/* Port wide control signals */                                                   
#define LPFOut_CTL                    (* (reg8 *) LPFOut__CTL)
/* Drive Modes */
#define LPFOut_DM0                    (* (reg8 *) LPFOut__DM0) 
#define LPFOut_DM1                    (* (reg8 *) LPFOut__DM1)
#define LPFOut_DM2                    (* (reg8 *) LPFOut__DM2) 
/* Input Buffer Disable Override */
#define LPFOut_INP_DIS                (* (reg8 *) LPFOut__INP_DIS)
/* LCD Common or Segment Drive */
#define LPFOut_LCD_COM_SEG            (* (reg8 *) LPFOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define LPFOut_LCD_EN                 (* (reg8 *) LPFOut__LCD_EN)
/* Slew Rate Control */
#define LPFOut_SLW                    (* (reg8 *) LPFOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LPFOut_PRTDSI__CAPS_SEL       (* (reg8 *) LPFOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LPFOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LPFOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LPFOut_PRTDSI__OE_SEL0        (* (reg8 *) LPFOut__PRTDSI__OE_SEL0) 
#define LPFOut_PRTDSI__OE_SEL1        (* (reg8 *) LPFOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LPFOut_PRTDSI__OUT_SEL0       (* (reg8 *) LPFOut__PRTDSI__OUT_SEL0) 
#define LPFOut_PRTDSI__OUT_SEL1       (* (reg8 *) LPFOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LPFOut_PRTDSI__SYNC_OUT       (* (reg8 *) LPFOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LPFOut__SIO_CFG)
    #define LPFOut_SIO_HYST_EN        (* (reg8 *) LPFOut__SIO_HYST_EN)
    #define LPFOut_SIO_REG_HIFREQ     (* (reg8 *) LPFOut__SIO_REG_HIFREQ)
    #define LPFOut_SIO_CFG            (* (reg8 *) LPFOut__SIO_CFG)
    #define LPFOut_SIO_DIFF           (* (reg8 *) LPFOut__SIO_DIFF)
#endif /* (LPFOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(LPFOut__INTSTAT)
    #define LPFOut_INTSTAT            (* (reg8 *) LPFOut__INTSTAT)
    #define LPFOut_SNAP               (* (reg8 *) LPFOut__SNAP)
    
	#define LPFOut_0_INTTYPE_REG 		(* (reg8 *) LPFOut__0__INTTYPE)
#endif /* (LPFOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LPFOut_H */


/* [] END OF FILE */
