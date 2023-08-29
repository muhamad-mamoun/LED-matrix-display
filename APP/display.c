/*
====================================================================================================================
Author       : Mamoun
Module       : Display
File Name    : display.c
Date Created : Aug 11, 2023
Description  : Source file for the Display driver [Used to display on the LED Matrix].
====================================================================================================================
*/


/*==================================================================================================================
                                               < Includes >
==================================================================================================================*/

#include "display.h"
#include "characters_map.h"
#include "../HAL/shift_register.h"
#include "../MCAL/gpio.h"
#include <util/delay.h>

/*==================================================================================================================
                                           < Global Variables >
==================================================================================================================*/

static HC595_registerPinsType g_rowsRegisterPins = {PORTA_ID,PIN0_ID,PORTA_ID,PIN1_ID,PORTA_ID,PIN2_ID};
static HC595_registerPinsType g_colsRegisterPins = {PORTA_ID,PIN3_ID,PORTA_ID,PIN4_ID,PORTA_ID,PIN5_ID};

static DISPLAY_characterMapIndexType g_display_buffer[DISPLAY_BUFFER_SIZE] = {0};

/*==================================================================================================================
                                      < Private Functions Prototypes >
==================================================================================================================*/


/*==================================================================================================================
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : <>      ->
 *                   <>      ->
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_shiftBuffer(void);


/*==================================================================================================================
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : <>      ->
 *                   <>      ->
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_renderBuffer(void);


/*==================================================================================================================
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : <>      ->
 *                   <>      ->
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_emptyColumn(uint8 a_numberOfColumns);

/*==================================================================================================================
                                          < Functions Definitions >
==================================================================================================================*/

/*==================================================================================================================
 * [Function Name] : DISPLAY_init
 * [Description]   : Initialize the Display module by setting up the rows and columns shift registers.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 =================================================================================================================*/
void DISPLAY_init(void)
{
	HC595_init(&g_rowsRegisterPins);                            /* Initialize the rows shift register.     */
	HC595_init(&g_colsRegisterPins);                            /* Initialize the columnss shift register. */
}

/*==================================================================================================================
 * [Function Name] : DISPLAY_string
 * [Description]   : Display a specific string on the LED Matrix screen.
 * [Arguments]     : <a_ptr2message>      -> Pointer points to the required string to be displayed.
 * [return]        : The function returns void.
 =================================================================================================================*/
void DISPLAY_string(DISPLAY_characterType* a_ptr2message)
{
	for(uint8 character_counter = 0; *(a_ptr2message + character_counter) != MESSAGE_TERMINATOR; character_counter++)
	{
		DISPLAY_characterMapIndexType* character_map_address = CALCULATE_CHARACTER_MAP_ADDRESS(*(a_ptr2message + character_counter));
		for(uint8 character_map_index = 0; *(character_map_address + character_map_index) != CHARACTER_MAP_TERMINATOR; character_map_index++)
		{
			DISPLAY_shiftBuffer();
			g_display_buffer[0] = *(character_map_address + character_map_index);
			DISPLAY_renderBuffer();
		}
		DISPLAY_emptyColumn(2);
	}
	/* display ~2 spaces before display it again. */
}

static void DISPLAY_emptyColumn(uint8 a_numberOfColumns)
{
	for(uint8 space_counter = 0; space_counter < a_numberOfColumns; space_counter++)
	{
		DISPLAY_shiftBuffer();
		g_display_buffer[0] = 0X00;
		DISPLAY_renderBuffer();
	}
}

/*==================================================================================================================
 * [Function Name] : DISPLAY_shiftBuffer
 * [Description]   : Shift the entire Buffer array by one index.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_shiftBuffer(void)
{
	for(sint8 counter = (DISPLAY_BUFFER_SIZE - 2); counter >= 0; counter--)
	{
		/* Store each index in the array at the next index of it. */
		g_display_buffer[counter + 1] = g_display_buffer[counter];
	}
}

/*==================================================================================================================
 * [Function Name] : DISPLAY_renderBuffer
 * [Description]   : Display the content of the Buffer on the LED Matrix screen.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_renderBuffer(void)
{
	for(uint8 iteration_counter = 0; iteration_counter < DISPLAY_SPEED; iteration_counter++)
	{
		/* Activate the first column in the matrix. */
		HC595_updatedShiftRegister(&g_colsRegisterPins,1,1);

		/* Round-Robin on the entire columns in the matrix one by one. */
		for(uint8 column_counter = 0; column_counter < SCREEN_NUMBER_OF_COLS; column_counter++)
		{
			/* Fill the current column with its value by shifting the row register. */
			HC595_updatedShiftRegister(&g_rowsRegisterPins,SCREEN_NUMBER_OF_ROWS,*(g_display_buffer + column_counter));

			/* Small delay the eye cannot perceive it, So it appears continuously. */
			_delay_us(ITERATION_SPEED);

			/* Activate the next column in the matrix. */
			HC595_updatedShiftRegister(&g_colsRegisterPins,1,0);
		}
	}
}
