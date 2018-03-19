/*******************************************************************************
* File Name: LowF_OnePWM.h
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

#if !defined(CY_PWM_LowF_OnePWM_H)
#define CY_PWM_LowF_OnePWM_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 LowF_OnePWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define LowF_OnePWM_Resolution                     (16u)
#define LowF_OnePWM_UsingFixedFunction             (0u)
#define LowF_OnePWM_DeadBandMode                   (0u)
#define LowF_OnePWM_KillModeMinTime                (0u)
#define LowF_OnePWM_KillMode                       (0u)
#define LowF_OnePWM_PWMMode                        (0u)
#define LowF_OnePWM_PWMModeIsCenterAligned         (0u)
#define LowF_OnePWM_DeadBandUsed                   (0u)
#define LowF_OnePWM_DeadBand2_4                    (0u)

#if !defined(LowF_OnePWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define LowF_OnePWM_UseStatus                  (1u)
#else
    #define LowF_OnePWM_UseStatus                  (0u)
#endif /* !defined(LowF_OnePWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(LowF_OnePWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define LowF_OnePWM_UseControl                 (1u)
#else
    #define LowF_OnePWM_UseControl                 (0u)
#endif /* !defined(LowF_OnePWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define LowF_OnePWM_UseOneCompareMode              (1u)
#define LowF_OnePWM_MinimumKillTime                (1u)
#define LowF_OnePWM_EnableMode                     (0u)

#define LowF_OnePWM_CompareMode1SW                 (0u)
#define LowF_OnePWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define LowF_OnePWM__B_PWM__DISABLED 0
#define LowF_OnePWM__B_PWM__ASYNCHRONOUS 1
#define LowF_OnePWM__B_PWM__SINGLECYCLE 2
#define LowF_OnePWM__B_PWM__LATCHED 3
#define LowF_OnePWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define LowF_OnePWM__B_PWM__DBMDISABLED 0
#define LowF_OnePWM__B_PWM__DBM_2_4_CLOCKS 1
#define LowF_OnePWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define LowF_OnePWM__B_PWM__ONE_OUTPUT 0
#define LowF_OnePWM__B_PWM__TWO_OUTPUTS 1
#define LowF_OnePWM__B_PWM__DUAL_EDGE 2
#define LowF_OnePWM__B_PWM__CENTER_ALIGN 3
#define LowF_OnePWM__B_PWM__DITHER 5
#define LowF_OnePWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define LowF_OnePWM__B_PWM__LESS_THAN 1
#define LowF_OnePWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define LowF_OnePWM__B_PWM__GREATER_THAN 3
#define LowF_OnePWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define LowF_OnePWM__B_PWM__EQUAL 0
#define LowF_OnePWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!LowF_OnePWM_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!LowF_OnePWM_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!LowF_OnePWM_PWMModeIsCenterAligned) */
        #if (LowF_OnePWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (LowF_OnePWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(LowF_OnePWM_DeadBandMode == LowF_OnePWM__B_PWM__DBM_256_CLOCKS || \
            LowF_OnePWM_DeadBandMode == LowF_OnePWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(LowF_OnePWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (LowF_OnePWM_KillModeMinTime) */

        /* Backup control register */
        #if(LowF_OnePWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (LowF_OnePWM_UseControl) */

    #endif /* (!LowF_OnePWM_UsingFixedFunction) */

}LowF_OnePWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    LowF_OnePWM_Start(void) ;
void    LowF_OnePWM_Stop(void) ;

#if (LowF_OnePWM_UseStatus || LowF_OnePWM_UsingFixedFunction)
    void  LowF_OnePWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 LowF_OnePWM_ReadStatusRegister(void) ;
#endif /* (LowF_OnePWM_UseStatus || LowF_OnePWM_UsingFixedFunction) */

#define LowF_OnePWM_GetInterruptSource() LowF_OnePWM_ReadStatusRegister()

#if (LowF_OnePWM_UseControl)
    uint8 LowF_OnePWM_ReadControlRegister(void) ;
    void  LowF_OnePWM_WriteControlRegister(uint8 control)
          ;
#endif /* (LowF_OnePWM_UseControl) */

#if (LowF_OnePWM_UseOneCompareMode)
   #if (LowF_OnePWM_CompareMode1SW)
       void    LowF_OnePWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (LowF_OnePWM_CompareMode1SW) */
#else
    #if (LowF_OnePWM_CompareMode1SW)
        void    LowF_OnePWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (LowF_OnePWM_CompareMode1SW) */
    #if (LowF_OnePWM_CompareMode2SW)
        void    LowF_OnePWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (LowF_OnePWM_CompareMode2SW) */
