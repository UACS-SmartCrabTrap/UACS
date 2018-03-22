/*******************************************************************************
* File Name: HighF_OnePWM.h
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

#if !defined(CY_PWM_HighF_OnePWM_H)
#define CY_PWM_HighF_OnePWM_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 HighF_OnePWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define HighF_OnePWM_Resolution                     (16u)
#define HighF_OnePWM_UsingFixedFunction             (0u)
#define HighF_OnePWM_DeadBandMode                   (0u)
#define HighF_OnePWM_KillModeMinTime                (0u)
#define HighF_OnePWM_KillMode                       (0u)
#define HighF_OnePWM_PWMMode                        (0u)
#define HighF_OnePWM_PWMModeIsCenterAligned         (0u)
#define HighF_OnePWM_DeadBandUsed                   (0u)
#define HighF_OnePWM_DeadBand2_4                    (0u)

#if !defined(HighF_OnePWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define HighF_OnePWM_UseStatus                  (1u)
#else
    #define HighF_OnePWM_UseStatus                  (0u)
#endif /* !defined(HighF_OnePWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(HighF_OnePWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define HighF_OnePWM_UseControl                 (1u)
#else
    #define HighF_OnePWM_UseControl                 (0u)
#endif /* !defined(HighF_OnePWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define HighF_OnePWM_UseOneCompareMode              (1u)
#define HighF_OnePWM_MinimumKillTime                (1u)
#define HighF_OnePWM_EnableMode                     (0u)

#define HighF_OnePWM_CompareMode1SW                 (0u)
#define HighF_OnePWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define HighF_OnePWM__B_PWM__DISABLED 0
#define HighF_OnePWM__B_PWM__ASYNCHRONOUS 1
#define HighF_OnePWM__B_PWM__SINGLECYCLE 2
#define HighF_OnePWM__B_PWM__LATCHED 3
#define HighF_OnePWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define HighF_OnePWM__B_PWM__DBMDISABLED 0
#define HighF_OnePWM__B_PWM__DBM_2_4_CLOCKS 1
#define HighF_OnePWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define HighF_OnePWM__B_PWM__ONE_OUTPUT 0
#define HighF_OnePWM__B_PWM__TWO_OUTPUTS 1
#define HighF_OnePWM__B_PWM__DUAL_EDGE 2
#define HighF_OnePWM__B_PWM__CENTER_ALIGN 3
#define HighF_OnePWM__B_PWM__DITHER 5
#define HighF_OnePWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define HighF_OnePWM__B_PWM__LESS_THAN 1
#define HighF_OnePWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define HighF_OnePWM__B_PWM__GREATER_THAN 3
#define HighF_OnePWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define HighF_OnePWM__B_PWM__EQUAL 0
#define HighF_OnePWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!HighF_OnePWM_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!HighF_OnePWM_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!HighF_OnePWM_PWMModeIsCenterAligned) */
        #if (HighF_OnePWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (HighF_OnePWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(HighF_OnePWM_DeadBandMode == HighF_OnePWM__B_PWM__DBM_256_CLOCKS || \
            HighF_OnePWM_DeadBandMode == HighF_OnePWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(HighF_OnePWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (HighF_OnePWM_KillModeMinTime) */

        /* Backup control register */
        #if(HighF_OnePWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (HighF_OnePWM_UseControl) */

    #endif /* (!HighF_OnePWM_UsingFixedFunction) */

}HighF_OnePWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    HighF_OnePWM_Start(void) ;
void    HighF_OnePWM_Stop(void) ;

#if (HighF_OnePWM_UseStatus || HighF_OnePWM_UsingFixedFunction)
    void  HighF_OnePWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 HighF_OnePWM_ReadStatusRegister(void) ;
#endif /* (HighF_OnePWM_UseStatus || HighF_OnePWM_UsingFixedFunction) */

