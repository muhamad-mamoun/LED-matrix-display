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

uint8 g_dispaly_state = DISPLAY_ON;

static HC595_registerPinsType g_rowsRegisterPins = {PORTA_ID,PIN0_ID,PORTA_ID,PIN1_ID,PORTA_ID,PIN2_ID};
static HC595_registerPinsType g_colsRegisterPins = {PORTA_ID,PIN3_ID,PORTA_ID,PIN4_ID,PORTA_ID,PIN5_ID};

static DISPLAY_characterMapIndexType g_display_buffer[DISPLAY_BUFFER_SIZE] = {0};

/*==================================================================================================================
                                      < Private Functions Prototypes >
==================================================================================================================*/

/*==================================================================================================================
 * [Function Name] : DISPLAY_sendEmptyColumn
 * [Description]   : Send a specific number of empty columns to the buffer to be displayed on the LED Matrix screen.
 * [Arguments]     : <a_numberOfColumns>      -> The required number of empty columns to be displayed.
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_sendEmptyColumn(uint8 a_numberOfColumns);

/*==================================================================================================================
 * [Function Name] : DISPLAY_shiftBuffer
 * [Description]   : Shift the entire Buffer array by one index.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_shiftBuffer(void);

/*==================================================================================================================
 * [Function Name] : DISPLAY_renderBuffer
 * [Description]   : Display the content of the Buffer on the LED Matrix screen.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_renderBuffer(void);

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
 * [Function Name] : DISPLAY_sendString
 * [Description]   : Send a specific string to the buffer to be displayed on the LED Matrix screen.
 * [Arguments]     : <a_ptr2message>      -> Pointer points to the required string to be displayed.
 * [return]        : The function returns void.
 =================================================================================================================*/
void DISPLAY_sendString(DISPLAY_characterType* a_ptr2message)
{
	/* Iterate through the characters of the string and send them to the buffer to be displayed. */
	for(uint8 character_counter = 0; *(a_ptr2message + character_counter) != MESSAGE_TERMINATOR; character_counter++)
	{
		/* Stop displaying if the display is turned OFF due to switching to receiving mode. */
		if(g_dispaly_state == DISPLAY_OFF) return;

		/* Send the current character to the buffer to be displayed. */
		DISPLAY_sendCharacter(*(a_ptr2message + character_counter));

		/* Send empty columns between every two characters. */
		DISPLAY_sendEmptyColumn(2);
	}

	/* Send empty columns at the end of the string. */
	DISPLAY_sendEmptyColumn(4);
}

/*==================================================================================================================
 * [Function Name] : DISPLAY_sendCharacter
 * [Description]   : Send a specific character to the buffer to be displayed on the LED Matrix screen.
 * [Arguments]     : <a_character>      -> The required character to be displayed.
 * [return]        : The function returns void.
 =================================================================================================================*/
void DISPLAY_sendCharacter(DISPLAY_characterType a_character)
{
	uint8 character_map_index = 0;
	DISPLAY_characterMapIndexType* character_map_address = NULL_PTR;
	character_map_address = CALCULATE_CHARACTER_MAP_ADDRESS(a_character);

	/* Guarding from accessing a NULL pointer. */
	if(character_map_address != NULL_PTR)
	{
		/* Iterate through the indexes of the character and send them to the buffer to be displayed. */
		for(; *(character_map_address + character_map_index) != CHARACTER_MAP_TERMINATOR; character_map_index++)
		{
			/* Stop displaying if the display is turned OFF due to switching to receiving mode. */
			if(g_dispaly_state == DISPLAY_OFF) return;

			DISPLAY_shiftBuffer(); /* Shift the buffer indexes by one and store the next index at buffer[0]. */
			g_display_buffer[0] = *(character_map_address + character_map_index);

			/* Render the content of the buffer to be displayed on the LED Matrix screen. */
			DISPLAY_renderBuffer();
		}
	}
}

/*==================================================================================================================
 * [Function Name] : DISPLAY_sendEmptyColumn
 * [Description]   : Send a specific number of empty columns to the buffer to be displayed on the LED Matrix screen.
 * [Arguments]     : <a_numberOfColumns>      -> The required number of empty columns to be displayed.
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_sendEmptyColumn(uint8 a_numberOfColumns)
{
	for(uint8 space_counter = 0; space_counter < a_numberOfColumns; space_counter++)
	{
		DISPLAY_shiftBuffer(); /* Shift the buffer indexes by one and store the next index at buffer[0]. */
		g_display_buffer[0] = 0X00;

		/* Render the content of the buffer to be displayed on the LED Matrix screen. */
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
