#ifndef UART_H_
#define UART_H_

#include "main.h"

void uart_init(unsigned int ubrr);
void uart_transmit_char(unsigned char data);
void uart_transmit_str(char* str);
void uart_transmit_int(int val);
void uart_transmit_break();

#endif