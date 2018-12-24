#include "CommProtocol.h"

unsigned char COMM_IsHeader(unsigned char value) {
	
	return value & 0x80;
}

unsigned char COMM_IsWrite(unsigned char value) {
	
	return value & 0x40;
}

unsigned char COMM_GetField(unsigned char value) {
	
	return (value >> 3) & 0x07;
}

unsigned int COMM_GetPayloadHigh(unsigned char value) {
	
	return (unsigned int)(value & 0x07) << 7;
}

unsigned int COMM_GetPayloadLow(unsigned char value) {
	
	return value & 0x7F;
}

unsigned char COMM_GetWriteHeader(unsigned char field, unsigned int value) {
	
	unsigned char data;
	
	data  = (value >> 7) & 0x07;
	data |= (field << 3) & 0x38;
	data |= 0xC0;
	
	return data;
}

unsigned char COMM_GetWritePayload(unsigned int value) {
	
	return (value & 0x7F);
}