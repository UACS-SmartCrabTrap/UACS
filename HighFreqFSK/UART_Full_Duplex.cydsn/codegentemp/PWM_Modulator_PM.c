/*******************************************************************************
* File Name: PWM_Modulator_PM.c
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

#include "PWM_Modulator.h"

static PWM_Modulator_backupStruct PWM_Modulator_backup;


/*******************************************************************************
* Function Name: PWM_Modulator_SaveConfig
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
*  PWM_Modulator_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Modulator_SaveConfig(void) 
{

    #if(!PWM_Modulator_UsingFixedFunction)
        #if(!PWM_Modulator_PWMModeIsCenterAligned)
            PWM_Modulator_backup.PWMPeriod = PWM_Modulator_ReadPeriod();
        #endif /* (!PWM_Modulator_PWMModeIsCenterAligned) */
        PWM_Modulator_backup.PWMUdb = PWM_Modulator_ReadCounter();
        #if (PWM_Modulator_UseStatus)
            PWM_Modulator_backup.InterruptMaskValue = PWM_Modulator_STATUS_MASK;
        #endif /* (PWM_Modulator_UseStatus) */

        #if(PWM_Modulator_DeadBandMode == PWM_Modulator__B_PWM__DBM_256_CLOCKS || \
            PWM_Modulator_DeadBandMode == PWM_Modulator__B_PWM__DBM_2_4_CLOCKS)
            PWM_Modulator_backup.PWMdeadBandValue = PWM_Modulator_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Modulator_KillModeMinTime)
             PWM_Modulator_backup.PWMKillCounterPeriod = PWM_Modulator_ReadKillTime();
        #endif /* (PWM_Modulator_KillModeMinTime) */

        #if(PWM_Modulator_UseControl)
            PWM_Modulator_backup.PWMControlRegister = PWM_Modulator_ReadControlRegister();
        #endif /* (PWM_Modulator_UseControl) */
    #endif  /* (!PWM_Modulator_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Modulator_RestoreConfig
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
*  PWM_Modulator_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Modulator_RestoreConfig(void) 
{
        #if(!PWM_Modulator_UsingFixedFunction)
            #if(!PWM_Modulator_PWMModeIsCenterAligned)
                PWM_Modulator_WritePeriod(PWM_Modulator_backup.PWMPeriod);
            #endif /* (!PWM_Modulator_PWMModeIsCenterAligned) */

            PWM_Modulator_WriteCounter(PWM_Modulator_backup.PWMUdb);

            #if (PWM_Modulator_UseStatus)
                PWM_Modulator_STATUS_MASK = PWM_Modulator_backup.InterruptMaskValue;
            #endif /* (PWM_Modulator_UseStatus) */

            #if(PWM_Modulator_DeadBandMode == PWM_Modulator__B_PWM__DBM_256_CLOCKS || \
                PWM_Modulator_DeadBandMode == PWM_Modulator__B_PWM__DBM_2_4_CLOCKS)
                PWM_Modulator_WriteDeadTime(PWM_Modulator_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Modulator_KillModeMinTime)
                PWM_Modulator_WriteKillTime(PWM_Modulator_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Modulator_KillModeMinTime) */

            #if(PWM_Modulator_UseControl)
                PWM_Modulator_WriteControlRegister(PWM_Modulator_backup.PWMControlRegister);
            #endif /* (PWM_Modulator_UseControl) */
        #endif  /* (!PWM_Modulator_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Modulator_Sleep
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
*  PWM_Modulator_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Modulator_Sleep(void) 
{
    #if(PWM_Modulator_UseControl)
        if(PWM_Modulator_CTRL_ENABLE == (PWM_Modulator_CONTROL & PWM_Modulator_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Modulator_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Modulator_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Modulator_UseControl) */

    /* Stop component */
    PWM_Modulator_Stop();

    /* Save registers configuration */
    PWM_Modulator_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Modulator_Wakeup
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
*  PWM_Modulator_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Modulator_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Modulator_RestoreConfig();

    if(PWM_Modulator_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Modulator_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
