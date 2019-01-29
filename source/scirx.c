#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "scirx.h"
#include "scitx.h"

#define WAVE_AMOUNT (16)


RS422RXQUE gRS422RxQue = {0};
char rs422rxPack[16];
static void WaveCommand(VAR16 a, int b, int c) {
	int i;

	for(i = 0; i < WAVE_AMOUNT; ++i){
		//unpack bit information
		if((a.value & (0x0001 << i)) >> i){
			gRx422TxEnableFlag[i] = ENABLE_TX;
		}
		else{
			gRx422TxEnableFlag[i] = DISABLE_TX;
		}
	}
}
const functionMsgCodeUnpack msgInterface[] = {
			WaveCommand,
			0,
			0
};
int EnQueue(int e, RS422RXQUE *RS422RxQue){

	if((RS422RxQue->rear + 1) % MAXQSIZE == RS422RxQue->front){
		RS422RxQue->front = (RS422RxQue->front + 1) % MAXQSIZE;
	}

	RS422RxQue->rxBuff[RS422RxQue->rear] = e;
	RS422RxQue->rear = (RS422RxQue->rear + 1) % MAXQSIZE;
	return 1;
}

int DeQueue(RS422RXQUE *RS422RxQue){
	if(RS422RxQue->front == RS422RxQue->rear){
		return 0;
	}

	RS422RxQue->front = (RS422RxQue->front + 1) % MAXQSIZE;
	return 1;
}

Uint16 IsQueueEmpty(RS422RXQUE *RS422RxQue){
	if(RS422RxQue->front == RS422RxQue->rear){
		return 0;
	}
	else{
		return 1;
	}
}

int RS422RxQueLength(RS422RXQUE *RS422RxQue){
	int length;
	length = (RS422RxQue->rear - RS422RxQue->front + MAXQSIZE) % MAXQSIZE;
	return length;
}

void SciRxIsrThread(RS422RXQUE *RS422RxQue){
	int16 data;

	while(ScibRegs.SCIFFRX.bit.RXFFST != 0){// rs422 rx fifo is not empty
		data = ScibRegs.SCIRXBUF.all;
		if(EnQueue(data, RS422RxQue) == 0){
		//todo
		}
	}

}

int CalCrc(int crc, const char *buf, int len){
	int x;
	int i;

	for(i = 0; i < len; ++i){
		x = ((crc >> 8) ^ buf[i]) & 0xff;
		x ^= x >> 4;
		crc = (crc << 8) ^ (x  << 12) ^ (x << 5) ^ x;
		crc &= 0xffff;
	}
	return crc;
}

int findhead(RS422RXQUE *RS422RxQue){

	char head1;
	char head2;

	while(1){

		head1 = RS422RxQue->rxBuff[RS422RxQue->front];
		head2 = RS422RxQue->rxBuff[(RS422RxQue->front + 1) % MAXQSIZE];

		if(head1 == HEAD1 && head2 == HEAD2){
			return SUCCESS;
		}

		if(DeQueue(RS422RxQue) == 0){
			//printf("rs422 rx queue is empty\r\n");
			return FAIL;
		}
	}
}
int findtail(int len, RS422RXQUE *RS422RxQue){
	char tail1;
	char tail2;

	tail1 = RS422RxQue->rxBuff[(RS422RxQue->front + len - 1) % MAXQSIZE];
	tail2 = RS422RxQue->rxBuff[(RS422RxQue->front + len - 2) % MAXQSIZE];

	if(tail1 == TAIL1 && tail2 == TAIL2){
		return SUCCESS;
	}
	else{
		return FAIL;
	}
}
int checklength(RS422RXQUE *RS422RxQue){

	if((RS422RxQue->rxBuff[(RS422RxQue->front + 2) % MAXQSIZE] * UNIT_LEN + EXTRA_LEN) <= RS422RxQueLength(RS422RxQue)){
		return SUCCESS;
	}
	else{
		return FAIL;
	}
}
void saveprofile(int len, RS422RXQUE *RS422RxQue){
	int i;

	for(i = 0; i < len; ++i){
		rs422rxPack[i] = RS422RxQue->rxBuff[(RS422RxQue->front + i) % MAXQSIZE];
	}
}
void unpack(int len){
	int i;
	int msgCode;
	VAR16 var16;

	for(i = 0; i < len; ++i){

		msgCode = rs422rxPack[OFFSET + UNIT_LEN * i];
		var16.datahl.h = rs422rxPack[OFFSET + UNIT_LEN*i + 1];
		var16.datahl.l = rs422rxPack[OFFSET + UNIT_LEN*i + 2];


		if(msgCode < (sizeof(msgInterface) / sizeof(msgInterface[0]))){
			//printf("msgCode = %d\r\n",msgCode);
			if(msgInterface[msgCode]){
				msgInterface[msgCode](var16, 0, 0);
			}
		}
		else{
			//printf("unpack msg code is out of range\r\n");
		}
	}
}
void updatehead(int len, RS422RXQUE *RS422RxQue){
	RS422RxQue->front = (RS422RxQue->front + len) % MAXQSIZE;
}
void UpdateRS422RxSerialNumber(void){

//	gRS422Status.currentSerialNumber = (rs422rxPack[3] << 8) + rs422rxPack[4];

}

void UnpackSciPackage(RS422RXQUE *RS422RxQue){
	int length;
	while(RS422RxQueLength(RS422RxQue) > EXTRA_LEN){
		if(findhead(RS422RxQue) == FAIL){
			//printf("find head failed\r\n");
			return;
		}

		if(checklength(RS422RxQue) == FAIL){
			return;
		}

		length = RS422RxQue->rxBuff[(RS422RxQue->front + 2) % MAXQSIZE] * UNIT_LEN + EXTRA_LEN;

		if(findtail(length,RS422RxQue) == FAIL){
			if(DeQueue(RS422RxQue) == 0){
			}
			return;
		}

		saveprofile(length,RS422RxQue);

		if(CalCrc(0, rs422rxPack + OFFSET, length - EXTRA_LEN + 2) != 0){
			if(DeQueue(RS422RxQue) == 0){
			}
			return;
		}

		unpack(RS422RxQue->rxBuff[(RS422RxQue->front + 2) % MAXQSIZE]);
		UpdateRS422RxSerialNumber();
		updatehead(length, RS422RxQue);
	}
}
