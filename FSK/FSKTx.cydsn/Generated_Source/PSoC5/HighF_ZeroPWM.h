/*******************************************************************************
* File Name: HighF_ZeroPWM.h
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

#if !defined(CY_PWM_HighF_ZeroPWM_H)
#define CY_PWM_HighF_ZeroPWM_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 HighF_ZeroPWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define HighF_ZeroPWM_Resolution                     (16u)
#define HighF_ZeroPWM_UsingFixedFunction             (0u)
#define HighF_ZeroPWM_DeadBandMode                   (0u)
#define HighF_ZeroPWM_KillModeMinTime                (0u)
#define HighF_ZeroPWM_KillMode                       (0u)
#define HighF_ZeroPWM_PWMMode                        (0u)
#define HighF_ZeroPWM_PWMModeIsCenterAligned         (0u)
#define HighF_ZeroPWM_DeadBandUsed                   (0u)
#define HighF_ZeroPWM_DeadBand2_4                    (0u)

#if !defined(HighF_ZeroPWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define HighF_ZeroPWM_UseStatus                  (1u)
#else
    #define HighF_ZeroPWM_UseStatus                  (0u)
#endif /* !defined(HighF_ZeroPWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(HighF_ZeroPWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define HighF_ZeroPWM_UseControl                 (1u)
#else
    #define HighF_ZeroPWM_UseControl                 (0u)
#endif /* !defined(HighF_ZeroPWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define HighF_ZeroPWM_UseOneCompareMode              (1u)
#define HighF_ZeroPWM_MinimumKillTime                (1u)
#define HighF_ZeroPWM_EnableMode                     (0u)

#define HighF_ZeroPWM_CompareMode1SW                 (0u)
#define HighF_ZeroPWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define HighF_ZeroPWM__B_PWM__DISABLED 0
#define HighF_ZeroPWM__B_PWM__ASYNCHRONOUS 1
#define HighF_ZeroPWM__B_PWM__SINGLECYCLE 2
#define HighF_ZeroPWM__B_PWM__LATCHED 3
#define HighF_ZeroPWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define HighF_ZeroPWM__B_PWM__DBMDISABLED 0
#define HighF_ZeroPWM__B_PWM__DBM_2_4_CLOCKS 1
#define HighF_ZeroPWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define HighF_ZeroPWM__B_PWM__ONE_OUTPUT 0
#define HighF_ZeroPWM__B_PWM__TWO_OUTPUTS 1
#define HighF_ZeroPWM__B_PWM__DUAL_EDGE 2
#define HighF_ZeroPWM__B_PWM__CENTER_ALIGN 3
#define HighF_ZeroPWM__B_PWM__DITHER 5
#define HighF_ZeroPWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define HighF_ZeroPWM__B_PWM__LESS_THAN 1
#define HighF_ZeroPWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define HighF_ZeroPWM__B_PWM__GREATER_THAN 3
#define HighF_ZeroPWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define HighF_ZeroPWM__B_PWM__EQUAL 0
#define HighF_ZeroPWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!HighF_ZeroPWM_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!HighF_ZeroPWM_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!HighF_ZeroPWM_PWMModeIsCenterAligned) */
        #if (HighF_ZeroPWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (HighF_ZeroPWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(HighF_ZeroPWM_DeadBandMode == HighF_ZeroPWM__B_PWM__DBM_256_CLOCKS || \
            HighF_ZeroPWM_DeadBandMode == HighF_ZeroPWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(HighF_ZeroPWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (HighF_ZeroPWM_KillModeMinTime) */

        /* Backup control register */
        #if(HighF_ZeroPWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (HighF_ZeroPWM_UseControl) */

    #endif /* (!HighF_ZeroPWM_UsingFixedFunction) */

}HighF_ZeroPWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    HighF_ZeroPWM_Start(void) ;
void    HighF_ZeroPWM_Stop(void) ;

#if (HighF_ZeroPWM_UseStatus || HighF_ZeroPWM_UsingFixedFunction)
    void  HighF_ZeroPWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 HighF_ZeroPWM_ReadStatusRegister(void) ;
