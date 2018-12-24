#ifndef UART_H_
#define UART_H_

void			UART_Init(unsigned int);
unsigned char	UART_DataAvailable();
unsigned char	UART_Read();
unsigned char	UART_ReadBlocking();
void			UART_Write(unsigned char);

#endif