 /******************************************************************************
 *
 * Module: system display
 *
 * File Name: display.h
 *
 * Description: Header file for the system display
 *
 * Author: Mohamed Hesham
 *
 *******************************************************************************/
#ifndef DISPLAY_H_
#define DISPLAY_H_
/*******************************************************************************
 *                           included libraries                                 *
 *******************************************************************************/
#include "uart.h"
#include"lcd.h"
#include "keypad.h"
#include "timer0.h"
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
/*******************************************************************************
 *                                global variables and configurations                                  *
 *******************************************************************************/
uint8 origgpassword[NUMBER_CHAR];
uint8 newwpassword[NUMBER_CHAR];
uint8 reepassword[NUMBER_CHAR];
uint8 g_errornew=0,g_errorconfirm=0; // global variable to count errors
uint16 g_tick1=0,g_tick2open=0,g_tick2close=0,g_tick3=0; // global variables to count ticks needed
UART_ConfigType uartConfig = {9600,UART_8BIT,OFF,OFF_STOPBIT};
TIMER_ConfigType TIMERconfig={NORMAL0,0,0,F0_CPU_1024};
uint8 g_checknew=1; // global variable to check first time entrance
uint8 g_compareresult1,g_compareresult2; // global variable to recieve result of checked passwords
uint8 g_pressedkey; // global variable to take pressed key from keypad

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Function to take password from user by Keypad
 *  return void
 * takes one array by address to store value in it
 *
 */
void enterpassword(uint8 aarr[]);
/*
 * Function is used to display wrong password matching error
 * takes no argument
 * return void
 */
void wrongscreen();
/*
 * Function to send password to control micro by UART driver
 *  return void
 * takes one array by address to send value in it
 */
void sendpassword(uint8 a_arr[]);
/*
 * Function is  used to enter new password
 * takes one array by address to store in it first password
 * returns void
 */
void firsttime(uint8 aarr[]);
/*
 * Function used to change old password to new one
 * takes no argument
 * returns void
 */
void changepassword();
/*
 * Function to count number of ticks need for alarm
 *  * takes no argument
 * returns void
 */
void alarmdelay();
/*
 * Function to count number of ticks need for motor to open
 *  * takes no argument
 * returns void
 */
void countermotoropen();
/*
 * Function to count number of ticks need for motor to close
 *  * takes no argument
 * returns void
 */
void countermotorclose();

/*
 * Function to count 3 seconds
 *  * takes no argument
 * returns void
 */
void counter3sec();
/*
 * Function called when user exceeded number of entering wrong password
 *  * takes no argument
 * returns void
 *
 */

void alertscreen();
/*
 * Function responsible for openning and closing motor
 *  * takes no argument
 * returns void
 */
void opennmotor();
/*
 * Function responsible for displaying main options
 *  * takes no argument
 * returns void
 */
void Mainoption();
#endif /* DISPLAY_H_ */
