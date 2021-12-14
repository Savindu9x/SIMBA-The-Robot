/*******************************************************************************
* File Name: clk6.h
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

#if !defined(CY_CLOCK_clk6_H)
#define CY_CLOCK_clk6_H

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

void clk6_Start(void) ;
void clk6_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clk6_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clk6_StandbyPower(uint8 state) ;
void clk6_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clk6_GetDividerRegister(void) ;
void clk6_SetModeRegister(uint8 modeBitMask) ;
void clk6_ClearModeRegister(uint8 modeBitMask) ;
uint8 clk6_GetModeRegister(void) ;
void clk6_SetSourceRegister(uint8 clkSource) ;
uint8 clk6_GetSourceRegister(void) ;
#if defined(clk6__CFG3)
void clk6_SetPhaseRegister(uint8 clkPhase) ;
uint8 clk6_GetPhaseRegister(void) ;
#endif /* defined(clk6__CFG3) */

#define clk6_Enable()                       clk6_Start()
#define clk6_Disable()                      clk6_Stop()
#define clk6_SetDivider(clkDivider)         clk6_SetDividerRegister(clkDivider, 1u)
#define clk6_SetDividerValue(clkDivider)    clk6_SetDividerRegister((clkDivider) - 1u, 1u)
#define clk6_SetMode(clkMode)               clk6_SetModeRegister(clkMode)
#define clk6_SetSource(clkSource)           clk6_SetSourceRegister(clkSource)
#if defined(clk6__CFG3)
#define clk6_SetPhase(clkPhase)             clk6_SetPhaseRegister(clkPhase)
#define clk6_SetPhaseValue(clkPhase)        clk6_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clk6__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clk6_CLKEN              (* (reg8 *) clk6__PM_ACT_CFG)
#define clk6_CLKEN_PTR          ((reg8 *) clk6__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clk6_CLKSTBY            (* (reg8 *) clk6__PM_STBY_CFG)
#define clk6_CLKSTBY_PTR        ((reg8 *) clk6__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clk6_DIV_LSB            (* (reg8 *) clk6__CFG0)
#define clk6_DIV_LSB_PTR        ((reg8 *) clk6__CFG0)
#define clk6_DIV_PTR            ((reg16 *) clk6__CFG0)

/* Clock MSB divider configuration register. */
#define clk6_DIV_MSB            (* (reg8 *) clk6__CFG1)
#define clk6_DIV_MSB_PTR        ((reg8 *) clk6__CFG1)

/* Mode and source configuration register */
#define clk6_MOD_SRC            (* (reg8 *) clk6__CFG2)
#define clk6_MOD_SRC_PTR        ((reg8 *) clk6__CFG2)

#if defined(clk6__CFG3)
/* Analog clock phase configuration register */
#define clk6_PHASE              (* (reg8 *) clk6__CFG3)
#define clk6_PHASE_PTR          ((reg8 *) clk6__CFG3)
#endif /* defined(clk6__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clk6_CLKEN_MASK         clk6__PM_ACT_MSK
#define clk6_CLKSTBY_MASK       clk6__PM_STBY_MSK

/* CFG2 field masks */
#define clk6_SRC_SEL_MSK        clk6__CFG2_SRC_SEL_MASK
#define clk6_MODE_MASK          (~(clk6_SRC_SEL_MSK))

#if defined(clk6__CFG3)
/* CFG3 phase mask */
#define clk6_PHASE_MASK         clk6__CFG3_PHASE_DLY_MASK
#endif /* defined(clk6__CFG3) */

#endif /* CY_CLOCK_clk6_H */


/* [] END OF FILE */
