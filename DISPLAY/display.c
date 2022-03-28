 /******************************************************************************
 *
 * Module: system display
 *
 * File Name: display.c
 *
 * Description: Source file for the system display
 *
 * Author: Mohamed Hesham
 *
 *******************************************************************************/

#include "display.h"

/*
 * Function is used to enter password from keypad
 * arguments: array to saved password in
 * local variables: keypressed & counter
 * Move cursor on LCD to second line
 * take input from keypad function and store it in array
 * display a star character every entered key
 * wait for '=' character to terminate function
 * returns:void
 *
 */
void enterpassword(uint8 aarr[])
{  uint8 l_key;
	uint8 l_counter=0;
LCD_moveCursor(1,0);
	for(l_counter=0;l_counter<NUMBER_CHAR;l_counter++)
	{
		l_key=KEYPAD_getPressedKey();
		aarr[l_counter]=l_key;
		LCD_displayCharacter('*');
		_delay_ms(500);
	}

	while(l_key!='=')
	{
		l_key=KEYPAD_getPressedKey();
	}

}
/*
 * Function used when user enters a wrong choice
 * arguments: none
 * returns:void
 *
 */
void wrongscreen()
{
	LCD_clearScreen();
	LCD_displayString("NOT MATCHED!");
	_delay_ms(2000);
}
/*
 * Function used to send entered password to second micro
 * arguments: password to be sent
 * we use UART driver to send password byte by byte
 * returns : void
 */
void sendpassword(uint8 a_arr[])
{
	uint8 i;
	for( i=0;i<NUMBER_CHAR;i++)
	{
		UART_sendByte(a_arr[i]);
	}
}
/*
 * Function called at new passwords with flag to check on it
 * display at first for user to enter new password
 * call enter password function
 * wait for micro to save password
 *   Using Uart driver we check availability of second micro
 * then send them desired operation
 * desired operation here is to store entered password
 *  * display at first for user to enter new password again
 * call enter password function
 * wait for micro to save password
 *   Using Uart driver we check availability of second micro
 * then send them desired operation and password
 * desired operation here is to check  entered password
 *  *   Using Uart driver we check availability of second micro
 * then send them desired operation and password
 * wait for result
 * if result is true
 * make flag of first entry and error equal zero and continue to main option
 * if result is false
 * start again and increment error counter
 * and if error counter is equal to 3 we call alert function
 * returns: void
 */
void firsttimepass(uint8 aarr[])
{
	g_checknew=1;
	LCD_clearScreen();
	LCD_displayString("ENTER NEW PASS:");
enterpassword(newwpassword);
LCD_clearScreen();
		LCD_displayString("LOADING WAIT ");
UART_sendByte(START);
while(UART_recieveByte()!=START){};
UART_sendByte(storepassword);
sendpassword(newwpassword);
LCD_clearScreen();
LCD_displayString("CONFIRM NEW PASS:");
enterpassword(reepassword);
LCD_clearScreen();
		LCD_displayString("LOADING WAIT ");
UART_sendByte(START);
while(UART_recieveByte()!=START){};
UART_sendByte(checkpassword);
sendpassword(reepassword);
g_compareresult1=UART_recieveByte();
if(g_compareresult1==TRUE)
{
	g_checknew=0;
	g_errornew=0;
}
else
{
	wrongscreen();
	g_errornew++;
	if(g_errornew==3)
	{
		alertscreen();
	}
}
}
/*
 *   Function called to change password
 *   display at first to confirm old password
 *   * call enter password function
 * wait for micro to save password
 *   Using Uart driver we check availability of second micro
 * then send them desired operation and password
 * desired operation here is to check  entered password
 *  *   Using Uart driver we check availability of second micro
 * then send them desired operation and password
 * wait for result
 * if result is true continue and call firsttime function to enter new password
 * if result is false increment error counter and continue to main options
 * and if error counter is equal to 3 we call alert function
 * returns: void
 */

void changepassword()
{
	LCD_clearScreen();
	LCD_displayString("OLD PASS IS:");
enterpassword(origgpassword);
LCD_clearScreen();
		LCD_displayString("LOADING WAIT ");
UART_sendByte(START);
while(UART_recieveByte()!=START){};
UART_sendByte(trialpassword);
sendpassword(origgpassword);
g_compareresult2=UART_recieveByte();
if(g_compareresult2==TRUE)
{
	firsttimepass(origgpassword);
}
else
{
	wrongscreen();
	g_errorconfirm++;
	if(g_errorconfirm==3)
	{
		alertscreen();
	}
}
}
/*
 * callback function for timer driver for thief warning
 * arguments: none
 * variables: tick1 to count for timer
 * return : void
 */
void alarmdelay()
{
	g_tick1++;
	if(g_tick1 == TIMER_TICKS_1MINUTE+3)
		{
			TIMER0_deInit();
			g_tick1=0;
		}

}
/*
 * callback function for timer driver to open door
 * arguments: none
 * variables: tick2open to count for timer
 * return : void
 */
void countermotoropen()
{
	g_tick2open++;

	if(g_tick2open==TIMER_TICKS_15SEC+3)
	{

		TIMER0_deInit();
		g_tick2open=0;
	}
}
/*
 * callback function for timer driver to close door
 * arguments: none
 * variables: tick2close to count for timer
 * return : void
 */
