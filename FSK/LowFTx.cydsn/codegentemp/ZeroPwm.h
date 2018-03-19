/*******************************************************************************
* File Name: ZeroPwm.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_ZeroPwm_H)
#define CY_PWM_ZeroPwm_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 ZeroPwm_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define ZeroPwm_Resolution                     (16u)
#define ZeroPwm_UsingFixedFunction             (0u)
#define ZeroPwm_DeadBandMode                   (0u)
#define ZeroPwm_KillModeMinTime                (0u)
#define ZeroPwm_KillMode                       (0u)
#define ZeroPwm_PWMMode                        (0u)
#define ZeroPwm_PWMModeIsCenterAligned         (0u)
#define ZeroPwm_DeadBandUsed                   (0u)
#define ZeroPwm_DeadBand2_4                    (0u)

#if !defined(ZeroPwm_PWMUDB_genblk8_stsreg__REMOVED)
    #define ZeroPwm_UseStatus                  (1u)
#else
    #define ZeroPwm_UseStatus                  (0u)
#endif /* !defined(ZeroPwm_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(ZeroPwm_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define ZeroPwm_UseControl                 (1u)
#else
    #define ZeroPwm_UseControl                 (0u)
#endif /* !defined(ZeroPwm_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define ZeroPwm_UseOneCompareMode              (1u)
#define ZeroPwm_MinimumKillTime                (1u)
#define ZeroPwm_EnableMode                     (0u)

#define ZeroPwm_CompareMode1SW                 (0u)
#define ZeroPwm_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define ZeroPwm__B_PWM__DISABLED 0
#define ZeroPwm__B_PWM__ASYNCHRONOUS 1
#define ZeroPwm__B_PWM__SINGLECYCLE 2
#define ZeroPwm__B_PWM__LATCHED 3
#define ZeroPwm__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define ZeroPwm__B_PWM__DBMDISABLED 0
#define ZeroPwm__B_PWM__DBM_2_4_CLOCKS 1
#define ZeroPwm__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define ZeroPwm__B_PWM__ONE_OUTPUT 0
#define ZeroPwm__B_PWM__TWO_OUTPUTS 1
#define ZeroPwm__B_PWM__DUAL_EDGE 2
#define ZeroPwm__B_PWM__CENTER_ALIGN 3
#define ZeroPwm__B_PWM__DITHER 5
#define ZeroPwm__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define ZeroPwm__B_PWM__LESS_THAN 1
#define ZeroPwm__B_PWM__LESS_THAN_OR_EQUAL 2
#define ZeroPwm__B_PWM__GREATER_THAN 3
#define ZeroPwm__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define ZeroPwm__B_PWM__EQUAL 0
#define ZeroPwm__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!ZeroPwm_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!ZeroPwm_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!ZeroPwm_PWMModeIsCenterAligned) */
        #if (ZeroPwm_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (ZeroPwm_UseStatus) */

        /* Backup for Deadband parameters */
        #if(ZeroPwm_DeadBandMode == ZeroPwm__B_PWM__DBM_256_CLOCKS || \
            ZeroPwm_DeadBandMode == ZeroPwm__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(ZeroPwm_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (ZeroPwm_KillModeMinTime) */

        /* Backup control register */
        #if(ZeroPwm_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (ZeroPwm_UseControl) */

    #endif /* (!ZeroPwm_UsingFixedFunction) */

}ZeroPwm_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    ZeroPwm_Start(void) ;
void    ZeroPwm_Stop(void) ;

#if (ZeroPwm_UseStatus || ZeroPwm_UsingFixedFunction)
    void  ZeroPwm_SetInterruptMode(uint8 interruptMode) ;
    uint8 ZeroPwm_ReadStatusRegister(void) ;
#endif /* (ZeroPwm_UseStatus || ZeroPwm_UsingFixedFunction) */

#define ZeroPwm_GetInterruptSource() ZeroPwm_ReadStatusRegister()

#if (ZeroPwm_UseControl)
    uint8 ZeroPwm_ReadControlRegister(void) ;
    void  ZeroPwm_WriteControlRegister(uint8 control)
          ;
#endif /* (ZeroPwm_UseControl) */

#if (ZeroPwm_UseOneCompareMode)
   #if (ZeroPwm_CompareMode1SW)
       void    ZeroPwm_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (ZeroPwm_CompareMode1SW) */
#else
    #if (ZeroPwm_CompareMode1SW)
        void    ZeroPwm_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (ZeroPwm_CompareMode1SW) */
    #if (ZeroPwm_CompareMode2SW)
        void    ZeroPwm_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (ZeroPwm_CompareMode2SW) */
