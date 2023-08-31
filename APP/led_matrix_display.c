/*
=======================================================================================================================
Author       : Mamoun
Module       : LED Matrix Display
File Name    : led_matrix_display.c
Date Created : Aug 8, 2023
Description  : Source file for the LED Matrix Display Project.
=======================================================================================================================
*/


/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "led_matrix_display.h"
#include "../OTHERS/common_macros.h"
#include "../MCAL/external_interrupt.h"
#include "../MCAL/uart.h"
#include "../HAL/led.h"
#include "display.h"
#include <avr/io.h>

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

static volatile void (*g_ptr2activeModeFunction)(void) = NULL_PTR;

DISPLAY_characterType g_message[MESSAGE_LENGTH_LIMIT] = "Hello, World!";

UART_configurationsType g_UART_configuration = {UART_SINGLE_STOP_BIT,UART_PARITY_DISABLED,9600};

/*=====================================================================================================================
                                      < Private Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : SwitchMode
 * [Description]   : Switch the system mode from Display to Receive for receiving new string.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static volatile void SwitchMode(void);

/*=====================================================================================================================
 * [Function Name] : DisplayData
 * [Description]   : Display the data stored in the system.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static volatile void DisplayData(void);

/*=====================================================================================================================
 * [Function Name] : ReceiveData
 * [Description]   : Receive a new string from Mobile Phone using UART to be displayed.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static volatile void ReceiveData(void);

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : main
 * [Description]   : The main function of the LED Matrix Display project
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
int main(void)
{
	DISPLAY_init();                                             /* Initialize the Display module.           */
	INT0_init(INT0_RISING_EDGE);                                /* Initialize the INT0 External Interrupt.  */
	INT0_setCallBack(SwitchMode);                               /* Set the INT0 call-back function address. */
	UART0_init(&g_UART_configuration);                          /* Initialize the UART0 peripheral.         */
	g_ptr2activeModeFunction = DisplayData;                     /* Set the Display mode as the active mode. */
	LED_init(SWITCH_MODE_LED_PORT,SWITCH_MODE_LED_PIN);         /* Initialize the LED.                      */
	ENABLE_GLOBAL_INT();                                        /* Enable the AVR global interrupt.         */

	while(1)
	{
		/* Guarding from accessing a NULL pointer. */
		if(g_ptr2activeModeFunction != NULL_PTR)
		{
			/* Call the active mode function. */
			(*g_ptr2activeModeFunction)();
		}
	}
}

/*=====================================================================================================================
 * [Function Name] : SwitchMode
 * [Description]   : Switch the system mode from Display to Receive for receiving new string.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static volatile void SwitchMode(void)
{
	g_dispaly_state = DISPLAY_OFF;                              /* Turn OFF the display.         */
	g_ptr2activeModeFunction = ReceiveData;                     /* Switch to the Receive mode.   */
}

/*=====================================================================================================================
 * [Function Name] : DisplayData
 * [Description]   : Display the data stored in the system.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static volatile void DisplayData(void)
{
	DISPLAY_sendString(g_message);                              /* Display the message. */
}

/*=====================================================================================================================
 * [Function Name] : ReceiveData
 * [Description]   : Receive a new string from Mobile Phone using UART to be displayed.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static volatile void ReceiveData(void)
{

	LED_on(SWITCH_MODE_LED_PORT,SWITCH_MODE_LED_PIN);           /* Turn ON the receiving LED indicator.   */
	UART0_receiveString(g_message);                             /* Receive the new message through UART.  */
	LED_off(SWITCH_MODE_LED_PORT,SWITCH_MODE_LED_PIN);          /* Turn OFF the receiving LED indicator.  */
	g_ptr2activeModeFunction = DisplayData;                     /* Switch to the Dispaly mode.            */
	g_dispaly_state = DISPLAY_ON;                               /* Turn ON the display.                   */
}