#endif /* (HighF_ZeroPWM_UseStatus || HighF_ZeroPWM_UsingFixedFunction) */

#define HighF_ZeroPWM_GetInterruptSource() HighF_ZeroPWM_ReadStatusRegister()

#if (HighF_ZeroPWM_UseControl)
    uint8 HighF_ZeroPWM_ReadControlRegister(void) ;
    void  HighF_ZeroPWM_WriteControlRegister(uint8 control)
          ;
#endif /* (HighF_ZeroPWM_UseControl) */

#if (HighF_ZeroPWM_UseOneCompareMode)
   #if (HighF_ZeroPWM_CompareMode1SW)
       void    HighF_ZeroPWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (HighF_ZeroPWM_CompareMode1SW) */
#else
    #if (HighF_ZeroPWM_CompareMode1SW)
        void    HighF_ZeroPWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (HighF_ZeroPWM_CompareMode1SW) */
    #if (HighF_ZeroPWM_CompareMode2SW)
        void    HighF_ZeroPWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (HighF_ZeroPWM_CompareMode2SW) */
#endif /* (HighF_ZeroPWM_UseOneCompareMode) */

#if (!HighF_ZeroPWM_UsingFixedFunction)
    uint16   HighF_ZeroPWM_ReadCounter(void) ;
    uint16 HighF_ZeroPWM_ReadCapture(void) ;

    #if (HighF_ZeroPWM_UseStatus)
            void HighF_ZeroPWM_ClearFIFO(void) ;
    #endif /* (HighF_ZeroPWM_UseStatus) */

    void    HighF_ZeroPWM_WriteCounter(uint16 counter)
            ;
#endif /* (!HighF_ZeroPWM_UsingFixedFunction) */

void    HighF_ZeroPWM_WritePeriod(uint16 period)
        ;
uint16 HighF_ZeroPWM_ReadPeriod(void) ;

#if (HighF_ZeroPWM_UseOneCompareMode)
    void    HighF_ZeroPWM_WriteCompare(uint16 compare)
            ;
    uint16 HighF_ZeroPWM_ReadCompare(void) ;
#else
    void    HighF_ZeroPWM_WriteCompare1(uint16 compare)
            ;
    uint16 HighF_ZeroPWM_ReadCompare1(void) ;
    void    HighF_ZeroPWM_WriteCompare2(uint16 compare)
            ;
    uint16 HighF_ZeroPWM_ReadCompare2(void) ;
#endif /* (HighF_ZeroPWM_UseOneCompareMode) */


#if (HighF_ZeroPWM_DeadBandUsed)
    void    HighF_ZeroPWM_WriteDeadTime(uint8 deadtime) ;
    uint8   HighF_ZeroPWM_ReadDeadTime(void) ;
#endif /* (HighF_ZeroPWM_DeadBandUsed) */

#if ( HighF_ZeroPWM_KillModeMinTime)
    void HighF_ZeroPWM_WriteKillTime(uint8 killtime) ;
    uint8 HighF_ZeroPWM_ReadKillTime(void) ;
#endif /* ( HighF_ZeroPWM_KillModeMinTime) */

