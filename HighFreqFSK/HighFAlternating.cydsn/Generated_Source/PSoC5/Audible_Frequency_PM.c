/*******************************************************************************
* File Name: Audible_Frequency_PM.c
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

#include "Audible_Frequency.h"

static Audible_Frequency_backupStruct Audible_Frequency_backup;


/*******************************************************************************
* Function Name: Audible_Frequency_SaveConfig
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
*  Audible_Frequency_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Audible_Frequency_SaveConfig(void) 
{

    #if(!Audible_Frequency_UsingFixedFunction)
        #if(!Audible_Frequency_PWMModeIsCenterAligned)
            Audible_Frequency_backup.PWMPeriod = Audible_Frequency_ReadPeriod();
        #endif /* (!Audible_Frequency_PWMModeIsCenterAligned) */
        Audible_Frequency_backup.PWMUdb = Audible_Frequency_ReadCounter();
        #if (Audible_Frequency_UseStatus)
            Audible_Frequency_backup.InterruptMaskValue = Audible_Frequency_STATUS_MASK;
        #endif /* (Audible_Frequency_UseStatus) */

        #if(Audible_Frequency_DeadBandMode == Audible_Frequency__B_PWM__DBM_256_CLOCKS || \
            Audible_Frequency_DeadBandMode == Audible_Frequency__B_PWM__DBM_2_4_CLOCKS)
            Audible_Frequency_backup.PWMdeadBandValue = Audible_Frequency_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Audible_Frequency_KillModeMinTime)
             Audible_Frequency_backup.PWMKillCounterPeriod = Audible_Frequency_ReadKillTime();
        #endif /* (Audible_Frequency_KillModeMinTime) */

        #if(Audible_Frequency_UseControl)
            Audible_Frequency_backup.PWMControlRegister = Audible_Frequency_ReadControlRegister();
        #endif /* (Audible_Frequency_UseControl) */
    #endif  /* (!Audible_Frequency_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Audible_Frequency_RestoreConfig
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
*  Audible_Frequency_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Audible_Frequency_RestoreConfig(void) 
{
        #if(!Audible_Frequency_UsingFixedFunction)
            #if(!Audible_Frequency_PWMModeIsCenterAligned)
                Audible_Frequency_WritePeriod(Audible_Frequency_backup.PWMPeriod);
            #endif /* (!Audible_Frequency_PWMModeIsCenterAligned) */

            Audible_Frequency_WriteCounter(Audible_Frequency_backup.PWMUdb);

            #if (Audible_Frequency_UseStatus)
                Audible_Frequency_STATUS_MASK = Audible_Frequency_backup.InterruptMaskValue;
            #endif /* (Audible_Frequency_UseStatus) */

            #if(Audible_Frequency_DeadBandMode == Audible_Frequency__B_PWM__DBM_256_CLOCKS || \
                Audible_Frequency_DeadBandMode == Audible_Frequency__B_PWM__DBM_2_4_CLOCKS)
                Audible_Frequency_WriteDeadTime(Audible_Frequency_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Audible_Frequency_KillModeMinTime)
                Audible_Frequency_WriteKillTime(Audible_Frequency_backup.PWMKillCounterPeriod);
            #endif /* (Audible_Frequency_KillModeMinTime) */

            #if(Audible_Frequency_UseControl)
                Audible_Frequency_WriteControlRegister(Audible_Frequency_backup.PWMControlRegister);
            #endif /* (Audible_Frequency_UseControl) */
        #endif  /* (!Audible_Frequency_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Audible_Frequency_Sleep
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
*  Audible_Frequency_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Audible_Frequency_Sleep(void) 
{
    #if(Audible_Frequency_UseControl)
        if(Audible_Frequency_CTRL_ENABLE == (Audible_Frequency_CONTROL & Audible_Frequency_CTRL_ENABLE))
        {
            /*Component is enabled */
            Audible_Frequency_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Audible_Frequency_backup.PWMEnableState = 0u;
        }
    #endif /* (Audible_Frequency_UseControl) */

    /* Stop component */
    Audible_Frequency_Stop();

    /* Save registers configuration */
    Audible_Frequency_SaveConfig();
}


/*******************************************************************************
* Function Name: Audible_Frequency_Wakeup
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
*  Audible_Frequency_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Audible_Frequency_Wakeup(void) 
{
     /* Restore registers values */
    Audible_Frequency_RestoreConfig();

    if(Audible_Frequency_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Audible_Frequency_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
