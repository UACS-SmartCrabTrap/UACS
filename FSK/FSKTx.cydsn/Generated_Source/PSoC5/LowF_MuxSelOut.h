/*******************************************************************************
* File Name: LowF_MuxSelOut.h  
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

#if !defined(CY_PINS_LowF_MuxSelOut_H) /* Pins LowF_MuxSelOut_H */
#define CY_PINS_LowF_MuxSelOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LowF_MuxSelOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LowF_MuxSelOut__PORT == 15 && ((LowF_MuxSelOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LowF_MuxSelOut_Write(uint8 value);
void    LowF_MuxSelOut_SetDriveMode(uint8 mode);
uint8   LowF_MuxSelOut_ReadDataReg(void);
uint8   LowF_MuxSelOut_Read(void);
void    LowF_MuxSelOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   LowF_MuxSelOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LowF_MuxSelOut_SetDriveMode() function.
     *  @{
     */
        #define LowF_MuxSelOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LowF_MuxSelOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LowF_MuxSelOut_DM_RES_UP          PIN_DM_RES_UP
        #define LowF_MuxSelOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define LowF_MuxSelOut_DM_OD_LO           PIN_DM_OD_LO
        #define LowF_MuxSelOut_DM_OD_HI           PIN_DM_OD_HI
        #define LowF_MuxSelOut_DM_STRONG          PIN_DM_STRONG
        #define LowF_MuxSelOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LowF_MuxSelOut_MASK               LowF_MuxSelOut__MASK
#define LowF_MuxSelOut_SHIFT              LowF_MuxSelOut__SHIFT
#define LowF_MuxSelOut_WIDTH              1u

/* Interrupt constants */
#if defined(LowF_MuxSelOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LowF_MuxSelOut_SetInterruptMode() function.
     *  @{
     */
        #define LowF_MuxSelOut_INTR_NONE      (uint16)(0x0000u)
        #define LowF_MuxSelOut_INTR_RISING    (uint16)(0x0001u)
        #define LowF_MuxSelOut_INTR_FALLING   (uint16)(0x0002u)
        #define LowF_MuxSelOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LowF_MuxSelOut_INTR_MASK      (0x01u) 
#endif /* (LowF_MuxSelOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LowF_MuxSelOut_PS                     (* (reg8 *) LowF_MuxSelOut__PS)
/* Data Register */
#define LowF_MuxSelOut_DR                     (* (reg8 *) LowF_MuxSelOut__DR)
/* Port Number */
#define LowF_MuxSelOut_PRT_NUM                (* (reg8 *) LowF_MuxSelOut__PRT) 
/* Connect to Analog Globals */                                                  
#define LowF_MuxSelOut_AG                     (* (reg8 *) LowF_MuxSelOut__AG)                       
/* Analog MUX bux enable */
#define LowF_MuxSelOut_AMUX                   (* (reg8 *) LowF_MuxSelOut__AMUX) 
/* Bidirectional Enable */                                                        
#define LowF_MuxSelOut_BIE                    (* (reg8 *) LowF_MuxSelOut__BIE)
/* Bit-mask for Aliased Register Access */
#define LowF_MuxSelOut_BIT_MASK               (* (reg8 *) LowF_MuxSelOut__BIT_MASK)
/* Bypass Enable */
#define LowF_MuxSelOut_BYP                    (* (reg8 *) LowF_MuxSelOut__BYP)
/* Port wide control signals */                                                   
#define LowF_MuxSelOut_CTL                    (* (reg8 *) LowF_MuxSelOut__CTL)
/* Drive Modes */
#define LowF_MuxSelOut_DM0                    (* (reg8 *) LowF_MuxSelOut__DM0) 
#define LowF_MuxSelOut_DM1                    (* (reg8 *) LowF_MuxSelOut__DM1)
#define LowF_MuxSelOut_DM2                    (* (reg8 *) LowF_MuxSelOut__DM2) 
/* Input Buffer Disable Override */
#define LowF_MuxSelOut_INP_DIS                (* (reg8 *) LowF_MuxSelOut__INP_DIS)
/* LCD Common or Segment Drive */
#define LowF_MuxSelOut_LCD_COM_SEG            (* (reg8 *) LowF_MuxSelOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define LowF_MuxSelOut_LCD_EN                 (* (reg8 *) LowF_MuxSelOut__LCD_EN)
/* Slew Rate Control */
#define LowF_MuxSelOut_SLW                    (* (reg8 *) LowF_MuxSelOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LowF_MuxSelOut_PRTDSI__CAPS_SEL       (* (reg8 *) LowF_MuxSelOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LowF_MuxSelOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LowF_MuxSelOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LowF_MuxSelOut_PRTDSI__OE_SEL0        (* (reg8 *) LowF_MuxSelOut__PRTDSI__OE_SEL0) 
#define LowF_MuxSelOut_PRTDSI__OE_SEL1        (* (reg8 *) LowF_MuxSelOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LowF_MuxSelOut_PRTDSI__OUT_SEL0       (* (reg8 *) LowF_MuxSelOut__PRTDSI__OUT_SEL0) 
#define LowF_MuxSelOut_PRTDSI__OUT_SEL1       (* (reg8 *) LowF_MuxSelOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LowF_MuxSelOut_PRTDSI__SYNC_OUT       (* (reg8 *) LowF_MuxSelOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LowF_MuxSelOut__SIO_CFG)
    #define LowF_MuxSelOut_SIO_HYST_EN        (* (reg8 *) LowF_MuxSelOut__SIO_HYST_EN)
    #define LowF_MuxSelOut_SIO_REG_HIFREQ     (* (reg8 *) LowF_MuxSelOut__SIO_REG_HIFREQ)
    #define LowF_MuxSelOut_SIO_CFG            (* (reg8 *) LowF_MuxSelOut__SIO_CFG)
    #define LowF_MuxSelOut_SIO_DIFF           (* (reg8 *) LowF_MuxSelOut__SIO_DIFF)
#endif /* (LowF_MuxSelOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(LowF_MuxSelOut__INTSTAT)
    #define LowF_MuxSelOut_INTSTAT            (* (reg8 *) LowF_MuxSelOut__INTSTAT)
    #define LowF_MuxSelOut_SNAP               (* (reg8 *) LowF_MuxSelOut__SNAP)
    
	#define LowF_MuxSelOut_0_INTTYPE_REG 		(* (reg8 *) LowF_MuxSelOut__0__INTTYPE)
#endif /* (LowF_MuxSelOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LowF_MuxSelOut_H */


/* [] END OF FILE */
