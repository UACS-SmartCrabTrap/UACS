/*******************************************************************************
* File Name: VGround_Buffer.c  
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the PGA 
*  User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "VGround_Buffer.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static VGround_Buffer_BACKUP_STRUCT  VGround_Buffer_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 VGround_Buffer_initVar = 0u;


/*******************************************************************************   
* Function Name: VGround_Buffer_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  VGround_Buffer_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void VGround_Buffer_Init(void) 
{
    /* Set PGA mode */
    VGround_Buffer_CR0_REG = VGround_Buffer_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    VGround_Buffer_CR1_REG |= VGround_Buffer_PGA_NINV;  
    /* Set default gain and ref mode */
    VGround_Buffer_CR2_REG = VGround_Buffer_VREF_MODE;
    /* Set gain and compensation */
    VGround_Buffer_SetGain(VGround_Buffer_DEFAULT_GAIN);
    /* Set power */
    VGround_Buffer_SetPower(VGround_Buffer_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: VGround_Buffer_Enable
********************************************************************************
*
* Summary:
*  Enables the PGA block operation.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void VGround_Buffer_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(VGround_Buffer_P5backup.enableState == 1u)
        {
            VGround_Buffer_CR1_REG = VGround_Buffer_P5backup.scCR1Reg;
            VGround_Buffer_CR2_REG = VGround_Buffer_P5backup.scCR2Reg;
            VGround_Buffer_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    VGround_Buffer_PM_ACT_CFG_REG |= VGround_Buffer_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    VGround_Buffer_PM_STBY_CFG_REG |= VGround_Buffer_STBY_PWR_EN;
    
    VGround_Buffer_PUMP_CR1_REG |= VGround_Buffer_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                VGround_Buffer_BSTCLK_REG &= (uint8)(~VGround_Buffer_BST_CLK_INDEX_MASK);
                VGround_Buffer_BSTCLK_REG |= VGround_Buffer_BST_CLK_EN | CyScBoostClk__INDEX;
                VGround_Buffer_SC_MISC_REG |= VGround_Buffer_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                VGround_Buffer_BSTCLK_REG &= (uint8)(~VGround_Buffer_BST_CLK_EN);
                VGround_Buffer_SC_MISC_REG &= (uint8)(~VGround_Buffer_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: VGround_Buffer_Start
********************************************************************************
*
* Summary:
*  The start function initializes the PGA with the default values and sets
*  the power to the given level. A power level of 0, is same as executing
*  the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void VGround_Buffer_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(VGround_Buffer_initVar == 0u)
    {
        VGround_Buffer_Init();
        VGround_Buffer_initVar = 1u;
    }

    VGround_Buffer_Enable();
}


/*******************************************************************************
* Function Name: VGround_Buffer_Stop
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
void VGround_Buffer_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    VGround_Buffer_PM_ACT_CFG_REG &= (uint8)(~VGround_Buffer_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    VGround_Buffer_PM_STBY_CFG_REG &= (uint8)(~VGround_Buffer_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            VGround_Buffer_BSTCLK_REG &= (uint8)(~VGround_Buffer_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((VGround_Buffer_PM_ACT_CFG_REG & VGround_Buffer_PM_ACT_CFG_MASK) == 0u)
            {
                VGround_Buffer_SC_MISC_REG &= (uint8)(~VGround_Buffer_PUMP_FORCE);
                VGround_Buffer_PUMP_CR1_REG &= (uint8)(~VGround_Buffer_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        VGround_Buffer_P5backup.scCR1Reg = VGround_Buffer_CR1_REG;
        VGround_Buffer_P5backup.scCR2Reg = VGround_Buffer_CR2_REG;
        VGround_Buffer_CR1_REG = 0x00u;
        VGround_Buffer_CR2_REG = 0x00u;
        VGround_Buffer_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VGround_Buffer_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the PGA.
*
* Parameters:
*  power: Sets power level between (0) and (3) high power
*
* Return:
*  void
*
*******************************************************************************/
void VGround_Buffer_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = VGround_Buffer_CR1_REG & (uint8)(~VGround_Buffer_DRIVE_MASK);
    tmpCR |= (power & VGround_Buffer_DRIVE_MASK);
    VGround_Buffer_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: VGround_Buffer_SetGain
********************************************************************************
*
* Summary:
*  This function sets values of the input and feedback resistors to set a 
*  specific gain of the amplifier.
*
* Parameters:
*  gain: Gain value of PGA (See header file for gain values.)
*
* Return:
*  void 
*
*******************************************************************************/
void VGround_Buffer_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 VGround_Buffer_GainArray[9] = { 
        (VGround_Buffer_RVAL_0K   | VGround_Buffer_R20_40B_40K | VGround_Buffer_BIAS_LOW), /* G=1  */
        (VGround_Buffer_RVAL_40K  | VGround_Buffer_R20_40B_40K | VGround_Buffer_BIAS_LOW), /* G=2  */
        (VGround_Buffer_RVAL_120K | VGround_Buffer_R20_40B_40K | VGround_Buffer_BIAS_LOW), /* G=4  */
        (VGround_Buffer_RVAL_280K | VGround_Buffer_R20_40B_40K | VGround_Buffer_BIAS_LOW), /* G=8  */
        (VGround_Buffer_RVAL_600K | VGround_Buffer_R20_40B_40K | VGround_Buffer_BIAS_LOW), /* G=16 */
        (VGround_Buffer_RVAL_460K | VGround_Buffer_R20_40B_40K | VGround_Buffer_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (VGround_Buffer_RVAL_620K | VGround_Buffer_R20_40B_20K | VGround_Buffer_BIAS_LOW), /* G=32 */
        (VGround_Buffer_RVAL_470K | VGround_Buffer_R20_40B_20K | VGround_Buffer_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (VGround_Buffer_RVAL_490K | VGround_Buffer_R20_40B_20K | VGround_Buffer_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 VGround_Buffer_GainComp[9] = { 
        ( VGround_Buffer_COMP_4P35PF  | (uint8)( VGround_Buffer_REDC_00 >> 2 )), /* G=1  */
        ( VGround_Buffer_COMP_4P35PF  | (uint8)( VGround_Buffer_REDC_01 >> 2 )), /* G=2  */
        ( VGround_Buffer_COMP_3P0PF   | (uint8)( VGround_Buffer_REDC_01 >> 2 )), /* G=4  */
        ( VGround_Buffer_COMP_3P0PF   | (uint8)( VGround_Buffer_REDC_01 >> 2 )), /* G=8  */
        ( VGround_Buffer_COMP_3P6PF   | (uint8)( VGround_Buffer_REDC_01 >> 2 )), /* G=16 */
        ( VGround_Buffer_COMP_3P6PF   | (uint8)( VGround_Buffer_REDC_11 >> 2 )), /* G=24 */
        ( VGround_Buffer_COMP_3P6PF   | (uint8)( VGround_Buffer_REDC_11 >> 2 )), /* G=32 */
        ( VGround_Buffer_COMP_3P6PF   | (uint8)( VGround_Buffer_REDC_00 >> 2 )), /* G=48 */
        ( VGround_Buffer_COMP_3P6PF   | (uint8)( VGround_Buffer_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= VGround_Buffer_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        VGround_Buffer_CR2_REG &= (uint8)(~(VGround_Buffer_RVAL_MASK | VGround_Buffer_R20_40B_MASK | 
                                VGround_Buffer_REDC_MASK | VGround_Buffer_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        VGround_Buffer_CR2_REG |= (VGround_Buffer_GainArray[gain] |
                                ((uint8)(VGround_Buffer_GainComp[gain] << 2 ) & VGround_Buffer_REDC_MASK));

        /* Clear sc_comp  */
        VGround_Buffer_CR1_REG &= (uint8)(~VGround_Buffer_COMP_MASK);
        /* Set sc_comp  */
        VGround_Buffer_CR1_REG |= ( VGround_Buffer_GainComp[gain] | VGround_Buffer_COMP_MASK );
    }
}


/* [] END OF FILE */
