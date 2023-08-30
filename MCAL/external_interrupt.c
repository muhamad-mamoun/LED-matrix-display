/*
=============================================================================================================
Author       : Mamoun
Module       : External Interrupt
File Name    : external_interrupt.c
Date Created : Aug 30, 2023
Description  : Source File for all AVR external interrupts driver.
=============================================================================================================
*/


/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "external_interrupt.h"
#include "../OTHERS/common_macros.h"
#include <avr/interrupt.h>
#include <avr/io.h>

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

#if (EXTERNAL_INTERRUPT_0 == ENABLE)
static volatile void (*g_INT0_ptr2callBackFunction)(void) = NULL_PTR;
#endif

#if (EXTERNAL_INTERRUPT_1 == ENABLE)
static volatile void (*g_INT1_ptr2callBackFunction)(void) = NULL_PTR;
#endif

#if (EXTERNAL_INTERRUPT_2 == ENABLE)
static volatile void (*g_INT2_ptr2callBackFunction)(void) = NULL_PTR;
#endif

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

#if (EXTERNAL_INTERRUPT_0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : INT0_init
 * [Description]   : Initialize external interrupt 0 with specific configurations.
 * [Arguments]     : <a_edgeType>      -> Indicates to the required edge type to be detected.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT0_init(INT0_senseControlType a_edgeType)
{
	EICRA = (EICRA & 0XFC)|(a_edgeType);         /* Set INT0 To Trigger Interrupt With Falling Edge. */
	SET_BIT(EIMSK,INT0);                         /* Enable External Interrupt 0. */
}

/*===========================================================================================================
 * [Function Name] : INT0_disable
 * [Description]   : Disable the external interrupt 0.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT0_disable(void)
{
	CLEAR_BIT(EIMSK,INT0);                       /* Disable External Interrupt 0. */
}

/*===========================================================================================================
 * [Function Name] : INT0_setCallBack
 * [Description]   : Save the address of the Call back function in a global variable.
 * [Arguments]     : <a_ptr2func>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT0_setCallBack(void(*a_ptr2func)(void))
{
	/* Save the address of the Call back function in a global variable. */
	g_INT0_ptr2callBackFunction = a_ptr2func;
}
#endif

#if (EXTERNAL_INTERRUPT_1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : INT1_init
 * [Description]   : Initialize external interrupt 1 with specific configurations.
 * [Arguments]     : <a_edgeType>      -> Indicates to the required edge type to be detected.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT1_init(INT1_senseControlType a_edgeType)
{
	EICRA = (EICRA & 0XF3)|(a_edgeType<<2);      /* Set INT1 To Trigger Interrupt With Falling Edge. */
	SET_BIT(EIMSK,INT1);                         /* Enable External Interrupt 1. */
}

/*===========================================================================================================
 * [Function Name] : INT1_disable
 * [Description]   : Disable the external interrupt 1.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT1_disable(void)
{
	CLEAR_BIT(EIMSK,INT1);                       /* Disable External Interrupt 1. */
}

/*===========================================================================================================
 * [Function Name] : INT1_setCallBack
 * [Description]   : Save the address of the Call back function in a global variable.
 * [Arguments]     : <a_ptr2func>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT1_setCallBack(void(*a_ptr2func)(void))
{
	/* Save the address of the Call back function in a global variable. */
	g_INT1_ptr2callBackFunction = a_ptr2func;
}
#endif

#if (EXTERNAL_INTERRUPT_2 == ENABLE)
/*===========================================================================================================
 * [Function Name] : INT2_init
 * [Description]   : Initialize external interrupt 2 with specific configurations.
 * [Arguments]     : <a_edgeType>      -> Indicates to the required edge type to be detected.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT2_init(INT2_senseControlType a_edgeType)
{
	EICRA = (EICRA & 0XCF)|(a_edgeType<<4);      /* Set INT0 To Trigger Interrupt With Falling Edge. */
	SET_BIT(EIMSK,INT2);                         /* Enable External Interrupt 2. */
}

/*===========================================================================================================
 * [Function Name] : INT2_disable
 * [Description]   : Disable the external interrupt 2.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT2_disable(void)
{
	CLEAR_BIT(EIMSK,INT2);                       /* Disable External Interrupt 2. */
}

/*===========================================================================================================
 * [Function Name] : INT2_setCallBack
 * [Description]   : Save the address of the Call back function in a global variable.
 * [Arguments]     : <a_ptr2func>      -> Pointer points to the call-back function.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void INT2_setCallBack(void(*a_ptr2func)(void))
{
	/* Save the address of the Call back function in a global variable. */
	g_INT2_ptr2callBackFunction = a_ptr2func;
}
#endif

/*=====================================================================================================================
                                          < Interrupt Service Routine >
=====================================================================================================================*/

#if (EXTERNAL_INTERRUPT_0 == ENABLE)
ISR(INT0_vect)
{
	if(g_INT0_ptr2callBackFunction != NULL_PTR)
	{
		(*g_INT0_ptr2callBackFunction)();
	}
}
#endif

#if (EXTERNAL_INTERRUPT_1 == ENABLE)
ISR(INT1_vect)
{
	if(g_INT1_ptr2callBackFunction != NULL_PTR)
	{
		(*g_INT1_ptr2callBackFunction)();
	}
}
#endif

#if (EXTERNAL_INTERRUPT_2 == ENABLE)
ISR(INT2_vect)
{
	if(g_INT2_ptr2callBackFunction != NULL_PTR)
	{
		(*g_INT2_ptr2callBackFunction)();
	}
}
#endif
