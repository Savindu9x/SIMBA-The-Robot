/*******************************************************************************
* File Name: RobotArm_Servo.h
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

#if !defined(CY_PWM_RobotArm_Servo_H)
#define CY_PWM_RobotArm_Servo_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 RobotArm_Servo_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define RobotArm_Servo_Resolution                     (16u)
#define RobotArm_Servo_UsingFixedFunction             (0u)
#define RobotArm_Servo_DeadBandMode                   (0u)
#define RobotArm_Servo_KillModeMinTime                (0u)
#define RobotArm_Servo_KillMode                       (0u)
#define RobotArm_Servo_PWMMode                        (1u)
#define RobotArm_Servo_PWMModeIsCenterAligned         (0u)
#define RobotArm_Servo_DeadBandUsed                   (0u)
#define RobotArm_Servo_DeadBand2_4                    (0u)

#if !defined(RobotArm_Servo_PWMUDB_genblk8_stsreg__REMOVED)
    #define RobotArm_Servo_UseStatus                  (1u)
#else
    #define RobotArm_Servo_UseStatus                  (0u)
#endif /* !defined(RobotArm_Servo_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(RobotArm_Servo_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define RobotArm_Servo_UseControl                 (1u)
#else
    #define RobotArm_Servo_UseControl                 (0u)
#endif /* !defined(RobotArm_Servo_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define RobotArm_Servo_UseOneCompareMode              (0u)
#define RobotArm_Servo_MinimumKillTime                (1u)
#define RobotArm_Servo_EnableMode                     (0u)

#define RobotArm_Servo_CompareMode1SW                 (0u)
#define RobotArm_Servo_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define RobotArm_Servo__B_PWM__DISABLED 0
#define RobotArm_Servo__B_PWM__ASYNCHRONOUS 1
#define RobotArm_Servo__B_PWM__SINGLECYCLE 2
#define RobotArm_Servo__B_PWM__LATCHED 3
#define RobotArm_Servo__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define RobotArm_Servo__B_PWM__DBMDISABLED 0
#define RobotArm_Servo__B_PWM__DBM_2_4_CLOCKS 1
#define RobotArm_Servo__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define RobotArm_Servo__B_PWM__ONE_OUTPUT 0
#define RobotArm_Servo__B_PWM__TWO_OUTPUTS 1
#define RobotArm_Servo__B_PWM__DUAL_EDGE 2
#define RobotArm_Servo__B_PWM__CENTER_ALIGN 3
#define RobotArm_Servo__B_PWM__DITHER 5
#define RobotArm_Servo__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define RobotArm_Servo__B_PWM__LESS_THAN 1
#define RobotArm_Servo__B_PWM__LESS_THAN_OR_EQUAL 2
#define RobotArm_Servo__B_PWM__GREATER_THAN 3
#define RobotArm_Servo__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define RobotArm_Servo__B_PWM__EQUAL 0
#define RobotArm_Servo__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!RobotArm_Servo_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!RobotArm_Servo_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!RobotArm_Servo_PWMModeIsCenterAligned) */
        #if (RobotArm_Servo_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (RobotArm_Servo_UseStatus) */

        /* Backup for Deadband parameters */
        #if(RobotArm_Servo_DeadBandMode == RobotArm_Servo__B_PWM__DBM_256_CLOCKS || \
            RobotArm_Servo_DeadBandMode == RobotArm_Servo__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(RobotArm_Servo_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (RobotArm_Servo_KillModeMinTime) */

        /* Backup control register */
        #if(RobotArm_Servo_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (RobotArm_Servo_UseControl) */

    #endif /* (!RobotArm_Servo_UsingFixedFunction) */

}RobotArm_Servo_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    RobotArm_Servo_Start(void) ;
void    RobotArm_Servo_Stop(void) ;

#if (RobotArm_Servo_UseStatus || RobotArm_Servo_UsingFixedFunction)
    void  RobotArm_Servo_SetInterruptMode(uint8 interruptMode) ;
    uint8 RobotArm_Servo_ReadStatusRegister(void) ;
