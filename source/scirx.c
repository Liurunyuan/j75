#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "scirx.h"
#include "scitx.h"
#include <string.h>
#include "pid.h"

#define WAVE_AMOUNT (16)


RS422RXQUE gRS422RxQue = {0};
char rs422rxPack[16];


inline void Init_gRS422RxQue(void) {
	gRS422RxQue.front = 0;
	gRS422RxQue.rear = 0;
	memset(gRS422RxQue.rxBuff, 0, sizeof(gRS422RxQue.rxBuff));
}

void InitSciRxVar(void){
	Init_gRS422RxQue();
}

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
static void SetTargetSpeed(VAR16 a, int b, int c) {
	gTargetSpeed = a.value;
}

static void SetSystemState(VAR16 a, int b, int c) {
	gSysState.targetState = a.value;
}

static void SetPidKp(VAR16 a, int b, int c) {
	gPidPara.kp = a.value;
}

static void SetPidKi(VAR16 a, int b, int c) {
	gPidPara.ki = a.value;
}

static void SetPidKd(VAR16 a, int b, int c) {
	gPidPara.kd = a.value;
}

static void SetDutyForTest(VAR16 a, int b, int c){
	int duty =  0;
	duty = (int16)a.value;

	if(duty >= 0){
		// gSysInfo.duty = a.value; // do not need to change the duty, only change the target speed
		// gSysInfo.repeatPeriod = duty;
		gPidPara.kp = duty;
	}
}

static void ClearAlarmInfo(VAR16 a, int b, int c){
	int clearAlarm = 0;
	clearAlarm = a.value;
	if(clearAlarm == 1){
		gSysAlarm.all = 0;
		gSysInfo.hallErrorCount = 0;
		gSysInfo.maxCurrent = 0;
	}
}

const functionMsgCodeUnpack msgInterface[] = {
			0,					   	//0
			SetSystemState,		   	//1
			SetTargetSpeed,		   	//2
			WaveCommand,		   	//3
			ClearAlarmInfo,			//4
			0,						//5
			0,						//6
			0,						//7
			0,						//8
			0,						//9
			0,						//10
			0,						//11
			0,						//12
			0,						//13
			0,						//14
			0,						//15
			0,						//16
			0,						//17
			0,						//18
			0,						//19
			0,						//20
			0,						//21
			0,						//22
			0,						//23
			0,						//24
			0,						//25
			0,						//26
			0,						//27
			0,						//28
			0,						//29
			0,						//30
			0,						//31
			0,						//32
			0,						//33
			0,						//34
			0,						//35
			0,						//36
			0,						//37
			0,						//38
			0,						//39
			0,						//40
			0,						//41
			0,						//42
			0,						//43
			0,						//44
			0,						//45
			0,						//46
			0,						//47
			0,						//48
			0,						//49
			0,						//50
			0,						//51
			0,						//52
			0,						//53
			0,						//54
			0,						//55
			0,						//56
			0,						//57
			0,						//58
			0,						//59
			0,						//60
			0,						//61
			0,						//62
			0,						//63
			0,						//64
			0,						//65
			0,						//66
			0,						//67
			0,						//68
			0,						//69
			0,						//70
			0,						//71
			0,						//72
			0,						//73
			0,						//74
			SetPidKp,				//75
			SetPidKi,				//76
			SetPidKd,				//77
			0,						//78
			SetDutyForTest,			//79
			0,						//80
			0,						//81
			0						//82

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