void countermotorclose()
{
	g_tick2close++;

	if(g_tick2close==TIMER_TICKS_15SEC+3)
	{

		TIMER0_deInit();
		g_tick2close=0;
	}
}
/*
 * callback function for timer driver to wait 3 seconds
 * arguments: none
 * variables: tick3to count for timer
 * return : void
 */
void counter3sec()
{
	g_tick3++;

	if(g_tick3==TIMER_TICKS_3SEC+3)
	{

		TIMER0_deInit();
		g_tick3=0;
	}
}
/*
 * Function called at thief warning
 * arguments: none
 * Using Uart driver we check availability of second micro
 * then send them desired operation
 * then set timer driver to count 1 minute
 * display warning message for thief on screen
 * after finishing 1 minute clear all error counters
 * returns : void
 */
void alertscreen()
{
	g_tick1=0;
	UART_sendByte(START);
while(UART_recieveByte()!=START){};
	UART_sendByte(errormessage);
	LCD_clearScreen();
	TIMER0_setCallBack(alarmdelay);
	TIMER0_init(&TIMERconfig);
		LCD_moveCursor(0,0);
				LCD_displayString("HELLO THIEF");
	while(g_tick1 <= TIMER_TICKS_1MINUTE){};
	g_errornew=0;
	g_errorconfirm=0;


}
/*
 *   Function called to opendoor
 *   display at first to confirm old password
 *   * call enter password function
 * wait for micro to save password
 *   Using Uart driver we check availability of second micro
 * then send them desired operation and password
 * desired operation here is to check  entered password
 *  *   Using Uart driver we check availability of second micro
 * then send them desired operation and password
 * wait for result
 * if result is true continue
 *  *   Using Uart driver we check availability of second micro
 * then send them desired operation and password
 * desired operation here is to open door
 * using timer we count 15second and display that door is locking
 * then we use timer again to stop door for 3sec and display it
 * using timer we count 15second and display that door is closing
 * if result is false increment error counter and continue to main options
 * and if error counter is equal to 3 we call alert function
 * */
void openndoor()
{
	LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"OLD PASS is");
		enterpassword(origgpassword);
		LCD_clearScreen();
		LCD_displayString("LOADING WAIT ");
		UART_sendByte(START);
		while(UART_recieveByte()!=START){};
		UART_sendByte(checkpassword);
		sendpassword(origgpassword);
		g_compareresult1=UART_recieveByte();

	if(g_compareresult1==TRUE)
	{
		g_tick1=0,g_tick2open=0,g_tick2close=0,g_tick3=0;
		g_errorconfirm=0;
		UART_sendByte(START);
			while(UART_recieveByte()!=START){};
		UART_sendByte(openmotor);
		LCD_clearScreen();
		TIMER0_setCallBack(countermotoropen);
		TIMER0_init(&TIMERconfig);
		LCD_displayStringRowColumn(0,0,"OPENING DOOR");
		while(g_tick2open <= TIMER_TICKS_15SEC){};
		LCD_clearScreen();
				TIMER0_setCallBack(counter3sec);
				TIMER0_init(&TIMERconfig);
	LCD_displayString("Door is open");
	while(g_tick3 <= TIMER_TICKS_3SEC){};
	LCD_clearScreen();
	TIMER0_setCallBack(countermotorclose);
	TIMER0_init(&TIMERconfig);
	LCD_displayStringRowColumn(0,0,"CLOSING DOOR");
	while(g_tick2close <= TIMER_TICKS_15SEC){};
	LCD_clearScreen();
		LCD_displayString("LOADING WAIT ");
	}
	else
	{ g_errorconfirm++;
	wrongscreen();
				if(g_errorconfirm==3)
				{
					alertscreen();
				}

	}
}
/*
 * Main options functions
 * arguments: none
 * display main options on screen
 * receive it through keypad
 * Using Uart driver we check availability of second micro
 * then send them desired option
 * and start here desired option
 * return void
 */
void Mainoption()
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+:Open door");
	LCD_displayStringRowColumn(1,0,"-:Change pass");
	g_pressedkey=KEYPAD_getPressedKey();
	_delay_ms(500);
	switch(g_pressedkey)
	{
	case '+':
	{
		openndoor();
		break;
	}
	case '-':
	{
	changepassword();
	break;
	}
	default:
	{
		wrongscreen();
	}
	}
}


int main()
{
	SREG|=(1<<7);// enabling global interrupt
	LCD_init(); // initializing LCD
	UART_init(&uartConfig);//Initializing UART
TIMER0_setCallBack(counter3sec);  // Set timer for welcome screen to our project
		TIMER0_init(&TIMERconfig);
		LCD_displayString("Door Locker ");
		LCD_displayStringRowColumn(1,0,"Security system");
	while(g_tick3 <= TIMER_TICKS_3SEC){};
	while(1)
	{
		if(g_checknew==1)
		{
			firsttimepass(origgpassword); //happens at new passwords
		}
		else
		{
			Mainoption(); // it is always on our main menu
		}
	}
}
