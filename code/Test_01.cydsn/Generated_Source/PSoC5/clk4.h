/*******************************************************************************
* File Name: clk4.h
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

#if !defined(CY_CLOCK_clk4_H)
#define CY_CLOCK_clk4_H

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

void clk4_Start(void) ;
void clk4_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clk4_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clk4_StandbyPower(uint8 state) ;
void clk4_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clk4_GetDividerRegister(void) ;
void clk4_SetModeRegister(uint8 modeBitMask) ;
void clk4_ClearModeRegister(uint8 modeBitMask) ;
uint8 clk4_GetModeRegister(void) ;
void clk4_SetSourceRegister(uint8 clkSource) ;
uint8 clk4_GetSourceRegister(void) ;
#if defined(clk4__CFG3)
void clk4_SetPhaseRegister(uint8 clkPhase) ;
uint8 clk4_GetPhaseRegister(void) ;
#endif /* defined(clk4__CFG3) */

#define clk4_Enable()                       clk4_Start()
#define clk4_Disable()                      clk4_Stop()
#define clk4_SetDivider(clkDivider)         clk4_SetDividerRegister(clkDivider, 1u)
#define clk4_SetDividerValue(clkDivider)    clk4_SetDividerRegister((clkDivider) - 1u, 1u)
#define clk4_SetMode(clkMode)               clk4_SetModeRegister(clkMode)
#define clk4_SetSource(clkSource)           clk4_SetSourceRegister(clkSource)
#if defined(clk4__CFG3)
#define clk4_SetPhase(clkPhase)             clk4_SetPhaseRegister(clkPhase)
#define clk4_SetPhaseValue(clkPhase)        clk4_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clk4__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clk4_CLKEN              (* (reg8 *) clk4__PM_ACT_CFG)
#define clk4_CLKEN_PTR          ((reg8 *) clk4__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clk4_CLKSTBY            (* (reg8 *) clk4__PM_STBY_CFG)
#define clk4_CLKSTBY_PTR        ((reg8 *) clk4__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clk4_DIV_LSB            (* (reg8 *) clk4__CFG0)
#define clk4_DIV_LSB_PTR        ((reg8 *) clk4__CFG0)
#define clk4_DIV_PTR            ((reg16 *) clk4__CFG0)

/* Clock MSB divider configuration register. */
#define clk4_DIV_MSB            (* (reg8 *) clk4__CFG1)
#define clk4_DIV_MSB_PTR        ((reg8 *) clk4__CFG1)

/* Mode and source configuration register */
#define clk4_MOD_SRC            (* (reg8 *) clk4__CFG2)
#define clk4_MOD_SRC_PTR        ((reg8 *) clk4__CFG2)

#if defined(clk4__CFG3)
/* Analog clock phase configuration register */
#define clk4_PHASE              (* (reg8 *) clk4__CFG3)
#define clk4_PHASE_PTR          ((reg8 *) clk4__CFG3)
#endif /* defined(clk4__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clk4_CLKEN_MASK         clk4__PM_ACT_MSK
#define clk4_CLKSTBY_MASK       clk4__PM_STBY_MSK

/* CFG2 field masks */
#define clk4_SRC_SEL_MSK        clk4__CFG2_SRC_SEL_MASK
#define clk4_MODE_MASK          (~(clk4_SRC_SEL_MSK))

#if defined(clk4__CFG3)
/* CFG3 phase mask */
#define clk4_PHASE_MASK         clk4__CFG3_PHASE_DLY_MASK
#endif /* defined(clk4__CFG3) */

#endif /* CY_CLOCK_clk4_H */


/* [] END OF FILE */