#endif /* (RobotArm_Servo_UseStatus || RobotArm_Servo_UsingFixedFunction) */

#define RobotArm_Servo_GetInterruptSource() RobotArm_Servo_ReadStatusRegister()

#if (RobotArm_Servo_UseControl)
    uint8 RobotArm_Servo_ReadControlRegister(void) ;
    void  RobotArm_Servo_WriteControlRegister(uint8 control)
          ;
#endif /* (RobotArm_Servo_UseControl) */

#if (RobotArm_Servo_UseOneCompareMode)
   #if (RobotArm_Servo_CompareMode1SW)
       void    RobotArm_Servo_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (RobotArm_Servo_CompareMode1SW) */
#else
    #if (RobotArm_Servo_CompareMode1SW)
        void    RobotArm_Servo_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (RobotArm_Servo_CompareMode1SW) */
    #if (RobotArm_Servo_CompareMode2SW)
        void    RobotArm_Servo_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (RobotArm_Servo_CompareMode2SW) */
#endif /* (RobotArm_Servo_UseOneCompareMode) */

#if (!RobotArm_Servo_UsingFixedFunction)
    uint16   RobotArm_Servo_ReadCounter(void) ;
    uint16 RobotArm_Servo_ReadCapture(void) ;

    #if (RobotArm_Servo_UseStatus)
            void RobotArm_Servo_ClearFIFO(void) ;
    #endif /* (RobotArm_Servo_UseStatus) */

    void    RobotArm_Servo_WriteCounter(uint16 counter)
            ;
#endif /* (!RobotArm_Servo_UsingFixedFunction) */

void    RobotArm_Servo_WritePeriod(uint16 period)
        ;
uint16 RobotArm_Servo_ReadPeriod(void) ;

#if (RobotArm_Servo_UseOneCompareMode)
    void    RobotArm_Servo_WriteCompare(uint16 compare)
            ;
    uint16 RobotArm_Servo_ReadCompare(void) ;
#else
    void    RobotArm_Servo_WriteCompare1(uint16 compare)
            ;
    uint16 RobotArm_Servo_ReadCompare1(void) ;
    void    RobotArm_Servo_WriteCompare2(uint16 compare)
            ;
    uint16 RobotArm_Servo_ReadCompare2(void) ;
#endif /* (RobotArm_Servo_UseOneCompareMode) */


#if (RobotArm_Servo_DeadBandUsed)
    void    RobotArm_Servo_WriteDeadTime(uint8 deadtime) ;
    uint8   RobotArm_Servo_ReadDeadTime(void) ;
#endif /* (RobotArm_Servo_DeadBandUsed) */

#if ( RobotArm_Servo_KillModeMinTime)
    void RobotArm_Servo_WriteKillTime(uint8 killtime) ;
    uint8 RobotArm_Servo_ReadKillTime(void) ;
#endif /* ( RobotArm_Servo_KillModeMinTime) */

