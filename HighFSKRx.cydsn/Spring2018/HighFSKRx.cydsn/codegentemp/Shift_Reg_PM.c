/*******************************************************************************
* File Name: Shift_Reg_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Shift_Reg.h"

static Shift_Reg_BACKUP_STRUCT Shift_Reg_backup =
{
    Shift_Reg_DISABLED,

    ((uint32) Shift_Reg_DEFAULT_A0),
    ((uint32) Shift_Reg_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint32) Shift_Reg_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: Shift_Reg_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Shift_Reg_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    Shift_Reg_backup.saveSrA0Reg   = CY_GET_REG32(Shift_Reg_SHIFT_REG_LSB_PTR);
    Shift_Reg_backup.saveSrA1Reg   = CY_GET_REG32(Shift_Reg_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        Shift_Reg_backup.saveSrIntMask = Shift_Reg_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: Shift_Reg_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Shift_Reg_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG32(Shift_Reg_SHIFT_REG_LSB_PTR, Shift_Reg_backup.saveSrA0Reg);
    CY_SET_REG32(Shift_Reg_SHIFT_REG_VALUE_LSB_PTR, Shift_Reg_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        Shift_Reg_SR_STATUS_MASK = ((uint8) Shift_Reg_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: Shift_Reg_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Shift_Reg_Sleep(void) 
{
    Shift_Reg_backup.enableState = ((uint8) Shift_Reg_IS_ENABLED);

    Shift_Reg_Stop();
    Shift_Reg_SaveConfig();
}


/*******************************************************************************
* Function Name: Shift_Reg_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Shift_Reg_Wakeup(void) 
{
    Shift_Reg_RestoreConfig();

    if(0u != Shift_Reg_backup.enableState)
    {
        Shift_Reg_Enable();
    }
}


/* [] END OF FILE */
