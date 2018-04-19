/*******************************************************************************
* File Name: HighF_OutComp.c
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Analog Comparator User Module.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COMP_HighF_OutComp_H) 
#define CY_COMP_HighF_OutComp_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h" 


#define HighF_OutComp_RECALMODE (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Comp_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
   /* uint8 compCRReg; */
}HighF_OutComp_backupStruct;

#if (CY_PSOC5A)
    /* Stop API changes for PSoC5A */
    typedef struct
    {
        uint8 compCRReg;
    }   HighF_OutComp_LOWPOWER_BACKUP_STRUCT;
#endif /* CY_PSOC5A */

/* component init state */
extern uint8 HighF_OutComp_initVar;


/**************************************
*        Function Prototypes 
**************************************/

void    HighF_OutComp_Start(void)                  ;
void    HighF_OutComp_Stop(void)                   ;
void    HighF_OutComp_SetSpeed(uint8 speed)        ;
uint8   HighF_OutComp_GetCompare(void)             ;
uint16  HighF_OutComp_ZeroCal(void)                ;
void    HighF_OutComp_LoadTrim(uint16 trimVal)     ;
void HighF_OutComp_Init(void)                      ; 
void HighF_OutComp_Enable(void)                    ;
void HighF_OutComp_SaveConfig(void)                ;
void HighF_OutComp_RestoreConfig(void)             ;
void HighF_OutComp_Sleep(void)                     ;
void HighF_OutComp_Wakeup(void)                    ;
/* Below APIs are valid only for PSoC3, PSoC5LP silicons.*/
#if (CY_PSOC3 || CY_PSOC5LP) 
    void HighF_OutComp_PwrDwnOverrideEnable(void)  ;
    void HighF_OutComp_PwrDwnOverrideDisable(void) ;
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*           API Constants        
**************************************/

/* Power constants for SetSpeed() function */
#define HighF_OutComp_SLOWSPEED   (0x00u)
#define HighF_OutComp_HIGHSPEED   (0x01u)
#define HighF_OutComp_LOWPOWER    (0x02u)


/**************************************
*           Parameter Defaults        
**************************************/

#define HighF_OutComp_DEFAULT_SPEED       (2u) 
#define HighF_OutComp_DEFAULT_HYSTERESIS  (1u)
#define HighF_OutComp_DEFAULT_POLARITY    (0u)
#define HighF_OutComp_DEFAULT_BYPASS_SYNC (1u)
#define HighF_OutComp_DEFAULT_PWRDWN_OVRD (0u)


/**************************************
*             Registers        
**************************************/
#define HighF_OutComp_CR_REG            (* (reg8 *) HighF_OutComp_ctComp__CR )               /* Config register */
#define HighF_OutComp_CR_PTR            (  (reg8 *) HighF_OutComp_ctComp__CR )
#define HighF_OutComp_CLK_REG           (* (reg8 *) HighF_OutComp_ctComp__CLK )  /* Comp clock control register */
#define HighF_OutComp_CLK_PTR           (  (reg8 *) HighF_OutComp_ctComp__CLK )
#define HighF_OutComp_SW0_REG           (* (reg8 *) HighF_OutComp_ctComp__SW0 )            /* Routing registers */
#define HighF_OutComp_SW0_PTR           (  (reg8 *) HighF_OutComp_ctComp__SW0 )
#define HighF_OutComp_SW2_REG           (* (reg8 *) HighF_OutComp_ctComp__SW2 )
#define HighF_OutComp_SW2_PTR           (  (reg8 *) HighF_OutComp_ctComp__SW2 )
#define HighF_OutComp_SW3_REG           (* (reg8 *) HighF_OutComp_ctComp__SW3 )
#define HighF_OutComp_SW3_PTR           (  (reg8 *) HighF_OutComp_ctComp__SW3 )
#define HighF_OutComp_SW4_REG           (* (reg8 *) HighF_OutComp_ctComp__SW4 )
#define HighF_OutComp_SW4_PTR           (  (reg8 *) HighF_OutComp_ctComp__SW4 )
#define HighF_OutComp_SW6_REG           (* (reg8 *) HighF_OutComp_ctComp__SW6 )
#define HighF_OutComp_SW6_PTR           (  (reg8 *) HighF_OutComp_ctComp__SW6 )