#define HighF_OnePWM_GetInterruptSource() HighF_OnePWM_ReadStatusRegister()

#if (HighF_OnePWM_UseControl)
    uint8 HighF_OnePWM_ReadControlRegister(void) ;
    void  HighF_OnePWM_WriteControlRegister(uint8 control)
          ;
#endif /* (HighF_OnePWM_UseControl) */

#if (HighF_OnePWM_UseOneCompareMode)
   #if (HighF_OnePWM_CompareMode1SW)
       void    HighF_OnePWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (HighF_OnePWM_CompareMode1SW) */
#else
    #if (HighF_OnePWM_CompareMode1SW)
        void    HighF_OnePWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (HighF_OnePWM_CompareMode1SW) */
    #if (HighF_OnePWM_CompareMode2SW)
        void    HighF_OnePWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (HighF_OnePWM_CompareMode2SW) */
#endif /* (HighF_OnePWM_UseOneCompareMode) */

#if (!HighF_OnePWM_UsingFixedFunction)
    uint16   HighF_OnePWM_ReadCounter(void) ;
    uint16 HighF_OnePWM_ReadCapture(void) ;

    #if (HighF_OnePWM_UseStatus)
            void HighF_OnePWM_ClearFIFO(void) ;
    #endif /* (HighF_OnePWM_UseStatus) */

    void    HighF_OnePWM_WriteCounter(uint16 counter)
            ;
#endif /* (!HighF_OnePWM_UsingFixedFunction) */

void    HighF_OnePWM_WritePeriod(uint16 period)
        ;
uint16 HighF_OnePWM_ReadPeriod(void) ;

#if (HighF_OnePWM_UseOneCompareMode)
    void    HighF_OnePWM_WriteCompare(uint16 compare)
            ;
    uint16 HighF_OnePWM_ReadCompare(void) ;
#else
    void    HighF_OnePWM_WriteCompare1(uint16 compare)
            ;
    uint16 HighF_OnePWM_ReadCompare1(void) ;
    void    HighF_OnePWM_WriteCompare2(uint16 compare)
            ;
    uint16 HighF_OnePWM_ReadCompare2(void) ;
#endif /* (HighF_OnePWM_UseOneCompareMode) */


#if (HighF_OnePWM_DeadBandUsed)
    void    HighF_OnePWM_WriteDeadTime(uint8 deadtime) ;
    uint8   HighF_OnePWM_ReadDeadTime(void) ;
#endif /* (HighF_OnePWM_DeadBandUsed) */

#if ( HighF_OnePWM_KillModeMinTime)
    void HighF_OnePWM_WriteKillTime(uint8 killtime) ;
    uint8 HighF_OnePWM_ReadKillTime(void) ;
#endif /* ( HighF_OnePWM_KillModeMinTime) */

