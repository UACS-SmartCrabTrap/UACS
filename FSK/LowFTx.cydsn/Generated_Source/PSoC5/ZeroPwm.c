/*******************************************************************************
* File Name: ZeroPwm.c
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

#include "ZeroPwm.h"

/* Error message for removed <resource> through optimization */
#ifdef ZeroPwm_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* ZeroPwm_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 ZeroPwm_initVar = 0u;


/*******************************************************************************
* Function Name: ZeroPwm_Start
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
*  ZeroPwm_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ZeroPwm_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(ZeroPwm_initVar == 0u)
    {
        ZeroPwm_Init();
        ZeroPwm_initVar = 1u;
    }
    ZeroPwm_Enable();

}


/*******************************************************************************
* Function Name: ZeroPwm_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  ZeroPwm_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ZeroPwm_Init(void) 
{
    #if (ZeroPwm_UsingFixedFunction || ZeroPwm_UseControl)
        uint8 ctrl;
    #endif /* (ZeroPwm_UsingFixedFunction || ZeroPwm_UseControl) */

    #if(!ZeroPwm_UsingFixedFunction)
        #if(ZeroPwm_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 ZeroPwm_interruptState;
        #endif /* (ZeroPwm_UseStatus) */
    #endif /* (!ZeroPwm_UsingFixedFunction) */

    #if (ZeroPwm_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        ZeroPwm_CONTROL |= ZeroPwm_CFG0_MODE;
        #if (ZeroPwm_DeadBand2_4)
            ZeroPwm_CONTROL |= ZeroPwm_CFG0_DB;
        #endif /* (ZeroPwm_DeadBand2_4) */

        ctrl = ZeroPwm_CONTROL3 & ((uint8 )(~ZeroPwm_CTRL_CMPMODE1_MASK));
        ZeroPwm_CONTROL3 = ctrl | ZeroPwm_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        ZeroPwm_RT1 &= ((uint8)(~ZeroPwm_RT1_MASK));
        ZeroPwm_RT1 |= ZeroPwm_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        ZeroPwm_RT1 &= ((uint8)(~ZeroPwm_SYNCDSI_MASK));
        ZeroPwm_RT1 |= ZeroPwm_SYNCDSI_EN;

    #elif (ZeroPwm_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = ZeroPwm_CONTROL & ((uint8)(~ZeroPwm_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~ZeroPwm_CTRL_CMPMODE1_MASK));
        ZeroPwm_CONTROL = ctrl | ZeroPwm_DEFAULT_COMPARE2_MODE |
                                   ZeroPwm_DEFAULT_COMPARE1_MODE;
    #endif /* (ZeroPwm_UsingFixedFunction) */

    #if (!ZeroPwm_UsingFixedFunction)
        #if (ZeroPwm_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            ZeroPwm_AUX_CONTROLDP0 |= (ZeroPwm_AUX_CTRL_FIFO0_CLR);
        #else /* (ZeroPwm_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            ZeroPwm_AUX_CONTROLDP0 |= (ZeroPwm_AUX_CTRL_FIFO0_CLR);
            ZeroPwm_AUX_CONTROLDP1 |= (ZeroPwm_AUX_CTRL_FIFO0_CLR);
        #endif /* (ZeroPwm_Resolution == 8) */

        ZeroPwm_WriteCounter(ZeroPwm_INIT_PERIOD_VALUE);
    #endif /* (!ZeroPwm_UsingFixedFunction) */

    ZeroPwm_WritePeriod(ZeroPwm_INIT_PERIOD_VALUE);

        #if (ZeroPwm_UseOneCompareMode)
            ZeroPwm_WriteCompare(ZeroPwm_INIT_COMPARE_VALUE1);
        #else
            ZeroPwm_WriteCompare1(ZeroPwm_INIT_COMPARE_VALUE1);
            ZeroPwm_WriteCompare2(ZeroPwm_INIT_COMPARE_VALUE2);
        #endif /* (ZeroPwm_UseOneCompareMode) */

        #if (ZeroPwm_KillModeMinTime)
            ZeroPwm_WriteKillTime(ZeroPwm_MinimumKillTime);
        #endif /* (ZeroPwm_KillModeMinTime) */

        #if (ZeroPwm_DeadBandUsed)
            ZeroPwm_WriteDeadTime(ZeroPwm_INIT_DEAD_TIME);
        #endif /* (ZeroPwm_DeadBandUsed) */

    #if (ZeroPwm_UseStatus || ZeroPwm_UsingFixedFunction)
        ZeroPwm_SetInterruptMode(ZeroPwm_INIT_INTERRUPTS_MODE);
    #endif /* (ZeroPwm_UseStatus || ZeroPwm_UsingFixedFunction) */

    #if (ZeroPwm_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        ZeroPwm_GLOBAL_ENABLE |= ZeroPwm_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        ZeroPwm_CONTROL2 |= ZeroPwm_CTRL2_IRQ_SEL;
    #else
        #if(ZeroPwm_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ZeroPwm_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            ZeroPwm_STATUS_AUX_CTRL |= ZeroPwm_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(ZeroPwm_interruptState);

            /* Clear the FIFO to enable the ZeroPwm_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            ZeroPwm_ClearFIFO();
        #endif /* (ZeroPwm_UseStatus) */
    #endif /* (ZeroPwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ZeroPwm_Enable
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
void ZeroPwm_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ZeroPwm_UsingFixedFunction)
        ZeroPwm_GLOBAL_ENABLE |= ZeroPwm_BLOCK_EN_MASK;
        ZeroPwm_GLOBAL_STBY_ENABLE |= ZeroPwm_BLOCK_STBY_EN_MASK;
    #endif /* (ZeroPwm_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (ZeroPwm_UseControl || ZeroPwm_UsingFixedFunction)
        ZeroPwm_CONTROL |= ZeroPwm_CTRL_ENABLE;
    #endif /* (ZeroPwm_UseControl || ZeroPwm_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ZeroPwm_Stop
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
void ZeroPwm_Stop(void) 
{
    #if (ZeroPwm_UseControl || ZeroPwm_UsingFixedFunction)
        ZeroPwm_CONTROL &= ((uint8)(~ZeroPwm_CTRL_ENABLE));
    #endif /* (ZeroPwm_UseControl || ZeroPwm_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (ZeroPwm_UsingFixedFunction)
        ZeroPwm_GLOBAL_ENABLE &= ((uint8)(~ZeroPwm_BLOCK_EN_MASK));
        ZeroPwm_GLOBAL_STBY_ENABLE &= ((uint8)(~ZeroPwm_BLOCK_STBY_EN_MASK));
    #endif /* (ZeroPwm_UsingFixedFunction) */
}

