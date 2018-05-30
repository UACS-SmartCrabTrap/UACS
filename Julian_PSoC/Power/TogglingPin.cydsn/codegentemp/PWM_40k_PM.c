/*******************************************************************************
* File Name: PWM_40k_PM.c
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

#include "PWM_40k.h"

static PWM_40k_backupStruct PWM_40k_backup;


/*******************************************************************************
* Function Name: PWM_40k_SaveConfig
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
*  PWM_40k_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_40k_SaveConfig(void) 
{

    #if(!PWM_40k_UsingFixedFunction)
        #if(!PWM_40k_PWMModeIsCenterAligned)
            PWM_40k_backup.PWMPeriod = PWM_40k_ReadPeriod();
        #endif /* (!PWM_40k_PWMModeIsCenterAligned) */
        PWM_40k_backup.PWMUdb = PWM_40k_ReadCounter();
        #if (PWM_40k_UseStatus)
            PWM_40k_backup.InterruptMaskValue = PWM_40k_STATUS_MASK;
        #endif /* (PWM_40k_UseStatus) */

        #if(PWM_40k_DeadBandMode == PWM_40k__B_PWM__DBM_256_CLOCKS || \
            PWM_40k_DeadBandMode == PWM_40k__B_PWM__DBM_2_4_CLOCKS)
            PWM_40k_backup.PWMdeadBandValue = PWM_40k_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_40k_KillModeMinTime)
             PWM_40k_backup.PWMKillCounterPeriod = PWM_40k_ReadKillTime();
        #endif /* (PWM_40k_KillModeMinTime) */

        #if(PWM_40k_UseControl)
            PWM_40k_backup.PWMControlRegister = PWM_40k_ReadControlRegister();
        #endif /* (PWM_40k_UseControl) */
    #endif  /* (!PWM_40k_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_40k_RestoreConfig
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
*  PWM_40k_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_40k_RestoreConfig(void) 
{
        #if(!PWM_40k_UsingFixedFunction)
            #if(!PWM_40k_PWMModeIsCenterAligned)
                PWM_40k_WritePeriod(PWM_40k_backup.PWMPeriod);
            #endif /* (!PWM_40k_PWMModeIsCenterAligned) */

            PWM_40k_WriteCounter(PWM_40k_backup.PWMUdb);

            #if (PWM_40k_UseStatus)
                PWM_40k_STATUS_MASK = PWM_40k_backup.InterruptMaskValue;
            #endif /* (PWM_40k_UseStatus) */

            #if(PWM_40k_DeadBandMode == PWM_40k__B_PWM__DBM_256_CLOCKS || \
                PWM_40k_DeadBandMode == PWM_40k__B_PWM__DBM_2_4_CLOCKS)
                PWM_40k_WriteDeadTime(PWM_40k_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_40k_KillModeMinTime)
                PWM_40k_WriteKillTime(PWM_40k_backup.PWMKillCounterPeriod);
            #endif /* (PWM_40k_KillModeMinTime) */

            #if(PWM_40k_UseControl)
                PWM_40k_WriteControlRegister(PWM_40k_backup.PWMControlRegister);
            #endif /* (PWM_40k_UseControl) */
        #endif  /* (!PWM_40k_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_40k_Sleep
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
*  PWM_40k_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_40k_Sleep(void) 
{
    #if(PWM_40k_UseControl)
        if(PWM_40k_CTRL_ENABLE == (PWM_40k_CONTROL & PWM_40k_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_40k_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_40k_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_40k_UseControl) */

    /* Stop component */
    PWM_40k_Stop();

    /* Save registers configuration */
    PWM_40k_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_40k_Wakeup
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
*  PWM_40k_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_40k_Wakeup(void) 
{
     /* Restore registers values */
    PWM_40k_RestoreConfig();

    if(PWM_40k_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_40k_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
