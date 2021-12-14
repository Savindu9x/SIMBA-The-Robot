/*******************************************************************************
* File Name: Counter_Color_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Counter_Color.h"

static Counter_Color_backupStruct Counter_Color_backup;


/*******************************************************************************
* Function Name: Counter_Color_SaveConfig
********************************************************************************
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
*  Counter_Color_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_Color_SaveConfig(void) 
{
    #if (!Counter_Color_UsingFixedFunction)

        Counter_Color_backup.CounterUdb = Counter_Color_ReadCounter();

        #if(!Counter_Color_ControlRegRemoved)
            Counter_Color_backup.CounterControlRegister = Counter_Color_ReadControlRegister();
        #endif /* (!Counter_Color_ControlRegRemoved) */

    #endif /* (!Counter_Color_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_Color_RestoreConfig
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
*  Counter_Color_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_Color_RestoreConfig(void) 
{      
    #if (!Counter_Color_UsingFixedFunction)

       Counter_Color_WriteCounter(Counter_Color_backup.CounterUdb);

        #if(!Counter_Color_ControlRegRemoved)
            Counter_Color_WriteControlRegister(Counter_Color_backup.CounterControlRegister);
        #endif /* (!Counter_Color_ControlRegRemoved) */

    #endif /* (!Counter_Color_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_Color_Sleep
********************************************************************************
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
*  Counter_Color_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_Color_Sleep(void) 
{
    #if(!Counter_Color_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_Color_CTRL_ENABLE == (Counter_Color_CONTROL & Counter_Color_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_Color_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_Color_backup.CounterEnableState = 0u;
        }
    #else
        Counter_Color_backup.CounterEnableState = 1u;
        if(Counter_Color_backup.CounterEnableState != 0u)
        {
            Counter_Color_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_Color_ControlRegRemoved) */
    
    Counter_Color_Stop();
    Counter_Color_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_Color_Wakeup
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
*  Counter_Color_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_Color_Wakeup(void) 
{
    Counter_Color_RestoreConfig();
    #if(!Counter_Color_ControlRegRemoved)
        if(Counter_Color_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_Color_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_Color_ControlRegRemoved) */
    
}


/* [] END OF FILE */
