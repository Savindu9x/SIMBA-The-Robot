/*******************************************************************************
* File Name: clk2.h
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

#if !defined(CY_CLOCK_clk2_H)
#define CY_CLOCK_clk2_H

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

void clk2_Start(void) ;
void clk2_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clk2_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clk2_StandbyPower(uint8 state) ;
void clk2_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clk2_GetDividerRegister(void) ;
void clk2_SetModeRegister(uint8 modeBitMask) ;
void clk2_ClearModeRegister(uint8 modeBitMask) ;
uint8 clk2_GetModeRegister(void) ;
void clk2_SetSourceRegister(uint8 clkSource) ;
uint8 clk2_GetSourceRegister(void) ;
#if defined(clk2__CFG3)
void clk2_SetPhaseRegister(uint8 clkPhase) ;
uint8 clk2_GetPhaseRegister(void) ;
#endif /* defined(clk2__CFG3) */

#define clk2_Enable()                       clk2_Start()
#define clk2_Disable()                      clk2_Stop()
#define clk2_SetDivider(clkDivider)         clk2_SetDividerRegister(clkDivider, 1u)
#define clk2_SetDividerValue(clkDivider)    clk2_SetDividerRegister((clkDivider) - 1u, 1u)
#define clk2_SetMode(clkMode)               clk2_SetModeRegister(clkMode)
#define clk2_SetSource(clkSource)           clk2_SetSourceRegister(clkSource)
#if defined(clk2__CFG3)
#define clk2_SetPhase(clkPhase)             clk2_SetPhaseRegister(clkPhase)
#define clk2_SetPhaseValue(clkPhase)        clk2_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clk2__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clk2_CLKEN              (* (reg8 *) clk2__PM_ACT_CFG)
#define clk2_CLKEN_PTR          ((reg8 *) clk2__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clk2_CLKSTBY            (* (reg8 *) clk2__PM_STBY_CFG)
#define clk2_CLKSTBY_PTR        ((reg8 *) clk2__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clk2_DIV_LSB            (* (reg8 *) clk2__CFG0)
#define clk2_DIV_LSB_PTR        ((reg8 *) clk2__CFG0)
#define clk2_DIV_PTR            ((reg16 *) clk2__CFG0)

/* Clock MSB divider configuration register. */
#define clk2_DIV_MSB            (* (reg8 *) clk2__CFG1)
#define clk2_DIV_MSB_PTR        ((reg8 *) clk2__CFG1)

/* Mode and source configuration register */
#define clk2_MOD_SRC            (* (reg8 *) clk2__CFG2)
#define clk2_MOD_SRC_PTR        ((reg8 *) clk2__CFG2)

#if defined(clk2__CFG3)
/* Analog clock phase configuration register */
#define clk2_PHASE              (* (reg8 *) clk2__CFG3)
#define clk2_PHASE_PTR          ((reg8 *) clk2__CFG3)
#endif /* defined(clk2__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clk2_CLKEN_MASK         clk2__PM_ACT_MSK
#define clk2_CLKSTBY_MASK       clk2__PM_STBY_MSK

/* CFG2 field masks */
#define clk2_SRC_SEL_MSK        clk2__CFG2_SRC_SEL_MASK
#define clk2_MODE_MASK          (~(clk2_SRC_SEL_MSK))

#if defined(clk2__CFG3)
/* CFG3 phase mask */
#define clk2_PHASE_MASK         clk2__CFG3_PHASE_DLY_MASK
#endif /* defined(clk2__CFG3) */

#endif /* CY_CLOCK_clk2_H */


/* [] END OF FILE */
