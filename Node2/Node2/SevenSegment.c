#define F_CPU   14745600

#include <avr/io.h>
#include <util/delay.h>

#define NUM_SEGMENTS	8

#define SEGMENTS_OFF	0xFF
#define SEGMENTS_DOT	0x7F
#define SEGMENTS_MINUS	0xBF

unsigned char segmentData[] = {	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 
								0x92, 0x82, 0xF8, 0x80, 0x90 };

unsigned char displayBuffer[NUM_SEGMENTS];

unsigned char currentDigit;

void SEGDISP_Clear() {
	
	unsigned char i = 0;
	
	for(i=0; i<NUM_SEGMENTS; i++)
	displayBuffer[i] = SEGMENTS_OFF;
}

void SEGDISP_Init() {
	
	DDRB |= 0x07;
	DDRD = 0xFF;
	
	PORTB = 0;
	PORTD = SEGMENTS_OFF;
	
	currentDigit = 0;
	
	SEGDISP_Clear();
}



void SEGDISP_SetNumber(long int value, int decimalPointPosition) {
	
	SEGDISP_Clear();
	
	unsigned char isNegative = value < 0;
	unsigned char digit = 0;
	
	value = value < 0 ? -value : value;
	decimalPointPosition = decimalPointPosition >= NUM_SEGMENTS ? 0 : decimalPointPosition;
	
	while(value > 0 || digit <= decimalPointPosition) {
		
		displayBuffer[NUM_SEGMENTS - digit - 1] = segmentData[value % 10];
		
		value /= 10;
		digit++;
		
		if(digit - 1 >= NUM_SEGMENTS)
			break;
	}
	
	if(decimalPointPosition)
		displayBuffer[NUM_SEGMENTS - decimalPointPosition - 1] &= SEGMENTS_DOT;
	
	if(isNegative && digit < NUM_SEGMENTS)
		displayBuffer[NUM_SEGMENTS - digit - 1] = SEGMENTS_MINUS;
}

void SEGDISP_SetInteger(int value) {
	
	SEGDISP_SetNumber(value, 0);
}

void SEGDISP_SetFloat(float number, unsigned char decimals) {
		
	unsigned char shifts = 0;
	for(shifts=0; shifts<decimals; shifts++)
		number *= 10;
		
	SEGDISP_SetNumber((long int)number, decimals);
}

void SEGDISP_Refresh() {
	
	// Turn off temporarily
	PORTD = SEGMENTS_OFF;
	
	// Switch to current digit
	PORTB = currentDigit;

	// Digits in displayBuffer must be already encoded
	PORTD = displayBuffer[currentDigit];
	
	// Switch to next digit
	if(++currentDigit == NUM_SEGMENTS)
		currentDigit = 0;
}