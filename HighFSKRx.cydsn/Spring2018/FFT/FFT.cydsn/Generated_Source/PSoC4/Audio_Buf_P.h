/*******************************************************************************
* File Name: Audio_Buf_P.h
* Version 1.20
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Opamp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_Audio_Buf_P_H)
#define CY_OPAMP_Audio_Buf_P_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Audio_Buf_P_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void Audio_Buf_P_Init(void);
void Audio_Buf_P_Enable(void);
void Audio_Buf_P_Start(void);
void Audio_Buf_P_Stop(void);
void Audio_Buf_P_SetPower(uint32 power);
void Audio_Buf_P_PumpControl(uint32 onOff);
void Audio_Buf_P_Sleep(void);
void Audio_Buf_P_Wakeup(void);
void Audio_Buf_P_SaveConfig(void);
void Audio_Buf_P_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define Audio_Buf_P_LOW_POWER      (1u)
#define Audio_Buf_P_MED_POWER      (2u)
#define Audio_Buf_P_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define Audio_Buf_P_PUMP_ON        (1u)
#define Audio_Buf_P_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define Audio_Buf_P_OUTPUT_CURRENT         (0u)
#define Audio_Buf_P_POWER                  (3u)
#define Audio_Buf_P_MODE                   (1u)
#define Audio_Buf_P_OA_COMP_TRIM_VALUE     (1u)
#define Audio_Buf_P_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  Audio_Buf_P_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define Audio_Buf_P_CTB_CTRL_REG       (*(reg32 *) Audio_Buf_P_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define Audio_Buf_P_CTB_CTRL_PTR       ( (reg32 *) Audio_Buf_P_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define Audio_Buf_P_CTB_CTRL_REG       (*(reg32 *) Audio_Buf_P_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define Audio_Buf_P_CTB_CTRL_PTR       ( (reg32 *) Audio_Buf_P_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define Audio_Buf_P_OA_RES_CTRL_REG    (*(reg32 *) Audio_Buf_P_cy_psoc4_abuf__OA_RES_CTRL)
#define Audio_Buf_P_OA_RES_CTRL_PTR    ( (reg32 *) Audio_Buf_P_cy_psoc4_abuf__OA_RES_CTRL)
#define Audio_Buf_P_OA_COMP_TRIM_REG   (*(reg32 *) Audio_Buf_P_cy_psoc4_abuf__OA_COMP_TRIM)
#define Audio_Buf_P_OA_COMP_TRIM_PTR   ( (reg32 *) Audio_Buf_P_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* Audio_Buf_P_CTB_CTRL_REG */
#define Audio_Buf_P_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define Audio_Buf_P_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define Audio_Buf_P_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << Audio_Buf_P_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define Audio_Buf_P_CTB_CTRL_ENABLED               ((uint32) 0x01u << Audio_Buf_P_CTB_CTRL_ENABLED_SHIFT)


/* Audio_Buf_P_OA_RES_CTRL_REG */
#define Audio_Buf_P_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define Audio_Buf_P_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define Audio_Buf_P_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define Audio_Buf_P_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define Audio_Buf_P_OA_PWR_MODE                ((uint32) 0x02u << Audio_Buf_P_OA_PWR_MODE_SHIFT)
#define Audio_Buf_P_OA_PWR_MODE_MASK           ((uint32) 0x03u << Audio_Buf_P_OA_PWR_MODE_SHIFT)
#define Audio_Buf_P_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << Audio_Buf_P_OA_DRIVE_STR_SEL_SHIFT)
#define Audio_Buf_P_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << Audio_Buf_P_OA_DRIVE_STR_SEL_SHIFT)
#define Audio_Buf_P_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << Audio_Buf_P_OA_DRIVE_STR_SEL_SHIFT)
#define Audio_Buf_P_OA_COMP_EN                 ((uint32) 0x00u << Audio_Buf_P_OA_COMP_EN_SHIFT)
#define Audio_Buf_P_OA_PUMP_EN                 ((uint32) 0x01u << Audio_Buf_P_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define Audio_Buf_P_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (Audio_Buf_P_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define Audio_Buf_P_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (Audio_Buf_P_OA_DRIVE_STR_SEL_10X) : \
                                                                             (Audio_Buf_P_OA_DRIVE_STR_SEL_1X))
#define Audio_Buf_P_GET_OA_PWR_MODE(mode)          ((mode) & Audio_Buf_P_OA_PWR_MODE_MASK)
#define Audio_Buf_P_CHECK_PWR_MODE_OFF             (0u != (Audio_Buf_P_OA_RES_CTRL_REG & \
                                                                Audio_Buf_P_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define Audio_Buf_P_CHECK_DEEPSLEEP_SUPPORT        (0u != Audio_Buf_P_DEEPSLEEP_SUPPORT) 

#define Audio_Buf_P_DEFAULT_CTB_CTRL (Audio_Buf_P_GET_DEEPSLEEP_ON(Audio_Buf_P_DEEPSLEEP_SUPPORT) | \
                                           Audio_Buf_P_CTB_CTRL_ENABLED)

#define Audio_Buf_P_DEFAULT_OA_RES_CTRL (Audio_Buf_P_OA_COMP_EN | \
                                              Audio_Buf_P_GET_OA_DRIVE_STR(Audio_Buf_P_OUTPUT_CURRENT))

#define Audio_Buf_P_DEFAULT_OA_COMP_TRIM_REG (Audio_Buf_P_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define Audio_Buf_P_LOWPOWER                   (Audio_Buf_P_LOW_POWER)
#define Audio_Buf_P_MEDPOWER                   (Audio_Buf_P_MED_POWER)
#define Audio_Buf_P_HIGHPOWER                  (Audio_Buf_P_HIGH_POWER)

/* PUMP ON/OFF defines */
#define Audio_Buf_P_PUMPON                     (Audio_Buf_P_PUMP_ON)
#define Audio_Buf_P_PUMPOFF                    (Audio_Buf_P_PUMP_OFF)

#define Audio_Buf_P_OA_CTRL                    (Audio_Buf_P_CTB_CTRL_REG)
#define Audio_Buf_P_OA_RES_CTRL                (Audio_Buf_P_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define Audio_Buf_P_OA_CTB_EN_SHIFT            (Audio_Buf_P_CTB_CTRL_ENABLED_SHIFT)
#define Audio_Buf_P_OA_PUMP_CTRL_SHIFT         (Audio_Buf_P_OA_PUMP_EN_SHIFT)
#define Audio_Buf_P_OA_PUMP_EN_MASK            (0x800u)
#define Audio_Buf_P_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_Audio_Buf_P_H */


/* [] END OF FILE */
