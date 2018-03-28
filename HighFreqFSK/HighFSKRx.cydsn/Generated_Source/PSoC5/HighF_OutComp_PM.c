/*******************************************************************************
* File Name: HighF_OutComp.c
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

#include "HighF_OutComp.h"

static HighF_OutComp_backupStruct HighF_OutComp_backup;


/*******************************************************************************
* Function Name: HighF_OutComp_SaveConfig
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
void HighF_OutComp_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: HighF_OutComp_RestoreConfig
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
void HighF_OutComp_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: HighF_OutComp_Sleep
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
*  HighF_OutComp_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void HighF_OutComp_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(HighF_OutComp_ACT_PWR_EN == (HighF_OutComp_PWRMGR & HighF_OutComp_ACT_PWR_EN))
    {
        /* Comp is enabled */
        HighF_OutComp_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        HighF_OutComp_backup.enableState = 0u;
    }    
    
    HighF_OutComp_Stop();
    HighF_OutComp_SaveConfig();
}


/*******************************************************************************
* Function Name: HighF_OutComp_Wakeup
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
*  HighF_OutComp_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HighF_OutComp_Wakeup(void) 
{
    HighF_OutComp_RestoreConfig();
    
    if(HighF_OutComp_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        HighF_OutComp_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
