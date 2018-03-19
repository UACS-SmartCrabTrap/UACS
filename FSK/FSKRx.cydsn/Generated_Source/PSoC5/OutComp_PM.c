/*******************************************************************************
* File Name: OutComp.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "OutComp.h"

static OutComp_backupStruct OutComp_backup;


/*******************************************************************************
* Function Name: OutComp_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void OutComp_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: OutComp_RestoreConfig
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
********************************************************************************/
void OutComp_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: OutComp_Sleep
********************************************************************************
*
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  OutComp_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void OutComp_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(OutComp_ACT_PWR_EN == (OutComp_PWRMGR & OutComp_ACT_PWR_EN))
    {
        /* Comp is enabled */
        OutComp_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        OutComp_backup.enableState = 0u;
    }    
    
    OutComp_Stop();
    OutComp_SaveConfig();
}


/*******************************************************************************
* Function Name: OutComp_Wakeup
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
*  OutComp_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void OutComp_Wakeup(void) 
{
    OutComp_RestoreConfig();
    
    if(OutComp_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        OutComp_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
