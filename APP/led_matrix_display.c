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
#include "../MCAL/external_interrupt.h"
#include "../MCAL/uart.h"
#include "display.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

volatile void (*g_ptr2eventHandlingFunction)(void) = NULL_PTR;

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
volatile void SwitchMode(void);

/*=====================================================================================================================
 * [Function Name] : DisplayData
 * [Description]   : Display the data stored in the system.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
volatile void DisplayData(void);

/*=====================================================================================================================
 * [Function Name] : ReceiveData
 * [Description]   : Receive a new string from Mobile Phone using UART to be displayed.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
volatile void ReceiveData(void);

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
	DISPLAY_init();
	INT0_init(INT0_RISING_EDGE);
	INT0_setCallBack(SwitchMode);
	UART0_init(&g_UART_configuration);
	g_ptr2eventHandlingFunction = DisplayData;

	while(1)
	{
		if(g_ptr2eventHandlingFunction != NULL_PTR)
		{
			(*g_ptr2eventHandlingFunction)();
		}
	}
}

/*=====================================================================================================================
 * [Function Name] : SwitchMode
 * [Description]   : Switch the system mode from Display to Receive for receiving new string.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
volatile void SwitchMode(void)
{
	g_ptr2eventHandlingFunction = ReceiveData;
}

/*=====================================================================================================================
 * [Function Name] : DisplayData
 * [Description]   : Display the data stored in the system.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
volatile void DisplayData(void)
{
	DISPLAY_sendString(g_message);
}

/*=====================================================================================================================
 * [Function Name] : ReceiveData
 * [Description]   : Receive a new string from Mobile Phone using UART to be displayed.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
volatile void ReceiveData(void)
{
	UART0_receiveString(g_message);
	g_ptr2eventHandlingFunction = DisplayData;
}
