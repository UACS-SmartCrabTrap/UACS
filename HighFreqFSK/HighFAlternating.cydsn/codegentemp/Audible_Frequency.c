/*******************************************************************************
* File Name: Audible_Frequency.c
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

#include "Audible_Frequency.h"

/* Error message for removed <resource> through optimization */
#ifdef Audible_Frequency_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* Audible_Frequency_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 Audible_Frequency_initVar = 0u;


/*******************************************************************************
* Function Name: Audible_Frequency_Start
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
*  Audible_Frequency_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Audible_Frequency_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Audible_Frequency_initVar == 0u)
    {
        Audible_Frequency_Init();
        Audible_Frequency_initVar = 1u;
    }
    Audible_Frequency_Enable();

}


/*******************************************************************************
* Function Name: Audible_Frequency_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  Audible_Frequency_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Audible_Frequency_Init(void) 
{
    #if (Audible_Frequency_UsingFixedFunction || Audible_Frequency_UseControl)
        uint8 ctrl;
    #endif /* (Audible_Frequency_UsingFixedFunction || Audible_Frequency_UseControl) */

    #if(!Audible_Frequency_UsingFixedFunction)
        #if(Audible_Frequency_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 Audible_Frequency_interruptState;
        #endif /* (Audible_Frequency_UseStatus) */
    #endif /* (!Audible_Frequency_UsingFixedFunction) */

    #if (Audible_Frequency_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        Audible_Frequency_CONTROL |= Audible_Frequency_CFG0_MODE;
        #if (Audible_Frequency_DeadBand2_4)
            Audible_Frequency_CONTROL |= Audible_Frequency_CFG0_DB;
        #endif /* (Audible_Frequency_DeadBand2_4) */

        ctrl = Audible_Frequency_CONTROL3 & ((uint8 )(~Audible_Frequency_CTRL_CMPMODE1_MASK));
        Audible_Frequency_CONTROL3 = ctrl | Audible_Frequency_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        Audible_Frequency_RT1 &= ((uint8)(~Audible_Frequency_RT1_MASK));
        Audible_Frequency_RT1 |= Audible_Frequency_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        Audible_Frequency_RT1 &= ((uint8)(~Audible_Frequency_SYNCDSI_MASK));
        Audible_Frequency_RT1 |= Audible_Frequency_SYNCDSI_EN;

    #elif (Audible_Frequency_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = Audible_Frequency_CONTROL & ((uint8)(~Audible_Frequency_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~Audible_Frequency_CTRL_CMPMODE1_MASK));
        Audible_Frequency_CONTROL = ctrl | Audible_Frequency_DEFAULT_COMPARE2_MODE |
                                   Audible_Frequency_DEFAULT_COMPARE1_MODE;
    #endif /* (Audible_Frequency_UsingFixedFunction) */

    #if (!Audible_Frequency_UsingFixedFunction)
        #if (Audible_Frequency_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            Audible_Frequency_AUX_CONTROLDP0 |= (Audible_Frequency_AUX_CTRL_FIFO0_CLR);
        #else /* (Audible_Frequency_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            Audible_Frequency_AUX_CONTROLDP0 |= (Audible_Frequency_AUX_CTRL_FIFO0_CLR);
            Audible_Frequency_AUX_CONTROLDP1 |= (Audible_Frequency_AUX_CTRL_FIFO0_CLR);
        #endif /* (Audible_Frequency_Resolution == 8) */

        Audible_Frequency_WriteCounter(Audible_Frequency_INIT_PERIOD_VALUE);
    #endif /* (!Audible_Frequency_UsingFixedFunction) */

    Audible_Frequency_WritePeriod(Audible_Frequency_INIT_PERIOD_VALUE);

        #if (Audible_Frequency_UseOneCompareMode)
            Audible_Frequency_WriteCompare(Audible_Frequency_INIT_COMPARE_VALUE1);
        #else
            Audible_Frequency_WriteCompare1(Audible_Frequency_INIT_COMPARE_VALUE1);
            Audible_Frequency_WriteCompare2(Audible_Frequency_INIT_COMPARE_VALUE2);
        #endif /* (Audible_Frequency_UseOneCompareMode) */

        #if (Audible_Frequency_KillModeMinTime)
            Audible_Frequency_WriteKillTime(Audible_Frequency_MinimumKillTime);
        #endif /* (Audible_Frequency_KillModeMinTime) */

        #if (Audible_Frequency_DeadBandUsed)
            Audible_Frequency_WriteDeadTime(Audible_Frequency_INIT_DEAD_TIME);
        #endif /* (Audible_Frequency_DeadBandUsed) */

    #if (Audible_Frequency_UseStatus || Audible_Frequency_UsingFixedFunction)
        Audible_Frequency_SetInterruptMode(Audible_Frequency_INIT_INTERRUPTS_MODE);
    #endif /* (Audible_Frequency_UseStatus || Audible_Frequency_UsingFixedFunction) */

    #if (Audible_Frequency_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        Audible_Frequency_GLOBAL_ENABLE |= Audible_Frequency_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        Audible_Frequency_CONTROL2 |= Audible_Frequency_CTRL2_IRQ_SEL;
    #else
        #if(Audible_Frequency_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Audible_Frequency_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Audible_Frequency_STATUS_AUX_CTRL |= Audible_Frequency_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(Audible_Frequency_interruptState);

            /* Clear the FIFO to enable the Audible_Frequency_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            Audible_Frequency_ClearFIFO();
        #endif /* (Audible_Frequency_UseStatus) */
    #endif /* (Audible_Frequency_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Audible_Frequency_Enable
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
void Audible_Frequency_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Audible_Frequency_UsingFixedFunction)
        Audible_Frequency_GLOBAL_ENABLE |= Audible_Frequency_BLOCK_EN_MASK;
        Audible_Frequency_GLOBAL_STBY_ENABLE |= Audible_Frequency_BLOCK_STBY_EN_MASK;
    #endif /* (Audible_Frequency_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (Audible_Frequency_UseControl || Audible_Frequency_UsingFixedFunction)
        Audible_Frequency_CONTROL |= Audible_Frequency_CTRL_ENABLE;
    #endif /* (Audible_Frequency_UseControl || Audible_Frequency_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Audible_Frequency_Stop
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
void Audible_Frequency_Stop(void) 
{
    #if (Audible_Frequency_UseControl || Audible_Frequency_UsingFixedFunction)
        Audible_Frequency_CONTROL &= ((uint8)(~Audible_Frequency_CTRL_ENABLE));
    #endif /* (Audible_Frequency_UseControl || Audible_Frequency_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (Audible_Frequency_UsingFixedFunction)
        Audible_Frequency_GLOBAL_ENABLE &= ((uint8)(~Audible_Frequency_BLOCK_EN_MASK));
        Audible_Frequency_GLOBAL_STBY_ENABLE &= ((uint8)(~Audible_Frequency_BLOCK_STBY_EN_MASK));
    #endif /* (Audible_Frequency_UsingFixedFunction) */
}

