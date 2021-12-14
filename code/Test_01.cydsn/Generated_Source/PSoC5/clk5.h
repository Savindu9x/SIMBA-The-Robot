/*******************************************************************************
* File Name: clk5.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_clk5_H)
#define CY_CLOCK_clk5_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void clk5_Start(void) ;
void clk5_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clk5_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clk5_StandbyPower(uint8 state) ;
void clk5_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clk5_GetDividerRegister(void) ;
void clk5_SetModeRegister(uint8 modeBitMask) ;
void clk5_ClearModeRegister(uint8 modeBitMask) ;
uint8 clk5_GetModeRegister(void) ;
void clk5_SetSourceRegister(uint8 clkSource) ;
uint8 clk5_GetSourceRegister(void) ;
#if defined(clk5__CFG3)
void clk5_SetPhaseRegister(uint8 clkPhase) ;
uint8 clk5_GetPhaseRegister(void) ;
#endif /* defined(clk5__CFG3) */

#define clk5_Enable()                       clk5_Start()
#define clk5_Disable()                      clk5_Stop()
#define clk5_SetDivider(clkDivider)         clk5_SetDividerRegister(clkDivider, 1u)
#define clk5_SetDividerValue(clkDivider)    clk5_SetDividerRegister((clkDivider) - 1u, 1u)
#define clk5_SetMode(clkMode)               clk5_SetModeRegister(clkMode)
#define clk5_SetSource(clkSource)           clk5_SetSourceRegister(clkSource)
#if defined(clk5__CFG3)
#define clk5_SetPhase(clkPhase)             clk5_SetPhaseRegister(clkPhase)
#define clk5_SetPhaseValue(clkPhase)        clk5_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clk5__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clk5_CLKEN              (* (reg8 *) clk5__PM_ACT_CFG)
#define clk5_CLKEN_PTR          ((reg8 *) clk5__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clk5_CLKSTBY            (* (reg8 *) clk5__PM_STBY_CFG)
#define clk5_CLKSTBY_PTR        ((reg8 *) clk5__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clk5_DIV_LSB            (* (reg8 *) clk5__CFG0)
#define clk5_DIV_LSB_PTR        ((reg8 *) clk5__CFG0)
#define clk5_DIV_PTR            ((reg16 *) clk5__CFG0)

/* Clock MSB divider configuration register. */
#define clk5_DIV_MSB            (* (reg8 *) clk5__CFG1)
#define clk5_DIV_MSB_PTR        ((reg8 *) clk5__CFG1)

/* Mode and source configuration register */
#define clk5_MOD_SRC            (* (reg8 *) clk5__CFG2)
#define clk5_MOD_SRC_PTR        ((reg8 *) clk5__CFG2)

#if defined(clk5__CFG3)
/* Analog clock phase configuration register */
#define clk5_PHASE              (* (reg8 *) clk5__CFG3)
#define clk5_PHASE_PTR          ((reg8 *) clk5__CFG3)
#endif /* defined(clk5__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clk5_CLKEN_MASK         clk5__PM_ACT_MSK
#define clk5_CLKSTBY_MASK       clk5__PM_STBY_MSK

/* CFG2 field masks */
#define clk5_SRC_SEL_MSK        clk5__CFG2_SRC_SEL_MASK
#define clk5_MODE_MASK          (~(clk5_SRC_SEL_MSK))

#if defined(clk5__CFG3)
/* CFG3 phase mask */
#define clk5_PHASE_MASK         clk5__CFG3_PHASE_DLY_MASK
#endif /* defined(clk5__CFG3) */

#endif /* CY_CLOCK_clk5_H */


/* [] END OF FILE */
