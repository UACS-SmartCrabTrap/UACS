/*******************************************************************************
* File Name: LevelCount.h  
* Version 3.0
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
    
#if !defined(CY_COUNTER_LevelCount_H)
#define CY_COUNTER_LevelCount_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 LevelCount_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed LevelCount_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef LevelCount_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* LevelCount_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define LevelCount_Resolution            16u
#define LevelCount_UsingFixedFunction    1u
#define LevelCount_ControlRegRemoved     0u
#define LevelCount_COMPARE_MODE_SOFTWARE 0u
#define LevelCount_CAPTURE_MODE_SOFTWARE 0u
#define LevelCount_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    uint16 CounterUdb;         /* Current Counter Value */

    #if (!LevelCount_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!LevelCount_ControlRegRemoved) */

}LevelCount_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    LevelCount_Start(void) ;
void    LevelCount_Stop(void) ;
void    LevelCount_SetInterruptMode(uint8 interruptsMask) ;
uint8   LevelCount_ReadStatusRegister(void) ;
#define LevelCount_GetInterruptSource() LevelCount_ReadStatusRegister()
#if(!LevelCount_ControlRegRemoved)
    uint8   LevelCount_ReadControlRegister(void) ;
    void    LevelCount_WriteControlRegister(uint8 control) \
        ;
#endif /* (!LevelCount_ControlRegRemoved) */
#if (!(LevelCount_UsingFixedFunction && (CY_PSOC5A)))
    void    LevelCount_WriteCounter(uint16 counter) \
            ; 
#endif /* (!(LevelCount_UsingFixedFunction && (CY_PSOC5A))) */
uint16  LevelCount_ReadCounter(void) ;
uint16  LevelCount_ReadCapture(void) ;
void    LevelCount_WritePeriod(uint16 period) \
    ;
uint16  LevelCount_ReadPeriod( void ) ;
#if (!LevelCount_UsingFixedFunction)
    void    LevelCount_WriteCompare(uint16 compare) \
        ;
    uint16  LevelCount_ReadCompare( void ) \
        ;
#endif /* (!LevelCount_UsingFixedFunction) */

#if (LevelCount_COMPARE_MODE_SOFTWARE)
    void    LevelCount_SetCompareMode(uint8 compareMode) ;
#endif /* (LevelCount_COMPARE_MODE_SOFTWARE) */
#if (LevelCount_CAPTURE_MODE_SOFTWARE)
    void    LevelCount_SetCaptureMode(uint8 captureMode) ;
#endif /* (LevelCount_CAPTURE_MODE_SOFTWARE) */
void LevelCount_ClearFIFO(void)     ;
void LevelCount_Init(void)          ;
void LevelCount_Enable(void)        ;
void LevelCount_SaveConfig(void)    ;
void LevelCount_RestoreConfig(void) ;
void LevelCount_Sleep(void)         ;
void LevelCount_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define LevelCount__B_COUNTER__LESS_THAN 1
#define LevelCount__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define LevelCount__B_COUNTER__EQUAL 0
#define LevelCount__B_COUNTER__GREATER_THAN 3
#define LevelCount__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define LevelCount__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define LevelCount_CMP_MODE_LT 1u
#define LevelCount_CMP_MODE_LTE 2u
#define LevelCount_CMP_MODE_EQ 0u
#define LevelCount_CMP_MODE_GT 3u
#define LevelCount_CMP_MODE_GTE 4u
#define LevelCount_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define LevelCount__B_COUNTER__NONE 0
#define LevelCount__B_COUNTER__RISING_EDGE 1
#define LevelCount__B_COUNTER__FALLING_EDGE 2
#define LevelCount__B_COUNTER__EITHER_EDGE 3
#define LevelCount__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define LevelCount_CAP_MODE_NONE 0u
#define LevelCount_CAP_MODE_RISE 1u
#define LevelCount_CAP_MODE_FALL 2u
#define LevelCount_CAP_MODE_BOTH 3u
#define LevelCount_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define LevelCount_CAPTURE_MODE_CONF       0u
#define LevelCount_INIT_PERIOD_VALUE       255u
#define LevelCount_INIT_COUNTER_VALUE      255u
#if (LevelCount_UsingFixedFunction)
#define LevelCount_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << LevelCount_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define LevelCount_INIT_COMPARE_VALUE      128u
#define LevelCount_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << LevelCount_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << LevelCount_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << LevelCount_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << LevelCount_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << LevelCount_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define LevelCount_DEFAULT_COMPARE_MODE    1u