/* Trim registers */
/* PSoC5A */
#if (CY_PSOC5A)
    #define HighF_OutComp_TR_REG        (* (reg8 *) HighF_OutComp_ctComp__TR )                /* Trim registers */
    #define HighF_OutComp_TR_PTR        (  (reg8 *) HighF_OutComp_ctComp__TR )
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP) 
    #define HighF_OutComp_TR0_REG       (* (reg8 *) HighF_OutComp_ctComp__TR0 )/* Trim register for P-type load */
    #define HighF_OutComp_TR0_PTR       (  (reg8 *) HighF_OutComp_ctComp__TR0 ) 
    #define HighF_OutComp_TR1_REG       (* (reg8 *) HighF_OutComp_ctComp__TR1 )/* Trim register for N-type load */
    #define HighF_OutComp_TR1_PTR       (  (reg8 *) HighF_OutComp_ctComp__TR1 ) 
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define HighF_OutComp_WRK_REG           (* (reg8 *) HighF_OutComp_ctComp__WRK )    /* Working register - output */
#define HighF_OutComp_WRK_PTR           (  (reg8 *) HighF_OutComp_ctComp__WRK )
#define HighF_OutComp_PWRMGR_REG        (* (reg8 *) HighF_OutComp_ctComp__PM_ACT_CFG )  /* Active Power manager */
#define HighF_OutComp_PWRMGR_PTR        (  (reg8 *) HighF_OutComp_ctComp__PM_ACT_CFG )
#define HighF_OutComp_STBY_PWRMGR_REG   (* (reg8 *) HighF_OutComp_ctComp__PM_STBY_CFG )/* Standby Power manager */
#define HighF_OutComp_STBY_PWRMGR_PTR   (  (reg8 *) HighF_OutComp_ctComp__PM_STBY_CFG )

/*      Trim Locations      */
#define HighF_OutComp_ctComp__TRIM__TR0_HS_PTR     ((void CYFAR *) HighF_OutComp_ctComp__TRIM__TR0_HS)
#define HighF_OutComp_ctComp__TRIM__TR0_HS_REG     CY_GET_XTND_REG8(HighF_OutComp_ctComp__TRIM__TR0_HS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define HighF_OutComp_ctComp__TRIM__TR1_HS_PTR ((void CYFAR *) HighF_OutComp_ctComp__TRIM__TR1_HS)
    #define HighF_OutComp_ctComp__TRIM__TR1_HS_REG CY_GET_XTND_REG8(HighF_OutComp_ctComp__TRIM__TR1_HS_PTR)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */
#define HighF_OutComp_ctComp__TRIM__TR0_LS_PTR     ((void CYFAR *) ((uint32)HighF_OutComp_ctComp__TRIM__TR0 + 1u))
#define HighF_OutComp_ctComp__TRIM__TR0_LS_REG     CY_GET_XTND_REG8(HighF_OutComp_ctComp__TRIM__TR0_LS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define HighF_OutComp_ctComp__TRIM__TR1_LS_PTR ((void CYFAR *) ((uint32)HighF_OutComp_ctComp__TRIM__TR1 + 1u))
    #define HighF_OutComp_ctComp__TRIM__TR1_LS_REG CY_GET_XTND_REG8(HighF_OutComp_ctComp__TRIM__TR1_LS_PTR)
#endif /* CY_PSOC3 || CY_PSOC5LP */


/***************************************
*  Registers definitions
* for backward capability        
***************************************/
#define HighF_OutComp_CR                (* (reg8 *) HighF_OutComp_ctComp__CR )               /* Config register */
#define HighF_OutComp_CLK               (* (reg8 *) HighF_OutComp_ctComp__CLK )  /* Comp clock control register */
#define HighF_OutComp_SW0               (* (reg8 *) HighF_OutComp_ctComp__SW0 )            /* Routing registers */
#define HighF_OutComp_SW2               (* (reg8 *) HighF_OutComp_ctComp__SW2 )
#define HighF_OutComp_SW3               (* (reg8 *) HighF_OutComp_ctComp__SW3 )
#define HighF_OutComp_SW4               (* (reg8 *) HighF_OutComp_ctComp__SW4 )
#define HighF_OutComp_SW6               (* (reg8 *) HighF_OutComp_ctComp__SW6 )

/* Trim registers */
/* PSoC5A */
#if (CY_PSOC5A)
    #define HighF_OutComp_TR            (* (reg8 *) HighF_OutComp_ctComp__TR )                /* Trim registers */
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP) 
    #define HighF_OutComp_TR0           (* (reg8 *) HighF_OutComp_ctComp__TR0 )/* Trim register for P-type load */
    #define HighF_OutComp_TR1           (* (reg8 *) HighF_OutComp_ctComp__TR1 )/* Trim register for N-type load */
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define HighF_OutComp_WRK               (* (reg8 *) HighF_OutComp_ctComp__WRK )    /* Working register - output */
#define HighF_OutComp_PWRMGR            (* (reg8 *) HighF_OutComp_ctComp__PM_ACT_CFG )  /* Active Power manager */
#define HighF_OutComp_STBY_PWRMGR       (* (reg8 *) HighF_OutComp_ctComp__PM_STBY_CFG )/* Standby Power manager */

