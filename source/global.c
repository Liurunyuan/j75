#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"


SYSINFO gSysInfo = {0};
SYSSTATE gSysState = {0};
SYSALARM gSysAlarm = {0};

void InitGlobalVar(void){
	gSysState.currentstate = INIT;
	gSysInfo.duty = 100;
	gSysInfo.dutyUp = 0;
	gSysInfo.dutyDown = 0;
	gSysInfo.currentHallPosition = 0;
	gSysInfo.lastTimeHalllPosition = 0;
	gSysInfo.isEcapRefresh = 0;

	gSysAlarm.all = 0;
}
void Delay(int time){
	int i;
	for(i = 0; i < time; ++i){
		asm(" NOP");
	}
}


void clearHardwareErro(void){
	GpioDataRegs.GPADAT.bit.GPIO29 = 1;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	GpioDataRegs.GPADAT.bit.GPIO29 = 0;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	GpioDataRegs.GPADAT.bit.GPIO29 = 1;
}


void enablePwmOutput(void){
	GpioDataRegs.GPADAT.bit.GPIO31 = 0;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
}
