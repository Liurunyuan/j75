#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include <string.h>
#include "global.h"
#include "scitx.h"
#include "ecap.h"

#define S (0)

RS422TXQUE gRS422TxQue = {0};
GRX422TX gRx422TxVar[TOTAL_TX_VAR] = {0};
Uint16 gRx422TxEnableFlag[TOTAL_TX_VAR] = {0};

void GetTorqueCurve(int a, int b, int c){
	gRx422TxVar[0].value = 500;
}
void GetMotorSpeedCurve(int a, int b, int c){
	gRx422TxVar[1].value = gMotorSpeedEcap;
}
void GetDisplacementCurve(int a, int b, int c){
	gRx422TxVar[2].value = 1;
}
void GetMotorCurrentCurve(int a, int b, int c){
	gRx422TxVar[3].value = 2;
}
void GetDynamoVoltageCurve(int a, int b, int c){
	gRx422TxVar[4].value = 1;
}
void GetDynamoCurrentCurve(int a, int b, int c){
	gRx422TxVar[4].value = 1;
}
void GetTemperatureCurve(int a, int b, int c){
	gRx422TxVar[5].value = 3000;
}
void GetMotorAccelCurve(int a, int b, int c){
	gRx422TxVar[6].value = 3;
}
void InitgRx422TxEnableFlag(void){
	int index;

	memset(gRx422TxEnableFlag, 0, sizeof(gRx422TxEnableFlag));
	for (index = 0; index < 16; ++index) {

		gRx422TxEnableFlag[index] = 0;
	}
}
void Init_gRS422TxQue(void) {
	gRS422TxQue.front = 0;
	gRS422TxQue.rear = 0;
	memset(gRS422TxQue.txBuf, 0, sizeof(gRS422TxQue.txBuf));
}
void InitgRx422TxVar(void) {

	int index;

	memset(gRx422TxVar, 0, sizeof(gRx422TxVar));
	for (index = 0; index < 16; ++index) {

		gRx422TxVar[index].isTx = 0;
		gRx422TxVar[index].index = index;
	}
	gRx422TxVar[0].updateValue = GetTorqueCurve;
	gRx422TxVar[1].updateValue = GetMotorSpeedCurve;
	gRx422TxVar[2].updateValue = GetDisplacementCurve;
	gRx422TxVar[3].updateValue = GetMotorCurrentCurve;
	gRx422TxVar[4].updateValue = GetDynamoVoltageCurve;
	gRx422TxVar[5].updateValue = GetDynamoCurrentCurve;
	gRx422TxVar[6].updateValue = GetTemperatureCurve;
	gRx422TxVar[7].updateValue = GetMotorAccelCurve;
}

void InitSciTxVar(void){
	InitgRx422TxVar();
	Init_gRS422TxQue();
	InitgRx422TxEnableFlag();
}

int RX422TXEnQueue(char e){
	if((gRS422TxQue.rear + 1) % TXMAXQSIZE == gRS422TxQue.front){
		asm ("      ESTOP0");
		return 0;
	}

	gRS422TxQue.txBuf[gRS422TxQue.rear] = e;
	gRS422TxQue.rear = (gRS422TxQue.rear + 1) % TXMAXQSIZE;
	return 1;
}
int RX422TXDeQueue(void){
	if(gRS422TxQue.front == gRS422TxQue.rear){
		return 0;
	}
	gRS422TxQue.front = (gRS422TxQue.front + 1) % TXMAXQSIZE;
	return 1;
}
int RS422TxQueLength(){
	int length;
	length = (gRS422TxQue.rear - gRS422TxQue.front + TXMAXQSIZE) % TXMAXQSIZE;
	return length;
}
int calCrc(int crc, const char *buf, int len) {
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
void updateTxEnableFlag(void) {
	int i;
	for (i = 0; i < TOTAL_TX_VAR; ++i) {
		gRx422TxVar[i].isTx = gRx422TxEnableFlag[i];
	}
}
void PackRS422TxData(void){
	int i;
	char crcl;
	char crch;
	static unsigned char count = 0;
	static int crc = 0;
	char tmp[3] = {0};
	int lenPosition = 0;
	Uint16 total =0;

	if(count == 0){
		if(RX422TXEnQueue(0x5a) == 0){
			asm ("      ESTOP0");
			return;
		}
		if(RX422TXEnQueue(0x5a) == 0){
			asm ("      ESTOP0");
			return;
		}

		lenPosition = gRS422TxQue.rear;
		if(RX422TXEnQueue(0x05) == 0){
			asm ("      ESTOP0");
			return;
		}
		if(RX422TXEnQueue(0xff) == 0){
			asm ("      ESTOP0");
			return;
		}
		if(RX422TXEnQueue(0xff) == 0){
			asm ("      ESTOP0");
			return;
		}
		updateTxEnableFlag();
	}

	for(i = 0; i < TOTAL_TX_VAR; ++i){
		if(gRx422TxVar[i].isTx){
			++total;

			gRx422TxVar[i].updateValue(0,0,0);
			tmp[0] = gRx422TxVar[i].index;
			tmp[1] = gRx422TxVar[i].value >> 8;
			tmp[2] = gRx422TxVar[i].value;
			if(RX422TXEnQueue(gRx422TxVar[i].index) == 0){
				asm ("      ESTOP0");
				return;
			}
			if(RX422TXEnQueue(gRx422TxVar[i].value >> 8) == 0){
				asm ("      ESTOP0");
				return;
			}
			if(RX422TXEnQueue(gRx422TxVar[i].value) == 0){
				asm ("      ESTOP0");
				return;
			}
			crc = calCrc(crc, tmp, 3);
		}
	}

	if(count == 0){
		gRS422TxQue.txBuf[lenPosition] = total * (S + 1);//timer0 interrupt isr can not be interrupted by TX, so we can set length value here
	}

	++count;

	if(count > S){

		crcl = (char)crc;
		crch = (char)(crc >> 8);
		crc = 0;
		count = 0;
		if(RX422TXEnQueue(crch) == 0){
			asm ("      ESTOP0");
			return;
		}
		if(RX422TXEnQueue(crcl) == 0){
			asm ("      ESTOP0");
			return;
		}
		if(RX422TXEnQueue(0xa5) == 0){
			asm ("      ESTOP0");
			return;
		}
		if(RX422TXEnQueue(0xa5) == 0){
			asm ("      ESTOP0");
			return;
		}
	}
}
void ScibTxByte(Uint16 t){

	ScibRegs.SCITXBUF = t;

}

void SciaTxByte(Uint16 t){

	SciaRegs.SCITXBUF = t;
}

void DisableScibTxInterrupt(void){

	ScibRegs.SCIFFTX.bit.TXFFIENA = 0;

}

void SciTxIsrThread(void){
	if(gRS422TxQue.front == gRS422TxQue.rear){
		DisableScibTxInterrupt();//disable the tx interrupt when tx fifo empty
		return;
	}

	while((ScibRegs.SCIFFTX.bit.TXFFST != 16)){
		if(RS422TxQueLength() == 0)
		{
			return;
		}
		
		ScibTxByte(gRS422TxQue.txBuf[gRS422TxQue.front]);

		if(RX422TXDeQueue() == 0){
			DisableScibTxInterrupt();
			return;
		}
	}
}