#endif /* (LowF_OnePWM_UseOneCompareMode) */

#if (!LowF_OnePWM_UsingFixedFunction)
    uint16   LowF_OnePWM_ReadCounter(void) ;
    uint16 LowF_OnePWM_ReadCapture(void) ;

    #if (LowF_OnePWM_UseStatus)
            void LowF_OnePWM_ClearFIFO(void) ;
    #endif /* (LowF_OnePWM_UseStatus) */

    void    LowF_OnePWM_WriteCounter(uint16 counter)
            ;
#endif /* (!LowF_OnePWM_UsingFixedFunction) */

void    LowF_OnePWM_WritePeriod(uint16 period)
        ;
uint16 LowF_OnePWM_ReadPeriod(void) ;

#if (LowF_OnePWM_UseOneCompareMode)
    void    LowF_OnePWM_WriteCompare(uint16 compare)
            ;
    uint16 LowF_OnePWM_ReadCompare(void) ;
#else
    void    LowF_OnePWM_WriteCompare1(uint16 compare)
            ;
    uint16 LowF_OnePWM_ReadCompare1(void) ;
    void    LowF_OnePWM_WriteCompare2(uint16 compare)
            ;
    uint16 LowF_OnePWM_ReadCompare2(void) ;
#endif /* (LowF_OnePWM_UseOneCompareMode) */


#if (LowF_OnePWM_DeadBandUsed)
    void    LowF_OnePWM_WriteDeadTime(uint8 deadtime) ;
    uint8   LowF_OnePWM_ReadDeadTime(void) ;
#endif /* (LowF_OnePWM_DeadBandUsed) */

#if ( LowF_OnePWM_KillModeMinTime)
    void LowF_OnePWM_WriteKillTime(uint8 killtime) ;
    uint8 LowF_OnePWM_ReadKillTime(void) ;
#endif /* ( LowF_OnePWM_KillModeMinTime) */

void LowF_OnePWM_Init(void) ;
void LowF_OnePWM_Enable(void) ;
void LowF_OnePWM_Sleep(void) ;
void LowF_OnePWM_Wakeup(void) ;
void LowF_OnePWM_SaveConfig(void) ;
void LowF_OnePWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define LowF_OnePWM_INIT_PERIOD_VALUE          (255u)
#define LowF_OnePWM_INIT_COMPARE_VALUE1        (127u)
#define LowF_OnePWM_INIT_COMPARE_VALUE2        (63u)
#define LowF_OnePWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    LowF_OnePWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    LowF_OnePWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    LowF_OnePWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    LowF_OnePWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define LowF_OnePWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  LowF_OnePWM_CTRL_CMPMODE2_SHIFT)
#define LowF_OnePWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  LowF_OnePWM_CTRL_CMPMODE1_SHIFT)
#define LowF_OnePWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (LowF_OnePWM_UsingFixedFunction)
   #define LowF_OnePWM_PERIOD_LSB              (*(reg16 *) LowF_OnePWM_PWMHW__PER0)
   #define LowF_OnePWM_PERIOD_LSB_PTR          ( (reg16 *) LowF_OnePWM_PWMHW__PER0)
   #define LowF_OnePWM_COMPARE1_LSB            (*(reg16 *) LowF_OnePWM_PWMHW__CNT_CMP0)
   #define LowF_OnePWM_COMPARE1_LSB_PTR        ( (reg16 *) LowF_OnePWM_PWMHW__CNT_CMP0)
   #define LowF_OnePWM_COMPARE2_LSB            (0x00u)
   #define LowF_OnePWM_COMPARE2_LSB_PTR        (0x00u)
   #define LowF_OnePWM_COUNTER_LSB             (*(reg16 *) LowF_OnePWM_PWMHW__CNT_CMP0)
   #define LowF_OnePWM_COUNTER_LSB_PTR         ( (reg16 *) LowF_OnePWM_PWMHW__CNT_CMP0)
   #define LowF_OnePWM_CAPTURE_LSB             (*(reg16 *) LowF_OnePWM_PWMHW__CAP0)
   #define LowF_OnePWM_CAPTURE_LSB_PTR         ( (reg16 *) LowF_OnePWM_PWMHW__CAP0)
   #define LowF_OnePWM_RT1                     (*(reg8 *)  LowF_OnePWM_PWMHW__RT1)
   #define LowF_OnePWM_RT1_PTR                 ( (reg8 *)  LowF_OnePWM_PWMHW__RT1)

