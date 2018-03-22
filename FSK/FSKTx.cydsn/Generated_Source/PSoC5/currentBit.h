/*******************************************************************************
* File Name: currentBit.h  
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

#if !defined(CY_PINS_currentBit_H) /* Pins currentBit_H */
#define CY_PINS_currentBit_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "currentBit_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 currentBit__PORT == 15 && ((currentBit__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    currentBit_Write(uint8 value);
void    currentBit_SetDriveMode(uint8 mode);
uint8   currentBit_ReadDataReg(void);
uint8   currentBit_Read(void);
void    currentBit_SetInterruptMode(uint16 position, uint16 mode);
uint8   currentBit_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the currentBit_SetDriveMode() function.
     *  @{
     */
        #define currentBit_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define currentBit_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define currentBit_DM_RES_UP          PIN_DM_RES_UP
        #define currentBit_DM_RES_DWN         PIN_DM_RES_DWN
        #define currentBit_DM_OD_LO           PIN_DM_OD_LO
        #define currentBit_DM_OD_HI           PIN_DM_OD_HI
        #define currentBit_DM_STRONG          PIN_DM_STRONG
        #define currentBit_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define currentBit_MASK               currentBit__MASK
#define currentBit_SHIFT              currentBit__SHIFT
#define currentBit_WIDTH              1u

/* Interrupt constants */
#if defined(currentBit__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in currentBit_SetInterruptMode() function.
     *  @{
     */
        #define currentBit_INTR_NONE      (uint16)(0x0000u)
        #define currentBit_INTR_RISING    (uint16)(0x0001u)
        #define currentBit_INTR_FALLING   (uint16)(0x0002u)
        #define currentBit_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define currentBit_INTR_MASK      (0x01u) 
#endif /* (currentBit__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define currentBit_PS                     (* (reg8 *) currentBit__PS)
/* Data Register */
#define currentBit_DR                     (* (reg8 *) currentBit__DR)
/* Port Number */
#define currentBit_PRT_NUM                (* (reg8 *) currentBit__PRT) 
/* Connect to Analog Globals */                                                  
#define currentBit_AG                     (* (reg8 *) currentBit__AG)                       
/* Analog MUX bux enable */
#define currentBit_AMUX                   (* (reg8 *) currentBit__AMUX) 
/* Bidirectional Enable */                                                        
#define currentBit_BIE                    (* (reg8 *) currentBit__BIE)
/* Bit-mask for Aliased Register Access */
#define currentBit_BIT_MASK               (* (reg8 *) currentBit__BIT_MASK)
/* Bypass Enable */
#define currentBit_BYP                    (* (reg8 *) currentBit__BYP)
/* Port wide control signals */                                                   
#define currentBit_CTL                    (* (reg8 *) currentBit__CTL)
/* Drive Modes */
#define currentBit_DM0                    (* (reg8 *) currentBit__DM0) 
#define currentBit_DM1                    (* (reg8 *) currentBit__DM1)
#define currentBit_DM2                    (* (reg8 *) currentBit__DM2) 
/* Input Buffer Disable Override */
#define currentBit_INP_DIS                (* (reg8 *) currentBit__INP_DIS)
/* LCD Common or Segment Drive */
#define currentBit_LCD_COM_SEG            (* (reg8 *) currentBit__LCD_COM_SEG)
/* Enable Segment LCD */
#define currentBit_LCD_EN                 (* (reg8 *) currentBit__LCD_EN)
/* Slew Rate Control */
#define currentBit_SLW                    (* (reg8 *) currentBit__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define currentBit_PRTDSI__CAPS_SEL       (* (reg8 *) currentBit__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define currentBit_PRTDSI__DBL_SYNC_IN    (* (reg8 *) currentBit__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define currentBit_PRTDSI__OE_SEL0        (* (reg8 *) currentBit__PRTDSI__OE_SEL0) 
#define currentBit_PRTDSI__OE_SEL1        (* (reg8 *) currentBit__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define currentBit_PRTDSI__OUT_SEL0       (* (reg8 *) currentBit__PRTDSI__OUT_SEL0) 
#define currentBit_PRTDSI__OUT_SEL1       (* (reg8 *) currentBit__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define currentBit_PRTDSI__SYNC_OUT       (* (reg8 *) currentBit__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(currentBit__SIO_CFG)
    #define currentBit_SIO_HYST_EN        (* (reg8 *) currentBit__SIO_HYST_EN)
    #define currentBit_SIO_REG_HIFREQ     (* (reg8 *) currentBit__SIO_REG_HIFREQ)
    #define currentBit_SIO_CFG            (* (reg8 *) currentBit__SIO_CFG)
    #define currentBit_SIO_DIFF           (* (reg8 *) currentBit__SIO_DIFF)
#endif /* (currentBit__SIO_CFG) */

/* Interrupt Registers */
#if defined(currentBit__INTSTAT)
    #define currentBit_INTSTAT            (* (reg8 *) currentBit__INTSTAT)
    #define currentBit_SNAP               (* (reg8 *) currentBit__SNAP)
    
	#define currentBit_0_INTTYPE_REG 		(* (reg8 *) currentBit__0__INTTYPE)
#endif /* (currentBit__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_currentBit_H */


/* [] END OF FILE */