#if (Audible_Frequency_UseOneCompareMode)
    #if (Audible_Frequency_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Audible_Frequency_SetCompareMode
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
        void Audible_Frequency_SetCompareMode(uint8 comparemode) 
        {
            #if(Audible_Frequency_UsingFixedFunction)

                #if(0 != Audible_Frequency_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << Audible_Frequency_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != Audible_Frequency_CTRL_CMPMODE1_SHIFT) */

                Audible_Frequency_CONTROL3 &= ((uint8)(~Audible_Frequency_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                Audible_Frequency_CONTROL3 |= comparemodemasked;

            #elif (Audible_Frequency_UseControl)

                #if(0 != Audible_Frequency_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << Audible_Frequency_CTRL_CMPMODE1_SHIFT)) &
                                                Audible_Frequency_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & Audible_Frequency_CTRL_CMPMODE1_MASK;
                #endif /* (0 != Audible_Frequency_CTRL_CMPMODE1_SHIFT) */

                #if(0 != Audible_Frequency_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << Audible_Frequency_CTRL_CMPMODE2_SHIFT)) &
                                               Audible_Frequency_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & Audible_Frequency_CTRL_CMPMODE2_MASK;
                #endif /* (0 != Audible_Frequency_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                Audible_Frequency_CONTROL &= ((uint8)(~(Audible_Frequency_CTRL_CMPMODE1_MASK |
                                            Audible_Frequency_CTRL_CMPMODE2_MASK)));
                Audible_Frequency_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (Audible_Frequency_UsingFixedFunction) */
        }
    #endif /* Audible_Frequency_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (Audible_Frequency_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Audible_Frequency_SetCompareMode1
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
        void Audible_Frequency_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != Audible_Frequency_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << Audible_Frequency_CTRL_CMPMODE1_SHIFT)) &
                                           Audible_Frequency_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & Audible_Frequency_CTRL_CMPMODE1_MASK;
            #endif /* (0 != Audible_Frequency_CTRL_CMPMODE1_SHIFT) */

            #if (Audible_Frequency_UseControl)
                Audible_Frequency_CONTROL &= ((uint8)(~Audible_Frequency_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                Audible_Frequency_CONTROL |= comparemodemasked;
            #endif /* (Audible_Frequency_UseControl) */
        }
    #endif /* Audible_Frequency_CompareMode1SW */

#if (Audible_Frequency_CompareMode2SW)


    /*******************************************************************************
    * Function Name: Audible_Frequency_SetCompareMode2
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
    void Audible_Frequency_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != Audible_Frequency_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << Audible_Frequency_CTRL_CMPMODE2_SHIFT)) &
                                                 Audible_Frequency_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & Audible_Frequency_CTRL_CMPMODE2_MASK;
        #endif /* (0 != Audible_Frequency_CTRL_CMPMODE2_SHIFT) */

        #if (Audible_Frequency_UseControl)
            Audible_Frequency_CONTROL &= ((uint8)(~Audible_Frequency_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            Audible_Frequency_CONTROL |= comparemodemasked;
        #endif /* (Audible_Frequency_UseControl) */
    }
    #endif /*Audible_Frequency_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!Audible_Frequency_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Audible_Frequency_WriteCounter
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
    void Audible_Frequency_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(Audible_Frequency_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: Audible_Frequency_ReadCounter
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
    uint16 Audible_Frequency_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(Audible_Frequency_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(Audible_Frequency_CAPTURE_LSB_PTR));
    }

    #if (Audible_Frequency_UseStatus)


        /*******************************************************************************
        * Function Name: Audible_Frequency_ClearFIFO
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
        void Audible_Frequency_ClearFIFO(void) 
        {
            while(0u != (Audible_Frequency_ReadStatusRegister() & Audible_Frequency_STATUS_FIFONEMPTY))
            {
                (void)Audible_Frequency_ReadCapture();
            }
        }

    #endif /* Audible_Frequency_UseStatus */

#endif /* !Audible_Frequency_UsingFixedFunction */


/*******************************************************************************
* Function Name: Audible_Frequency_WritePeriod
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
void Audible_Frequency_WritePeriod(uint16 period) 
{
    #if(Audible_Frequency_UsingFixedFunction)
        CY_SET_REG16(Audible_Frequency_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(Audible_Frequency_PERIOD_LSB_PTR, period);
    #endif /* (Audible_Frequency_UsingFixedFunction) */
}

#if (Audible_Frequency_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Audible_Frequency_WriteCompare
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
    void Audible_Frequency_WriteCompare(uint16 compare) \
                                       
    {
        #if(Audible_Frequency_UsingFixedFunction)
            CY_SET_REG16(Audible_Frequency_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Audible_Frequency_COMPARE1_LSB_PTR, compare);
        #endif /* (Audible_Frequency_UsingFixedFunction) */

        #if (Audible_Frequency_PWMMode == Audible_Frequency__B_PWM__DITHER)
            #if(Audible_Frequency_UsingFixedFunction)
                CY_SET_REG16(Audible_Frequency_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(Audible_Frequency_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (Audible_Frequency_UsingFixedFunction) */
        #endif /* (Audible_Frequency_PWMMode == Audible_Frequency__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: Audible_Frequency_WriteCompare1
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
    void Audible_Frequency_WriteCompare1(uint16 compare) \
                                        
    {
        #if(Audible_Frequency_UsingFixedFunction)
            CY_SET_REG16(Audible_Frequency_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Audible_Frequency_COMPARE1_LSB_PTR, compare);
        #endif /* (Audible_Frequency_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: Audible_Frequency_WriteCompare2
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
    void Audible_Frequency_WriteCompare2(uint16 compare) \
                                        
    {
        #if(Audible_Frequency_UsingFixedFunction)
            CY_SET_REG16(Audible_Frequency_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(Audible_Frequency_COMPARE2_LSB_PTR, compare);
        #endif /* (Audible_Frequency_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (Audible_Frequency_DeadBandUsed)


    /*******************************************************************************
    * Function Name: Audible_Frequency_WriteDeadTime
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
    void Audible_Frequency_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!Audible_Frequency_DeadBand2_4)
            CY_SET_REG8(Audible_Frequency_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            Audible_Frequency_DEADBAND_COUNT &= ((uint8)(~Audible_Frequency_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(Audible_Frequency_DEADBAND_COUNT_SHIFT)
                Audible_Frequency_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << Audible_Frequency_DEADBAND_COUNT_SHIFT)) &
                                                    Audible_Frequency_DEADBAND_COUNT_MASK;
            #else
                Audible_Frequency_DEADBAND_COUNT |= deadtime & Audible_Frequency_DEADBAND_COUNT_MASK;
            #endif /* (Audible_Frequency_DEADBAND_COUNT_SHIFT) */

        #endif /* (!Audible_Frequency_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: Audible_Frequency_ReadDeadTime
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
    uint8 Audible_Frequency_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!Audible_Frequency_DeadBand2_4)
            return (CY_GET_REG8(Audible_Frequency_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(Audible_Frequency_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(Audible_Frequency_DEADBAND_COUNT & Audible_Frequency_DEADBAND_COUNT_MASK)) >>
                                                                           Audible_Frequency_DEADBAND_COUNT_SHIFT));
            #else
                return (Audible_Frequency_DEADBAND_COUNT & Audible_Frequency_DEADBAND_COUNT_MASK);
            #endif /* (Audible_Frequency_DEADBAND_COUNT_SHIFT) */
        #endif /* (!Audible_Frequency_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (Audible_Frequency_UseStatus || Audible_Frequency_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Audible_Frequency_SetInterruptMode
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
    void Audible_Frequency_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(Audible_Frequency_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: Audible_Frequency_ReadStatusRegister
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
    uint8 Audible_Frequency_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(Audible_Frequency_STATUS_PTR));
    }

#endif /* (Audible_Frequency_UseStatus || Audible_Frequency_UsingFixedFunction) */


#if (Audible_Frequency_UseControl)


    /*******************************************************************************
    * Function Name: Audible_Frequency_ReadControlRegister
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
    uint8 Audible_Frequency_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(Audible_Frequency_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: Audible_Frequency_WriteControlRegister
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
    void Audible_Frequency_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(Audible_Frequency_CONTROL_PTR, control);
    }

#endif /* (Audible_Frequency_UseControl) */


#if (!Audible_Frequency_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Audible_Frequency_ReadCapture
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
    uint16 Audible_Frequency_ReadCapture(void) 
    {
        return (CY_GET_REG16(Audible_Frequency_CAPTURE_LSB_PTR));
    }

#endif /* (!Audible_Frequency_UsingFixedFunction) */


#if (Audible_Frequency_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Audible_Frequency_ReadCompare
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
    uint16 Audible_Frequency_ReadCompare(void) 
    {
        #if(Audible_Frequency_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(Audible_Frequency_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(Audible_Frequency_COMPARE1_LSB_PTR));
        #endif /* (Audible_Frequency_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: Audible_Frequency_ReadCompare1
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
    uint16 Audible_Frequency_ReadCompare1(void) 
    {
        return (CY_GET_REG16(Audible_Frequency_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: Audible_Frequency_ReadCompare2
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
    uint16 Audible_Frequency_ReadCompare2(void) 
    {
        return (CY_GET_REG16(Audible_Frequency_COMPARE2_LSB_PTR));
    }

#endif /* (Audible_Frequency_UseOneCompareMode) */


/*******************************************************************************
* Function Name: Audible_Frequency_ReadPeriod
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
uint16 Audible_Frequency_ReadPeriod(void) 
{
    #if(Audible_Frequency_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Audible_Frequency_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(Audible_Frequency_PERIOD_LSB_PTR));
    #endif /* (Audible_Frequency_UsingFixedFunction) */
}

#if ( Audible_Frequency_KillModeMinTime)


    /*******************************************************************************
    * Function Name: Audible_Frequency_WriteKillTime
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
    void Audible_Frequency_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(Audible_Frequency_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: Audible_Frequency_ReadKillTime
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
    uint8 Audible_Frequency_ReadKillTime(void) 
    {
        return (CY_GET_REG8(Audible_Frequency_KILLMODEMINTIME_PTR));
    }

#endif /* ( Audible_Frequency_KillModeMinTime) */

/* [] END OF FILE */
