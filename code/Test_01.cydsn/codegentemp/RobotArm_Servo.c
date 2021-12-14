/*******************************************************************************
* File Name: RobotArm_Servo.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "RobotArm_Servo.h"

/* Error message for removed <resource> through optimization */
#ifdef RobotArm_Servo_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* RobotArm_Servo_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 RobotArm_Servo_initVar = 0u;


/*******************************************************************************
* Function Name: RobotArm_Servo_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RobotArm_Servo_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void RobotArm_Servo_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(RobotArm_Servo_initVar == 0u)
    {
        RobotArm_Servo_Init();
        RobotArm_Servo_initVar = 1u;
    }
    RobotArm_Servo_Enable();

}


/*******************************************************************************
* Function Name: RobotArm_Servo_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  RobotArm_Servo_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void RobotArm_Servo_Init(void) 
{
    #if (RobotArm_Servo_UsingFixedFunction || RobotArm_Servo_UseControl)
        uint8 ctrl;
    #endif /* (RobotArm_Servo_UsingFixedFunction || RobotArm_Servo_UseControl) */

    #if(!RobotArm_Servo_UsingFixedFunction)
        #if(RobotArm_Servo_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 RobotArm_Servo_interruptState;
        #endif /* (RobotArm_Servo_UseStatus) */
    #endif /* (!RobotArm_Servo_UsingFixedFunction) */

    #if (RobotArm_Servo_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        RobotArm_Servo_CONTROL |= RobotArm_Servo_CFG0_MODE;
        #if (RobotArm_Servo_DeadBand2_4)
            RobotArm_Servo_CONTROL |= RobotArm_Servo_CFG0_DB;
        #endif /* (RobotArm_Servo_DeadBand2_4) */

        ctrl = RobotArm_Servo_CONTROL3 & ((uint8 )(~RobotArm_Servo_CTRL_CMPMODE1_MASK));
        RobotArm_Servo_CONTROL3 = ctrl | RobotArm_Servo_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        RobotArm_Servo_RT1 &= ((uint8)(~RobotArm_Servo_RT1_MASK));
        RobotArm_Servo_RT1 |= RobotArm_Servo_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        RobotArm_Servo_RT1 &= ((uint8)(~RobotArm_Servo_SYNCDSI_MASK));
        RobotArm_Servo_RT1 |= RobotArm_Servo_SYNCDSI_EN;

    #elif (RobotArm_Servo_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = RobotArm_Servo_CONTROL & ((uint8)(~RobotArm_Servo_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~RobotArm_Servo_CTRL_CMPMODE1_MASK));
        RobotArm_Servo_CONTROL = ctrl | RobotArm_Servo_DEFAULT_COMPARE2_MODE |
                                   RobotArm_Servo_DEFAULT_COMPARE1_MODE;
    #endif /* (RobotArm_Servo_UsingFixedFunction) */

    #if (!RobotArm_Servo_UsingFixedFunction)
        #if (RobotArm_Servo_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            RobotArm_Servo_AUX_CONTROLDP0 |= (RobotArm_Servo_AUX_CTRL_FIFO0_CLR);
        #else /* (RobotArm_Servo_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            RobotArm_Servo_AUX_CONTROLDP0 |= (RobotArm_Servo_AUX_CTRL_FIFO0_CLR);
            RobotArm_Servo_AUX_CONTROLDP1 |= (RobotArm_Servo_AUX_CTRL_FIFO0_CLR);
        #endif /* (RobotArm_Servo_Resolution == 8) */

        RobotArm_Servo_WriteCounter(RobotArm_Servo_INIT_PERIOD_VALUE);
    #endif /* (!RobotArm_Servo_UsingFixedFunction) */

    RobotArm_Servo_WritePeriod(RobotArm_Servo_INIT_PERIOD_VALUE);

        #if (RobotArm_Servo_UseOneCompareMode)
            RobotArm_Servo_WriteCompare(RobotArm_Servo_INIT_COMPARE_VALUE1);
        #else
            RobotArm_Servo_WriteCompare1(RobotArm_Servo_INIT_COMPARE_VALUE1);
            RobotArm_Servo_WriteCompare2(RobotArm_Servo_INIT_COMPARE_VALUE2);
        #endif /* (RobotArm_Servo_UseOneCompareMode) */

        #if (RobotArm_Servo_KillModeMinTime)
            RobotArm_Servo_WriteKillTime(RobotArm_Servo_MinimumKillTime);
        #endif /* (RobotArm_Servo_KillModeMinTime) */

        #if (RobotArm_Servo_DeadBandUsed)
            RobotArm_Servo_WriteDeadTime(RobotArm_Servo_INIT_DEAD_TIME);
        #endif /* (RobotArm_Servo_DeadBandUsed) */

    #if (RobotArm_Servo_UseStatus || RobotArm_Servo_UsingFixedFunction)
        RobotArm_Servo_SetInterruptMode(RobotArm_Servo_INIT_INTERRUPTS_MODE);
    #endif /* (RobotArm_Servo_UseStatus || RobotArm_Servo_UsingFixedFunction) */

    #if (RobotArm_Servo_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        RobotArm_Servo_GLOBAL_ENABLE |= RobotArm_Servo_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        RobotArm_Servo_CONTROL2 |= RobotArm_Servo_CTRL2_IRQ_SEL;
    #else
        #if(RobotArm_Servo_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            RobotArm_Servo_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            RobotArm_Servo_STATUS_AUX_CTRL |= RobotArm_Servo_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(RobotArm_Servo_interruptState);

            /* Clear the FIFO to enable the RobotArm_Servo_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            RobotArm_Servo_ClearFIFO();
        #endif /* (RobotArm_Servo_UseStatus) */
    #endif /* (RobotArm_Servo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RobotArm_Servo_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void RobotArm_Servo_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (RobotArm_Servo_UsingFixedFunction)
        RobotArm_Servo_GLOBAL_ENABLE |= RobotArm_Servo_BLOCK_EN_MASK;
        RobotArm_Servo_GLOBAL_STBY_ENABLE |= RobotArm_Servo_BLOCK_STBY_EN_MASK;
    #endif /* (RobotArm_Servo_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (RobotArm_Servo_UseControl || RobotArm_Servo_UsingFixedFunction)
        RobotArm_Servo_CONTROL |= RobotArm_Servo_CTRL_ENABLE;
    #endif /* (RobotArm_Servo_UseControl || RobotArm_Servo_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RobotArm_Servo_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void RobotArm_Servo_Stop(void) 
{
    #if (RobotArm_Servo_UseControl || RobotArm_Servo_UsingFixedFunction)
        RobotArm_Servo_CONTROL &= ((uint8)(~RobotArm_Servo_CTRL_ENABLE));
    #endif /* (RobotArm_Servo_UseControl || RobotArm_Servo_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (RobotArm_Servo_UsingFixedFunction)
        RobotArm_Servo_GLOBAL_ENABLE &= ((uint8)(~RobotArm_Servo_BLOCK_EN_MASK));
        RobotArm_Servo_GLOBAL_STBY_ENABLE &= ((uint8)(~RobotArm_Servo_BLOCK_STBY_EN_MASK));
    #endif /* (RobotArm_Servo_UsingFixedFunction) */
}