void HighF_ZeroPWM_Init(void) ;
void HighF_ZeroPWM_Enable(void) ;
void HighF_ZeroPWM_Sleep(void) ;
void HighF_ZeroPWM_Wakeup(void) ;
void HighF_ZeroPWM_SaveConfig(void) ;
void HighF_ZeroPWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define HighF_ZeroPWM_INIT_PERIOD_VALUE          (255u)
#define HighF_ZeroPWM_INIT_COMPARE_VALUE1        (127u)
#define HighF_ZeroPWM_INIT_COMPARE_VALUE2        (63u)
#define HighF_ZeroPWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    HighF_ZeroPWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    HighF_ZeroPWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    HighF_ZeroPWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    HighF_ZeroPWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define HighF_ZeroPWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  HighF_ZeroPWM_CTRL_CMPMODE2_SHIFT)
#define HighF_ZeroPWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  HighF_ZeroPWM_CTRL_CMPMODE1_SHIFT)
#define HighF_ZeroPWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (HighF_ZeroPWM_UsingFixedFunction)
   #define HighF_ZeroPWM_PERIOD_LSB              (*(reg16 *) HighF_ZeroPWM_PWMHW__PER0)
   #define HighF_ZeroPWM_PERIOD_LSB_PTR          ( (reg16 *) HighF_ZeroPWM_PWMHW__PER0)
   #define HighF_ZeroPWM_COMPARE1_LSB            (*(reg16 *) HighF_ZeroPWM_PWMHW__CNT_CMP0)
   #define HighF_ZeroPWM_COMPARE1_LSB_PTR        ( (reg16 *) HighF_ZeroPWM_PWMHW__CNT_CMP0)
   #define HighF_ZeroPWM_COMPARE2_LSB            (0x00u)
   #define HighF_ZeroPWM_COMPARE2_LSB_PTR        (0x00u)
   #define HighF_ZeroPWM_COUNTER_LSB             (*(reg16 *) HighF_ZeroPWM_PWMHW__CNT_CMP0)
   #define HighF_ZeroPWM_COUNTER_LSB_PTR         ( (reg16 *) HighF_ZeroPWM_PWMHW__CNT_CMP0)
   #define HighF_ZeroPWM_CAPTURE_LSB             (*(reg16 *) HighF_ZeroPWM_PWMHW__CAP0)
   #define HighF_ZeroPWM_CAPTURE_LSB_PTR         ( (reg16 *) HighF_ZeroPWM_PWMHW__CAP0)
   #define HighF_ZeroPWM_RT1                     (*(reg8 *)  HighF_ZeroPWM_PWMHW__RT1)
   #define HighF_ZeroPWM_RT1_PTR                 ( (reg8 *)  HighF_ZeroPWM_PWMHW__RT1)

#else
   #if (HighF_ZeroPWM_Resolution == 8u) /* 8bit - PWM */

       #if(HighF_ZeroPWM_PWMModeIsCenterAligned)
           #define HighF_ZeroPWM_PERIOD_LSB      (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define HighF_ZeroPWM_PERIOD_LSB_PTR  ((reg8 *)   HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define HighF_ZeroPWM_PERIOD_LSB      (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define HighF_ZeroPWM_PERIOD_LSB_PTR  ((reg8 *)   HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (HighF_ZeroPWM_PWMModeIsCenterAligned) */

       #define HighF_ZeroPWM_COMPARE1_LSB        (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define HighF_ZeroPWM_COMPARE1_LSB_PTR    ((reg8 *)   HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define HighF_ZeroPWM_COMPARE2_LSB        (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define HighF_ZeroPWM_COMPARE2_LSB_PTR    ((reg8 *)   HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define HighF_ZeroPWM_COUNTERCAP_LSB      (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define HighF_ZeroPWM_COUNTERCAP_LSB_PTR  ((reg8 *)   HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define HighF_ZeroPWM_COUNTER_LSB         (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define HighF_ZeroPWM_COUNTER_LSB_PTR     ((reg8 *)   HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define HighF_ZeroPWM_CAPTURE_LSB         (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define HighF_ZeroPWM_CAPTURE_LSB_PTR     ((reg8 *)   HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(HighF_ZeroPWM_PWMModeIsCenterAligned)
               #define HighF_ZeroPWM_PERIOD_LSB      (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define HighF_ZeroPWM_PERIOD_LSB_PTR  ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define HighF_ZeroPWM_PERIOD_LSB      (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define HighF_ZeroPWM_PERIOD_LSB_PTR  ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (HighF_ZeroPWM_PWMModeIsCenterAligned) */

            #define HighF_ZeroPWM_COMPARE1_LSB       (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define HighF_ZeroPWM_COMPARE1_LSB_PTR   ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define HighF_ZeroPWM_COMPARE2_LSB       (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define HighF_ZeroPWM_COMPARE2_LSB_PTR   ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define HighF_ZeroPWM_COUNTERCAP_LSB     (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define HighF_ZeroPWM_COUNTERCAP_LSB_PTR ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define HighF_ZeroPWM_COUNTER_LSB        (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define HighF_ZeroPWM_COUNTER_LSB_PTR    ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define HighF_ZeroPWM_CAPTURE_LSB        (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define HighF_ZeroPWM_CAPTURE_LSB_PTR    ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(HighF_ZeroPWM_PWMModeIsCenterAligned)
               #define HighF_ZeroPWM_PERIOD_LSB      (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define HighF_ZeroPWM_PERIOD_LSB_PTR  ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define HighF_ZeroPWM_PERIOD_LSB      (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define HighF_ZeroPWM_PERIOD_LSB_PTR  ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (HighF_ZeroPWM_PWMModeIsCenterAligned) */

            #define HighF_ZeroPWM_COMPARE1_LSB       (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define HighF_ZeroPWM_COMPARE1_LSB_PTR   ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define HighF_ZeroPWM_COMPARE2_LSB       (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define HighF_ZeroPWM_COMPARE2_LSB_PTR   ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define HighF_ZeroPWM_COUNTERCAP_LSB     (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define HighF_ZeroPWM_COUNTERCAP_LSB_PTR ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define HighF_ZeroPWM_COUNTER_LSB        (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define HighF_ZeroPWM_COUNTER_LSB_PTR    ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define HighF_ZeroPWM_CAPTURE_LSB        (*(reg16 *) HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define HighF_ZeroPWM_CAPTURE_LSB_PTR    ((reg16 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define HighF_ZeroPWM_AUX_CONTROLDP1          (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define HighF_ZeroPWM_AUX_CONTROLDP1_PTR      ((reg8 *)   HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (HighF_ZeroPWM_Resolution == 8) */

   #define HighF_ZeroPWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define HighF_ZeroPWM_AUX_CONTROLDP0          (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define HighF_ZeroPWM_AUX_CONTROLDP0_PTR      ((reg8 *)   HighF_ZeroPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (HighF_ZeroPWM_UsingFixedFunction) */

