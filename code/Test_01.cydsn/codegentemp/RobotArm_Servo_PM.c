/*******************************************************************************
* File Name: RobotArm_Servo_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RobotArm_Servo.h"

static RobotArm_Servo_backupStruct RobotArm_Servo_backup;


/*******************************************************************************
* Function Name: RobotArm_Servo_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RobotArm_Servo_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void RobotArm_Servo_SaveConfig(void) 
{

    #if(!RobotArm_Servo_UsingFixedFunction)
        #if(!RobotArm_Servo_PWMModeIsCenterAligned)
            RobotArm_Servo_backup.PWMPeriod = RobotArm_Servo_ReadPeriod();
        #endif /* (!RobotArm_Servo_PWMModeIsCenterAligned) */
        RobotArm_Servo_backup.PWMUdb = RobotArm_Servo_ReadCounter();
        #if (RobotArm_Servo_UseStatus)
            RobotArm_Servo_backup.InterruptMaskValue = RobotArm_Servo_STATUS_MASK;
        #endif /* (RobotArm_Servo_UseStatus) */

        #if(RobotArm_Servo_DeadBandMode == RobotArm_Servo__B_PWM__DBM_256_CLOCKS || \
            RobotArm_Servo_DeadBandMode == RobotArm_Servo__B_PWM__DBM_2_4_CLOCKS)
            RobotArm_Servo_backup.PWMdeadBandValue = RobotArm_Servo_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(RobotArm_Servo_KillModeMinTime)
             RobotArm_Servo_backup.PWMKillCounterPeriod = RobotArm_Servo_ReadKillTime();
        #endif /* (RobotArm_Servo_KillModeMinTime) */

        #if(RobotArm_Servo_UseControl)
            RobotArm_Servo_backup.PWMControlRegister = RobotArm_Servo_ReadControlRegister();
        #endif /* (RobotArm_Servo_UseControl) */
    #endif  /* (!RobotArm_Servo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RobotArm_Servo_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RobotArm_Servo_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void RobotArm_Servo_RestoreConfig(void) 
{
        #if(!RobotArm_Servo_UsingFixedFunction)
            #if(!RobotArm_Servo_PWMModeIsCenterAligned)
                RobotArm_Servo_WritePeriod(RobotArm_Servo_backup.PWMPeriod);
            #endif /* (!RobotArm_Servo_PWMModeIsCenterAligned) */

            RobotArm_Servo_WriteCounter(RobotArm_Servo_backup.PWMUdb);

            #if (RobotArm_Servo_UseStatus)
                RobotArm_Servo_STATUS_MASK = RobotArm_Servo_backup.InterruptMaskValue;
            #endif /* (RobotArm_Servo_UseStatus) */

            #if(RobotArm_Servo_DeadBandMode == RobotArm_Servo__B_PWM__DBM_256_CLOCKS || \
                RobotArm_Servo_DeadBandMode == RobotArm_Servo__B_PWM__DBM_2_4_CLOCKS)
                RobotArm_Servo_WriteDeadTime(RobotArm_Servo_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(RobotArm_Servo_KillModeMinTime)
                RobotArm_Servo_WriteKillTime(RobotArm_Servo_backup.PWMKillCounterPeriod);
            #endif /* (RobotArm_Servo_KillModeMinTime) */

            #if(RobotArm_Servo_UseControl)
                RobotArm_Servo_WriteControlRegister(RobotArm_Servo_backup.PWMControlRegister);
            #endif /* (RobotArm_Servo_UseControl) */
        #endif  /* (!RobotArm_Servo_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: RobotArm_Servo_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RobotArm_Servo_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void RobotArm_Servo_Sleep(void) 
{
    #if(RobotArm_Servo_UseControl)
        if(RobotArm_Servo_CTRL_ENABLE == (RobotArm_Servo_CONTROL & RobotArm_Servo_CTRL_ENABLE))
        {
            /*Component is enabled */
            RobotArm_Servo_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            RobotArm_Servo_backup.PWMEnableState = 0u;
        }
    #endif /* (RobotArm_Servo_UseControl) */

    /* Stop component */
    RobotArm_Servo_Stop();

    /* Save registers configuration */
    RobotArm_Servo_SaveConfig();
}


/*******************************************************************************
* Function Name: RobotArm_Servo_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RobotArm_Servo_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void RobotArm_Servo_Wakeup(void) 
{
     /* Restore registers values */
    RobotArm_Servo_RestoreConfig();

    if(RobotArm_Servo_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        RobotArm_Servo_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
