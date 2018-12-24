#define F_CPU   14745600

#include "UART_PC.h"
#include <avr/io.h>

void UART_PC_Init(unsigned int baudrate) {
	
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);
	
	unsigned long int ubrrValue = F_CPU / (16UL * baudrate) - 1;
	
	UBRR1H = (ubrrValue >> 8) & 0xFF;
	UBRR1L = ubrrValue & 0xFF;
}

unsigned char UART_PC_DataAvailable() {
	
	return UCSR1A & (1<<RXC1);
}

unsigned char UART_PC_Read() {
	
	return UDR1;
}

unsigned char UART_PC_ReadBlocking() {
	
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
}

void UART_PC_Write(unsigned char data) {
	
	while(!TXC1);
	UDR1 = data;
}