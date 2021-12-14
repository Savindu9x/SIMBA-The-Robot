/*******************************************************************************
* File Name: Gripper.h  
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

#if !defined(CY_PINS_Gripper_H) /* Pins Gripper_H */
#define CY_PINS_Gripper_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Gripper_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Gripper__PORT == 15 && ((Gripper__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Gripper_Write(uint8 value);
void    Gripper_SetDriveMode(uint8 mode);
uint8   Gripper_ReadDataReg(void);
uint8   Gripper_Read(void);
void    Gripper_SetInterruptMode(uint16 position, uint16 mode);
uint8   Gripper_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Gripper_SetDriveMode() function.
     *  @{
     */
        #define Gripper_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Gripper_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Gripper_DM_RES_UP          PIN_DM_RES_UP
        #define Gripper_DM_RES_DWN         PIN_DM_RES_DWN
        #define Gripper_DM_OD_LO           PIN_DM_OD_LO
        #define Gripper_DM_OD_HI           PIN_DM_OD_HI
        #define Gripper_DM_STRONG          PIN_DM_STRONG
        #define Gripper_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Gripper_MASK               Gripper__MASK
#define Gripper_SHIFT              Gripper__SHIFT
#define Gripper_WIDTH              1u

/* Interrupt constants */
#if defined(Gripper__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Gripper_SetInterruptMode() function.
     *  @{
     */
        #define Gripper_INTR_NONE      (uint16)(0x0000u)
        #define Gripper_INTR_RISING    (uint16)(0x0001u)
        #define Gripper_INTR_FALLING   (uint16)(0x0002u)
        #define Gripper_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Gripper_INTR_MASK      (0x01u) 
#endif /* (Gripper__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Gripper_PS                     (* (reg8 *) Gripper__PS)
/* Data Register */
#define Gripper_DR                     (* (reg8 *) Gripper__DR)
/* Port Number */
#define Gripper_PRT_NUM                (* (reg8 *) Gripper__PRT) 
/* Connect to Analog Globals */                                                  
#define Gripper_AG                     (* (reg8 *) Gripper__AG)                       
/* Analog MUX bux enable */
#define Gripper_AMUX                   (* (reg8 *) Gripper__AMUX) 
/* Bidirectional Enable */                                                        
#define Gripper_BIE                    (* (reg8 *) Gripper__BIE)
/* Bit-mask for Aliased Register Access */
#define Gripper_BIT_MASK               (* (reg8 *) Gripper__BIT_MASK)
/* Bypass Enable */
#define Gripper_BYP                    (* (reg8 *) Gripper__BYP)
/* Port wide control signals */                                                   
#define Gripper_CTL                    (* (reg8 *) Gripper__CTL)
/* Drive Modes */
#define Gripper_DM0                    (* (reg8 *) Gripper__DM0) 
#define Gripper_DM1                    (* (reg8 *) Gripper__DM1)
#define Gripper_DM2                    (* (reg8 *) Gripper__DM2) 
/* Input Buffer Disable Override */
#define Gripper_INP_DIS                (* (reg8 *) Gripper__INP_DIS)
/* LCD Common or Segment Drive */
#define Gripper_LCD_COM_SEG            (* (reg8 *) Gripper__LCD_COM_SEG)
/* Enable Segment LCD */
#define Gripper_LCD_EN                 (* (reg8 *) Gripper__LCD_EN)
/* Slew Rate Control */
#define Gripper_SLW                    (* (reg8 *) Gripper__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Gripper_PRTDSI__CAPS_SEL       (* (reg8 *) Gripper__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Gripper_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Gripper__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Gripper_PRTDSI__OE_SEL0        (* (reg8 *) Gripper__PRTDSI__OE_SEL0) 
#define Gripper_PRTDSI__OE_SEL1        (* (reg8 *) Gripper__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Gripper_PRTDSI__OUT_SEL0       (* (reg8 *) Gripper__PRTDSI__OUT_SEL0) 
#define Gripper_PRTDSI__OUT_SEL1       (* (reg8 *) Gripper__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Gripper_PRTDSI__SYNC_OUT       (* (reg8 *) Gripper__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Gripper__SIO_CFG)
    #define Gripper_SIO_HYST_EN        (* (reg8 *) Gripper__SIO_HYST_EN)
    #define Gripper_SIO_REG_HIFREQ     (* (reg8 *) Gripper__SIO_REG_HIFREQ)
    #define Gripper_SIO_CFG            (* (reg8 *) Gripper__SIO_CFG)
    #define Gripper_SIO_DIFF           (* (reg8 *) Gripper__SIO_DIFF)
#endif /* (Gripper__SIO_CFG) */

/* Interrupt Registers */
#if defined(Gripper__INTSTAT)
    #define Gripper_INTSTAT            (* (reg8 *) Gripper__INTSTAT)
    #define Gripper_SNAP               (* (reg8 *) Gripper__SNAP)
    
	#define Gripper_0_INTTYPE_REG 		(* (reg8 *) Gripper__0__INTTYPE)
#endif /* (Gripper__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Gripper_H */


/* [] END OF FILE */