#endif /* (ZeroPwm_UseOneCompareMode) */

#if (!ZeroPwm_UsingFixedFunction)
    uint16   ZeroPwm_ReadCounter(void) ;
    uint16 ZeroPwm_ReadCapture(void) ;

    #if (ZeroPwm_UseStatus)
            void ZeroPwm_ClearFIFO(void) ;
    #endif /* (ZeroPwm_UseStatus) */

    void    ZeroPwm_WriteCounter(uint16 counter)
            ;
#endif /* (!ZeroPwm_UsingFixedFunction) */

void    ZeroPwm_WritePeriod(uint16 period)
        ;
uint16 ZeroPwm_ReadPeriod(void) ;

#if (ZeroPwm_UseOneCompareMode)
    void    ZeroPwm_WriteCompare(uint16 compare)
            ;
    uint16 ZeroPwm_ReadCompare(void) ;
#else
    void    ZeroPwm_WriteCompare1(uint16 compare)
            ;
    uint16 ZeroPwm_ReadCompare1(void) ;
    void    ZeroPwm_WriteCompare2(uint16 compare)
            ;
    uint16 ZeroPwm_ReadCompare2(void) ;
#endif /* (ZeroPwm_UseOneCompareMode) */


#if (ZeroPwm_DeadBandUsed)
    void    ZeroPwm_WriteDeadTime(uint8 deadtime) ;
    uint8   ZeroPwm_ReadDeadTime(void) ;
#endif /* (ZeroPwm_DeadBandUsed) */

#if ( ZeroPwm_KillModeMinTime)
    void ZeroPwm_WriteKillTime(uint8 killtime) ;
    uint8 ZeroPwm_ReadKillTime(void) ;
#endif /* ( ZeroPwm_KillModeMinTime) */

void ZeroPwm_Init(void) ;
void ZeroPwm_Enable(void) ;
void ZeroPwm_Sleep(void) ;
void ZeroPwm_Wakeup(void) ;
void ZeroPwm_SaveConfig(void) ;
void ZeroPwm_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define ZeroPwm_INIT_PERIOD_VALUE          (255u)
#define ZeroPwm_INIT_COMPARE_VALUE1        (127u)
#define ZeroPwm_INIT_COMPARE_VALUE2        (63u)
#define ZeroPwm_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    ZeroPwm_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ZeroPwm_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ZeroPwm_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    ZeroPwm_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define ZeroPwm_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  ZeroPwm_CTRL_CMPMODE2_SHIFT)
#define ZeroPwm_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  ZeroPwm_CTRL_CMPMODE1_SHIFT)
#define ZeroPwm_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (ZeroPwm_UsingFixedFunction)
   #define ZeroPwm_PERIOD_LSB              (*(reg16 *) ZeroPwm_PWMHW__PER0)
   #define ZeroPwm_PERIOD_LSB_PTR          ( (reg16 *) ZeroPwm_PWMHW__PER0)
   #define ZeroPwm_COMPARE1_LSB            (*(reg16 *) ZeroPwm_PWMHW__CNT_CMP0)
   #define ZeroPwm_COMPARE1_LSB_PTR        ( (reg16 *) ZeroPwm_PWMHW__CNT_CMP0)
   #define ZeroPwm_COMPARE2_LSB            (0x00u)
   #define ZeroPwm_COMPARE2_LSB_PTR        (0x00u)
   #define ZeroPwm_COUNTER_LSB             (*(reg16 *) ZeroPwm_PWMHW__CNT_CMP0)
   #define ZeroPwm_COUNTER_LSB_PTR         ( (reg16 *) ZeroPwm_PWMHW__CNT_CMP0)
   #define ZeroPwm_CAPTURE_LSB             (*(reg16 *) ZeroPwm_PWMHW__CAP0)
   #define ZeroPwm_CAPTURE_LSB_PTR         ( (reg16 *) ZeroPwm_PWMHW__CAP0)
   #define ZeroPwm_RT1                     (*(reg8 *)  ZeroPwm_PWMHW__RT1)
   #define ZeroPwm_RT1_PTR                 ( (reg8 *)  ZeroPwm_PWMHW__RT1)

