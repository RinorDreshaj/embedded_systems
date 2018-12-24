#define F_CPU   14745600

#include <avr/io.h>
#include <util/delay.h>
#include "CommProtocol.h"
#include "Luminescence.h"
#include "Temperature.h"
#include "UART.h"
#include "Fan.h"

#define		FILED_LUMINESCENCE_SENSOR	1
#define		FILED_TEMPERATURE_SENSOR	3
#define		FILED_FAN_SPEED				4

void ProcessWriteRequest();
void ProcessReadRequest();
void SetFanSpeedValue(unsigned int value);
void WriteTemperatureValue();
void WriteLuminescenceValue();

unsigned char currentField;
unsigned int  currentPayload;

int main(void)
{
	UART_Init(9600);
	
	TEMP_Init();
	LUM_Init();
	FAN_Init();
	
	while (1)
	{
		unsigned char data = UART_ReadBlocking();
		
		if(COMM_IsHeader(data))
		{
			currentField = COMM_GetField(data);
							
			if(COMM_IsWrite(data))
			{
				currentPayload = COMM_GetPayloadHigh(data);
			}
			else
			{
				ProcessReadRequest();
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
		case FILED_FAN_SPEED:
		FAN_SetSpeed(currentPayload);
		break;
	}
}

void ProcessReadRequest() 
{
	switch (currentField)
	{
		case FILED_TEMPERATURE_SENSOR:
		WriteTemperatureValue();
		break;
		
		case FILED_LUMINESCENCE_SENSOR:
		WriteLuminescenceValue();
		break;
	}
}

void WriteTemperatureValue()
{
	unsigned int temperatureValue = TEMP_Read();
	
	UART_Write(COMM_GetWriteHeader(FILED_TEMPERATURE_SENSOR, temperatureValue));
	UART_Write(COMM_GetWritePayload(temperatureValue));
}

void WriteLuminescenceValue() 
{
	unsigned int luminescenceValue = LUM_Read();
	
	UART_Write(COMM_GetWriteHeader(FILED_LUMINESCENCE_SENSOR, luminescenceValue));
	UART_Write(COMM_GetWritePayload(luminescenceValue));
}