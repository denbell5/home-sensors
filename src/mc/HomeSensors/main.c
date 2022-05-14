/*
 * HomeSensors.c
 *
 * Created: 5/13/2022 4:50:46 PM
 * Author : Denis
 */ 

#include "main.h"

uint8_t motion_status = 0;
uint8_t motion_timeout_window = 0;
uint8_t motion_timeout_pending = 0;

uint8_t time_window = 0;

ISR (TIMER1_COMPA_vect)
{
	if (
		!motion_status &&
		time_window == motion_timeout_window &&
		motion_timeout_pending)
	{
		uart_transmit_line("[event] motion_timeout");
		motion_timeout_pending = 0;
	}
	
	time_window = !time_window; // 0 or 1
}

int main(void)
{
	uart_init(MYUBRR);
	i2c_init();
	
	sei(); // enable global interrupts
	timer_init();
	
	uint8_t temp = 0;
	
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
		
		uint8_t next_motion_status = PINC & 0b0000001;
		if (motion_status != next_motion_status)
		{
			motion_status = next_motion_status;
			uint8_t motion_status = PINC & 0b0000001;
			if (!motion_status)
			{
				motion_timeout_pending = 1;
				motion_timeout_window = !time_window; // next window
			}
			char temp_str[5];
			itoa(motion_status, temp_str, 10);
			uart_transmit_line("motion status changed: ");
			uart_transmit_line(temp_str);
		}
		
		_delay_ms(300);
    }
}