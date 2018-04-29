/*******************************************************************************
* File Name: PWM_Recon_PM.c
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

#include "PWM_Recon.h"

static PWM_Recon_backupStruct PWM_Recon_backup;


/*******************************************************************************
* Function Name: PWM_Recon_SaveConfig
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
*  PWM_Recon_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Recon_SaveConfig(void) 
{

    #if(!PWM_Recon_UsingFixedFunction)
        #if(!PWM_Recon_PWMModeIsCenterAligned)
            PWM_Recon_backup.PWMPeriod = PWM_Recon_ReadPeriod();
        #endif /* (!PWM_Recon_PWMModeIsCenterAligned) */
        PWM_Recon_backup.PWMUdb = PWM_Recon_ReadCounter();
        #if (PWM_Recon_UseStatus)
            PWM_Recon_backup.InterruptMaskValue = PWM_Recon_STATUS_MASK;
        #endif /* (PWM_Recon_UseStatus) */

        #if(PWM_Recon_DeadBandMode == PWM_Recon__B_PWM__DBM_256_CLOCKS || \
            PWM_Recon_DeadBandMode == PWM_Recon__B_PWM__DBM_2_4_CLOCKS)
            PWM_Recon_backup.PWMdeadBandValue = PWM_Recon_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Recon_KillModeMinTime)
             PWM_Recon_backup.PWMKillCounterPeriod = PWM_Recon_ReadKillTime();
        #endif /* (PWM_Recon_KillModeMinTime) */

        #if(PWM_Recon_UseControl)
            PWM_Recon_backup.PWMControlRegister = PWM_Recon_ReadControlRegister();
        #endif /* (PWM_Recon_UseControl) */
    #endif  /* (!PWM_Recon_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Recon_RestoreConfig
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
*  PWM_Recon_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Recon_RestoreConfig(void) 
{
        #if(!PWM_Recon_UsingFixedFunction)
            #if(!PWM_Recon_PWMModeIsCenterAligned)
                PWM_Recon_WritePeriod(PWM_Recon_backup.PWMPeriod);
            #endif /* (!PWM_Recon_PWMModeIsCenterAligned) */

            PWM_Recon_WriteCounter(PWM_Recon_backup.PWMUdb);

            #if (PWM_Recon_UseStatus)
                PWM_Recon_STATUS_MASK = PWM_Recon_backup.InterruptMaskValue;
            #endif /* (PWM_Recon_UseStatus) */

            #if(PWM_Recon_DeadBandMode == PWM_Recon__B_PWM__DBM_256_CLOCKS || \
                PWM_Recon_DeadBandMode == PWM_Recon__B_PWM__DBM_2_4_CLOCKS)
                PWM_Recon_WriteDeadTime(PWM_Recon_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Recon_KillModeMinTime)
                PWM_Recon_WriteKillTime(PWM_Recon_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Recon_KillModeMinTime) */

            #if(PWM_Recon_UseControl)
                PWM_Recon_WriteControlRegister(PWM_Recon_backup.PWMControlRegister);
            #endif /* (PWM_Recon_UseControl) */
        #endif  /* (!PWM_Recon_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Recon_Sleep
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
*  PWM_Recon_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Recon_Sleep(void) 
{
    #if(PWM_Recon_UseControl)
        if(PWM_Recon_CTRL_ENABLE == (PWM_Recon_CONTROL & PWM_Recon_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Recon_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Recon_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Recon_UseControl) */

    /* Stop component */
    PWM_Recon_Stop();

    /* Save registers configuration */
    PWM_Recon_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Recon_Wakeup
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
*  PWM_Recon_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Recon_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Recon_RestoreConfig();

    if(PWM_Recon_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Recon_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
