/*******************************************************************************
* File Name: cts.h  
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

#if !defined(CY_PINS_cts_H) /* Pins cts_H */
#define CY_PINS_cts_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "cts_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 cts__PORT == 15 && ((cts__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    cts_Write(uint8 value);
void    cts_SetDriveMode(uint8 mode);
uint8   cts_ReadDataReg(void);
uint8   cts_Read(void);
void    cts_SetInterruptMode(uint16 position, uint16 mode);
uint8   cts_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the cts_SetDriveMode() function.
     *  @{
     */
        #define cts_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define cts_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define cts_DM_RES_UP          PIN_DM_RES_UP
        #define cts_DM_RES_DWN         PIN_DM_RES_DWN
        #define cts_DM_OD_LO           PIN_DM_OD_LO
        #define cts_DM_OD_HI           PIN_DM_OD_HI
        #define cts_DM_STRONG          PIN_DM_STRONG
        #define cts_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define cts_MASK               cts__MASK
#define cts_SHIFT              cts__SHIFT
#define cts_WIDTH              1u

/* Interrupt constants */
#if defined(cts__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cts_SetInterruptMode() function.
     *  @{
     */
        #define cts_INTR_NONE      (uint16)(0x0000u)
        #define cts_INTR_RISING    (uint16)(0x0001u)
        #define cts_INTR_FALLING   (uint16)(0x0002u)
        #define cts_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define cts_INTR_MASK      (0x01u) 
#endif /* (cts__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define cts_PS                     (* (reg8 *) cts__PS)
/* Data Register */
#define cts_DR                     (* (reg8 *) cts__DR)
/* Port Number */
#define cts_PRT_NUM                (* (reg8 *) cts__PRT) 
/* Connect to Analog Globals */                                                  
#define cts_AG                     (* (reg8 *) cts__AG)                       
/* Analog MUX bux enable */
#define cts_AMUX                   (* (reg8 *) cts__AMUX) 
/* Bidirectional Enable */                                                        
#define cts_BIE                    (* (reg8 *) cts__BIE)
/* Bit-mask for Aliased Register Access */
#define cts_BIT_MASK               (* (reg8 *) cts__BIT_MASK)
/* Bypass Enable */
#define cts_BYP                    (* (reg8 *) cts__BYP)
/* Port wide control signals */                                                   
#define cts_CTL                    (* (reg8 *) cts__CTL)
/* Drive Modes */
#define cts_DM0                    (* (reg8 *) cts__DM0) 
#define cts_DM1                    (* (reg8 *) cts__DM1)
#define cts_DM2                    (* (reg8 *) cts__DM2) 
/* Input Buffer Disable Override */
#define cts_INP_DIS                (* (reg8 *) cts__INP_DIS)
/* LCD Common or Segment Drive */
#define cts_LCD_COM_SEG            (* (reg8 *) cts__LCD_COM_SEG)
/* Enable Segment LCD */
#define cts_LCD_EN                 (* (reg8 *) cts__LCD_EN)
/* Slew Rate Control */
#define cts_SLW                    (* (reg8 *) cts__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define cts_PRTDSI__CAPS_SEL       (* (reg8 *) cts__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define cts_PRTDSI__DBL_SYNC_IN    (* (reg8 *) cts__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define cts_PRTDSI__OE_SEL0        (* (reg8 *) cts__PRTDSI__OE_SEL0) 
#define cts_PRTDSI__OE_SEL1        (* (reg8 *) cts__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define cts_PRTDSI__OUT_SEL0       (* (reg8 *) cts__PRTDSI__OUT_SEL0) 
#define cts_PRTDSI__OUT_SEL1       (* (reg8 *) cts__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define cts_PRTDSI__SYNC_OUT       (* (reg8 *) cts__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(cts__SIO_CFG)
    #define cts_SIO_HYST_EN        (* (reg8 *) cts__SIO_HYST_EN)
    #define cts_SIO_REG_HIFREQ     (* (reg8 *) cts__SIO_REG_HIFREQ)
    #define cts_SIO_CFG            (* (reg8 *) cts__SIO_CFG)
    #define cts_SIO_DIFF           (* (reg8 *) cts__SIO_DIFF)
#endif /* (cts__SIO_CFG) */

/* Interrupt Registers */
#if defined(cts__INTSTAT)
    #define cts_INTSTAT            (* (reg8 *) cts__INTSTAT)
    #define cts_SNAP               (* (reg8 *) cts__SNAP)
    
	#define cts_0_INTTYPE_REG 		(* (reg8 *) cts__0__INTTYPE)
#endif /* (cts__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_cts_H */


/* [] END OF FILE */
