 /******************************************************************************
 *
 * Module: Buzzer Motor
 *
 * File Name: buzzer.c
 *
 * Description: source file for the Buzzer driver
 *
 * Author: Mohamed Hesham
 *
 *******************************************************************************/

#include "buzzer.h"
/*
 * Function to initialize buzzer
 * arguments: none
 * set direction of pin as output bin
 * turn it off
 * returns void:
 */
void BUZZER_init()
{
	GPIO_setupPinDirection(PORTC_ID,PIN2_ID,PIN_OUTPUT);
	GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
}
/*
 * Function to trigger buzzer
 * arguments: none
 * turn it on
 * returns void:
 */

void BUZZER_start()
{
	GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_HIGH);
}
/*
 * Function to stop buzzer
 * arguments: none
 * turn it off
 * returns void:
 */

void BUZZER_stop()
{
	GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
}
