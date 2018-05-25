/*******************************************************************************
* File Name: Bit_Timer_PM.c
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

#include "Bit_Timer.h"

static Bit_Timer_backupStruct Bit_Timer_backup;


/*******************************************************************************
* Function Name: Bit_Timer_SaveConfig
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
*  Bit_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Bit_Timer_SaveConfig(void) 
{
    #if (!Bit_Timer_UsingFixedFunction)
        Bit_Timer_backup.TimerUdb = Bit_Timer_ReadCounter();
        Bit_Timer_backup.InterruptMaskValue = Bit_Timer_STATUS_MASK;
        #if (Bit_Timer_UsingHWCaptureCounter)
            Bit_Timer_backup.TimerCaptureCounter = Bit_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Bit_Timer_UDB_CONTROL_REG_REMOVED)
            Bit_Timer_backup.TimerControlRegister = Bit_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Bit_Timer_RestoreConfig
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
*  Bit_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Bit_Timer_RestoreConfig(void) 
{   
    #if (!Bit_Timer_UsingFixedFunction)

        Bit_Timer_WriteCounter(Bit_Timer_backup.TimerUdb);
        Bit_Timer_STATUS_MASK =Bit_Timer_backup.InterruptMaskValue;
        #if (Bit_Timer_UsingHWCaptureCounter)
            Bit_Timer_SetCaptureCount(Bit_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Bit_Timer_UDB_CONTROL_REG_REMOVED)
            Bit_Timer_WriteControlRegister(Bit_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Bit_Timer_Sleep
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
*  Bit_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Bit_Timer_Sleep(void) 
{
    #if(!Bit_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Bit_Timer_CTRL_ENABLE == (Bit_Timer_CONTROL & Bit_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Bit_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Bit_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Bit_Timer_Stop();
    Bit_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Bit_Timer_Wakeup
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
*  Bit_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Bit_Timer_Wakeup(void) 
{
    Bit_Timer_RestoreConfig();
    #if(!Bit_Timer_UDB_CONTROL_REG_REMOVED)
        if(Bit_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Bit_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
