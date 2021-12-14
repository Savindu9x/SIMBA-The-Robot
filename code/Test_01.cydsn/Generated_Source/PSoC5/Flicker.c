/*******************************************************************************
* File Name: Flicker.c  
* Version 2.20
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Flicker.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Flicker__PORT == 15 && ((Flicker__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Flicker_Write
****************************************************************************//**
*
* \brief Writes the value to the physical port (data output register), masking
*  and shifting the bits appropriately. 
*
* The data output register controls the signal applied to the physical pin in 
* conjunction with the drive mode parameter. This function avoids changing 
* other bits in the port by using the appropriate method (read-modify-write or
* bit banding).
*
* <b>Note</b> This function should not be used on a hardware digital output pin 
* as it is driven by the hardware signal attached to it.
*
* \param value
*  Value to write to the component instance.
*
* \return 
*  None 
*
* \sideeffect
*  If you use read-modify-write operations that are not atomic; the Interrupt 
*  Service Routines (ISR) can cause corruption of this function. An ISR that 
*  interrupts this function and performs writes to the Pins component data 
*  register can cause corrupted port data. To avoid this issue, you should 
*  either use the Per-Pin APIs (primary method) or disable interrupts around 
*  this function.
*
* \funcusage
*  \snippet Flicker_SUT.c usage_Flicker_Write
*******************************************************************************/
void Flicker_Write(uint8 value)
{
    uint8 staticBits = (Flicker_DR & (uint8)(~Flicker_MASK));
    Flicker_DR = staticBits | ((uint8)(value << Flicker_SHIFT) & Flicker_MASK);
}


/*******************************************************************************
* Function Name: Flicker_SetDriveMode
****************************************************************************//**
*
* \brief Sets the drive mode for each of the Pins component's pins.
* 
* <b>Note</b> This affects all pins in the Pins component instance. Use the
* Per-Pin APIs if you wish to control individual pin's drive modes.
*
* \param mode
*  Mode for the selected signals. Valid options are documented in 
*  \ref driveMode.
*
* \return
*  None
*
* \sideeffect
*  If you use read-modify-write operations that are not atomic, the ISR can
*  cause corruption of this function. An ISR that interrupts this function 
*  and performs writes to the Pins component Drive Mode registers can cause 
*  corrupted port data. To avoid this issue, you should either use the Per-Pin
*  APIs (primary method) or disable interrupts around this function.
*
* \funcusage
*  \snippet Flicker_SUT.c usage_Flicker_SetDriveMode
*******************************************************************************/
void Flicker_SetDriveMode(uint8 mode)
{
	CyPins_SetPinDriveMode(Flicker_0, mode);
}


/*******************************************************************************
* Function Name: Flicker_Read
****************************************************************************//**
*
* \brief Reads the associated physical port (pin status register) and masks 
*  the required bits according to the width and bit position of the component
*  instance. 
*
* The pin's status register returns the current logic level present on the 
* physical pin.
*
* \return 
*  The current value for the pins in the component as a right justified number.
*
* \funcusage
*  \snippet Flicker_SUT.c usage_Flicker_Read  
*******************************************************************************/
uint8 Flicker_Read(void)
{
    return (Flicker_PS & Flicker_MASK) >> Flicker_SHIFT;
}


/*******************************************************************************
* Function Name: Flicker_ReadDataReg
****************************************************************************//**
*
* \brief Reads the associated physical port's data output register and masks 
*  the correct bits according to the width and bit position of the component 
*  instance. 
*
* The data output register controls the signal applied to the physical pin in 
* conjunction with the drive mode parameter. This is not the same as the 
* preferred Flicker_Read() API because the 
* Flicker_ReadDataReg() reads the data register instead of the status 
* register. For output pins this is a useful function to determine the value 
* just written to the pin.
*
* \return 
*  The current value of the data register masked and shifted into a right 
*  justified number for the component instance.
*
* \funcusage
*  \snippet Flicker_SUT.c usage_Flicker_ReadDataReg 
*******************************************************************************/
uint8 Flicker_ReadDataReg(void)
{
    return (Flicker_DR & Flicker_MASK) >> Flicker_SHIFT;
}


/* If interrupt is connected for this Pins component */ 
#if defined(Flicker_INTSTAT) 

    /*******************************************************************************
    * Function Name: Flicker_SetInterruptMode
    ****************************************************************************//**
    *
    * \brief Configures the interrupt mode for each of the Pins component's
    *  pins. Alternatively you may set the interrupt mode for all the pins
    *  specified in the Pins component.
    *
    *  <b>Note</b> The interrupt is port-wide and therefore any enabled pin
    *  interrupt may trigger it.
    *
    * \param position
    *  The pin position as listed in the Pins component. You may OR these to be 
    *  able to configure the interrupt mode of multiple pins within a Pins 
    *  component. Or you may use Flicker_INTR_ALL to configure the
    *  interrupt mode of all the pins in the Pins component.       
    *  - Flicker_0_INTR       (First pin in the list)
    *  - Flicker_1_INTR       (Second pin in the list)
    *  - ...
    *  - Flicker_INTR_ALL     (All pins in Pins component)
    *
    * \param mode
    *  Interrupt mode for the selected pins. Valid options are documented in
    *  \ref intrMode.
    *
    * \return 
    *  None
    *  
    * \sideeffect
    *  It is recommended that the interrupt be disabled before calling this 
    *  function to avoid unintended interrupt requests. Note that the interrupt
    *  type is port wide, and therefore will trigger for any enabled pin on the 
    *  port.
    *
    * \funcusage
    *  \snippet Flicker_SUT.c usage_Flicker_SetInterruptMode
    *******************************************************************************/
    void Flicker_SetInterruptMode(uint16 position, uint16 mode)
    {
		if((position & Flicker_0_INTR) != 0u) 
		{ 
			 Flicker_0_INTTYPE_REG = (uint8)mode; 
		}
    }
    
    
    /*******************************************************************************
    * Function Name: Flicker_ClearInterrupt
    ****************************************************************************//**
    *
    * \brief Clears any active interrupts attached with the component and returns 
    *  the value of the interrupt status register allowing determination of which
    *  pins generated an interrupt event.
    *
    * \return 
    *  The right-shifted current value of the interrupt status register. Each pin 
    *  has one bit set if it generated an interrupt event. For example, bit 0 is 
    *  for pin 0 and bit 1 is for pin 1 of the Pins component.
    *  
    * \sideeffect
    *  Clears all bits of the physical port's interrupt status register, not just
    *  those associated with the Pins component.
    *
    * \funcusage
    *  \snippet Flicker_SUT.c usage_Flicker_ClearInterrupt
    *******************************************************************************/
    uint8 Flicker_ClearInterrupt(void)
    {
        return (Flicker_INTSTAT & Flicker_MASK) >> Flicker_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
