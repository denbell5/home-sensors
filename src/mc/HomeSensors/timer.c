/*
 * CFile1.c
 *
 * Created: 5/14/2022 4:03:09 PM
 *  Author: Denis
 */ 

#include "timer.h"

void timer_init(void)
{
	TCCR1B |= (1<<WGM12); // set CTC mode
	TIMSK |= (1<<OCIE1A); // enable interrupt
	
	// set compare number
	uint16_t compare_num = (F_CPU / 1024) * 5; // count for 5 seconds
	OCR1AH = compare_num >> 8;
	OCR1AL = (compare_num << 8) >> 8;
	
	TCCR1B |= (1<<CS12) | (1<<CS10);
}