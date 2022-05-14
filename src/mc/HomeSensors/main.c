#include "main.h"

void init_app();
void process_temp();
void process_motion();
void process_motion_timeout();

// Global variables

uint8_t temp = 0;

uint8_t motion_status = 0;
uint8_t motion_timeout_window = 0;
uint8_t motion_timeout_pending = 0;

uint8_t time_window = 0;

// Global variables end

int main(void)
{
	init_app();
    while (1) 
    {
		process_temp();
		process_motion();
		_delay_ms(300);
    }
}

// timer interrupt, every 5 seconds
ISR (TIMER1_COMPA_vect)
{
	process_motion_timeout();
	time_window = !time_window; // switch time window to next (0 or 1)
}

void init_app()
{
	uart_init(MYUBRR);
	i2c_init();
	
	sei(); // enable global interrupts
	timer_init();
	
	DDRC = 0b00000010; // set C1 as output and other C pins as input
	
	tc74_init();
	temp = tc74_read();
}

void process_temp()
{
	uint8_t next_temp = tc74_read();
	if (next_temp != temp)
	{
		temp = next_temp;
		uart_transmit_str("[event] temperature_change ");
		uart_transmit_int(temp);
		uart_transmit_break();
	}
}

void process_motion()
{
	uint8_t next_motion_status = PINC & 0b0000001;
	if (motion_status != next_motion_status)
	{
		motion_status = next_motion_status;
		uint8_t motion_status = PINC & 0b0000001;
		if (motion_status)
		{
			PORTC |= 0b00000010; // enable C1 pin (led)
		}
		if (!motion_status)
		{
			motion_timeout_pending = 1; // schedule motion timeout
			motion_timeout_window = !time_window; // next window
		}
		uart_transmit_str("[event] motion_status_change ");
		uart_transmit_int(motion_status);
		uart_transmit_break();
	}
}

void process_motion_timeout()
{
	if (
		!motion_status &&
		time_window == motion_timeout_window &&
		motion_timeout_pending)
	{
		PORTC &= 0b11111101; // disable C1 pin (led)
		uart_transmit_str("[event] motion_timeout");
		uart_transmit_break();
		motion_timeout_pending = 0;
	}
}