/*******************************************************************************
* File Name: LowF_OnePWM_PM.c
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

#include "LowF_OnePWM.h"

static LowF_OnePWM_backupStruct LowF_OnePWM_backup;


/*******************************************************************************
* Function Name: LowF_OnePWM_SaveConfig
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
*  LowF_OnePWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LowF_OnePWM_SaveConfig(void) 
{

    #if(!LowF_OnePWM_UsingFixedFunction)
        #if(!LowF_OnePWM_PWMModeIsCenterAligned)
            LowF_OnePWM_backup.PWMPeriod = LowF_OnePWM_ReadPeriod();
        #endif /* (!LowF_OnePWM_PWMModeIsCenterAligned) */
        LowF_OnePWM_backup.PWMUdb = LowF_OnePWM_ReadCounter();
        #if (LowF_OnePWM_UseStatus)
            LowF_OnePWM_backup.InterruptMaskValue = LowF_OnePWM_STATUS_MASK;
        #endif /* (LowF_OnePWM_UseStatus) */

        #if(LowF_OnePWM_DeadBandMode == LowF_OnePWM__B_PWM__DBM_256_CLOCKS || \
            LowF_OnePWM_DeadBandMode == LowF_OnePWM__B_PWM__DBM_2_4_CLOCKS)
            LowF_OnePWM_backup.PWMdeadBandValue = LowF_OnePWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(LowF_OnePWM_KillModeMinTime)
             LowF_OnePWM_backup.PWMKillCounterPeriod = LowF_OnePWM_ReadKillTime();
        #endif /* (LowF_OnePWM_KillModeMinTime) */

        #if(LowF_OnePWM_UseControl)
            LowF_OnePWM_backup.PWMControlRegister = LowF_OnePWM_ReadControlRegister();
        #endif /* (LowF_OnePWM_UseControl) */
    #endif  /* (!LowF_OnePWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LowF_OnePWM_RestoreConfig
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
*  LowF_OnePWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LowF_OnePWM_RestoreConfig(void) 
{
        #if(!LowF_OnePWM_UsingFixedFunction)
            #if(!LowF_OnePWM_PWMModeIsCenterAligned)
                LowF_OnePWM_WritePeriod(LowF_OnePWM_backup.PWMPeriod);
            #endif /* (!LowF_OnePWM_PWMModeIsCenterAligned) */

            LowF_OnePWM_WriteCounter(LowF_OnePWM_backup.PWMUdb);

            #if (LowF_OnePWM_UseStatus)
                LowF_OnePWM_STATUS_MASK = LowF_OnePWM_backup.InterruptMaskValue;
            #endif /* (LowF_OnePWM_UseStatus) */

            #if(LowF_OnePWM_DeadBandMode == LowF_OnePWM__B_PWM__DBM_256_CLOCKS || \
                LowF_OnePWM_DeadBandMode == LowF_OnePWM__B_PWM__DBM_2_4_CLOCKS)
                LowF_OnePWM_WriteDeadTime(LowF_OnePWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(LowF_OnePWM_KillModeMinTime)
                LowF_OnePWM_WriteKillTime(LowF_OnePWM_backup.PWMKillCounterPeriod);
            #endif /* (LowF_OnePWM_KillModeMinTime) */

            #if(LowF_OnePWM_UseControl)
                LowF_OnePWM_WriteControlRegister(LowF_OnePWM_backup.PWMControlRegister);
            #endif /* (LowF_OnePWM_UseControl) */
        #endif  /* (!LowF_OnePWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: LowF_OnePWM_Sleep
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
*  LowF_OnePWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LowF_OnePWM_Sleep(void) 
{
    #if(LowF_OnePWM_UseControl)
        if(LowF_OnePWM_CTRL_ENABLE == (LowF_OnePWM_CONTROL & LowF_OnePWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            LowF_OnePWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LowF_OnePWM_backup.PWMEnableState = 0u;
        }
    #endif /* (LowF_OnePWM_UseControl) */

    /* Stop component */
    LowF_OnePWM_Stop();

    /* Save registers configuration */
    LowF_OnePWM_SaveConfig();
}


/*******************************************************************************
* Function Name: LowF_OnePWM_Wakeup
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
*  LowF_OnePWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LowF_OnePWM_Wakeup(void) 
{
     /* Restore registers values */
    LowF_OnePWM_RestoreConfig();

    if(LowF_OnePWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LowF_OnePWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
