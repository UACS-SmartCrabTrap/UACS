/*******************************************************************************
* File Name: ZeroPwm_PM.c
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

#include "ZeroPwm.h"

static ZeroPwm_backupStruct ZeroPwm_backup;


/*******************************************************************************
* Function Name: ZeroPwm_SaveConfig
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
*  ZeroPwm_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ZeroPwm_SaveConfig(void) 
{

    #if(!ZeroPwm_UsingFixedFunction)
        #if(!ZeroPwm_PWMModeIsCenterAligned)
            ZeroPwm_backup.PWMPeriod = ZeroPwm_ReadPeriod();
        #endif /* (!ZeroPwm_PWMModeIsCenterAligned) */
        ZeroPwm_backup.PWMUdb = ZeroPwm_ReadCounter();
        #if (ZeroPwm_UseStatus)
            ZeroPwm_backup.InterruptMaskValue = ZeroPwm_STATUS_MASK;
        #endif /* (ZeroPwm_UseStatus) */

        #if(ZeroPwm_DeadBandMode == ZeroPwm__B_PWM__DBM_256_CLOCKS || \
            ZeroPwm_DeadBandMode == ZeroPwm__B_PWM__DBM_2_4_CLOCKS)
            ZeroPwm_backup.PWMdeadBandValue = ZeroPwm_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(ZeroPwm_KillModeMinTime)
             ZeroPwm_backup.PWMKillCounterPeriod = ZeroPwm_ReadKillTime();
        #endif /* (ZeroPwm_KillModeMinTime) */

        #if(ZeroPwm_UseControl)
            ZeroPwm_backup.PWMControlRegister = ZeroPwm_ReadControlRegister();
        #endif /* (ZeroPwm_UseControl) */
    #endif  /* (!ZeroPwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ZeroPwm_RestoreConfig
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
*  ZeroPwm_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ZeroPwm_RestoreConfig(void) 
{
        #if(!ZeroPwm_UsingFixedFunction)
            #if(!ZeroPwm_PWMModeIsCenterAligned)
                ZeroPwm_WritePeriod(ZeroPwm_backup.PWMPeriod);
            #endif /* (!ZeroPwm_PWMModeIsCenterAligned) */

            ZeroPwm_WriteCounter(ZeroPwm_backup.PWMUdb);

            #if (ZeroPwm_UseStatus)
                ZeroPwm_STATUS_MASK = ZeroPwm_backup.InterruptMaskValue;
            #endif /* (ZeroPwm_UseStatus) */

            #if(ZeroPwm_DeadBandMode == ZeroPwm__B_PWM__DBM_256_CLOCKS || \
                ZeroPwm_DeadBandMode == ZeroPwm__B_PWM__DBM_2_4_CLOCKS)
                ZeroPwm_WriteDeadTime(ZeroPwm_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(ZeroPwm_KillModeMinTime)
                ZeroPwm_WriteKillTime(ZeroPwm_backup.PWMKillCounterPeriod);
            #endif /* (ZeroPwm_KillModeMinTime) */

            #if(ZeroPwm_UseControl)
                ZeroPwm_WriteControlRegister(ZeroPwm_backup.PWMControlRegister);
            #endif /* (ZeroPwm_UseControl) */
        #endif  /* (!ZeroPwm_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: ZeroPwm_Sleep
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
*  ZeroPwm_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ZeroPwm_Sleep(void) 
{
    #if(ZeroPwm_UseControl)
        if(ZeroPwm_CTRL_ENABLE == (ZeroPwm_CONTROL & ZeroPwm_CTRL_ENABLE))
        {
            /*Component is enabled */
            ZeroPwm_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            ZeroPwm_backup.PWMEnableState = 0u;
        }
    #endif /* (ZeroPwm_UseControl) */

    /* Stop component */
    ZeroPwm_Stop();

    /* Save registers configuration */
    ZeroPwm_SaveConfig();
}


/*******************************************************************************
* Function Name: ZeroPwm_Wakeup
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
*  ZeroPwm_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ZeroPwm_Wakeup(void) 
{
     /* Restore registers values */
    ZeroPwm_RestoreConfig();

    if(ZeroPwm_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        ZeroPwm_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
