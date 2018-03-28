/*******************************************************************************
* File Name: HighF_ShiftReg2.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_HighF_ShiftReg2_H)
#define CY_SHIFTREG_HighF_ShiftReg2_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define HighF_ShiftReg2_FIFO_SIZE          (4u)
#define HighF_ShiftReg2_USE_INPUT_FIFO     (0u)
#define HighF_ShiftReg2_USE_OUTPUT_FIFO    (0u)
#define HighF_ShiftReg2_SR_SIZE            (32u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint32 saveSrA0Reg;
    uint32 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint32 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} HighF_ShiftReg2_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  HighF_ShiftReg2_Start(void)                              ;
void  HighF_ShiftReg2_Stop(void)                               ;
void  HighF_ShiftReg2_Init(void)                               ;
void  HighF_ShiftReg2_Enable(void)                             ;
void  HighF_ShiftReg2_RestoreConfig(void)                      ;
void  HighF_ShiftReg2_SaveConfig(void)                         ;
void  HighF_ShiftReg2_Sleep(void)                              ;
void  HighF_ShiftReg2_Wakeup(void)                             ;
void  HighF_ShiftReg2_EnableInt(void)                          ;
void  HighF_ShiftReg2_DisableInt(void)                         ;
void  HighF_ShiftReg2_SetIntMode(uint8 interruptSource)        ;
uint8 HighF_ShiftReg2_GetIntStatus(void)                       ;
void  HighF_ShiftReg2_WriteRegValue(uint32 shiftData) \
                                                                ;
uint32 HighF_ShiftReg2_ReadRegValue(void) ;
uint8    HighF_ShiftReg2_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != HighF_ShiftReg2_USE_INPUT_FIFO)
    cystatus HighF_ShiftReg2_WriteData(uint32 shiftData) \
                                                                ;
#endif /* (0u != HighF_ShiftReg2_USE_INPUT_FIFO) */

#if(0u != HighF_ShiftReg2_USE_OUTPUT_FIFO)
    uint32 HighF_ShiftReg2_ReadData(void) ;
#endif /* (0u != HighF_ShiftReg2_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 HighF_ShiftReg2_initVar;


/***************************************
*           API Constants
***************************************/

#define HighF_ShiftReg2_LOAD                   (0x01u)
#define HighF_ShiftReg2_STORE                  (0x02u)
#define HighF_ShiftReg2_RESET                  (0x04u)

#define HighF_ShiftReg2_IN_FIFO                (0x01u)
#define HighF_ShiftReg2_OUT_FIFO               (0x02u)

#define HighF_ShiftReg2_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define HighF_ShiftReg2_RET_FIFO_NOT_EMPTY     (0x01u)

