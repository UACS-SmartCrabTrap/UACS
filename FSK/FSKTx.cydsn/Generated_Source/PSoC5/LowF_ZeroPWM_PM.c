/*******************************************************************************
* File Name: LowF_ZeroPWM_PM.c
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

#include "LowF_ZeroPWM.h"

static LowF_ZeroPWM_backupStruct LowF_ZeroPWM_backup;


/*******************************************************************************
* Function Name: LowF_ZeroPWM_SaveConfig
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
*  LowF_ZeroPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LowF_ZeroPWM_SaveConfig(void) 
{

    #if(!LowF_ZeroPWM_UsingFixedFunction)
        #if(!LowF_ZeroPWM_PWMModeIsCenterAligned)
            LowF_ZeroPWM_backup.PWMPeriod = LowF_ZeroPWM_ReadPeriod();
        #endif /* (!LowF_ZeroPWM_PWMModeIsCenterAligned) */
        LowF_ZeroPWM_backup.PWMUdb = LowF_ZeroPWM_ReadCounter();
        #if (LowF_ZeroPWM_UseStatus)
            LowF_ZeroPWM_backup.InterruptMaskValue = LowF_ZeroPWM_STATUS_MASK;
        #endif /* (LowF_ZeroPWM_UseStatus) */

        #if(LowF_ZeroPWM_DeadBandMode == LowF_ZeroPWM__B_PWM__DBM_256_CLOCKS || \
            LowF_ZeroPWM_DeadBandMode == LowF_ZeroPWM__B_PWM__DBM_2_4_CLOCKS)
            LowF_ZeroPWM_backup.PWMdeadBandValue = LowF_ZeroPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(LowF_ZeroPWM_KillModeMinTime)
             LowF_ZeroPWM_backup.PWMKillCounterPeriod = LowF_ZeroPWM_ReadKillTime();
        #endif /* (LowF_ZeroPWM_KillModeMinTime) */

        #if(LowF_ZeroPWM_UseControl)
            LowF_ZeroPWM_backup.PWMControlRegister = LowF_ZeroPWM_ReadControlRegister();
        #endif /* (LowF_ZeroPWM_UseControl) */
    #endif  /* (!LowF_ZeroPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LowF_ZeroPWM_RestoreConfig
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
*  LowF_ZeroPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LowF_ZeroPWM_RestoreConfig(void) 
{
        #if(!LowF_ZeroPWM_UsingFixedFunction)
            #if(!LowF_ZeroPWM_PWMModeIsCenterAligned)
                LowF_ZeroPWM_WritePeriod(LowF_ZeroPWM_backup.PWMPeriod);
            #endif /* (!LowF_ZeroPWM_PWMModeIsCenterAligned) */

            LowF_ZeroPWM_WriteCounter(LowF_ZeroPWM_backup.PWMUdb);

            #if (LowF_ZeroPWM_UseStatus)
                LowF_ZeroPWM_STATUS_MASK = LowF_ZeroPWM_backup.InterruptMaskValue;
            #endif /* (LowF_ZeroPWM_UseStatus) */

            #if(LowF_ZeroPWM_DeadBandMode == LowF_ZeroPWM__B_PWM__DBM_256_CLOCKS || \
                LowF_ZeroPWM_DeadBandMode == LowF_ZeroPWM__B_PWM__DBM_2_4_CLOCKS)
                LowF_ZeroPWM_WriteDeadTime(LowF_ZeroPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(LowF_ZeroPWM_KillModeMinTime)
                LowF_ZeroPWM_WriteKillTime(LowF_ZeroPWM_backup.PWMKillCounterPeriod);
            #endif /* (LowF_ZeroPWM_KillModeMinTime) */

            #if(LowF_ZeroPWM_UseControl)
                LowF_ZeroPWM_WriteControlRegister(LowF_ZeroPWM_backup.PWMControlRegister);
            #endif /* (LowF_ZeroPWM_UseControl) */
        #endif  /* (!LowF_ZeroPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: LowF_ZeroPWM_Sleep
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
*  LowF_ZeroPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LowF_ZeroPWM_Sleep(void) 
{
    #if(LowF_ZeroPWM_UseControl)
        if(LowF_ZeroPWM_CTRL_ENABLE == (LowF_ZeroPWM_CONTROL & LowF_ZeroPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            LowF_ZeroPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LowF_ZeroPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (LowF_ZeroPWM_UseControl) */

    /* Stop component */
    LowF_ZeroPWM_Stop();

    /* Save registers configuration */
    LowF_ZeroPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: LowF_ZeroPWM_Wakeup
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
*  LowF_ZeroPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LowF_ZeroPWM_Wakeup(void) 
{
     /* Restore registers values */
    LowF_ZeroPWM_RestoreConfig();

    if(LowF_ZeroPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LowF_ZeroPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
