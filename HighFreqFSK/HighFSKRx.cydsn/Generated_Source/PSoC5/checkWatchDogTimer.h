/*******************************************************************************
* File Name: checkWatchDogTimer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_checkWatchDogTimer_H)
#define CY_Timer_v2_60_checkWatchDogTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 checkWatchDogTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define checkWatchDogTimer_Resolution                 16u
#define checkWatchDogTimer_UsingFixedFunction         1u
#define checkWatchDogTimer_UsingHWCaptureCounter      0u
#define checkWatchDogTimer_SoftwareCaptureMode        0u
#define checkWatchDogTimer_SoftwareTriggerMode        0u
#define checkWatchDogTimer_UsingHWEnable              0u
#define checkWatchDogTimer_EnableTriggerMode          0u
#define checkWatchDogTimer_InterruptOnCaptureCount    0u
#define checkWatchDogTimer_RunModeUsed                0u
#define checkWatchDogTimer_ControlRegRemoved          0u

#if defined(checkWatchDogTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define checkWatchDogTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (checkWatchDogTimer_UsingFixedFunction)
    #define checkWatchDogTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define checkWatchDogTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End checkWatchDogTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!checkWatchDogTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (checkWatchDogTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!checkWatchDogTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}checkWatchDogTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    checkWatchDogTimer_Start(void) ;
void    checkWatchDogTimer_Stop(void) ;

void    checkWatchDogTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   checkWatchDogTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define checkWatchDogTimer_GetInterruptSource() checkWatchDogTimer_ReadStatusRegister()

#if(!checkWatchDogTimer_UDB_CONTROL_REG_REMOVED)
    uint8   checkWatchDogTimer_ReadControlRegister(void) ;
    void    checkWatchDogTimer_WriteControlRegister(uint8 control) ;
#endif /* (!checkWatchDogTimer_UDB_CONTROL_REG_REMOVED) */

uint16  checkWatchDogTimer_ReadPeriod(void) ;
void    checkWatchDogTimer_WritePeriod(uint16 period) ;
uint16  checkWatchDogTimer_ReadCounter(void) ;
void    checkWatchDogTimer_WriteCounter(uint16 counter) ;
uint16  checkWatchDogTimer_ReadCapture(void) ;
void    checkWatchDogTimer_SoftwareCapture(void) ;

#if(!checkWatchDogTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (checkWatchDogTimer_SoftwareCaptureMode)
        void    checkWatchDogTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!checkWatchDogTimer_UsingFixedFunction) */

    #if (checkWatchDogTimer_SoftwareTriggerMode)
        void    checkWatchDogTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (checkWatchDogTimer_SoftwareTriggerMode) */

    #if (checkWatchDogTimer_EnableTriggerMode)
        void    checkWatchDogTimer_EnableTrigger(void) ;
        void    checkWatchDogTimer_DisableTrigger(void) ;
    #endif /* (checkWatchDogTimer_EnableTriggerMode) */


    #if(checkWatchDogTimer_InterruptOnCaptureCount)
        void    checkWatchDogTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (checkWatchDogTimer_InterruptOnCaptureCount) */

    #if (checkWatchDogTimer_UsingHWCaptureCounter)
        void    checkWatchDogTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   checkWatchDogTimer_ReadCaptureCount(void) ;
    #endif /* (checkWatchDogTimer_UsingHWCaptureCounter) */

    void checkWatchDogTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void checkWatchDogTimer_Init(void)          ;
void checkWatchDogTimer_Enable(void)        ;
void checkWatchDogTimer_SaveConfig(void)    ;
void checkWatchDogTimer_RestoreConfig(void) ;
void checkWatchDogTimer_Sleep(void)         ;
void checkWatchDogTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define checkWatchDogTimer__B_TIMER__CM_NONE 0
#define checkWatchDogTimer__B_TIMER__CM_RISINGEDGE 1
#define checkWatchDogTimer__B_TIMER__CM_FALLINGEDGE 2
#define checkWatchDogTimer__B_TIMER__CM_EITHEREDGE 3
#define checkWatchDogTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define checkWatchDogTimer__B_TIMER__TM_NONE 0x00u
#define checkWatchDogTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define checkWatchDogTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define checkWatchDogTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define checkWatchDogTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define checkWatchDogTimer_INIT_PERIOD             65535u
#define checkWatchDogTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << checkWatchDogTimer_CTRL_CAP_MODE_SHIFT))
#define checkWatchDogTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << checkWatchDogTimer_CTRL_TRIG_MODE_SHIFT))
#if (checkWatchDogTimer_UsingFixedFunction)
    #define checkWatchDogTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << checkWatchDogTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << checkWatchDogTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define checkWatchDogTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << checkWatchDogTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << checkWatchDogTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << checkWatchDogTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (checkWatchDogTimer_UsingFixedFunction) */