/*      Trim Locations      */
#define HighF_OutComp_HS_TRIM_TR0        CY_GET_XTND_REG8(HighF_OutComp_ctComp__TRIM__TR0_HS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define HighF_OutComp_HS_TRIM_TR1    CY_GET_XTND_REG8(HighF_OutComp_ctComp__TRIM__TR1_HS_PTR)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */
#define HighF_OutComp_LS_TRIM_TR0        CY_GET_XTND_REG8(HighF_OutComp_ctComp__TRIM__TR0_LS_PTR)
#if (CY_PSOC3 || CY_PSOC5LP)
    #define HighF_OutComp_LS_TRIM_TR1    CY_GET_XTND_REG8(HighF_OutComp_ctComp__TRIM__TR1_LS_PTR)
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*       Register Constants        
**************************************/

/* CR (Comp Control Register)             */
#define HighF_OutComp_CFG_MODE_MASK      (0x78u)
#define HighF_OutComp_FILTER_ON          (0x40u)
#define HighF_OutComp_HYST_OFF           (0x20u)
#define HighF_OutComp_CAL_ON             (0x10u)
#define HighF_OutComp_MX_AO              (0x08u)
#define HighF_OutComp_PWRDWN_OVRD        (0x04u)

#define HighF_OutComp_PWR_MODE_SHIFT     (0x00u)
#define HighF_OutComp_PWR_MODE_MASK      ((uint8)(0x03u << HighF_OutComp_PWR_MODE_SHIFT))
#define HighF_OutComp_PWR_MODE_SLOW      ((uint8)(0x00u << HighF_OutComp_PWR_MODE_SHIFT))
#define HighF_OutComp_PWR_MODE_FAST      ((uint8)(0x01u << HighF_OutComp_PWR_MODE_SHIFT))
#define HighF_OutComp_PWR_MODE_ULOW      ((uint8)(0x02u << HighF_OutComp_PWR_MODE_SHIFT))

/* CLK (Comp Clock Control Register)      */
#define HighF_OutComp_BYPASS_SYNC        (0x10u)
#define HighF_OutComp_SYNC_CLK_EN        (0x08u)
#define HighF_OutComp_SYNCCLK_MASK       (HighF_OutComp_BYPASS_SYNC | HighF_OutComp_SYNC_CLK_EN)

/* SW3 Routing Register definitions */
#define HighF_OutComp_CMP_SW3_INPCTL_MASK (0x09u)   /* SW3 bits for inP routing control */

/* TR (Comp Trim Register)     */
#define HighF_OutComp_DEFAULT_CMP_TRIM    (0x00u)

/* PSoC5A */
#if (CY_PSOC5A)
    #define HighF_OutComp_CMP_TRIM1_DIR   (0x08u)   /* Trim direction for N-type load for offset calibration */
    #define HighF_OutComp_CMP_TRIM1_MASK  (0x07u)   /* Trim for N-type load for offset calibration */
    #define HighF_OutComp_CMP_TRIM2_DIR   (0x80u)   /* Trim direction for P-type load for offset calibration */
    #define HighF_OutComp_CMP_TRIM2_MASK  (0x70u)   /* Trim for P-type load for offset calibration */
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP)
    #define HighF_OutComp_CMP_TR0_DIR     (0x10u)   /* Trim direction for N-type load for offset calibration */
    #define HighF_OutComp_CMP_TR0_MASK    (0x0Fu)   /* Trim for N-type load for offset calibration */
    #define HighF_OutComp_CMP_TR1_DIR     (0x10u)   /* Trim direction for P-type load for offset calibration */
    #define HighF_OutComp_CMP_TR1_MASK    (0x07u)   /* Trim for P-type load for offset calibration */ 
#endif /* CY_PSOC3 || CY_PSOC5LP */


/* WRK (Comp output working register)     */ 
#define HighF_OutComp_CMP_OUT_MASK       HighF_OutComp_ctComp__WRK_MASK /* Specific comparator out mask */

/* PM_ACT_CFG7 (Active Power Mode CFG Register)     */ 
#define HighF_OutComp_ACT_PWR_EN         HighF_OutComp_ctComp__PM_ACT_MSK /* Power enable mask */

/* PM_STBY_CFG7 (Standby Power Mode CFG Register)     */ 
#define HighF_OutComp_STBY_PWR_EN        HighF_OutComp_ctComp__PM_STBY_MSK /* Standby Power enable mask */

#if (CY_PSOC5A)
    /* For stop API changes mask to make the COMP register CR to 0X00  */
    #define HighF_OutComp_COMP_REG_CLR   (0x00u)
#endif /* CY_PSOC5A */

#endif /* CY_COMP_HighF_OutComp_H */


/* [] END OF FILE */
