/*******************************************************************************
* File Name: Shift_Reg.h
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


#if !defined(CY_SHIFTREG_Shift_Reg_H)
#define CY_SHIFTREG_Shift_Reg_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Shift_Reg_FIFO_SIZE          (4u)
#define Shift_Reg_USE_INPUT_FIFO     (0u)
#define Shift_Reg_USE_OUTPUT_FIFO    (0u)
#define Shift_Reg_SR_SIZE            (32u)


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

} Shift_Reg_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  Shift_Reg_Start(void)                              ;
void  Shift_Reg_Stop(void)                               ;
void  Shift_Reg_Init(void)                               ;
void  Shift_Reg_Enable(void)                             ;
void  Shift_Reg_RestoreConfig(void)                      ;
void  Shift_Reg_SaveConfig(void)                         ;
void  Shift_Reg_Sleep(void)                              ;
void  Shift_Reg_Wakeup(void)                             ;
void  Shift_Reg_EnableInt(void)                          ;
void  Shift_Reg_DisableInt(void)                         ;
void  Shift_Reg_SetIntMode(uint8 interruptSource)        ;
uint8 Shift_Reg_GetIntStatus(void)                       ;
void  Shift_Reg_WriteRegValue(uint32 shiftData) \
                                                                ;
uint32 Shift_Reg_ReadRegValue(void) ;
uint8    Shift_Reg_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != Shift_Reg_USE_INPUT_FIFO)
    cystatus Shift_Reg_WriteData(uint32 shiftData) \
                                                                ;
#endif /* (0u != Shift_Reg_USE_INPUT_FIFO) */

#if(0u != Shift_Reg_USE_OUTPUT_FIFO)
    uint32 Shift_Reg_ReadData(void) ;
#endif /* (0u != Shift_Reg_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 Shift_Reg_initVar;


/***************************************
*           API Constants
***************************************/

#define Shift_Reg_LOAD                   (0x01u)
#define Shift_Reg_STORE                  (0x02u)
#define Shift_Reg_RESET                  (0x04u)

#define Shift_Reg_IN_FIFO                (0x01u)
#define Shift_Reg_OUT_FIFO               (0x02u)

#define Shift_Reg_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define Shift_Reg_RET_FIFO_NOT_EMPTY     (0x01u)

