/*******************************************************************************
* File Name: bitStream.h  
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

#if !defined(CY_PINS_bitStream_H) /* Pins bitStream_H */
#define CY_PINS_bitStream_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bitStream_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bitStream__PORT == 15 && ((bitStream__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bitStream_Write(uint8 value);
void    bitStream_SetDriveMode(uint8 mode);
uint8   bitStream_ReadDataReg(void);
uint8   bitStream_Read(void);
void    bitStream_SetInterruptMode(uint16 position, uint16 mode);
uint8   bitStream_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bitStream_SetDriveMode() function.
     *  @{
     */
        #define bitStream_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bitStream_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bitStream_DM_RES_UP          PIN_DM_RES_UP
        #define bitStream_DM_RES_DWN         PIN_DM_RES_DWN
        #define bitStream_DM_OD_LO           PIN_DM_OD_LO
        #define bitStream_DM_OD_HI           PIN_DM_OD_HI
        #define bitStream_DM_STRONG          PIN_DM_STRONG
        #define bitStream_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bitStream_MASK               bitStream__MASK
#define bitStream_SHIFT              bitStream__SHIFT
#define bitStream_WIDTH              1u

/* Interrupt constants */
#if defined(bitStream__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bitStream_SetInterruptMode() function.
     *  @{
     */
        #define bitStream_INTR_NONE      (uint16)(0x0000u)
        #define bitStream_INTR_RISING    (uint16)(0x0001u)
        #define bitStream_INTR_FALLING   (uint16)(0x0002u)
        #define bitStream_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bitStream_INTR_MASK      (0x01u) 
#endif /* (bitStream__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bitStream_PS                     (* (reg8 *) bitStream__PS)
/* Data Register */
#define bitStream_DR                     (* (reg8 *) bitStream__DR)
/* Port Number */
#define bitStream_PRT_NUM                (* (reg8 *) bitStream__PRT) 
/* Connect to Analog Globals */                                                  
#define bitStream_AG                     (* (reg8 *) bitStream__AG)                       
/* Analog MUX bux enable */
#define bitStream_AMUX                   (* (reg8 *) bitStream__AMUX) 
/* Bidirectional Enable */                                                        
#define bitStream_BIE                    (* (reg8 *) bitStream__BIE)
/* Bit-mask for Aliased Register Access */
#define bitStream_BIT_MASK               (* (reg8 *) bitStream__BIT_MASK)
/* Bypass Enable */
#define bitStream_BYP                    (* (reg8 *) bitStream__BYP)
/* Port wide control signals */                                                   
#define bitStream_CTL                    (* (reg8 *) bitStream__CTL)
/* Drive Modes */
#define bitStream_DM0                    (* (reg8 *) bitStream__DM0) 
#define bitStream_DM1                    (* (reg8 *) bitStream__DM1)
#define bitStream_DM2                    (* (reg8 *) bitStream__DM2) 
/* Input Buffer Disable Override */
#define bitStream_INP_DIS                (* (reg8 *) bitStream__INP_DIS)
/* LCD Common or Segment Drive */
#define bitStream_LCD_COM_SEG            (* (reg8 *) bitStream__LCD_COM_SEG)
/* Enable Segment LCD */
#define bitStream_LCD_EN                 (* (reg8 *) bitStream__LCD_EN)
/* Slew Rate Control */
#define bitStream_SLW                    (* (reg8 *) bitStream__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bitStream_PRTDSI__CAPS_SEL       (* (reg8 *) bitStream__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bitStream_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bitStream__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bitStream_PRTDSI__OE_SEL0        (* (reg8 *) bitStream__PRTDSI__OE_SEL0) 
#define bitStream_PRTDSI__OE_SEL1        (* (reg8 *) bitStream__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bitStream_PRTDSI__OUT_SEL0       (* (reg8 *) bitStream__PRTDSI__OUT_SEL0) 
#define bitStream_PRTDSI__OUT_SEL1       (* (reg8 *) bitStream__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bitStream_PRTDSI__SYNC_OUT       (* (reg8 *) bitStream__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bitStream__SIO_CFG)
    #define bitStream_SIO_HYST_EN        (* (reg8 *) bitStream__SIO_HYST_EN)
    #define bitStream_SIO_REG_HIFREQ     (* (reg8 *) bitStream__SIO_REG_HIFREQ)
    #define bitStream_SIO_CFG            (* (reg8 *) bitStream__SIO_CFG)
    #define bitStream_SIO_DIFF           (* (reg8 *) bitStream__SIO_DIFF)
#endif /* (bitStream__SIO_CFG) */

/* Interrupt Registers */
#if defined(bitStream__INTSTAT)
    #define bitStream_INTSTAT            (* (reg8 *) bitStream__INTSTAT)
    #define bitStream_SNAP               (* (reg8 *) bitStream__SNAP)
    
	#define bitStream_0_INTTYPE_REG 		(* (reg8 *) bitStream__0__INTTYPE)
#endif /* (bitStream__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bitStream_H */


/* [] END OF FILE */