void HighF_OnePWM_Init(void) ;
void HighF_OnePWM_Enable(void) ;
void HighF_OnePWM_Sleep(void) ;
void HighF_OnePWM_Wakeup(void) ;
void HighF_OnePWM_SaveConfig(void) ;
void HighF_OnePWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define HighF_OnePWM_INIT_PERIOD_VALUE          (255u)
#define HighF_OnePWM_INIT_COMPARE_VALUE1        (127u)
#define HighF_OnePWM_INIT_COMPARE_VALUE2        (63u)
#define HighF_OnePWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    HighF_OnePWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    HighF_OnePWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    HighF_OnePWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    HighF_OnePWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define HighF_OnePWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  HighF_OnePWM_CTRL_CMPMODE2_SHIFT)
#define HighF_OnePWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  HighF_OnePWM_CTRL_CMPMODE1_SHIFT)
#define HighF_OnePWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (HighF_OnePWM_UsingFixedFunction)
   #define HighF_OnePWM_PERIOD_LSB              (*(reg16 *) HighF_OnePWM_PWMHW__PER0)
   #define HighF_OnePWM_PERIOD_LSB_PTR          ( (reg16 *) HighF_OnePWM_PWMHW__PER0)
   #define HighF_OnePWM_COMPARE1_LSB            (*(reg16 *) HighF_OnePWM_PWMHW__CNT_CMP0)
   #define HighF_OnePWM_COMPARE1_LSB_PTR        ( (reg16 *) HighF_OnePWM_PWMHW__CNT_CMP0)
   #define HighF_OnePWM_COMPARE2_LSB            (0x00u)
   #define HighF_OnePWM_COMPARE2_LSB_PTR        (0x00u)
   #define HighF_OnePWM_COUNTER_LSB             (*(reg16 *) HighF_OnePWM_PWMHW__CNT_CMP0)
   #define HighF_OnePWM_COUNTER_LSB_PTR         ( (reg16 *) HighF_OnePWM_PWMHW__CNT_CMP0)
   #define HighF_OnePWM_CAPTURE_LSB             (*(reg16 *) HighF_OnePWM_PWMHW__CAP0)
   #define HighF_OnePWM_CAPTURE_LSB_PTR         ( (reg16 *) HighF_OnePWM_PWMHW__CAP0)
   #define HighF_OnePWM_RT1                     (*(reg8 *)  HighF_OnePWM_PWMHW__RT1)
   #define HighF_OnePWM_RT1_PTR                 ( (reg8 *)  HighF_OnePWM_PWMHW__RT1)

#else
   #if (HighF_OnePWM_Resolution == 8u) /* 8bit - PWM */

       #if(HighF_OnePWM_PWMModeIsCenterAligned)
           #define HighF_OnePWM_PERIOD_LSB      (*(reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define HighF_OnePWM_PERIOD_LSB_PTR  ((reg8 *)   HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define HighF_OnePWM_PERIOD_LSB      (*(reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define HighF_OnePWM_PERIOD_LSB_PTR  ((reg8 *)   HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (HighF_OnePWM_PWMModeIsCenterAligned) */

       #define HighF_OnePWM_COMPARE1_LSB        (*(reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define HighF_OnePWM_COMPARE1_LSB_PTR    ((reg8 *)   HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define HighF_OnePWM_COMPARE2_LSB        (*(reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define HighF_OnePWM_COMPARE2_LSB_PTR    ((reg8 *)   HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define HighF_OnePWM_COUNTERCAP_LSB      (*(reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define HighF_OnePWM_COUNTERCAP_LSB_PTR  ((reg8 *)   HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define HighF_OnePWM_COUNTER_LSB         (*(reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define HighF_OnePWM_COUNTER_LSB_PTR     ((reg8 *)   HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define HighF_OnePWM_CAPTURE_LSB         (*(reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define HighF_OnePWM_CAPTURE_LSB_PTR     ((reg8 *)   HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(HighF_OnePWM_PWMModeIsCenterAligned)
               #define HighF_OnePWM_PERIOD_LSB      (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define HighF_OnePWM_PERIOD_LSB_PTR  ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define HighF_OnePWM_PERIOD_LSB      (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define HighF_OnePWM_PERIOD_LSB_PTR  ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (HighF_OnePWM_PWMModeIsCenterAligned) */

            #define HighF_OnePWM_COMPARE1_LSB       (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define HighF_OnePWM_COMPARE1_LSB_PTR   ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define HighF_OnePWM_COMPARE2_LSB       (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define HighF_OnePWM_COMPARE2_LSB_PTR   ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define HighF_OnePWM_COUNTERCAP_LSB     (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define HighF_OnePWM_COUNTERCAP_LSB_PTR ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define HighF_OnePWM_COUNTER_LSB        (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define HighF_OnePWM_COUNTER_LSB_PTR    ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define HighF_OnePWM_CAPTURE_LSB        (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define HighF_OnePWM_CAPTURE_LSB_PTR    ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(HighF_OnePWM_PWMModeIsCenterAligned)
               #define HighF_OnePWM_PERIOD_LSB      (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define HighF_OnePWM_PERIOD_LSB_PTR  ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define HighF_OnePWM_PERIOD_LSB      (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define HighF_OnePWM_PERIOD_LSB_PTR  ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (HighF_OnePWM_PWMModeIsCenterAligned) */

            #define HighF_OnePWM_COMPARE1_LSB       (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define HighF_OnePWM_COMPARE1_LSB_PTR   ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define HighF_OnePWM_COMPARE2_LSB       (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define HighF_OnePWM_COMPARE2_LSB_PTR   ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define HighF_OnePWM_COUNTERCAP_LSB     (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define HighF_OnePWM_COUNTERCAP_LSB_PTR ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define HighF_OnePWM_COUNTER_LSB        (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define HighF_OnePWM_COUNTER_LSB_PTR    ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define HighF_OnePWM_CAPTURE_LSB        (*(reg16 *) HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define HighF_OnePWM_CAPTURE_LSB_PTR    ((reg16 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define HighF_OnePWM_AUX_CONTROLDP1          (*(reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define HighF_OnePWM_AUX_CONTROLDP1_PTR      ((reg8 *)   HighF_OnePWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (HighF_OnePWM_Resolution == 8) */

   #define HighF_OnePWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define HighF_OnePWM_AUX_CONTROLDP0          (*(reg8 *)  HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define HighF_OnePWM_AUX_CONTROLDP0_PTR      ((reg8 *)   HighF_OnePWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (HighF_OnePWM_UsingFixedFunction) */