#define Shift_Reg_RET_FIFO_PARTIAL       (0x01u)
#define Shift_Reg_RET_FIFO_EMPTY         (0x02u)
#define Shift_Reg_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Shift_Reg__LEFT 0
#define Shift_Reg__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define Shift_Reg_SR_MASK    (0xFFFFFFFFu) /* Unsigned is added to parameter */
#define Shift_Reg_INT_SRC    (0u)
#define Shift_Reg_DIRECTION  (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define Shift_Reg_SR_CONTROL_REG (* (reg8 *) \
                                           Shift_Reg_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define Shift_Reg_SR_CONTROL_PTR (  (reg8 *) \
                                           Shift_Reg_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define Shift_Reg_SR_STATUS_REG      (* (reg8 *) Shift_Reg_bSR_StsReg__STATUS_REG)
#define Shift_Reg_SR_STATUS_PTR      (  (reg8 *) Shift_Reg_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define Shift_Reg_SR_STATUS_MASK_REG (* (reg8 *) Shift_Reg_bSR_StsReg__MASK_REG)
#define Shift_Reg_SR_STATUS_MASK_PTR (  (reg8 *) Shift_Reg_bSR_StsReg__MASK_REG)

/* Aux control register */
#define Shift_Reg_SR_AUX_CONTROL_REG (* (reg8 *) Shift_Reg_bSR_StsReg__STATUS_AUX_CTL_REG)
#define Shift_Reg_SR_AUX_CONTROL_PTR (  (reg8 *) Shift_Reg_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define Shift_Reg_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define Shift_Reg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__F0_REG )

    #define Shift_Reg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__A0_REG )

    #define Shift_Reg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__A1_REG )

    #define Shift_Reg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__F1_REG )

#else
    #if(Shift_Reg_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define Shift_Reg_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__F0_REG )

        #define Shift_Reg_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__A0_REG )

        #define Shift_Reg_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__A1_REG )

        #define Shift_Reg_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__F1_REG )

    #elif(Shift_Reg_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define Shift_Reg_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  Shift_Reg_bSR_sC32_BShiftRegDp_u0__16BIT_F0_REG )

        #define Shift_Reg_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  Shift_Reg_bSR_sC32_BShiftRegDp_u0__16BIT_A0_REG )

        #define Shift_Reg_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  Shift_Reg_bSR_sC32_BShiftRegDp_u0__16BIT_A1_REG )

        #define Shift_Reg_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  Shift_Reg_bSR_sC32_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(Shift_Reg_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define Shift_Reg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__F0_REG )

        #define Shift_Reg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__A0_REG )

        #define Shift_Reg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__A1_REG )

        #define Shift_Reg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        Shift_Reg_bSR_sC32_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define Shift_Reg_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  Shift_Reg_bSR_sC32_BShiftRegDp_u0__32BIT_F0_REG )

        #define Shift_Reg_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  Shift_Reg_bSR_sC32_BShiftRegDp_u0__32BIT_A0_REG )

        #define Shift_Reg_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  Shift_Reg_bSR_sC32_BShiftRegDp_u0__32BIT_A1_REG )

        #define Shift_Reg_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  Shift_Reg_bSR_sC32_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (Shift_Reg_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define Shift_Reg_INTERRUPTS_ENABLE      (0x10u)
#define Shift_Reg_LOAD_INT_EN            (0x01u)
#define Shift_Reg_STORE_INT_EN           (0x02u)
#define Shift_Reg_RESET_INT_EN           (0x04u)
#define Shift_Reg_CLK_EN                 (0x01u)

#define Shift_Reg_RESET_INT_EN_MASK      (0xFBu)
#define Shift_Reg_LOAD_INT_EN_MASK       (0xFEu)
#define Shift_Reg_STORE_INT_EN_MASK      (0xFDu)
#define Shift_Reg_INTS_EN_MASK           (0x07u)

#define Shift_Reg_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != Shift_Reg_USE_INPUT_FIFO)

    #define Shift_Reg_IN_FIFO_MASK       (0x18u)

    #define Shift_Reg_IN_FIFO_FULL       (0x00u)
    #define Shift_Reg_IN_FIFO_EMPTY      (0x01u)
    #define Shift_Reg_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define Shift_Reg_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != Shift_Reg_USE_INPUT_FIFO) */

#define Shift_Reg_OUT_FIFO_MASK          (0x60u)

#define Shift_Reg_OUT_FIFO_EMPTY         (0x00u)
#define Shift_Reg_OUT_FIFO_FULL          (0x01u)
#define Shift_Reg_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define Shift_Reg_OUT_FIFO_NOT_EMPTY     (0x02u)

#define Shift_Reg_IN_FIFO_SHIFT_MASK     (0x03u)
#define Shift_Reg_OUT_FIFO_SHIFT_MASK    (0x05u)

#define Shift_Reg_DISABLED               (0u)
#define Shift_Reg_DEFAULT_A0             (0u)
#define Shift_Reg_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define Shift_Reg_IS_ENABLED         (0u != (Shift_Reg_SR_CONTROL & Shift_Reg_CLK_EN))

#define Shift_Reg_GET_OUT_FIFO_STS   ((Shift_Reg_SR_STATUS & Shift_Reg_OUT_FIFO_MASK) >> \
                                              Shift_Reg_OUT_FIFO_SHIFT_MASK)

#define Shift_Reg_GET_IN_FIFO_STS    ((Shift_Reg_SR_STATUS & Shift_Reg_IN_FIFO_MASK)  >> \
                                              Shift_Reg_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define Shift_Reg_SR_CONTROL     (Shift_Reg_SR_CONTROL_REG)
#define Shift_Reg_SR_STATUS      (Shift_Reg_SR_STATUS_REG)
#define Shift_Reg_SR_STATUS_MASK (Shift_Reg_SR_STATUS_MASK_REG)
#define Shift_Reg_SR_AUX_CONTROL (Shift_Reg_SR_AUX_CONTROL_REG)

#define Shift_Reg_IN_FIFO_SHFT_MASK  (Shift_Reg_IN_FIFO_SHIFT_MASK)
#define Shift_Reg_OUT_FIFO_SHFT_MASK (Shift_Reg_OUT_FIFO_SHFIT_MASK)

#define Shift_Reg_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_Shift_Reg_H) */


/* [] END OF FILE */
