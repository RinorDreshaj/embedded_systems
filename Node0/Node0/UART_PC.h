#ifndef UART_PC_H_
#define UART_PC_H_

void			UART_PC_Init(unsigned int);
unsigned char	UART_PC_DataAvailable();
unsigned char	UART_PC_Read();
unsigned char	UART_PC_ReadBlocking();
void			UART_PC_Write(unsigned char);

#endif