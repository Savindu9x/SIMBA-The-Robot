/*******************************************************************************
* File Name: Rack.h  
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

#if !defined(CY_PINS_Rack_H) /* Pins Rack_H */
#define CY_PINS_Rack_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Rack_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Rack__PORT == 15 && ((Rack__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Rack_Write(uint8 value);
void    Rack_SetDriveMode(uint8 mode);
uint8   Rack_ReadDataReg(void);
uint8   Rack_Read(void);
void    Rack_SetInterruptMode(uint16 position, uint16 mode);
uint8   Rack_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Rack_SetDriveMode() function.
     *  @{
     */
        #define Rack_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Rack_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Rack_DM_RES_UP          PIN_DM_RES_UP
        #define Rack_DM_RES_DWN         PIN_DM_RES_DWN
        #define Rack_DM_OD_LO           PIN_DM_OD_LO
        #define Rack_DM_OD_HI           PIN_DM_OD_HI
        #define Rack_DM_STRONG          PIN_DM_STRONG
        #define Rack_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Rack_MASK               Rack__MASK
#define Rack_SHIFT              Rack__SHIFT
#define Rack_WIDTH              1u

/* Interrupt constants */
#if defined(Rack__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Rack_SetInterruptMode() function.
     *  @{
     */
        #define Rack_INTR_NONE      (uint16)(0x0000u)
        #define Rack_INTR_RISING    (uint16)(0x0001u)
        #define Rack_INTR_FALLING   (uint16)(0x0002u)
        #define Rack_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Rack_INTR_MASK      (0x01u) 
#endif /* (Rack__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rack_PS                     (* (reg8 *) Rack__PS)
/* Data Register */
#define Rack_DR                     (* (reg8 *) Rack__DR)
/* Port Number */
#define Rack_PRT_NUM                (* (reg8 *) Rack__PRT) 
/* Connect to Analog Globals */                                                  
#define Rack_AG                     (* (reg8 *) Rack__AG)                       
/* Analog MUX bux enable */
#define Rack_AMUX                   (* (reg8 *) Rack__AMUX) 
/* Bidirectional Enable */                                                        
#define Rack_BIE                    (* (reg8 *) Rack__BIE)
/* Bit-mask for Aliased Register Access */
#define Rack_BIT_MASK               (* (reg8 *) Rack__BIT_MASK)
/* Bypass Enable */
#define Rack_BYP                    (* (reg8 *) Rack__BYP)
/* Port wide control signals */                                                   
#define Rack_CTL                    (* (reg8 *) Rack__CTL)
/* Drive Modes */
#define Rack_DM0                    (* (reg8 *) Rack__DM0) 
#define Rack_DM1                    (* (reg8 *) Rack__DM1)
#define Rack_DM2                    (* (reg8 *) Rack__DM2) 
/* Input Buffer Disable Override */
#define Rack_INP_DIS                (* (reg8 *) Rack__INP_DIS)
/* LCD Common or Segment Drive */
#define Rack_LCD_COM_SEG            (* (reg8 *) Rack__LCD_COM_SEG)
/* Enable Segment LCD */
#define Rack_LCD_EN                 (* (reg8 *) Rack__LCD_EN)
/* Slew Rate Control */
#define Rack_SLW                    (* (reg8 *) Rack__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Rack_PRTDSI__CAPS_SEL       (* (reg8 *) Rack__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Rack_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Rack__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Rack_PRTDSI__OE_SEL0        (* (reg8 *) Rack__PRTDSI__OE_SEL0) 
#define Rack_PRTDSI__OE_SEL1        (* (reg8 *) Rack__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Rack_PRTDSI__OUT_SEL0       (* (reg8 *) Rack__PRTDSI__OUT_SEL0) 
#define Rack_PRTDSI__OUT_SEL1       (* (reg8 *) Rack__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Rack_PRTDSI__SYNC_OUT       (* (reg8 *) Rack__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Rack__SIO_CFG)
    #define Rack_SIO_HYST_EN        (* (reg8 *) Rack__SIO_HYST_EN)
    #define Rack_SIO_REG_HIFREQ     (* (reg8 *) Rack__SIO_REG_HIFREQ)
    #define Rack_SIO_CFG            (* (reg8 *) Rack__SIO_CFG)
    #define Rack_SIO_DIFF           (* (reg8 *) Rack__SIO_DIFF)
#endif /* (Rack__SIO_CFG) */

/* Interrupt Registers */
#if defined(Rack__INTSTAT)
    #define Rack_INTSTAT            (* (reg8 *) Rack__INTSTAT)
    #define Rack_SNAP               (* (reg8 *) Rack__SNAP)
    
	#define Rack_0_INTTYPE_REG 		(* (reg8 *) Rack__0__INTTYPE)
#endif /* (Rack__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Rack_H */


/* [] END OF FILE */
