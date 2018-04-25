/*******************************************************************************
* File Name: PWM_Alternating_PM.c
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

#include "PWM_Alternating.h"

static PWM_Alternating_backupStruct PWM_Alternating_backup;


/*******************************************************************************
* Function Name: PWM_Alternating_SaveConfig
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
*  PWM_Alternating_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Alternating_SaveConfig(void) 
{

    #if(!PWM_Alternating_UsingFixedFunction)
        #if(!PWM_Alternating_PWMModeIsCenterAligned)
            PWM_Alternating_backup.PWMPeriod = PWM_Alternating_ReadPeriod();
        #endif /* (!PWM_Alternating_PWMModeIsCenterAligned) */
        PWM_Alternating_backup.PWMUdb = PWM_Alternating_ReadCounter();
        #if (PWM_Alternating_UseStatus)
            PWM_Alternating_backup.InterruptMaskValue = PWM_Alternating_STATUS_MASK;
        #endif /* (PWM_Alternating_UseStatus) */

        #if(PWM_Alternating_DeadBandMode == PWM_Alternating__B_PWM__DBM_256_CLOCKS || \
            PWM_Alternating_DeadBandMode == PWM_Alternating__B_PWM__DBM_2_4_CLOCKS)
            PWM_Alternating_backup.PWMdeadBandValue = PWM_Alternating_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Alternating_KillModeMinTime)
             PWM_Alternating_backup.PWMKillCounterPeriod = PWM_Alternating_ReadKillTime();
        #endif /* (PWM_Alternating_KillModeMinTime) */

        #if(PWM_Alternating_UseControl)
            PWM_Alternating_backup.PWMControlRegister = PWM_Alternating_ReadControlRegister();
        #endif /* (PWM_Alternating_UseControl) */
    #endif  /* (!PWM_Alternating_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Alternating_RestoreConfig
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
*  PWM_Alternating_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Alternating_RestoreConfig(void) 
{
        #if(!PWM_Alternating_UsingFixedFunction)
            #if(!PWM_Alternating_PWMModeIsCenterAligned)
                PWM_Alternating_WritePeriod(PWM_Alternating_backup.PWMPeriod);
            #endif /* (!PWM_Alternating_PWMModeIsCenterAligned) */

            PWM_Alternating_WriteCounter(PWM_Alternating_backup.PWMUdb);

            #if (PWM_Alternating_UseStatus)
                PWM_Alternating_STATUS_MASK = PWM_Alternating_backup.InterruptMaskValue;
            #endif /* (PWM_Alternating_UseStatus) */

            #if(PWM_Alternating_DeadBandMode == PWM_Alternating__B_PWM__DBM_256_CLOCKS || \
                PWM_Alternating_DeadBandMode == PWM_Alternating__B_PWM__DBM_2_4_CLOCKS)
                PWM_Alternating_WriteDeadTime(PWM_Alternating_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Alternating_KillModeMinTime)
                PWM_Alternating_WriteKillTime(PWM_Alternating_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Alternating_KillModeMinTime) */

            #if(PWM_Alternating_UseControl)
                PWM_Alternating_WriteControlRegister(PWM_Alternating_backup.PWMControlRegister);
            #endif /* (PWM_Alternating_UseControl) */
        #endif  /* (!PWM_Alternating_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Alternating_Sleep
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
*  PWM_Alternating_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Alternating_Sleep(void) 
{
    #if(PWM_Alternating_UseControl)
        if(PWM_Alternating_CTRL_ENABLE == (PWM_Alternating_CONTROL & PWM_Alternating_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Alternating_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Alternating_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Alternating_UseControl) */

    /* Stop component */
    PWM_Alternating_Stop();

    /* Save registers configuration */
    PWM_Alternating_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Alternating_Wakeup
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
*  PWM_Alternating_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Alternating_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Alternating_RestoreConfig();

    if(PWM_Alternating_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Alternating_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
