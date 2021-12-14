/*******************************************************************************
* File Name: Flicker_Servo_PM.c
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

#include "Flicker_Servo.h"

static Flicker_Servo_backupStruct Flicker_Servo_backup;


/*******************************************************************************
* Function Name: Flicker_Servo_SaveConfig
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
*  Flicker_Servo_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Flicker_Servo_SaveConfig(void) 
{

    #if(!Flicker_Servo_UsingFixedFunction)
        #if(!Flicker_Servo_PWMModeIsCenterAligned)
            Flicker_Servo_backup.PWMPeriod = Flicker_Servo_ReadPeriod();
        #endif /* (!Flicker_Servo_PWMModeIsCenterAligned) */
        Flicker_Servo_backup.PWMUdb = Flicker_Servo_ReadCounter();
        #if (Flicker_Servo_UseStatus)
            Flicker_Servo_backup.InterruptMaskValue = Flicker_Servo_STATUS_MASK;
        #endif /* (Flicker_Servo_UseStatus) */

        #if(Flicker_Servo_DeadBandMode == Flicker_Servo__B_PWM__DBM_256_CLOCKS || \
            Flicker_Servo_DeadBandMode == Flicker_Servo__B_PWM__DBM_2_4_CLOCKS)
            Flicker_Servo_backup.PWMdeadBandValue = Flicker_Servo_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Flicker_Servo_KillModeMinTime)
             Flicker_Servo_backup.PWMKillCounterPeriod = Flicker_Servo_ReadKillTime();
        #endif /* (Flicker_Servo_KillModeMinTime) */

        #if(Flicker_Servo_UseControl)
            Flicker_Servo_backup.PWMControlRegister = Flicker_Servo_ReadControlRegister();
        #endif /* (Flicker_Servo_UseControl) */
    #endif  /* (!Flicker_Servo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Flicker_Servo_RestoreConfig
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
*  Flicker_Servo_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Flicker_Servo_RestoreConfig(void) 
{
        #if(!Flicker_Servo_UsingFixedFunction)
            #if(!Flicker_Servo_PWMModeIsCenterAligned)
                Flicker_Servo_WritePeriod(Flicker_Servo_backup.PWMPeriod);
            #endif /* (!Flicker_Servo_PWMModeIsCenterAligned) */

            Flicker_Servo_WriteCounter(Flicker_Servo_backup.PWMUdb);

            #if (Flicker_Servo_UseStatus)
                Flicker_Servo_STATUS_MASK = Flicker_Servo_backup.InterruptMaskValue;
            #endif /* (Flicker_Servo_UseStatus) */

            #if(Flicker_Servo_DeadBandMode == Flicker_Servo__B_PWM__DBM_256_CLOCKS || \
                Flicker_Servo_DeadBandMode == Flicker_Servo__B_PWM__DBM_2_4_CLOCKS)
                Flicker_Servo_WriteDeadTime(Flicker_Servo_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Flicker_Servo_KillModeMinTime)
                Flicker_Servo_WriteKillTime(Flicker_Servo_backup.PWMKillCounterPeriod);
            #endif /* (Flicker_Servo_KillModeMinTime) */

            #if(Flicker_Servo_UseControl)
                Flicker_Servo_WriteControlRegister(Flicker_Servo_backup.PWMControlRegister);
            #endif /* (Flicker_Servo_UseControl) */
        #endif  /* (!Flicker_Servo_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Flicker_Servo_Sleep
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
*  Flicker_Servo_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Flicker_Servo_Sleep(void) 
{
    #if(Flicker_Servo_UseControl)
        if(Flicker_Servo_CTRL_ENABLE == (Flicker_Servo_CONTROL & Flicker_Servo_CTRL_ENABLE))
        {
            /*Component is enabled */
            Flicker_Servo_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Flicker_Servo_backup.PWMEnableState = 0u;
        }
    #endif /* (Flicker_Servo_UseControl) */

    /* Stop component */
    Flicker_Servo_Stop();

    /* Save registers configuration */
    Flicker_Servo_SaveConfig();
}


/*******************************************************************************
* Function Name: Flicker_Servo_Wakeup
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
*  Flicker_Servo_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Flicker_Servo_Wakeup(void) 
{
     /* Restore registers values */
    Flicker_Servo_RestoreConfig();

    if(Flicker_Servo_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Flicker_Servo_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
