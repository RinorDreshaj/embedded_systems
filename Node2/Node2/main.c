#define F_CPU   14745600

#include <avr/io.h>
#include <util/delay.h>
#include "SevenSegment.h"
#include "CommProtocol.h"
#include "UART.h"

#define		FILED_TEMPERATURE_SENSOR	3

void ProcessWriteRequest();
void SetTemperatureValue(unsigned int value);

unsigned char displayRefreshCounter;
unsigned char currentField;
unsigned int  currentPayload;

int main(void)
{
	SEGDISP_Init();
	UART_Init(9600);
	
	displayRefreshCounter = 0;
	
	while (1)
	{
		if(!displayRefreshCounter++)
			SEGDISP_Refresh();
		
		if(UART_DataAvailable())
		{
			unsigned char data = UART_Read();
		
			if(COMM_IsHeader(data))
			{
				if(COMM_IsWrite(data))
				{
					currentField = COMM_GetField(data);
					currentPayload = COMM_GetPayloadHigh(data);
				}
				else
				{
					// Node 2 doesn't have any sensors, so we ignore reads
				}
			}
			else
			{
				currentPayload = currentPayload | COMM_GetPayloadLow(data);
				ProcessWriteRequest();
			}
		}
	}
}

void ProcessWriteRequest()
{
	switch (currentField)
	{
		case FILED_TEMPERATURE_SENSOR:
			SetTemperatureValue(currentPayload);
			break;
	}
}

void SetTemperatureValue(unsigned int value)
{
	// Convert ADC value to temperature (check LM335 datasheet!)
	float temperatureValue = 500.0f * value / 1024.0f - 273.15f;
	
	SEGDISP_SetFloat(temperatureValue, 2);
}

