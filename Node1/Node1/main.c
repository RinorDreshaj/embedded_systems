#define F_CPU   14745600

#include <avr/io.h>
#include <stdlib.h>
#include "CommProtocol.h"
#include "UART.h"
#include "LCD.h"

#define		FILED_LUMINESCENCE_SENSOR		1
#define		FILED_LAMP_INTENSITY			2

void ProcessWriteRequest();
void SetLuminescenceValue(unsigned int value);
void SetLampIntensity(unsigned int value);

unsigned char currentField;
unsigned int  currentPayload;

int main(void)
{
	LCD_Init();
	UART_Init(9600);
	
    while (1) 
    {
		unsigned char data = UART_ReadBlocking();
		
		if(COMM_IsHeader(data)) 
		{
			if(COMM_IsWrite(data)) 
			{
				currentField = COMM_GetField(data);
				currentPayload = COMM_GetPayloadHigh(data);
			}
			else 
			{
				// Node 1 doesn't have any sensors, so we ignore reads
			}
		}
		else 
		{
			currentPayload = currentPayload | COMM_GetPayloadLow(data);
			ProcessWriteRequest();
		}
    }
}

void ProcessWriteRequest() 
{
	switch (currentField)
	{
		case FILED_LUMINESCENCE_SENSOR:
			SetLuminescenceValue(currentPayload);
			break;
		
		case FILED_LAMP_INTENSITY:
			SetLampIntensity(currentPayload);
			break;
	}
}

void SetLuminescenceValue(unsigned int value) 
{
	LCD_Clear();

	LCD_SetAddress(0, 1);
	LCD_WriteString("Intensity: ");
	
	char strValue[6];
	itoa(value, strValue, 10);
	
	LCD_WriteString(strValue);
}

void SetLampIntensity(unsigned int value)
{
	DDRB |= 1<<PINB5 | 1<<PINB6;

	TCCR1A |= (1<<COM1C1) | (1<<COM1A1) | (1<<WGM11) | (1<<WGM10);
	TCCR1B = (1<<WGM12) | (1<<CS10);

	OCR1A = value;
}
