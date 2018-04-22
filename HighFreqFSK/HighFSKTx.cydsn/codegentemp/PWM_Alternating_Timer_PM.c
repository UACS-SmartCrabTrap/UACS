/*******************************************************************************
* File Name: PWM_Alternating_Timer_PM.c
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

#include "PWM_Alternating_Timer.h"

static PWM_Alternating_Timer_backupStruct PWM_Alternating_Timer_backup;


/*******************************************************************************
* Function Name: PWM_Alternating_Timer_SaveConfig
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
*  PWM_Alternating_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Alternating_Timer_SaveConfig(void) 
{
    #if (!PWM_Alternating_Timer_UsingFixedFunction)
        PWM_Alternating_Timer_backup.TimerUdb = PWM_Alternating_Timer_ReadCounter();
        PWM_Alternating_Timer_backup.InterruptMaskValue = PWM_Alternating_Timer_STATUS_MASK;
        #if (PWM_Alternating_Timer_UsingHWCaptureCounter)
            PWM_Alternating_Timer_backup.TimerCaptureCounter = PWM_Alternating_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!PWM_Alternating_Timer_UDB_CONTROL_REG_REMOVED)
            PWM_Alternating_Timer_backup.TimerControlRegister = PWM_Alternating_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: PWM_Alternating_Timer_RestoreConfig
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
*  PWM_Alternating_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Alternating_Timer_RestoreConfig(void) 
{   
    #if (!PWM_Alternating_Timer_UsingFixedFunction)

        PWM_Alternating_Timer_WriteCounter(PWM_Alternating_Timer_backup.TimerUdb);
        PWM_Alternating_Timer_STATUS_MASK =PWM_Alternating_Timer_backup.InterruptMaskValue;
        #if (PWM_Alternating_Timer_UsingHWCaptureCounter)
            PWM_Alternating_Timer_SetCaptureCount(PWM_Alternating_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!PWM_Alternating_Timer_UDB_CONTROL_REG_REMOVED)
            PWM_Alternating_Timer_WriteControlRegister(PWM_Alternating_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: PWM_Alternating_Timer_Sleep
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
*  PWM_Alternating_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Alternating_Timer_Sleep(void) 
{
    #if(!PWM_Alternating_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(PWM_Alternating_Timer_CTRL_ENABLE == (PWM_Alternating_Timer_CONTROL & PWM_Alternating_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            PWM_Alternating_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            PWM_Alternating_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    PWM_Alternating_Timer_Stop();
    PWM_Alternating_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Alternating_Timer_Wakeup
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
*  PWM_Alternating_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Alternating_Timer_Wakeup(void) 
{
    PWM_Alternating_Timer_RestoreConfig();
    #if(!PWM_Alternating_Timer_UDB_CONTROL_REG_REMOVED)
        if(PWM_Alternating_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                PWM_Alternating_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
