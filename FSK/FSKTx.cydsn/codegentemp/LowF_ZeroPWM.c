/*******************************************************************************
* File Name: LowF_ZeroPWM.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "LowF_ZeroPWM.h"

/* Error message for removed <resource> through optimization */
#ifdef LowF_ZeroPWM_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* LowF_ZeroPWM_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 LowF_ZeroPWM_initVar = 0u;


/*******************************************************************************
* Function Name: LowF_ZeroPWM_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LowF_ZeroPWM_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void LowF_ZeroPWM_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(LowF_ZeroPWM_initVar == 0u)
    {
        LowF_ZeroPWM_Init();
        LowF_ZeroPWM_initVar = 1u;
    }
    LowF_ZeroPWM_Enable();

}


/*******************************************************************************
* Function Name: LowF_ZeroPWM_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  LowF_ZeroPWM_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LowF_ZeroPWM_Init(void) 
{
    #if (LowF_ZeroPWM_UsingFixedFunction || LowF_ZeroPWM_UseControl)
        uint8 ctrl;
    #endif /* (LowF_ZeroPWM_UsingFixedFunction || LowF_ZeroPWM_UseControl) */

    #if(!LowF_ZeroPWM_UsingFixedFunction)
        #if(LowF_ZeroPWM_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 LowF_ZeroPWM_interruptState;
        #endif /* (LowF_ZeroPWM_UseStatus) */
    #endif /* (!LowF_ZeroPWM_UsingFixedFunction) */

    #if (LowF_ZeroPWM_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        LowF_ZeroPWM_CONTROL |= LowF_ZeroPWM_CFG0_MODE;
        #if (LowF_ZeroPWM_DeadBand2_4)
            LowF_ZeroPWM_CONTROL |= LowF_ZeroPWM_CFG0_DB;
        #endif /* (LowF_ZeroPWM_DeadBand2_4) */

        ctrl = LowF_ZeroPWM_CONTROL3 & ((uint8 )(~LowF_ZeroPWM_CTRL_CMPMODE1_MASK));
        LowF_ZeroPWM_CONTROL3 = ctrl | LowF_ZeroPWM_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        LowF_ZeroPWM_RT1 &= ((uint8)(~LowF_ZeroPWM_RT1_MASK));
        LowF_ZeroPWM_RT1 |= LowF_ZeroPWM_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        LowF_ZeroPWM_RT1 &= ((uint8)(~LowF_ZeroPWM_SYNCDSI_MASK));
        LowF_ZeroPWM_RT1 |= LowF_ZeroPWM_SYNCDSI_EN;

    #elif (LowF_ZeroPWM_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = LowF_ZeroPWM_CONTROL & ((uint8)(~LowF_ZeroPWM_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~LowF_ZeroPWM_CTRL_CMPMODE1_MASK));
        LowF_ZeroPWM_CONTROL = ctrl | LowF_ZeroPWM_DEFAULT_COMPARE2_MODE |
                                   LowF_ZeroPWM_DEFAULT_COMPARE1_MODE;
    #endif /* (LowF_ZeroPWM_UsingFixedFunction) */

    #if (!LowF_ZeroPWM_UsingFixedFunction)
        #if (LowF_ZeroPWM_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            LowF_ZeroPWM_AUX_CONTROLDP0 |= (LowF_ZeroPWM_AUX_CTRL_FIFO0_CLR);
        #else /* (LowF_ZeroPWM_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            LowF_ZeroPWM_AUX_CONTROLDP0 |= (LowF_ZeroPWM_AUX_CTRL_FIFO0_CLR);
            LowF_ZeroPWM_AUX_CONTROLDP1 |= (LowF_ZeroPWM_AUX_CTRL_FIFO0_CLR);
        #endif /* (LowF_ZeroPWM_Resolution == 8) */

        LowF_ZeroPWM_WriteCounter(LowF_ZeroPWM_INIT_PERIOD_VALUE);
    #endif /* (!LowF_ZeroPWM_UsingFixedFunction) */

    LowF_ZeroPWM_WritePeriod(LowF_ZeroPWM_INIT_PERIOD_VALUE);

        #if (LowF_ZeroPWM_UseOneCompareMode)
            LowF_ZeroPWM_WriteCompare(LowF_ZeroPWM_INIT_COMPARE_VALUE1);
        #else
            LowF_ZeroPWM_WriteCompare1(LowF_ZeroPWM_INIT_COMPARE_VALUE1);
            LowF_ZeroPWM_WriteCompare2(LowF_ZeroPWM_INIT_COMPARE_VALUE2);
        #endif /* (LowF_ZeroPWM_UseOneCompareMode) */

        #if (LowF_ZeroPWM_KillModeMinTime)
            LowF_ZeroPWM_WriteKillTime(LowF_ZeroPWM_MinimumKillTime);
        #endif /* (LowF_ZeroPWM_KillModeMinTime) */

        #if (LowF_ZeroPWM_DeadBandUsed)
            LowF_ZeroPWM_WriteDeadTime(LowF_ZeroPWM_INIT_DEAD_TIME);
        #endif /* (LowF_ZeroPWM_DeadBandUsed) */

    #if (LowF_ZeroPWM_UseStatus || LowF_ZeroPWM_UsingFixedFunction)
        LowF_ZeroPWM_SetInterruptMode(LowF_ZeroPWM_INIT_INTERRUPTS_MODE);
    #endif /* (LowF_ZeroPWM_UseStatus || LowF_ZeroPWM_UsingFixedFunction) */

    #if (LowF_ZeroPWM_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        LowF_ZeroPWM_GLOBAL_ENABLE |= LowF_ZeroPWM_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        LowF_ZeroPWM_CONTROL2 |= LowF_ZeroPWM_CTRL2_IRQ_SEL;
    #else
        #if(LowF_ZeroPWM_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            LowF_ZeroPWM_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            LowF_ZeroPWM_STATUS_AUX_CTRL |= LowF_ZeroPWM_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(LowF_ZeroPWM_interruptState);

            /* Clear the FIFO to enable the LowF_ZeroPWM_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            LowF_ZeroPWM_ClearFIFO();
        #endif /* (LowF_ZeroPWM_UseStatus) */
    #endif /* (LowF_ZeroPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LowF_ZeroPWM_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void LowF_ZeroPWM_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (LowF_ZeroPWM_UsingFixedFunction)
        LowF_ZeroPWM_GLOBAL_ENABLE |= LowF_ZeroPWM_BLOCK_EN_MASK;
        LowF_ZeroPWM_GLOBAL_STBY_ENABLE |= LowF_ZeroPWM_BLOCK_STBY_EN_MASK;
    #endif /* (LowF_ZeroPWM_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (LowF_ZeroPWM_UseControl || LowF_ZeroPWM_UsingFixedFunction)
        LowF_ZeroPWM_CONTROL |= LowF_ZeroPWM_CTRL_ENABLE;
    #endif /* (LowF_ZeroPWM_UseControl || LowF_ZeroPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LowF_ZeroPWM_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void LowF_ZeroPWM_Stop(void) 
{
    #if (LowF_ZeroPWM_UseControl || LowF_ZeroPWM_UsingFixedFunction)
        LowF_ZeroPWM_CONTROL &= ((uint8)(~LowF_ZeroPWM_CTRL_ENABLE));
    #endif /* (LowF_ZeroPWM_UseControl || LowF_ZeroPWM_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (LowF_ZeroPWM_UsingFixedFunction)
        LowF_ZeroPWM_GLOBAL_ENABLE &= ((uint8)(~LowF_ZeroPWM_BLOCK_EN_MASK));
        LowF_ZeroPWM_GLOBAL_STBY_ENABLE &= ((uint8)(~LowF_ZeroPWM_BLOCK_STBY_EN_MASK));
    #endif /* (LowF_ZeroPWM_UsingFixedFunction) */
}