void RobotArm_Servo_Init(void) ;
void RobotArm_Servo_Enable(void) ;
void RobotArm_Servo_Sleep(void) ;
void RobotArm_Servo_Wakeup(void) ;
void RobotArm_Servo_SaveConfig(void) ;
void RobotArm_Servo_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define RobotArm_Servo_INIT_PERIOD_VALUE          (20000u)
#define RobotArm_Servo_INIT_COMPARE_VALUE1        (0u)
#define RobotArm_Servo_INIT_COMPARE_VALUE2        (0u)
#define RobotArm_Servo_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    RobotArm_Servo_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    RobotArm_Servo_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    RobotArm_Servo_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    RobotArm_Servo_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define RobotArm_Servo_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  RobotArm_Servo_CTRL_CMPMODE2_SHIFT)
#define RobotArm_Servo_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  RobotArm_Servo_CTRL_CMPMODE1_SHIFT)
#define RobotArm_Servo_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (RobotArm_Servo_UsingFixedFunction)
   #define RobotArm_Servo_PERIOD_LSB              (*(reg16 *) RobotArm_Servo_PWMHW__PER0)
   #define RobotArm_Servo_PERIOD_LSB_PTR          ( (reg16 *) RobotArm_Servo_PWMHW__PER0)
   #define RobotArm_Servo_COMPARE1_LSB            (*(reg16 *) RobotArm_Servo_PWMHW__CNT_CMP0)
   #define RobotArm_Servo_COMPARE1_LSB_PTR        ( (reg16 *) RobotArm_Servo_PWMHW__CNT_CMP0)
   #define RobotArm_Servo_COMPARE2_LSB            (0x00u)
   #define RobotArm_Servo_COMPARE2_LSB_PTR        (0x00u)
   #define RobotArm_Servo_COUNTER_LSB             (*(reg16 *) RobotArm_Servo_PWMHW__CNT_CMP0)
   #define RobotArm_Servo_COUNTER_LSB_PTR         ( (reg16 *) RobotArm_Servo_PWMHW__CNT_CMP0)
   #define RobotArm_Servo_CAPTURE_LSB             (*(reg16 *) RobotArm_Servo_PWMHW__CAP0)
   #define RobotArm_Servo_CAPTURE_LSB_PTR         ( (reg16 *) RobotArm_Servo_PWMHW__CAP0)
   #define RobotArm_Servo_RT1                     (*(reg8 *)  RobotArm_Servo_PWMHW__RT1)
   #define RobotArm_Servo_RT1_PTR                 ( (reg8 *)  RobotArm_Servo_PWMHW__RT1)

#else
   #if (RobotArm_Servo_Resolution == 8u) /* 8bit - PWM */

       #if(RobotArm_Servo_PWMModeIsCenterAligned)
           #define RobotArm_Servo_PERIOD_LSB      (*(reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define RobotArm_Servo_PERIOD_LSB_PTR  ((reg8 *)   RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define RobotArm_Servo_PERIOD_LSB      (*(reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define RobotArm_Servo_PERIOD_LSB_PTR  ((reg8 *)   RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (RobotArm_Servo_PWMModeIsCenterAligned) */

       #define RobotArm_Servo_COMPARE1_LSB        (*(reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define RobotArm_Servo_COMPARE1_LSB_PTR    ((reg8 *)   RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define RobotArm_Servo_COMPARE2_LSB        (*(reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define RobotArm_Servo_COMPARE2_LSB_PTR    ((reg8 *)   RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define RobotArm_Servo_COUNTERCAP_LSB      (*(reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define RobotArm_Servo_COUNTERCAP_LSB_PTR  ((reg8 *)   RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define RobotArm_Servo_COUNTER_LSB         (*(reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define RobotArm_Servo_COUNTER_LSB_PTR     ((reg8 *)   RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define RobotArm_Servo_CAPTURE_LSB         (*(reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define RobotArm_Servo_CAPTURE_LSB_PTR     ((reg8 *)   RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(RobotArm_Servo_PWMModeIsCenterAligned)
               #define RobotArm_Servo_PERIOD_LSB      (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define RobotArm_Servo_PERIOD_LSB_PTR  ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define RobotArm_Servo_PERIOD_LSB      (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define RobotArm_Servo_PERIOD_LSB_PTR  ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (RobotArm_Servo_PWMModeIsCenterAligned) */

            #define RobotArm_Servo_COMPARE1_LSB       (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define RobotArm_Servo_COMPARE1_LSB_PTR   ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define RobotArm_Servo_COMPARE2_LSB       (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define RobotArm_Servo_COMPARE2_LSB_PTR   ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define RobotArm_Servo_COUNTERCAP_LSB     (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define RobotArm_Servo_COUNTERCAP_LSB_PTR ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define RobotArm_Servo_COUNTER_LSB        (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define RobotArm_Servo_COUNTER_LSB_PTR    ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define RobotArm_Servo_CAPTURE_LSB        (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define RobotArm_Servo_CAPTURE_LSB_PTR    ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(RobotArm_Servo_PWMModeIsCenterAligned)
               #define RobotArm_Servo_PERIOD_LSB      (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define RobotArm_Servo_PERIOD_LSB_PTR  ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define RobotArm_Servo_PERIOD_LSB      (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define RobotArm_Servo_PERIOD_LSB_PTR  ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (RobotArm_Servo_PWMModeIsCenterAligned) */

            #define RobotArm_Servo_COMPARE1_LSB       (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define RobotArm_Servo_COMPARE1_LSB_PTR   ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define RobotArm_Servo_COMPARE2_LSB       (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define RobotArm_Servo_COMPARE2_LSB_PTR   ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define RobotArm_Servo_COUNTERCAP_LSB     (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define RobotArm_Servo_COUNTERCAP_LSB_PTR ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define RobotArm_Servo_COUNTER_LSB        (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define RobotArm_Servo_COUNTER_LSB_PTR    ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define RobotArm_Servo_CAPTURE_LSB        (*(reg16 *) RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define RobotArm_Servo_CAPTURE_LSB_PTR    ((reg16 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define RobotArm_Servo_AUX_CONTROLDP1          (*(reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define RobotArm_Servo_AUX_CONTROLDP1_PTR      ((reg8 *)   RobotArm_Servo_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (RobotArm_Servo_Resolution == 8) */

   #define RobotArm_Servo_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define RobotArm_Servo_AUX_CONTROLDP0          (*(reg8 *)  RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define RobotArm_Servo_AUX_CONTROLDP0_PTR      ((reg8 *)   RobotArm_Servo_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (RobotArm_Servo_UsingFixedFunction) */

