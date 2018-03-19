/*******************************************************************************
* File Name: FSKOutput_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
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

#include "FSKOutput.h"

static FSKOutput_backupStruct FSKOutput_backup;


/*******************************************************************************
* Function Name: FSKOutput_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void FSKOutput_SaveConfig(void) 
{
    if (!((FSKOutput_CR1 & FSKOutput_SRC_MASK) == FSKOutput_SRC_UDB))
    {
        FSKOutput_backup.data_value = FSKOutput_Data;
    }
}


/*******************************************************************************
* Function Name: FSKOutput_RestoreConfig
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
*******************************************************************************/
void FSKOutput_RestoreConfig(void) 
{
    if (!((FSKOutput_CR1 & FSKOutput_SRC_MASK) == FSKOutput_SRC_UDB))
    {
        if((FSKOutput_Strobe & FSKOutput_STRB_MASK) == FSKOutput_STRB_EN)
        {
            FSKOutput_Strobe &= (uint8)(~FSKOutput_STRB_MASK);
            FSKOutput_Data = FSKOutput_backup.data_value;
            FSKOutput_Strobe |= FSKOutput_STRB_EN;
        }
        else
        {
            FSKOutput_Data = FSKOutput_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: FSKOutput_Sleep
********************************************************************************
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
*  FSKOutput_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void FSKOutput_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(FSKOutput_ACT_PWR_EN == (FSKOutput_PWRMGR & FSKOutput_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        FSKOutput_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        FSKOutput_backup.enableState = 0u;
    }
    
    FSKOutput_Stop();
    FSKOutput_SaveConfig();
}


/*******************************************************************************
* Function Name: FSKOutput_Wakeup
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
*  FSKOutput_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FSKOutput_Wakeup(void) 
{
    FSKOutput_RestoreConfig();
    
    if(FSKOutput_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        FSKOutput_Enable();

        /* Restore the data register */
        FSKOutput_SetValue(FSKOutput_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