#if(HighF_OnePWM_KillModeMinTime )
    #define HighF_OnePWM_KILLMODEMINTIME        (*(reg8 *)  HighF_OnePWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define HighF_OnePWM_KILLMODEMINTIME_PTR    ((reg8 *)   HighF_OnePWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (HighF_OnePWM_KillModeMinTime ) */

#if(HighF_OnePWM_DeadBandMode == HighF_OnePWM__B_PWM__DBM_256_CLOCKS)
    #define HighF_OnePWM_DEADBAND_COUNT         (*(reg8 *)  HighF_OnePWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define HighF_OnePWM_DEADBAND_COUNT_PTR     ((reg8 *)   HighF_OnePWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define HighF_OnePWM_DEADBAND_LSB_PTR       ((reg8 *)   HighF_OnePWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define HighF_OnePWM_DEADBAND_LSB           (*(reg8 *)  HighF_OnePWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(HighF_OnePWM_DeadBandMode == HighF_OnePWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (HighF_OnePWM_UsingFixedFunction)
        #define HighF_OnePWM_DEADBAND_COUNT         (*(reg8 *)  HighF_OnePWM_PWMHW__CFG0)
        #define HighF_OnePWM_DEADBAND_COUNT_PTR     ((reg8 *)   HighF_OnePWM_PWMHW__CFG0)
        #define HighF_OnePWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << HighF_OnePWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define HighF_OnePWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define HighF_OnePWM_DEADBAND_COUNT         (*(reg8 *)  HighF_OnePWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define HighF_OnePWM_DEADBAND_COUNT_PTR     ((reg8 *)   HighF_OnePWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define HighF_OnePWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << HighF_OnePWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define HighF_OnePWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (HighF_OnePWM_UsingFixedFunction) */
#endif /* (HighF_OnePWM_DeadBandMode == HighF_OnePWM__B_PWM__DBM_256_CLOCKS) */



