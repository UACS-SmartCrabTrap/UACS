/*******************************************************************************
* File Name: HighF_PGA.c  
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

#include "HighF_PGA.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static HighF_PGA_BACKUP_STRUCT  HighF_PGA_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 HighF_PGA_initVar = 0u;


/*******************************************************************************   
* Function Name: HighF_PGA_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  HighF_PGA_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void HighF_PGA_Init(void) 
{
    /* Set PGA mode */
    HighF_PGA_CR0_REG = HighF_PGA_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    HighF_PGA_CR1_REG |= HighF_PGA_PGA_NINV;  
    /* Set default gain and ref mode */
    HighF_PGA_CR2_REG = HighF_PGA_VREF_MODE;
    /* Set gain and compensation */
    HighF_PGA_SetGain(HighF_PGA_DEFAULT_GAIN);
    /* Set power */
    HighF_PGA_SetPower(HighF_PGA_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: HighF_PGA_Enable
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
void HighF_PGA_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(HighF_PGA_P5backup.enableState == 1u)
        {
            HighF_PGA_CR1_REG = HighF_PGA_P5backup.scCR1Reg;
            HighF_PGA_CR2_REG = HighF_PGA_P5backup.scCR2Reg;
            HighF_PGA_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    HighF_PGA_PM_ACT_CFG_REG |= HighF_PGA_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    HighF_PGA_PM_STBY_CFG_REG |= HighF_PGA_STBY_PWR_EN;
    
    HighF_PGA_PUMP_CR1_REG |= HighF_PGA_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                HighF_PGA_BSTCLK_REG &= (uint8)(~HighF_PGA_BST_CLK_INDEX_MASK);
                HighF_PGA_BSTCLK_REG |= HighF_PGA_BST_CLK_EN | CyScBoostClk__INDEX;
                HighF_PGA_SC_MISC_REG |= HighF_PGA_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                HighF_PGA_BSTCLK_REG &= (uint8)(~HighF_PGA_BST_CLK_EN);
                HighF_PGA_SC_MISC_REG &= (uint8)(~HighF_PGA_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: HighF_PGA_Start
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
void HighF_PGA_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(HighF_PGA_initVar == 0u)
    {
        HighF_PGA_Init();
        HighF_PGA_initVar = 1u;
    }

    HighF_PGA_Enable();
}


/*******************************************************************************
* Function Name: HighF_PGA_Stop
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
void HighF_PGA_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    HighF_PGA_PM_ACT_CFG_REG &= (uint8)(~HighF_PGA_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    HighF_PGA_PM_STBY_CFG_REG &= (uint8)(~HighF_PGA_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            HighF_PGA_BSTCLK_REG &= (uint8)(~HighF_PGA_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((HighF_PGA_PM_ACT_CFG_REG & HighF_PGA_PM_ACT_CFG_MASK) == 0u)
            {
                HighF_PGA_SC_MISC_REG &= (uint8)(~HighF_PGA_PUMP_FORCE);
                HighF_PGA_PUMP_CR1_REG &= (uint8)(~HighF_PGA_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        HighF_PGA_P5backup.scCR1Reg = HighF_PGA_CR1_REG;
        HighF_PGA_P5backup.scCR2Reg = HighF_PGA_CR2_REG;
        HighF_PGA_CR1_REG = 0x00u;
        HighF_PGA_CR2_REG = 0x00u;
        HighF_PGA_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: HighF_PGA_SetPower
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
void HighF_PGA_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = HighF_PGA_CR1_REG & (uint8)(~HighF_PGA_DRIVE_MASK);
    tmpCR |= (power & HighF_PGA_DRIVE_MASK);
    HighF_PGA_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: HighF_PGA_SetGain
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
void HighF_PGA_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 HighF_PGA_GainArray[9] = { 
        (HighF_PGA_RVAL_0K   | HighF_PGA_R20_40B_40K | HighF_PGA_BIAS_LOW), /* G=1  */
        (HighF_PGA_RVAL_40K  | HighF_PGA_R20_40B_40K | HighF_PGA_BIAS_LOW), /* G=2  */
        (HighF_PGA_RVAL_120K | HighF_PGA_R20_40B_40K | HighF_PGA_BIAS_LOW), /* G=4  */
        (HighF_PGA_RVAL_280K | HighF_PGA_R20_40B_40K | HighF_PGA_BIAS_LOW), /* G=8  */
        (HighF_PGA_RVAL_600K | HighF_PGA_R20_40B_40K | HighF_PGA_BIAS_LOW), /* G=16 */
        (HighF_PGA_RVAL_460K | HighF_PGA_R20_40B_40K | HighF_PGA_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (HighF_PGA_RVAL_620K | HighF_PGA_R20_40B_20K | HighF_PGA_BIAS_LOW), /* G=32 */
        (HighF_PGA_RVAL_470K | HighF_PGA_R20_40B_20K | HighF_PGA_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (HighF_PGA_RVAL_490K | HighF_PGA_R20_40B_20K | HighF_PGA_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 HighF_PGA_GainComp[9] = { 
        ( HighF_PGA_COMP_4P35PF  | (uint8)( HighF_PGA_REDC_00 >> 2 )), /* G=1  */
        ( HighF_PGA_COMP_4P35PF  | (uint8)( HighF_PGA_REDC_01 >> 2 )), /* G=2  */
        ( HighF_PGA_COMP_3P0PF   | (uint8)( HighF_PGA_REDC_01 >> 2 )), /* G=4  */
        ( HighF_PGA_COMP_3P0PF   | (uint8)( HighF_PGA_REDC_01 >> 2 )), /* G=8  */
        ( HighF_PGA_COMP_3P6PF   | (uint8)( HighF_PGA_REDC_01 >> 2 )), /* G=16 */
        ( HighF_PGA_COMP_3P6PF   | (uint8)( HighF_PGA_REDC_11 >> 2 )), /* G=24 */
        ( HighF_PGA_COMP_3P6PF   | (uint8)( HighF_PGA_REDC_11 >> 2 )), /* G=32 */
        ( HighF_PGA_COMP_3P6PF   | (uint8)( HighF_PGA_REDC_00 >> 2 )), /* G=48 */
        ( HighF_PGA_COMP_3P6PF   | (uint8)( HighF_PGA_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= HighF_PGA_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        HighF_PGA_CR2_REG &= (uint8)(~(HighF_PGA_RVAL_MASK | HighF_PGA_R20_40B_MASK | 
                                HighF_PGA_REDC_MASK | HighF_PGA_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        HighF_PGA_CR2_REG |= (HighF_PGA_GainArray[gain] |
                                ((uint8)(HighF_PGA_GainComp[gain] << 2 ) & HighF_PGA_REDC_MASK));

        /* Clear sc_comp  */
        HighF_PGA_CR1_REG &= (uint8)(~HighF_PGA_COMP_MASK);
        /* Set sc_comp  */
        HighF_PGA_CR1_REG |= ( HighF_PGA_GainComp[gain] | HighF_PGA_COMP_MASK );
    }
}


/* [] END OF FILE */
