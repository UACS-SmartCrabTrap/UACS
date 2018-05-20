/*******************************************************************************
* File Name: Shift_Reg.c
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

#include "Shift_Reg.h"

uint8 Shift_Reg_initVar = 0u;


/*******************************************************************************
* Function Name: Shift_Reg_Start
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
*  Shift_Reg_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Shift_Reg_Start(void) 
{
    if(0u == Shift_Reg_initVar)
    {
        Shift_Reg_Init();
        Shift_Reg_initVar = 1u; /* Component initialized */
    }

    Shift_Reg_Enable();
}


/*******************************************************************************
* Function Name: Shift_Reg_Enable
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
void Shift_Reg_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    Shift_Reg_SR_CONTROL |= Shift_Reg_CLK_EN;

    Shift_Reg_EnableInt();
}


/*******************************************************************************
* Function Name: Shift_Reg_Init
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
void Shift_Reg_Init(void) 
{
    Shift_Reg_SetIntMode(Shift_Reg_INT_SRC);
}


/*******************************************************************************
* Function Name: Shift_Reg_Stop
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
void Shift_Reg_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    Shift_Reg_SR_CONTROL &= ((uint8) ~Shift_Reg_CLK_EN);
    Shift_Reg_DisableInt();
}


/*******************************************************************************
* Function Name: Shift_Reg_EnableInt
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
void Shift_Reg_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    Shift_Reg_SR_AUX_CONTROL |= Shift_Reg_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Shift_Reg_DisableInt
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
void Shift_Reg_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    Shift_Reg_SR_AUX_CONTROL &= ((uint8) ~Shift_Reg_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Shift_Reg_GetFIFOStatus
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
uint8 Shift_Reg_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = Shift_Reg_RET_FIFO_NOT_DEFINED;

    #if(0u != Shift_Reg_USE_INPUT_FIFO)
        if(Shift_Reg_IN_FIFO == fifoId)
        {
            switch(Shift_Reg_GET_IN_FIFO_STS)
            {
                case Shift_Reg_IN_FIFO_FULL :
                    result = Shift_Reg_RET_FIFO_FULL;
                    break;

                case Shift_Reg_IN_FIFO_EMPTY :
                    result = Shift_Reg_RET_FIFO_EMPTY;
                    break;

                case Shift_Reg_IN_FIFO_PARTIAL:
                    result = Shift_Reg_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = Shift_Reg_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != Shift_Reg_USE_INPUT_FIFO) */

    if(Shift_Reg_OUT_FIFO == fifoId)
    {
        switch(Shift_Reg_GET_OUT_FIFO_STS)
        {
            case Shift_Reg_OUT_FIFO_FULL :
                result = Shift_Reg_RET_FIFO_FULL;
                break;

            case Shift_Reg_OUT_FIFO_EMPTY :
                result = Shift_Reg_RET_FIFO_EMPTY;
                break;

            case Shift_Reg_OUT_FIFO_PARTIAL :
                result = Shift_Reg_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = Shift_Reg_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: Shift_Reg_SetIntMode
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
void Shift_Reg_SetIntMode(uint8 interruptSource) 
{
    Shift_Reg_SR_STATUS_MASK &= ((uint8) ~Shift_Reg_INTS_EN_MASK);          /* Clear existing int */
    Shift_Reg_SR_STATUS_MASK |= (interruptSource & Shift_Reg_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: Shift_Reg_GetIntStatus
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
uint8 Shift_Reg_GetIntStatus(void) 
{
    return(Shift_Reg_SR_STATUS & Shift_Reg_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: Shift_Reg_WriteRegValue
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
void Shift_Reg_WriteRegValue(uint32 shiftData)
                                                                     
{
    CY_SET_REG32(Shift_Reg_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != Shift_Reg_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: Shift_Reg_WriteData
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
    cystatus Shift_Reg_WriteData(uint32 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(Shift_Reg_RET_FIFO_FULL != (Shift_Reg_GetFIFOStatus(Shift_Reg_IN_FIFO)))
        {
            CY_SET_REG32(Shift_Reg_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != Shift_Reg_USE_INPUT_FIFO) */


#if(0u != Shift_Reg_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: Shift_Reg_ReadData
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
    uint32 Shift_Reg_ReadData(void) 
    {
        return(CY_GET_REG32(Shift_Reg_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != Shift_Reg_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: Shift_Reg_ReadRegValue
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
uint32 Shift_Reg_ReadRegValue(void) 
{
    uint32 result;

    /* Clear FIFO before software capture */
    while(Shift_Reg_RET_FIFO_EMPTY != Shift_Reg_GetFIFOStatus(Shift_Reg_OUT_FIFO))
    {
        (void) CY_GET_REG32(Shift_Reg_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(Shift_Reg_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG32(Shift_Reg_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (Shift_Reg_SR_SIZE % 8u))
        result &= ((uint32) Shift_Reg_SR_MASK);
    #endif /* (0u != (Shift_Reg_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
