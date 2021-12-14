/*******************************************************************************
* File Name: S2_Trigger.h  
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

#if !defined(CY_PINS_S2_Trigger_H) /* Pins S2_Trigger_H */
#define CY_PINS_S2_Trigger_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S2_Trigger_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S2_Trigger__PORT == 15 && ((S2_Trigger__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S2_Trigger_Write(uint8 value);
void    S2_Trigger_SetDriveMode(uint8 mode);
uint8   S2_Trigger_ReadDataReg(void);
uint8   S2_Trigger_Read(void);
void    S2_Trigger_SetInterruptMode(uint16 position, uint16 mode);
uint8   S2_Trigger_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S2_Trigger_SetDriveMode() function.
     *  @{
     */
        #define S2_Trigger_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S2_Trigger_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S2_Trigger_DM_RES_UP          PIN_DM_RES_UP
        #define S2_Trigger_DM_RES_DWN         PIN_DM_RES_DWN
        #define S2_Trigger_DM_OD_LO           PIN_DM_OD_LO
        #define S2_Trigger_DM_OD_HI           PIN_DM_OD_HI
        #define S2_Trigger_DM_STRONG          PIN_DM_STRONG
        #define S2_Trigger_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S2_Trigger_MASK               S2_Trigger__MASK
#define S2_Trigger_SHIFT              S2_Trigger__SHIFT
#define S2_Trigger_WIDTH              1u

/* Interrupt constants */
#if defined(S2_Trigger__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S2_Trigger_SetInterruptMode() function.
     *  @{
     */
        #define S2_Trigger_INTR_NONE      (uint16)(0x0000u)
        #define S2_Trigger_INTR_RISING    (uint16)(0x0001u)
        #define S2_Trigger_INTR_FALLING   (uint16)(0x0002u)
        #define S2_Trigger_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S2_Trigger_INTR_MASK      (0x01u) 
#endif /* (S2_Trigger__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S2_Trigger_PS                     (* (reg8 *) S2_Trigger__PS)
/* Data Register */
#define S2_Trigger_DR                     (* (reg8 *) S2_Trigger__DR)
/* Port Number */
#define S2_Trigger_PRT_NUM                (* (reg8 *) S2_Trigger__PRT) 
/* Connect to Analog Globals */                                                  
#define S2_Trigger_AG                     (* (reg8 *) S2_Trigger__AG)                       
/* Analog MUX bux enable */
#define S2_Trigger_AMUX                   (* (reg8 *) S2_Trigger__AMUX) 
/* Bidirectional Enable */                                                        
#define S2_Trigger_BIE                    (* (reg8 *) S2_Trigger__BIE)
/* Bit-mask for Aliased Register Access */
#define S2_Trigger_BIT_MASK               (* (reg8 *) S2_Trigger__BIT_MASK)
/* Bypass Enable */
#define S2_Trigger_BYP                    (* (reg8 *) S2_Trigger__BYP)
/* Port wide control signals */                                                   
#define S2_Trigger_CTL                    (* (reg8 *) S2_Trigger__CTL)
/* Drive Modes */
#define S2_Trigger_DM0                    (* (reg8 *) S2_Trigger__DM0) 
#define S2_Trigger_DM1                    (* (reg8 *) S2_Trigger__DM1)
#define S2_Trigger_DM2                    (* (reg8 *) S2_Trigger__DM2) 
/* Input Buffer Disable Override */
#define S2_Trigger_INP_DIS                (* (reg8 *) S2_Trigger__INP_DIS)
/* LCD Common or Segment Drive */
#define S2_Trigger_LCD_COM_SEG            (* (reg8 *) S2_Trigger__LCD_COM_SEG)
/* Enable Segment LCD */
#define S2_Trigger_LCD_EN                 (* (reg8 *) S2_Trigger__LCD_EN)
/* Slew Rate Control */
#define S2_Trigger_SLW                    (* (reg8 *) S2_Trigger__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S2_Trigger_PRTDSI__CAPS_SEL       (* (reg8 *) S2_Trigger__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S2_Trigger_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S2_Trigger__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S2_Trigger_PRTDSI__OE_SEL0        (* (reg8 *) S2_Trigger__PRTDSI__OE_SEL0) 
#define S2_Trigger_PRTDSI__OE_SEL1        (* (reg8 *) S2_Trigger__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S2_Trigger_PRTDSI__OUT_SEL0       (* (reg8 *) S2_Trigger__PRTDSI__OUT_SEL0) 
#define S2_Trigger_PRTDSI__OUT_SEL1       (* (reg8 *) S2_Trigger__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S2_Trigger_PRTDSI__SYNC_OUT       (* (reg8 *) S2_Trigger__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S2_Trigger__SIO_CFG)
    #define S2_Trigger_SIO_HYST_EN        (* (reg8 *) S2_Trigger__SIO_HYST_EN)
    #define S2_Trigger_SIO_REG_HIFREQ     (* (reg8 *) S2_Trigger__SIO_REG_HIFREQ)
    #define S2_Trigger_SIO_CFG            (* (reg8 *) S2_Trigger__SIO_CFG)
    #define S2_Trigger_SIO_DIFF           (* (reg8 *) S2_Trigger__SIO_DIFF)
#endif /* (S2_Trigger__SIO_CFG) */

/* Interrupt Registers */
#if defined(S2_Trigger__INTSTAT)
    #define S2_Trigger_INTSTAT            (* (reg8 *) S2_Trigger__INTSTAT)
    #define S2_Trigger_SNAP               (* (reg8 *) S2_Trigger__SNAP)
    
	#define S2_Trigger_0_INTTYPE_REG 		(* (reg8 *) S2_Trigger__0__INTTYPE)
#endif /* (S2_Trigger__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S2_Trigger_H */


/* [] END OF FILE */
