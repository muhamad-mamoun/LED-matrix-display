/*
=============================================================================================================
Author       : Mamoun
Module       : UART
File Name    : uart.h
Date Created : Aug 30, 2023
Description  : Header file for the UART driver.
=============================================================================================================
*/


#ifndef MCAL_UART_H_
#define MCAL_UART_H_

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../OTHERS/std_types.h"

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define DISABLE                   (0U)
#define ENABLE                    (1U)

#define UART0                     (ENABLE)
#define UART1                     (DISABLE)

#define UART_MESSAGE_TERMINATOR     ';'     /* Pre-agreed string terminator character between Tx and Rx */

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef enum
{
	UART_SINGLE_STOP_BIT,UART_DOUBLE_STOP_BIT
}UART_stopBitSizeType;

typedef enum
{
	UART_PARITY_DISABLED,UART_EVEN_PARITY=2,UART_ODD_PARITY=3
}UART_parityModeType;

typedef struct
{
	UART_stopBitSizeType stopBitSize;
	UART_parityModeType parityMode;
	uint32 baudrateValue;
}UART_configurationsType;

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/


#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_init
 * [Description]   : Initialize the UART0 peripheral with specific configurations.
 * [Arguments]     : <a_ptr2configuration>      -> Pointer to structure.
 *                                                 This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART0_init(const UART_configurationsType* a_ptr2configuration);
#endif


#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_init
 * [Description]   : Initialize the UART1 peripheral with specific configurations.
 * [Arguments]     : <a_ptr2configuration>      -> Pointer to structure.
 *                                                 This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART1_init(const UART_configurationsType* a_ptr2configuration);
#endif


#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_sendByte
 * [Description]   : Transmit a specific byte to another device using UART0.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART0_sendByte(const uint8 a_data);
#endif


#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_sendByte
 * [Description]   : Transmit a specific byte to another device using UART1.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART1_sendByte(const uint8 a_data);
#endif


#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_sendString
 * [Description]   : Transmit a specific string to another device using UART0.
 * [Arguments]     : <a_ptr2data>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART0_sendString(const uint8* a_ptr2data);
#endif


#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_sendString
 * [Description]   : Transmit a specific string to another device using UART1.
 * [Arguments]     : <a_ptr2data>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART1_sendString(const uint8* a_ptr2data);
#endif


#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_receiveByte
 * [Description]   : Receive a byte from another device using UART0.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 UART0_receiveByte(void);
#endif


#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_receiveByte
 * [Description]   : Receive a byte from another device using UART1.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 UART1_receiveByte(void);
#endif


#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_receiveString
 * [Description]   : Receive a string from another device using UART0.
 * [Arguments]     : <a_ptr2string>      -> Pointer points to an array to write the string in it.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART0_receiveString(uint8* const a_ptr2string);
#endif


#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_receiveString
 * [Description]   : Receive a string from another device using UART1.
 * [Arguments]     : <a_ptr2string>      -> Pointer points to an array to write the string in it.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART1_receiveString(uint8* const a_ptr2string);
#endif

#endif /* MCAL_UART_H_ */
