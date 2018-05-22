/*******************************************************************************
* File Name: Audible_Frequency.h
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

#if !defined(CY_PWM_Audible_Frequency_H)
#define CY_PWM_Audible_Frequency_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Audible_Frequency_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Audible_Frequency_Resolution                     (16u)
#define Audible_Frequency_UsingFixedFunction             (0u)
#define Audible_Frequency_DeadBandMode                   (0u)
#define Audible_Frequency_KillModeMinTime                (0u)
#define Audible_Frequency_KillMode                       (0u)
#define Audible_Frequency_PWMMode                        (0u)
#define Audible_Frequency_PWMModeIsCenterAligned         (0u)
#define Audible_Frequency_DeadBandUsed                   (0u)
#define Audible_Frequency_DeadBand2_4                    (0u)

#if !defined(Audible_Frequency_PWMUDB_genblk8_stsreg__REMOVED)
    #define Audible_Frequency_UseStatus                  (1u)
#else
    #define Audible_Frequency_UseStatus                  (0u)
#endif /* !defined(Audible_Frequency_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Audible_Frequency_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Audible_Frequency_UseControl                 (1u)
#else
    #define Audible_Frequency_UseControl                 (0u)
#endif /* !defined(Audible_Frequency_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Audible_Frequency_UseOneCompareMode              (1u)
#define Audible_Frequency_MinimumKillTime                (1u)
#define Audible_Frequency_EnableMode                     (0u)

#define Audible_Frequency_CompareMode1SW                 (0u)
#define Audible_Frequency_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Audible_Frequency__B_PWM__DISABLED 0
#define Audible_Frequency__B_PWM__ASYNCHRONOUS 1
#define Audible_Frequency__B_PWM__SINGLECYCLE 2
#define Audible_Frequency__B_PWM__LATCHED 3
#define Audible_Frequency__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Audible_Frequency__B_PWM__DBMDISABLED 0
#define Audible_Frequency__B_PWM__DBM_2_4_CLOCKS 1
#define Audible_Frequency__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Audible_Frequency__B_PWM__ONE_OUTPUT 0
#define Audible_Frequency__B_PWM__TWO_OUTPUTS 1
#define Audible_Frequency__B_PWM__DUAL_EDGE 2
#define Audible_Frequency__B_PWM__CENTER_ALIGN 3
#define Audible_Frequency__B_PWM__DITHER 5
#define Audible_Frequency__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Audible_Frequency__B_PWM__LESS_THAN 1
#define Audible_Frequency__B_PWM__LESS_THAN_OR_EQUAL 2
#define Audible_Frequency__B_PWM__GREATER_THAN 3
#define Audible_Frequency__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Audible_Frequency__B_PWM__EQUAL 0
#define Audible_Frequency__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Audible_Frequency_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Audible_Frequency_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Audible_Frequency_PWMModeIsCenterAligned) */
        #if (Audible_Frequency_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Audible_Frequency_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Audible_Frequency_DeadBandMode == Audible_Frequency__B_PWM__DBM_256_CLOCKS || \
            Audible_Frequency_DeadBandMode == Audible_Frequency__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Audible_Frequency_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Audible_Frequency_KillModeMinTime) */

        /* Backup control register */
        #if(Audible_Frequency_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Audible_Frequency_UseControl) */

    #endif /* (!Audible_Frequency_UsingFixedFunction) */

}Audible_Frequency_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Audible_Frequency_Start(void) ;
void    Audible_Frequency_Stop(void) ;

#if (Audible_Frequency_UseStatus || Audible_Frequency_UsingFixedFunction)
    void  Audible_Frequency_SetInterruptMode(uint8 interruptMode) ;
    uint8 Audible_Frequency_ReadStatusRegister(void) ;
#endif /* (Audible_Frequency_UseStatus || Audible_Frequency_UsingFixedFunction) */

#define Audible_Frequency_GetInterruptSource() Audible_Frequency_ReadStatusRegister()

#if (Audible_Frequency_UseControl)
    uint8 Audible_Frequency_ReadControlRegister(void) ;
    void  Audible_Frequency_WriteControlRegister(uint8 control)
          ;
#endif /* (Audible_Frequency_UseControl) */

#if (Audible_Frequency_UseOneCompareMode)
   #if (Audible_Frequency_CompareMode1SW)
       void    Audible_Frequency_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Audible_Frequency_CompareMode1SW) */
#else
    #if (Audible_Frequency_CompareMode1SW)
        void    Audible_Frequency_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Audible_Frequency_CompareMode1SW) */
    #if (Audible_Frequency_CompareMode2SW)
        void    Audible_Frequency_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Audible_Frequency_CompareMode2SW) */
