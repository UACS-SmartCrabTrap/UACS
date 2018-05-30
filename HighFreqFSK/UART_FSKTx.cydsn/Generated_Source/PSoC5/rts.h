/*******************************************************************************
* File Name: rts.h  
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

#if !defined(CY_PINS_rts_H) /* Pins rts_H */
#define CY_PINS_rts_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "rts_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 rts__PORT == 15 && ((rts__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    rts_Write(uint8 value);
void    rts_SetDriveMode(uint8 mode);
uint8   rts_ReadDataReg(void);
uint8   rts_Read(void);
void    rts_SetInterruptMode(uint16 position, uint16 mode);
uint8   rts_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the rts_SetDriveMode() function.
     *  @{
     */
        #define rts_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define rts_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define rts_DM_RES_UP          PIN_DM_RES_UP
        #define rts_DM_RES_DWN         PIN_DM_RES_DWN
        #define rts_DM_OD_LO           PIN_DM_OD_LO
        #define rts_DM_OD_HI           PIN_DM_OD_HI
        #define rts_DM_STRONG          PIN_DM_STRONG
        #define rts_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define rts_MASK               rts__MASK
#define rts_SHIFT              rts__SHIFT
#define rts_WIDTH              1u

/* Interrupt constants */
#if defined(rts__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in rts_SetInterruptMode() function.
     *  @{
     */
        #define rts_INTR_NONE      (uint16)(0x0000u)
        #define rts_INTR_RISING    (uint16)(0x0001u)
        #define rts_INTR_FALLING   (uint16)(0x0002u)
        #define rts_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define rts_INTR_MASK      (0x01u) 
#endif /* (rts__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define rts_PS                     (* (reg8 *) rts__PS)
/* Data Register */
#define rts_DR                     (* (reg8 *) rts__DR)
/* Port Number */
#define rts_PRT_NUM                (* (reg8 *) rts__PRT) 
/* Connect to Analog Globals */                                                  
#define rts_AG                     (* (reg8 *) rts__AG)                       
/* Analog MUX bux enable */
#define rts_AMUX                   (* (reg8 *) rts__AMUX) 
/* Bidirectional Enable */                                                        
#define rts_BIE                    (* (reg8 *) rts__BIE)
/* Bit-mask for Aliased Register Access */
#define rts_BIT_MASK               (* (reg8 *) rts__BIT_MASK)
/* Bypass Enable */
#define rts_BYP                    (* (reg8 *) rts__BYP)
/* Port wide control signals */                                                   
#define rts_CTL                    (* (reg8 *) rts__CTL)
/* Drive Modes */
#define rts_DM0                    (* (reg8 *) rts__DM0) 
#define rts_DM1                    (* (reg8 *) rts__DM1)
#define rts_DM2                    (* (reg8 *) rts__DM2) 
/* Input Buffer Disable Override */
#define rts_INP_DIS                (* (reg8 *) rts__INP_DIS)
/* LCD Common or Segment Drive */
#define rts_LCD_COM_SEG            (* (reg8 *) rts__LCD_COM_SEG)
/* Enable Segment LCD */
#define rts_LCD_EN                 (* (reg8 *) rts__LCD_EN)
/* Slew Rate Control */
#define rts_SLW                    (* (reg8 *) rts__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define rts_PRTDSI__CAPS_SEL       (* (reg8 *) rts__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define rts_PRTDSI__DBL_SYNC_IN    (* (reg8 *) rts__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define rts_PRTDSI__OE_SEL0        (* (reg8 *) rts__PRTDSI__OE_SEL0) 
#define rts_PRTDSI__OE_SEL1        (* (reg8 *) rts__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define rts_PRTDSI__OUT_SEL0       (* (reg8 *) rts__PRTDSI__OUT_SEL0) 
#define rts_PRTDSI__OUT_SEL1       (* (reg8 *) rts__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define rts_PRTDSI__SYNC_OUT       (* (reg8 *) rts__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(rts__SIO_CFG)
    #define rts_SIO_HYST_EN        (* (reg8 *) rts__SIO_HYST_EN)
    #define rts_SIO_REG_HIFREQ     (* (reg8 *) rts__SIO_REG_HIFREQ)
    #define rts_SIO_CFG            (* (reg8 *) rts__SIO_CFG)
    #define rts_SIO_DIFF           (* (reg8 *) rts__SIO_DIFF)
#endif /* (rts__SIO_CFG) */

/* Interrupt Registers */
#if defined(rts__INTSTAT)
    #define rts_INTSTAT            (* (reg8 *) rts__INTSTAT)
    #define rts_SNAP               (* (reg8 *) rts__SNAP)
    
	#define rts_0_INTTYPE_REG 		(* (reg8 *) rts__0__INTTYPE)
#endif /* (rts__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_rts_H */


/* [] END OF FILE */
