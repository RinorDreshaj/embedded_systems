#include <avr/io.h>
#include "Fan.h"

void FAN_Init()
{
	DDRB = 0x20;

	TCCR1A = (1<<COM1A1) | (1<<WGM11) | (1<<WGM10);
	TCCR1B = (1<<WGM12) | (1<<CS10);
	
	FAN_SetSpeed(0);
}

void FAN_SetSpeed(unsigned int speed)
{
	OCR1A = speed;
}