#if (RobotArm_Servo_UseOneCompareMode)
    #if (RobotArm_Servo_CompareMode1SW)


        /*******************************************************************************
        * Function Name: RobotArm_Servo_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void RobotArm_Servo_SetCompareMode(uint8 comparemode) 
        {
            #if(RobotArm_Servo_UsingFixedFunction)

                #if(0 != RobotArm_Servo_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << RobotArm_Servo_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != RobotArm_Servo_CTRL_CMPMODE1_SHIFT) */

                RobotArm_Servo_CONTROL3 &= ((uint8)(~RobotArm_Servo_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                RobotArm_Servo_CONTROL3 |= comparemodemasked;

            #elif (RobotArm_Servo_UseControl)

                #if(0 != RobotArm_Servo_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << RobotArm_Servo_CTRL_CMPMODE1_SHIFT)) &
                                                RobotArm_Servo_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & RobotArm_Servo_CTRL_CMPMODE1_MASK;
                #endif /* (0 != RobotArm_Servo_CTRL_CMPMODE1_SHIFT) */

                #if(0 != RobotArm_Servo_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << RobotArm_Servo_CTRL_CMPMODE2_SHIFT)) &
                                               RobotArm_Servo_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & RobotArm_Servo_CTRL_CMPMODE2_MASK;
                #endif /* (0 != RobotArm_Servo_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                RobotArm_Servo_CONTROL &= ((uint8)(~(RobotArm_Servo_CTRL_CMPMODE1_MASK |
                                            RobotArm_Servo_CTRL_CMPMODE2_MASK)));
                RobotArm_Servo_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (RobotArm_Servo_UsingFixedFunction) */
        }
    #endif /* RobotArm_Servo_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (RobotArm_Servo_CompareMode1SW)


        /*******************************************************************************
        * Function Name: RobotArm_Servo_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void RobotArm_Servo_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != RobotArm_Servo_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << RobotArm_Servo_CTRL_CMPMODE1_SHIFT)) &
                                           RobotArm_Servo_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & RobotArm_Servo_CTRL_CMPMODE1_MASK;
            #endif /* (0 != RobotArm_Servo_CTRL_CMPMODE1_SHIFT) */

            #if (RobotArm_Servo_UseControl)
                RobotArm_Servo_CONTROL &= ((uint8)(~RobotArm_Servo_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                RobotArm_Servo_CONTROL |= comparemodemasked;
            #endif /* (RobotArm_Servo_UseControl) */
        }
    #endif /* RobotArm_Servo_CompareMode1SW */

#if (RobotArm_Servo_CompareMode2SW)


    /*******************************************************************************
    * Function Name: RobotArm_Servo_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RobotArm_Servo_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != RobotArm_Servo_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << RobotArm_Servo_CTRL_CMPMODE2_SHIFT)) &
                                                 RobotArm_Servo_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & RobotArm_Servo_CTRL_CMPMODE2_MASK;
        #endif /* (0 != RobotArm_Servo_CTRL_CMPMODE2_SHIFT) */

        #if (RobotArm_Servo_UseControl)
            RobotArm_Servo_CONTROL &= ((uint8)(~RobotArm_Servo_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            RobotArm_Servo_CONTROL |= comparemodemasked;
        #endif /* (RobotArm_Servo_UseControl) */
    }
    #endif /*RobotArm_Servo_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!RobotArm_Servo_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: RobotArm_Servo_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void RobotArm_Servo_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(RobotArm_Servo_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: RobotArm_Servo_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 RobotArm_Servo_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(RobotArm_Servo_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(RobotArm_Servo_CAPTURE_LSB_PTR));
    }

    #if (RobotArm_Servo_UseStatus)


        /*******************************************************************************
        * Function Name: RobotArm_Servo_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void RobotArm_Servo_ClearFIFO(void) 
        {
            while(0u != (RobotArm_Servo_ReadStatusRegister() & RobotArm_Servo_STATUS_FIFONEMPTY))
            {
                (void)RobotArm_Servo_ReadCapture();
            }
        }

    #endif /* RobotArm_Servo_UseStatus */

#endif /* !RobotArm_Servo_UsingFixedFunction */


/*******************************************************************************
* Function Name: RobotArm_Servo_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void RobotArm_Servo_WritePeriod(uint16 period) 
{
    #if(RobotArm_Servo_UsingFixedFunction)
        CY_SET_REG16(RobotArm_Servo_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(RobotArm_Servo_PERIOD_LSB_PTR, period);
    #endif /* (RobotArm_Servo_UsingFixedFunction) */
}

