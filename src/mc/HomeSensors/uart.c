/*
 * uart.c
 *
 * Created: 5/13/2022 5:44:08 PM
 *  Author: Denis
 */ 

#include "uart.h"

void uart_init(unsigned int ubrr)
{
	// Set baud rate
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	
	UCSRB=(1<<RXEN)|( 1<<TXEN); // Enable receive and transmit
	UCSRB |= (1<<RXCIE); // Allow interrupts
	
	// 1<<URSEL to write to register UCSRC
	// 1<<USBS to set 1 stop-bit (?)
	// 1<<UCSZ1, 1<<UCSZ0 to set 8 bit frame size
	UCSRC = (1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
}

void uart_transmit_char(unsigned char data)
{
	while ( !( UCSRA & (1<<UDRE)) ); // Wait for empty transmit buffer
	UDR = data; // Put data into buffer, sends the data
}

void uart_transmit_line(char* str)
{
	for(int i=0; i < strlen(str); i++)
	{
		uart_transmit_char(str[i]);
	}
	uart_transmit_char('\r');
}