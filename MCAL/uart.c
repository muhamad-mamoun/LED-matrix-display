/*
=============================================================================================================
Author       : Mamoun
Module       : UART
File Name    : uart.c
Date Created : Aug 30, 2023
Description  : Source file for the ATmega1284P UART driver.
=============================================================================================================
*/


/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "uart.h"
#include "../OTHERS/common_macros.h"
#include <avr/io.h>

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_init
 * [Description]   : Initialize the UART0 peripheral with specific configurations.
 * [Arguments]     : <a_ptr2configuration>      -> Pointer to structure.
 *                                                 This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART0_init(const UART_configurationsType* a_ptr2configuration)
{
	uint16 UBRR0_value;
	SET_BIT(UCSR0A,U2X0);                                            /* Enable the double speed mode.        */
	SET_BIT(UCSR0B,RXEN0);                                           /* Enable the UART0 receiver.           */
	UCSR0C = (UCSR0C&0XCF)|(a_ptr2configuration->parityMode<<4);     /* Set the parity mode.                 */
	WRITE_BIT(UCSR0C,USBS0,a_ptr2configuration->stopBitSize);        /* Choose the number of stop bit.       */
	UCSR0C = (UCSR0C&0XF9)|(0X06);                                   /* Select the size of the data (8-bit). */

	/* Calculate the UBRR0 value corresponding to the required baudrate. */
	UBRR0_value = (uint16)((F_CPU/(8U * a_ptr2configuration->baudrateValue))-1);
	UBRR0H = (UBRR0_value>>8);                                       /* Assign the last 4-bit in the UBRR0H. */
	UBRR0L = UBRR0_value;                                            /* Assign the first 8-bit in the UBRR0L.*/
}
#endif

#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_init
 * [Description]   : Initialize the UART1 peripheral with specific configurations.
 * [Arguments]     : <a_ptr2configuration>      -> Pointer to structure.
 *                                                 This structure have the required configurations.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART1_init(const UART_configurationsType* a_ptr2configuration)
{
	uint16 UBRR1_value;
	SET_BIT(UCSR1A,U2X1);                                            /* Enable the double speed mode.        */
	SET_BIT(UCSR1B,RXEN1);                                           /* Enable the UART1 receiver.           */
	UCSR1C = (UCSR1C&0XCF)|(a_ptr2configuration->parityMode<<4);     /* Set the parity mode.                 */
	WRITE_BIT(UCSR1C,USBS1,a_ptr2configuration->stopBitSize);        /* Choose the number of stop bit.       */
	UCSR1C = (UCSR1C&0XF9)|(0X06);                                   /* Select the size of the data (8-bit). */

	/* Calculate the UBRR1 value corresponding to the required baudrate. */
	UBRR1_value = (uint16)((F_CPU/(8U * a_ptr2configuration->baudrateValue))-1);
	UBRR0H = (UBRR1_value>>8);                                       /* Assign the last 4-bit in the UBRR1H. */
	UBRR0L = UBRR1_value;                                            /* Assign the first 8-bit in the UBRR1L.*/
}
#endif

#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_sendByte
 * [Description]   : Transmit a specific byte to another device using UART0.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART0_sendByte(const uint8 a_data)
{
	/* Wait until the Data Register Empty flag is set to one. */
	/* The flag is set when the Tx buffer is empty and ready for transmitting a new byte. */
	while(BIT_IS_CLEAR(UCSR0A,UDRE0));

	/* Write the required data in the UDR register to be transmitted. */
	/* This step also clears the UDRE flag. */
	UDR0 = a_data;
}
#endif

#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_sendByte
 * [Description]   : Transmit a specific byte to another device using UART1.
 * [Arguments]     : <a_data>      -> Indicates to the required byte.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART1_sendByte(const uint8 a_data)
{
	/* Wait until the Data Register Empty flag is set to one. */
	/* The flag is set when the Tx buffer is empty and ready for transmitting a new byte. */
	while(BIT_IS_CLEAR(UCSR1A,UDRE1));

	/* Write the required data in the UDR register to be transmitted. */
	/* This step also clears the UDRE flag. */
	UDR1 = a_data;
}
#endif

