/*******************************************************************************
* File Name: HighF_LevelCount_PM.c
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

#include "HighF_LevelCount.h"

static HighF_LevelCount_backupStruct HighF_LevelCount_backup;


/*******************************************************************************
* Function Name: HighF_LevelCount_SaveConfig
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
*  HighF_LevelCount_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HighF_LevelCount_SaveConfig(void) 
{
    #if (!HighF_LevelCount_UsingFixedFunction)
        HighF_LevelCount_backup.TimerUdb = HighF_LevelCount_ReadCounter();
        HighF_LevelCount_backup.InterruptMaskValue = HighF_LevelCount_STATUS_MASK;
        #if (HighF_LevelCount_UsingHWCaptureCounter)
            HighF_LevelCount_backup.TimerCaptureCounter = HighF_LevelCount_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!HighF_LevelCount_UDB_CONTROL_REG_REMOVED)
            HighF_LevelCount_backup.TimerControlRegister = HighF_LevelCount_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_RestoreConfig
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
*  HighF_LevelCount_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HighF_LevelCount_RestoreConfig(void) 
{   
    #if (!HighF_LevelCount_UsingFixedFunction)

        HighF_LevelCount_WriteCounter(HighF_LevelCount_backup.TimerUdb);
        HighF_LevelCount_STATUS_MASK =HighF_LevelCount_backup.InterruptMaskValue;
        #if (HighF_LevelCount_UsingHWCaptureCounter)
            HighF_LevelCount_SetCaptureCount(HighF_LevelCount_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!HighF_LevelCount_UDB_CONTROL_REG_REMOVED)
            HighF_LevelCount_WriteControlRegister(HighF_LevelCount_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_Sleep
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
*  HighF_LevelCount_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void HighF_LevelCount_Sleep(void) 
{
    #if(!HighF_LevelCount_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(HighF_LevelCount_CTRL_ENABLE == (HighF_LevelCount_CONTROL & HighF_LevelCount_CTRL_ENABLE))
        {
            /* Timer is enabled */
            HighF_LevelCount_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            HighF_LevelCount_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    HighF_LevelCount_Stop();
    HighF_LevelCount_SaveConfig();
}


/*******************************************************************************
* Function Name: HighF_LevelCount_Wakeup
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
*  HighF_LevelCount_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HighF_LevelCount_Wakeup(void) 
{
    HighF_LevelCount_RestoreConfig();
    #if(!HighF_LevelCount_UDB_CONTROL_REG_REMOVED)
        if(HighF_LevelCount_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                HighF_LevelCount_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
