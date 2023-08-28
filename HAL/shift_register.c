/*
=======================================================================================================================
Author       : Mamoun
Module       : Shift Register
File Name    : shift_register.c
Date Created : Aug 9, 2023
Description  : Source file for the 74HC595 shift register driver.
=======================================================================================================================
*/


/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "shift_register.h"
#include "../MCAL/gpio.h"
#include "../OTHERS/common_macros.h"
#include <util/delay.h>

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : HC595_init
 * [Description]   : Initialize a specific shift register by setting its pins direction and its initial states.
 * [Arguments]     : <a_registerPins>      -> Pointer to a structure stores the ports and the pins
 *                                            of a specific register (Clock - Data - Latch).
 * [return]        : The function returns void.
 ====================================================================================================================*/
void HC595_init(HC595_registerPinsType* a_registerPins)
{
	GPIO_setupPinDirection(a_registerPins->clock_port_ID,a_registerPins->clock_pin_ID,OUTPUT_PIN);
	GPIO_writePin(a_registerPins->clock_port_ID,a_registerPins->clock_pin_ID,LOW_PIN);

	GPIO_setupPinDirection(a_registerPins->data_port_ID,a_registerPins->data_pin_ID,OUTPUT_PIN);
	GPIO_writePin(a_registerPins->data_port_ID,a_registerPins->data_pin_ID,LOW_PIN);

	GPIO_setupPinDirection(a_registerPins->latch_port_ID,a_registerPins->latch_pin_ID,OUTPUT_PIN);
	GPIO_writePin(a_registerPins->latch_port_ID,a_registerPins->latch_pin_ID,LOW_PIN);
}

/*=====================================================================================================================
 * [Function Name] : HC595_updatedShiftRegister
 * [Description]   : Update the shift register with a specific value and a specific number of bits.
 * [Arguments]     : <a_registerPins>      -> Pointer to a structure stores the ports and the pins
 *                                            of a specific register (Clock - Data - Latch).
 *                   <a_numberOfBits>      -> Indicates to the number of bits to be shifted.
 *                   <a_value>             -> Indicates to the value that the register will be shifted with.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void HC595_updatedShiftRegister(HC595_registerPinsType* a_registerPins, uint8 a_numberOfBits, uint8 a_value)
{
	GPIO_writePin(a_registerPins->latch_port_ID,a_registerPins->latch_pin_ID,LOW_PIN);

	for(uint8 bit_counter = 0; bit_counter < a_numberOfBits; bit_counter++)
	{
		GPIO_writePin(a_registerPins->data_port_ID,a_registerPins->data_pin_ID,GET_BIT(a_value,bit_counter));
		GPIO_writePin(a_registerPins->clock_port_ID,a_registerPins->clock_pin_ID,HIGH_PIN);
		_delay_us(CLOCK_PULSE_WIDTH);
		GPIO_writePin(a_registerPins->clock_port_ID,a_registerPins->clock_pin_ID,LOW_PIN);
	}

	GPIO_writePin(a_registerPins->latch_port_ID,a_registerPins->latch_pin_ID,HIGH_PIN);
}
