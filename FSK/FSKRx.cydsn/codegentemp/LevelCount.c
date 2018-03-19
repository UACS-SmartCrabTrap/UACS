/*******************************************************************************
* File Name: LevelCount.c  
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

#include "LevelCount.h"

uint8 LevelCount_initVar = 0u;


/*******************************************************************************
* Function Name: LevelCount_Init
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
void LevelCount_Init(void) 
{
        #if (!LevelCount_UsingFixedFunction && !LevelCount_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!LevelCount_UsingFixedFunction && !LevelCount_ControlRegRemoved) */
        
        #if(!LevelCount_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 LevelCount_interruptState;
        #endif /* (!LevelCount_UsingFixedFunction) */
        
        #if (LevelCount_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            LevelCount_CONTROL &= LevelCount_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                LevelCount_CONTROL2 &= ((uint8)(~LevelCount_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                LevelCount_CONTROL3 &= ((uint8)(~LevelCount_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (LevelCount_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                LevelCount_CONTROL |= LevelCount_ONESHOT;
            #endif /* (LevelCount_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            LevelCount_CONTROL2 |= LevelCount_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            LevelCount_RT1 &= ((uint8)(~LevelCount_RT1_MASK));
            LevelCount_RT1 |= LevelCount_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            LevelCount_RT1 &= ((uint8)(~LevelCount_SYNCDSI_MASK));
            LevelCount_RT1 |= LevelCount_SYNCDSI_EN;

        #else
            #if(!LevelCount_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = LevelCount_CONTROL & ((uint8)(~LevelCount_CTRL_CMPMODE_MASK));
            LevelCount_CONTROL = ctrl | LevelCount_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = LevelCount_CONTROL & ((uint8)(~LevelCount_CTRL_CAPMODE_MASK));
            
            #if( 0 != LevelCount_CAPTURE_MODE_CONF)
                LevelCount_CONTROL = ctrl | LevelCount_DEFAULT_CAPTURE_MODE;
            #else
                LevelCount_CONTROL = ctrl;
            #endif /* 0 != LevelCount_CAPTURE_MODE */ 
            
            #endif /* (!LevelCount_ControlRegRemoved) */
        #endif /* (LevelCount_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!LevelCount_UsingFixedFunction)
            LevelCount_ClearFIFO();
        #endif /* (!LevelCount_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        LevelCount_WritePeriod(LevelCount_INIT_PERIOD_VALUE);
        #if (!(LevelCount_UsingFixedFunction && (CY_PSOC5A)))
            LevelCount_WriteCounter(LevelCount_INIT_COUNTER_VALUE);
        #endif /* (!(LevelCount_UsingFixedFunction && (CY_PSOC5A))) */
        LevelCount_SetInterruptMode(LevelCount_INIT_INTERRUPTS_MASK);
        
        #if (!LevelCount_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)LevelCount_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            LevelCount_WriteCompare(LevelCount_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            LevelCount_interruptState = CyEnterCriticalSection();
            
            LevelCount_STATUS_AUX_CTRL |= LevelCount_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(LevelCount_interruptState);
            
        #endif /* (!LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LevelCount_Enable
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
void LevelCount_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (LevelCount_UsingFixedFunction)
        LevelCount_GLOBAL_ENABLE |= LevelCount_BLOCK_EN_MASK;
        LevelCount_GLOBAL_STBY_ENABLE |= LevelCount_BLOCK_STBY_EN_MASK;
    #endif /* (LevelCount_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!LevelCount_ControlRegRemoved || LevelCount_UsingFixedFunction)
        LevelCount_CONTROL |= LevelCount_CTRL_ENABLE;                
    #endif /* (!LevelCount_ControlRegRemoved || LevelCount_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: LevelCount_Start
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
*  LevelCount_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void LevelCount_Start(void) 
{
    if(LevelCount_initVar == 0u)
    {
        LevelCount_Init();
        
        LevelCount_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    LevelCount_Enable();        
}


/*******************************************************************************
* Function Name: LevelCount_Stop
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
void LevelCount_Stop(void) 
{
    /* Disable Counter */
    #if(!LevelCount_ControlRegRemoved || LevelCount_UsingFixedFunction)
        LevelCount_CONTROL &= ((uint8)(~LevelCount_CTRL_ENABLE));        
    #endif /* (!LevelCount_ControlRegRemoved || LevelCount_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (LevelCount_UsingFixedFunction)
        LevelCount_GLOBAL_ENABLE &= ((uint8)(~LevelCount_BLOCK_EN_MASK));
        LevelCount_GLOBAL_STBY_ENABLE &= ((uint8)(~LevelCount_BLOCK_STBY_EN_MASK));
    #endif /* (LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LevelCount_SetInterruptMode
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
void LevelCount_SetInterruptMode(uint8 interruptsMask) 
{
    LevelCount_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: LevelCount_ReadStatusRegister
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
uint8   LevelCount_ReadStatusRegister(void) 
{
    return LevelCount_STATUS;
}


#if(!LevelCount_ControlRegRemoved)
/*******************************************************************************
* Function Name: LevelCount_ReadControlRegister
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
uint8   LevelCount_ReadControlRegister(void) 
{
    return LevelCount_CONTROL;
}


/*******************************************************************************
* Function Name: LevelCount_WriteControlRegister
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
void    LevelCount_WriteControlRegister(uint8 control) 
{
    LevelCount_CONTROL = control;
}

#endif  /* (!LevelCount_ControlRegRemoved) */


#if (!(LevelCount_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: LevelCount_WriteCounter
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
void LevelCount_WriteCounter(uint16 counter) \
                                   
{
    #if(LevelCount_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (LevelCount_GLOBAL_ENABLE & LevelCount_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        LevelCount_GLOBAL_ENABLE |= LevelCount_BLOCK_EN_MASK;
        CY_SET_REG16(LevelCount_COUNTER_LSB_PTR, (uint16)counter);
        LevelCount_GLOBAL_ENABLE &= ((uint8)(~LevelCount_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(LevelCount_COUNTER_LSB_PTR, counter);
    #endif /* (LevelCount_UsingFixedFunction) */
}
#endif /* (!(LevelCount_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: LevelCount_ReadCounter
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
uint16 LevelCount_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(LevelCount_UsingFixedFunction)
		(void)CY_GET_REG16(LevelCount_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(LevelCount_COUNTER_LSB_PTR_8BIT);
	#endif/* (LevelCount_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(LevelCount_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(LevelCount_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(LevelCount_STATICCOUNT_LSB_PTR));
    #endif /* (LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LevelCount_ReadCapture
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
uint16 LevelCount_ReadCapture(void) 
{
    #if(LevelCount_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(LevelCount_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(LevelCount_STATICCOUNT_LSB_PTR));
    #endif /* (LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LevelCount_WritePeriod
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
void LevelCount_WritePeriod(uint16 period) 
{
    #if(LevelCount_UsingFixedFunction)
        CY_SET_REG16(LevelCount_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(LevelCount_PERIOD_LSB_PTR, period);
    #endif /* (LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LevelCount_ReadPeriod
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
uint16 LevelCount_ReadPeriod(void) 
{
    #if(LevelCount_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(LevelCount_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(LevelCount_PERIOD_LSB_PTR));
    #endif /* (LevelCount_UsingFixedFunction) */
}


#if (!LevelCount_UsingFixedFunction)
/*******************************************************************************
* Function Name: LevelCount_WriteCompare
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
void LevelCount_WriteCompare(uint16 compare) \
                                   
{
    #if(LevelCount_UsingFixedFunction)
        CY_SET_REG16(LevelCount_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(LevelCount_COMPARE_LSB_PTR, compare);
    #endif /* (LevelCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LevelCount_ReadCompare
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
uint16 LevelCount_ReadCompare(void) 
{
    return (CY_GET_REG16(LevelCount_COMPARE_LSB_PTR));
}


#if (LevelCount_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: LevelCount_SetCompareMode
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
void LevelCount_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    LevelCount_CONTROL &= ((uint8)(~LevelCount_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    LevelCount_CONTROL |= compareMode;
}
#endif  /* (LevelCount_COMPARE_MODE_SOFTWARE) */


#if (LevelCount_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: LevelCount_SetCaptureMode
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
void LevelCount_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    LevelCount_CONTROL &= ((uint8)(~LevelCount_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    LevelCount_CONTROL |= ((uint8)((uint8)captureMode << LevelCount_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (LevelCount_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: LevelCount_ClearFIFO
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
void LevelCount_ClearFIFO(void) 
{

    while(0u != (LevelCount_ReadStatusRegister() & LevelCount_STATUS_FIFONEMP))
    {
        (void)LevelCount_ReadCapture();
    }

}
#endif  /* (!LevelCount_UsingFixedFunction) */


/* [] END OF FILE */