#if(RobotArm_Servo_KillModeMinTime )
    #define RobotArm_Servo_KILLMODEMINTIME        (*(reg8 *)  RobotArm_Servo_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define RobotArm_Servo_KILLMODEMINTIME_PTR    ((reg8 *)   RobotArm_Servo_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (RobotArm_Servo_KillModeMinTime ) */

#if(RobotArm_Servo_DeadBandMode == RobotArm_Servo__B_PWM__DBM_256_CLOCKS)
    #define RobotArm_Servo_DEADBAND_COUNT         (*(reg8 *)  RobotArm_Servo_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define RobotArm_Servo_DEADBAND_COUNT_PTR     ((reg8 *)   RobotArm_Servo_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define RobotArm_Servo_DEADBAND_LSB_PTR       ((reg8 *)   RobotArm_Servo_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define RobotArm_Servo_DEADBAND_LSB           (*(reg8 *)  RobotArm_Servo_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(RobotArm_Servo_DeadBandMode == RobotArm_Servo__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (RobotArm_Servo_UsingFixedFunction)
        #define RobotArm_Servo_DEADBAND_COUNT         (*(reg8 *)  RobotArm_Servo_PWMHW__CFG0)
        #define RobotArm_Servo_DEADBAND_COUNT_PTR     ((reg8 *)   RobotArm_Servo_PWMHW__CFG0)
        #define RobotArm_Servo_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << RobotArm_Servo_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define RobotArm_Servo_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define RobotArm_Servo_DEADBAND_COUNT         (*(reg8 *)  RobotArm_Servo_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define RobotArm_Servo_DEADBAND_COUNT_PTR     ((reg8 *)   RobotArm_Servo_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define RobotArm_Servo_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << RobotArm_Servo_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define RobotArm_Servo_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (RobotArm_Servo_UsingFixedFunction) */
#endif /* (RobotArm_Servo_DeadBandMode == RobotArm_Servo__B_PWM__DBM_256_CLOCKS) */