#else
   #if (ZeroPwm_Resolution == 8u) /* 8bit - PWM */

       #if(ZeroPwm_PWMModeIsCenterAligned)
           #define ZeroPwm_PERIOD_LSB      (*(reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define ZeroPwm_PERIOD_LSB_PTR  ((reg8 *)   ZeroPwm_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define ZeroPwm_PERIOD_LSB      (*(reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define ZeroPwm_PERIOD_LSB_PTR  ((reg8 *)   ZeroPwm_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (ZeroPwm_PWMModeIsCenterAligned) */

       #define ZeroPwm_COMPARE1_LSB        (*(reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define ZeroPwm_COMPARE1_LSB_PTR    ((reg8 *)   ZeroPwm_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define ZeroPwm_COMPARE2_LSB        (*(reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define ZeroPwm_COMPARE2_LSB_PTR    ((reg8 *)   ZeroPwm_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define ZeroPwm_COUNTERCAP_LSB      (*(reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define ZeroPwm_COUNTERCAP_LSB_PTR  ((reg8 *)   ZeroPwm_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define ZeroPwm_COUNTER_LSB         (*(reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define ZeroPwm_COUNTER_LSB_PTR     ((reg8 *)   ZeroPwm_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define ZeroPwm_CAPTURE_LSB         (*(reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define ZeroPwm_CAPTURE_LSB_PTR     ((reg8 *)   ZeroPwm_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(ZeroPwm_PWMModeIsCenterAligned)
               #define ZeroPwm_PERIOD_LSB      (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define ZeroPwm_PERIOD_LSB_PTR  ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define ZeroPwm_PERIOD_LSB      (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define ZeroPwm_PERIOD_LSB_PTR  ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (ZeroPwm_PWMModeIsCenterAligned) */

            #define ZeroPwm_COMPARE1_LSB       (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define ZeroPwm_COMPARE1_LSB_PTR   ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define ZeroPwm_COMPARE2_LSB       (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define ZeroPwm_COMPARE2_LSB_PTR   ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define ZeroPwm_COUNTERCAP_LSB     (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define ZeroPwm_COUNTERCAP_LSB_PTR ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define ZeroPwm_COUNTER_LSB        (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define ZeroPwm_COUNTER_LSB_PTR    ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define ZeroPwm_CAPTURE_LSB        (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define ZeroPwm_CAPTURE_LSB_PTR    ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(ZeroPwm_PWMModeIsCenterAligned)
               #define ZeroPwm_PERIOD_LSB      (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define ZeroPwm_PERIOD_LSB_PTR  ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define ZeroPwm_PERIOD_LSB      (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define ZeroPwm_PERIOD_LSB_PTR  ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (ZeroPwm_PWMModeIsCenterAligned) */

            #define ZeroPwm_COMPARE1_LSB       (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define ZeroPwm_COMPARE1_LSB_PTR   ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define ZeroPwm_COMPARE2_LSB       (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define ZeroPwm_COMPARE2_LSB_PTR   ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define ZeroPwm_COUNTERCAP_LSB     (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define ZeroPwm_COUNTERCAP_LSB_PTR ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define ZeroPwm_COUNTER_LSB        (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define ZeroPwm_COUNTER_LSB_PTR    ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define ZeroPwm_CAPTURE_LSB        (*(reg16 *) ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define ZeroPwm_CAPTURE_LSB_PTR    ((reg16 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define ZeroPwm_AUX_CONTROLDP1          (*(reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define ZeroPwm_AUX_CONTROLDP1_PTR      ((reg8 *)   ZeroPwm_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (ZeroPwm_Resolution == 8) */

   #define ZeroPwm_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define ZeroPwm_AUX_CONTROLDP0          (*(reg8 *)  ZeroPwm_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define ZeroPwm_AUX_CONTROLDP0_PTR      ((reg8 *)   ZeroPwm_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (ZeroPwm_UsingFixedFunction) */

#if(ZeroPwm_KillModeMinTime )
    #define ZeroPwm_KILLMODEMINTIME        (*(reg8 *)  ZeroPwm_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define ZeroPwm_KILLMODEMINTIME_PTR    ((reg8 *)   ZeroPwm_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (ZeroPwm_KillModeMinTime ) */

