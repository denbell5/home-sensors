/*
 * main.h
 *
 * Created: 5/13/2022 7:26:02 PM
 *  Author: Denis
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 1600000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "avr/interrupt.h"
#include "uart.h"
#include "i2c.h"
#include "tc74.h"
#include "timer.h"

#endif /* MAIN_H_ */