#if (RobotArm_Servo_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: RobotArm_Servo_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void RobotArm_Servo_WriteCompare(uint16 compare) \
                                       
    {
        #if(RobotArm_Servo_UsingFixedFunction)
            CY_SET_REG16(RobotArm_Servo_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(RobotArm_Servo_COMPARE1_LSB_PTR, compare);
        #endif /* (RobotArm_Servo_UsingFixedFunction) */

        #if (RobotArm_Servo_PWMMode == RobotArm_Servo__B_PWM__DITHER)
            #if(RobotArm_Servo_UsingFixedFunction)
                CY_SET_REG16(RobotArm_Servo_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(RobotArm_Servo_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (RobotArm_Servo_UsingFixedFunction) */
        #endif /* (RobotArm_Servo_PWMMode == RobotArm_Servo__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: RobotArm_Servo_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RobotArm_Servo_WriteCompare1(uint16 compare) \
                                        
    {
        #if(RobotArm_Servo_UsingFixedFunction)
            CY_SET_REG16(RobotArm_Servo_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(RobotArm_Servo_COMPARE1_LSB_PTR, compare);
        #endif /* (RobotArm_Servo_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: RobotArm_Servo_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RobotArm_Servo_WriteCompare2(uint16 compare) \
                                        
    {
        #if(RobotArm_Servo_UsingFixedFunction)
            CY_SET_REG16(RobotArm_Servo_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(RobotArm_Servo_COMPARE2_LSB_PTR, compare);
        #endif /* (RobotArm_Servo_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (RobotArm_Servo_DeadBandUsed)


    /*******************************************************************************
    * Function Name: RobotArm_Servo_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RobotArm_Servo_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!RobotArm_Servo_DeadBand2_4)
            CY_SET_REG8(RobotArm_Servo_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            RobotArm_Servo_DEADBAND_COUNT &= ((uint8)(~RobotArm_Servo_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(RobotArm_Servo_DEADBAND_COUNT_SHIFT)
                RobotArm_Servo_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << RobotArm_Servo_DEADBAND_COUNT_SHIFT)) &
                                                    RobotArm_Servo_DEADBAND_COUNT_MASK;
            #else
                RobotArm_Servo_DEADBAND_COUNT |= deadtime & RobotArm_Servo_DEADBAND_COUNT_MASK;
            #endif /* (RobotArm_Servo_DEADBAND_COUNT_SHIFT) */

        #endif /* (!RobotArm_Servo_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: RobotArm_Servo_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 RobotArm_Servo_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!RobotArm_Servo_DeadBand2_4)
            return (CY_GET_REG8(RobotArm_Servo_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(RobotArm_Servo_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(RobotArm_Servo_DEADBAND_COUNT & RobotArm_Servo_DEADBAND_COUNT_MASK)) >>
                                                                           RobotArm_Servo_DEADBAND_COUNT_SHIFT));
            #else
                return (RobotArm_Servo_DEADBAND_COUNT & RobotArm_Servo_DEADBAND_COUNT_MASK);
            #endif /* (RobotArm_Servo_DEADBAND_COUNT_SHIFT) */
        #endif /* (!RobotArm_Servo_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (RobotArm_Servo_UseStatus || RobotArm_Servo_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: RobotArm_Servo_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RobotArm_Servo_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(RobotArm_Servo_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: RobotArm_Servo_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 RobotArm_Servo_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(RobotArm_Servo_STATUS_PTR));
    }

#endif /* (RobotArm_Servo_UseStatus || RobotArm_Servo_UsingFixedFunction) */


#if (RobotArm_Servo_UseControl)


    /*******************************************************************************
    * Function Name: RobotArm_Servo_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 RobotArm_Servo_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(RobotArm_Servo_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: RobotArm_Servo_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RobotArm_Servo_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(RobotArm_Servo_CONTROL_PTR, control);
    }

#endif /* (RobotArm_Servo_UseControl) */


#if (!RobotArm_Servo_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: RobotArm_Servo_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 RobotArm_Servo_ReadCapture(void) 
    {
        return (CY_GET_REG16(RobotArm_Servo_CAPTURE_LSB_PTR));
    }

#endif /* (!RobotArm_Servo_UsingFixedFunction) */


#if (RobotArm_Servo_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: RobotArm_Servo_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 RobotArm_Servo_ReadCompare(void) 
    {
        #if(RobotArm_Servo_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(RobotArm_Servo_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(RobotArm_Servo_COMPARE1_LSB_PTR));
        #endif /* (RobotArm_Servo_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: RobotArm_Servo_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 RobotArm_Servo_ReadCompare1(void) 
    {
        return (CY_GET_REG16(RobotArm_Servo_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: RobotArm_Servo_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 RobotArm_Servo_ReadCompare2(void) 
    {
        return (CY_GET_REG16(RobotArm_Servo_COMPARE2_LSB_PTR));
    }

#endif /* (RobotArm_Servo_UseOneCompareMode) */


/*******************************************************************************
* Function Name: RobotArm_Servo_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 RobotArm_Servo_ReadPeriod(void) 
{
    #if(RobotArm_Servo_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(RobotArm_Servo_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(RobotArm_Servo_PERIOD_LSB_PTR));
    #endif /* (RobotArm_Servo_UsingFixedFunction) */
}

#if ( RobotArm_Servo_KillModeMinTime)


    /*******************************************************************************
    * Function Name: RobotArm_Servo_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void RobotArm_Servo_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(RobotArm_Servo_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: RobotArm_Servo_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 RobotArm_Servo_ReadKillTime(void) 
    {
        return (CY_GET_REG8(RobotArm_Servo_KILLMODEMINTIME_PTR));
    }

#endif /* ( RobotArm_Servo_KillModeMinTime) */

/* [] END OF FILE */