#endif /* (Audible_Frequency_UseOneCompareMode) */

#if (!Audible_Frequency_UsingFixedFunction)
    uint16   Audible_Frequency_ReadCounter(void) ;
    uint16 Audible_Frequency_ReadCapture(void) ;

    #if (Audible_Frequency_UseStatus)
            void Audible_Frequency_ClearFIFO(void) ;
    #endif /* (Audible_Frequency_UseStatus) */

    void    Audible_Frequency_WriteCounter(uint16 counter)
            ;
#endif /* (!Audible_Frequency_UsingFixedFunction) */

void    Audible_Frequency_WritePeriod(uint16 period)
        ;
uint16 Audible_Frequency_ReadPeriod(void) ;

#if (Audible_Frequency_UseOneCompareMode)
    void    Audible_Frequency_WriteCompare(uint16 compare)
            ;
    uint16 Audible_Frequency_ReadCompare(void) ;
#else
    void    Audible_Frequency_WriteCompare1(uint16 compare)
            ;
    uint16 Audible_Frequency_ReadCompare1(void) ;
    void    Audible_Frequency_WriteCompare2(uint16 compare)
            ;
    uint16 Audible_Frequency_ReadCompare2(void) ;
#endif /* (Audible_Frequency_UseOneCompareMode) */


#if (Audible_Frequency_DeadBandUsed)
    void    Audible_Frequency_WriteDeadTime(uint8 deadtime) ;
    uint8   Audible_Frequency_ReadDeadTime(void) ;
#endif /* (Audible_Frequency_DeadBandUsed) */

#if ( Audible_Frequency_KillModeMinTime)
    void Audible_Frequency_WriteKillTime(uint8 killtime) ;
    uint8 Audible_Frequency_ReadKillTime(void) ;
#endif /* ( Audible_Frequency_KillModeMinTime) */

void Audible_Frequency_Init(void) ;
void Audible_Frequency_Enable(void) ;
void Audible_Frequency_Sleep(void) ;
void Audible_Frequency_Wakeup(void) ;
void Audible_Frequency_SaveConfig(void) ;
void Audible_Frequency_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Audible_Frequency_INIT_PERIOD_VALUE          (82u)
#define Audible_Frequency_INIT_COMPARE_VALUE1        (41u)
#define Audible_Frequency_INIT_COMPARE_VALUE2        (63u)
#define Audible_Frequency_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Audible_Frequency_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Audible_Frequency_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Audible_Frequency_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Audible_Frequency_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Audible_Frequency_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Audible_Frequency_CTRL_CMPMODE2_SHIFT)
#define Audible_Frequency_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Audible_Frequency_CTRL_CMPMODE1_SHIFT)
#define Audible_Frequency_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Audible_Frequency_UsingFixedFunction)
   #define Audible_Frequency_PERIOD_LSB              (*(reg16 *) Audible_Frequency_PWMHW__PER0)
   #define Audible_Frequency_PERIOD_LSB_PTR          ( (reg16 *) Audible_Frequency_PWMHW__PER0)
   #define Audible_Frequency_COMPARE1_LSB            (*(reg16 *) Audible_Frequency_PWMHW__CNT_CMP0)
   #define Audible_Frequency_COMPARE1_LSB_PTR        ( (reg16 *) Audible_Frequency_PWMHW__CNT_CMP0)
   #define Audible_Frequency_COMPARE2_LSB            (0x00u)
   #define Audible_Frequency_COMPARE2_LSB_PTR        (0x00u)
   #define Audible_Frequency_COUNTER_LSB             (*(reg16 *) Audible_Frequency_PWMHW__CNT_CMP0)
   #define Audible_Frequency_COUNTER_LSB_PTR         ( (reg16 *) Audible_Frequency_PWMHW__CNT_CMP0)
   #define Audible_Frequency_CAPTURE_LSB             (*(reg16 *) Audible_Frequency_PWMHW__CAP0)
   #define Audible_Frequency_CAPTURE_LSB_PTR         ( (reg16 *) Audible_Frequency_PWMHW__CAP0)
   #define Audible_Frequency_RT1                     (*(reg8 *)  Audible_Frequency_PWMHW__RT1)
   #define Audible_Frequency_RT1_PTR                 ( (reg8 *)  Audible_Frequency_PWMHW__RT1)

