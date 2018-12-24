#include "lcd.h"

void SPI_MasterInit(void)
{
	DDRB = 0xCF;
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPR1);

	PORTB = 0x80;
}

void SPI_MasterTransmit(unsigned char Data)
{
	SPDR = Data;
	while(!(SPSR & (1<<SPIF)));
}

void LCD_InitContrastPWM()
{
	TCCR1A = (1<<COM1C1) | (1<<WGM11) | (1<<WGM10);
	TCCR1B = (1<<WGM12) | (1<<CS10);
	
	OCR1C = 300;
}

void LCD_Write(unsigned char Value, unsigned char RS, unsigned char RW)
{
	unsigned char ReversedValue = 0;
	unsigned char Bit = 8;

	//Byte has to be transmitted in a LSb first order (pretty stupid), so we reverse the byte
	while(Bit)
	{
		Bit--;

		if(Value & (1<<Bit))
		ReversedValue |= (1<<(7-Bit));
	}

	unsigned char StartByte = 0xF8;
	unsigned char FirstData = ReversedValue & 0xF0;
	unsigned char SecondData = (ReversedValue << 4) & 0xF0;
	
	if(RS)
		StartByte |= 2;

	if(RW)
		StartByte |= 4;

	
	SPI_MasterTransmit(StartByte);
	
	SPI_MasterTransmit(FirstData);
	
	SPI_MasterTransmit(SecondData);
}

void LCD_Clear()
{
	LCD_Write(0x01, 0, 0);
	_delay_ms(2);
}

void LCD_SetAddress(unsigned char Position, unsigned char Line)
{
	if(Line == 2)
		LCD_Write(0x80 | 0x20 | Position, 0, 0);
	else if(Line == 3)
		LCD_Write(0x80 | 0x40 | Position, 0, 0);
	else if(Line == 4)
		LCD_Write(0x80 | 0x60 | Position, 0, 0);
	else
		LCD_Write(0x80, 0, 0);
}

void LCD_Init()
{
	_delay_ms(100);
	
	SPI_MasterInit();
	LCD_InitContrastPWM();

	_delay_ms(25);

	LCD_Write(0x34, 0, 0);
	_delay_us(40);

	LCD_Write(0x09, 0, 0);
	_delay_us(40);

	LCD_Write(0x30, 0, 0);
	_delay_us(40);

	LCD_Write(0x0C, 0, 0);
	_delay_us(40);

	LCD_Clear();

	LCD_Write(0x06, 0, 0);
	_delay_us(40);
}

void LCD_WriteString(char *Data)
{
	while(*Data)
		LCD_Write(*Data++, 1, 0);
}

void LCD_WriteCharacter(char Data)
{
	LCD_Write(Data, 1, 0);
}

void LCD_SetContrast(unsigned int value)
{
	OCR1C = value;
}
