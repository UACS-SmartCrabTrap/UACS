/*******************************************************************************
* File Name: BPFIn.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BPFIn_ALIASES_H) /* Pins BPFIn_ALIASES_H */
#define CY_PINS_BPFIn_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define BPFIn_0			(BPFIn__0__PC)
#define BPFIn_0_INTR	((uint16)((uint16)0x0001u << BPFIn__0__SHIFT))

#define BPFIn_INTR_ALL	 ((uint16)(BPFIn_0_INTR))

#endif /* End Pins BPFIn_ALIASES_H */


/* [] END OF FILE */
