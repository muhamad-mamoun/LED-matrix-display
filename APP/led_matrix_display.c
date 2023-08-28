/*
=======================================================================================================================
Author       : Mamoun
Module       : 
File Name    : led_matrix_display.c
Date Created : Aug 8, 2023
Description  : 
=======================================================================================================================
*/


/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "display.h"
#include "led_matrix_display.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

DISPLAY_characterType g_message[MESSAGE_LENGTH] = "Hello, World!";

/*=====================================================================================================================
                                      < Private Functions Prototypes >
=====================================================================================================================*/



/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : 
 * [Description]   : 
 * [Arguments]     : <>      -> 
 *                   <>      -> 
 * [return]        : The function returns void.
 ====================================================================================================================*/
int main(void)
{
	DISPLAY_init();
	while(1)
	{
		DISPLAY_string(g_message);
	}
}
