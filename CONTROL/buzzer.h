 /******************************************************************************
 *
 * Module: Buzzer Motor
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Mohamed Hesham
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_
#include "gpio.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 *  Function to initialize buzzer
 */
void BUZZER_init();
/*
 *  Function to trigger buzzer
 */
void BUZZER_start();
/*
 *  Function to stop buzzer
 */
void BUZZER_stop();

#endif /* BUZZER_H_ */