#if(HighF_ZeroPWM_KillModeMinTime )
    #define HighF_ZeroPWM_KILLMODEMINTIME        (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define HighF_ZeroPWM_KILLMODEMINTIME_PTR    ((reg8 *)   HighF_ZeroPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (HighF_ZeroPWM_KillModeMinTime ) */

#if(HighF_ZeroPWM_DeadBandMode == HighF_ZeroPWM__B_PWM__DBM_256_CLOCKS)
    #define HighF_ZeroPWM_DEADBAND_COUNT         (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define HighF_ZeroPWM_DEADBAND_COUNT_PTR     ((reg8 *)   HighF_ZeroPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define HighF_ZeroPWM_DEADBAND_LSB_PTR       ((reg8 *)   HighF_ZeroPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define HighF_ZeroPWM_DEADBAND_LSB           (*(reg8 *)  HighF_ZeroPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(HighF_ZeroPWM_DeadBandMode == HighF_ZeroPWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (HighF_ZeroPWM_UsingFixedFunction)
        #define HighF_ZeroPWM_DEADBAND_COUNT         (*(reg8 *)  HighF_ZeroPWM_PWMHW__CFG0)
        #define HighF_ZeroPWM_DEADBAND_COUNT_PTR     ((reg8 *)   HighF_ZeroPWM_PWMHW__CFG0)
        #define HighF_ZeroPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << HighF_ZeroPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define HighF_ZeroPWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define HighF_ZeroPWM_DEADBAND_COUNT         (*(reg8 *)  HighF_ZeroPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define HighF_ZeroPWM_DEADBAND_COUNT_PTR     ((reg8 *)   HighF_ZeroPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define HighF_ZeroPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << HighF_ZeroPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define HighF_ZeroPWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (HighF_ZeroPWM_UsingFixedFunction) */
#endif /* (HighF_ZeroPWM_DeadBandMode == HighF_ZeroPWM__B_PWM__DBM_256_CLOCKS) */



