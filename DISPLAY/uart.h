 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Hesham
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	OFF,RESERVED,ON_EVEN,ON_ODD
}UART_ParityMode;
typedef enum
{
	UART_5BIT,UART_6BIT,UART_7BIT,UART_8BIT,UART_RESERVED1,UART_RESERVED2,UART_RESERVED3,UART_9BIT
}UART_Charactersize ;
typedef enum
{
	OFF_STOPBIT,ON_STOPBIT
}UART_StopBit;

typedef struct
{  uint32 baud_rate;
	UART_Charactersize CHARSIZE;
	UART_ParityMode PARITY;
	UART_StopBit stopbit;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
