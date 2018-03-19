/*******************************************************************************
* File Name: LevelCount_PM.c  
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

#include "LevelCount.h"

static LevelCount_backupStruct LevelCount_backup;


/*******************************************************************************
* Function Name: LevelCount_SaveConfig
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
*  LevelCount_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void LevelCount_SaveConfig(void) 
{
    #if (!LevelCount_UsingFixedFunction)

        LevelCount_backup.CounterUdb = LevelCount_ReadCounter();

        #if(!LevelCount_ControlRegRemoved)
            LevelCount_backup.CounterControlRegister = LevelCount_ReadControlRegister();
        #endif /* (!LevelCount_ControlRegRemoved) */

    #endif /* (!LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LevelCount_RestoreConfig
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
*  LevelCount_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LevelCount_RestoreConfig(void) 
{      
    #if (!LevelCount_UsingFixedFunction)

       LevelCount_WriteCounter(LevelCount_backup.CounterUdb);

        #if(!LevelCount_ControlRegRemoved)
            LevelCount_WriteControlRegister(LevelCount_backup.CounterControlRegister);
        #endif /* (!LevelCount_ControlRegRemoved) */

    #endif /* (!LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LevelCount_Sleep
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
*  LevelCount_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LevelCount_Sleep(void) 
{
    #if(!LevelCount_ControlRegRemoved)
        /* Save Counter's enable state */
        if(LevelCount_CTRL_ENABLE == (LevelCount_CONTROL & LevelCount_CTRL_ENABLE))
        {
            /* Counter is enabled */
            LevelCount_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            LevelCount_backup.CounterEnableState = 0u;
        }
    #else
        LevelCount_backup.CounterEnableState = 1u;
        if(LevelCount_backup.CounterEnableState != 0u)
        {
            LevelCount_backup.CounterEnableState = 0u;
        }
    #endif /* (!LevelCount_ControlRegRemoved) */
    
    LevelCount_Stop();
    LevelCount_SaveConfig();
}


/*******************************************************************************
* Function Name: LevelCount_Wakeup
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
*  LevelCount_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LevelCount_Wakeup(void) 
{
    LevelCount_RestoreConfig();
    #if(!LevelCount_ControlRegRemoved)
        if(LevelCount_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            LevelCount_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!LevelCount_ControlRegRemoved) */
    
}


/* [] END OF FILE */
