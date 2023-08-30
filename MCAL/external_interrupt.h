/*
=============================================================================================================
Author       : Mamoun
Module       : External Interrupt
File Name    : external_interrupt.h
Date Created : Aug 30, 2023
Description  : Header File for all AVR external interrupts driver.
=============================================================================================================
*/


#ifndef MCAL_EXTERNAL_INTERRUPT_H_
#define MCAL_EXTERNAL_INTERRUPT_H_

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../OTHERS/std_types.h"

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define DISABLE                   (0u)
#define ENABLE                    (1u)

#define EXTERNAL_INTERRUPT_0      (ENABLE)
#define EXTERNAL_INTERRUPT_1      (DISABLE)
#define EXTERNAL_INTERRUPT_2      (DISABLE)

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

#if (EXTERNAL_INTERRUPT_0 == ENABLE)
typedef enum
{
	INT0_LOW_LEVEL,INT0_ANY_LOGICAL,INT0_FALLING_EDGE,INT0_RISING_EDGE
}INT0_senseControlType;
#endif

#if (EXTERNAL_INTERRUPT_1 == ENABLE)
typedef enum
{
	INT1_LOW_LEVEL,INT1_ANY_LOGICAL,INT1_FALLING_EDGE,INT1_RISING_EDGE
}INT1_senseControlType;
#endif

#if (EXTERNAL_INTERRUPT_2 == ENABLE)
typedef enum
{
	INT2_FALLING_EDGE,INT2_RISING_EDGE
}INT2_senseControlType;
#endif

/*=====================================================================================================================
                                         < Function-like Macros >
=====================================================================================================================*/



/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/



#endif /* MCAL_EXTERNAL_INTERRUPT_H_ */
