/*******************************************************************************
* File Name: S4_Timer_PM.c
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

#include "S4_Timer.h"

static S4_Timer_backupStruct S4_Timer_backup;


/*******************************************************************************
* Function Name: S4_Timer_SaveConfig
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
*  S4_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void S4_Timer_SaveConfig(void) 
{
    #if (!S4_Timer_UsingFixedFunction)
        S4_Timer_backup.TimerUdb = S4_Timer_ReadCounter();
        S4_Timer_backup.InterruptMaskValue = S4_Timer_STATUS_MASK;
        #if (S4_Timer_UsingHWCaptureCounter)
            S4_Timer_backup.TimerCaptureCounter = S4_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!S4_Timer_UDB_CONTROL_REG_REMOVED)
            S4_Timer_backup.TimerControlRegister = S4_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: S4_Timer_RestoreConfig
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
*  S4_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void S4_Timer_RestoreConfig(void) 
{   
    #if (!S4_Timer_UsingFixedFunction)

        S4_Timer_WriteCounter(S4_Timer_backup.TimerUdb);
        S4_Timer_STATUS_MASK =S4_Timer_backup.InterruptMaskValue;
        #if (S4_Timer_UsingHWCaptureCounter)
            S4_Timer_SetCaptureCount(S4_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!S4_Timer_UDB_CONTROL_REG_REMOVED)
            S4_Timer_WriteControlRegister(S4_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: S4_Timer_Sleep
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
*  S4_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void S4_Timer_Sleep(void) 
{
    #if(!S4_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(S4_Timer_CTRL_ENABLE == (S4_Timer_CONTROL & S4_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            S4_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            S4_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    S4_Timer_Stop();
    S4_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: S4_Timer_Wakeup
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
*  S4_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void S4_Timer_Wakeup(void) 
{
    S4_Timer_RestoreConfig();
    #if(!S4_Timer_UDB_CONTROL_REG_REMOVED)
        if(S4_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                S4_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
