/*******************************************************************************
* File Name: Backward_R.h  
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

#if !defined(CY_PINS_Backward_R_H) /* Pins Backward_R_H */
#define CY_PINS_Backward_R_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Backward_R_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Backward_R__PORT == 15 && ((Backward_R__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Backward_R_Write(uint8 value);
void    Backward_R_SetDriveMode(uint8 mode);
uint8   Backward_R_ReadDataReg(void);
uint8   Backward_R_Read(void);
void    Backward_R_SetInterruptMode(uint16 position, uint16 mode);
uint8   Backward_R_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Backward_R_SetDriveMode() function.
     *  @{
     */
        #define Backward_R_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Backward_R_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Backward_R_DM_RES_UP          PIN_DM_RES_UP
        #define Backward_R_DM_RES_DWN         PIN_DM_RES_DWN
        #define Backward_R_DM_OD_LO           PIN_DM_OD_LO
        #define Backward_R_DM_OD_HI           PIN_DM_OD_HI
        #define Backward_R_DM_STRONG          PIN_DM_STRONG
        #define Backward_R_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Backward_R_MASK               Backward_R__MASK
#define Backward_R_SHIFT              Backward_R__SHIFT
#define Backward_R_WIDTH              1u

/* Interrupt constants */
#if defined(Backward_R__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Backward_R_SetInterruptMode() function.
     *  @{
     */
        #define Backward_R_INTR_NONE      (uint16)(0x0000u)
        #define Backward_R_INTR_RISING    (uint16)(0x0001u)
        #define Backward_R_INTR_FALLING   (uint16)(0x0002u)
        #define Backward_R_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Backward_R_INTR_MASK      (0x01u) 
#endif /* (Backward_R__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Backward_R_PS                     (* (reg8 *) Backward_R__PS)
/* Data Register */
#define Backward_R_DR                     (* (reg8 *) Backward_R__DR)
/* Port Number */
#define Backward_R_PRT_NUM                (* (reg8 *) Backward_R__PRT) 
/* Connect to Analog Globals */                                                  
#define Backward_R_AG                     (* (reg8 *) Backward_R__AG)                       
/* Analog MUX bux enable */
#define Backward_R_AMUX                   (* (reg8 *) Backward_R__AMUX) 
/* Bidirectional Enable */                                                        
#define Backward_R_BIE                    (* (reg8 *) Backward_R__BIE)
/* Bit-mask for Aliased Register Access */
#define Backward_R_BIT_MASK               (* (reg8 *) Backward_R__BIT_MASK)
/* Bypass Enable */
#define Backward_R_BYP                    (* (reg8 *) Backward_R__BYP)
/* Port wide control signals */                                                   
#define Backward_R_CTL                    (* (reg8 *) Backward_R__CTL)
/* Drive Modes */
#define Backward_R_DM0                    (* (reg8 *) Backward_R__DM0) 
#define Backward_R_DM1                    (* (reg8 *) Backward_R__DM1)
#define Backward_R_DM2                    (* (reg8 *) Backward_R__DM2) 
/* Input Buffer Disable Override */
#define Backward_R_INP_DIS                (* (reg8 *) Backward_R__INP_DIS)
/* LCD Common or Segment Drive */
#define Backward_R_LCD_COM_SEG            (* (reg8 *) Backward_R__LCD_COM_SEG)
/* Enable Segment LCD */
#define Backward_R_LCD_EN                 (* (reg8 *) Backward_R__LCD_EN)
/* Slew Rate Control */
#define Backward_R_SLW                    (* (reg8 *) Backward_R__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Backward_R_PRTDSI__CAPS_SEL       (* (reg8 *) Backward_R__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Backward_R_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Backward_R__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Backward_R_PRTDSI__OE_SEL0        (* (reg8 *) Backward_R__PRTDSI__OE_SEL0) 
#define Backward_R_PRTDSI__OE_SEL1        (* (reg8 *) Backward_R__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Backward_R_PRTDSI__OUT_SEL0       (* (reg8 *) Backward_R__PRTDSI__OUT_SEL0) 
#define Backward_R_PRTDSI__OUT_SEL1       (* (reg8 *) Backward_R__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Backward_R_PRTDSI__SYNC_OUT       (* (reg8 *) Backward_R__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Backward_R__SIO_CFG)
    #define Backward_R_SIO_HYST_EN        (* (reg8 *) Backward_R__SIO_HYST_EN)
    #define Backward_R_SIO_REG_HIFREQ     (* (reg8 *) Backward_R__SIO_REG_HIFREQ)
    #define Backward_R_SIO_CFG            (* (reg8 *) Backward_R__SIO_CFG)
    #define Backward_R_SIO_DIFF           (* (reg8 *) Backward_R__SIO_DIFF)
#endif /* (Backward_R__SIO_CFG) */

/* Interrupt Registers */
#if defined(Backward_R__INTSTAT)
    #define Backward_R_INTSTAT            (* (reg8 *) Backward_R__INTSTAT)
    #define Backward_R_SNAP               (* (reg8 *) Backward_R__SNAP)
    
	#define Backward_R_0_INTTYPE_REG 		(* (reg8 *) Backward_R__0__INTTYPE)
#endif /* (Backward_R__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Backward_R_H */


/* [] END OF FILE */
