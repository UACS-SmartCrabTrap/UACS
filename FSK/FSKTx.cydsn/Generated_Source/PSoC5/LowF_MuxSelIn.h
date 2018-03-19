/*******************************************************************************
* File Name: LowF_MuxSelIn.h  
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

#if !defined(CY_PINS_LowF_MuxSelIn_H) /* Pins LowF_MuxSelIn_H */
#define CY_PINS_LowF_MuxSelIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LowF_MuxSelIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LowF_MuxSelIn__PORT == 15 && ((LowF_MuxSelIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LowF_MuxSelIn_Write(uint8 value);
void    LowF_MuxSelIn_SetDriveMode(uint8 mode);
uint8   LowF_MuxSelIn_ReadDataReg(void);
uint8   LowF_MuxSelIn_Read(void);
void    LowF_MuxSelIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   LowF_MuxSelIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LowF_MuxSelIn_SetDriveMode() function.
     *  @{
     */
        #define LowF_MuxSelIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LowF_MuxSelIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LowF_MuxSelIn_DM_RES_UP          PIN_DM_RES_UP
        #define LowF_MuxSelIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define LowF_MuxSelIn_DM_OD_LO           PIN_DM_OD_LO
        #define LowF_MuxSelIn_DM_OD_HI           PIN_DM_OD_HI
        #define LowF_MuxSelIn_DM_STRONG          PIN_DM_STRONG
        #define LowF_MuxSelIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LowF_MuxSelIn_MASK               LowF_MuxSelIn__MASK
#define LowF_MuxSelIn_SHIFT              LowF_MuxSelIn__SHIFT
#define LowF_MuxSelIn_WIDTH              1u

/* Interrupt constants */
#if defined(LowF_MuxSelIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LowF_MuxSelIn_SetInterruptMode() function.
     *  @{
     */
        #define LowF_MuxSelIn_INTR_NONE      (uint16)(0x0000u)
        #define LowF_MuxSelIn_INTR_RISING    (uint16)(0x0001u)
        #define LowF_MuxSelIn_INTR_FALLING   (uint16)(0x0002u)
        #define LowF_MuxSelIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LowF_MuxSelIn_INTR_MASK      (0x01u) 
#endif /* (LowF_MuxSelIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LowF_MuxSelIn_PS                     (* (reg8 *) LowF_MuxSelIn__PS)
/* Data Register */
#define LowF_MuxSelIn_DR                     (* (reg8 *) LowF_MuxSelIn__DR)
/* Port Number */
#define LowF_MuxSelIn_PRT_NUM                (* (reg8 *) LowF_MuxSelIn__PRT) 
/* Connect to Analog Globals */                                                  
#define LowF_MuxSelIn_AG                     (* (reg8 *) LowF_MuxSelIn__AG)                       
/* Analog MUX bux enable */
#define LowF_MuxSelIn_AMUX                   (* (reg8 *) LowF_MuxSelIn__AMUX) 
/* Bidirectional Enable */                                                        
#define LowF_MuxSelIn_BIE                    (* (reg8 *) LowF_MuxSelIn__BIE)
/* Bit-mask for Aliased Register Access */
#define LowF_MuxSelIn_BIT_MASK               (* (reg8 *) LowF_MuxSelIn__BIT_MASK)
/* Bypass Enable */
#define LowF_MuxSelIn_BYP                    (* (reg8 *) LowF_MuxSelIn__BYP)
/* Port wide control signals */                                                   
#define LowF_MuxSelIn_CTL                    (* (reg8 *) LowF_MuxSelIn__CTL)
/* Drive Modes */
#define LowF_MuxSelIn_DM0                    (* (reg8 *) LowF_MuxSelIn__DM0) 
#define LowF_MuxSelIn_DM1                    (* (reg8 *) LowF_MuxSelIn__DM1)
#define LowF_MuxSelIn_DM2                    (* (reg8 *) LowF_MuxSelIn__DM2) 
/* Input Buffer Disable Override */
#define LowF_MuxSelIn_INP_DIS                (* (reg8 *) LowF_MuxSelIn__INP_DIS)
/* LCD Common or Segment Drive */
#define LowF_MuxSelIn_LCD_COM_SEG            (* (reg8 *) LowF_MuxSelIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define LowF_MuxSelIn_LCD_EN                 (* (reg8 *) LowF_MuxSelIn__LCD_EN)
/* Slew Rate Control */
#define LowF_MuxSelIn_SLW                    (* (reg8 *) LowF_MuxSelIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LowF_MuxSelIn_PRTDSI__CAPS_SEL       (* (reg8 *) LowF_MuxSelIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LowF_MuxSelIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LowF_MuxSelIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LowF_MuxSelIn_PRTDSI__OE_SEL0        (* (reg8 *) LowF_MuxSelIn__PRTDSI__OE_SEL0) 
#define LowF_MuxSelIn_PRTDSI__OE_SEL1        (* (reg8 *) LowF_MuxSelIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LowF_MuxSelIn_PRTDSI__OUT_SEL0       (* (reg8 *) LowF_MuxSelIn__PRTDSI__OUT_SEL0) 
#define LowF_MuxSelIn_PRTDSI__OUT_SEL1       (* (reg8 *) LowF_MuxSelIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LowF_MuxSelIn_PRTDSI__SYNC_OUT       (* (reg8 *) LowF_MuxSelIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LowF_MuxSelIn__SIO_CFG)
    #define LowF_MuxSelIn_SIO_HYST_EN        (* (reg8 *) LowF_MuxSelIn__SIO_HYST_EN)
    #define LowF_MuxSelIn_SIO_REG_HIFREQ     (* (reg8 *) LowF_MuxSelIn__SIO_REG_HIFREQ)
    #define LowF_MuxSelIn_SIO_CFG            (* (reg8 *) LowF_MuxSelIn__SIO_CFG)
    #define LowF_MuxSelIn_SIO_DIFF           (* (reg8 *) LowF_MuxSelIn__SIO_DIFF)
#endif /* (LowF_MuxSelIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(LowF_MuxSelIn__INTSTAT)
    #define LowF_MuxSelIn_INTSTAT            (* (reg8 *) LowF_MuxSelIn__INTSTAT)
    #define LowF_MuxSelIn_SNAP               (* (reg8 *) LowF_MuxSelIn__SNAP)
    
	#define LowF_MuxSelIn_0_INTTYPE_REG 		(* (reg8 *) LowF_MuxSelIn__0__INTTYPE)
#endif /* (LowF_MuxSelIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LowF_MuxSelIn_H */


/* [] END OF FILE */
