/*
 * HomeSensors.c
 *
 * Created: 5/13/2022 4:50:46 PM
 * Author : Denis
 */ 

#include "main.h"

int main(void)
{
	uart_init(MYUBRR);
    while (1) 
    {
		_delay_ms(1000);
		uart_transmit_line("test");
    }
}