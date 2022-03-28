 /******************************************************************************
 *
 * Module: system control
 *
 * File Name: control.c
 *
 * Description: source file for the system control
 *
 * Author: Mohamed Hesham
 *
 *******************************************************************************/
#include "control.h"
/*
 * Function used to recieve entered password in micro1
 * arguments: array to store recieved password
 * we use UART driver to recieve password byte by byte
 * returns : void
 */
void recievepassword(uint8 arr[])
{

	for(int i=0 ; i<NUMBER_CHAR ; i++){
		arr[i]=UART_recieveByte();
	}

}
/*
 * Function used to store entered password in micro1
 * arguments:none
 * we use EEPROM driver to store password byte by byte
 * returns : void
 */
void storeepassword()
{
	for(uint8 i=0;i<NUMBER_CHAR;i++)
	{
		EEPROM_writeByte(EEPROM_ADDRESS+i,savedpassword[i]);
_delay_ms(10);
	}

}
/*
 * Function of comparison
 * argument: password to be compared with original password
 * take original password from EEPROM
 * then compare it with received password
 * retun: result of comparison
 */
uint8 Matchingornot(uint8 aarr1[])
{
	uint8 aarr2[NUMBER_CHAR];
	uint8 i,j;
	for(j=0;j<NUMBER_CHAR;j++)
	{
		EEPROM_readByte((EEPROM_ADDRESS+j),(aarr2+j));
		_delay_ms(10);
	}
	for( i=0 ; i<NUMBER_CHAR ; i++)
	{
		if(aarr1[i]!= aarr2[i])
			{
			return FALSE;
			}
	}
		return TRUE;
}
/*
 * callback function for timer driver to open door
 * arguments: none
 * variables: tick2CW to count for timer
 * return : void
 */
void tickCountermotorCW()
{
	g_tick2CW++;
	if(g_tick2CW==TIMER_TICKS_15SEC+3)
	{
		TIMER0_deInit();
		g_tick2CW=0;
	}
}
/*
 * callback function for timer driver to close door
 * arguments: none
 * variables: tick2ACW to count for timer
 * return : void
 */
void tickCountermotorACW()
{
	g_tick2ACW++;
	if(g_tick2ACW==TIMER_TICKS_15SEC+3)
	{
		TIMER0_deInit();
		g_tick2ACW=0;
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
 * callback function for timer driver for thief warning
 * arguments: none
 * variables: tick1 to count for timer
 * return : void
 */
void tickCounterbuzzer()
{
	g_tick1++;
	if(g_tick1==TIMER_TICKS_1MINUTE+3)
	{
		TIMER0_deInit();
		g_tick1=0;

	}
}

int main()
{
	UART_init(&uartConfig); // Initialization of UART
		SREG|=(1<<7); //Enabling global interrupt
	TWI_init(&TWIINIT); // Initialization of I2C
	BUZZER_init();// Initialization of BUZZER
	DcMotor_Init();// Initialization of MOTOR(our door)
	while(1)
	{ /*
	 *   Using UART driver we check availability of first micro
 * then receive  operation and
	*/
		while(UART_recieveByte()!=START){};
		UART_sendByte(START);

		recievedoperation=UART_recieveByte();// store received option
	switch(recievedoperation) // we have 5 cases
	{
	case storepassword:// First case store password
	{
		recievepassword(savedpassword); // receive password from micro1
		storeepassword(savedpassword);// store password in EEPROM
		break;
	}
	case checkpassword:// second case check received password
	{
		recievepassword(ccheckpassword);// receive password from micro1
		// return result of comparison between received pass and pass in eeprom
		UART_sendByte(Matchingornot(ccheckpassword));
		break;
	}
	case trialpassword:// third case check received password
	{
		recievepassword(triallpassword);// receive password from micro1
		// return result of comparison between received pass and pass in eeprom
		UART_sendByte(Matchingornot(triallpassword));
		break;
	}
	case errormessage:// fourth case error message
			{
				g_tick1=0; // clear ticks of timer
				/*
				 * Initialize timer
				 * set callback function for timer
				 */
				TIMER0_setCallBack(tickCounterbuzzer);
				TIMER0_init(&TIMERconfig);
				BUZZER_start();// start the alarm
			while(g_tick1 <= TIMER_TICKS_1MINUTE){};// wait for one minute
			BUZZER_stop();// stop the alarm
		        break;
			}
			case openmotor:// fifth and last case openning door and closing it
			{
				g_tick2CW=0,g_tick2ACW=0,g_tick3=0; // clear ticks of timer
				/*
				 * Initialize timer
					* set callback function for timer
			 */
				TIMER0_setCallBack(tickCountermotorCW);
								TIMER0_init(&TIMERconfig);
								DcMotor_Rotate(DC_MOTOR_CW); // start motor to rotate clockwise
				while(g_tick2CW <= TIMER_TICKS_15SEC){}; // wait for 15 seconds
				/*
				 * Initialize timer
				 * set callback function for timer
					 */
					TIMER0_setCallBack(counter3sec);
							TIMER0_init(&TIMERconfig);
							DcMotor_Rotate(DC_MOTOR_STOP);// stop motor
					while(g_tick3 <= TIMER_TICKS_3SEC){};// wait for 3 seconds
					/*
				 * Initialize timer
					* set callback function for timer
					 */
					TIMER0_setCallBack(tickCountermotorACW);
								TIMER0_init(&TIMERconfig);
								DcMotor_Rotate(DC_MOTOR_ACW);// start motor to rotate anticlockwise
			while(g_tick2ACW <= TIMER_TICKS_15SEC){};// wait for 15 second
				DcMotor_Rotate(DC_MOTOR_STOP);// stop motor
			break;
			}
	}


	}
}



