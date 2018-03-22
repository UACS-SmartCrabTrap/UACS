/*******************************************************************************
* File Name: LevelCount_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "LevelCount.h"

static LevelCount_backupStruct LevelCount_backup;


/*******************************************************************************
* Function Name: LevelCount_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  LevelCount_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LevelCount_SaveConfig(void) 
{
    #if (!LevelCount_UsingFixedFunction)
        LevelCount_backup.TimerUdb = LevelCount_ReadCounter();
        LevelCount_backup.InterruptMaskValue = LevelCount_STATUS_MASK;
        #if (LevelCount_UsingHWCaptureCounter)
            LevelCount_backup.TimerCaptureCounter = LevelCount_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!LevelCount_UDB_CONTROL_REG_REMOVED)
            LevelCount_backup.TimerControlRegister = LevelCount_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: LevelCount_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  LevelCount_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LevelCount_RestoreConfig(void) 
{   
    #if (!LevelCount_UsingFixedFunction)

        LevelCount_WriteCounter(LevelCount_backup.TimerUdb);
        LevelCount_STATUS_MASK =LevelCount_backup.InterruptMaskValue;
        #if (LevelCount_UsingHWCaptureCounter)
            LevelCount_SetCaptureCount(LevelCount_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!LevelCount_UDB_CONTROL_REG_REMOVED)
            LevelCount_WriteControlRegister(LevelCount_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: LevelCount_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  LevelCount_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void LevelCount_Sleep(void) 
{
    #if(!LevelCount_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(LevelCount_CTRL_ENABLE == (LevelCount_CONTROL & LevelCount_CTRL_ENABLE))
        {
            /* Timer is enabled */
            LevelCount_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            LevelCount_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    LevelCount_Stop();
    LevelCount_SaveConfig();
}


/*******************************************************************************
* Function Name: LevelCount_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  LevelCount_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LevelCount_Wakeup(void) 
{
    LevelCount_RestoreConfig();
    #if(!LevelCount_UDB_CONTROL_REG_REMOVED)
        if(LevelCount_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                LevelCount_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
