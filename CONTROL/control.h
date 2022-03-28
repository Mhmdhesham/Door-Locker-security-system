 /******************************************************************************
 *
 * Module: system control
 *
 * File Name: control.h
 *
 * Description: Header file for the system control
 *
 * Author: Mohamed Hesham
 *
 *******************************************************************************/
/*******************************************************************************
 *                                included libraries                                  *
 *******************************************************************************/
#ifndef CONTROL_H_
#define CONTROL_H_
#include "uart.h"
#include "timer0.h"
#include "dc_motor.h"
#include "external_eeprom.h"
#include "twi.h"
#include "gpio.h"
#include "buzzer.h"
#include <util/delay.h>
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUMBER_CHAR 5
#define TIMER_TICKS_15SEC 454
#define TIMER_TICKS_3SEC 87
#define TIMER_TICKS_1MINUTE  1828
#define START 'S'
#define storepassword 's'
#define openmotor '+'
#define errormessage 'e'
#define checkpassword 'c'
#define trialpassword 't'
#define EEPROM_ADDRESS 0x0311
/*******************************************************************************
 *                                global variables and configurations                                  *
 *******************************************************************************/

uint8 savedpassword[NUMBER_CHAR]; // global array to store saved password
uint8 ccheckpassword[NUMBER_CHAR];// global array to store password to be checked
uint8 triallpassword[NUMBER_CHAR];// global array to store password to be tried
uint8 eepromreadarr[NUMBER_CHAR];// global array to store password read from eeprom
uint16 g_tick1=0,g_tick2CW=0,g_tick2ACW=0,g_tick3=0; // global variable to count ticks

uint8 recievedoperation=0; // global variable for wanted state
UART_ConfigType uartConfig = {9600,UART_8BIT,OFF,OFF_STOPBIT};
TIMER_ConfigType TIMERconfig={NORMAL0,0,0,F0_CPU_1024};
TWI_ConfigType TWIINIT={400000,0x01,pre_1};

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Function to receive password through UART driver from micro1
 * takes one argument
 * return void
 */
void recievepassword(uint8 arr[]);
/*
 * Function to store password in eeprom
 * takes no argument
 * return void
 */
void storeepassword();
/*
 * Function to compare password recieved from micro1 and password stored in eeprom
 * takes two argument
 * return result of comparison
 */
uint8 Matchingornot(uint8 a_arr1[]);
/*
 * Function to count number of ticks need for motor
 *  * takes no argument
 * returns void
 */
void tickCountermotorCW();
/*
 * Function to count number of ticks need for motor
 *  * takes no argument
 * returns void
 */
void tickCountermotorACW();

/*
 * Function to count 3 seconds
 *  * takes no argument
 * returns void
 */
void counter3sec();
/*
 * Function to count number of ticks need for buzzer
 *  * takes no argument
 * returns void
 */
void tickCounterbuzzer();

#endif /* CONTROL_H_ */
