/*******************************************************************************
* File Name: LowFPwm_PM.c
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

#include "LowFPwm.h"

static LowFPwm_backupStruct LowFPwm_backup;


/*******************************************************************************
* Function Name: LowFPwm_SaveConfig
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
*  LowFPwm_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LowFPwm_SaveConfig(void) 
{

    #if(!LowFPwm_UsingFixedFunction)
        #if(!LowFPwm_PWMModeIsCenterAligned)
            LowFPwm_backup.PWMPeriod = LowFPwm_ReadPeriod();
        #endif /* (!LowFPwm_PWMModeIsCenterAligned) */
        LowFPwm_backup.PWMUdb = LowFPwm_ReadCounter();
        #if (LowFPwm_UseStatus)
            LowFPwm_backup.InterruptMaskValue = LowFPwm_STATUS_MASK;
        #endif /* (LowFPwm_UseStatus) */

        #if(LowFPwm_DeadBandMode == LowFPwm__B_PWM__DBM_256_CLOCKS || \
            LowFPwm_DeadBandMode == LowFPwm__B_PWM__DBM_2_4_CLOCKS)
            LowFPwm_backup.PWMdeadBandValue = LowFPwm_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(LowFPwm_KillModeMinTime)
             LowFPwm_backup.PWMKillCounterPeriod = LowFPwm_ReadKillTime();
        #endif /* (LowFPwm_KillModeMinTime) */

        #if(LowFPwm_UseControl)
            LowFPwm_backup.PWMControlRegister = LowFPwm_ReadControlRegister();
        #endif /* (LowFPwm_UseControl) */
    #endif  /* (!LowFPwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LowFPwm_RestoreConfig
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
*  LowFPwm_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LowFPwm_RestoreConfig(void) 
{
        #if(!LowFPwm_UsingFixedFunction)
            #if(!LowFPwm_PWMModeIsCenterAligned)
                LowFPwm_WritePeriod(LowFPwm_backup.PWMPeriod);
            #endif /* (!LowFPwm_PWMModeIsCenterAligned) */

            LowFPwm_WriteCounter(LowFPwm_backup.PWMUdb);

            #if (LowFPwm_UseStatus)
                LowFPwm_STATUS_MASK = LowFPwm_backup.InterruptMaskValue;
            #endif /* (LowFPwm_UseStatus) */

            #if(LowFPwm_DeadBandMode == LowFPwm__B_PWM__DBM_256_CLOCKS || \
                LowFPwm_DeadBandMode == LowFPwm__B_PWM__DBM_2_4_CLOCKS)
                LowFPwm_WriteDeadTime(LowFPwm_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(LowFPwm_KillModeMinTime)
                LowFPwm_WriteKillTime(LowFPwm_backup.PWMKillCounterPeriod);
            #endif /* (LowFPwm_KillModeMinTime) */

            #if(LowFPwm_UseControl)
                LowFPwm_WriteControlRegister(LowFPwm_backup.PWMControlRegister);
            #endif /* (LowFPwm_UseControl) */
        #endif  /* (!LowFPwm_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: LowFPwm_Sleep
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
*  LowFPwm_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LowFPwm_Sleep(void) 
{
    #if(LowFPwm_UseControl)
        if(LowFPwm_CTRL_ENABLE == (LowFPwm_CONTROL & LowFPwm_CTRL_ENABLE))
        {
            /*Component is enabled */
            LowFPwm_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LowFPwm_backup.PWMEnableState = 0u;
        }
    #endif /* (LowFPwm_UseControl) */

    /* Stop component */
    LowFPwm_Stop();

    /* Save registers configuration */
    LowFPwm_SaveConfig();
}


/*******************************************************************************
* Function Name: LowFPwm_Wakeup
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
*  LowFPwm_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LowFPwm_Wakeup(void) 
{
     /* Restore registers values */
    LowFPwm_RestoreConfig();

    if(LowFPwm_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LowFPwm_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
