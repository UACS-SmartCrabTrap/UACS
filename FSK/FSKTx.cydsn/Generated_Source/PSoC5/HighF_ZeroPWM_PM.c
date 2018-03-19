/*******************************************************************************
* File Name: HighF_ZeroPWM_PM.c
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

#include "HighF_ZeroPWM.h"

static HighF_ZeroPWM_backupStruct HighF_ZeroPWM_backup;


/*******************************************************************************
* Function Name: HighF_ZeroPWM_SaveConfig
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
*  HighF_ZeroPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HighF_ZeroPWM_SaveConfig(void) 
{

    #if(!HighF_ZeroPWM_UsingFixedFunction)
        #if(!HighF_ZeroPWM_PWMModeIsCenterAligned)
            HighF_ZeroPWM_backup.PWMPeriod = HighF_ZeroPWM_ReadPeriod();
        #endif /* (!HighF_ZeroPWM_PWMModeIsCenterAligned) */
        HighF_ZeroPWM_backup.PWMUdb = HighF_ZeroPWM_ReadCounter();
        #if (HighF_ZeroPWM_UseStatus)
            HighF_ZeroPWM_backup.InterruptMaskValue = HighF_ZeroPWM_STATUS_MASK;
        #endif /* (HighF_ZeroPWM_UseStatus) */

        #if(HighF_ZeroPWM_DeadBandMode == HighF_ZeroPWM__B_PWM__DBM_256_CLOCKS || \
            HighF_ZeroPWM_DeadBandMode == HighF_ZeroPWM__B_PWM__DBM_2_4_CLOCKS)
            HighF_ZeroPWM_backup.PWMdeadBandValue = HighF_ZeroPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(HighF_ZeroPWM_KillModeMinTime)
             HighF_ZeroPWM_backup.PWMKillCounterPeriod = HighF_ZeroPWM_ReadKillTime();
        #endif /* (HighF_ZeroPWM_KillModeMinTime) */

        #if(HighF_ZeroPWM_UseControl)
            HighF_ZeroPWM_backup.PWMControlRegister = HighF_ZeroPWM_ReadControlRegister();
        #endif /* (HighF_ZeroPWM_UseControl) */
    #endif  /* (!HighF_ZeroPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_ZeroPWM_RestoreConfig
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
*  HighF_ZeroPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HighF_ZeroPWM_RestoreConfig(void) 
{
        #if(!HighF_ZeroPWM_UsingFixedFunction)
            #if(!HighF_ZeroPWM_PWMModeIsCenterAligned)
                HighF_ZeroPWM_WritePeriod(HighF_ZeroPWM_backup.PWMPeriod);
            #endif /* (!HighF_ZeroPWM_PWMModeIsCenterAligned) */

            HighF_ZeroPWM_WriteCounter(HighF_ZeroPWM_backup.PWMUdb);

            #if (HighF_ZeroPWM_UseStatus)
                HighF_ZeroPWM_STATUS_MASK = HighF_ZeroPWM_backup.InterruptMaskValue;
            #endif /* (HighF_ZeroPWM_UseStatus) */

            #if(HighF_ZeroPWM_DeadBandMode == HighF_ZeroPWM__B_PWM__DBM_256_CLOCKS || \
                HighF_ZeroPWM_DeadBandMode == HighF_ZeroPWM__B_PWM__DBM_2_4_CLOCKS)
                HighF_ZeroPWM_WriteDeadTime(HighF_ZeroPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(HighF_ZeroPWM_KillModeMinTime)
                HighF_ZeroPWM_WriteKillTime(HighF_ZeroPWM_backup.PWMKillCounterPeriod);
            #endif /* (HighF_ZeroPWM_KillModeMinTime) */

            #if(HighF_ZeroPWM_UseControl)
                HighF_ZeroPWM_WriteControlRegister(HighF_ZeroPWM_backup.PWMControlRegister);
            #endif /* (HighF_ZeroPWM_UseControl) */
        #endif  /* (!HighF_ZeroPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: HighF_ZeroPWM_Sleep
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
*  HighF_ZeroPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void HighF_ZeroPWM_Sleep(void) 
{
    #if(HighF_ZeroPWM_UseControl)
        if(HighF_ZeroPWM_CTRL_ENABLE == (HighF_ZeroPWM_CONTROL & HighF_ZeroPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            HighF_ZeroPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            HighF_ZeroPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (HighF_ZeroPWM_UseControl) */

    /* Stop component */
    HighF_ZeroPWM_Stop();

    /* Save registers configuration */
    HighF_ZeroPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: HighF_ZeroPWM_Wakeup
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
*  HighF_ZeroPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HighF_ZeroPWM_Wakeup(void) 
{
     /* Restore registers values */
    HighF_ZeroPWM_RestoreConfig();

    if(HighF_ZeroPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        HighF_ZeroPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