#if (HighF_OnePWM_UsingFixedFunction)
    #define HighF_OnePWM_STATUS                 (*(reg8 *) HighF_OnePWM_PWMHW__SR0)
    #define HighF_OnePWM_STATUS_PTR             ((reg8 *) HighF_OnePWM_PWMHW__SR0)
    #define HighF_OnePWM_STATUS_MASK            (*(reg8 *) HighF_OnePWM_PWMHW__SR0)
    #define HighF_OnePWM_STATUS_MASK_PTR        ((reg8 *) HighF_OnePWM_PWMHW__SR0)
    #define HighF_OnePWM_CONTROL                (*(reg8 *) HighF_OnePWM_PWMHW__CFG0)
    #define HighF_OnePWM_CONTROL_PTR            ((reg8 *) HighF_OnePWM_PWMHW__CFG0)
    #define HighF_OnePWM_CONTROL2               (*(reg8 *) HighF_OnePWM_PWMHW__CFG1)
    #define HighF_OnePWM_CONTROL3               (*(reg8 *) HighF_OnePWM_PWMHW__CFG2)
    #define HighF_OnePWM_GLOBAL_ENABLE          (*(reg8 *) HighF_OnePWM_PWMHW__PM_ACT_CFG)
    #define HighF_OnePWM_GLOBAL_ENABLE_PTR      ( (reg8 *) HighF_OnePWM_PWMHW__PM_ACT_CFG)
    #define HighF_OnePWM_GLOBAL_STBY_ENABLE     (*(reg8 *) HighF_OnePWM_PWMHW__PM_STBY_CFG)
    #define HighF_OnePWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) HighF_OnePWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define HighF_OnePWM_BLOCK_EN_MASK          (HighF_OnePWM_PWMHW__PM_ACT_MSK)
    #define HighF_OnePWM_BLOCK_STBY_EN_MASK     (HighF_OnePWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define HighF_OnePWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define HighF_OnePWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define HighF_OnePWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define HighF_OnePWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define HighF_OnePWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define HighF_OnePWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define HighF_OnePWM_CTRL_ENABLE            (uint8)((uint8)0x01u << HighF_OnePWM_CTRL_ENABLE_SHIFT)
    #define HighF_OnePWM_CTRL_RESET             (uint8)((uint8)0x01u << HighF_OnePWM_CTRL_RESET_SHIFT)
    #define HighF_OnePWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << HighF_OnePWM_CTRL_CMPMODE2_SHIFT)
    #define HighF_OnePWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << HighF_OnePWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define HighF_OnePWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define HighF_OnePWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << HighF_OnePWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define HighF_OnePWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define HighF_OnePWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define HighF_OnePWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define HighF_OnePWM_STATUS_TC_INT_EN_MASK_SHIFT            (HighF_OnePWM_STATUS_TC_SHIFT - 4u)
    #define HighF_OnePWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define HighF_OnePWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (HighF_OnePWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define HighF_OnePWM_STATUS_TC              (uint8)((uint8)0x01u << HighF_OnePWM_STATUS_TC_SHIFT)
    #define HighF_OnePWM_STATUS_CMP1            (uint8)((uint8)0x01u << HighF_OnePWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define HighF_OnePWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)HighF_OnePWM_STATUS_TC >> 4u)
    #define HighF_OnePWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)HighF_OnePWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define HighF_OnePWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define HighF_OnePWM_RT1_MASK              (uint8)((uint8)0x03u << HighF_OnePWM_RT1_SHIFT)
    #define HighF_OnePWM_SYNC                  (uint8)((uint8)0x03u << HighF_OnePWM_RT1_SHIFT)
    #define HighF_OnePWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define HighF_OnePWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << HighF_OnePWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define HighF_OnePWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << HighF_OnePWM_SYNCDSI_SHIFT)


