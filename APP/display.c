/*
====================================================================================================================
Author       : Mamoun
Module       : 
File Name    : display.c
Date Created : Aug 11, 2023
Description  : 
====================================================================================================================
*/


/*==================================================================================================================
                                               < Includes >
==================================================================================================================*/

#include "display.h"
#include "../HAL/shift_register.h"
#include <util/delay.h>

/*==================================================================================================================
                                           < Global Variables >
==================================================================================================================*/

/* PROTOTYPE */
static uint8 g_character_M_map[8] = {0b00111111,0b01111110,0b01100000,0b00110000,0b01100001,0b01111111,0b00111110,0b11111111};

static HC595_registerPinsType g_rowsRegisterPins = {PORTA_ID,PIN0_ID,PORTA_ID,PIN1_ID,PORTA_ID,PIN2_ID};
static HC595_registerPinsType g_colsRegisterPins = {PORTA_ID,PIN3_ID,PORTA_ID,PIN4_ID,PORTA_ID,PIN5_ID};

DISPLAY_characterMapType g_display_buffer[DISPLAY_BUFFER_SIZE] = {0};

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
static void DISPLAY_buffer(void);

/*==================================================================================================================
                                          < Functions Definitions >
==================================================================================================================*/

/*==================================================================================================================
 * [Function Name] : 
 * [Description]   : 
 * [Arguments]     : <>      -> 
 *                   <>      -> 
 * [return]        : The function returns void.
 =================================================================================================================*/
void DISPLAY_init(void)
{
	HC595_init(&g_rowsRegisterPins);                            /* Initialize rows shift register.     */
	HC595_init(&g_colsRegisterPins);                            /* Initialize columnss shift register. */
}

void DISPLAY_string(DISPLAY_characterType* a_ptr2message)
{
	for(uint8 character_counter = 0; *(a_ptr2message + character_counter) != MESSAGE_TERMINATOR; character_counter++)
	{
		/* equation to calculate the address of the character in the EEPROM */
		// uint16* character_map_address = FIRST_CHARACTER_ADDRESS + *(a_ptr2message + character_counter);
		for(uint8 character_map_index = 0; *(g_character_M_map + character_map_index) != 0XFF; character_map_index++)
		{
			DISPLAY_shiftBuffer();
			g_display_buffer[0] = *(g_character_M_map + character_map_index);
			// EEPROM_readByte((g_character_M_map + character_map_index),g_display_buffer);

			DISPLAY_buffer();
		}
		DISPLAY_shiftBuffer();
		g_display_buffer[0] = 0b00000000;
		DISPLAY_shiftBuffer();
		g_display_buffer[0] = 0b00000000;
		DISPLAY_buffer();
	}
	/* display ~2 spaces before display it again. */
}

/*==================================================================================================================
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : <>      ->
 *                   <>      ->
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_shiftBuffer(void)
{
	for(sint8 counter = (DISPLAY_BUFFER_SIZE - 2); counter >= 0; counter--)
	{
		g_display_buffer[counter + 1] = g_display_buffer[counter];
	}
}

static void DISPLAY_buffer(void)
{
	for(uint8 iteration_counter = 0; iteration_counter < 5; iteration_counter++)
	{
		/* Activate the first column. */
		HC595_updatedShiftRegister(&g_colsRegisterPins,1,1);
		for(uint8 counter = 0; counter < NUMBER_OF_COLS; counter++)
		{
			/* fill each column with delay */
			HC595_updatedShiftRegister(&g_rowsRegisterPins,NUMBER_OF_ROWS,*(g_display_buffer + counter));
			_delay_us(500);
			HC595_updatedShiftRegister(&g_colsRegisterPins,1,0);
		}
	}
}
