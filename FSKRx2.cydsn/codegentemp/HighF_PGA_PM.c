/*******************************************************************************
* File Name: HighF_PGA_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power manager source code to the API for PGA 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "HighF_PGA.h"

static HighF_PGA_BACKUP_STRUCT  HighF_PGA_backup;


/*******************************************************************************
* Function Name: HighF_PGA_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user register configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HighF_PGA_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: HighF_PGA_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HighF_PGA_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: HighF_PGA_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HighF_PGA_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void HighF_PGA_Sleep(void) 
{
    /* Save PGA enable state */
    if((HighF_PGA_PM_ACT_CFG_REG & HighF_PGA_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        HighF_PGA_backup.enableState = 1u;
        /* Stop the configuration */
        HighF_PGA_Stop();
    }
    else
    {
        /* Component is disabled */
        HighF_PGA_backup.enableState = 0u;
    }
    /* Save the configuration */
    HighF_PGA_SaveConfig();
}


/*******************************************************************************
* Function Name: HighF_PGA_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  void
*
* Global variables:
*  HighF_PGA_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void HighF_PGA_Wakeup(void) 
{
    /* Restore the configurations */
    HighF_PGA_RestoreConfig();
     /* Enables the component operation */
    if(HighF_PGA_backup.enableState == 1u)
    {
        HighF_PGA_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