#if(ZeroPwm_DeadBandMode == ZeroPwm__B_PWM__DBM_256_CLOCKS)
    #define ZeroPwm_DEADBAND_COUNT         (*(reg8 *)  ZeroPwm_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ZeroPwm_DEADBAND_COUNT_PTR     ((reg8 *)   ZeroPwm_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ZeroPwm_DEADBAND_LSB_PTR       ((reg8 *)   ZeroPwm_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define ZeroPwm_DEADBAND_LSB           (*(reg8 *)  ZeroPwm_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(ZeroPwm_DeadBandMode == ZeroPwm__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (ZeroPwm_UsingFixedFunction)
        #define ZeroPwm_DEADBAND_COUNT         (*(reg8 *)  ZeroPwm_PWMHW__CFG0)
        #define ZeroPwm_DEADBAND_COUNT_PTR     ((reg8 *)   ZeroPwm_PWMHW__CFG0)
        #define ZeroPwm_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ZeroPwm_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define ZeroPwm_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define ZeroPwm_DEADBAND_COUNT         (*(reg8 *)  ZeroPwm_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ZeroPwm_DEADBAND_COUNT_PTR     ((reg8 *)   ZeroPwm_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define ZeroPwm_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << ZeroPwm_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define ZeroPwm_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (ZeroPwm_UsingFixedFunction) */
#endif /* (ZeroPwm_DeadBandMode == ZeroPwm__B_PWM__DBM_256_CLOCKS) */



#if (ZeroPwm_UsingFixedFunction)
    #define ZeroPwm_STATUS                 (*(reg8 *) ZeroPwm_PWMHW__SR0)
    #define ZeroPwm_STATUS_PTR             ((reg8 *) ZeroPwm_PWMHW__SR0)
    #define ZeroPwm_STATUS_MASK            (*(reg8 *) ZeroPwm_PWMHW__SR0)
    #define ZeroPwm_STATUS_MASK_PTR        ((reg8 *) ZeroPwm_PWMHW__SR0)
    #define ZeroPwm_CONTROL                (*(reg8 *) ZeroPwm_PWMHW__CFG0)
    #define ZeroPwm_CONTROL_PTR            ((reg8 *) ZeroPwm_PWMHW__CFG0)
    #define ZeroPwm_CONTROL2               (*(reg8 *) ZeroPwm_PWMHW__CFG1)
    #define ZeroPwm_CONTROL3               (*(reg8 *) ZeroPwm_PWMHW__CFG2)
    #define ZeroPwm_GLOBAL_ENABLE          (*(reg8 *) ZeroPwm_PWMHW__PM_ACT_CFG)
    #define ZeroPwm_GLOBAL_ENABLE_PTR      ( (reg8 *) ZeroPwm_PWMHW__PM_ACT_CFG)
    #define ZeroPwm_GLOBAL_STBY_ENABLE     (*(reg8 *) ZeroPwm_PWMHW__PM_STBY_CFG)
    #define ZeroPwm_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) ZeroPwm_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define ZeroPwm_BLOCK_EN_MASK          (ZeroPwm_PWMHW__PM_ACT_MSK)
    #define ZeroPwm_BLOCK_STBY_EN_MASK     (ZeroPwm_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define ZeroPwm_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define ZeroPwm_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define ZeroPwm_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define ZeroPwm_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define ZeroPwm_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define ZeroPwm_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define ZeroPwm_CTRL_ENABLE            (uint8)((uint8)0x01u << ZeroPwm_CTRL_ENABLE_SHIFT)
    #define ZeroPwm_CTRL_RESET             (uint8)((uint8)0x01u << ZeroPwm_CTRL_RESET_SHIFT)
    #define ZeroPwm_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ZeroPwm_CTRL_CMPMODE2_SHIFT)
    #define ZeroPwm_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ZeroPwm_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define ZeroPwm_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define ZeroPwm_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << ZeroPwm_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define ZeroPwm_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define ZeroPwm_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define ZeroPwm_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define ZeroPwm_STATUS_TC_INT_EN_MASK_SHIFT            (ZeroPwm_STATUS_TC_SHIFT - 4u)
    #define ZeroPwm_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define ZeroPwm_STATUS_CMP1_INT_EN_MASK_SHIFT          (ZeroPwm_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define ZeroPwm_STATUS_TC              (uint8)((uint8)0x01u << ZeroPwm_STATUS_TC_SHIFT)
    #define ZeroPwm_STATUS_CMP1            (uint8)((uint8)0x01u << ZeroPwm_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define ZeroPwm_STATUS_TC_INT_EN_MASK              (uint8)((uint8)ZeroPwm_STATUS_TC >> 4u)
    #define ZeroPwm_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)ZeroPwm_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define ZeroPwm_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define ZeroPwm_RT1_MASK              (uint8)((uint8)0x03u << ZeroPwm_RT1_SHIFT)
    #define ZeroPwm_SYNC                  (uint8)((uint8)0x03u << ZeroPwm_RT1_SHIFT)
    #define ZeroPwm_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define ZeroPwm_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << ZeroPwm_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define ZeroPwm_SYNCDSI_EN            (uint8)((uint8)0x0Fu << ZeroPwm_SYNCDSI_SHIFT)


