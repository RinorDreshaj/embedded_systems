#define F_CPU   14745600

#include <avr/io.h>
#include <util/delay.h>
#include "CommProtocol.h"
#include "UART_PC.h"
#include "UART.h"

#define		FILED_LUMINESCENCE_SENSOR	1
#define		FILED_TEMPERATURE_SENSOR	3

int main(void)
{
	UART_Init(9600);
	UART_PC_Init(9600);
	
	unsigned long int pollDelay = 0;
	
    while (1) 
    {
		if(UART_DataAvailable())
			UART_PC_Write(UART_Read());
			
		if(UART_PC_DataAvailable())
			UART_Write(UART_PC_Read());
    }
}

