#include <avr/io.h>
#include "Temperature.h"

#define TEMP_SENSOR_CHANNEL		1

void TEMP_Init() 
{
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned int TEMP_Read()
{
	ADMUX = TEMP_SENSOR_CHANNEL;
	ADCSRA |= (1<<ADSC);

	while(ADCSRA & (1<<ADSC));

	return ADC;
}