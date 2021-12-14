/*******************************************************************************
* File Name: PhaseB_R.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PhaseB_R_H) /* Pins PhaseB_R_H */
#define CY_PINS_PhaseB_R_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PhaseB_R_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PhaseB_R__PORT == 15 && ((PhaseB_R__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PhaseB_R_Write(uint8 value);
void    PhaseB_R_SetDriveMode(uint8 mode);
uint8   PhaseB_R_ReadDataReg(void);
uint8   PhaseB_R_Read(void);
void    PhaseB_R_SetInterruptMode(uint16 position, uint16 mode);
uint8   PhaseB_R_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PhaseB_R_SetDriveMode() function.
     *  @{
     */
        #define PhaseB_R_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PhaseB_R_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PhaseB_R_DM_RES_UP          PIN_DM_RES_UP
        #define PhaseB_R_DM_RES_DWN         PIN_DM_RES_DWN
        #define PhaseB_R_DM_OD_LO           PIN_DM_OD_LO
        #define PhaseB_R_DM_OD_HI           PIN_DM_OD_HI
        #define PhaseB_R_DM_STRONG          PIN_DM_STRONG
        #define PhaseB_R_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PhaseB_R_MASK               PhaseB_R__MASK
#define PhaseB_R_SHIFT              PhaseB_R__SHIFT
#define PhaseB_R_WIDTH              1u

/* Interrupt constants */
#if defined(PhaseB_R__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PhaseB_R_SetInterruptMode() function.
     *  @{
     */
        #define PhaseB_R_INTR_NONE      (uint16)(0x0000u)
        #define PhaseB_R_INTR_RISING    (uint16)(0x0001u)
        #define PhaseB_R_INTR_FALLING   (uint16)(0x0002u)
        #define PhaseB_R_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PhaseB_R_INTR_MASK      (0x01u) 
#endif /* (PhaseB_R__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PhaseB_R_PS                     (* (reg8 *) PhaseB_R__PS)
/* Data Register */
#define PhaseB_R_DR                     (* (reg8 *) PhaseB_R__DR)
/* Port Number */
#define PhaseB_R_PRT_NUM                (* (reg8 *) PhaseB_R__PRT) 
/* Connect to Analog Globals */                                                  
#define PhaseB_R_AG                     (* (reg8 *) PhaseB_R__AG)                       
/* Analog MUX bux enable */
#define PhaseB_R_AMUX                   (* (reg8 *) PhaseB_R__AMUX) 
/* Bidirectional Enable */                                                        
#define PhaseB_R_BIE                    (* (reg8 *) PhaseB_R__BIE)
/* Bit-mask for Aliased Register Access */
#define PhaseB_R_BIT_MASK               (* (reg8 *) PhaseB_R__BIT_MASK)
/* Bypass Enable */
#define PhaseB_R_BYP                    (* (reg8 *) PhaseB_R__BYP)
/* Port wide control signals */                                                   
#define PhaseB_R_CTL                    (* (reg8 *) PhaseB_R__CTL)
/* Drive Modes */
#define PhaseB_R_DM0                    (* (reg8 *) PhaseB_R__DM0) 
#define PhaseB_R_DM1                    (* (reg8 *) PhaseB_R__DM1)
#define PhaseB_R_DM2                    (* (reg8 *) PhaseB_R__DM2) 
/* Input Buffer Disable Override */
#define PhaseB_R_INP_DIS                (* (reg8 *) PhaseB_R__INP_DIS)
/* LCD Common or Segment Drive */
#define PhaseB_R_LCD_COM_SEG            (* (reg8 *) PhaseB_R__LCD_COM_SEG)
/* Enable Segment LCD */
#define PhaseB_R_LCD_EN                 (* (reg8 *) PhaseB_R__LCD_EN)
/* Slew Rate Control */
#define PhaseB_R_SLW                    (* (reg8 *) PhaseB_R__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PhaseB_R_PRTDSI__CAPS_SEL       (* (reg8 *) PhaseB_R__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PhaseB_R_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PhaseB_R__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PhaseB_R_PRTDSI__OE_SEL0        (* (reg8 *) PhaseB_R__PRTDSI__OE_SEL0) 
#define PhaseB_R_PRTDSI__OE_SEL1        (* (reg8 *) PhaseB_R__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PhaseB_R_PRTDSI__OUT_SEL0       (* (reg8 *) PhaseB_R__PRTDSI__OUT_SEL0) 
#define PhaseB_R_PRTDSI__OUT_SEL1       (* (reg8 *) PhaseB_R__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PhaseB_R_PRTDSI__SYNC_OUT       (* (reg8 *) PhaseB_R__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PhaseB_R__SIO_CFG)
    #define PhaseB_R_SIO_HYST_EN        (* (reg8 *) PhaseB_R__SIO_HYST_EN)
    #define PhaseB_R_SIO_REG_HIFREQ     (* (reg8 *) PhaseB_R__SIO_REG_HIFREQ)
    #define PhaseB_R_SIO_CFG            (* (reg8 *) PhaseB_R__SIO_CFG)
    #define PhaseB_R_SIO_DIFF           (* (reg8 *) PhaseB_R__SIO_DIFF)
#endif /* (PhaseB_R__SIO_CFG) */

/* Interrupt Registers */
#if defined(PhaseB_R__INTSTAT)
    #define PhaseB_R_INTSTAT            (* (reg8 *) PhaseB_R__INTSTAT)
    #define PhaseB_R_SNAP               (* (reg8 *) PhaseB_R__SNAP)
    
	#define PhaseB_R_0_INTTYPE_REG 		(* (reg8 *) PhaseB_R__0__INTTYPE)
#endif /* (PhaseB_R__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PhaseB_R_H */


/* [] END OF FILE */
