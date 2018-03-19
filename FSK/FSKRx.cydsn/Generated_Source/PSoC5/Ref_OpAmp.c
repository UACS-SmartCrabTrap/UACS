/*******************************************************************************
* File Name: Ref_OpAmp.c
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

#include "Ref_OpAmp.h"

uint8 Ref_OpAmp_initVar = 0u;


/*******************************************************************************   
* Function Name: Ref_OpAmp_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Ref_OpAmp_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Ref_OpAmp_Init(void) 
{
    Ref_OpAmp_SetPower(Ref_OpAmp_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: Ref_OpAmp_Enable
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
void Ref_OpAmp_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    Ref_OpAmp_PUMP_CR1_REG  |= (Ref_OpAmp_PUMP_CR1_CLKSEL | Ref_OpAmp_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    Ref_OpAmp_PM_ACT_CFG_REG |= Ref_OpAmp_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    Ref_OpAmp_PM_STBY_CFG_REG |= Ref_OpAmp_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   Ref_OpAmp_Start
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
*  Ref_OpAmp_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void Ref_OpAmp_Start(void) 
{
    if(Ref_OpAmp_initVar == 0u)
    {
        Ref_OpAmp_initVar = 1u;
        Ref_OpAmp_Init();
    }

    Ref_OpAmp_Enable();
}


/*******************************************************************************
* Function Name: Ref_OpAmp_Stop
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
void Ref_OpAmp_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    Ref_OpAmp_PM_ACT_CFG_REG &= (uint8)(~Ref_OpAmp_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    Ref_OpAmp_PM_STBY_CFG_REG &= (uint8)(~Ref_OpAmp_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(Ref_OpAmp_PM_ACT_CFG_REG == 0u)
    {
        Ref_OpAmp_PUMP_CR1_REG &= (uint8)(~(Ref_OpAmp_PUMP_CR1_CLKSEL | Ref_OpAmp_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: Ref_OpAmp_SetPower
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
void Ref_OpAmp_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        Ref_OpAmp_CR_REG &= (uint8)(~Ref_OpAmp_PWR_MASK);
        Ref_OpAmp_CR_REG |= power & Ref_OpAmp_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(Ref_OpAmp_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
