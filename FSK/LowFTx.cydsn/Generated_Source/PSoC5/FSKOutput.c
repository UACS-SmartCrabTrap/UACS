/*******************************************************************************
* File Name: FSKOutput.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "FSKOutput.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 FSKOutput_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 FSKOutput_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static FSKOutput_backupStruct FSKOutput_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: FSKOutput_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FSKOutput_Init(void) 
{
    FSKOutput_CR0 = (FSKOutput_MODE_V );

    /* Set default data source */
    #if(FSKOutput_DEFAULT_DATA_SRC != 0 )
        FSKOutput_CR1 = (FSKOutput_DEFAULT_CNTL | FSKOutput_DACBUS_ENABLE) ;
    #else
        FSKOutput_CR1 = (FSKOutput_DEFAULT_CNTL | FSKOutput_DACBUS_DISABLE) ;
    #endif /* (FSKOutput_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(FSKOutput_DEFAULT_STRB != 0)
        FSKOutput_Strobe |= FSKOutput_STRB_EN ;
    #endif/* (FSKOutput_DEFAULT_STRB != 0) */

    /* Set default range */
    FSKOutput_SetRange(FSKOutput_DEFAULT_RANGE); 

    /* Set default speed */
    FSKOutput_SetSpeed(FSKOutput_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: FSKOutput_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FSKOutput_Enable(void) 
{
    FSKOutput_PWRMGR |= FSKOutput_ACT_PWR_EN;
    FSKOutput_STBY_PWRMGR |= FSKOutput_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(FSKOutput_restoreVal == 1u) 
        {
             FSKOutput_CR0 = FSKOutput_backup.data_value;
             FSKOutput_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: FSKOutput_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  FSKOutput_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void FSKOutput_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(FSKOutput_initVar == 0u)
    { 
        FSKOutput_Init();
        FSKOutput_initVar = 1u;
    }

    /* Enable power to DAC */
    FSKOutput_Enable();

    /* Set default value */
    FSKOutput_SetValue(FSKOutput_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: FSKOutput_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FSKOutput_Stop(void) 
{
    /* Disble power to DAC */
    FSKOutput_PWRMGR &= (uint8)(~FSKOutput_ACT_PWR_EN);
    FSKOutput_STBY_PWRMGR &= (uint8)(~FSKOutput_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        FSKOutput_backup.data_value = FSKOutput_CR0;
        FSKOutput_CR0 = FSKOutput_CUR_MODE_OUT_OFF;
        FSKOutput_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: FSKOutput_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FSKOutput_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    FSKOutput_CR0 &= (uint8)(~FSKOutput_HS_MASK);
    FSKOutput_CR0 |=  (speed & FSKOutput_HS_MASK);
}


/*******************************************************************************
* Function Name: FSKOutput_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void FSKOutput_SetRange(uint8 range) 
{
    FSKOutput_CR0 &= (uint8)(~FSKOutput_RANGE_MASK);      /* Clear existing mode */
    FSKOutput_CR0 |= (range & FSKOutput_RANGE_MASK);      /*  Set Range  */
    FSKOutput_DacTrim();
}


/*******************************************************************************
* Function Name: FSKOutput_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void FSKOutput_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 FSKOutput_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    FSKOutput_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        FSKOutput_Data = value;
        CyExitCriticalSection(FSKOutput_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: FSKOutput_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void FSKOutput_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((FSKOutput_CR0 & FSKOutput_RANGE_MASK) >> 2) + FSKOutput_TRIM_M7_1V_RNG_OFFSET;
    FSKOutput_TR = CY_GET_XTND_REG8((uint8 *)(FSKOutput_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