#if (HighF_ZeroPWM_UsingFixedFunction)
    #define HighF_ZeroPWM_STATUS                 (*(reg8 *) HighF_ZeroPWM_PWMHW__SR0)
    #define HighF_ZeroPWM_STATUS_PTR             ((reg8 *) HighF_ZeroPWM_PWMHW__SR0)
    #define HighF_ZeroPWM_STATUS_MASK            (*(reg8 *) HighF_ZeroPWM_PWMHW__SR0)
    #define HighF_ZeroPWM_STATUS_MASK_PTR        ((reg8 *) HighF_ZeroPWM_PWMHW__SR0)
    #define HighF_ZeroPWM_CONTROL                (*(reg8 *) HighF_ZeroPWM_PWMHW__CFG0)
    #define HighF_ZeroPWM_CONTROL_PTR            ((reg8 *) HighF_ZeroPWM_PWMHW__CFG0)
    #define HighF_ZeroPWM_CONTROL2               (*(reg8 *) HighF_ZeroPWM_PWMHW__CFG1)
    #define HighF_ZeroPWM_CONTROL3               (*(reg8 *) HighF_ZeroPWM_PWMHW__CFG2)
    #define HighF_ZeroPWM_GLOBAL_ENABLE          (*(reg8 *) HighF_ZeroPWM_PWMHW__PM_ACT_CFG)
    #define HighF_ZeroPWM_GLOBAL_ENABLE_PTR      ( (reg8 *) HighF_ZeroPWM_PWMHW__PM_ACT_CFG)
    #define HighF_ZeroPWM_GLOBAL_STBY_ENABLE     (*(reg8 *) HighF_ZeroPWM_PWMHW__PM_STBY_CFG)
    #define HighF_ZeroPWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) HighF_ZeroPWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define HighF_ZeroPWM_BLOCK_EN_MASK          (HighF_ZeroPWM_PWMHW__PM_ACT_MSK)
    #define HighF_ZeroPWM_BLOCK_STBY_EN_MASK     (HighF_ZeroPWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define HighF_ZeroPWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define HighF_ZeroPWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define HighF_ZeroPWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define HighF_ZeroPWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define HighF_ZeroPWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define HighF_ZeroPWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define HighF_ZeroPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << HighF_ZeroPWM_CTRL_ENABLE_SHIFT)
    #define HighF_ZeroPWM_CTRL_RESET             (uint8)((uint8)0x01u << HighF_ZeroPWM_CTRL_RESET_SHIFT)
    #define HighF_ZeroPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << HighF_ZeroPWM_CTRL_CMPMODE2_SHIFT)
    #define HighF_ZeroPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << HighF_ZeroPWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define HighF_ZeroPWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define HighF_ZeroPWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << HighF_ZeroPWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define HighF_ZeroPWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define HighF_ZeroPWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define HighF_ZeroPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define HighF_ZeroPWM_STATUS_TC_INT_EN_MASK_SHIFT            (HighF_ZeroPWM_STATUS_TC_SHIFT - 4u)
    #define HighF_ZeroPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define HighF_ZeroPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (HighF_ZeroPWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define HighF_ZeroPWM_STATUS_TC              (uint8)((uint8)0x01u << HighF_ZeroPWM_STATUS_TC_SHIFT)
    #define HighF_ZeroPWM_STATUS_CMP1            (uint8)((uint8)0x01u << HighF_ZeroPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define HighF_ZeroPWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)HighF_ZeroPWM_STATUS_TC >> 4u)
    #define HighF_ZeroPWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)HighF_ZeroPWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define HighF_ZeroPWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define HighF_ZeroPWM_RT1_MASK              (uint8)((uint8)0x03u << HighF_ZeroPWM_RT1_SHIFT)
    #define HighF_ZeroPWM_SYNC                  (uint8)((uint8)0x03u << HighF_ZeroPWM_RT1_SHIFT)
    #define HighF_ZeroPWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define HighF_ZeroPWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << HighF_ZeroPWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define HighF_ZeroPWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << HighF_ZeroPWM_SYNCDSI_SHIFT)


