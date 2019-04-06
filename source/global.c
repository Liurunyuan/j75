#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"


SYSINFO gSysInfo = {0};
SYSSTATE gSysState = {0};
SYSALARM gSysAlarm = {0};

void InitGlobalVar(void){
	gSysState.currentstate = INIT;
	gSysInfo.duty = 0;
	gSysInfo.currentHallPosition = 0;
	gSysInfo.lastTimeHalllPosition = 0;

	gSysAlarm.all = 0;
}
void Delay(int time){
	int i;
	for(i = 0; i < time; ++i){
		asm(" NOP");
	}
}
