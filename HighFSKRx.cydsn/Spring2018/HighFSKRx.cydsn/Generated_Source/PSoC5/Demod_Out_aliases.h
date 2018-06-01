/*******************************************************************************
* File Name: Demod_Out.h  
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

#if !defined(CY_PINS_Demod_Out_ALIASES_H) /* Pins Demod_Out_ALIASES_H */
#define CY_PINS_Demod_Out_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Demod_Out_0			(Demod_Out__0__PC)
#define Demod_Out_0_INTR	((uint16)((uint16)0x0001u << Demod_Out__0__SHIFT))

#define Demod_Out_INTR_ALL	 ((uint16)(Demod_Out_0_INTR))

#endif /* End Pins Demod_Out_ALIASES_H */


/* [] END OF FILE */