#else
   #if (Audible_Frequency_Resolution == 8u) /* 8bit - PWM */

       #if(Audible_Frequency_PWMModeIsCenterAligned)
           #define Audible_Frequency_PERIOD_LSB      (*(reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Audible_Frequency_PERIOD_LSB_PTR  ((reg8 *)   Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Audible_Frequency_PERIOD_LSB      (*(reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Audible_Frequency_PERIOD_LSB_PTR  ((reg8 *)   Audible_Frequency_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Audible_Frequency_PWMModeIsCenterAligned) */

       #define Audible_Frequency_COMPARE1_LSB        (*(reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Audible_Frequency_COMPARE1_LSB_PTR    ((reg8 *)   Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Audible_Frequency_COMPARE2_LSB        (*(reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Audible_Frequency_COMPARE2_LSB_PTR    ((reg8 *)   Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Audible_Frequency_COUNTERCAP_LSB      (*(reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Audible_Frequency_COUNTERCAP_LSB_PTR  ((reg8 *)   Audible_Frequency_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Audible_Frequency_COUNTER_LSB         (*(reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Audible_Frequency_COUNTER_LSB_PTR     ((reg8 *)   Audible_Frequency_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Audible_Frequency_CAPTURE_LSB         (*(reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Audible_Frequency_CAPTURE_LSB_PTR     ((reg8 *)   Audible_Frequency_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Audible_Frequency_PWMModeIsCenterAligned)
               #define Audible_Frequency_PERIOD_LSB      (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Audible_Frequency_PERIOD_LSB_PTR  ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Audible_Frequency_PERIOD_LSB      (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Audible_Frequency_PERIOD_LSB_PTR  ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Audible_Frequency_PWMModeIsCenterAligned) */

            #define Audible_Frequency_COMPARE1_LSB       (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Audible_Frequency_COMPARE1_LSB_PTR   ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Audible_Frequency_COMPARE2_LSB       (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Audible_Frequency_COMPARE2_LSB_PTR   ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Audible_Frequency_COUNTERCAP_LSB     (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Audible_Frequency_COUNTERCAP_LSB_PTR ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Audible_Frequency_COUNTER_LSB        (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Audible_Frequency_COUNTER_LSB_PTR    ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Audible_Frequency_CAPTURE_LSB        (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Audible_Frequency_CAPTURE_LSB_PTR    ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Audible_Frequency_PWMModeIsCenterAligned)
               #define Audible_Frequency_PERIOD_LSB      (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Audible_Frequency_PERIOD_LSB_PTR  ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Audible_Frequency_PERIOD_LSB      (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Audible_Frequency_PERIOD_LSB_PTR  ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Audible_Frequency_PWMModeIsCenterAligned) */

            #define Audible_Frequency_COMPARE1_LSB       (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Audible_Frequency_COMPARE1_LSB_PTR   ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Audible_Frequency_COMPARE2_LSB       (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Audible_Frequency_COMPARE2_LSB_PTR   ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Audible_Frequency_COUNTERCAP_LSB     (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Audible_Frequency_COUNTERCAP_LSB_PTR ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Audible_Frequency_COUNTER_LSB        (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Audible_Frequency_COUNTER_LSB_PTR    ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Audible_Frequency_CAPTURE_LSB        (*(reg16 *) Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Audible_Frequency_CAPTURE_LSB_PTR    ((reg16 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Audible_Frequency_AUX_CONTROLDP1          (*(reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Audible_Frequency_AUX_CONTROLDP1_PTR      ((reg8 *)   Audible_Frequency_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Audible_Frequency_Resolution == 8) */

   #define Audible_Frequency_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Audible_Frequency_AUX_CONTROLDP0          (*(reg8 *)  Audible_Frequency_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Audible_Frequency_AUX_CONTROLDP0_PTR      ((reg8 *)   Audible_Frequency_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Audible_Frequency_UsingFixedFunction) */

#if(Audible_Frequency_KillModeMinTime )
    #define Audible_Frequency_KILLMODEMINTIME        (*(reg8 *)  Audible_Frequency_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Audible_Frequency_KILLMODEMINTIME_PTR    ((reg8 *)   Audible_Frequency_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Audible_Frequency_KillModeMinTime ) */