#else
    #define HighF_OnePWM_STATUS                (*(reg8 *)   HighF_OnePWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define HighF_OnePWM_STATUS_PTR            ((reg8 *)    HighF_OnePWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define HighF_OnePWM_STATUS_MASK           (*(reg8 *)   HighF_OnePWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define HighF_OnePWM_STATUS_MASK_PTR       ((reg8 *)    HighF_OnePWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define HighF_OnePWM_STATUS_AUX_CTRL       (*(reg8 *)   HighF_OnePWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define HighF_OnePWM_CONTROL               (*(reg8 *)   HighF_OnePWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define HighF_OnePWM_CONTROL_PTR           ((reg8 *)    HighF_OnePWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define HighF_OnePWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define HighF_OnePWM_CTRL_RESET_SHIFT       (0x06u)
    #define HighF_OnePWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define HighF_OnePWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define HighF_OnePWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define HighF_OnePWM_CTRL_ENABLE            (uint8)((uint8)0x01u << HighF_OnePWM_CTRL_ENABLE_SHIFT)
    #define HighF_OnePWM_CTRL_RESET             (uint8)((uint8)0x01u << HighF_OnePWM_CTRL_RESET_SHIFT)
    #define HighF_OnePWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << HighF_OnePWM_CTRL_CMPMODE2_SHIFT)
    #define HighF_OnePWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << HighF_OnePWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define HighF_OnePWM_STATUS_KILL_SHIFT          (0x05u)
    #define HighF_OnePWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define HighF_OnePWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define HighF_OnePWM_STATUS_TC_SHIFT            (0x02u)
    #define HighF_OnePWM_STATUS_CMP2_SHIFT          (0x01u)
    #define HighF_OnePWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define HighF_OnePWM_STATUS_KILL_INT_EN_MASK_SHIFT          (HighF_OnePWM_STATUS_KILL_SHIFT)
    #define HighF_OnePWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (HighF_OnePWM_STATUS_FIFONEMPTY_SHIFT)
    #define HighF_OnePWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (HighF_OnePWM_STATUS_FIFOFULL_SHIFT)
    #define HighF_OnePWM_STATUS_TC_INT_EN_MASK_SHIFT            (HighF_OnePWM_STATUS_TC_SHIFT)
    #define HighF_OnePWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (HighF_OnePWM_STATUS_CMP2_SHIFT)
    #define HighF_OnePWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (HighF_OnePWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define HighF_OnePWM_STATUS_KILL            (uint8)((uint8)0x00u << HighF_OnePWM_STATUS_KILL_SHIFT )
    #define HighF_OnePWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << HighF_OnePWM_STATUS_FIFOFULL_SHIFT)
    #define HighF_OnePWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << HighF_OnePWM_STATUS_FIFONEMPTY_SHIFT)
    #define HighF_OnePWM_STATUS_TC              (uint8)((uint8)0x01u << HighF_OnePWM_STATUS_TC_SHIFT)
    #define HighF_OnePWM_STATUS_CMP2            (uint8)((uint8)0x01u << HighF_OnePWM_STATUS_CMP2_SHIFT)
    #define HighF_OnePWM_STATUS_CMP1            (uint8)((uint8)0x01u << HighF_OnePWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define HighF_OnePWM_STATUS_KILL_INT_EN_MASK            (HighF_OnePWM_STATUS_KILL)
    #define HighF_OnePWM_STATUS_FIFOFULL_INT_EN_MASK        (HighF_OnePWM_STATUS_FIFOFULL)
    #define HighF_OnePWM_STATUS_FIFONEMPTY_INT_EN_MASK      (HighF_OnePWM_STATUS_FIFONEMPTY)
    #define HighF_OnePWM_STATUS_TC_INT_EN_MASK              (HighF_OnePWM_STATUS_TC)
    #define HighF_OnePWM_STATUS_CMP2_INT_EN_MASK            (HighF_OnePWM_STATUS_CMP2)
    #define HighF_OnePWM_STATUS_CMP1_INT_EN_MASK            (HighF_OnePWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define HighF_OnePWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define HighF_OnePWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define HighF_OnePWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define HighF_OnePWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define HighF_OnePWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* HighF_OnePWM_UsingFixedFunction */

#endif  /* CY_PWM_HighF_OnePWM_H */


/* [] END OF FILE */