#if (LowF_ZeroPWM_UseOneCompareMode)
    #if (LowF_ZeroPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: LowF_ZeroPWM_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void LowF_ZeroPWM_SetCompareMode(uint8 comparemode) 
        {
            #if(LowF_ZeroPWM_UsingFixedFunction)

                #if(0 != LowF_ZeroPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << LowF_ZeroPWM_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != LowF_ZeroPWM_CTRL_CMPMODE1_SHIFT) */

                LowF_ZeroPWM_CONTROL3 &= ((uint8)(~LowF_ZeroPWM_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                LowF_ZeroPWM_CONTROL3 |= comparemodemasked;

            #elif (LowF_ZeroPWM_UseControl)

                #if(0 != LowF_ZeroPWM_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << LowF_ZeroPWM_CTRL_CMPMODE1_SHIFT)) &
                                                LowF_ZeroPWM_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & LowF_ZeroPWM_CTRL_CMPMODE1_MASK;
                #endif /* (0 != LowF_ZeroPWM_CTRL_CMPMODE1_SHIFT) */

                #if(0 != LowF_ZeroPWM_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << LowF_ZeroPWM_CTRL_CMPMODE2_SHIFT)) &
                                               LowF_ZeroPWM_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & LowF_ZeroPWM_CTRL_CMPMODE2_MASK;
                #endif /* (0 != LowF_ZeroPWM_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                LowF_ZeroPWM_CONTROL &= ((uint8)(~(LowF_ZeroPWM_CTRL_CMPMODE1_MASK |
                                            LowF_ZeroPWM_CTRL_CMPMODE2_MASK)));
                LowF_ZeroPWM_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (LowF_ZeroPWM_UsingFixedFunction) */
        }
    #endif /* LowF_ZeroPWM_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (LowF_ZeroPWM_CompareMode1SW)


        /*******************************************************************************
        * Function Name: LowF_ZeroPWM_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void LowF_ZeroPWM_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != LowF_ZeroPWM_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << LowF_ZeroPWM_CTRL_CMPMODE1_SHIFT)) &
                                           LowF_ZeroPWM_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & LowF_ZeroPWM_CTRL_CMPMODE1_MASK;
            #endif /* (0 != LowF_ZeroPWM_CTRL_CMPMODE1_SHIFT) */

            #if (LowF_ZeroPWM_UseControl)
                LowF_ZeroPWM_CONTROL &= ((uint8)(~LowF_ZeroPWM_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                LowF_ZeroPWM_CONTROL |= comparemodemasked;
            #endif /* (LowF_ZeroPWM_UseControl) */
        }
    #endif /* LowF_ZeroPWM_CompareMode1SW */

#if (LowF_ZeroPWM_CompareMode2SW)


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LowF_ZeroPWM_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != LowF_ZeroPWM_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << LowF_ZeroPWM_CTRL_CMPMODE2_SHIFT)) &
                                                 LowF_ZeroPWM_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & LowF_ZeroPWM_CTRL_CMPMODE2_MASK;
        #endif /* (0 != LowF_ZeroPWM_CTRL_CMPMODE2_SHIFT) */

        #if (LowF_ZeroPWM_UseControl)
            LowF_ZeroPWM_CONTROL &= ((uint8)(~LowF_ZeroPWM_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            LowF_ZeroPWM_CONTROL |= comparemodemasked;
        #endif /* (LowF_ZeroPWM_UseControl) */
    }
    #endif /*LowF_ZeroPWM_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!LowF_ZeroPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void LowF_ZeroPWM_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(LowF_ZeroPWM_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 LowF_ZeroPWM_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(LowF_ZeroPWM_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(LowF_ZeroPWM_CAPTURE_LSB_PTR));
    }

    #if (LowF_ZeroPWM_UseStatus)


        /*******************************************************************************
        * Function Name: LowF_ZeroPWM_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void LowF_ZeroPWM_ClearFIFO(void) 
        {
            while(0u != (LowF_ZeroPWM_ReadStatusRegister() & LowF_ZeroPWM_STATUS_FIFONEMPTY))
            {
                (void)LowF_ZeroPWM_ReadCapture();
            }
        }

    #endif /* LowF_ZeroPWM_UseStatus */

