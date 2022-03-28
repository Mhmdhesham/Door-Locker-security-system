 /******************************************************************************
 *
 * Module: Timer0 driver
 *
 * File Name: timer0.h
 *
 * Description: Header file for the timer0 driver
 *
 * Author: Mohamed Hesham
 *
 *******************************************************************************/
/*******************************************************************************
 *                                included libraries                                  *
 *******************************************************************************/
#ifndef TIMER0_H_
#define TIMER0_H_
/*******************************************************************************
 *                                included libraries                                  *
 *******************************************************************************/
#include <avr/io.h>
#include "std_types.h"
#include <avr/interrupt.h>
#include "common_macros.h"
/*******************************************************************************
 *                                Definitions                                 *
 *******************************************************************************/
typedef enum
{
	NORMAL0,PWM0,COMPARE0,FAST_PWM0
}TIMER_MODE ;
typedef enum
{
     STOP0,OFF0_PRESCALER,F0_CPU_8,F0_CPU_64,F0_CPU_256,F0_CPU_1024,EXT0_FALLING,EXT0_RISING
}TIMER0_PRESCALER;
typedef struct
{
	TIMER_MODE timermode0;
	uint8 INITVALUE;
	uint8 COMPAREVALUE;
	TIMER0_PRESCALER PRESCALER0;
}TIMER_ConfigType;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void TIMER0_init(const TIMER_ConfigType * Config_Ptr);


void TIMER0_setCallBack(void(*a_ptr)(void));
/*
 * Function to stop timer
 */

void TIMER0_deInit();
#endif /* TIMER0_H_ */
