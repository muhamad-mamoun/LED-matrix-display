/*
=====================================================================================================================
Author       : Mamoun
Module       : Display
File Name    : display.h
Date Created : Aug 11, 2023
Description  : Header file for the Display driver [Used to display on the LED Matrix].
=====================================================================================================================
*/


#ifndef APP_DISPLAY_H_
#define APP_DISPLAY_H_

/*===================================================================================================================
                                               < Includes >
===================================================================================================================*/

#include "../OTHERS/std_types.h"

/*===================================================================================================================
                                < Definitions and Static Configurations >
===================================================================================================================*/

#define SCREEN_NUMBER_OF_ROWS                     (8U)
#define SCREEN_NUMBER_OF_COLS                     (32U)
#define DISPLAY_BUFFER_SIZE                       (100U)
#define MESSAGE_TERMINATOR                        ('\0')
#define ITERATION_SPEED                           (500)
#define DISPLAY_SPEED                             (2U)    /* The lower the value, the faster the display.  */

#if (DISPLAY_BUFFER_SIZE > 127)
#error "Display buffer size limit is 127." /* To increase it, you need to change some variables datatypes. */
#endif

#if (DISPLAY_SPEED <= 0)
#error "Invalid display speed."
#endif

#if (DISPLAY_SPEED > 20)
#warning "The display speed is too slow."
#endif

/*===================================================================================================================
                                       < User-defined Data Types >
===================================================================================================================*/

typedef unsigned char DISPLAY_characterType;
typedef unsigned char DISPLAY_characterMapIndexType;

/*===================================================================================================================
                                         < Function-like Macros >
===================================================================================================================*/

#define CALCULATE_CHARACTER_MAP_ADDRESS(CHARACTER) ((DISPLAY_characterMapIndexType*)((g_character_map) + (CHARACTER) - (FIRST_CHARACTER_VALUE)))

/*===================================================================================================================
                                         < Functions Prototypes >
===================================================================================================================*/


/*==================================================================================================================
 * [Function Name] : DISPLAY_init
 * [Description]   : Initialize the Display module by setting up the rows and columns shift registers.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 =================================================================================================================*/
void DISPLAY_init(void);


/*==================================================================================================================
 * [Function Name] : DISPLAY_sendString
 * [Description]   : Send a specific string to the buffer to be displayed on the LED Matrix screen.
 * [Arguments]     : <a_ptr2message>      -> Pointer points to the required string to be displayed.
 * [return]        : The function returns void.
 =================================================================================================================*/
void DISPLAY_sendString(DISPLAY_characterType* a_ptr2message);


/*==================================================================================================================
 * [Function Name] : DISPLAY_sendCharacter
 * [Description]   : Send a specific character to the buffer to be displayed on the LED Matrix screen.
 * [Arguments]     : <a_character>      -> The required character to be displayed.
 * [return]        : The function returns void.
 =================================================================================================================*/
void DISPLAY_sendCharacter(DISPLAY_characterType a_character);

#endif /* APP_DISPLAY_H_ */