#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_sendString
 * [Description]   : Transmit a specific string to another device using UART0.
 * [Arguments]     : <a_ptr2data>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART0_sendString(const uint8* a_ptr2data)
{
	/* Loop on the string characters until the NULL character. */
	for(uint8 counter=0; *(a_ptr2data + counter) != '\0'; counter++)
	{
		/* Send every character to the UART_sendByte to be transmitted. */
		UART0_sendByte(*(a_ptr2data + counter));
	}
}
#endif

#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_sendString
 * [Description]   : Transmit a specific string to another device using UART1.
 * [Arguments]     : <a_ptr2data>      -> Pointer points to the required string.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART1_sendString(const uint8* a_ptr2data)
{
	/* Loop on the string characters until the NULL character. */
	for(uint8 counter=0; *(a_ptr2data + counter) != '\0'; counter++)
	{
		/* Send every character to the UART_sendByte to be transmitted. */
		UART1_sendByte(*(a_ptr2data + counter));
	}
}
#endif

#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_receiveByte
 * [Description]   : Receive a byte from another device using UART0.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 UART0_receiveByte(void)
{
	/* Wait until the Receive Complete flag is set to one. */
	/* The flag is set to one when there are unread data in the receive buffer. */
	while(BIT_IS_CLEAR(UCSR0A,RXC0));

	/* Read the received byte and return it. */
	/* This step also clears the RXC0 flag. */
	return UDR0;
}
#endif

#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_receiveByte
 * [Description]   : Receive a byte from another device using UART1.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the received byte.
 ==========================================================================================================*/
uint8 UART1_receiveByte(void)
{
	/* Wait until the Receive Complete flag is set to one. */
	/* The flag is set to one when there are unread data in the receive buffer. */
	while(BIT_IS_CLEAR(UCSR1A,RXC1));

	/* Read the received byte and return it. */
	/* This step also clears the RXC1 flag. */
	return UDR1;
}
#endif

#if (UART0 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART0_receiveString
 * [Description]   : Receive a string from another device using UART0.
 * [Arguments]     : <a_ptr2string>      -> Pointer points to an array to write the string in it.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART0_receiveString(uint8* const a_ptr2string)
{
	uint8 counter = 0;

	/* Read the received character and store it in the array. */
	*(a_ptr2string + counter) = UART0_receiveByte();

	/* Check if the received character is the pre-agreed terminator character. */
	while(*(a_ptr2string + counter) != UART_MESSAGE_TERMINATOR)
	{
		counter++;
		/* Read the next character and store it in the array. */
		*(a_ptr2string + counter) = UART0_receiveByte();
	}

	/* Replace the pre-agreed terminator character with a NULL character. */
	*(a_ptr2string + counter) = '\0';
}
#endif

#if (UART1 == ENABLE)
/*===========================================================================================================
 * [Function Name] : UART1_receiveString
 * [Description]   : Receive a string from another device using UART1.
 * [Arguments]     : <a_ptr2string>      -> Pointer points to an array to write the string in it.
 * [return]        : The function returns void.
 ==========================================================================================================*/
void UART1_receiveString(uint8* const a_ptr2string)
{
	uint8 counter = 0;

	/* Read the received character and store it in the array. */
	*(a_ptr2string + counter) = UART1_receiveByte();

	/* Check if the received character is the pre-agreed terminator character. */
	while(*(a_ptr2string + counter) != UART_MESSAGE_TERMINATOR)
	{
		counter++;
		/* Read the next character and store it in the array. */
		*(a_ptr2string + counter) = UART1_receiveByte();
	}

	/* Replace the pre-agreed terminator character with a NULL character. */
	*(a_ptr2string + counter) = '\0';
}
#endif
