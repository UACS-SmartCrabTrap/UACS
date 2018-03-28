/*******************************************************************************
* File Name: HighF_ShiftReg2_PM.c
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

#include "HighF_ShiftReg2.h"

static HighF_ShiftReg2_BACKUP_STRUCT HighF_ShiftReg2_backup =
{
    HighF_ShiftReg2_DISABLED,

    ((uint32) HighF_ShiftReg2_DEFAULT_A0),
    ((uint32) HighF_ShiftReg2_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint32) HighF_ShiftReg2_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: HighF_ShiftReg2_SaveConfig
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
void HighF_ShiftReg2_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    HighF_ShiftReg2_backup.saveSrA0Reg   = CY_GET_REG32(HighF_ShiftReg2_SHIFT_REG_LSB_PTR);
    HighF_ShiftReg2_backup.saveSrA1Reg   = CY_GET_REG32(HighF_ShiftReg2_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        HighF_ShiftReg2_backup.saveSrIntMask = HighF_ShiftReg2_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: HighF_ShiftReg2_RestoreConfig
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
void HighF_ShiftReg2_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG32(HighF_ShiftReg2_SHIFT_REG_LSB_PTR, HighF_ShiftReg2_backup.saveSrA0Reg);
    CY_SET_REG32(HighF_ShiftReg2_SHIFT_REG_VALUE_LSB_PTR, HighF_ShiftReg2_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        HighF_ShiftReg2_SR_STATUS_MASK = ((uint8) HighF_ShiftReg2_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: HighF_ShiftReg2_Sleep
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
void HighF_ShiftReg2_Sleep(void) 
{
    HighF_ShiftReg2_backup.enableState = ((uint8) HighF_ShiftReg2_IS_ENABLED);

    HighF_ShiftReg2_Stop();
    HighF_ShiftReg2_SaveConfig();
}


/*******************************************************************************
* Function Name: HighF_ShiftReg2_Wakeup
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
void HighF_ShiftReg2_Wakeup(void) 
{
    HighF_ShiftReg2_RestoreConfig();

    if(0u != HighF_ShiftReg2_backup.enableState)
    {
        HighF_ShiftReg2_Enable();
    }
}


/* [] END OF FILE */
