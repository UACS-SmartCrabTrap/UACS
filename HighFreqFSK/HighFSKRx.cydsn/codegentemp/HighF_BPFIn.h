/*******************************************************************************
* File Name: HighF_BPFIn.h  
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

#if !defined(CY_PINS_HighF_BPFIn_H) /* Pins HighF_BPFIn_H */
#define CY_PINS_HighF_BPFIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HighF_BPFIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HighF_BPFIn__PORT == 15 && ((HighF_BPFIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HighF_BPFIn_Write(uint8 value);
void    HighF_BPFIn_SetDriveMode(uint8 mode);
uint8   HighF_BPFIn_ReadDataReg(void);
uint8   HighF_BPFIn_Read(void);
void    HighF_BPFIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   HighF_BPFIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HighF_BPFIn_SetDriveMode() function.
     *  @{
     */
        #define HighF_BPFIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HighF_BPFIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HighF_BPFIn_DM_RES_UP          PIN_DM_RES_UP
        #define HighF_BPFIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define HighF_BPFIn_DM_OD_LO           PIN_DM_OD_LO
        #define HighF_BPFIn_DM_OD_HI           PIN_DM_OD_HI
        #define HighF_BPFIn_DM_STRONG          PIN_DM_STRONG
        #define HighF_BPFIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HighF_BPFIn_MASK               HighF_BPFIn__MASK
#define HighF_BPFIn_SHIFT              HighF_BPFIn__SHIFT
#define HighF_BPFIn_WIDTH              1u

/* Interrupt constants */
#if defined(HighF_BPFIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HighF_BPFIn_SetInterruptMode() function.
     *  @{
     */
        #define HighF_BPFIn_INTR_NONE      (uint16)(0x0000u)
        #define HighF_BPFIn_INTR_RISING    (uint16)(0x0001u)
        #define HighF_BPFIn_INTR_FALLING   (uint16)(0x0002u)
        #define HighF_BPFIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HighF_BPFIn_INTR_MASK      (0x01u) 
#endif /* (HighF_BPFIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HighF_BPFIn_PS                     (* (reg8 *) HighF_BPFIn__PS)
/* Data Register */
#define HighF_BPFIn_DR                     (* (reg8 *) HighF_BPFIn__DR)
/* Port Number */
#define HighF_BPFIn_PRT_NUM                (* (reg8 *) HighF_BPFIn__PRT) 
/* Connect to Analog Globals */                                                  
#define HighF_BPFIn_AG                     (* (reg8 *) HighF_BPFIn__AG)                       
/* Analog MUX bux enable */
#define HighF_BPFIn_AMUX                   (* (reg8 *) HighF_BPFIn__AMUX) 
/* Bidirectional Enable */                                                        
#define HighF_BPFIn_BIE                    (* (reg8 *) HighF_BPFIn__BIE)
/* Bit-mask for Aliased Register Access */
#define HighF_BPFIn_BIT_MASK               (* (reg8 *) HighF_BPFIn__BIT_MASK)
/* Bypass Enable */
#define HighF_BPFIn_BYP                    (* (reg8 *) HighF_BPFIn__BYP)
/* Port wide control signals */                                                   
#define HighF_BPFIn_CTL                    (* (reg8 *) HighF_BPFIn__CTL)
/* Drive Modes */
#define HighF_BPFIn_DM0                    (* (reg8 *) HighF_BPFIn__DM0) 
#define HighF_BPFIn_DM1                    (* (reg8 *) HighF_BPFIn__DM1)
#define HighF_BPFIn_DM2                    (* (reg8 *) HighF_BPFIn__DM2) 
/* Input Buffer Disable Override */
#define HighF_BPFIn_INP_DIS                (* (reg8 *) HighF_BPFIn__INP_DIS)
/* LCD Common or Segment Drive */
#define HighF_BPFIn_LCD_COM_SEG            (* (reg8 *) HighF_BPFIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define HighF_BPFIn_LCD_EN                 (* (reg8 *) HighF_BPFIn__LCD_EN)
/* Slew Rate Control */
#define HighF_BPFIn_SLW                    (* (reg8 *) HighF_BPFIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HighF_BPFIn_PRTDSI__CAPS_SEL       (* (reg8 *) HighF_BPFIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HighF_BPFIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HighF_BPFIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HighF_BPFIn_PRTDSI__OE_SEL0        (* (reg8 *) HighF_BPFIn__PRTDSI__OE_SEL0) 
#define HighF_BPFIn_PRTDSI__OE_SEL1        (* (reg8 *) HighF_BPFIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HighF_BPFIn_PRTDSI__OUT_SEL0       (* (reg8 *) HighF_BPFIn__PRTDSI__OUT_SEL0) 
#define HighF_BPFIn_PRTDSI__OUT_SEL1       (* (reg8 *) HighF_BPFIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HighF_BPFIn_PRTDSI__SYNC_OUT       (* (reg8 *) HighF_BPFIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HighF_BPFIn__SIO_CFG)
    #define HighF_BPFIn_SIO_HYST_EN        (* (reg8 *) HighF_BPFIn__SIO_HYST_EN)
    #define HighF_BPFIn_SIO_REG_HIFREQ     (* (reg8 *) HighF_BPFIn__SIO_REG_HIFREQ)
    #define HighF_BPFIn_SIO_CFG            (* (reg8 *) HighF_BPFIn__SIO_CFG)
    #define HighF_BPFIn_SIO_DIFF           (* (reg8 *) HighF_BPFIn__SIO_DIFF)
#endif /* (HighF_BPFIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(HighF_BPFIn__INTSTAT)
    #define HighF_BPFIn_INTSTAT            (* (reg8 *) HighF_BPFIn__INTSTAT)
    #define HighF_BPFIn_SNAP               (* (reg8 *) HighF_BPFIn__SNAP)
    
	#define HighF_BPFIn_0_INTTYPE_REG 		(* (reg8 *) HighF_BPFIn__0__INTTYPE)
#endif /* (HighF_BPFIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HighF_BPFIn_H */


/* [] END OF FILE */
