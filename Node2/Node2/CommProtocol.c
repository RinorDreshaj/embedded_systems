#include "CommProtocol.h"

unsigned char COMM_IsHeader(unsigned char value) {
	
	return value & 0x80;
}

unsigned char COMM_IsWrite(unsigned char value) {
	
	return value & 0x40;
}

unsigned char COMM_GetField(unsigned char value) {
	
	return (value >> 3) & 0x03;
}

unsigned int COMM_GetPayloadHigh(unsigned char value) {
	
	return (unsigned int)(value & 0x07) << 7;
}

unsigned int COMM_GetPayloadLow(unsigned char value) {
	
	return value & 0x7F;
}

