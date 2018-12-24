#ifndef COMMPROTOCOL_H_
#define COMMPROTOCOL_H_

unsigned char	COMM_IsHeader(unsigned char);
unsigned char	COMM_IsWrite(unsigned char);
unsigned char	COMM_GetField(unsigned char);
unsigned char	COMM_GetWriteHeader(unsigned char, unsigned int);
unsigned char	COMM_GetWritePayload(unsigned int);
unsigned int	COMM_GetPayloadHigh(unsigned char);
unsigned int	COMM_GetPayloadLow(unsigned char);

#endif