#else
   #if (LowF_OnePWM_Resolution == 8u) /* 8bit - PWM */

       #if(LowF_OnePWM_PWMModeIsCenterAligned)
           #define LowF_OnePWM_PERIOD_LSB      (*(reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define LowF_OnePWM_PERIOD_LSB_PTR  ((reg8 *)   LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define LowF_OnePWM_PERIOD_LSB      (*(reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define LowF_OnePWM_PERIOD_LSB_PTR  ((reg8 *)   LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (LowF_OnePWM_PWMModeIsCenterAligned) */

       #define LowF_OnePWM_COMPARE1_LSB        (*(reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define LowF_OnePWM_COMPARE1_LSB_PTR    ((reg8 *)   LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define LowF_OnePWM_COMPARE2_LSB        (*(reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define LowF_OnePWM_COMPARE2_LSB_PTR    ((reg8 *)   LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define LowF_OnePWM_COUNTERCAP_LSB      (*(reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define LowF_OnePWM_COUNTERCAP_LSB_PTR  ((reg8 *)   LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define LowF_OnePWM_COUNTER_LSB         (*(reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define LowF_OnePWM_COUNTER_LSB_PTR     ((reg8 *)   LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define LowF_OnePWM_CAPTURE_LSB         (*(reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define LowF_OnePWM_CAPTURE_LSB_PTR     ((reg8 *)   LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(LowF_OnePWM_PWMModeIsCenterAligned)
               #define LowF_OnePWM_PERIOD_LSB      (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define LowF_OnePWM_PERIOD_LSB_PTR  ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define LowF_OnePWM_PERIOD_LSB      (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define LowF_OnePWM_PERIOD_LSB_PTR  ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (LowF_OnePWM_PWMModeIsCenterAligned) */

            #define LowF_OnePWM_COMPARE1_LSB       (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define LowF_OnePWM_COMPARE1_LSB_PTR   ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define LowF_OnePWM_COMPARE2_LSB       (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define LowF_OnePWM_COMPARE2_LSB_PTR   ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define LowF_OnePWM_COUNTERCAP_LSB     (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define LowF_OnePWM_COUNTERCAP_LSB_PTR ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define LowF_OnePWM_COUNTER_LSB        (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define LowF_OnePWM_COUNTER_LSB_PTR    ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define LowF_OnePWM_CAPTURE_LSB        (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define LowF_OnePWM_CAPTURE_LSB_PTR    ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(LowF_OnePWM_PWMModeIsCenterAligned)
               #define LowF_OnePWM_PERIOD_LSB      (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define LowF_OnePWM_PERIOD_LSB_PTR  ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define LowF_OnePWM_PERIOD_LSB      (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define LowF_OnePWM_PERIOD_LSB_PTR  ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (LowF_OnePWM_PWMModeIsCenterAligned) */

            #define LowF_OnePWM_COMPARE1_LSB       (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define LowF_OnePWM_COMPARE1_LSB_PTR   ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define LowF_OnePWM_COMPARE2_LSB       (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define LowF_OnePWM_COMPARE2_LSB_PTR   ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define LowF_OnePWM_COUNTERCAP_LSB     (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define LowF_OnePWM_COUNTERCAP_LSB_PTR ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define LowF_OnePWM_COUNTER_LSB        (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define LowF_OnePWM_COUNTER_LSB_PTR    ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define LowF_OnePWM_CAPTURE_LSB        (*(reg16 *) LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define LowF_OnePWM_CAPTURE_LSB_PTR    ((reg16 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define LowF_OnePWM_AUX_CONTROLDP1          (*(reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define LowF_OnePWM_AUX_CONTROLDP1_PTR      ((reg8 *)   LowF_OnePWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (LowF_OnePWM_Resolution == 8) */

   #define LowF_OnePWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define LowF_OnePWM_AUX_CONTROLDP0          (*(reg8 *)  LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define LowF_OnePWM_AUX_CONTROLDP0_PTR      ((reg8 *)   LowF_OnePWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (LowF_OnePWM_UsingFixedFunction) */

#if(LowF_OnePWM_KillModeMinTime )
    #define LowF_OnePWM_KILLMODEMINTIME        (*(reg8 *)  LowF_OnePWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define LowF_OnePWM_KILLMODEMINTIME_PTR    ((reg8 *)   LowF_OnePWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (LowF_OnePWM_KillModeMinTime ) */

