/*
=============================================================================================================
Author       : Mamoun
Module       : LED
File Name    : led.h
Date Created : Aug 31, 2023
Description  : Header file for the LED driver.
=============================================================================================================
*/


#ifndef HAL_LED_H_
#define HAL_LED_H_

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../MCAL/gpio.h"
#include "../OTHERS/std_types.h"

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/


/*===========================================================================================================
 * [Function Name] : LED_init
 * [Description]   : Initialize a specific LED by: - Adjusting its pin direction.
 *                                                 - Disable it in the beginning.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the LED is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LED_init(uint8 a_portID, uint8 a_pinID);


/*===========================================================================================================
 * [Function Name] : LED_on
 * [Description]   : Turn a specific LED ON.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the LED is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LED_on(uint8 a_portID, uint8 a_pinID);


/*===========================================================================================================
 * [Function Name] : LED_off
 * [Description]   : Turn a specific LED OFF.
 * [Arguments]     : <a_portID>     -> Indicates to the port number which the LED is in.
 *                   <a_pinID>      -> Indicates to the pin number.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void LED_off(uint8 a_portID, uint8 a_pinID);

#endif /* HAL_LED_H_ */