#if (ZeroPwm_UseOneCompareMode)
    #if (ZeroPwm_CompareMode1SW)


        /*******************************************************************************
        * Function Name: ZeroPwm_SetCompareMode
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
        void ZeroPwm_SetCompareMode(uint8 comparemode) 
        {
            #if(ZeroPwm_UsingFixedFunction)

                #if(0 != ZeroPwm_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << ZeroPwm_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != ZeroPwm_CTRL_CMPMODE1_SHIFT) */

                ZeroPwm_CONTROL3 &= ((uint8)(~ZeroPwm_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                ZeroPwm_CONTROL3 |= comparemodemasked;

            #elif (ZeroPwm_UseControl)

                #if(0 != ZeroPwm_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << ZeroPwm_CTRL_CMPMODE1_SHIFT)) &
                                                ZeroPwm_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & ZeroPwm_CTRL_CMPMODE1_MASK;
                #endif /* (0 != ZeroPwm_CTRL_CMPMODE1_SHIFT) */

                #if(0 != ZeroPwm_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << ZeroPwm_CTRL_CMPMODE2_SHIFT)) &
                                               ZeroPwm_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & ZeroPwm_CTRL_CMPMODE2_MASK;
                #endif /* (0 != ZeroPwm_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                ZeroPwm_CONTROL &= ((uint8)(~(ZeroPwm_CTRL_CMPMODE1_MASK |
                                            ZeroPwm_CTRL_CMPMODE2_MASK)));
                ZeroPwm_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (ZeroPwm_UsingFixedFunction) */
        }
    #endif /* ZeroPwm_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (ZeroPwm_CompareMode1SW)


        /*******************************************************************************
        * Function Name: ZeroPwm_SetCompareMode1
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
        void ZeroPwm_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != ZeroPwm_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << ZeroPwm_CTRL_CMPMODE1_SHIFT)) &
                                           ZeroPwm_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & ZeroPwm_CTRL_CMPMODE1_MASK;
            #endif /* (0 != ZeroPwm_CTRL_CMPMODE1_SHIFT) */

            #if (ZeroPwm_UseControl)
                ZeroPwm_CONTROL &= ((uint8)(~ZeroPwm_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                ZeroPwm_CONTROL |= comparemodemasked;
            #endif /* (ZeroPwm_UseControl) */
        }
    #endif /* ZeroPwm_CompareMode1SW */

#if (ZeroPwm_CompareMode2SW)


    /*******************************************************************************
    * Function Name: ZeroPwm_SetCompareMode2
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
    void ZeroPwm_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != ZeroPwm_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << ZeroPwm_CTRL_CMPMODE2_SHIFT)) &
                                                 ZeroPwm_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & ZeroPwm_CTRL_CMPMODE2_MASK;
        #endif /* (0 != ZeroPwm_CTRL_CMPMODE2_SHIFT) */

        #if (ZeroPwm_UseControl)
            ZeroPwm_CONTROL &= ((uint8)(~ZeroPwm_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            ZeroPwm_CONTROL |= comparemodemasked;
        #endif /* (ZeroPwm_UseControl) */
    }
    #endif /*ZeroPwm_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!ZeroPwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ZeroPwm_WriteCounter
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
    void ZeroPwm_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(ZeroPwm_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: ZeroPwm_ReadCounter
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
    uint16 ZeroPwm_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(ZeroPwm_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(ZeroPwm_CAPTURE_LSB_PTR));
    }

    #if (ZeroPwm_UseStatus)


        /*******************************************************************************
        * Function Name: ZeroPwm_ClearFIFO
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
        void ZeroPwm_ClearFIFO(void) 
        {
            while(0u != (ZeroPwm_ReadStatusRegister() & ZeroPwm_STATUS_FIFONEMPTY))
            {
                (void)ZeroPwm_ReadCapture();
            }
        }

    #endif /* ZeroPwm_UseStatus */

#endif /* !ZeroPwm_UsingFixedFunction */


/*******************************************************************************
* Function Name: ZeroPwm_WritePeriod
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
void ZeroPwm_WritePeriod(uint16 period) 
{
    #if(ZeroPwm_UsingFixedFunction)
        CY_SET_REG16(ZeroPwm_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(ZeroPwm_PERIOD_LSB_PTR, period);
    #endif /* (ZeroPwm_UsingFixedFunction) */
}

#if (ZeroPwm_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: ZeroPwm_WriteCompare
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
    void ZeroPwm_WriteCompare(uint16 compare) \
                                       
    {
        #if(ZeroPwm_UsingFixedFunction)
            CY_SET_REG16(ZeroPwm_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(ZeroPwm_COMPARE1_LSB_PTR, compare);
        #endif /* (ZeroPwm_UsingFixedFunction) */

        #if (ZeroPwm_PWMMode == ZeroPwm__B_PWM__DITHER)
            #if(ZeroPwm_UsingFixedFunction)
                CY_SET_REG16(ZeroPwm_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(ZeroPwm_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (ZeroPwm_UsingFixedFunction) */
        #endif /* (ZeroPwm_PWMMode == ZeroPwm__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: ZeroPwm_WriteCompare1
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
    void ZeroPwm_WriteCompare1(uint16 compare) \
                                        
    {
        #if(ZeroPwm_UsingFixedFunction)
            CY_SET_REG16(ZeroPwm_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(ZeroPwm_COMPARE1_LSB_PTR, compare);
        #endif /* (ZeroPwm_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: ZeroPwm_WriteCompare2
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
    void ZeroPwm_WriteCompare2(uint16 compare) \
                                        
    {
        #if(ZeroPwm_UsingFixedFunction)
            CY_SET_REG16(ZeroPwm_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(ZeroPwm_COMPARE2_LSB_PTR, compare);
        #endif /* (ZeroPwm_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (ZeroPwm_DeadBandUsed)


    /*******************************************************************************
    * Function Name: ZeroPwm_WriteDeadTime
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
    void ZeroPwm_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!ZeroPwm_DeadBand2_4)
            CY_SET_REG8(ZeroPwm_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            ZeroPwm_DEADBAND_COUNT &= ((uint8)(~ZeroPwm_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(ZeroPwm_DEADBAND_COUNT_SHIFT)
                ZeroPwm_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << ZeroPwm_DEADBAND_COUNT_SHIFT)) &
                                                    ZeroPwm_DEADBAND_COUNT_MASK;
            #else
                ZeroPwm_DEADBAND_COUNT |= deadtime & ZeroPwm_DEADBAND_COUNT_MASK;
            #endif /* (ZeroPwm_DEADBAND_COUNT_SHIFT) */

        #endif /* (!ZeroPwm_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: ZeroPwm_ReadDeadTime
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
    uint8 ZeroPwm_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!ZeroPwm_DeadBand2_4)
            return (CY_GET_REG8(ZeroPwm_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(ZeroPwm_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(ZeroPwm_DEADBAND_COUNT & ZeroPwm_DEADBAND_COUNT_MASK)) >>
                                                                           ZeroPwm_DEADBAND_COUNT_SHIFT));
            #else
                return (ZeroPwm_DEADBAND_COUNT & ZeroPwm_DEADBAND_COUNT_MASK);
            #endif /* (ZeroPwm_DEADBAND_COUNT_SHIFT) */
        #endif /* (!ZeroPwm_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (ZeroPwm_UseStatus || ZeroPwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ZeroPwm_SetInterruptMode
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
    void ZeroPwm_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(ZeroPwm_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: ZeroPwm_ReadStatusRegister
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
    uint8 ZeroPwm_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(ZeroPwm_STATUS_PTR));
    }

#endif /* (ZeroPwm_UseStatus || ZeroPwm_UsingFixedFunction) */


#if (ZeroPwm_UseControl)


    /*******************************************************************************
    * Function Name: ZeroPwm_ReadControlRegister
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
    uint8 ZeroPwm_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(ZeroPwm_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: ZeroPwm_WriteControlRegister
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
    void ZeroPwm_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(ZeroPwm_CONTROL_PTR, control);
    }

#endif /* (ZeroPwm_UseControl) */


#if (!ZeroPwm_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: ZeroPwm_ReadCapture
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
    uint16 ZeroPwm_ReadCapture(void) 
    {
        return (CY_GET_REG16(ZeroPwm_CAPTURE_LSB_PTR));
    }

#endif /* (!ZeroPwm_UsingFixedFunction) */


#if (ZeroPwm_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: ZeroPwm_ReadCompare
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
    uint16 ZeroPwm_ReadCompare(void) 
    {
        #if(ZeroPwm_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(ZeroPwm_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(ZeroPwm_COMPARE1_LSB_PTR));
        #endif /* (ZeroPwm_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: ZeroPwm_ReadCompare1
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
    uint16 ZeroPwm_ReadCompare1(void) 
    {
        return (CY_GET_REG16(ZeroPwm_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: ZeroPwm_ReadCompare2
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
    uint16 ZeroPwm_ReadCompare2(void) 
    {
        return (CY_GET_REG16(ZeroPwm_COMPARE2_LSB_PTR));
    }

#endif /* (ZeroPwm_UseOneCompareMode) */


/*******************************************************************************
* Function Name: ZeroPwm_ReadPeriod
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
uint16 ZeroPwm_ReadPeriod(void) 
{
    #if(ZeroPwm_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(ZeroPwm_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(ZeroPwm_PERIOD_LSB_PTR));
    #endif /* (ZeroPwm_UsingFixedFunction) */
}

#if ( ZeroPwm_KillModeMinTime)


    /*******************************************************************************
    * Function Name: ZeroPwm_WriteKillTime
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
    void ZeroPwm_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(ZeroPwm_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: ZeroPwm_ReadKillTime
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
    uint8 ZeroPwm_ReadKillTime(void) 
    {
        return (CY_GET_REG8(ZeroPwm_KILLMODEMINTIME_PTR));
    }

#endif /* ( ZeroPwm_KillModeMinTime) */

/* [] END OF FILE */