#if( 0 != LevelCount_CAPTURE_MODE_CONF)
    #define LevelCount_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << LevelCount_CTRL_CAPMODE0_SHIFT))
#else    
    #define LevelCount_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != LevelCount_CAPTURE_MODE_CONF) */

#endif /* (LevelCount_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (LevelCount_UsingFixedFunction)
    #define LevelCount_STATICCOUNT_LSB     (*(reg16 *) LevelCount_CounterHW__CAP0 )
    #define LevelCount_STATICCOUNT_LSB_PTR ( (reg16 *) LevelCount_CounterHW__CAP0 )
    #define LevelCount_PERIOD_LSB          (*(reg16 *) LevelCount_CounterHW__PER0 )
    #define LevelCount_PERIOD_LSB_PTR      ( (reg16 *) LevelCount_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define LevelCount_COMPARE_LSB         (*(reg16 *) LevelCount_CounterHW__CNT_CMP0 )
    #define LevelCount_COMPARE_LSB_PTR     ( (reg16 *) LevelCount_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define LevelCount_COUNTER_LSB         (*(reg16 *) LevelCount_CounterHW__CNT_CMP0 )
    #define LevelCount_COUNTER_LSB_PTR     ( (reg16 *) LevelCount_CounterHW__CNT_CMP0 )
    #define LevelCount_RT1                 (*(reg8 *) LevelCount_CounterHW__RT1)
    #define LevelCount_RT1_PTR             ( (reg8 *) LevelCount_CounterHW__RT1)
