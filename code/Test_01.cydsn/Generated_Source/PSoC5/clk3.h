/*******************************************************************************
* File Name: clk3.h
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

#if !defined(CY_CLOCK_clk3_H)
#define CY_CLOCK_clk3_H

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

void clk3_Start(void) ;
void clk3_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clk3_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clk3_StandbyPower(uint8 state) ;
void clk3_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clk3_GetDividerRegister(void) ;
void clk3_SetModeRegister(uint8 modeBitMask) ;
void clk3_ClearModeRegister(uint8 modeBitMask) ;
uint8 clk3_GetModeRegister(void) ;
void clk3_SetSourceRegister(uint8 clkSource) ;
uint8 clk3_GetSourceRegister(void) ;
#if defined(clk3__CFG3)
void clk3_SetPhaseRegister(uint8 clkPhase) ;
uint8 clk3_GetPhaseRegister(void) ;
#endif /* defined(clk3__CFG3) */

#define clk3_Enable()                       clk3_Start()
#define clk3_Disable()                      clk3_Stop()
#define clk3_SetDivider(clkDivider)         clk3_SetDividerRegister(clkDivider, 1u)
#define clk3_SetDividerValue(clkDivider)    clk3_SetDividerRegister((clkDivider) - 1u, 1u)
#define clk3_SetMode(clkMode)               clk3_SetModeRegister(clkMode)
#define clk3_SetSource(clkSource)           clk3_SetSourceRegister(clkSource)
#if defined(clk3__CFG3)
#define clk3_SetPhase(clkPhase)             clk3_SetPhaseRegister(clkPhase)
#define clk3_SetPhaseValue(clkPhase)        clk3_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clk3__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clk3_CLKEN              (* (reg8 *) clk3__PM_ACT_CFG)
#define clk3_CLKEN_PTR          ((reg8 *) clk3__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clk3_CLKSTBY            (* (reg8 *) clk3__PM_STBY_CFG)
#define clk3_CLKSTBY_PTR        ((reg8 *) clk3__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clk3_DIV_LSB            (* (reg8 *) clk3__CFG0)
#define clk3_DIV_LSB_PTR        ((reg8 *) clk3__CFG0)
#define clk3_DIV_PTR            ((reg16 *) clk3__CFG0)

/* Clock MSB divider configuration register. */
#define clk3_DIV_MSB            (* (reg8 *) clk3__CFG1)
#define clk3_DIV_MSB_PTR        ((reg8 *) clk3__CFG1)

/* Mode and source configuration register */
#define clk3_MOD_SRC            (* (reg8 *) clk3__CFG2)
#define clk3_MOD_SRC_PTR        ((reg8 *) clk3__CFG2)

#if defined(clk3__CFG3)
/* Analog clock phase configuration register */
#define clk3_PHASE              (* (reg8 *) clk3__CFG3)
#define clk3_PHASE_PTR          ((reg8 *) clk3__CFG3)
#endif /* defined(clk3__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clk3_CLKEN_MASK         clk3__PM_ACT_MSK
#define clk3_CLKSTBY_MASK       clk3__PM_STBY_MSK

/* CFG2 field masks */
#define clk3_SRC_SEL_MSK        clk3__CFG2_SRC_SEL_MASK
#define clk3_MODE_MASK          (~(clk3_SRC_SEL_MSK))

#if defined(clk3__CFG3)
/* CFG3 phase mask */
#define clk3_PHASE_MASK         clk3__CFG3_PHASE_DLY_MASK
#endif /* defined(clk3__CFG3) */

#endif /* CY_CLOCK_clk3_H */


/* [] END OF FILE */
