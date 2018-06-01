/*******************************************************************************
* File Name: XOR_Out_LPF.h  
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

#if !defined(CY_PINS_XOR_Out_LPF_H) /* Pins XOR_Out_LPF_H */
#define CY_PINS_XOR_Out_LPF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "XOR_Out_LPF_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 XOR_Out_LPF__PORT == 15 && ((XOR_Out_LPF__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    XOR_Out_LPF_Write(uint8 value);
void    XOR_Out_LPF_SetDriveMode(uint8 mode);
uint8   XOR_Out_LPF_ReadDataReg(void);
uint8   XOR_Out_LPF_Read(void);
void    XOR_Out_LPF_SetInterruptMode(uint16 position, uint16 mode);
uint8   XOR_Out_LPF_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the XOR_Out_LPF_SetDriveMode() function.
     *  @{
     */
        #define XOR_Out_LPF_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define XOR_Out_LPF_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define XOR_Out_LPF_DM_RES_UP          PIN_DM_RES_UP
        #define XOR_Out_LPF_DM_RES_DWN         PIN_DM_RES_DWN
        #define XOR_Out_LPF_DM_OD_LO           PIN_DM_OD_LO
        #define XOR_Out_LPF_DM_OD_HI           PIN_DM_OD_HI
        #define XOR_Out_LPF_DM_STRONG          PIN_DM_STRONG
        #define XOR_Out_LPF_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define XOR_Out_LPF_MASK               XOR_Out_LPF__MASK
#define XOR_Out_LPF_SHIFT              XOR_Out_LPF__SHIFT
#define XOR_Out_LPF_WIDTH              1u

/* Interrupt constants */
#if defined(XOR_Out_LPF__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in XOR_Out_LPF_SetInterruptMode() function.
     *  @{
     */
        #define XOR_Out_LPF_INTR_NONE      (uint16)(0x0000u)
        #define XOR_Out_LPF_INTR_RISING    (uint16)(0x0001u)
        #define XOR_Out_LPF_INTR_FALLING   (uint16)(0x0002u)
        #define XOR_Out_LPF_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define XOR_Out_LPF_INTR_MASK      (0x01u) 
#endif /* (XOR_Out_LPF__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define XOR_Out_LPF_PS                     (* (reg8 *) XOR_Out_LPF__PS)
/* Data Register */
#define XOR_Out_LPF_DR                     (* (reg8 *) XOR_Out_LPF__DR)
/* Port Number */
#define XOR_Out_LPF_PRT_NUM                (* (reg8 *) XOR_Out_LPF__PRT) 
/* Connect to Analog Globals */                                                  
#define XOR_Out_LPF_AG                     (* (reg8 *) XOR_Out_LPF__AG)                       
/* Analog MUX bux enable */
#define XOR_Out_LPF_AMUX                   (* (reg8 *) XOR_Out_LPF__AMUX) 
/* Bidirectional Enable */                                                        
#define XOR_Out_LPF_BIE                    (* (reg8 *) XOR_Out_LPF__BIE)
/* Bit-mask for Aliased Register Access */
#define XOR_Out_LPF_BIT_MASK               (* (reg8 *) XOR_Out_LPF__BIT_MASK)
/* Bypass Enable */
#define XOR_Out_LPF_BYP                    (* (reg8 *) XOR_Out_LPF__BYP)
/* Port wide control signals */                                                   
#define XOR_Out_LPF_CTL                    (* (reg8 *) XOR_Out_LPF__CTL)
/* Drive Modes */
#define XOR_Out_LPF_DM0                    (* (reg8 *) XOR_Out_LPF__DM0) 
#define XOR_Out_LPF_DM1                    (* (reg8 *) XOR_Out_LPF__DM1)
#define XOR_Out_LPF_DM2                    (* (reg8 *) XOR_Out_LPF__DM2) 
/* Input Buffer Disable Override */
#define XOR_Out_LPF_INP_DIS                (* (reg8 *) XOR_Out_LPF__INP_DIS)
/* LCD Common or Segment Drive */
#define XOR_Out_LPF_LCD_COM_SEG            (* (reg8 *) XOR_Out_LPF__LCD_COM_SEG)
/* Enable Segment LCD */
#define XOR_Out_LPF_LCD_EN                 (* (reg8 *) XOR_Out_LPF__LCD_EN)
/* Slew Rate Control */
#define XOR_Out_LPF_SLW                    (* (reg8 *) XOR_Out_LPF__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define XOR_Out_LPF_PRTDSI__CAPS_SEL       (* (reg8 *) XOR_Out_LPF__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define XOR_Out_LPF_PRTDSI__DBL_SYNC_IN    (* (reg8 *) XOR_Out_LPF__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define XOR_Out_LPF_PRTDSI__OE_SEL0        (* (reg8 *) XOR_Out_LPF__PRTDSI__OE_SEL0) 
#define XOR_Out_LPF_PRTDSI__OE_SEL1        (* (reg8 *) XOR_Out_LPF__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define XOR_Out_LPF_PRTDSI__OUT_SEL0       (* (reg8 *) XOR_Out_LPF__PRTDSI__OUT_SEL0) 
#define XOR_Out_LPF_PRTDSI__OUT_SEL1       (* (reg8 *) XOR_Out_LPF__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define XOR_Out_LPF_PRTDSI__SYNC_OUT       (* (reg8 *) XOR_Out_LPF__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(XOR_Out_LPF__SIO_CFG)
    #define XOR_Out_LPF_SIO_HYST_EN        (* (reg8 *) XOR_Out_LPF__SIO_HYST_EN)
    #define XOR_Out_LPF_SIO_REG_HIFREQ     (* (reg8 *) XOR_Out_LPF__SIO_REG_HIFREQ)
    #define XOR_Out_LPF_SIO_CFG            (* (reg8 *) XOR_Out_LPF__SIO_CFG)
    #define XOR_Out_LPF_SIO_DIFF           (* (reg8 *) XOR_Out_LPF__SIO_DIFF)
#endif /* (XOR_Out_LPF__SIO_CFG) */

/* Interrupt Registers */
#if defined(XOR_Out_LPF__INTSTAT)
    #define XOR_Out_LPF_INTSTAT            (* (reg8 *) XOR_Out_LPF__INTSTAT)
    #define XOR_Out_LPF_SNAP               (* (reg8 *) XOR_Out_LPF__SNAP)
    
	#define XOR_Out_LPF_0_INTTYPE_REG 		(* (reg8 *) XOR_Out_LPF__0__INTTYPE)
#endif /* (XOR_Out_LPF__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_XOR_Out_LPF_H */


/* [] END OF FILE */