#else
    
    #if (LevelCount_Resolution <= 8u) /* 8-bit Counter */
    
        #define LevelCount_STATICCOUNT_LSB     (*(reg8 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define LevelCount_STATICCOUNT_LSB_PTR ( (reg8 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define LevelCount_PERIOD_LSB          (*(reg8 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define LevelCount_PERIOD_LSB_PTR      ( (reg8 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define LevelCount_COMPARE_LSB         (*(reg8 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define LevelCount_COMPARE_LSB_PTR     ( (reg8 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define LevelCount_COUNTER_LSB         (*(reg8 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define LevelCount_COUNTER_LSB_PTR     ( (reg8 *)\
            LevelCount_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #elif(LevelCount_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define LevelCount_STATICCOUNT_LSB     (*(reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define LevelCount_STATICCOUNT_LSB_PTR ( (reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define LevelCount_PERIOD_LSB          (*(reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define LevelCount_PERIOD_LSB_PTR      ( (reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define LevelCount_COMPARE_LSB         (*(reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define LevelCount_COMPARE_LSB_PTR     ( (reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define LevelCount_COUNTER_LSB         (*(reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define LevelCount_COUNTER_LSB_PTR     ( (reg16 *)\
                LevelCount_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define LevelCount_STATICCOUNT_LSB     (*(reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define LevelCount_STATICCOUNT_LSB_PTR ( (reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define LevelCount_PERIOD_LSB          (*(reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define LevelCount_PERIOD_LSB_PTR      ( (reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define LevelCount_COMPARE_LSB         (*(reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define LevelCount_COMPARE_LSB_PTR     ( (reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define LevelCount_COUNTER_LSB         (*(reg16 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )  
            #define LevelCount_COUNTER_LSB_PTR     ( (reg16 *)\
                LevelCount_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(LevelCount_Resolution <= 24u) /* 24-bit Counter */
        
        #define LevelCount_STATICCOUNT_LSB     (*(reg32 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define LevelCount_STATICCOUNT_LSB_PTR ( (reg32 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define LevelCount_PERIOD_LSB          (*(reg32 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define LevelCount_PERIOD_LSB_PTR      ( (reg32 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define LevelCount_COMPARE_LSB         (*(reg32 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define LevelCount_COMPARE_LSB_PTR     ( (reg32 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define LevelCount_COUNTER_LSB         (*(reg32 *) \
            LevelCount_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define LevelCount_COUNTER_LSB_PTR     ( (reg32 *)\
            LevelCount_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define LevelCount_STATICCOUNT_LSB     (*(reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define LevelCount_STATICCOUNT_LSB_PTR ( (reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define LevelCount_PERIOD_LSB          (*(reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define LevelCount_PERIOD_LSB_PTR      ( (reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define LevelCount_COMPARE_LSB         (*(reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define LevelCount_COMPARE_LSB_PTR     ( (reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define LevelCount_COUNTER_LSB         (*(reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define LevelCount_COUNTER_LSB_PTR     ( (reg32 *)\
                LevelCount_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define LevelCount_STATICCOUNT_LSB     (*(reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define LevelCount_STATICCOUNT_LSB_PTR ( (reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define LevelCount_PERIOD_LSB          (*(reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define LevelCount_PERIOD_LSB_PTR      ( (reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define LevelCount_COMPARE_LSB         (*(reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define LevelCount_COMPARE_LSB_PTR     ( (reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define LevelCount_COUNTER_LSB         (*(reg32 *) \
                LevelCount_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )  
            #define LevelCount_COUNTER_LSB_PTR     ( (reg32 *)\
                LevelCount_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define LevelCount_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                LevelCount_CounterUDB_sC16_counterdp_u0__A0_REG )
				
    #define LevelCount_AUX_CONTROLDP0 \
        (*(reg8 *) LevelCount_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #define LevelCount_AUX_CONTROLDP0_PTR \
        ( (reg8 *) LevelCount_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (LevelCount_Resolution == 16 || LevelCount_Resolution == 24 || LevelCount_Resolution == 32)
       #define LevelCount_AUX_CONTROLDP1 \
           (*(reg8 *) LevelCount_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
       #define LevelCount_AUX_CONTROLDP1_PTR \
           ( (reg8 *) LevelCount_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (LevelCount_Resolution == 16 || LevelCount_Resolution == 24 || LevelCount_Resolution == 32) */
    
    #if (LevelCount_Resolution == 24 || LevelCount_Resolution == 32)
       #define LevelCount_AUX_CONTROLDP2 \
           (*(reg8 *) LevelCount_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
       #define LevelCount_AUX_CONTROLDP2_PTR \
           ( (reg8 *) LevelCount_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (LevelCount_Resolution == 24 || LevelCount_Resolution == 32) */
    
    #if (LevelCount_Resolution == 32)
       #define LevelCount_AUX_CONTROLDP3 \
           (*(reg8 *) LevelCount_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
       #define LevelCount_AUX_CONTROLDP3_PTR \
           ( (reg8 *) LevelCount_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (LevelCount_Resolution == 32) */

#endif  /* (LevelCount_UsingFixedFunction) */

#if (LevelCount_UsingFixedFunction)
    #define LevelCount_STATUS         (*(reg8 *) LevelCount_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define LevelCount_STATUS_MASK             (*(reg8 *) LevelCount_CounterHW__SR0 )
    #define LevelCount_STATUS_MASK_PTR         ( (reg8 *) LevelCount_CounterHW__SR0 )
    #define LevelCount_CONTROL                 (*(reg8 *) LevelCount_CounterHW__CFG0)
    #define LevelCount_CONTROL_PTR             ( (reg8 *) LevelCount_CounterHW__CFG0)
    #define LevelCount_CONTROL2                (*(reg8 *) LevelCount_CounterHW__CFG1)
    #define LevelCount_CONTROL2_PTR            ( (reg8 *) LevelCount_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define LevelCount_CONTROL3       (*(reg8 *) LevelCount_CounterHW__CFG2)
        #define LevelCount_CONTROL3_PTR   ( (reg8 *) LevelCount_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define LevelCount_GLOBAL_ENABLE           (*(reg8 *) LevelCount_CounterHW__PM_ACT_CFG)
    #define LevelCount_GLOBAL_ENABLE_PTR       ( (reg8 *) LevelCount_CounterHW__PM_ACT_CFG)
    #define LevelCount_GLOBAL_STBY_ENABLE      (*(reg8 *) LevelCount_CounterHW__PM_STBY_CFG)
    #define LevelCount_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) LevelCount_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define LevelCount_BLOCK_EN_MASK          LevelCount_CounterHW__PM_ACT_MSK
    #define LevelCount_BLOCK_STBY_EN_MASK     LevelCount_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define LevelCount_CTRL_ENABLE_SHIFT      0x00u
    #define LevelCount_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define LevelCount_CTRL_ENABLE            ((uint8)((uint8)0x01u << LevelCount_CTRL_ENABLE_SHIFT))         
    #define LevelCount_ONESHOT                ((uint8)((uint8)0x01u << LevelCount_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define LevelCount_CTRL_MODE_SHIFT        0x01u    
        #define LevelCount_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << LevelCount_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define LevelCount_CTRL_MODE_SHIFT        0x00u    
        #define LevelCount_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << LevelCount_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define LevelCount_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define LevelCount_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << LevelCount_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define LevelCount_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define LevelCount_STATUS_ZERO_INT_EN_MASK_SHIFT      (LevelCount_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define LevelCount_STATUS_ZERO            ((uint8)((uint8)0x01u << LevelCount_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define LevelCount_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)LevelCount_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define LevelCount_RT1_SHIFT            0x04u
    #define LevelCount_RT1_MASK             ((uint8)((uint8)0x03u << LevelCount_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define LevelCount_SYNC                 ((uint8)((uint8)0x03u << LevelCount_RT1_SHIFT))
    #define LevelCount_SYNCDSI_SHIFT        0x00u
    #define LevelCount_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << LevelCount_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define LevelCount_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << LevelCount_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !LevelCount_UsingFixedFunction */
    #define LevelCount_STATUS               (* (reg8 *) LevelCount_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define LevelCount_STATUS_PTR           (  (reg8 *) LevelCount_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define LevelCount_STATUS_MASK          (* (reg8 *) LevelCount_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define LevelCount_STATUS_MASK_PTR      (  (reg8 *) LevelCount_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define LevelCount_STATUS_AUX_CTRL      (*(reg8 *) LevelCount_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define LevelCount_STATUS_AUX_CTRL_PTR  ( (reg8 *) LevelCount_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define LevelCount_CONTROL              (* (reg8 *) LevelCount_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define LevelCount_CONTROL_PTR          (  (reg8 *) LevelCount_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define LevelCount_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define LevelCount_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define LevelCount_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define LevelCount_CTRL_CMPMODE_MASK      0x07u 
    #define LevelCount_CTRL_CAPMODE_MASK      0x03u  
    #define LevelCount_CTRL_RESET             ((uint8)((uint8)0x01u << LevelCount_CTRL_RESET_SHIFT))  
    #define LevelCount_CTRL_ENABLE            ((uint8)((uint8)0x01u << LevelCount_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define LevelCount_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define LevelCount_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define LevelCount_STATUS_CMP_INT_EN_MASK_SHIFT       LevelCount_STATUS_CMP_SHIFT       
    #define LevelCount_STATUS_ZERO_INT_EN_MASK_SHIFT      LevelCount_STATUS_ZERO_SHIFT      
    #define LevelCount_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  LevelCount_STATUS_OVERFLOW_SHIFT  
    #define LevelCount_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT LevelCount_STATUS_UNDERFLOW_SHIFT 
    #define LevelCount_STATUS_CAPTURE_INT_EN_MASK_SHIFT   LevelCount_STATUS_CAPTURE_SHIFT   
    #define LevelCount_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  LevelCount_STATUS_FIFOFULL_SHIFT  
    #define LevelCount_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  LevelCount_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define LevelCount_STATUS_CMP             ((uint8)((uint8)0x01u << LevelCount_STATUS_CMP_SHIFT))  
    #define LevelCount_STATUS_ZERO            ((uint8)((uint8)0x01u << LevelCount_STATUS_ZERO_SHIFT)) 
    #define LevelCount_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << LevelCount_STATUS_OVERFLOW_SHIFT)) 
    #define LevelCount_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << LevelCount_STATUS_UNDERFLOW_SHIFT)) 
    #define LevelCount_STATUS_CAPTURE         ((uint8)((uint8)0x01u << LevelCount_STATUS_CAPTURE_SHIFT)) 
    #define LevelCount_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << LevelCount_STATUS_FIFOFULL_SHIFT))
    #define LevelCount_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << LevelCount_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define LevelCount_STATUS_CMP_INT_EN_MASK            LevelCount_STATUS_CMP                    
    #define LevelCount_STATUS_ZERO_INT_EN_MASK           LevelCount_STATUS_ZERO            
    #define LevelCount_STATUS_OVERFLOW_INT_EN_MASK       LevelCount_STATUS_OVERFLOW        
    #define LevelCount_STATUS_UNDERFLOW_INT_EN_MASK      LevelCount_STATUS_UNDERFLOW       
    #define LevelCount_STATUS_CAPTURE_INT_EN_MASK        LevelCount_STATUS_CAPTURE         
    #define LevelCount_STATUS_FIFOFULL_INT_EN_MASK       LevelCount_STATUS_FIFOFULL        
    #define LevelCount_STATUS_FIFONEMP_INT_EN_MASK       LevelCount_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define LevelCount_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define LevelCount_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define LevelCount_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define LevelCount_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define LevelCount_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define LevelCount_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* LevelCount_UsingFixedFunction */

#endif  /* CY_COUNTER_LevelCount_H */


/* [] END OF FILE */