#if(LowF_OnePWM_DeadBandMode == LowF_OnePWM__B_PWM__DBM_256_CLOCKS)
    #define LowF_OnePWM_DEADBAND_COUNT         (*(reg8 *)  LowF_OnePWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LowF_OnePWM_DEADBAND_COUNT_PTR     ((reg8 *)   LowF_OnePWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LowF_OnePWM_DEADBAND_LSB_PTR       ((reg8 *)   LowF_OnePWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define LowF_OnePWM_DEADBAND_LSB           (*(reg8 *)  LowF_OnePWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(LowF_OnePWM_DeadBandMode == LowF_OnePWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (LowF_OnePWM_UsingFixedFunction)
        #define LowF_OnePWM_DEADBAND_COUNT         (*(reg8 *)  LowF_OnePWM_PWMHW__CFG0)
        #define LowF_OnePWM_DEADBAND_COUNT_PTR     ((reg8 *)   LowF_OnePWM_PWMHW__CFG0)
        #define LowF_OnePWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << LowF_OnePWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define LowF_OnePWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define LowF_OnePWM_DEADBAND_COUNT         (*(reg8 *)  LowF_OnePWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define LowF_OnePWM_DEADBAND_COUNT_PTR     ((reg8 *)   LowF_OnePWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define LowF_OnePWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << LowF_OnePWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define LowF_OnePWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (LowF_OnePWM_UsingFixedFunction) */
#endif /* (LowF_OnePWM_DeadBandMode == LowF_OnePWM__B_PWM__DBM_256_CLOCKS) */



#if (LowF_OnePWM_UsingFixedFunction)
    #define LowF_OnePWM_STATUS                 (*(reg8 *) LowF_OnePWM_PWMHW__SR0)
    #define LowF_OnePWM_STATUS_PTR             ((reg8 *) LowF_OnePWM_PWMHW__SR0)
    #define LowF_OnePWM_STATUS_MASK            (*(reg8 *) LowF_OnePWM_PWMHW__SR0)
    #define LowF_OnePWM_STATUS_MASK_PTR        ((reg8 *) LowF_OnePWM_PWMHW__SR0)
    #define LowF_OnePWM_CONTROL                (*(reg8 *) LowF_OnePWM_PWMHW__CFG0)
    #define LowF_OnePWM_CONTROL_PTR            ((reg8 *) LowF_OnePWM_PWMHW__CFG0)
    #define LowF_OnePWM_CONTROL2               (*(reg8 *) LowF_OnePWM_PWMHW__CFG1)
    #define LowF_OnePWM_CONTROL3               (*(reg8 *) LowF_OnePWM_PWMHW__CFG2)
    #define LowF_OnePWM_GLOBAL_ENABLE          (*(reg8 *) LowF_OnePWM_PWMHW__PM_ACT_CFG)
    #define LowF_OnePWM_GLOBAL_ENABLE_PTR      ( (reg8 *) LowF_OnePWM_PWMHW__PM_ACT_CFG)
    #define LowF_OnePWM_GLOBAL_STBY_ENABLE     (*(reg8 *) LowF_OnePWM_PWMHW__PM_STBY_CFG)
    #define LowF_OnePWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) LowF_OnePWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define LowF_OnePWM_BLOCK_EN_MASK          (LowF_OnePWM_PWMHW__PM_ACT_MSK)
    #define LowF_OnePWM_BLOCK_STBY_EN_MASK     (LowF_OnePWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define LowF_OnePWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define LowF_OnePWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define LowF_OnePWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define LowF_OnePWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define LowF_OnePWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define LowF_OnePWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define LowF_OnePWM_CTRL_ENABLE            (uint8)((uint8)0x01u << LowF_OnePWM_CTRL_ENABLE_SHIFT)
    #define LowF_OnePWM_CTRL_RESET             (uint8)((uint8)0x01u << LowF_OnePWM_CTRL_RESET_SHIFT)
    #define LowF_OnePWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << LowF_OnePWM_CTRL_CMPMODE2_SHIFT)
    #define LowF_OnePWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << LowF_OnePWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define LowF_OnePWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define LowF_OnePWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << LowF_OnePWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define LowF_OnePWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define LowF_OnePWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define LowF_OnePWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define LowF_OnePWM_STATUS_TC_INT_EN_MASK_SHIFT            (LowF_OnePWM_STATUS_TC_SHIFT - 4u)
    #define LowF_OnePWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define LowF_OnePWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (LowF_OnePWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define LowF_OnePWM_STATUS_TC              (uint8)((uint8)0x01u << LowF_OnePWM_STATUS_TC_SHIFT)
    #define LowF_OnePWM_STATUS_CMP1            (uint8)((uint8)0x01u << LowF_OnePWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define LowF_OnePWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)LowF_OnePWM_STATUS_TC >> 4u)
    #define LowF_OnePWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)LowF_OnePWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define LowF_OnePWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define LowF_OnePWM_RT1_MASK              (uint8)((uint8)0x03u << LowF_OnePWM_RT1_SHIFT)
    #define LowF_OnePWM_SYNC                  (uint8)((uint8)0x03u << LowF_OnePWM_RT1_SHIFT)
    #define LowF_OnePWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define LowF_OnePWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << LowF_OnePWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define LowF_OnePWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << LowF_OnePWM_SYNCDSI_SHIFT)