#define checkWatchDogTimer_INIT_CAPTURE_COUNT      (2u)
#define checkWatchDogTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << checkWatchDogTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (checkWatchDogTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define checkWatchDogTimer_STATUS         (*(reg8 *) checkWatchDogTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define checkWatchDogTimer_STATUS_MASK    (*(reg8 *) checkWatchDogTimer_TimerHW__SR0 )
    #define checkWatchDogTimer_CONTROL        (*(reg8 *) checkWatchDogTimer_TimerHW__CFG0)
    #define checkWatchDogTimer_CONTROL2       (*(reg8 *) checkWatchDogTimer_TimerHW__CFG1)
    #define checkWatchDogTimer_CONTROL2_PTR   ( (reg8 *) checkWatchDogTimer_TimerHW__CFG1)
    #define checkWatchDogTimer_RT1            (*(reg8 *) checkWatchDogTimer_TimerHW__RT1)
    #define checkWatchDogTimer_RT1_PTR        ( (reg8 *) checkWatchDogTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define checkWatchDogTimer_CONTROL3       (*(reg8 *) checkWatchDogTimer_TimerHW__CFG2)
        #define checkWatchDogTimer_CONTROL3_PTR   ( (reg8 *) checkWatchDogTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define checkWatchDogTimer_GLOBAL_ENABLE  (*(reg8 *) checkWatchDogTimer_TimerHW__PM_ACT_CFG)
    #define checkWatchDogTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) checkWatchDogTimer_TimerHW__PM_STBY_CFG)

    #define checkWatchDogTimer_CAPTURE_LSB         (* (reg16 *) checkWatchDogTimer_TimerHW__CAP0 )
    #define checkWatchDogTimer_CAPTURE_LSB_PTR       ((reg16 *) checkWatchDogTimer_TimerHW__CAP0 )
    #define checkWatchDogTimer_PERIOD_LSB          (* (reg16 *) checkWatchDogTimer_TimerHW__PER0 )
    #define checkWatchDogTimer_PERIOD_LSB_PTR        ((reg16 *) checkWatchDogTimer_TimerHW__PER0 )
    #define checkWatchDogTimer_COUNTER_LSB         (* (reg16 *) checkWatchDogTimer_TimerHW__CNT_CMP0 )
    #define checkWatchDogTimer_COUNTER_LSB_PTR       ((reg16 *) checkWatchDogTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define checkWatchDogTimer_BLOCK_EN_MASK                     checkWatchDogTimer_TimerHW__PM_ACT_MSK
    #define checkWatchDogTimer_BLOCK_STBY_EN_MASK                checkWatchDogTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define checkWatchDogTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define checkWatchDogTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define checkWatchDogTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define checkWatchDogTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define checkWatchDogTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define checkWatchDogTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << checkWatchDogTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define checkWatchDogTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define checkWatchDogTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << checkWatchDogTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define checkWatchDogTimer_CTRL_MODE_SHIFT                 0x01u
        #define checkWatchDogTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << checkWatchDogTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define checkWatchDogTimer_CTRL_RCOD_SHIFT        0x02u
        #define checkWatchDogTimer_CTRL_ENBL_SHIFT        0x00u
        #define checkWatchDogTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define checkWatchDogTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << checkWatchDogTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define checkWatchDogTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << checkWatchDogTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define checkWatchDogTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << checkWatchDogTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define checkWatchDogTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << checkWatchDogTimer_CTRL_RCOD_SHIFT))
        #define checkWatchDogTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << checkWatchDogTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define checkWatchDogTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define checkWatchDogTimer_RT1_MASK                        ((uint8)((uint8)0x03u << checkWatchDogTimer_RT1_SHIFT))
    #define checkWatchDogTimer_SYNC                            ((uint8)((uint8)0x03u << checkWatchDogTimer_RT1_SHIFT))
    #define checkWatchDogTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define checkWatchDogTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << checkWatchDogTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define checkWatchDogTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << checkWatchDogTimer_SYNCDSI_SHIFT))

    #define checkWatchDogTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << checkWatchDogTimer_CTRL_MODE_SHIFT))
    #define checkWatchDogTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << checkWatchDogTimer_CTRL_MODE_SHIFT))
    #define checkWatchDogTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << checkWatchDogTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define checkWatchDogTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define checkWatchDogTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define checkWatchDogTimer_STATUS_TC_INT_MASK_SHIFT        (checkWatchDogTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define checkWatchDogTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (checkWatchDogTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define checkWatchDogTimer_STATUS_TC                       ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_TC_SHIFT))
    #define checkWatchDogTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define checkWatchDogTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define checkWatchDogTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define checkWatchDogTimer_STATUS              (* (reg8 *) checkWatchDogTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define checkWatchDogTimer_STATUS_MASK         (* (reg8 *) checkWatchDogTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define checkWatchDogTimer_STATUS_AUX_CTRL     (* (reg8 *) checkWatchDogTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define checkWatchDogTimer_CONTROL             (* (reg8 *) checkWatchDogTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(checkWatchDogTimer_Resolution <= 8u) /* 8-bit Timer */
        #define checkWatchDogTimer_CAPTURE_LSB         (* (reg8 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define checkWatchDogTimer_CAPTURE_LSB_PTR       ((reg8 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define checkWatchDogTimer_PERIOD_LSB          (* (reg8 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define checkWatchDogTimer_PERIOD_LSB_PTR        ((reg8 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define checkWatchDogTimer_COUNTER_LSB         (* (reg8 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define checkWatchDogTimer_COUNTER_LSB_PTR       ((reg8 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(checkWatchDogTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define checkWatchDogTimer_CAPTURE_LSB         (* (reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define checkWatchDogTimer_CAPTURE_LSB_PTR       ((reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define checkWatchDogTimer_PERIOD_LSB          (* (reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define checkWatchDogTimer_PERIOD_LSB_PTR        ((reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define checkWatchDogTimer_COUNTER_LSB         (* (reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define checkWatchDogTimer_COUNTER_LSB_PTR       ((reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define checkWatchDogTimer_CAPTURE_LSB         (* (reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define checkWatchDogTimer_CAPTURE_LSB_PTR       ((reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define checkWatchDogTimer_PERIOD_LSB          (* (reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define checkWatchDogTimer_PERIOD_LSB_PTR        ((reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define checkWatchDogTimer_COUNTER_LSB         (* (reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define checkWatchDogTimer_COUNTER_LSB_PTR       ((reg16 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(checkWatchDogTimer_Resolution <= 24u)/* 24-bit Timer */
        #define checkWatchDogTimer_CAPTURE_LSB         (* (reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define checkWatchDogTimer_CAPTURE_LSB_PTR       ((reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define checkWatchDogTimer_PERIOD_LSB          (* (reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define checkWatchDogTimer_PERIOD_LSB_PTR        ((reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define checkWatchDogTimer_COUNTER_LSB         (* (reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define checkWatchDogTimer_COUNTER_LSB_PTR       ((reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define checkWatchDogTimer_CAPTURE_LSB         (* (reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define checkWatchDogTimer_CAPTURE_LSB_PTR       ((reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define checkWatchDogTimer_PERIOD_LSB          (* (reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define checkWatchDogTimer_PERIOD_LSB_PTR        ((reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define checkWatchDogTimer_COUNTER_LSB         (* (reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define checkWatchDogTimer_COUNTER_LSB_PTR       ((reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define checkWatchDogTimer_CAPTURE_LSB         (* (reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define checkWatchDogTimer_CAPTURE_LSB_PTR       ((reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define checkWatchDogTimer_PERIOD_LSB          (* (reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define checkWatchDogTimer_PERIOD_LSB_PTR        ((reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define checkWatchDogTimer_COUNTER_LSB         (* (reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define checkWatchDogTimer_COUNTER_LSB_PTR       ((reg32 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define checkWatchDogTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) checkWatchDogTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (checkWatchDogTimer_UsingHWCaptureCounter)
        #define checkWatchDogTimer_CAP_COUNT              (*(reg8 *) checkWatchDogTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define checkWatchDogTimer_CAP_COUNT_PTR          ( (reg8 *) checkWatchDogTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define checkWatchDogTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) checkWatchDogTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define checkWatchDogTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) checkWatchDogTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (checkWatchDogTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define checkWatchDogTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define checkWatchDogTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define checkWatchDogTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define checkWatchDogTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define checkWatchDogTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define checkWatchDogTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << checkWatchDogTimer_CTRL_INTCNT_SHIFT))
    #define checkWatchDogTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << checkWatchDogTimer_CTRL_TRIG_MODE_SHIFT))
    #define checkWatchDogTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << checkWatchDogTimer_CTRL_TRIG_EN_SHIFT))
    #define checkWatchDogTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << checkWatchDogTimer_CTRL_CAP_MODE_SHIFT))
    #define checkWatchDogTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << checkWatchDogTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define checkWatchDogTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define checkWatchDogTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define checkWatchDogTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define checkWatchDogTimer_STATUS_TC_INT_MASK_SHIFT       checkWatchDogTimer_STATUS_TC_SHIFT
    #define checkWatchDogTimer_STATUS_CAPTURE_INT_MASK_SHIFT  checkWatchDogTimer_STATUS_CAPTURE_SHIFT
    #define checkWatchDogTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define checkWatchDogTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define checkWatchDogTimer_STATUS_FIFOFULL_INT_MASK_SHIFT checkWatchDogTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define checkWatchDogTimer_STATUS_TC                      ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define checkWatchDogTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define checkWatchDogTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define checkWatchDogTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define checkWatchDogTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define checkWatchDogTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define checkWatchDogTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << checkWatchDogTimer_STATUS_FIFOFULL_SHIFT))

    #define checkWatchDogTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define checkWatchDogTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define checkWatchDogTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define checkWatchDogTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define checkWatchDogTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define checkWatchDogTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_checkWatchDogTimer_H */


/* [] END OF FILE */
