/*******************************************************************************
* File Name: Flicker.h  
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

#if !defined(CY_PINS_Flicker_H) /* Pins Flicker_H */
#define CY_PINS_Flicker_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Flicker_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Flicker__PORT == 15 && ((Flicker__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Flicker_Write(uint8 value);
void    Flicker_SetDriveMode(uint8 mode);
uint8   Flicker_ReadDataReg(void);
uint8   Flicker_Read(void);
void    Flicker_SetInterruptMode(uint16 position, uint16 mode);
uint8   Flicker_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Flicker_SetDriveMode() function.
     *  @{
     */
        #define Flicker_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Flicker_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Flicker_DM_RES_UP          PIN_DM_RES_UP
        #define Flicker_DM_RES_DWN         PIN_DM_RES_DWN
        #define Flicker_DM_OD_LO           PIN_DM_OD_LO
        #define Flicker_DM_OD_HI           PIN_DM_OD_HI
        #define Flicker_DM_STRONG          PIN_DM_STRONG
        #define Flicker_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Flicker_MASK               Flicker__MASK
#define Flicker_SHIFT              Flicker__SHIFT
#define Flicker_WIDTH              1u

/* Interrupt constants */
#if defined(Flicker__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Flicker_SetInterruptMode() function.
     *  @{
     */
        #define Flicker_INTR_NONE      (uint16)(0x0000u)
        #define Flicker_INTR_RISING    (uint16)(0x0001u)
        #define Flicker_INTR_FALLING   (uint16)(0x0002u)
        #define Flicker_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Flicker_INTR_MASK      (0x01u) 
#endif /* (Flicker__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Flicker_PS                     (* (reg8 *) Flicker__PS)
/* Data Register */
#define Flicker_DR                     (* (reg8 *) Flicker__DR)
/* Port Number */
#define Flicker_PRT_NUM                (* (reg8 *) Flicker__PRT) 
/* Connect to Analog Globals */                                                  
#define Flicker_AG                     (* (reg8 *) Flicker__AG)                       
/* Analog MUX bux enable */
#define Flicker_AMUX                   (* (reg8 *) Flicker__AMUX) 
/* Bidirectional Enable */                                                        
#define Flicker_BIE                    (* (reg8 *) Flicker__BIE)
/* Bit-mask for Aliased Register Access */
#define Flicker_BIT_MASK               (* (reg8 *) Flicker__BIT_MASK)
/* Bypass Enable */
#define Flicker_BYP                    (* (reg8 *) Flicker__BYP)
/* Port wide control signals */                                                   
#define Flicker_CTL                    (* (reg8 *) Flicker__CTL)
/* Drive Modes */
#define Flicker_DM0                    (* (reg8 *) Flicker__DM0) 
#define Flicker_DM1                    (* (reg8 *) Flicker__DM1)
#define Flicker_DM2                    (* (reg8 *) Flicker__DM2) 
/* Input Buffer Disable Override */
#define Flicker_INP_DIS                (* (reg8 *) Flicker__INP_DIS)
/* LCD Common or Segment Drive */
#define Flicker_LCD_COM_SEG            (* (reg8 *) Flicker__LCD_COM_SEG)
/* Enable Segment LCD */
#define Flicker_LCD_EN                 (* (reg8 *) Flicker__LCD_EN)
/* Slew Rate Control */
#define Flicker_SLW                    (* (reg8 *) Flicker__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Flicker_PRTDSI__CAPS_SEL       (* (reg8 *) Flicker__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Flicker_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Flicker__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Flicker_PRTDSI__OE_SEL0        (* (reg8 *) Flicker__PRTDSI__OE_SEL0) 
#define Flicker_PRTDSI__OE_SEL1        (* (reg8 *) Flicker__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Flicker_PRTDSI__OUT_SEL0       (* (reg8 *) Flicker__PRTDSI__OUT_SEL0) 
#define Flicker_PRTDSI__OUT_SEL1       (* (reg8 *) Flicker__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Flicker_PRTDSI__SYNC_OUT       (* (reg8 *) Flicker__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Flicker__SIO_CFG)
    #define Flicker_SIO_HYST_EN        (* (reg8 *) Flicker__SIO_HYST_EN)
    #define Flicker_SIO_REG_HIFREQ     (* (reg8 *) Flicker__SIO_REG_HIFREQ)
    #define Flicker_SIO_CFG            (* (reg8 *) Flicker__SIO_CFG)
    #define Flicker_SIO_DIFF           (* (reg8 *) Flicker__SIO_DIFF)
#endif /* (Flicker__SIO_CFG) */

/* Interrupt Registers */
#if defined(Flicker__INTSTAT)
    #define Flicker_INTSTAT            (* (reg8 *) Flicker__INTSTAT)
    #define Flicker_SNAP               (* (reg8 *) Flicker__SNAP)
    
	#define Flicker_0_INTTYPE_REG 		(* (reg8 *) Flicker__0__INTTYPE)
#endif /* (Flicker__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Flicker_H */


/* [] END OF FILE */
