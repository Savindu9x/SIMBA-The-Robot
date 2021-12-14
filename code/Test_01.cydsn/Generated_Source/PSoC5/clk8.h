/*******************************************************************************
* File Name: clk8.h
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

#if !defined(CY_CLOCK_clk8_H)
#define CY_CLOCK_clk8_H

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

void clk8_Start(void) ;
void clk8_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clk8_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clk8_StandbyPower(uint8 state) ;
void clk8_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clk8_GetDividerRegister(void) ;
void clk8_SetModeRegister(uint8 modeBitMask) ;
void clk8_ClearModeRegister(uint8 modeBitMask) ;
uint8 clk8_GetModeRegister(void) ;
void clk8_SetSourceRegister(uint8 clkSource) ;
uint8 clk8_GetSourceRegister(void) ;
#if defined(clk8__CFG3)
void clk8_SetPhaseRegister(uint8 clkPhase) ;
uint8 clk8_GetPhaseRegister(void) ;
#endif /* defined(clk8__CFG3) */

#define clk8_Enable()                       clk8_Start()
#define clk8_Disable()                      clk8_Stop()
#define clk8_SetDivider(clkDivider)         clk8_SetDividerRegister(clkDivider, 1u)
#define clk8_SetDividerValue(clkDivider)    clk8_SetDividerRegister((clkDivider) - 1u, 1u)
#define clk8_SetMode(clkMode)               clk8_SetModeRegister(clkMode)
#define clk8_SetSource(clkSource)           clk8_SetSourceRegister(clkSource)
#if defined(clk8__CFG3)
#define clk8_SetPhase(clkPhase)             clk8_SetPhaseRegister(clkPhase)
#define clk8_SetPhaseValue(clkPhase)        clk8_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clk8__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clk8_CLKEN              (* (reg8 *) clk8__PM_ACT_CFG)
#define clk8_CLKEN_PTR          ((reg8 *) clk8__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clk8_CLKSTBY            (* (reg8 *) clk8__PM_STBY_CFG)
#define clk8_CLKSTBY_PTR        ((reg8 *) clk8__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clk8_DIV_LSB            (* (reg8 *) clk8__CFG0)
#define clk8_DIV_LSB_PTR        ((reg8 *) clk8__CFG0)
#define clk8_DIV_PTR            ((reg16 *) clk8__CFG0)

/* Clock MSB divider configuration register. */
#define clk8_DIV_MSB            (* (reg8 *) clk8__CFG1)
#define clk8_DIV_MSB_PTR        ((reg8 *) clk8__CFG1)

/* Mode and source configuration register */
#define clk8_MOD_SRC            (* (reg8 *) clk8__CFG2)
#define clk8_MOD_SRC_PTR        ((reg8 *) clk8__CFG2)

#if defined(clk8__CFG3)
/* Analog clock phase configuration register */
#define clk8_PHASE              (* (reg8 *) clk8__CFG3)
#define clk8_PHASE_PTR          ((reg8 *) clk8__CFG3)
#endif /* defined(clk8__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clk8_CLKEN_MASK         clk8__PM_ACT_MSK
#define clk8_CLKSTBY_MASK       clk8__PM_STBY_MSK

/* CFG2 field masks */
#define clk8_SRC_SEL_MSK        clk8__CFG2_SRC_SEL_MASK
#define clk8_MODE_MASK          (~(clk8_SRC_SEL_MSK))

#if defined(clk8__CFG3)
/* CFG3 phase mask */
#define clk8_PHASE_MASK         clk8__CFG3_PHASE_DLY_MASK
#endif /* defined(clk8__CFG3) */

#endif /* CY_CLOCK_clk8_H */


/* [] END OF FILE */
