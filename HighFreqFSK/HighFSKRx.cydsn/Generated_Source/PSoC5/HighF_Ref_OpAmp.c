/*******************************************************************************
* File Name: HighF_Ref_OpAmp.c
* Version 1.90
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer) 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "HighF_Ref_OpAmp.h"

uint8 HighF_Ref_OpAmp_initVar = 0u;


/*******************************************************************************   
* Function Name: HighF_Ref_OpAmp_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  HighF_Ref_OpAmp_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HighF_Ref_OpAmp_Init(void) 
{
    HighF_Ref_OpAmp_SetPower(HighF_Ref_OpAmp_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: HighF_Ref_OpAmp_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HighF_Ref_OpAmp_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    HighF_Ref_OpAmp_PUMP_CR1_REG  |= (HighF_Ref_OpAmp_PUMP_CR1_CLKSEL | HighF_Ref_OpAmp_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    HighF_Ref_OpAmp_PM_ACT_CFG_REG |= HighF_Ref_OpAmp_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    HighF_Ref_OpAmp_PM_STBY_CFG_REG |= HighF_Ref_OpAmp_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   HighF_Ref_OpAmp_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and 
*  sets the power to the given level. A power level of 0, is same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  HighF_Ref_OpAmp_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void HighF_Ref_OpAmp_Start(void) 
{
    if(HighF_Ref_OpAmp_initVar == 0u)
    {
        HighF_Ref_OpAmp_initVar = 1u;
        HighF_Ref_OpAmp_Init();
    }

    HighF_Ref_OpAmp_Enable();
}


/*******************************************************************************
* Function Name: HighF_Ref_OpAmp_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HighF_Ref_OpAmp_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    HighF_Ref_OpAmp_PM_ACT_CFG_REG &= (uint8)(~HighF_Ref_OpAmp_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    HighF_Ref_OpAmp_PM_STBY_CFG_REG &= (uint8)(~HighF_Ref_OpAmp_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(HighF_Ref_OpAmp_PM_ACT_CFG_REG == 0u)
    {
        HighF_Ref_OpAmp_PUMP_CR1_REG &= (uint8)(~(HighF_Ref_OpAmp_PUMP_CR1_CLKSEL | HighF_Ref_OpAmp_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: HighF_Ref_OpAmp_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters: 
*  power: PSoC3: Sets power level between low (1) and high power (3).
*         PSoC5: Sets power level High (0)
*
* Return:
*  void
*
**********************************************************************************/
void HighF_Ref_OpAmp_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        HighF_Ref_OpAmp_CR_REG &= (uint8)(~HighF_Ref_OpAmp_PWR_MASK);
        HighF_Ref_OpAmp_CR_REG |= power & HighF_Ref_OpAmp_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(HighF_Ref_OpAmp_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
