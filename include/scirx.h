#ifndef _SCIRX_H
#define _SCIRX_H

#include "global.h"

#define MAXQSIZE 900

#define HEAD1 0x5a
#define HEAD2 0x5a

#define TAIL1 0xa5
#define TAIL2 0xa5

#define UNIT_LEN (3) 			//0x00(index 1 byte) + 0x00(high 8 bit) + 0x00(low 8 bit)
#define EXTRA_LEN  (9)          //head(2 bytes) + length(1 byte) + serial number(2 bytes) + crc(2 bytes) + tail(2 bytes)
#define OFFSET (5) 				//head(2 bytes) + length(1 byte) + serial number(2 bytes)

typedef void (*functionMsgCodeUnpack)(VAR16 a, int b,int c);

typedef struct _RS422RXQUE{
	char rxBuff[MAXQSIZE];
	int front;
	int rear;
}RS422RXQUE;

extern RS422RXQUE gRS422RxQue;

void SciRxIsrThread(RS422RXQUE *RS422RxQue);
void UnpackSciPackage(RS422RXQUE *RS422RxQue);
#endif
