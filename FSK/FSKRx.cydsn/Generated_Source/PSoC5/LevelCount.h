/*******************************************************************************
* File Name: LevelCount.h
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

#if !defined(CY_Timer_v2_60_LevelCount_H)
#define CY_Timer_v2_60_LevelCount_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 LevelCount_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define LevelCount_Resolution                 16u
#define LevelCount_UsingFixedFunction         0u
#define LevelCount_UsingHWCaptureCounter      0u
#define LevelCount_SoftwareCaptureMode        0u
#define LevelCount_SoftwareTriggerMode        0u
#define LevelCount_UsingHWEnable              0u
#define LevelCount_EnableTriggerMode          0u
#define LevelCount_InterruptOnCaptureCount    0u
#define LevelCount_RunModeUsed                0u
#define LevelCount_ControlRegRemoved          0u

#if defined(LevelCount_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define LevelCount_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (LevelCount_UsingFixedFunction)
    #define LevelCount_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define LevelCount_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End LevelCount_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!LevelCount_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (LevelCount_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!LevelCount_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}LevelCount_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    LevelCount_Start(void) ;
void    LevelCount_Stop(void) ;

void    LevelCount_SetInterruptMode(uint8 interruptMode) ;
uint8   LevelCount_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define LevelCount_GetInterruptSource() LevelCount_ReadStatusRegister()

#if(!LevelCount_UDB_CONTROL_REG_REMOVED)
    uint8   LevelCount_ReadControlRegister(void) ;
    void    LevelCount_WriteControlRegister(uint8 control) ;
#endif /* (!LevelCount_UDB_CONTROL_REG_REMOVED) */

uint16  LevelCount_ReadPeriod(void) ;
void    LevelCount_WritePeriod(uint16 period) ;
uint16  LevelCount_ReadCounter(void) ;
void    LevelCount_WriteCounter(uint16 counter) ;
uint16  LevelCount_ReadCapture(void) ;
void    LevelCount_SoftwareCapture(void) ;

#if(!LevelCount_UsingFixedFunction) /* UDB Prototypes */
    #if (LevelCount_SoftwareCaptureMode)
        void    LevelCount_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!LevelCount_UsingFixedFunction) */

    #if (LevelCount_SoftwareTriggerMode)
        void    LevelCount_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (LevelCount_SoftwareTriggerMode) */

    #if (LevelCount_EnableTriggerMode)
        void    LevelCount_EnableTrigger(void) ;
        void    LevelCount_DisableTrigger(void) ;
    #endif /* (LevelCount_EnableTriggerMode) */


    #if(LevelCount_InterruptOnCaptureCount)
        void    LevelCount_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (LevelCount_InterruptOnCaptureCount) */

    #if (LevelCount_UsingHWCaptureCounter)
        void    LevelCount_SetCaptureCount(uint8 captureCount) ;
        uint8   LevelCount_ReadCaptureCount(void) ;
    #endif /* (LevelCount_UsingHWCaptureCounter) */

    void LevelCount_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void LevelCount_Init(void)          ;
void LevelCount_Enable(void)        ;
void LevelCount_SaveConfig(void)    ;
void LevelCount_RestoreConfig(void) ;
void LevelCount_Sleep(void)         ;
void LevelCount_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define LevelCount__B_TIMER__CM_NONE 0
#define LevelCount__B_TIMER__CM_RISINGEDGE 1
#define LevelCount__B_TIMER__CM_FALLINGEDGE 2
#define LevelCount__B_TIMER__CM_EITHEREDGE 3
#define LevelCount__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define LevelCount__B_TIMER__TM_NONE 0x00u
#define LevelCount__B_TIMER__TM_RISINGEDGE 0x04u
#define LevelCount__B_TIMER__TM_FALLINGEDGE 0x08u
#define LevelCount__B_TIMER__TM_EITHEREDGE 0x0Cu
#define LevelCount__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define LevelCount_INIT_PERIOD             49u
#define LevelCount_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << LevelCount_CTRL_CAP_MODE_SHIFT))
#define LevelCount_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << LevelCount_CTRL_TRIG_MODE_SHIFT))
#if (LevelCount_UsingFixedFunction)
    #define LevelCount_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << LevelCount_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << LevelCount_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define LevelCount_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << LevelCount_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << LevelCount_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << LevelCount_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (LevelCount_UsingFixedFunction) */
