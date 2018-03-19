/*******************************************************************************
* File Name: HighF_ShiftReg.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the Shift Register component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "HighF_ShiftReg.h"

uint8 HighF_ShiftReg_initVar = 0u;


/*******************************************************************************
* Function Name: HighF_ShiftReg_Start
********************************************************************************
*
* Summary:
*  Starts the Shift Register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  HighF_ShiftReg_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void HighF_ShiftReg_Start(void) 
{
    if(0u == HighF_ShiftReg_initVar)
    {
        HighF_ShiftReg_Init();
        HighF_ShiftReg_initVar = 1u; /* Component initialized */
    }

    HighF_ShiftReg_Enable();
}


/*******************************************************************************
* Function Name: HighF_ShiftReg_Enable
********************************************************************************
*
* Summary:
*  Enables the Shift Register.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void HighF_ShiftReg_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    HighF_ShiftReg_SR_CONTROL |= HighF_ShiftReg_CLK_EN;

    HighF_ShiftReg_EnableInt();
}


/*******************************************************************************
* Function Name: HighF_ShiftReg_Init
********************************************************************************
*
* Summary:
*  Initializes Tx and/or Rx interrupt sources with initial values.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void HighF_ShiftReg_Init(void) 
{
    HighF_ShiftReg_SetIntMode(HighF_ShiftReg_INT_SRC);
}


/*******************************************************************************
* Function Name: HighF_ShiftReg_Stop
********************************************************************************
*
* Summary:
*  Disables the Shift Register
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void HighF_ShiftReg_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    HighF_ShiftReg_SR_CONTROL &= ((uint8) ~HighF_ShiftReg_CLK_EN);
    HighF_ShiftReg_DisableInt();
}


/*******************************************************************************
* Function Name: HighF_ShiftReg_EnableInt
********************************************************************************
*
* Summary:
*  Enables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void HighF_ShiftReg_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    HighF_ShiftReg_SR_AUX_CONTROL |= HighF_ShiftReg_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: HighF_ShiftReg_DisableInt
********************************************************************************
*
* Summary:
*  Disables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void HighF_ShiftReg_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    HighF_ShiftReg_SR_AUX_CONTROL &= ((uint8) ~HighF_ShiftReg_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: HighF_ShiftReg_GetFIFOStatus
********************************************************************************
*
* Summary:
*  Returns current status of input or output FIFO.
*
* Parameters:
*  fifoId.
*
* Return:
*  FIFO status.
*
*******************************************************************************/
uint8 HighF_ShiftReg_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = HighF_ShiftReg_RET_FIFO_NOT_DEFINED;

    #if(0u != HighF_ShiftReg_USE_INPUT_FIFO)
        if(HighF_ShiftReg_IN_FIFO == fifoId)
        {
            switch(HighF_ShiftReg_GET_IN_FIFO_STS)
            {
                case HighF_ShiftReg_IN_FIFO_FULL :
                    result = HighF_ShiftReg_RET_FIFO_FULL;
                    break;

                case HighF_ShiftReg_IN_FIFO_EMPTY :
                    result = HighF_ShiftReg_RET_FIFO_EMPTY;
                    break;

                case HighF_ShiftReg_IN_FIFO_PARTIAL:
                    result = HighF_ShiftReg_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = HighF_ShiftReg_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != HighF_ShiftReg_USE_INPUT_FIFO) */

    if(HighF_ShiftReg_OUT_FIFO == fifoId)
    {
        switch(HighF_ShiftReg_GET_OUT_FIFO_STS)
        {
            case HighF_ShiftReg_OUT_FIFO_FULL :
                result = HighF_ShiftReg_RET_FIFO_FULL;
                break;

            case HighF_ShiftReg_OUT_FIFO_EMPTY :
                result = HighF_ShiftReg_RET_FIFO_EMPTY;
                break;

            case HighF_ShiftReg_OUT_FIFO_PARTIAL :
                result = HighF_ShiftReg_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = HighF_ShiftReg_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: HighF_ShiftReg_SetIntMode
********************************************************************************
*
* Summary:
*  Sets the Interrupt Source for the Shift Register interrupt. Multiple
*  sources may be ORed together
*
* Parameters:
*  interruptSource: Byte containing the constant for the selected interrupt
*  source/s.
*
* Return:
*  None.
*
*******************************************************************************/
void HighF_ShiftReg_SetIntMode(uint8 interruptSource) 
{
    HighF_ShiftReg_SR_STATUS_MASK &= ((uint8) ~HighF_ShiftReg_INTS_EN_MASK);          /* Clear existing int */
    HighF_ShiftReg_SR_STATUS_MASK |= (interruptSource & HighF_ShiftReg_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: HighF_ShiftReg_GetIntStatus
********************************************************************************
*
* Summary:
*  Gets the Shift Register Interrupt status.
*
* Parameters:
*  None.
*
* Return:
*  Byte containing the constant for the selected interrupt source/s.
*
*******************************************************************************/
uint8 HighF_ShiftReg_GetIntStatus(void) 
{
    return(HighF_ShiftReg_SR_STATUS & HighF_ShiftReg_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: HighF_ShiftReg_WriteRegValue
********************************************************************************
*
* Summary:
*  Send state directly to shift register
*
* Parameters:
*  shiftData: containing shift register state.
*
* Return:
*  None.
*
*******************************************************************************/
void HighF_ShiftReg_WriteRegValue(uint32 shiftData)
                                                                     
{
    CY_SET_REG32(HighF_ShiftReg_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != HighF_ShiftReg_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: HighF_ShiftReg_WriteData
    ********************************************************************************
    *
    * Summary:
    *  Send state to FIFO for later transfer to shift register based on the Load
    *  input
    *
    * Parameters:
    *  shiftData: containing shift register state.
    *
    * Return:
    *  Indicates: successful execution of function
    *  when FIFO is empty; and error when FIFO is full.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    cystatus HighF_ShiftReg_WriteData(uint32 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(HighF_ShiftReg_RET_FIFO_FULL != (HighF_ShiftReg_GetFIFOStatus(HighF_ShiftReg_IN_FIFO)))
        {
            CY_SET_REG32(HighF_ShiftReg_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != HighF_ShiftReg_USE_INPUT_FIFO) */


#if(0u != HighF_ShiftReg_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: HighF_ShiftReg_ReadData
    ********************************************************************************
    *
    * Summary:
    *  Returns state in FIFO due to Store input.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Shift Register state
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint32 HighF_ShiftReg_ReadData(void) 
    {
        return(CY_GET_REG32(HighF_ShiftReg_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != HighF_ShiftReg_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: HighF_ShiftReg_ReadRegValue
********************************************************************************
*
* Summary:
*  Directly returns current state in shift register, not data in FIFO due
*  to Store input.
*
* Parameters:
*  None.
*
* Return:
*  Shift Register state. Clears output FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint32 HighF_ShiftReg_ReadRegValue(void) 
{
    uint32 result;

    /* Clear FIFO before software capture */
    while(HighF_ShiftReg_RET_FIFO_EMPTY != HighF_ShiftReg_GetFIFOStatus(HighF_ShiftReg_OUT_FIFO))
    {
        (void) CY_GET_REG32(HighF_ShiftReg_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(HighF_ShiftReg_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG32(HighF_ShiftReg_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (HighF_ShiftReg_SR_SIZE % 8u))
        result &= ((uint32) HighF_ShiftReg_SR_MASK);
    #endif /* (0u != (HighF_ShiftReg_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
