/*
 * uart.h
 *
 * Created: 5/13/2022 7:28:26 PM
 *  Author: Denis
 */ 


#ifndef UART_H_
#define UART_H_

#include "main.h"

void uart_init(unsigned int ubrr);
void uart_transmit_char(unsigned char data);
void uart_transmit_line(char* str);

#endif /* UART_H_ */