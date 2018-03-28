/*******************************************************************************
* File Name: HighF_LevelCount_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "HighF_LevelCount.h"

static HighF_LevelCount_backupStruct HighF_LevelCount_backup;


/*******************************************************************************
* Function Name: HighF_LevelCount_SaveConfig
********************************************************************************
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
*  HighF_LevelCount_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void HighF_LevelCount_SaveConfig(void) 
{
    #if (!HighF_LevelCount_UsingFixedFunction)

        HighF_LevelCount_backup.CounterUdb = HighF_LevelCount_ReadCounter();

        #if(!HighF_LevelCount_ControlRegRemoved)
            HighF_LevelCount_backup.CounterControlRegister = HighF_LevelCount_ReadControlRegister();
        #endif /* (!HighF_LevelCount_ControlRegRemoved) */

    #endif /* (!HighF_LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_RestoreConfig
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
*  HighF_LevelCount_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HighF_LevelCount_RestoreConfig(void) 
{      
    #if (!HighF_LevelCount_UsingFixedFunction)

       HighF_LevelCount_WriteCounter(HighF_LevelCount_backup.CounterUdb);

        #if(!HighF_LevelCount_ControlRegRemoved)
            HighF_LevelCount_WriteControlRegister(HighF_LevelCount_backup.CounterControlRegister);
        #endif /* (!HighF_LevelCount_ControlRegRemoved) */

    #endif /* (!HighF_LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_Sleep
********************************************************************************
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
*  HighF_LevelCount_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void HighF_LevelCount_Sleep(void) 
{
    #if(!HighF_LevelCount_ControlRegRemoved)
        /* Save Counter's enable state */
        if(HighF_LevelCount_CTRL_ENABLE == (HighF_LevelCount_CONTROL & HighF_LevelCount_CTRL_ENABLE))
        {
            /* Counter is enabled */
            HighF_LevelCount_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            HighF_LevelCount_backup.CounterEnableState = 0u;
        }
    #else
        HighF_LevelCount_backup.CounterEnableState = 1u;
        if(HighF_LevelCount_backup.CounterEnableState != 0u)
        {
            HighF_LevelCount_backup.CounterEnableState = 0u;
        }
    #endif /* (!HighF_LevelCount_ControlRegRemoved) */
    
    HighF_LevelCount_Stop();
    HighF_LevelCount_SaveConfig();
}


/*******************************************************************************
* Function Name: HighF_LevelCount_Wakeup
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
*  HighF_LevelCount_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HighF_LevelCount_Wakeup(void) 
{
    HighF_LevelCount_RestoreConfig();
    #if(!HighF_LevelCount_ControlRegRemoved)
        if(HighF_LevelCount_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            HighF_LevelCount_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!HighF_LevelCount_ControlRegRemoved) */
    
}


/* [] END OF FILE */
