/*******************************************************************************
* File Name: HighF_Ref_OpAmp_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "HighF_Ref_OpAmp.h"

static HighF_Ref_OpAmp_BACKUP_STRUCT  HighF_Ref_OpAmp_backup;


/*******************************************************************************  
* Function Name: HighF_Ref_OpAmp_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void HighF_Ref_OpAmp_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: HighF_Ref_OpAmp_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HighF_Ref_OpAmp_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: HighF_Ref_OpAmp_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  HighF_Ref_OpAmp_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void HighF_Ref_OpAmp_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((HighF_Ref_OpAmp_PM_ACT_CFG_REG & HighF_Ref_OpAmp_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        HighF_Ref_OpAmp_backup.enableState = 1u;
         /* Stops the component */
         HighF_Ref_OpAmp_Stop();
    }
    else
    {
        /* Component is disabled */
        HighF_Ref_OpAmp_backup.enableState = 0u;
    }
    /* Saves the configuration */
    HighF_Ref_OpAmp_SaveConfig();
}


/*******************************************************************************  
* Function Name: HighF_Ref_OpAmp_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  HighF_Ref_OpAmp_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void HighF_Ref_OpAmp_Wakeup(void) 
{
    /* Restore the user configuration */
    HighF_Ref_OpAmp_RestoreConfig();

    /* Enables the component operation */
    if(HighF_Ref_OpAmp_backup.enableState == 1u)
    {
        HighF_Ref_OpAmp_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