#else
    #define HighF_ZeroPWM_STATUS                (*(reg8 *)   HighF_ZeroPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define HighF_ZeroPWM_STATUS_PTR            ((reg8 *)    HighF_ZeroPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define HighF_ZeroPWM_STATUS_MASK           (*(reg8 *)   HighF_ZeroPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define HighF_ZeroPWM_STATUS_MASK_PTR       ((reg8 *)    HighF_ZeroPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define HighF_ZeroPWM_STATUS_AUX_CTRL       (*(reg8 *)   HighF_ZeroPWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define HighF_ZeroPWM_CONTROL               (*(reg8 *)   HighF_ZeroPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define HighF_ZeroPWM_CONTROL_PTR           ((reg8 *)    HighF_ZeroPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define HighF_ZeroPWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define HighF_ZeroPWM_CTRL_RESET_SHIFT       (0x06u)
    #define HighF_ZeroPWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define HighF_ZeroPWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define HighF_ZeroPWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define HighF_ZeroPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << HighF_ZeroPWM_CTRL_ENABLE_SHIFT)
    #define HighF_ZeroPWM_CTRL_RESET             (uint8)((uint8)0x01u << HighF_ZeroPWM_CTRL_RESET_SHIFT)
    #define HighF_ZeroPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << HighF_ZeroPWM_CTRL_CMPMODE2_SHIFT)
    #define HighF_ZeroPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << HighF_ZeroPWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define HighF_ZeroPWM_STATUS_KILL_SHIFT          (0x05u)
    #define HighF_ZeroPWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define HighF_ZeroPWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define HighF_ZeroPWM_STATUS_TC_SHIFT            (0x02u)
    #define HighF_ZeroPWM_STATUS_CMP2_SHIFT          (0x01u)
    #define HighF_ZeroPWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define HighF_ZeroPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (HighF_ZeroPWM_STATUS_KILL_SHIFT)
    #define HighF_ZeroPWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (HighF_ZeroPWM_STATUS_FIFONEMPTY_SHIFT)
    #define HighF_ZeroPWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (HighF_ZeroPWM_STATUS_FIFOFULL_SHIFT)
    #define HighF_ZeroPWM_STATUS_TC_INT_EN_MASK_SHIFT            (HighF_ZeroPWM_STATUS_TC_SHIFT)
    #define HighF_ZeroPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (HighF_ZeroPWM_STATUS_CMP2_SHIFT)
    #define HighF_ZeroPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (HighF_ZeroPWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define HighF_ZeroPWM_STATUS_KILL            (uint8)((uint8)0x00u << HighF_ZeroPWM_STATUS_KILL_SHIFT )
    #define HighF_ZeroPWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << HighF_ZeroPWM_STATUS_FIFOFULL_SHIFT)
    #define HighF_ZeroPWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << HighF_ZeroPWM_STATUS_FIFONEMPTY_SHIFT)
    #define HighF_ZeroPWM_STATUS_TC              (uint8)((uint8)0x01u << HighF_ZeroPWM_STATUS_TC_SHIFT)
    #define HighF_ZeroPWM_STATUS_CMP2            (uint8)((uint8)0x01u << HighF_ZeroPWM_STATUS_CMP2_SHIFT)
    #define HighF_ZeroPWM_STATUS_CMP1            (uint8)((uint8)0x01u << HighF_ZeroPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define HighF_ZeroPWM_STATUS_KILL_INT_EN_MASK            (HighF_ZeroPWM_STATUS_KILL)
    #define HighF_ZeroPWM_STATUS_FIFOFULL_INT_EN_MASK        (HighF_ZeroPWM_STATUS_FIFOFULL)
    #define HighF_ZeroPWM_STATUS_FIFONEMPTY_INT_EN_MASK      (HighF_ZeroPWM_STATUS_FIFONEMPTY)
    #define HighF_ZeroPWM_STATUS_TC_INT_EN_MASK              (HighF_ZeroPWM_STATUS_TC)
    #define HighF_ZeroPWM_STATUS_CMP2_INT_EN_MASK            (HighF_ZeroPWM_STATUS_CMP2)
    #define HighF_ZeroPWM_STATUS_CMP1_INT_EN_MASK            (HighF_ZeroPWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define HighF_ZeroPWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define HighF_ZeroPWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define HighF_ZeroPWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define HighF_ZeroPWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define HighF_ZeroPWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* HighF_ZeroPWM_UsingFixedFunction */

#endif  /* CY_PWM_HighF_ZeroPWM_H */


/* [] END OF FILE */
