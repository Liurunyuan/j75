#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"


volatile SYSINFO gSysInfo = {0};
volatile SYSSTATE gSysState = {0};
volatile SYSALARM gSysAlarm = {0};

void InitGlobalVar(void){
	gSysState.currentstate = INIT;
	gSysState.targetState = INIT;
	gSysInfo.duty = 0;
	gSysInfo.dutyUp = 0;
	gSysInfo.dutyDown = 0;
	gSysInfo.currentHallPosition = 0;
	gSysInfo.lastTimeHalllPosition = 0;
	gSysInfo.isEcapRefresh = 0;
	gSysInfo.targetDuty = 0;
	gSysInfo.currentDuty = 0;

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
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
}


void enablePwmOutput(void){
	GpioDataRegs.GPADAT.bit.GPIO31 = 0;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
}

void disablePwmOutput(void){
	GpioDataRegs.GPADAT.bit.GPIO31 = 1;
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
	asm(" NOP");
}

void enableEcapInterrupt(void){
	PieCtrlRegs.PIEIER4.bit.INTx1 = 1;//ECAP1
	PieCtrlRegs.PIEIER4.bit.INTx2 = 1;//ECAP2
	PieCtrlRegs.PIEIER4.bit.INTx3 = 1;//ECAP3
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1; 
	ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1; 
	ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1; 
}

void disableEcapInterrupt(void){
	PieCtrlRegs.PIEIER4.bit.INTx1 = 0;//ECAP1
	PieCtrlRegs.PIEIER4.bit.INTx2 = 0;//ECAP2
	PieCtrlRegs.PIEIER4.bit.INTx3 = 0;//ECAP3
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0; 
	ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0; 
	ECap3Regs.ECCTL2.bit.TSCTRSTOP = 0; 
}

void clearScibOverflow(void){
	if(ScibRegs.SCIFFRX.bit.RXFFOVF == 1){
		ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
		ScibRegs.SCIFFRX.bit.RXFFOVF = 1;
		gSysAlarm.bit.InitFault = 1;
	}
}

void readTZGpioState(void){
	//this function will remove when TZ is configured
	int gpio14state = -1;

	gpio14state = GpioDataRegs.GPADAT.bit.GPIO14;

	if(gpio14state == 0){
		gSysAlarm.bit.f = 1;
	}
}
