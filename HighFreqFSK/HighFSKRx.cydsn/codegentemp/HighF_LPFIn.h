/*******************************************************************************
* File Name: HighF_LPFIn.h  
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

#if !defined(CY_PINS_HighF_LPFIn_H) /* Pins HighF_LPFIn_H */
#define CY_PINS_HighF_LPFIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HighF_LPFIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HighF_LPFIn__PORT == 15 && ((HighF_LPFIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HighF_LPFIn_Write(uint8 value);
void    HighF_LPFIn_SetDriveMode(uint8 mode);
uint8   HighF_LPFIn_ReadDataReg(void);
uint8   HighF_LPFIn_Read(void);
void    HighF_LPFIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   HighF_LPFIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HighF_LPFIn_SetDriveMode() function.
     *  @{
     */
        #define HighF_LPFIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HighF_LPFIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HighF_LPFIn_DM_RES_UP          PIN_DM_RES_UP
        #define HighF_LPFIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define HighF_LPFIn_DM_OD_LO           PIN_DM_OD_LO
        #define HighF_LPFIn_DM_OD_HI           PIN_DM_OD_HI
        #define HighF_LPFIn_DM_STRONG          PIN_DM_STRONG
        #define HighF_LPFIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HighF_LPFIn_MASK               HighF_LPFIn__MASK
#define HighF_LPFIn_SHIFT              HighF_LPFIn__SHIFT
#define HighF_LPFIn_WIDTH              1u

/* Interrupt constants */
#if defined(HighF_LPFIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HighF_LPFIn_SetInterruptMode() function.
     *  @{
     */
        #define HighF_LPFIn_INTR_NONE      (uint16)(0x0000u)
        #define HighF_LPFIn_INTR_RISING    (uint16)(0x0001u)
        #define HighF_LPFIn_INTR_FALLING   (uint16)(0x0002u)
        #define HighF_LPFIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HighF_LPFIn_INTR_MASK      (0x01u) 
#endif /* (HighF_LPFIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HighF_LPFIn_PS                     (* (reg8 *) HighF_LPFIn__PS)
/* Data Register */
#define HighF_LPFIn_DR                     (* (reg8 *) HighF_LPFIn__DR)
/* Port Number */
#define HighF_LPFIn_PRT_NUM                (* (reg8 *) HighF_LPFIn__PRT) 
/* Connect to Analog Globals */                                                  
#define HighF_LPFIn_AG                     (* (reg8 *) HighF_LPFIn__AG)                       
/* Analog MUX bux enable */
#define HighF_LPFIn_AMUX                   (* (reg8 *) HighF_LPFIn__AMUX) 
/* Bidirectional Enable */                                                        
#define HighF_LPFIn_BIE                    (* (reg8 *) HighF_LPFIn__BIE)
/* Bit-mask for Aliased Register Access */
#define HighF_LPFIn_BIT_MASK               (* (reg8 *) HighF_LPFIn__BIT_MASK)
/* Bypass Enable */
#define HighF_LPFIn_BYP                    (* (reg8 *) HighF_LPFIn__BYP)
/* Port wide control signals */                                                   
#define HighF_LPFIn_CTL                    (* (reg8 *) HighF_LPFIn__CTL)
/* Drive Modes */
#define HighF_LPFIn_DM0                    (* (reg8 *) HighF_LPFIn__DM0) 
#define HighF_LPFIn_DM1                    (* (reg8 *) HighF_LPFIn__DM1)
#define HighF_LPFIn_DM2                    (* (reg8 *) HighF_LPFIn__DM2) 
/* Input Buffer Disable Override */
#define HighF_LPFIn_INP_DIS                (* (reg8 *) HighF_LPFIn__INP_DIS)
/* LCD Common or Segment Drive */
#define HighF_LPFIn_LCD_COM_SEG            (* (reg8 *) HighF_LPFIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define HighF_LPFIn_LCD_EN                 (* (reg8 *) HighF_LPFIn__LCD_EN)
/* Slew Rate Control */
#define HighF_LPFIn_SLW                    (* (reg8 *) HighF_LPFIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HighF_LPFIn_PRTDSI__CAPS_SEL       (* (reg8 *) HighF_LPFIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HighF_LPFIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HighF_LPFIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HighF_LPFIn_PRTDSI__OE_SEL0        (* (reg8 *) HighF_LPFIn__PRTDSI__OE_SEL0) 
#define HighF_LPFIn_PRTDSI__OE_SEL1        (* (reg8 *) HighF_LPFIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HighF_LPFIn_PRTDSI__OUT_SEL0       (* (reg8 *) HighF_LPFIn__PRTDSI__OUT_SEL0) 
#define HighF_LPFIn_PRTDSI__OUT_SEL1       (* (reg8 *) HighF_LPFIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HighF_LPFIn_PRTDSI__SYNC_OUT       (* (reg8 *) HighF_LPFIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HighF_LPFIn__SIO_CFG)
    #define HighF_LPFIn_SIO_HYST_EN        (* (reg8 *) HighF_LPFIn__SIO_HYST_EN)
    #define HighF_LPFIn_SIO_REG_HIFREQ     (* (reg8 *) HighF_LPFIn__SIO_REG_HIFREQ)
    #define HighF_LPFIn_SIO_CFG            (* (reg8 *) HighF_LPFIn__SIO_CFG)
    #define HighF_LPFIn_SIO_DIFF           (* (reg8 *) HighF_LPFIn__SIO_DIFF)
#endif /* (HighF_LPFIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(HighF_LPFIn__INTSTAT)
    #define HighF_LPFIn_INTSTAT            (* (reg8 *) HighF_LPFIn__INTSTAT)
    #define HighF_LPFIn_SNAP               (* (reg8 *) HighF_LPFIn__SNAP)
    
	#define HighF_LPFIn_0_INTTYPE_REG 		(* (reg8 *) HighF_LPFIn__0__INTTYPE)
#endif /* (HighF_LPFIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HighF_LPFIn_H */


/* [] END OF FILE */
