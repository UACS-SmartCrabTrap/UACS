/*******************************************************************************
* File Name: Bit_7.h  
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

#if !defined(CY_PINS_Bit_7_H) /* Pins Bit_7_H */
#define CY_PINS_Bit_7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Bit_7_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Bit_7__PORT == 15 && ((Bit_7__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Bit_7_Write(uint8 value);
void    Bit_7_SetDriveMode(uint8 mode);
uint8   Bit_7_ReadDataReg(void);
uint8   Bit_7_Read(void);
void    Bit_7_SetInterruptMode(uint16 position, uint16 mode);
uint8   Bit_7_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Bit_7_SetDriveMode() function.
     *  @{
     */
        #define Bit_7_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Bit_7_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Bit_7_DM_RES_UP          PIN_DM_RES_UP
        #define Bit_7_DM_RES_DWN         PIN_DM_RES_DWN
        #define Bit_7_DM_OD_LO           PIN_DM_OD_LO
        #define Bit_7_DM_OD_HI           PIN_DM_OD_HI
        #define Bit_7_DM_STRONG          PIN_DM_STRONG
        #define Bit_7_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Bit_7_MASK               Bit_7__MASK
#define Bit_7_SHIFT              Bit_7__SHIFT
#define Bit_7_WIDTH              1u

/* Interrupt constants */
#if defined(Bit_7__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Bit_7_SetInterruptMode() function.
     *  @{
     */
        #define Bit_7_INTR_NONE      (uint16)(0x0000u)
        #define Bit_7_INTR_RISING    (uint16)(0x0001u)
        #define Bit_7_INTR_FALLING   (uint16)(0x0002u)
        #define Bit_7_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Bit_7_INTR_MASK      (0x01u) 
#endif /* (Bit_7__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Bit_7_PS                     (* (reg8 *) Bit_7__PS)
/* Data Register */
#define Bit_7_DR                     (* (reg8 *) Bit_7__DR)
/* Port Number */
#define Bit_7_PRT_NUM                (* (reg8 *) Bit_7__PRT) 
/* Connect to Analog Globals */                                                  
#define Bit_7_AG                     (* (reg8 *) Bit_7__AG)                       
/* Analog MUX bux enable */
#define Bit_7_AMUX                   (* (reg8 *) Bit_7__AMUX) 
/* Bidirectional Enable */                                                        
#define Bit_7_BIE                    (* (reg8 *) Bit_7__BIE)
/* Bit-mask for Aliased Register Access */
#define Bit_7_BIT_MASK               (* (reg8 *) Bit_7__BIT_MASK)
/* Bypass Enable */
#define Bit_7_BYP                    (* (reg8 *) Bit_7__BYP)
/* Port wide control signals */                                                   
#define Bit_7_CTL                    (* (reg8 *) Bit_7__CTL)
/* Drive Modes */
#define Bit_7_DM0                    (* (reg8 *) Bit_7__DM0) 
#define Bit_7_DM1                    (* (reg8 *) Bit_7__DM1)
#define Bit_7_DM2                    (* (reg8 *) Bit_7__DM2) 
/* Input Buffer Disable Override */
#define Bit_7_INP_DIS                (* (reg8 *) Bit_7__INP_DIS)
/* LCD Common or Segment Drive */
#define Bit_7_LCD_COM_SEG            (* (reg8 *) Bit_7__LCD_COM_SEG)
/* Enable Segment LCD */
#define Bit_7_LCD_EN                 (* (reg8 *) Bit_7__LCD_EN)
/* Slew Rate Control */
#define Bit_7_SLW                    (* (reg8 *) Bit_7__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Bit_7_PRTDSI__CAPS_SEL       (* (reg8 *) Bit_7__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Bit_7_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Bit_7__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Bit_7_PRTDSI__OE_SEL0        (* (reg8 *) Bit_7__PRTDSI__OE_SEL0) 
#define Bit_7_PRTDSI__OE_SEL1        (* (reg8 *) Bit_7__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Bit_7_PRTDSI__OUT_SEL0       (* (reg8 *) Bit_7__PRTDSI__OUT_SEL0) 
#define Bit_7_PRTDSI__OUT_SEL1       (* (reg8 *) Bit_7__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Bit_7_PRTDSI__SYNC_OUT       (* (reg8 *) Bit_7__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Bit_7__SIO_CFG)
    #define Bit_7_SIO_HYST_EN        (* (reg8 *) Bit_7__SIO_HYST_EN)
    #define Bit_7_SIO_REG_HIFREQ     (* (reg8 *) Bit_7__SIO_REG_HIFREQ)
    #define Bit_7_SIO_CFG            (* (reg8 *) Bit_7__SIO_CFG)
    #define Bit_7_SIO_DIFF           (* (reg8 *) Bit_7__SIO_DIFF)
#endif /* (Bit_7__SIO_CFG) */

/* Interrupt Registers */
#if defined(Bit_7__INTSTAT)
    #define Bit_7_INTSTAT            (* (reg8 *) Bit_7__INTSTAT)
    #define Bit_7_SNAP               (* (reg8 *) Bit_7__SNAP)
    
	#define Bit_7_0_INTTYPE_REG 		(* (reg8 *) Bit_7__0__INTTYPE)
#endif /* (Bit_7__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Bit_7_H */


/* [] END OF FILE */
