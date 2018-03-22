/*******************************************************************************
* File Name: HighF_MuxSelIn.h  
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

#if !defined(CY_PINS_HighF_MuxSelIn_H) /* Pins HighF_MuxSelIn_H */
#define CY_PINS_HighF_MuxSelIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HighF_MuxSelIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HighF_MuxSelIn__PORT == 15 && ((HighF_MuxSelIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HighF_MuxSelIn_Write(uint8 value);
void    HighF_MuxSelIn_SetDriveMode(uint8 mode);
uint8   HighF_MuxSelIn_ReadDataReg(void);
uint8   HighF_MuxSelIn_Read(void);
void    HighF_MuxSelIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   HighF_MuxSelIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HighF_MuxSelIn_SetDriveMode() function.
     *  @{
     */
        #define HighF_MuxSelIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HighF_MuxSelIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HighF_MuxSelIn_DM_RES_UP          PIN_DM_RES_UP
        #define HighF_MuxSelIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define HighF_MuxSelIn_DM_OD_LO           PIN_DM_OD_LO
        #define HighF_MuxSelIn_DM_OD_HI           PIN_DM_OD_HI
        #define HighF_MuxSelIn_DM_STRONG          PIN_DM_STRONG
        #define HighF_MuxSelIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HighF_MuxSelIn_MASK               HighF_MuxSelIn__MASK
#define HighF_MuxSelIn_SHIFT              HighF_MuxSelIn__SHIFT
#define HighF_MuxSelIn_WIDTH              1u

/* Interrupt constants */
#if defined(HighF_MuxSelIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HighF_MuxSelIn_SetInterruptMode() function.
     *  @{
     */
        #define HighF_MuxSelIn_INTR_NONE      (uint16)(0x0000u)
        #define HighF_MuxSelIn_INTR_RISING    (uint16)(0x0001u)
        #define HighF_MuxSelIn_INTR_FALLING   (uint16)(0x0002u)
        #define HighF_MuxSelIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HighF_MuxSelIn_INTR_MASK      (0x01u) 
#endif /* (HighF_MuxSelIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HighF_MuxSelIn_PS                     (* (reg8 *) HighF_MuxSelIn__PS)
/* Data Register */
#define HighF_MuxSelIn_DR                     (* (reg8 *) HighF_MuxSelIn__DR)
/* Port Number */
#define HighF_MuxSelIn_PRT_NUM                (* (reg8 *) HighF_MuxSelIn__PRT) 
/* Connect to Analog Globals */                                                  
#define HighF_MuxSelIn_AG                     (* (reg8 *) HighF_MuxSelIn__AG)                       
/* Analog MUX bux enable */
#define HighF_MuxSelIn_AMUX                   (* (reg8 *) HighF_MuxSelIn__AMUX) 
/* Bidirectional Enable */                                                        
#define HighF_MuxSelIn_BIE                    (* (reg8 *) HighF_MuxSelIn__BIE)
/* Bit-mask for Aliased Register Access */
#define HighF_MuxSelIn_BIT_MASK               (* (reg8 *) HighF_MuxSelIn__BIT_MASK)
/* Bypass Enable */
#define HighF_MuxSelIn_BYP                    (* (reg8 *) HighF_MuxSelIn__BYP)
/* Port wide control signals */                                                   
#define HighF_MuxSelIn_CTL                    (* (reg8 *) HighF_MuxSelIn__CTL)
/* Drive Modes */
#define HighF_MuxSelIn_DM0                    (* (reg8 *) HighF_MuxSelIn__DM0) 
#define HighF_MuxSelIn_DM1                    (* (reg8 *) HighF_MuxSelIn__DM1)
#define HighF_MuxSelIn_DM2                    (* (reg8 *) HighF_MuxSelIn__DM2) 
/* Input Buffer Disable Override */
#define HighF_MuxSelIn_INP_DIS                (* (reg8 *) HighF_MuxSelIn__INP_DIS)
/* LCD Common or Segment Drive */
#define HighF_MuxSelIn_LCD_COM_SEG            (* (reg8 *) HighF_MuxSelIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define HighF_MuxSelIn_LCD_EN                 (* (reg8 *) HighF_MuxSelIn__LCD_EN)
/* Slew Rate Control */
#define HighF_MuxSelIn_SLW                    (* (reg8 *) HighF_MuxSelIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HighF_MuxSelIn_PRTDSI__CAPS_SEL       (* (reg8 *) HighF_MuxSelIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HighF_MuxSelIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HighF_MuxSelIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HighF_MuxSelIn_PRTDSI__OE_SEL0        (* (reg8 *) HighF_MuxSelIn__PRTDSI__OE_SEL0) 
#define HighF_MuxSelIn_PRTDSI__OE_SEL1        (* (reg8 *) HighF_MuxSelIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HighF_MuxSelIn_PRTDSI__OUT_SEL0       (* (reg8 *) HighF_MuxSelIn__PRTDSI__OUT_SEL0) 
#define HighF_MuxSelIn_PRTDSI__OUT_SEL1       (* (reg8 *) HighF_MuxSelIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HighF_MuxSelIn_PRTDSI__SYNC_OUT       (* (reg8 *) HighF_MuxSelIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HighF_MuxSelIn__SIO_CFG)
    #define HighF_MuxSelIn_SIO_HYST_EN        (* (reg8 *) HighF_MuxSelIn__SIO_HYST_EN)
    #define HighF_MuxSelIn_SIO_REG_HIFREQ     (* (reg8 *) HighF_MuxSelIn__SIO_REG_HIFREQ)
    #define HighF_MuxSelIn_SIO_CFG            (* (reg8 *) HighF_MuxSelIn__SIO_CFG)
    #define HighF_MuxSelIn_SIO_DIFF           (* (reg8 *) HighF_MuxSelIn__SIO_DIFF)
#endif /* (HighF_MuxSelIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(HighF_MuxSelIn__INTSTAT)
    #define HighF_MuxSelIn_INTSTAT            (* (reg8 *) HighF_MuxSelIn__INTSTAT)
    #define HighF_MuxSelIn_SNAP               (* (reg8 *) HighF_MuxSelIn__SNAP)
    
	#define HighF_MuxSelIn_0_INTTYPE_REG 		(* (reg8 *) HighF_MuxSelIn__0__INTTYPE)
#endif /* (HighF_MuxSelIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HighF_MuxSelIn_H */


/* [] END OF FILE */
