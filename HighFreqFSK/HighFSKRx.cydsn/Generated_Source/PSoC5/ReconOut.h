/*******************************************************************************
* File Name: ReconOut.h  
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

#if !defined(CY_PINS_ReconOut_H) /* Pins ReconOut_H */
#define CY_PINS_ReconOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ReconOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ReconOut__PORT == 15 && ((ReconOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ReconOut_Write(uint8 value);
void    ReconOut_SetDriveMode(uint8 mode);
uint8   ReconOut_ReadDataReg(void);
uint8   ReconOut_Read(void);
void    ReconOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   ReconOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ReconOut_SetDriveMode() function.
     *  @{
     */
        #define ReconOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ReconOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ReconOut_DM_RES_UP          PIN_DM_RES_UP
        #define ReconOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define ReconOut_DM_OD_LO           PIN_DM_OD_LO
        #define ReconOut_DM_OD_HI           PIN_DM_OD_HI
        #define ReconOut_DM_STRONG          PIN_DM_STRONG
        #define ReconOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ReconOut_MASK               ReconOut__MASK
#define ReconOut_SHIFT              ReconOut__SHIFT
#define ReconOut_WIDTH              1u

/* Interrupt constants */
#if defined(ReconOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ReconOut_SetInterruptMode() function.
     *  @{
     */
        #define ReconOut_INTR_NONE      (uint16)(0x0000u)
        #define ReconOut_INTR_RISING    (uint16)(0x0001u)
        #define ReconOut_INTR_FALLING   (uint16)(0x0002u)
        #define ReconOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ReconOut_INTR_MASK      (0x01u) 
#endif /* (ReconOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ReconOut_PS                     (* (reg8 *) ReconOut__PS)
/* Data Register */
#define ReconOut_DR                     (* (reg8 *) ReconOut__DR)
/* Port Number */
#define ReconOut_PRT_NUM                (* (reg8 *) ReconOut__PRT) 
/* Connect to Analog Globals */                                                  
#define ReconOut_AG                     (* (reg8 *) ReconOut__AG)                       
/* Analog MUX bux enable */
#define ReconOut_AMUX                   (* (reg8 *) ReconOut__AMUX) 
/* Bidirectional Enable */                                                        
#define ReconOut_BIE                    (* (reg8 *) ReconOut__BIE)
/* Bit-mask for Aliased Register Access */
#define ReconOut_BIT_MASK               (* (reg8 *) ReconOut__BIT_MASK)
/* Bypass Enable */
#define ReconOut_BYP                    (* (reg8 *) ReconOut__BYP)
/* Port wide control signals */                                                   
#define ReconOut_CTL                    (* (reg8 *) ReconOut__CTL)
/* Drive Modes */
#define ReconOut_DM0                    (* (reg8 *) ReconOut__DM0) 
#define ReconOut_DM1                    (* (reg8 *) ReconOut__DM1)
#define ReconOut_DM2                    (* (reg8 *) ReconOut__DM2) 
/* Input Buffer Disable Override */
#define ReconOut_INP_DIS                (* (reg8 *) ReconOut__INP_DIS)
/* LCD Common or Segment Drive */
#define ReconOut_LCD_COM_SEG            (* (reg8 *) ReconOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define ReconOut_LCD_EN                 (* (reg8 *) ReconOut__LCD_EN)
/* Slew Rate Control */
#define ReconOut_SLW                    (* (reg8 *) ReconOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ReconOut_PRTDSI__CAPS_SEL       (* (reg8 *) ReconOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ReconOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ReconOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ReconOut_PRTDSI__OE_SEL0        (* (reg8 *) ReconOut__PRTDSI__OE_SEL0) 
#define ReconOut_PRTDSI__OE_SEL1        (* (reg8 *) ReconOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ReconOut_PRTDSI__OUT_SEL0       (* (reg8 *) ReconOut__PRTDSI__OUT_SEL0) 
#define ReconOut_PRTDSI__OUT_SEL1       (* (reg8 *) ReconOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ReconOut_PRTDSI__SYNC_OUT       (* (reg8 *) ReconOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ReconOut__SIO_CFG)
    #define ReconOut_SIO_HYST_EN        (* (reg8 *) ReconOut__SIO_HYST_EN)
    #define ReconOut_SIO_REG_HIFREQ     (* (reg8 *) ReconOut__SIO_REG_HIFREQ)
    #define ReconOut_SIO_CFG            (* (reg8 *) ReconOut__SIO_CFG)
    #define ReconOut_SIO_DIFF           (* (reg8 *) ReconOut__SIO_DIFF)
#endif /* (ReconOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(ReconOut__INTSTAT)
    #define ReconOut_INTSTAT            (* (reg8 *) ReconOut__INTSTAT)
    #define ReconOut_SNAP               (* (reg8 *) ReconOut__SNAP)
    
	#define ReconOut_0_INTTYPE_REG 		(* (reg8 *) ReconOut__0__INTTYPE)
#endif /* (ReconOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ReconOut_H */


/* [] END OF FILE */
