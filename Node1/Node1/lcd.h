#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
	#define F_CPU	14745600
#endif

#include <avr/io.h>
#include <util/delay.h>

void LCD_Clear(void);
void LCD_SetAddress(unsigned char Position, unsigned char Line);
void LCD_Init(void);
void LCD_WriteString(char *Data);
void LCD_WriteCharacter(char Data);
void LCD_SetContrast(unsigned int value);


#endif 