#if (RobotArm_Servo_UsingFixedFunction)
    #define RobotArm_Servo_STATUS                 (*(reg8 *) RobotArm_Servo_PWMHW__SR0)
    #define RobotArm_Servo_STATUS_PTR             ((reg8 *) RobotArm_Servo_PWMHW__SR0)
    #define RobotArm_Servo_STATUS_MASK            (*(reg8 *) RobotArm_Servo_PWMHW__SR0)
    #define RobotArm_Servo_STATUS_MASK_PTR        ((reg8 *) RobotArm_Servo_PWMHW__SR0)
    #define RobotArm_Servo_CONTROL                (*(reg8 *) RobotArm_Servo_PWMHW__CFG0)
    #define RobotArm_Servo_CONTROL_PTR            ((reg8 *) RobotArm_Servo_PWMHW__CFG0)
    #define RobotArm_Servo_CONTROL2               (*(reg8 *) RobotArm_Servo_PWMHW__CFG1)
    #define RobotArm_Servo_CONTROL3               (*(reg8 *) RobotArm_Servo_PWMHW__CFG2)
    #define RobotArm_Servo_GLOBAL_ENABLE          (*(reg8 *) RobotArm_Servo_PWMHW__PM_ACT_CFG)
    #define RobotArm_Servo_GLOBAL_ENABLE_PTR      ( (reg8 *) RobotArm_Servo_PWMHW__PM_ACT_CFG)
    #define RobotArm_Servo_GLOBAL_STBY_ENABLE     (*(reg8 *) RobotArm_Servo_PWMHW__PM_STBY_CFG)
    #define RobotArm_Servo_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) RobotArm_Servo_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define RobotArm_Servo_BLOCK_EN_MASK          (RobotArm_Servo_PWMHW__PM_ACT_MSK)
    #define RobotArm_Servo_BLOCK_STBY_EN_MASK     (RobotArm_Servo_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define RobotArm_Servo_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define RobotArm_Servo_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define RobotArm_Servo_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define RobotArm_Servo_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define RobotArm_Servo_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define RobotArm_Servo_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define RobotArm_Servo_CTRL_ENABLE            (uint8)((uint8)0x01u << RobotArm_Servo_CTRL_ENABLE_SHIFT)
    #define RobotArm_Servo_CTRL_RESET             (uint8)((uint8)0x01u << RobotArm_Servo_CTRL_RESET_SHIFT)
    #define RobotArm_Servo_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << RobotArm_Servo_CTRL_CMPMODE2_SHIFT)
    #define RobotArm_Servo_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << RobotArm_Servo_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define RobotArm_Servo_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define RobotArm_Servo_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << RobotArm_Servo_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define RobotArm_Servo_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define RobotArm_Servo_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define RobotArm_Servo_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define RobotArm_Servo_STATUS_TC_INT_EN_MASK_SHIFT            (RobotArm_Servo_STATUS_TC_SHIFT - 4u)
    #define RobotArm_Servo_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define RobotArm_Servo_STATUS_CMP1_INT_EN_MASK_SHIFT          (RobotArm_Servo_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define RobotArm_Servo_STATUS_TC              (uint8)((uint8)0x01u << RobotArm_Servo_STATUS_TC_SHIFT)
    #define RobotArm_Servo_STATUS_CMP1            (uint8)((uint8)0x01u << RobotArm_Servo_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define RobotArm_Servo_STATUS_TC_INT_EN_MASK              (uint8)((uint8)RobotArm_Servo_STATUS_TC >> 4u)
    #define RobotArm_Servo_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)RobotArm_Servo_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define RobotArm_Servo_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define RobotArm_Servo_RT1_MASK              (uint8)((uint8)0x03u << RobotArm_Servo_RT1_SHIFT)
    #define RobotArm_Servo_SYNC                  (uint8)((uint8)0x03u << RobotArm_Servo_RT1_SHIFT)
    #define RobotArm_Servo_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define RobotArm_Servo_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << RobotArm_Servo_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define RobotArm_Servo_SYNCDSI_EN            (uint8)((uint8)0x0Fu << RobotArm_Servo_SYNCDSI_SHIFT)


