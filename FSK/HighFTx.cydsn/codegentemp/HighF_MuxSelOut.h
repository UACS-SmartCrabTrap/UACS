/*******************************************************************************
* File Name: HighF_MuxSelOut.h  
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

#if !defined(CY_PINS_HighF_MuxSelOut_H) /* Pins HighF_MuxSelOut_H */
#define CY_PINS_HighF_MuxSelOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HighF_MuxSelOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HighF_MuxSelOut__PORT == 15 && ((HighF_MuxSelOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HighF_MuxSelOut_Write(uint8 value);
void    HighF_MuxSelOut_SetDriveMode(uint8 mode);
uint8   HighF_MuxSelOut_ReadDataReg(void);
uint8   HighF_MuxSelOut_Read(void);
void    HighF_MuxSelOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   HighF_MuxSelOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HighF_MuxSelOut_SetDriveMode() function.
     *  @{
     */
        #define HighF_MuxSelOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HighF_MuxSelOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HighF_MuxSelOut_DM_RES_UP          PIN_DM_RES_UP
        #define HighF_MuxSelOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define HighF_MuxSelOut_DM_OD_LO           PIN_DM_OD_LO
        #define HighF_MuxSelOut_DM_OD_HI           PIN_DM_OD_HI
        #define HighF_MuxSelOut_DM_STRONG          PIN_DM_STRONG
        #define HighF_MuxSelOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HighF_MuxSelOut_MASK               HighF_MuxSelOut__MASK
#define HighF_MuxSelOut_SHIFT              HighF_MuxSelOut__SHIFT
#define HighF_MuxSelOut_WIDTH              1u

/* Interrupt constants */
#if defined(HighF_MuxSelOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HighF_MuxSelOut_SetInterruptMode() function.
     *  @{
     */
        #define HighF_MuxSelOut_INTR_NONE      (uint16)(0x0000u)
        #define HighF_MuxSelOut_INTR_RISING    (uint16)(0x0001u)
        #define HighF_MuxSelOut_INTR_FALLING   (uint16)(0x0002u)
        #define HighF_MuxSelOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HighF_MuxSelOut_INTR_MASK      (0x01u) 
#endif /* (HighF_MuxSelOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HighF_MuxSelOut_PS                     (* (reg8 *) HighF_MuxSelOut__PS)
/* Data Register */
#define HighF_MuxSelOut_DR                     (* (reg8 *) HighF_MuxSelOut__DR)
/* Port Number */
#define HighF_MuxSelOut_PRT_NUM                (* (reg8 *) HighF_MuxSelOut__PRT) 
/* Connect to Analog Globals */                                                  
#define HighF_MuxSelOut_AG                     (* (reg8 *) HighF_MuxSelOut__AG)                       
/* Analog MUX bux enable */
#define HighF_MuxSelOut_AMUX                   (* (reg8 *) HighF_MuxSelOut__AMUX) 
/* Bidirectional Enable */                                                        
#define HighF_MuxSelOut_BIE                    (* (reg8 *) HighF_MuxSelOut__BIE)
/* Bit-mask for Aliased Register Access */
#define HighF_MuxSelOut_BIT_MASK               (* (reg8 *) HighF_MuxSelOut__BIT_MASK)
/* Bypass Enable */
#define HighF_MuxSelOut_BYP                    (* (reg8 *) HighF_MuxSelOut__BYP)
/* Port wide control signals */                                                   
#define HighF_MuxSelOut_CTL                    (* (reg8 *) HighF_MuxSelOut__CTL)
/* Drive Modes */
#define HighF_MuxSelOut_DM0                    (* (reg8 *) HighF_MuxSelOut__DM0) 
#define HighF_MuxSelOut_DM1                    (* (reg8 *) HighF_MuxSelOut__DM1)
#define HighF_MuxSelOut_DM2                    (* (reg8 *) HighF_MuxSelOut__DM2) 
/* Input Buffer Disable Override */
#define HighF_MuxSelOut_INP_DIS                (* (reg8 *) HighF_MuxSelOut__INP_DIS)
/* LCD Common or Segment Drive */
#define HighF_MuxSelOut_LCD_COM_SEG            (* (reg8 *) HighF_MuxSelOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define HighF_MuxSelOut_LCD_EN                 (* (reg8 *) HighF_MuxSelOut__LCD_EN)
/* Slew Rate Control */
#define HighF_MuxSelOut_SLW                    (* (reg8 *) HighF_MuxSelOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HighF_MuxSelOut_PRTDSI__CAPS_SEL       (* (reg8 *) HighF_MuxSelOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HighF_MuxSelOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HighF_MuxSelOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HighF_MuxSelOut_PRTDSI__OE_SEL0        (* (reg8 *) HighF_MuxSelOut__PRTDSI__OE_SEL0) 
#define HighF_MuxSelOut_PRTDSI__OE_SEL1        (* (reg8 *) HighF_MuxSelOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HighF_MuxSelOut_PRTDSI__OUT_SEL0       (* (reg8 *) HighF_MuxSelOut__PRTDSI__OUT_SEL0) 
#define HighF_MuxSelOut_PRTDSI__OUT_SEL1       (* (reg8 *) HighF_MuxSelOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HighF_MuxSelOut_PRTDSI__SYNC_OUT       (* (reg8 *) HighF_MuxSelOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HighF_MuxSelOut__SIO_CFG)
    #define HighF_MuxSelOut_SIO_HYST_EN        (* (reg8 *) HighF_MuxSelOut__SIO_HYST_EN)
    #define HighF_MuxSelOut_SIO_REG_HIFREQ     (* (reg8 *) HighF_MuxSelOut__SIO_REG_HIFREQ)
    #define HighF_MuxSelOut_SIO_CFG            (* (reg8 *) HighF_MuxSelOut__SIO_CFG)
    #define HighF_MuxSelOut_SIO_DIFF           (* (reg8 *) HighF_MuxSelOut__SIO_DIFF)
#endif /* (HighF_MuxSelOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(HighF_MuxSelOut__INTSTAT)
    #define HighF_MuxSelOut_INTSTAT            (* (reg8 *) HighF_MuxSelOut__INTSTAT)
    #define HighF_MuxSelOut_SNAP               (* (reg8 *) HighF_MuxSelOut__SNAP)
    
	#define HighF_MuxSelOut_0_INTTYPE_REG 		(* (reg8 *) HighF_MuxSelOut__0__INTTYPE)
#endif /* (HighF_MuxSelOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HighF_MuxSelOut_H */


/* [] END OF FILE */
