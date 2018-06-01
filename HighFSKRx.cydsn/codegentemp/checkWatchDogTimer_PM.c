/*******************************************************************************
* File Name: checkWatchDogTimer_PM.c
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

#include "checkWatchDogTimer.h"

static checkWatchDogTimer_backupStruct checkWatchDogTimer_backup;


/*******************************************************************************
* Function Name: checkWatchDogTimer_SaveConfig
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
*  checkWatchDogTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void checkWatchDogTimer_SaveConfig(void) 
{
    #if (!checkWatchDogTimer_UsingFixedFunction)
        checkWatchDogTimer_backup.TimerUdb = checkWatchDogTimer_ReadCounter();
        checkWatchDogTimer_backup.InterruptMaskValue = checkWatchDogTimer_STATUS_MASK;
        #if (checkWatchDogTimer_UsingHWCaptureCounter)
            checkWatchDogTimer_backup.TimerCaptureCounter = checkWatchDogTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!checkWatchDogTimer_UDB_CONTROL_REG_REMOVED)
            checkWatchDogTimer_backup.TimerControlRegister = checkWatchDogTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: checkWatchDogTimer_RestoreConfig
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
*  checkWatchDogTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void checkWatchDogTimer_RestoreConfig(void) 
{   
    #if (!checkWatchDogTimer_UsingFixedFunction)

        checkWatchDogTimer_WriteCounter(checkWatchDogTimer_backup.TimerUdb);
        checkWatchDogTimer_STATUS_MASK =checkWatchDogTimer_backup.InterruptMaskValue;
        #if (checkWatchDogTimer_UsingHWCaptureCounter)
            checkWatchDogTimer_SetCaptureCount(checkWatchDogTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!checkWatchDogTimer_UDB_CONTROL_REG_REMOVED)
            checkWatchDogTimer_WriteControlRegister(checkWatchDogTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: checkWatchDogTimer_Sleep
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
*  checkWatchDogTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void checkWatchDogTimer_Sleep(void) 
{
    #if(!checkWatchDogTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(checkWatchDogTimer_CTRL_ENABLE == (checkWatchDogTimer_CONTROL & checkWatchDogTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            checkWatchDogTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            checkWatchDogTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    checkWatchDogTimer_Stop();
    checkWatchDogTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: checkWatchDogTimer_Wakeup
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
*  checkWatchDogTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void checkWatchDogTimer_Wakeup(void) 
{
    checkWatchDogTimer_RestoreConfig();
    #if(!checkWatchDogTimer_UDB_CONTROL_REG_REMOVED)
        if(checkWatchDogTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                checkWatchDogTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
