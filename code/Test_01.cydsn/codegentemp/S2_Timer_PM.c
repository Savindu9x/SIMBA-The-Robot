/*******************************************************************************
* File Name: S2_Timer_PM.c
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

#include "S2_Timer.h"

static S2_Timer_backupStruct S2_Timer_backup;


/*******************************************************************************
* Function Name: S2_Timer_SaveConfig
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
*  S2_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void S2_Timer_SaveConfig(void) 
{
    #if (!S2_Timer_UsingFixedFunction)
        S2_Timer_backup.TimerUdb = S2_Timer_ReadCounter();
        S2_Timer_backup.InterruptMaskValue = S2_Timer_STATUS_MASK;
        #if (S2_Timer_UsingHWCaptureCounter)
            S2_Timer_backup.TimerCaptureCounter = S2_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!S2_Timer_UDB_CONTROL_REG_REMOVED)
            S2_Timer_backup.TimerControlRegister = S2_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: S2_Timer_RestoreConfig
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
*  S2_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void S2_Timer_RestoreConfig(void) 
{   
    #if (!S2_Timer_UsingFixedFunction)

        S2_Timer_WriteCounter(S2_Timer_backup.TimerUdb);
        S2_Timer_STATUS_MASK =S2_Timer_backup.InterruptMaskValue;
        #if (S2_Timer_UsingHWCaptureCounter)
            S2_Timer_SetCaptureCount(S2_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!S2_Timer_UDB_CONTROL_REG_REMOVED)
            S2_Timer_WriteControlRegister(S2_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: S2_Timer_Sleep
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
*  S2_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void S2_Timer_Sleep(void) 
{
    #if(!S2_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(S2_Timer_CTRL_ENABLE == (S2_Timer_CONTROL & S2_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            S2_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            S2_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    S2_Timer_Stop();
    S2_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: S2_Timer_Wakeup
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
*  S2_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void S2_Timer_Wakeup(void) 
{
    S2_Timer_RestoreConfig();
    #if(!S2_Timer_UDB_CONTROL_REG_REMOVED)
        if(S2_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                S2_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
