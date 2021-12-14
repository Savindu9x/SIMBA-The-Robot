/*******************************************************************************
* File Name: S3_Timer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "S3_Timer.h"

static S3_Timer_backupStruct S3_Timer_backup;


/*******************************************************************************
* Function Name: S3_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  S3_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void S3_Timer_SaveConfig(void) 
{
    #if (!S3_Timer_UsingFixedFunction)
        S3_Timer_backup.TimerUdb = S3_Timer_ReadCounter();
        S3_Timer_backup.InterruptMaskValue = S3_Timer_STATUS_MASK;
        #if (S3_Timer_UsingHWCaptureCounter)
            S3_Timer_backup.TimerCaptureCounter = S3_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!S3_Timer_UDB_CONTROL_REG_REMOVED)
            S3_Timer_backup.TimerControlRegister = S3_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: S3_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  S3_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void S3_Timer_RestoreConfig(void) 
{   
    #if (!S3_Timer_UsingFixedFunction)

        S3_Timer_WriteCounter(S3_Timer_backup.TimerUdb);
        S3_Timer_STATUS_MASK =S3_Timer_backup.InterruptMaskValue;
        #if (S3_Timer_UsingHWCaptureCounter)
            S3_Timer_SetCaptureCount(S3_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!S3_Timer_UDB_CONTROL_REG_REMOVED)
            S3_Timer_WriteControlRegister(S3_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: S3_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  S3_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void S3_Timer_Sleep(void) 
{
    #if(!S3_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(S3_Timer_CTRL_ENABLE == (S3_Timer_CONTROL & S3_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            S3_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            S3_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    S3_Timer_Stop();
    S3_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: S3_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  S3_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void S3_Timer_Wakeup(void) 
{
    S3_Timer_RestoreConfig();
    #if(!S3_Timer_UDB_CONTROL_REG_REMOVED)
        if(S3_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                S3_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
