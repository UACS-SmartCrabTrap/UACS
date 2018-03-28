/*******************************************************************************
* File Name: BPF_Comp.c
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

#include "BPF_Comp.h"

static BPF_Comp_backupStruct BPF_Comp_backup;


/*******************************************************************************
* Function Name: BPF_Comp_SaveConfig
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
void BPF_Comp_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: BPF_Comp_RestoreConfig
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
void BPF_Comp_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: BPF_Comp_Sleep
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
*  BPF_Comp_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void BPF_Comp_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(BPF_Comp_ACT_PWR_EN == (BPF_Comp_PWRMGR & BPF_Comp_ACT_PWR_EN))
    {
        /* Comp is enabled */
        BPF_Comp_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        BPF_Comp_backup.enableState = 0u;
    }    
    
    BPF_Comp_Stop();
    BPF_Comp_SaveConfig();
}


/*******************************************************************************
* Function Name: BPF_Comp_Wakeup
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
*  BPF_Comp_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BPF_Comp_Wakeup(void) 
{
    BPF_Comp_RestoreConfig();
    
    if(BPF_Comp_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        BPF_Comp_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
