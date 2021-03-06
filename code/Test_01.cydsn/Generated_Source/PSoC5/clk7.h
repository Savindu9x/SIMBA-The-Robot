/*******************************************************************************
* File Name: clk7.h
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

#if !defined(CY_CLOCK_clk7_H)
#define CY_CLOCK_clk7_H

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

void clk7_Start(void) ;
void clk7_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clk7_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clk7_StandbyPower(uint8 state) ;
void clk7_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clk7_GetDividerRegister(void) ;
void clk7_SetModeRegister(uint8 modeBitMask) ;
void clk7_ClearModeRegister(uint8 modeBitMask) ;
uint8 clk7_GetModeRegister(void) ;
void clk7_SetSourceRegister(uint8 clkSource) ;
uint8 clk7_GetSourceRegister(void) ;
#if defined(clk7__CFG3)
void clk7_SetPhaseRegister(uint8 clkPhase) ;
uint8 clk7_GetPhaseRegister(void) ;
#endif /* defined(clk7__CFG3) */

#define clk7_Enable()                       clk7_Start()
#define clk7_Disable()                      clk7_Stop()
#define clk7_SetDivider(clkDivider)         clk7_SetDividerRegister(clkDivider, 1u)
#define clk7_SetDividerValue(clkDivider)    clk7_SetDividerRegister((clkDivider) - 1u, 1u)
#define clk7_SetMode(clkMode)               clk7_SetModeRegister(clkMode)
#define clk7_SetSource(clkSource)           clk7_SetSourceRegister(clkSource)
#if defined(clk7__CFG3)
#define clk7_SetPhase(clkPhase)             clk7_SetPhaseRegister(clkPhase)
#define clk7_SetPhaseValue(clkPhase)        clk7_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clk7__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clk7_CLKEN              (* (reg8 *) clk7__PM_ACT_CFG)
#define clk7_CLKEN_PTR          ((reg8 *) clk7__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clk7_CLKSTBY            (* (reg8 *) clk7__PM_STBY_CFG)
#define clk7_CLKSTBY_PTR        ((reg8 *) clk7__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clk7_DIV_LSB            (* (reg8 *) clk7__CFG0)
#define clk7_DIV_LSB_PTR        ((reg8 *) clk7__CFG0)
#define clk7_DIV_PTR            ((reg16 *) clk7__CFG0)

/* Clock MSB divider configuration register. */
#define clk7_DIV_MSB            (* (reg8 *) clk7__CFG1)
#define clk7_DIV_MSB_PTR        ((reg8 *) clk7__CFG1)

/* Mode and source configuration register */
#define clk7_MOD_SRC            (* (reg8 *) clk7__CFG2)
#define clk7_MOD_SRC_PTR        ((reg8 *) clk7__CFG2)

#if defined(clk7__CFG3)
/* Analog clock phase configuration register */
#define clk7_PHASE              (* (reg8 *) clk7__CFG3)
#define clk7_PHASE_PTR          ((reg8 *) clk7__CFG3)
#endif /* defined(clk7__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clk7_CLKEN_MASK         clk7__PM_ACT_MSK
#define clk7_CLKSTBY_MASK       clk7__PM_STBY_MSK

/* CFG2 field masks */
#define clk7_SRC_SEL_MSK        clk7__CFG2_SRC_SEL_MASK
#define clk7_MODE_MASK          (~(clk7_SRC_SEL_MSK))

#if defined(clk7__CFG3)
/* CFG3 phase mask */
#define clk7_PHASE_MASK         clk7__CFG3_PHASE_DLY_MASK
#endif /* defined(clk7__CFG3) */

#endif /* CY_CLOCK_clk7_H */


/* [] END OF FILE */
