/*******************************************************************************
* File Name: S3_Echo.h  
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

#if !defined(CY_PINS_S3_Echo_H) /* Pins S3_Echo_H */
#define CY_PINS_S3_Echo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S3_Echo_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S3_Echo__PORT == 15 && ((S3_Echo__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S3_Echo_Write(uint8 value);
void    S3_Echo_SetDriveMode(uint8 mode);
uint8   S3_Echo_ReadDataReg(void);
uint8   S3_Echo_Read(void);
void    S3_Echo_SetInterruptMode(uint16 position, uint16 mode);
uint8   S3_Echo_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S3_Echo_SetDriveMode() function.
     *  @{
     */
        #define S3_Echo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S3_Echo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S3_Echo_DM_RES_UP          PIN_DM_RES_UP
        #define S3_Echo_DM_RES_DWN         PIN_DM_RES_DWN
        #define S3_Echo_DM_OD_LO           PIN_DM_OD_LO
        #define S3_Echo_DM_OD_HI           PIN_DM_OD_HI
        #define S3_Echo_DM_STRONG          PIN_DM_STRONG
        #define S3_Echo_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S3_Echo_MASK               S3_Echo__MASK
#define S3_Echo_SHIFT              S3_Echo__SHIFT
#define S3_Echo_WIDTH              1u

/* Interrupt constants */
#if defined(S3_Echo__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S3_Echo_SetInterruptMode() function.
     *  @{
     */
        #define S3_Echo_INTR_NONE      (uint16)(0x0000u)
        #define S3_Echo_INTR_RISING    (uint16)(0x0001u)
        #define S3_Echo_INTR_FALLING   (uint16)(0x0002u)
        #define S3_Echo_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S3_Echo_INTR_MASK      (0x01u) 
#endif /* (S3_Echo__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S3_Echo_PS                     (* (reg8 *) S3_Echo__PS)
/* Data Register */
#define S3_Echo_DR                     (* (reg8 *) S3_Echo__DR)
/* Port Number */
#define S3_Echo_PRT_NUM                (* (reg8 *) S3_Echo__PRT) 
/* Connect to Analog Globals */                                                  
#define S3_Echo_AG                     (* (reg8 *) S3_Echo__AG)                       
/* Analog MUX bux enable */
#define S3_Echo_AMUX                   (* (reg8 *) S3_Echo__AMUX) 
/* Bidirectional Enable */                                                        
#define S3_Echo_BIE                    (* (reg8 *) S3_Echo__BIE)
/* Bit-mask for Aliased Register Access */
#define S3_Echo_BIT_MASK               (* (reg8 *) S3_Echo__BIT_MASK)
/* Bypass Enable */
#define S3_Echo_BYP                    (* (reg8 *) S3_Echo__BYP)
/* Port wide control signals */                                                   
#define S3_Echo_CTL                    (* (reg8 *) S3_Echo__CTL)
/* Drive Modes */
#define S3_Echo_DM0                    (* (reg8 *) S3_Echo__DM0) 
#define S3_Echo_DM1                    (* (reg8 *) S3_Echo__DM1)
#define S3_Echo_DM2                    (* (reg8 *) S3_Echo__DM2) 
/* Input Buffer Disable Override */
#define S3_Echo_INP_DIS                (* (reg8 *) S3_Echo__INP_DIS)
/* LCD Common or Segment Drive */
#define S3_Echo_LCD_COM_SEG            (* (reg8 *) S3_Echo__LCD_COM_SEG)
/* Enable Segment LCD */
#define S3_Echo_LCD_EN                 (* (reg8 *) S3_Echo__LCD_EN)
/* Slew Rate Control */
#define S3_Echo_SLW                    (* (reg8 *) S3_Echo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S3_Echo_PRTDSI__CAPS_SEL       (* (reg8 *) S3_Echo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S3_Echo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S3_Echo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S3_Echo_PRTDSI__OE_SEL0        (* (reg8 *) S3_Echo__PRTDSI__OE_SEL0) 
#define S3_Echo_PRTDSI__OE_SEL1        (* (reg8 *) S3_Echo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S3_Echo_PRTDSI__OUT_SEL0       (* (reg8 *) S3_Echo__PRTDSI__OUT_SEL0) 
#define S3_Echo_PRTDSI__OUT_SEL1       (* (reg8 *) S3_Echo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S3_Echo_PRTDSI__SYNC_OUT       (* (reg8 *) S3_Echo__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S3_Echo__SIO_CFG)
    #define S3_Echo_SIO_HYST_EN        (* (reg8 *) S3_Echo__SIO_HYST_EN)
    #define S3_Echo_SIO_REG_HIFREQ     (* (reg8 *) S3_Echo__SIO_REG_HIFREQ)
    #define S3_Echo_SIO_CFG            (* (reg8 *) S3_Echo__SIO_CFG)
    #define S3_Echo_SIO_DIFF           (* (reg8 *) S3_Echo__SIO_DIFF)
#endif /* (S3_Echo__SIO_CFG) */

/* Interrupt Registers */
#if defined(S3_Echo__INTSTAT)
    #define S3_Echo_INTSTAT            (* (reg8 *) S3_Echo__INTSTAT)
    #define S3_Echo_SNAP               (* (reg8 *) S3_Echo__SNAP)
    
	#define S3_Echo_0_INTTYPE_REG 		(* (reg8 *) S3_Echo__0__INTTYPE)
#endif /* (S3_Echo__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S3_Echo_H */


/* [] END OF FILE */