#endif /* !LowF_ZeroPWM_UsingFixedFunction */


/*******************************************************************************
* Function Name: LowF_ZeroPWM_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void LowF_ZeroPWM_WritePeriod(uint16 period) 
{
    #if(LowF_ZeroPWM_UsingFixedFunction)
        CY_SET_REG16(LowF_ZeroPWM_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(LowF_ZeroPWM_PERIOD_LSB_PTR, period);
    #endif /* (LowF_ZeroPWM_UsingFixedFunction) */
}

#if (LowF_ZeroPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void LowF_ZeroPWM_WriteCompare(uint16 compare) \
                                       
    {
        #if(LowF_ZeroPWM_UsingFixedFunction)
            CY_SET_REG16(LowF_ZeroPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(LowF_ZeroPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (LowF_ZeroPWM_UsingFixedFunction) */

        #if (LowF_ZeroPWM_PWMMode == LowF_ZeroPWM__B_PWM__DITHER)
            #if(LowF_ZeroPWM_UsingFixedFunction)
                CY_SET_REG16(LowF_ZeroPWM_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(LowF_ZeroPWM_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (LowF_ZeroPWM_UsingFixedFunction) */
        #endif /* (LowF_ZeroPWM_PWMMode == LowF_ZeroPWM__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LowF_ZeroPWM_WriteCompare1(uint16 compare) \
                                        
    {
        #if(LowF_ZeroPWM_UsingFixedFunction)
            CY_SET_REG16(LowF_ZeroPWM_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(LowF_ZeroPWM_COMPARE1_LSB_PTR, compare);
        #endif /* (LowF_ZeroPWM_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LowF_ZeroPWM_WriteCompare2(uint16 compare) \
                                        
    {
        #if(LowF_ZeroPWM_UsingFixedFunction)
            CY_SET_REG16(LowF_ZeroPWM_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(LowF_ZeroPWM_COMPARE2_LSB_PTR, compare);
        #endif /* (LowF_ZeroPWM_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (LowF_ZeroPWM_DeadBandUsed)


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LowF_ZeroPWM_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!LowF_ZeroPWM_DeadBand2_4)
            CY_SET_REG8(LowF_ZeroPWM_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            LowF_ZeroPWM_DEADBAND_COUNT &= ((uint8)(~LowF_ZeroPWM_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(LowF_ZeroPWM_DEADBAND_COUNT_SHIFT)
                LowF_ZeroPWM_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << LowF_ZeroPWM_DEADBAND_COUNT_SHIFT)) &
                                                    LowF_ZeroPWM_DEADBAND_COUNT_MASK;
            #else
                LowF_ZeroPWM_DEADBAND_COUNT |= deadtime & LowF_ZeroPWM_DEADBAND_COUNT_MASK;
            #endif /* (LowF_ZeroPWM_DEADBAND_COUNT_SHIFT) */

        #endif /* (!LowF_ZeroPWM_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 LowF_ZeroPWM_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!LowF_ZeroPWM_DeadBand2_4)
            return (CY_GET_REG8(LowF_ZeroPWM_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(LowF_ZeroPWM_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(LowF_ZeroPWM_DEADBAND_COUNT & LowF_ZeroPWM_DEADBAND_COUNT_MASK)) >>
                                                                           LowF_ZeroPWM_DEADBAND_COUNT_SHIFT));
            #else
                return (LowF_ZeroPWM_DEADBAND_COUNT & LowF_ZeroPWM_DEADBAND_COUNT_MASK);
            #endif /* (LowF_ZeroPWM_DEADBAND_COUNT_SHIFT) */
        #endif /* (!LowF_ZeroPWM_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (LowF_ZeroPWM_UseStatus || LowF_ZeroPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LowF_ZeroPWM_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(LowF_ZeroPWM_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 LowF_ZeroPWM_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(LowF_ZeroPWM_STATUS_PTR));
    }

#endif /* (LowF_ZeroPWM_UseStatus || LowF_ZeroPWM_UsingFixedFunction) */


#if (LowF_ZeroPWM_UseControl)


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 LowF_ZeroPWM_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(LowF_ZeroPWM_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LowF_ZeroPWM_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(LowF_ZeroPWM_CONTROL_PTR, control);
    }

#endif /* (LowF_ZeroPWM_UseControl) */


#if (!LowF_ZeroPWM_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 LowF_ZeroPWM_ReadCapture(void) 
    {
        return (CY_GET_REG16(LowF_ZeroPWM_CAPTURE_LSB_PTR));
    }

#endif /* (!LowF_ZeroPWM_UsingFixedFunction) */


#if (LowF_ZeroPWM_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 LowF_ZeroPWM_ReadCompare(void) 
    {
        #if(LowF_ZeroPWM_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(LowF_ZeroPWM_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(LowF_ZeroPWM_COMPARE1_LSB_PTR));
        #endif /* (LowF_ZeroPWM_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 LowF_ZeroPWM_ReadCompare1(void) 
    {
        return (CY_GET_REG16(LowF_ZeroPWM_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 LowF_ZeroPWM_ReadCompare2(void) 
    {
        return (CY_GET_REG16(LowF_ZeroPWM_COMPARE2_LSB_PTR));
    }

#endif /* (LowF_ZeroPWM_UseOneCompareMode) */


/*******************************************************************************
* Function Name: LowF_ZeroPWM_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 LowF_ZeroPWM_ReadPeriod(void) 
{
    #if(LowF_ZeroPWM_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(LowF_ZeroPWM_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(LowF_ZeroPWM_PERIOD_LSB_PTR));
    #endif /* (LowF_ZeroPWM_UsingFixedFunction) */
}

#if ( LowF_ZeroPWM_KillModeMinTime)


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LowF_ZeroPWM_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(LowF_ZeroPWM_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: LowF_ZeroPWM_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 LowF_ZeroPWM_ReadKillTime(void) 
    {
        return (CY_GET_REG8(LowF_ZeroPWM_KILLMODEMINTIME_PTR));
    }

#endif /* ( LowF_ZeroPWM_KillModeMinTime) */

/* [] END OF FILE */
