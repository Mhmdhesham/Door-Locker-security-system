 /******************************************************************************
 *
 * Module: Timer0 driver
 *
 * File Name: timer0.c
 *
 * Description: Source file for the timer0 driver
 *
 * Author: Mohamed Hesham
 *
 *******************************************************************************/

#include "timer0.h"
#include "gpio.h"
#include <util/delay.h>
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
ISR(TIMER0_OVF_vect)
{


	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after overflow occures */
		(*g_callBackPtr)();
	}

}
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after compare value reached */
		(*g_callBackPtr)();
	}
}


/*
 * Function to initialize timer:
 * it takes configuration structure
 * if normal mode detected:
 * 1- set FOC0 in register TCCR0 as non pwm
 * 2- clear value of TCNT0 register
 * 3- Set interrupts flag
 * if compare mode detected :
 * 1- set FOC0 in register TCCR0 as non pwm
 * 2- clear value of TCNT0 register
 * 3- Set interrupts flag
 * 4- set WGM01BIT in register TCCR0 to declare compare mode
 * if PWM mode is detected:
 *  * 1- set COM01,WGM01 for pwm mode
 * 2- clear value of TCNT0 register
 * 3- Set interrupts flag
 * 4- set WGM01BIT in register TCCR0 to declare compare mode
 *  * if FAST PWM mode is detected:
 *  * 1- set COM01,WGM01,WGM00 for PWM mode
 * 2- clear value of TCNT0 register
 * 3- Set interrupts flag
 * 4- set WGM01BIT in register TCCR0 to declare compare mode
 */
void TIMER0_init(const TIMER_ConfigType * Config_Ptr)
{

	if(((Config_Ptr->timermode0)!=PWM0)&&((Config_Ptr->timermode0)!=FAST_PWM0))
	{
		TCNT0=Config_Ptr->INITVALUE;
			TCCR0=(TCCR0 & 0XF8)|(0X07 & Config_Ptr->PRESCALER0);
		SET_BIT(TCCR0,FOC0);
		if((Config_Ptr->timermode0)==COMPARE0)
		{
			SET_BIT(TCCR0,WGM01);
			CLEAR_BIT(TCCR0,WGM00);
			OCR0=Config_Ptr->COMPAREVALUE;
			SET_BIT(TIMSK,OCIE0);
		}
		else
		{
			CLEAR_BIT(TCCR0,WGM00);
			CLEAR_BIT(TCCR0,WGM01);
			SET_BIT(TIMSK,TOIE0);
		}

	}
	else
	{
		SET_BIT(TCCR0,COM01);
		CLEAR_BIT(TCCR0,COM00);
		if((Config_Ptr->timermode0)==1)
		{
			SET_BIT(TCCR0,WGM00);
			CLEAR_BIT(TCCR0,WGM01);
		}
		else{

			SET_BIT(TCCR0,WGM01);
			SET_BIT(TCCR0,WGM00);
		}
		}

}
/*
 * Function to store callback function from main system
 */
void TIMER0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
/*
 * Function to deinitialize timer0 and clear its registers
 * and also clear interrupt flag
 */
void TIMER0_deInit()
{
	TCCR0=(TCCR0 & 0XF8);// stop the timer
	TIMSK &= ~(1<<TOIE0); // disable Timer0 Overflow Interrupt
	TIMSK &= ~(1<<OCIE0);// disable Timer0 Compare Interrupt

}
