/*******************************************************************************
* File Name: Forwad_R.h  
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

#if !defined(CY_PINS_Forwad_R_H) /* Pins Forwad_R_H */
#define CY_PINS_Forwad_R_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Forwad_R_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Forwad_R__PORT == 15 && ((Forwad_R__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Forwad_R_Write(uint8 value);
void    Forwad_R_SetDriveMode(uint8 mode);
uint8   Forwad_R_ReadDataReg(void);
uint8   Forwad_R_Read(void);
void    Forwad_R_SetInterruptMode(uint16 position, uint16 mode);
uint8   Forwad_R_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Forwad_R_SetDriveMode() function.
     *  @{
     */
        #define Forwad_R_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Forwad_R_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Forwad_R_DM_RES_UP          PIN_DM_RES_UP
        #define Forwad_R_DM_RES_DWN         PIN_DM_RES_DWN
        #define Forwad_R_DM_OD_LO           PIN_DM_OD_LO
        #define Forwad_R_DM_OD_HI           PIN_DM_OD_HI
        #define Forwad_R_DM_STRONG          PIN_DM_STRONG
        #define Forwad_R_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Forwad_R_MASK               Forwad_R__MASK
#define Forwad_R_SHIFT              Forwad_R__SHIFT
#define Forwad_R_WIDTH              1u

/* Interrupt constants */
#if defined(Forwad_R__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Forwad_R_SetInterruptMode() function.
     *  @{
     */
        #define Forwad_R_INTR_NONE      (uint16)(0x0000u)
        #define Forwad_R_INTR_RISING    (uint16)(0x0001u)
        #define Forwad_R_INTR_FALLING   (uint16)(0x0002u)
        #define Forwad_R_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Forwad_R_INTR_MASK      (0x01u) 
#endif /* (Forwad_R__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Forwad_R_PS                     (* (reg8 *) Forwad_R__PS)
/* Data Register */
#define Forwad_R_DR                     (* (reg8 *) Forwad_R__DR)
/* Port Number */
#define Forwad_R_PRT_NUM                (* (reg8 *) Forwad_R__PRT) 
/* Connect to Analog Globals */                                                  
#define Forwad_R_AG                     (* (reg8 *) Forwad_R__AG)                       
/* Analog MUX bux enable */
#define Forwad_R_AMUX                   (* (reg8 *) Forwad_R__AMUX) 
/* Bidirectional Enable */                                                        
#define Forwad_R_BIE                    (* (reg8 *) Forwad_R__BIE)
/* Bit-mask for Aliased Register Access */
#define Forwad_R_BIT_MASK               (* (reg8 *) Forwad_R__BIT_MASK)
/* Bypass Enable */
#define Forwad_R_BYP                    (* (reg8 *) Forwad_R__BYP)
/* Port wide control signals */                                                   
#define Forwad_R_CTL                    (* (reg8 *) Forwad_R__CTL)
/* Drive Modes */
#define Forwad_R_DM0                    (* (reg8 *) Forwad_R__DM0) 
#define Forwad_R_DM1                    (* (reg8 *) Forwad_R__DM1)
#define Forwad_R_DM2                    (* (reg8 *) Forwad_R__DM2) 
/* Input Buffer Disable Override */
#define Forwad_R_INP_DIS                (* (reg8 *) Forwad_R__INP_DIS)
/* LCD Common or Segment Drive */
#define Forwad_R_LCD_COM_SEG            (* (reg8 *) Forwad_R__LCD_COM_SEG)
/* Enable Segment LCD */
#define Forwad_R_LCD_EN                 (* (reg8 *) Forwad_R__LCD_EN)
/* Slew Rate Control */
#define Forwad_R_SLW                    (* (reg8 *) Forwad_R__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Forwad_R_PRTDSI__CAPS_SEL       (* (reg8 *) Forwad_R__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Forwad_R_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Forwad_R__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Forwad_R_PRTDSI__OE_SEL0        (* (reg8 *) Forwad_R__PRTDSI__OE_SEL0) 
#define Forwad_R_PRTDSI__OE_SEL1        (* (reg8 *) Forwad_R__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Forwad_R_PRTDSI__OUT_SEL0       (* (reg8 *) Forwad_R__PRTDSI__OUT_SEL0) 
#define Forwad_R_PRTDSI__OUT_SEL1       (* (reg8 *) Forwad_R__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Forwad_R_PRTDSI__SYNC_OUT       (* (reg8 *) Forwad_R__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Forwad_R__SIO_CFG)
    #define Forwad_R_SIO_HYST_EN        (* (reg8 *) Forwad_R__SIO_HYST_EN)
    #define Forwad_R_SIO_REG_HIFREQ     (* (reg8 *) Forwad_R__SIO_REG_HIFREQ)
    #define Forwad_R_SIO_CFG            (* (reg8 *) Forwad_R__SIO_CFG)
    #define Forwad_R_SIO_DIFF           (* (reg8 *) Forwad_R__SIO_DIFF)
#endif /* (Forwad_R__SIO_CFG) */

/* Interrupt Registers */
#if defined(Forwad_R__INTSTAT)
    #define Forwad_R_INTSTAT            (* (reg8 *) Forwad_R__INTSTAT)
    #define Forwad_R_SNAP               (* (reg8 *) Forwad_R__SNAP)
    
	#define Forwad_R_0_INTTYPE_REG 		(* (reg8 *) Forwad_R__0__INTTYPE)
#endif /* (Forwad_R__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Forwad_R_H */


/* [] END OF FILE */
