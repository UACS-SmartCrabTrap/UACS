/*******************************************************************************
* File Name: BPF_In.h  
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

#if !defined(CY_PINS_BPF_In_H) /* Pins BPF_In_H */
#define CY_PINS_BPF_In_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BPF_In_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BPF_In__PORT == 15 && ((BPF_In__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BPF_In_Write(uint8 value);
void    BPF_In_SetDriveMode(uint8 mode);
uint8   BPF_In_ReadDataReg(void);
uint8   BPF_In_Read(void);
void    BPF_In_SetInterruptMode(uint16 position, uint16 mode);
uint8   BPF_In_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BPF_In_SetDriveMode() function.
     *  @{
     */
        #define BPF_In_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BPF_In_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BPF_In_DM_RES_UP          PIN_DM_RES_UP
        #define BPF_In_DM_RES_DWN         PIN_DM_RES_DWN
        #define BPF_In_DM_OD_LO           PIN_DM_OD_LO
        #define BPF_In_DM_OD_HI           PIN_DM_OD_HI
        #define BPF_In_DM_STRONG          PIN_DM_STRONG
        #define BPF_In_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BPF_In_MASK               BPF_In__MASK
#define BPF_In_SHIFT              BPF_In__SHIFT
#define BPF_In_WIDTH              1u

/* Interrupt constants */
#if defined(BPF_In__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BPF_In_SetInterruptMode() function.
     *  @{
     */
        #define BPF_In_INTR_NONE      (uint16)(0x0000u)
        #define BPF_In_INTR_RISING    (uint16)(0x0001u)
        #define BPF_In_INTR_FALLING   (uint16)(0x0002u)
        #define BPF_In_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BPF_In_INTR_MASK      (0x01u) 
#endif /* (BPF_In__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BPF_In_PS                     (* (reg8 *) BPF_In__PS)
/* Data Register */
#define BPF_In_DR                     (* (reg8 *) BPF_In__DR)
/* Port Number */
#define BPF_In_PRT_NUM                (* (reg8 *) BPF_In__PRT) 
/* Connect to Analog Globals */                                                  
#define BPF_In_AG                     (* (reg8 *) BPF_In__AG)                       
/* Analog MUX bux enable */
#define BPF_In_AMUX                   (* (reg8 *) BPF_In__AMUX) 
/* Bidirectional Enable */                                                        
#define BPF_In_BIE                    (* (reg8 *) BPF_In__BIE)
/* Bit-mask for Aliased Register Access */
#define BPF_In_BIT_MASK               (* (reg8 *) BPF_In__BIT_MASK)
/* Bypass Enable */
#define BPF_In_BYP                    (* (reg8 *) BPF_In__BYP)
/* Port wide control signals */                                                   
#define BPF_In_CTL                    (* (reg8 *) BPF_In__CTL)
/* Drive Modes */
#define BPF_In_DM0                    (* (reg8 *) BPF_In__DM0) 
#define BPF_In_DM1                    (* (reg8 *) BPF_In__DM1)
#define BPF_In_DM2                    (* (reg8 *) BPF_In__DM2) 
/* Input Buffer Disable Override */
#define BPF_In_INP_DIS                (* (reg8 *) BPF_In__INP_DIS)
/* LCD Common or Segment Drive */
#define BPF_In_LCD_COM_SEG            (* (reg8 *) BPF_In__LCD_COM_SEG)
/* Enable Segment LCD */
#define BPF_In_LCD_EN                 (* (reg8 *) BPF_In__LCD_EN)
/* Slew Rate Control */
#define BPF_In_SLW                    (* (reg8 *) BPF_In__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BPF_In_PRTDSI__CAPS_SEL       (* (reg8 *) BPF_In__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BPF_In_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BPF_In__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BPF_In_PRTDSI__OE_SEL0        (* (reg8 *) BPF_In__PRTDSI__OE_SEL0) 
#define BPF_In_PRTDSI__OE_SEL1        (* (reg8 *) BPF_In__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BPF_In_PRTDSI__OUT_SEL0       (* (reg8 *) BPF_In__PRTDSI__OUT_SEL0) 
#define BPF_In_PRTDSI__OUT_SEL1       (* (reg8 *) BPF_In__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BPF_In_PRTDSI__SYNC_OUT       (* (reg8 *) BPF_In__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BPF_In__SIO_CFG)
    #define BPF_In_SIO_HYST_EN        (* (reg8 *) BPF_In__SIO_HYST_EN)
    #define BPF_In_SIO_REG_HIFREQ     (* (reg8 *) BPF_In__SIO_REG_HIFREQ)
    #define BPF_In_SIO_CFG            (* (reg8 *) BPF_In__SIO_CFG)
    #define BPF_In_SIO_DIFF           (* (reg8 *) BPF_In__SIO_DIFF)
#endif /* (BPF_In__SIO_CFG) */

/* Interrupt Registers */
#if defined(BPF_In__INTSTAT)
    #define BPF_In_INTSTAT            (* (reg8 *) BPF_In__INTSTAT)
    #define BPF_In_SNAP               (* (reg8 *) BPF_In__SNAP)
    
	#define BPF_In_0_INTTYPE_REG 		(* (reg8 *) BPF_In__0__INTTYPE)
#endif /* (BPF_In__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BPF_In_H */


/* [] END OF FILE */
