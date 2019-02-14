#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"


SYSINFO gSysInfo = {0};
SYSSTATE gSysState = {0};

void InitGlobalVar(void){
	gSysState.currentstate = 0;
	gSysInfo.duty = 0;
	gSysInfo.currentHallPosition = 0;
	gSysInfo.lastTimeHalllPosition = 0;
}
void Delay(int time){
	int i;
	for(i = 0; i < time; ++i){
		asm(" NOP");
	}
}
