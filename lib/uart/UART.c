#include "UART.h"
#include <avr/io.h>

void UART_Init(unsigned int baudrate) {
	
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<TXCIE0);
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	UBRR0H = baudrate >> 8;
	UBRR0L = baudrate & 0xff;
}

unsigned char UART_DataAvailable() {
	
	return UCSR0A & (1<<RXC0);
}

unsigned char UART_Read() {
	
	return UDR0;
}

unsigned char UART_ReadBlocking() {
	
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void UART_Write(unsigned char data) {
	
	while(!TXC0);
	UDR0 = data;
}