/*******************************************************************************
* File Name: Color_S1.h  
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

#if !defined(CY_PINS_Color_S1_H) /* Pins Color_S1_H */
#define CY_PINS_Color_S1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Color_S1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Color_S1__PORT == 15 && ((Color_S1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Color_S1_Write(uint8 value);
void    Color_S1_SetDriveMode(uint8 mode);
uint8   Color_S1_ReadDataReg(void);
uint8   Color_S1_Read(void);
void    Color_S1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Color_S1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Color_S1_SetDriveMode() function.
     *  @{
     */
        #define Color_S1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Color_S1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Color_S1_DM_RES_UP          PIN_DM_RES_UP
        #define Color_S1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Color_S1_DM_OD_LO           PIN_DM_OD_LO
        #define Color_S1_DM_OD_HI           PIN_DM_OD_HI
        #define Color_S1_DM_STRONG          PIN_DM_STRONG
        #define Color_S1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Color_S1_MASK               Color_S1__MASK
#define Color_S1_SHIFT              Color_S1__SHIFT
#define Color_S1_WIDTH              1u

/* Interrupt constants */
#if defined(Color_S1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Color_S1_SetInterruptMode() function.
     *  @{
     */
        #define Color_S1_INTR_NONE      (uint16)(0x0000u)
        #define Color_S1_INTR_RISING    (uint16)(0x0001u)
        #define Color_S1_INTR_FALLING   (uint16)(0x0002u)
        #define Color_S1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Color_S1_INTR_MASK      (0x01u) 
#endif /* (Color_S1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Color_S1_PS                     (* (reg8 *) Color_S1__PS)
/* Data Register */
#define Color_S1_DR                     (* (reg8 *) Color_S1__DR)
/* Port Number */
#define Color_S1_PRT_NUM                (* (reg8 *) Color_S1__PRT) 
/* Connect to Analog Globals */                                                  
#define Color_S1_AG                     (* (reg8 *) Color_S1__AG)                       
/* Analog MUX bux enable */
#define Color_S1_AMUX                   (* (reg8 *) Color_S1__AMUX) 
/* Bidirectional Enable */                                                        
#define Color_S1_BIE                    (* (reg8 *) Color_S1__BIE)
/* Bit-mask for Aliased Register Access */
#define Color_S1_BIT_MASK               (* (reg8 *) Color_S1__BIT_MASK)
/* Bypass Enable */
#define Color_S1_BYP                    (* (reg8 *) Color_S1__BYP)
/* Port wide control signals */                                                   
#define Color_S1_CTL                    (* (reg8 *) Color_S1__CTL)
/* Drive Modes */
#define Color_S1_DM0                    (* (reg8 *) Color_S1__DM0) 
#define Color_S1_DM1                    (* (reg8 *) Color_S1__DM1)
#define Color_S1_DM2                    (* (reg8 *) Color_S1__DM2) 
/* Input Buffer Disable Override */
#define Color_S1_INP_DIS                (* (reg8 *) Color_S1__INP_DIS)
/* LCD Common or Segment Drive */
#define Color_S1_LCD_COM_SEG            (* (reg8 *) Color_S1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Color_S1_LCD_EN                 (* (reg8 *) Color_S1__LCD_EN)
/* Slew Rate Control */
#define Color_S1_SLW                    (* (reg8 *) Color_S1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Color_S1_PRTDSI__CAPS_SEL       (* (reg8 *) Color_S1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Color_S1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Color_S1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Color_S1_PRTDSI__OE_SEL0        (* (reg8 *) Color_S1__PRTDSI__OE_SEL0) 
#define Color_S1_PRTDSI__OE_SEL1        (* (reg8 *) Color_S1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Color_S1_PRTDSI__OUT_SEL0       (* (reg8 *) Color_S1__PRTDSI__OUT_SEL0) 
#define Color_S1_PRTDSI__OUT_SEL1       (* (reg8 *) Color_S1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Color_S1_PRTDSI__SYNC_OUT       (* (reg8 *) Color_S1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Color_S1__SIO_CFG)
    #define Color_S1_SIO_HYST_EN        (* (reg8 *) Color_S1__SIO_HYST_EN)
    #define Color_S1_SIO_REG_HIFREQ     (* (reg8 *) Color_S1__SIO_REG_HIFREQ)
    #define Color_S1_SIO_CFG            (* (reg8 *) Color_S1__SIO_CFG)
    #define Color_S1_SIO_DIFF           (* (reg8 *) Color_S1__SIO_DIFF)
#endif /* (Color_S1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Color_S1__INTSTAT)
    #define Color_S1_INTSTAT            (* (reg8 *) Color_S1__INTSTAT)
    #define Color_S1_SNAP               (* (reg8 *) Color_S1__SNAP)
    
	#define Color_S1_0_INTTYPE_REG 		(* (reg8 *) Color_S1__0__INTTYPE)
#endif /* (Color_S1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Color_S1_H */


/* [] END OF FILE */
