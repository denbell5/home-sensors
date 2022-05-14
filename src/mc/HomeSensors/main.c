/*
 * HomeSensors.c
 *
 * Created: 5/13/2022 4:50:46 PM
 * Author : Denis
 */ 

#include "main.h"

unsigned char i = 0;

ISR (TIMER1_COMPA_vect)
{
	i++;
	uart_transmit_line("timer");
}

int main(void)
{
	uart_init(MYUBRR);
	i2c_init();
	
	sei(); // enable global interrupts
	timer_init();
	
	uint8_t temp = 0;
	uint8_t motion_detected = 0;
	
	PORTC = 0x00;
	
	tc74_init();
	temp = tc74_read();
	
    while (1) 
    {
		uint8_t next_temp = tc74_read();
		
		if (next_temp != temp)
		{
			temp = next_temp;
			char temp_str[5];
			itoa(temp, temp_str, 10);
			uart_transmit_line("temp changed: ");
			uart_transmit_line(temp_str);
		}
		
		uint8_t next_motion_detected = PINC & 0b0000001;
		if (motion_detected != next_motion_detected)
		{
			motion_detected = next_motion_detected;
			uint8_t motion_detected = PINC & 0b0000001;
			char temp_str[5];
			itoa(motion_detected, temp_str, 10);
			uart_transmit_line("motion status changed: ");
			uart_transmit_line(temp_str);
		}
		
		_delay_ms(300);
    }
}