#else
    #define RobotArm_Servo_STATUS                (*(reg8 *)   RobotArm_Servo_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define RobotArm_Servo_STATUS_PTR            ((reg8 *)    RobotArm_Servo_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define RobotArm_Servo_STATUS_MASK           (*(reg8 *)   RobotArm_Servo_PWMUDB_genblk8_stsreg__MASK_REG)
    #define RobotArm_Servo_STATUS_MASK_PTR       ((reg8 *)    RobotArm_Servo_PWMUDB_genblk8_stsreg__MASK_REG)
    #define RobotArm_Servo_STATUS_AUX_CTRL       (*(reg8 *)   RobotArm_Servo_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define RobotArm_Servo_CONTROL               (*(reg8 *)   RobotArm_Servo_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define RobotArm_Servo_CONTROL_PTR           ((reg8 *)    RobotArm_Servo_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define RobotArm_Servo_CTRL_ENABLE_SHIFT      (0x07u)
    #define RobotArm_Servo_CTRL_RESET_SHIFT       (0x06u)
    #define RobotArm_Servo_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define RobotArm_Servo_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define RobotArm_Servo_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define RobotArm_Servo_CTRL_ENABLE            (uint8)((uint8)0x01u << RobotArm_Servo_CTRL_ENABLE_SHIFT)
    #define RobotArm_Servo_CTRL_RESET             (uint8)((uint8)0x01u << RobotArm_Servo_CTRL_RESET_SHIFT)
    #define RobotArm_Servo_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << RobotArm_Servo_CTRL_CMPMODE2_SHIFT)
    #define RobotArm_Servo_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << RobotArm_Servo_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define RobotArm_Servo_STATUS_KILL_SHIFT          (0x05u)
    #define RobotArm_Servo_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define RobotArm_Servo_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define RobotArm_Servo_STATUS_TC_SHIFT            (0x02u)
    #define RobotArm_Servo_STATUS_CMP2_SHIFT          (0x01u)
    #define RobotArm_Servo_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define RobotArm_Servo_STATUS_KILL_INT_EN_MASK_SHIFT          (RobotArm_Servo_STATUS_KILL_SHIFT)
    #define RobotArm_Servo_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (RobotArm_Servo_STATUS_FIFONEMPTY_SHIFT)
    #define RobotArm_Servo_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (RobotArm_Servo_STATUS_FIFOFULL_SHIFT)
    #define RobotArm_Servo_STATUS_TC_INT_EN_MASK_SHIFT            (RobotArm_Servo_STATUS_TC_SHIFT)
    #define RobotArm_Servo_STATUS_CMP2_INT_EN_MASK_SHIFT          (RobotArm_Servo_STATUS_CMP2_SHIFT)
    #define RobotArm_Servo_STATUS_CMP1_INT_EN_MASK_SHIFT          (RobotArm_Servo_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define RobotArm_Servo_STATUS_KILL            (uint8)((uint8)0x00u << RobotArm_Servo_STATUS_KILL_SHIFT )
    #define RobotArm_Servo_STATUS_FIFOFULL        (uint8)((uint8)0x01u << RobotArm_Servo_STATUS_FIFOFULL_SHIFT)
    #define RobotArm_Servo_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << RobotArm_Servo_STATUS_FIFONEMPTY_SHIFT)
    #define RobotArm_Servo_STATUS_TC              (uint8)((uint8)0x01u << RobotArm_Servo_STATUS_TC_SHIFT)
    #define RobotArm_Servo_STATUS_CMP2            (uint8)((uint8)0x01u << RobotArm_Servo_STATUS_CMP2_SHIFT)
    #define RobotArm_Servo_STATUS_CMP1            (uint8)((uint8)0x01u << RobotArm_Servo_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define RobotArm_Servo_STATUS_KILL_INT_EN_MASK            (RobotArm_Servo_STATUS_KILL)
    #define RobotArm_Servo_STATUS_FIFOFULL_INT_EN_MASK        (RobotArm_Servo_STATUS_FIFOFULL)
    #define RobotArm_Servo_STATUS_FIFONEMPTY_INT_EN_MASK      (RobotArm_Servo_STATUS_FIFONEMPTY)
    #define RobotArm_Servo_STATUS_TC_INT_EN_MASK              (RobotArm_Servo_STATUS_TC)
    #define RobotArm_Servo_STATUS_CMP2_INT_EN_MASK            (RobotArm_Servo_STATUS_CMP2)
    #define RobotArm_Servo_STATUS_CMP1_INT_EN_MASK            (RobotArm_Servo_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define RobotArm_Servo_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define RobotArm_Servo_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define RobotArm_Servo_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define RobotArm_Servo_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define RobotArm_Servo_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* RobotArm_Servo_UsingFixedFunction */

#endif  /* CY_PWM_RobotArm_Servo_H */


/* [] END OF FILE */