#define HighF_ShiftReg2_RET_FIFO_PARTIAL       (0x01u)
#define HighF_ShiftReg2_RET_FIFO_EMPTY         (0x02u)
#define HighF_ShiftReg2_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define HighF_ShiftReg2__LEFT 0
#define HighF_ShiftReg2__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define HighF_ShiftReg2_SR_MASK    (0xFFFFFFFFu) /* Unsigned is added to parameter */
#define HighF_ShiftReg2_INT_SRC    (0u)
#define HighF_ShiftReg2_DIRECTION  (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define HighF_ShiftReg2_SR_CONTROL_REG (* (reg8 *) \
                                           HighF_ShiftReg2_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define HighF_ShiftReg2_SR_CONTROL_PTR (  (reg8 *) \
                                           HighF_ShiftReg2_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define HighF_ShiftReg2_SR_STATUS_REG      (* (reg8 *) HighF_ShiftReg2_bSR_StsReg__STATUS_REG)
#define HighF_ShiftReg2_SR_STATUS_PTR      (  (reg8 *) HighF_ShiftReg2_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define HighF_ShiftReg2_SR_STATUS_MASK_REG (* (reg8 *) HighF_ShiftReg2_bSR_StsReg__MASK_REG)
#define HighF_ShiftReg2_SR_STATUS_MASK_PTR (  (reg8 *) HighF_ShiftReg2_bSR_StsReg__MASK_REG)

/* Aux control register */
#define HighF_ShiftReg2_SR_AUX_CONTROL_REG (* (reg8 *) HighF_ShiftReg2_bSR_StsReg__STATUS_AUX_CTL_REG)
#define HighF_ShiftReg2_SR_AUX_CONTROL_PTR (  (reg8 *) HighF_ShiftReg2_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define HighF_ShiftReg2_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define HighF_ShiftReg2_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__F0_REG )

    #define HighF_ShiftReg2_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__A0_REG )

    #define HighF_ShiftReg2_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__A1_REG )

    #define HighF_ShiftReg2_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__F1_REG )

#else
    #if(HighF_ShiftReg2_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define HighF_ShiftReg2_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__F0_REG )

        #define HighF_ShiftReg2_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__A0_REG )

        #define HighF_ShiftReg2_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__A1_REG )

        #define HighF_ShiftReg2_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__F1_REG )

    #elif(HighF_ShiftReg2_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define HighF_ShiftReg2_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__16BIT_F0_REG )

        #define HighF_ShiftReg2_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__16BIT_A0_REG )

        #define HighF_ShiftReg2_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__16BIT_A1_REG )

        #define HighF_ShiftReg2_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(HighF_ShiftReg2_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define HighF_ShiftReg2_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__F0_REG )

        #define HighF_ShiftReg2_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__A0_REG )

        #define HighF_ShiftReg2_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__A1_REG )

        #define HighF_ShiftReg2_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define HighF_ShiftReg2_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__32BIT_F0_REG )

        #define HighF_ShiftReg2_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__32BIT_A0_REG )

        #define HighF_ShiftReg2_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__32BIT_A1_REG )

        #define HighF_ShiftReg2_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  HighF_ShiftReg2_bSR_sC32_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (HighF_ShiftReg2_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define HighF_ShiftReg2_INTERRUPTS_ENABLE      (0x10u)
#define HighF_ShiftReg2_LOAD_INT_EN            (0x01u)
#define HighF_ShiftReg2_STORE_INT_EN           (0x02u)
#define HighF_ShiftReg2_RESET_INT_EN           (0x04u)
#define HighF_ShiftReg2_CLK_EN                 (0x01u)

#define HighF_ShiftReg2_RESET_INT_EN_MASK      (0xFBu)
#define HighF_ShiftReg2_LOAD_INT_EN_MASK       (0xFEu)
#define HighF_ShiftReg2_STORE_INT_EN_MASK      (0xFDu)
#define HighF_ShiftReg2_INTS_EN_MASK           (0x07u)

#define HighF_ShiftReg2_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != HighF_ShiftReg2_USE_INPUT_FIFO)

    #define HighF_ShiftReg2_IN_FIFO_MASK       (0x18u)

    #define HighF_ShiftReg2_IN_FIFO_FULL       (0x00u)
    #define HighF_ShiftReg2_IN_FIFO_EMPTY      (0x01u)
    #define HighF_ShiftReg2_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define HighF_ShiftReg2_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != HighF_ShiftReg2_USE_INPUT_FIFO) */

#define HighF_ShiftReg2_OUT_FIFO_MASK          (0x60u)

#define HighF_ShiftReg2_OUT_FIFO_EMPTY         (0x00u)
#define HighF_ShiftReg2_OUT_FIFO_FULL          (0x01u)
#define HighF_ShiftReg2_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define HighF_ShiftReg2_OUT_FIFO_NOT_EMPTY     (0x02u)

#define HighF_ShiftReg2_IN_FIFO_SHIFT_MASK     (0x03u)
#define HighF_ShiftReg2_OUT_FIFO_SHIFT_MASK    (0x05u)

#define HighF_ShiftReg2_DISABLED               (0u)
#define HighF_ShiftReg2_DEFAULT_A0             (0u)
#define HighF_ShiftReg2_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define HighF_ShiftReg2_IS_ENABLED         (0u != (HighF_ShiftReg2_SR_CONTROL & HighF_ShiftReg2_CLK_EN))

#define HighF_ShiftReg2_GET_OUT_FIFO_STS   ((HighF_ShiftReg2_SR_STATUS & HighF_ShiftReg2_OUT_FIFO_MASK) >> \
                                              HighF_ShiftReg2_OUT_FIFO_SHIFT_MASK)

#define HighF_ShiftReg2_GET_IN_FIFO_STS    ((HighF_ShiftReg2_SR_STATUS & HighF_ShiftReg2_IN_FIFO_MASK)  >> \
                                              HighF_ShiftReg2_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define HighF_ShiftReg2_SR_CONTROL     (HighF_ShiftReg2_SR_CONTROL_REG)
#define HighF_ShiftReg2_SR_STATUS      (HighF_ShiftReg2_SR_STATUS_REG)
#define HighF_ShiftReg2_SR_STATUS_MASK (HighF_ShiftReg2_SR_STATUS_MASK_REG)
#define HighF_ShiftReg2_SR_AUX_CONTROL (HighF_ShiftReg2_SR_AUX_CONTROL_REG)

#define HighF_ShiftReg2_IN_FIFO_SHFT_MASK  (HighF_ShiftReg2_IN_FIFO_SHIFT_MASK)
#define HighF_ShiftReg2_OUT_FIFO_SHFT_MASK (HighF_ShiftReg2_OUT_FIFO_SHFIT_MASK)

#define HighF_ShiftReg2_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_HighF_ShiftReg2_H) */


/* [] END OF FILE */