#if(Audible_Frequency_DeadBandMode == Audible_Frequency__B_PWM__DBM_256_CLOCKS)
    #define Audible_Frequency_DEADBAND_COUNT         (*(reg8 *)  Audible_Frequency_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Audible_Frequency_DEADBAND_COUNT_PTR     ((reg8 *)   Audible_Frequency_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Audible_Frequency_DEADBAND_LSB_PTR       ((reg8 *)   Audible_Frequency_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Audible_Frequency_DEADBAND_LSB           (*(reg8 *)  Audible_Frequency_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Audible_Frequency_DeadBandMode == Audible_Frequency__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Audible_Frequency_UsingFixedFunction)
        #define Audible_Frequency_DEADBAND_COUNT         (*(reg8 *)  Audible_Frequency_PWMHW__CFG0)
        #define Audible_Frequency_DEADBAND_COUNT_PTR     ((reg8 *)   Audible_Frequency_PWMHW__CFG0)
        #define Audible_Frequency_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Audible_Frequency_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Audible_Frequency_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Audible_Frequency_DEADBAND_COUNT         (*(reg8 *)  Audible_Frequency_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Audible_Frequency_DEADBAND_COUNT_PTR     ((reg8 *)   Audible_Frequency_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Audible_Frequency_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Audible_Frequency_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Audible_Frequency_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Audible_Frequency_UsingFixedFunction) */
#endif /* (Audible_Frequency_DeadBandMode == Audible_Frequency__B_PWM__DBM_256_CLOCKS) */



#if (Audible_Frequency_UsingFixedFunction)
    #define Audible_Frequency_STATUS                 (*(reg8 *) Audible_Frequency_PWMHW__SR0)
    #define Audible_Frequency_STATUS_PTR             ((reg8 *) Audible_Frequency_PWMHW__SR0)
    #define Audible_Frequency_STATUS_MASK            (*(reg8 *) Audible_Frequency_PWMHW__SR0)
    #define Audible_Frequency_STATUS_MASK_PTR        ((reg8 *) Audible_Frequency_PWMHW__SR0)
    #define Audible_Frequency_CONTROL                (*(reg8 *) Audible_Frequency_PWMHW__CFG0)
    #define Audible_Frequency_CONTROL_PTR            ((reg8 *) Audible_Frequency_PWMHW__CFG0)
    #define Audible_Frequency_CONTROL2               (*(reg8 *) Audible_Frequency_PWMHW__CFG1)
    #define Audible_Frequency_CONTROL3               (*(reg8 *) Audible_Frequency_PWMHW__CFG2)
    #define Audible_Frequency_GLOBAL_ENABLE          (*(reg8 *) Audible_Frequency_PWMHW__PM_ACT_CFG)
    #define Audible_Frequency_GLOBAL_ENABLE_PTR      ( (reg8 *) Audible_Frequency_PWMHW__PM_ACT_CFG)
    #define Audible_Frequency_GLOBAL_STBY_ENABLE     (*(reg8 *) Audible_Frequency_PWMHW__PM_STBY_CFG)
    #define Audible_Frequency_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Audible_Frequency_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Audible_Frequency_BLOCK_EN_MASK          (Audible_Frequency_PWMHW__PM_ACT_MSK)
    #define Audible_Frequency_BLOCK_STBY_EN_MASK     (Audible_Frequency_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Audible_Frequency_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Audible_Frequency_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Audible_Frequency_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Audible_Frequency_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Audible_Frequency_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Audible_Frequency_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Audible_Frequency_CTRL_ENABLE            (uint8)((uint8)0x01u << Audible_Frequency_CTRL_ENABLE_SHIFT)
    #define Audible_Frequency_CTRL_RESET             (uint8)((uint8)0x01u << Audible_Frequency_CTRL_RESET_SHIFT)
    #define Audible_Frequency_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Audible_Frequency_CTRL_CMPMODE2_SHIFT)
    #define Audible_Frequency_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Audible_Frequency_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Audible_Frequency_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Audible_Frequency_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Audible_Frequency_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Audible_Frequency_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Audible_Frequency_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Audible_Frequency_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Audible_Frequency_STATUS_TC_INT_EN_MASK_SHIFT            (Audible_Frequency_STATUS_TC_SHIFT - 4u)
    #define Audible_Frequency_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Audible_Frequency_STATUS_CMP1_INT_EN_MASK_SHIFT          (Audible_Frequency_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Audible_Frequency_STATUS_TC              (uint8)((uint8)0x01u << Audible_Frequency_STATUS_TC_SHIFT)
    #define Audible_Frequency_STATUS_CMP1            (uint8)((uint8)0x01u << Audible_Frequency_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Audible_Frequency_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Audible_Frequency_STATUS_TC >> 4u)
    #define Audible_Frequency_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Audible_Frequency_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Audible_Frequency_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Audible_Frequency_RT1_MASK              (uint8)((uint8)0x03u << Audible_Frequency_RT1_SHIFT)
    #define Audible_Frequency_SYNC                  (uint8)((uint8)0x03u << Audible_Frequency_RT1_SHIFT)
    #define Audible_Frequency_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Audible_Frequency_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Audible_Frequency_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Audible_Frequency_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Audible_Frequency_SYNCDSI_SHIFT)


