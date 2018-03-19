/*******************************************************************************
* File Name: HighF_CompOut.h  
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

#if !defined(CY_PINS_HighF_CompOut_H) /* Pins HighF_CompOut_H */
#define CY_PINS_HighF_CompOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HighF_CompOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HighF_CompOut__PORT == 15 && ((HighF_CompOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HighF_CompOut_Write(uint8 value);
void    HighF_CompOut_SetDriveMode(uint8 mode);
uint8   HighF_CompOut_ReadDataReg(void);
uint8   HighF_CompOut_Read(void);
void    HighF_CompOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   HighF_CompOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HighF_CompOut_SetDriveMode() function.
     *  @{
     */
        #define HighF_CompOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HighF_CompOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HighF_CompOut_DM_RES_UP          PIN_DM_RES_UP
        #define HighF_CompOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define HighF_CompOut_DM_OD_LO           PIN_DM_OD_LO
        #define HighF_CompOut_DM_OD_HI           PIN_DM_OD_HI
        #define HighF_CompOut_DM_STRONG          PIN_DM_STRONG
        #define HighF_CompOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HighF_CompOut_MASK               HighF_CompOut__MASK
#define HighF_CompOut_SHIFT              HighF_CompOut__SHIFT
#define HighF_CompOut_WIDTH              1u

/* Interrupt constants */
#if defined(HighF_CompOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HighF_CompOut_SetInterruptMode() function.
     *  @{
     */
        #define HighF_CompOut_INTR_NONE      (uint16)(0x0000u)
        #define HighF_CompOut_INTR_RISING    (uint16)(0x0001u)
        #define HighF_CompOut_INTR_FALLING   (uint16)(0x0002u)
        #define HighF_CompOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HighF_CompOut_INTR_MASK      (0x01u) 
#endif /* (HighF_CompOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HighF_CompOut_PS                     (* (reg8 *) HighF_CompOut__PS)
/* Data Register */
#define HighF_CompOut_DR                     (* (reg8 *) HighF_CompOut__DR)
/* Port Number */
#define HighF_CompOut_PRT_NUM                (* (reg8 *) HighF_CompOut__PRT) 
/* Connect to Analog Globals */                                                  
#define HighF_CompOut_AG                     (* (reg8 *) HighF_CompOut__AG)                       
/* Analog MUX bux enable */
#define HighF_CompOut_AMUX                   (* (reg8 *) HighF_CompOut__AMUX) 
/* Bidirectional Enable */                                                        
#define HighF_CompOut_BIE                    (* (reg8 *) HighF_CompOut__BIE)
/* Bit-mask for Aliased Register Access */
#define HighF_CompOut_BIT_MASK               (* (reg8 *) HighF_CompOut__BIT_MASK)
/* Bypass Enable */
#define HighF_CompOut_BYP                    (* (reg8 *) HighF_CompOut__BYP)
/* Port wide control signals */                                                   
#define HighF_CompOut_CTL                    (* (reg8 *) HighF_CompOut__CTL)
/* Drive Modes */
#define HighF_CompOut_DM0                    (* (reg8 *) HighF_CompOut__DM0) 
#define HighF_CompOut_DM1                    (* (reg8 *) HighF_CompOut__DM1)
#define HighF_CompOut_DM2                    (* (reg8 *) HighF_CompOut__DM2) 
/* Input Buffer Disable Override */
#define HighF_CompOut_INP_DIS                (* (reg8 *) HighF_CompOut__INP_DIS)
/* LCD Common or Segment Drive */
#define HighF_CompOut_LCD_COM_SEG            (* (reg8 *) HighF_CompOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define HighF_CompOut_LCD_EN                 (* (reg8 *) HighF_CompOut__LCD_EN)
/* Slew Rate Control */
#define HighF_CompOut_SLW                    (* (reg8 *) HighF_CompOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HighF_CompOut_PRTDSI__CAPS_SEL       (* (reg8 *) HighF_CompOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HighF_CompOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HighF_CompOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HighF_CompOut_PRTDSI__OE_SEL0        (* (reg8 *) HighF_CompOut__PRTDSI__OE_SEL0) 
#define HighF_CompOut_PRTDSI__OE_SEL1        (* (reg8 *) HighF_CompOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HighF_CompOut_PRTDSI__OUT_SEL0       (* (reg8 *) HighF_CompOut__PRTDSI__OUT_SEL0) 
#define HighF_CompOut_PRTDSI__OUT_SEL1       (* (reg8 *) HighF_CompOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HighF_CompOut_PRTDSI__SYNC_OUT       (* (reg8 *) HighF_CompOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HighF_CompOut__SIO_CFG)
    #define HighF_CompOut_SIO_HYST_EN        (* (reg8 *) HighF_CompOut__SIO_HYST_EN)
    #define HighF_CompOut_SIO_REG_HIFREQ     (* (reg8 *) HighF_CompOut__SIO_REG_HIFREQ)
    #define HighF_CompOut_SIO_CFG            (* (reg8 *) HighF_CompOut__SIO_CFG)
    #define HighF_CompOut_SIO_DIFF           (* (reg8 *) HighF_CompOut__SIO_DIFF)
#endif /* (HighF_CompOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(HighF_CompOut__INTSTAT)
    #define HighF_CompOut_INTSTAT            (* (reg8 *) HighF_CompOut__INTSTAT)
    #define HighF_CompOut_SNAP               (* (reg8 *) HighF_CompOut__SNAP)
    
	#define HighF_CompOut_0_INTTYPE_REG 		(* (reg8 *) HighF_CompOut__0__INTTYPE)
#endif /* (HighF_CompOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HighF_CompOut_H */


/* [] END OF FILE */