#else
    #define LowF_OnePWM_STATUS                (*(reg8 *)   LowF_OnePWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define LowF_OnePWM_STATUS_PTR            ((reg8 *)    LowF_OnePWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define LowF_OnePWM_STATUS_MASK           (*(reg8 *)   LowF_OnePWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define LowF_OnePWM_STATUS_MASK_PTR       ((reg8 *)    LowF_OnePWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define LowF_OnePWM_STATUS_AUX_CTRL       (*(reg8 *)   LowF_OnePWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define LowF_OnePWM_CONTROL               (*(reg8 *)   LowF_OnePWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define LowF_OnePWM_CONTROL_PTR           ((reg8 *)    LowF_OnePWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define LowF_OnePWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define LowF_OnePWM_CTRL_RESET_SHIFT       (0x06u)
    #define LowF_OnePWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define LowF_OnePWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define LowF_OnePWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define LowF_OnePWM_CTRL_ENABLE            (uint8)((uint8)0x01u << LowF_OnePWM_CTRL_ENABLE_SHIFT)
    #define LowF_OnePWM_CTRL_RESET             (uint8)((uint8)0x01u << LowF_OnePWM_CTRL_RESET_SHIFT)
    #define LowF_OnePWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << LowF_OnePWM_CTRL_CMPMODE2_SHIFT)
    #define LowF_OnePWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << LowF_OnePWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define LowF_OnePWM_STATUS_KILL_SHIFT          (0x05u)
    #define LowF_OnePWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define LowF_OnePWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define LowF_OnePWM_STATUS_TC_SHIFT            (0x02u)
    #define LowF_OnePWM_STATUS_CMP2_SHIFT          (0x01u)
    #define LowF_OnePWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define LowF_OnePWM_STATUS_KILL_INT_EN_MASK_SHIFT          (LowF_OnePWM_STATUS_KILL_SHIFT)
    #define LowF_OnePWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (LowF_OnePWM_STATUS_FIFONEMPTY_SHIFT)
    #define LowF_OnePWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (LowF_OnePWM_STATUS_FIFOFULL_SHIFT)
    #define LowF_OnePWM_STATUS_TC_INT_EN_MASK_SHIFT            (LowF_OnePWM_STATUS_TC_SHIFT)
    #define LowF_OnePWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (LowF_OnePWM_STATUS_CMP2_SHIFT)
    #define LowF_OnePWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (LowF_OnePWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define LowF_OnePWM_STATUS_KILL            (uint8)((uint8)0x00u << LowF_OnePWM_STATUS_KILL_SHIFT )
    #define LowF_OnePWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << LowF_OnePWM_STATUS_FIFOFULL_SHIFT)
    #define LowF_OnePWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << LowF_OnePWM_STATUS_FIFONEMPTY_SHIFT)
    #define LowF_OnePWM_STATUS_TC              (uint8)((uint8)0x01u << LowF_OnePWM_STATUS_TC_SHIFT)
    #define LowF_OnePWM_STATUS_CMP2            (uint8)((uint8)0x01u << LowF_OnePWM_STATUS_CMP2_SHIFT)
    #define LowF_OnePWM_STATUS_CMP1            (uint8)((uint8)0x01u << LowF_OnePWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define LowF_OnePWM_STATUS_KILL_INT_EN_MASK            (LowF_OnePWM_STATUS_KILL)
    #define LowF_OnePWM_STATUS_FIFOFULL_INT_EN_MASK        (LowF_OnePWM_STATUS_FIFOFULL)
    #define LowF_OnePWM_STATUS_FIFONEMPTY_INT_EN_MASK      (LowF_OnePWM_STATUS_FIFONEMPTY)
    #define LowF_OnePWM_STATUS_TC_INT_EN_MASK              (LowF_OnePWM_STATUS_TC)
    #define LowF_OnePWM_STATUS_CMP2_INT_EN_MASK            (LowF_OnePWM_STATUS_CMP2)
    #define LowF_OnePWM_STATUS_CMP1_INT_EN_MASK            (LowF_OnePWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define LowF_OnePWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define LowF_OnePWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define LowF_OnePWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define LowF_OnePWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define LowF_OnePWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* LowF_OnePWM_UsingFixedFunction */

#endif  /* CY_PWM_LowF_OnePWM_H */


/* [] END OF FILE */