#else
    #define ZeroPwm_STATUS                (*(reg8 *)   ZeroPwm_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ZeroPwm_STATUS_PTR            ((reg8 *)    ZeroPwm_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define ZeroPwm_STATUS_MASK           (*(reg8 *)   ZeroPwm_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ZeroPwm_STATUS_MASK_PTR       ((reg8 *)    ZeroPwm_PWMUDB_genblk8_stsreg__MASK_REG)
    #define ZeroPwm_STATUS_AUX_CTRL       (*(reg8 *)   ZeroPwm_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define ZeroPwm_CONTROL               (*(reg8 *)   ZeroPwm_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define ZeroPwm_CONTROL_PTR           ((reg8 *)    ZeroPwm_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define ZeroPwm_CTRL_ENABLE_SHIFT      (0x07u)
    #define ZeroPwm_CTRL_RESET_SHIFT       (0x06u)
    #define ZeroPwm_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define ZeroPwm_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define ZeroPwm_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define ZeroPwm_CTRL_ENABLE            (uint8)((uint8)0x01u << ZeroPwm_CTRL_ENABLE_SHIFT)
    #define ZeroPwm_CTRL_RESET             (uint8)((uint8)0x01u << ZeroPwm_CTRL_RESET_SHIFT)
    #define ZeroPwm_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << ZeroPwm_CTRL_CMPMODE2_SHIFT)
    #define ZeroPwm_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << ZeroPwm_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define ZeroPwm_STATUS_KILL_SHIFT          (0x05u)
    #define ZeroPwm_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define ZeroPwm_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define ZeroPwm_STATUS_TC_SHIFT            (0x02u)
    #define ZeroPwm_STATUS_CMP2_SHIFT          (0x01u)
    #define ZeroPwm_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define ZeroPwm_STATUS_KILL_INT_EN_MASK_SHIFT          (ZeroPwm_STATUS_KILL_SHIFT)
    #define ZeroPwm_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (ZeroPwm_STATUS_FIFONEMPTY_SHIFT)
    #define ZeroPwm_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (ZeroPwm_STATUS_FIFOFULL_SHIFT)
    #define ZeroPwm_STATUS_TC_INT_EN_MASK_SHIFT            (ZeroPwm_STATUS_TC_SHIFT)
    #define ZeroPwm_STATUS_CMP2_INT_EN_MASK_SHIFT          (ZeroPwm_STATUS_CMP2_SHIFT)
    #define ZeroPwm_STATUS_CMP1_INT_EN_MASK_SHIFT          (ZeroPwm_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define ZeroPwm_STATUS_KILL            (uint8)((uint8)0x00u << ZeroPwm_STATUS_KILL_SHIFT )
    #define ZeroPwm_STATUS_FIFOFULL        (uint8)((uint8)0x01u << ZeroPwm_STATUS_FIFOFULL_SHIFT)
    #define ZeroPwm_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << ZeroPwm_STATUS_FIFONEMPTY_SHIFT)
    #define ZeroPwm_STATUS_TC              (uint8)((uint8)0x01u << ZeroPwm_STATUS_TC_SHIFT)
    #define ZeroPwm_STATUS_CMP2            (uint8)((uint8)0x01u << ZeroPwm_STATUS_CMP2_SHIFT)
    #define ZeroPwm_STATUS_CMP1            (uint8)((uint8)0x01u << ZeroPwm_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define ZeroPwm_STATUS_KILL_INT_EN_MASK            (ZeroPwm_STATUS_KILL)
    #define ZeroPwm_STATUS_FIFOFULL_INT_EN_MASK        (ZeroPwm_STATUS_FIFOFULL)
    #define ZeroPwm_STATUS_FIFONEMPTY_INT_EN_MASK      (ZeroPwm_STATUS_FIFONEMPTY)
    #define ZeroPwm_STATUS_TC_INT_EN_MASK              (ZeroPwm_STATUS_TC)
    #define ZeroPwm_STATUS_CMP2_INT_EN_MASK            (ZeroPwm_STATUS_CMP2)
    #define ZeroPwm_STATUS_CMP1_INT_EN_MASK            (ZeroPwm_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define ZeroPwm_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define ZeroPwm_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define ZeroPwm_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define ZeroPwm_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define ZeroPwm_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* ZeroPwm_UsingFixedFunction */

#endif  /* CY_PWM_ZeroPwm_H */


/* [] END OF FILE */
