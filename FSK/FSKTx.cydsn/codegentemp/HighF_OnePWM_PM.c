/*******************************************************************************
* File Name: HighF_OnePWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "HighF_OnePWM.h"

static HighF_OnePWM_backupStruct HighF_OnePWM_backup;


/*******************************************************************************
* Function Name: HighF_OnePWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HighF_OnePWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HighF_OnePWM_SaveConfig(void) 
{

    #if(!HighF_OnePWM_UsingFixedFunction)
        #if(!HighF_OnePWM_PWMModeIsCenterAligned)
            HighF_OnePWM_backup.PWMPeriod = HighF_OnePWM_ReadPeriod();
        #endif /* (!HighF_OnePWM_PWMModeIsCenterAligned) */
        HighF_OnePWM_backup.PWMUdb = HighF_OnePWM_ReadCounter();
        #if (HighF_OnePWM_UseStatus)
            HighF_OnePWM_backup.InterruptMaskValue = HighF_OnePWM_STATUS_MASK;
        #endif /* (HighF_OnePWM_UseStatus) */

        #if(HighF_OnePWM_DeadBandMode == HighF_OnePWM__B_PWM__DBM_256_CLOCKS || \
            HighF_OnePWM_DeadBandMode == HighF_OnePWM__B_PWM__DBM_2_4_CLOCKS)
            HighF_OnePWM_backup.PWMdeadBandValue = HighF_OnePWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(HighF_OnePWM_KillModeMinTime)
             HighF_OnePWM_backup.PWMKillCounterPeriod = HighF_OnePWM_ReadKillTime();
        #endif /* (HighF_OnePWM_KillModeMinTime) */

        #if(HighF_OnePWM_UseControl)
            HighF_OnePWM_backup.PWMControlRegister = HighF_OnePWM_ReadControlRegister();
        #endif /* (HighF_OnePWM_UseControl) */
    #endif  /* (!HighF_OnePWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_OnePWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HighF_OnePWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HighF_OnePWM_RestoreConfig(void) 
{
        #if(!HighF_OnePWM_UsingFixedFunction)
            #if(!HighF_OnePWM_PWMModeIsCenterAligned)
                HighF_OnePWM_WritePeriod(HighF_OnePWM_backup.PWMPeriod);
            #endif /* (!HighF_OnePWM_PWMModeIsCenterAligned) */

            HighF_OnePWM_WriteCounter(HighF_OnePWM_backup.PWMUdb);

            #if (HighF_OnePWM_UseStatus)
                HighF_OnePWM_STATUS_MASK = HighF_OnePWM_backup.InterruptMaskValue;
            #endif /* (HighF_OnePWM_UseStatus) */

            #if(HighF_OnePWM_DeadBandMode == HighF_OnePWM__B_PWM__DBM_256_CLOCKS || \
                HighF_OnePWM_DeadBandMode == HighF_OnePWM__B_PWM__DBM_2_4_CLOCKS)
                HighF_OnePWM_WriteDeadTime(HighF_OnePWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(HighF_OnePWM_KillModeMinTime)
                HighF_OnePWM_WriteKillTime(HighF_OnePWM_backup.PWMKillCounterPeriod);
            #endif /* (HighF_OnePWM_KillModeMinTime) */

            #if(HighF_OnePWM_UseControl)
                HighF_OnePWM_WriteControlRegister(HighF_OnePWM_backup.PWMControlRegister);
            #endif /* (HighF_OnePWM_UseControl) */
        #endif  /* (!HighF_OnePWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: HighF_OnePWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HighF_OnePWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void HighF_OnePWM_Sleep(void) 
{
    #if(HighF_OnePWM_UseControl)
        if(HighF_OnePWM_CTRL_ENABLE == (HighF_OnePWM_CONTROL & HighF_OnePWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            HighF_OnePWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            HighF_OnePWM_backup.PWMEnableState = 0u;
        }
    #endif /* (HighF_OnePWM_UseControl) */

    /* Stop component */
    HighF_OnePWM_Stop();

    /* Save registers configuration */
    HighF_OnePWM_SaveConfig();
}


/*******************************************************************************
* Function Name: HighF_OnePWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HighF_OnePWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HighF_OnePWM_Wakeup(void) 
{
     /* Restore registers values */
    HighF_OnePWM_RestoreConfig();

    if(HighF_OnePWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        HighF_OnePWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
