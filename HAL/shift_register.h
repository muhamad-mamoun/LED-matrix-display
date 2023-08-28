/*
=======================================================================================================================
Author       : Mamoun
Module       : Shift Register
File Name    : shift_register.h
Date Created : Aug 9, 2023
Description  : Header file for the 74HC595 shift register driver.
=======================================================================================================================
*/


#ifndef HAL_SHIFT_REGISTER_H_
#define HAL_SHIFT_REGISTER_H_

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../OTHERS/std_types.h"

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define CLOCK_PULSE_WIDTH                  (2U)        /* Microseconds */

/*=====================================================================================================================
                                       < Shared Global Variables >
=====================================================================================================================*/



/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef struct
{
	uint8 clock_port_ID;
	uint8 clock_pin_ID;
	uint8 data_port_ID;
	uint8 data_pin_ID;
	uint8 latch_port_ID;
	uint8 latch_pin_ID;
}HC595_registerPinsType;

/*=====================================================================================================================
                                         < Function-like Macros >
=====================================================================================================================*/



/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/


/*=====================================================================================================================
 * [Function Name] : HC595_init
 * [Description]   : Initialize a specific shift register by setting its pins direction and its initial states.
 * [Arguments]     : <a_registerPins>      -> Pointer to a structure stores the ports and the pins
 *                                            of a specific register (Clock - Data - Latch).
 * [return]        : The function returns void.
 ====================================================================================================================*/
void HC595_init(HC595_registerPinsType* a_registerPins);


/*=====================================================================================================================
 * [Function Name] : HC595_updatedShiftRegister
 * [Description]   : Update the shift register with a specific value and a specific number of bits.
 * [Arguments]     : <a_registerPins>      -> Pointer to a structure stores the ports and the pins
 *                                            of a specific register (Clock - Data - Latch).
 *                   <a_numberOfBits>      -> Indicates to the number of bits to be shifted.
 *                   <a_value>             -> Indicates to the value that the register will be shifted with.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void HC595_updatedShiftRegister(HC595_registerPinsType* a_registerPins, uint8 a_numberOfBits, uint8 a_value);


#endif /* HAL_SHIFT_REGISTER_H_ */