#define LevelCount_INIT_CAPTURE_COUNT      (2u)
#define LevelCount_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << LevelCount_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (LevelCount_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define LevelCount_STATUS         (*(reg8 *) LevelCount_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define LevelCount_STATUS_MASK    (*(reg8 *) LevelCount_TimerHW__SR0 )
    #define LevelCount_CONTROL        (*(reg8 *) LevelCount_TimerHW__CFG0)
    #define LevelCount_CONTROL2       (*(reg8 *) LevelCount_TimerHW__CFG1)
    #define LevelCount_CONTROL2_PTR   ( (reg8 *) LevelCount_TimerHW__CFG1)
    #define LevelCount_RT1            (*(reg8 *) LevelCount_TimerHW__RT1)
    #define LevelCount_RT1_PTR        ( (reg8 *) LevelCount_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define LevelCount_CONTROL3       (*(reg8 *) LevelCount_TimerHW__CFG2)
        #define LevelCount_CONTROL3_PTR   ( (reg8 *) LevelCount_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define LevelCount_GLOBAL_ENABLE  (*(reg8 *) LevelCount_TimerHW__PM_ACT_CFG)
    #define LevelCount_GLOBAL_STBY_ENABLE  (*(reg8 *) LevelCount_TimerHW__PM_STBY_CFG)

    #define LevelCount_CAPTURE_LSB         (* (reg16 *) LevelCount_TimerHW__CAP0 )
    #define LevelCount_CAPTURE_LSB_PTR       ((reg16 *) LevelCount_TimerHW__CAP0 )
    #define LevelCount_PERIOD_LSB          (* (reg16 *) LevelCount_TimerHW__PER0 )
    #define LevelCount_PERIOD_LSB_PTR        ((reg16 *) LevelCount_TimerHW__PER0 )
    #define LevelCount_COUNTER_LSB         (* (reg16 *) LevelCount_TimerHW__CNT_CMP0 )
    #define LevelCount_COUNTER_LSB_PTR       ((reg16 *) LevelCount_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define LevelCount_BLOCK_EN_MASK                     LevelCount_TimerHW__PM_ACT_MSK
    #define LevelCount_BLOCK_STBY_EN_MASK                LevelCount_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define LevelCount_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define LevelCount_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define LevelCount_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define LevelCount_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define LevelCount_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define LevelCount_CTRL_ENABLE                        ((uint8)((uint8)0x01u << LevelCount_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define LevelCount_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define LevelCount_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << LevelCount_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define LevelCount_CTRL_MODE_SHIFT                 0x01u
        #define LevelCount_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << LevelCount_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define LevelCount_CTRL_RCOD_SHIFT        0x02u
        #define LevelCount_CTRL_ENBL_SHIFT        0x00u
        #define LevelCount_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define LevelCount_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << LevelCount_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define LevelCount_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << LevelCount_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define LevelCount_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << LevelCount_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define LevelCount_CTRL_RCOD       ((uint8)((uint8)0x03u << LevelCount_CTRL_RCOD_SHIFT))
        #define LevelCount_CTRL_ENBL       ((uint8)((uint8)0x80u << LevelCount_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define LevelCount_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define LevelCount_RT1_MASK                        ((uint8)((uint8)0x03u << LevelCount_RT1_SHIFT))
    #define LevelCount_SYNC                            ((uint8)((uint8)0x03u << LevelCount_RT1_SHIFT))
    #define LevelCount_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define LevelCount_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << LevelCount_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define LevelCount_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << LevelCount_SYNCDSI_SHIFT))

    #define LevelCount_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << LevelCount_CTRL_MODE_SHIFT))
    #define LevelCount_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << LevelCount_CTRL_MODE_SHIFT))
    #define LevelCount_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << LevelCount_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define LevelCount_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define LevelCount_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define LevelCount_STATUS_TC_INT_MASK_SHIFT        (LevelCount_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define LevelCount_STATUS_CAPTURE_INT_MASK_SHIFT   (LevelCount_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define LevelCount_STATUS_TC                       ((uint8)((uint8)0x01u << LevelCount_STATUS_TC_SHIFT))
    #define LevelCount_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << LevelCount_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define LevelCount_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << LevelCount_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define LevelCount_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << LevelCount_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define LevelCount_STATUS              (* (reg8 *) LevelCount_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define LevelCount_STATUS_MASK         (* (reg8 *) LevelCount_TimerUDB_rstSts_stsreg__MASK_REG)
    #define LevelCount_STATUS_AUX_CTRL     (* (reg8 *) LevelCount_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define LevelCount_CONTROL             (* (reg8 *) LevelCount_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(LevelCount_Resolution <= 8u) /* 8-bit Timer */
        #define LevelCount_CAPTURE_LSB         (* (reg8 *) LevelCount_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define LevelCount_CAPTURE_LSB_PTR       ((reg8 *) LevelCount_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define LevelCount_PERIOD_LSB          (* (reg8 *) LevelCount_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define LevelCount_PERIOD_LSB_PTR        ((reg8 *) LevelCount_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define LevelCount_COUNTER_LSB         (* (reg8 *) LevelCount_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define LevelCount_COUNTER_LSB_PTR       ((reg8 *) LevelCount_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(LevelCount_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define LevelCount_CAPTURE_LSB         (* (reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define LevelCount_CAPTURE_LSB_PTR       ((reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define LevelCount_PERIOD_LSB          (* (reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define LevelCount_PERIOD_LSB_PTR        ((reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define LevelCount_COUNTER_LSB         (* (reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define LevelCount_COUNTER_LSB_PTR       ((reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define LevelCount_CAPTURE_LSB         (* (reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define LevelCount_CAPTURE_LSB_PTR       ((reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define LevelCount_PERIOD_LSB          (* (reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define LevelCount_PERIOD_LSB_PTR        ((reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define LevelCount_COUNTER_LSB         (* (reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define LevelCount_COUNTER_LSB_PTR       ((reg16 *) LevelCount_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(LevelCount_Resolution <= 24u)/* 24-bit Timer */
        #define LevelCount_CAPTURE_LSB         (* (reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define LevelCount_CAPTURE_LSB_PTR       ((reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define LevelCount_PERIOD_LSB          (* (reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define LevelCount_PERIOD_LSB_PTR        ((reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define LevelCount_COUNTER_LSB         (* (reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define LevelCount_COUNTER_LSB_PTR       ((reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define LevelCount_CAPTURE_LSB         (* (reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define LevelCount_CAPTURE_LSB_PTR       ((reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define LevelCount_PERIOD_LSB          (* (reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define LevelCount_PERIOD_LSB_PTR        ((reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define LevelCount_COUNTER_LSB         (* (reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define LevelCount_COUNTER_LSB_PTR       ((reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define LevelCount_CAPTURE_LSB         (* (reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define LevelCount_CAPTURE_LSB_PTR       ((reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define LevelCount_PERIOD_LSB          (* (reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define LevelCount_PERIOD_LSB_PTR        ((reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define LevelCount_COUNTER_LSB         (* (reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define LevelCount_COUNTER_LSB_PTR       ((reg32 *) LevelCount_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define LevelCount_COUNTER_LSB_PTR_8BIT       ((reg8 *) LevelCount_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (LevelCount_UsingHWCaptureCounter)
        #define LevelCount_CAP_COUNT              (*(reg8 *) LevelCount_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define LevelCount_CAP_COUNT_PTR          ( (reg8 *) LevelCount_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define LevelCount_CAPTURE_COUNT_CTRL     (*(reg8 *) LevelCount_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define LevelCount_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) LevelCount_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (LevelCount_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define LevelCount_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define LevelCount_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define LevelCount_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define LevelCount_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define LevelCount_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define LevelCount_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << LevelCount_CTRL_INTCNT_SHIFT))
    #define LevelCount_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << LevelCount_CTRL_TRIG_MODE_SHIFT))
    #define LevelCount_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << LevelCount_CTRL_TRIG_EN_SHIFT))
    #define LevelCount_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << LevelCount_CTRL_CAP_MODE_SHIFT))
    #define LevelCount_CTRL_ENABLE                    ((uint8)((uint8)0x01u << LevelCount_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define LevelCount_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define LevelCount_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_TC_INT_MASK_SHIFT       LevelCount_STATUS_TC_SHIFT
    #define LevelCount_STATUS_CAPTURE_INT_MASK_SHIFT  LevelCount_STATUS_CAPTURE_SHIFT
    #define LevelCount_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_FIFOFULL_INT_MASK_SHIFT LevelCount_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define LevelCount_STATUS_TC                      ((uint8)((uint8)0x01u << LevelCount_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define LevelCount_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << LevelCount_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define LevelCount_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << LevelCount_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define LevelCount_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << LevelCount_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define LevelCount_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << LevelCount_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define LevelCount_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << LevelCount_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define LevelCount_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << LevelCount_STATUS_FIFOFULL_SHIFT))

    #define LevelCount_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define LevelCount_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define LevelCount_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define LevelCount_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define LevelCount_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define LevelCount_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_LevelCount_H */


/* [] END OF FILE */
