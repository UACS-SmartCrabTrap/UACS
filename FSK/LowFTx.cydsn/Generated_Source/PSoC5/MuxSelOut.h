/*******************************************************************************
* File Name: MuxSelOut.h  
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

#if !defined(CY_PINS_MuxSelOut_H) /* Pins MuxSelOut_H */
#define CY_PINS_MuxSelOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MuxSelOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MuxSelOut__PORT == 15 && ((MuxSelOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MuxSelOut_Write(uint8 value);
void    MuxSelOut_SetDriveMode(uint8 mode);
uint8   MuxSelOut_ReadDataReg(void);
uint8   MuxSelOut_Read(void);
void    MuxSelOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   MuxSelOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MuxSelOut_SetDriveMode() function.
     *  @{
     */
        #define MuxSelOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MuxSelOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MuxSelOut_DM_RES_UP          PIN_DM_RES_UP
        #define MuxSelOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define MuxSelOut_DM_OD_LO           PIN_DM_OD_LO
        #define MuxSelOut_DM_OD_HI           PIN_DM_OD_HI
        #define MuxSelOut_DM_STRONG          PIN_DM_STRONG
        #define MuxSelOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MuxSelOut_MASK               MuxSelOut__MASK
#define MuxSelOut_SHIFT              MuxSelOut__SHIFT
#define MuxSelOut_WIDTH              1u

/* Interrupt constants */
#if defined(MuxSelOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MuxSelOut_SetInterruptMode() function.
     *  @{
     */
        #define MuxSelOut_INTR_NONE      (uint16)(0x0000u)
        #define MuxSelOut_INTR_RISING    (uint16)(0x0001u)
        #define MuxSelOut_INTR_FALLING   (uint16)(0x0002u)
        #define MuxSelOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MuxSelOut_INTR_MASK      (0x01u) 
#endif /* (MuxSelOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MuxSelOut_PS                     (* (reg8 *) MuxSelOut__PS)
/* Data Register */
#define MuxSelOut_DR                     (* (reg8 *) MuxSelOut__DR)
/* Port Number */
#define MuxSelOut_PRT_NUM                (* (reg8 *) MuxSelOut__PRT) 
/* Connect to Analog Globals */                                                  
#define MuxSelOut_AG                     (* (reg8 *) MuxSelOut__AG)                       
/* Analog MUX bux enable */
#define MuxSelOut_AMUX                   (* (reg8 *) MuxSelOut__AMUX) 
/* Bidirectional Enable */                                                        
#define MuxSelOut_BIE                    (* (reg8 *) MuxSelOut__BIE)
/* Bit-mask for Aliased Register Access */
#define MuxSelOut_BIT_MASK               (* (reg8 *) MuxSelOut__BIT_MASK)
/* Bypass Enable */
#define MuxSelOut_BYP                    (* (reg8 *) MuxSelOut__BYP)
/* Port wide control signals */                                                   
#define MuxSelOut_CTL                    (* (reg8 *) MuxSelOut__CTL)
/* Drive Modes */
#define MuxSelOut_DM0                    (* (reg8 *) MuxSelOut__DM0) 
#define MuxSelOut_DM1                    (* (reg8 *) MuxSelOut__DM1)
#define MuxSelOut_DM2                    (* (reg8 *) MuxSelOut__DM2) 
/* Input Buffer Disable Override */
#define MuxSelOut_INP_DIS                (* (reg8 *) MuxSelOut__INP_DIS)
/* LCD Common or Segment Drive */
#define MuxSelOut_LCD_COM_SEG            (* (reg8 *) MuxSelOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define MuxSelOut_LCD_EN                 (* (reg8 *) MuxSelOut__LCD_EN)
/* Slew Rate Control */
#define MuxSelOut_SLW                    (* (reg8 *) MuxSelOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MuxSelOut_PRTDSI__CAPS_SEL       (* (reg8 *) MuxSelOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MuxSelOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MuxSelOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MuxSelOut_PRTDSI__OE_SEL0        (* (reg8 *) MuxSelOut__PRTDSI__OE_SEL0) 
#define MuxSelOut_PRTDSI__OE_SEL1        (* (reg8 *) MuxSelOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MuxSelOut_PRTDSI__OUT_SEL0       (* (reg8 *) MuxSelOut__PRTDSI__OUT_SEL0) 
#define MuxSelOut_PRTDSI__OUT_SEL1       (* (reg8 *) MuxSelOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MuxSelOut_PRTDSI__SYNC_OUT       (* (reg8 *) MuxSelOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MuxSelOut__SIO_CFG)
    #define MuxSelOut_SIO_HYST_EN        (* (reg8 *) MuxSelOut__SIO_HYST_EN)
    #define MuxSelOut_SIO_REG_HIFREQ     (* (reg8 *) MuxSelOut__SIO_REG_HIFREQ)
    #define MuxSelOut_SIO_CFG            (* (reg8 *) MuxSelOut__SIO_CFG)
    #define MuxSelOut_SIO_DIFF           (* (reg8 *) MuxSelOut__SIO_DIFF)
#endif /* (MuxSelOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(MuxSelOut__INTSTAT)
    #define MuxSelOut_INTSTAT            (* (reg8 *) MuxSelOut__INTSTAT)
    #define MuxSelOut_SNAP               (* (reg8 *) MuxSelOut__SNAP)
    
	#define MuxSelOut_0_INTTYPE_REG 		(* (reg8 *) MuxSelOut__0__INTTYPE)
#endif /* (MuxSelOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MuxSelOut_H */


/* [] END OF FILE */
