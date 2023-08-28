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
#include "characters_map.h"
#include "../HAL/shift_register.h"
#include <util/delay.h>

/*==================================================================================================================
                                           < Global Variables >
==================================================================================================================*/

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
 * [Function Name] :
 * [Description]   :
 * [Arguments]     : <>      ->
 *                   <>      ->
 * [return]        : The function returns void.
 =================================================================================================================*/
static void DISPLAY_spaceBetweenCharacters(void);

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
		DISPLAY_characterMapType* character_map_address = (DISPLAY_characterMapType*)(g_character_map + *(a_ptr2message + character_counter) - 32);
		for(uint8 character_map_index = 0; *(character_map_address + character_map_index) != 0XFF; character_map_index++)
		{
			DISPLAY_shiftBuffer();
			g_display_buffer[0] = *(character_map_address + character_map_index);
			DISPLAY_buffer();
		}
		DISPLAY_spaceBetweenCharacters();
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
	for(uint8 iteration_counter = 0; iteration_counter < 2; iteration_counter++)
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

static void DISPLAY_spaceBetweenCharacters(void)
{
	for(uint8 space_counter = 0; space_counter < 2; space_counter++)
	{
		DISPLAY_shiftBuffer();
		g_display_buffer[0] = 0X00;
		DISPLAY_buffer();
	}
}
