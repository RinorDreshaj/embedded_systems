#include <avr/io.h>
#include "Luminescence.h"

#define LUM_SENSOR_CHANNEL		2

void LUM_Init()
{
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned int LUM_Read()
{
	ADMUX = LUM_SENSOR_CHANNEL;
	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1<<ADSC));

	return ADC;
}