#else
    #define Audible_Frequency_STATUS                (*(reg8 *)   Audible_Frequency_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Audible_Frequency_STATUS_PTR            ((reg8 *)    Audible_Frequency_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Audible_Frequency_STATUS_MASK           (*(reg8 *)   Audible_Frequency_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Audible_Frequency_STATUS_MASK_PTR       ((reg8 *)    Audible_Frequency_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Audible_Frequency_STATUS_AUX_CTRL       (*(reg8 *)   Audible_Frequency_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Audible_Frequency_CONTROL               (*(reg8 *)   Audible_Frequency_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Audible_Frequency_CONTROL_PTR           ((reg8 *)    Audible_Frequency_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Audible_Frequency_CTRL_ENABLE_SHIFT      (0x07u)
    #define Audible_Frequency_CTRL_RESET_SHIFT       (0x06u)
    #define Audible_Frequency_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Audible_Frequency_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Audible_Frequency_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Audible_Frequency_CTRL_ENABLE            (uint8)((uint8)0x01u << Audible_Frequency_CTRL_ENABLE_SHIFT)
    #define Audible_Frequency_CTRL_RESET             (uint8)((uint8)0x01u << Audible_Frequency_CTRL_RESET_SHIFT)
    #define Audible_Frequency_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Audible_Frequency_CTRL_CMPMODE2_SHIFT)
    #define Audible_Frequency_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Audible_Frequency_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Audible_Frequency_STATUS_KILL_SHIFT          (0x05u)
    #define Audible_Frequency_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Audible_Frequency_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Audible_Frequency_STATUS_TC_SHIFT            (0x02u)
    #define Audible_Frequency_STATUS_CMP2_SHIFT          (0x01u)
    #define Audible_Frequency_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Audible_Frequency_STATUS_KILL_INT_EN_MASK_SHIFT          (Audible_Frequency_STATUS_KILL_SHIFT)
    #define Audible_Frequency_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Audible_Frequency_STATUS_FIFONEMPTY_SHIFT)
    #define Audible_Frequency_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Audible_Frequency_STATUS_FIFOFULL_SHIFT)
    #define Audible_Frequency_STATUS_TC_INT_EN_MASK_SHIFT            (Audible_Frequency_STATUS_TC_SHIFT)
    #define Audible_Frequency_STATUS_CMP2_INT_EN_MASK_SHIFT          (Audible_Frequency_STATUS_CMP2_SHIFT)
    #define Audible_Frequency_STATUS_CMP1_INT_EN_MASK_SHIFT          (Audible_Frequency_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Audible_Frequency_STATUS_KILL            (uint8)((uint8)0x00u << Audible_Frequency_STATUS_KILL_SHIFT )
    #define Audible_Frequency_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Audible_Frequency_STATUS_FIFOFULL_SHIFT)
    #define Audible_Frequency_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Audible_Frequency_STATUS_FIFONEMPTY_SHIFT)
    #define Audible_Frequency_STATUS_TC              (uint8)((uint8)0x01u << Audible_Frequency_STATUS_TC_SHIFT)
    #define Audible_Frequency_STATUS_CMP2            (uint8)((uint8)0x01u << Audible_Frequency_STATUS_CMP2_SHIFT)
    #define Audible_Frequency_STATUS_CMP1            (uint8)((uint8)0x01u << Audible_Frequency_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Audible_Frequency_STATUS_KILL_INT_EN_MASK            (Audible_Frequency_STATUS_KILL)
    #define Audible_Frequency_STATUS_FIFOFULL_INT_EN_MASK        (Audible_Frequency_STATUS_FIFOFULL)
    #define Audible_Frequency_STATUS_FIFONEMPTY_INT_EN_MASK      (Audible_Frequency_STATUS_FIFONEMPTY)
    #define Audible_Frequency_STATUS_TC_INT_EN_MASK              (Audible_Frequency_STATUS_TC)
    #define Audible_Frequency_STATUS_CMP2_INT_EN_MASK            (Audible_Frequency_STATUS_CMP2)
    #define Audible_Frequency_STATUS_CMP1_INT_EN_MASK            (Audible_Frequency_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Audible_Frequency_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Audible_Frequency_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Audible_Frequency_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Audible_Frequency_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Audible_Frequency_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Audible_Frequency_UsingFixedFunction */

#endif  /* CY_PWM_Audible_Frequency_H */


/* [] END OF FILE */
