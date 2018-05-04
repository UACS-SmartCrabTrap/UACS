/*******************************************************************************
* File Name: VGround_Buffer_PM.c  
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

#include "VGround_Buffer.h"

static VGround_Buffer_BACKUP_STRUCT  VGround_Buffer_backup;


/*******************************************************************************
* Function Name: VGround_Buffer_SaveConfig
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
void VGround_Buffer_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: VGround_Buffer_RestoreConfig
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
void VGround_Buffer_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: VGround_Buffer_Sleep
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
*  VGround_Buffer_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void VGround_Buffer_Sleep(void) 
{
    /* Save PGA enable state */
    if((VGround_Buffer_PM_ACT_CFG_REG & VGround_Buffer_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        VGround_Buffer_backup.enableState = 1u;
        /* Stop the configuration */
        VGround_Buffer_Stop();
    }
    else
    {
        /* Component is disabled */
        VGround_Buffer_backup.enableState = 0u;
    }
    /* Save the configuration */
    VGround_Buffer_SaveConfig();
}


/*******************************************************************************
* Function Name: VGround_Buffer_Wakeup
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
*  VGround_Buffer_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void VGround_Buffer_Wakeup(void) 
{
    /* Restore the configurations */
    VGround_Buffer_RestoreConfig();
     /* Enables the component operation */
    if(VGround_Buffer_backup.enableState == 1u)
    {
        VGround_Buffer_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
