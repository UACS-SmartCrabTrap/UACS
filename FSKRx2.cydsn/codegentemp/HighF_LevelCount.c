/*******************************************************************************
* File Name: HighF_LevelCount.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "HighF_LevelCount.h"

uint8 HighF_LevelCount_initVar = 0u;


/*******************************************************************************
* Function Name: HighF_LevelCount_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void HighF_LevelCount_Init(void) 
{
        #if (!HighF_LevelCount_UsingFixedFunction && !HighF_LevelCount_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!HighF_LevelCount_UsingFixedFunction && !HighF_LevelCount_ControlRegRemoved) */
        
        #if(!HighF_LevelCount_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 HighF_LevelCount_interruptState;
        #endif /* (!HighF_LevelCount_UsingFixedFunction) */
        
        #if (HighF_LevelCount_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            HighF_LevelCount_CONTROL &= HighF_LevelCount_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                HighF_LevelCount_CONTROL2 &= ((uint8)(~HighF_LevelCount_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                HighF_LevelCount_CONTROL3 &= ((uint8)(~HighF_LevelCount_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (HighF_LevelCount_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                HighF_LevelCount_CONTROL |= HighF_LevelCount_ONESHOT;
            #endif /* (HighF_LevelCount_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            HighF_LevelCount_CONTROL2 |= HighF_LevelCount_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            HighF_LevelCount_RT1 &= ((uint8)(~HighF_LevelCount_RT1_MASK));
            HighF_LevelCount_RT1 |= HighF_LevelCount_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            HighF_LevelCount_RT1 &= ((uint8)(~HighF_LevelCount_SYNCDSI_MASK));
            HighF_LevelCount_RT1 |= HighF_LevelCount_SYNCDSI_EN;

        #else
            #if(!HighF_LevelCount_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = HighF_LevelCount_CONTROL & ((uint8)(~HighF_LevelCount_CTRL_CMPMODE_MASK));
            HighF_LevelCount_CONTROL = ctrl | HighF_LevelCount_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = HighF_LevelCount_CONTROL & ((uint8)(~HighF_LevelCount_CTRL_CAPMODE_MASK));
            
            #if( 0 != HighF_LevelCount_CAPTURE_MODE_CONF)
                HighF_LevelCount_CONTROL = ctrl | HighF_LevelCount_DEFAULT_CAPTURE_MODE;
            #else
                HighF_LevelCount_CONTROL = ctrl;
            #endif /* 0 != HighF_LevelCount_CAPTURE_MODE */ 
            
            #endif /* (!HighF_LevelCount_ControlRegRemoved) */
        #endif /* (HighF_LevelCount_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!HighF_LevelCount_UsingFixedFunction)
            HighF_LevelCount_ClearFIFO();
        #endif /* (!HighF_LevelCount_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        HighF_LevelCount_WritePeriod(HighF_LevelCount_INIT_PERIOD_VALUE);
        #if (!(HighF_LevelCount_UsingFixedFunction && (CY_PSOC5A)))
            HighF_LevelCount_WriteCounter(HighF_LevelCount_INIT_COUNTER_VALUE);
        #endif /* (!(HighF_LevelCount_UsingFixedFunction && (CY_PSOC5A))) */
        HighF_LevelCount_SetInterruptMode(HighF_LevelCount_INIT_INTERRUPTS_MASK);
        
        #if (!HighF_LevelCount_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)HighF_LevelCount_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            HighF_LevelCount_WriteCompare(HighF_LevelCount_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            HighF_LevelCount_interruptState = CyEnterCriticalSection();
            
            HighF_LevelCount_STATUS_AUX_CTRL |= HighF_LevelCount_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(HighF_LevelCount_interruptState);
            
        #endif /* (!HighF_LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void HighF_LevelCount_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (HighF_LevelCount_UsingFixedFunction)
        HighF_LevelCount_GLOBAL_ENABLE |= HighF_LevelCount_BLOCK_EN_MASK;
        HighF_LevelCount_GLOBAL_STBY_ENABLE |= HighF_LevelCount_BLOCK_STBY_EN_MASK;
    #endif /* (HighF_LevelCount_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!HighF_LevelCount_ControlRegRemoved || HighF_LevelCount_UsingFixedFunction)
        HighF_LevelCount_CONTROL |= HighF_LevelCount_CTRL_ENABLE;                
    #endif /* (!HighF_LevelCount_ControlRegRemoved || HighF_LevelCount_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: HighF_LevelCount_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  HighF_LevelCount_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void HighF_LevelCount_Start(void) 
{
    if(HighF_LevelCount_initVar == 0u)
    {
        HighF_LevelCount_Init();
        
        HighF_LevelCount_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    HighF_LevelCount_Enable();        
}


/*******************************************************************************
* Function Name: HighF_LevelCount_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void HighF_LevelCount_Stop(void) 
{
    /* Disable Counter */
    #if(!HighF_LevelCount_ControlRegRemoved || HighF_LevelCount_UsingFixedFunction)
        HighF_LevelCount_CONTROL &= ((uint8)(~HighF_LevelCount_CTRL_ENABLE));        
    #endif /* (!HighF_LevelCount_ControlRegRemoved || HighF_LevelCount_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (HighF_LevelCount_UsingFixedFunction)
        HighF_LevelCount_GLOBAL_ENABLE &= ((uint8)(~HighF_LevelCount_BLOCK_EN_MASK));
        HighF_LevelCount_GLOBAL_STBY_ENABLE &= ((uint8)(~HighF_LevelCount_BLOCK_STBY_EN_MASK));
    #endif /* (HighF_LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void HighF_LevelCount_SetInterruptMode(uint8 interruptsMask) 
{
    HighF_LevelCount_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: HighF_LevelCount_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   HighF_LevelCount_ReadStatusRegister(void) 
{
    return HighF_LevelCount_STATUS;
}


#if(!HighF_LevelCount_ControlRegRemoved)
/*******************************************************************************
* Function Name: HighF_LevelCount_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   HighF_LevelCount_ReadControlRegister(void) 
{
    return HighF_LevelCount_CONTROL;
}


/*******************************************************************************
* Function Name: HighF_LevelCount_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    HighF_LevelCount_WriteControlRegister(uint8 control) 
{
    HighF_LevelCount_CONTROL = control;
}

#endif  /* (!HighF_LevelCount_ControlRegRemoved) */


#if (!(HighF_LevelCount_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: HighF_LevelCount_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void HighF_LevelCount_WriteCounter(uint16 counter) \
                                   
{
    #if(HighF_LevelCount_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (HighF_LevelCount_GLOBAL_ENABLE & HighF_LevelCount_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        HighF_LevelCount_GLOBAL_ENABLE |= HighF_LevelCount_BLOCK_EN_MASK;
        CY_SET_REG16(HighF_LevelCount_COUNTER_LSB_PTR, (uint16)counter);
        HighF_LevelCount_GLOBAL_ENABLE &= ((uint8)(~HighF_LevelCount_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(HighF_LevelCount_COUNTER_LSB_PTR, counter);
    #endif /* (HighF_LevelCount_UsingFixedFunction) */
}
#endif /* (!(HighF_LevelCount_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: HighF_LevelCount_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 HighF_LevelCount_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(HighF_LevelCount_UsingFixedFunction)
		(void)CY_GET_REG16(HighF_LevelCount_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(HighF_LevelCount_COUNTER_LSB_PTR_8BIT);
	#endif/* (HighF_LevelCount_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(HighF_LevelCount_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HighF_LevelCount_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(HighF_LevelCount_STATICCOUNT_LSB_PTR));
    #endif /* (HighF_LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 HighF_LevelCount_ReadCapture(void) 
{
    #if(HighF_LevelCount_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HighF_LevelCount_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(HighF_LevelCount_STATICCOUNT_LSB_PTR));
    #endif /* (HighF_LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void HighF_LevelCount_WritePeriod(uint16 period) 
{
    #if(HighF_LevelCount_UsingFixedFunction)
        CY_SET_REG16(HighF_LevelCount_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(HighF_LevelCount_PERIOD_LSB_PTR, period);
    #endif /* (HighF_LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 HighF_LevelCount_ReadPeriod(void) 
{
    #if(HighF_LevelCount_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HighF_LevelCount_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(HighF_LevelCount_PERIOD_LSB_PTR));
    #endif /* (HighF_LevelCount_UsingFixedFunction) */
}


#if (!HighF_LevelCount_UsingFixedFunction)
/*******************************************************************************
* Function Name: HighF_LevelCount_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void HighF_LevelCount_WriteCompare(uint16 compare) \
                                   
{
    #if(HighF_LevelCount_UsingFixedFunction)
        CY_SET_REG16(HighF_LevelCount_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(HighF_LevelCount_COMPARE_LSB_PTR, compare);
    #endif /* (HighF_LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HighF_LevelCount_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 HighF_LevelCount_ReadCompare(void) 
{
    return (CY_GET_REG16(HighF_LevelCount_COMPARE_LSB_PTR));
}


#if (HighF_LevelCount_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: HighF_LevelCount_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void HighF_LevelCount_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    HighF_LevelCount_CONTROL &= ((uint8)(~HighF_LevelCount_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    HighF_LevelCount_CONTROL |= compareMode;
}
#endif  /* (HighF_LevelCount_COMPARE_MODE_SOFTWARE) */


#if (HighF_LevelCount_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: HighF_LevelCount_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void HighF_LevelCount_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    HighF_LevelCount_CONTROL &= ((uint8)(~HighF_LevelCount_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    HighF_LevelCount_CONTROL |= ((uint8)((uint8)captureMode << HighF_LevelCount_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (HighF_LevelCount_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: HighF_LevelCount_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void HighF_LevelCount_ClearFIFO(void) 
{

    while(0u != (HighF_LevelCount_ReadStatusRegister() & HighF_LevelCount_STATUS_FIFONEMP))
    {
        (void)HighF_LevelCount_ReadCapture();
    }

}
#endif  /* (!HighF_LevelCount_UsingFixedFunction) */


/* [] END OF FILE */

