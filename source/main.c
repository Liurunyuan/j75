/*
 * main.c
 */

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "pwm.h"
#include "scirx.h"
#include "scitx.h"
#include "adc.h"
#include "ecap.h"
#include "pid.h"
#include "kalman.h"

void InitPeripheral(){

	InitGpioForJ75();

	InitAdcForJ75();

	InitEcapForJ75();

	InitSciForJ75();

	InitEpwmForJ75();

	Init_CpuTimer_J75();
}
void InitVar(){
    gSysInfo.currentOffset = GET_I_AN_3V3_A2;

	InitAdcVar();

	InitSciRxVar();

	InitSciTxVar();

	InitEcapVar();

	InitPidVar();

	InitGlobalVar();
}

void ClearBeforeStart(void){
	gSysInfo.sek = 0;
	gSysInfo.duty = 0;
	gSysInfo.currentDuty = 0;
	gSysInfo.curp = 0;
}

void StateMachine(void){
	switch (gSysState.currentstate)
	{
		case INIT:
			if(gSysAlarm.bit.InitFault == 0){
				gSysState.currentstate = STOP;
			}
			else{
				gSysState.currentstate = ALARM;
			}
			break;
		case START:
			/* code */
			if(gSysAlarm.all != 0){
				gSysState.currentstate = ALARM;
			}
			else if(gSysState.targetState == STOP){
				gSysState.currentstate = STOP;
				DisablePwmOutput();
			}
			break;
		case STOP:
			if(gSysState.targetState == START){
			    ClearBeforeStart();
				gSysState.currentstate = START;
			}

			if(gSysAlarm.all != 0){
				gSysState.currentstate = ALARM;
			}
			break;
		case ALARM:
			DisablePwmOutput();
			if(gSysAlarm.all == 0){
				enablePwmOutput();
				if(GpioDataRegs.GPADAT.bit.GPIO15 == 1){
					gSysState.currentstate = STOP;
					gSysState.targetState = STOP;
					clearHardwareErro();
				}
				else{
					disablePwmOutput();
					gSysAlarm.bit.j = 1;
				}
			}
			break;
		default:
			gSysAlarm.bit.softwareFault = 1;
			gSysState.currentstate = ALARM;
			break;
	}
}

void MainLoop(){

	// FEED_WATCH_DOG = 1;

	ServiceDog();

	StateMachine();

	readTZGpioState();

	updateAndCheckVoltage();

	updateAndCheckTemperature();

	UnpackSciPackage(&gRS422RxQue);

	clearScibOverflow();

}

void main(void) {

	InitSysCtrl();

	InitPeripheral();

	InitVar();

	DisablePwmOutput();

	ClearBeforeStart();

	InitInterruptForJ75();

	enablePwmOutput();

	clearHardwareErro();

	enableSoftwareDog();

	while(1){
		MainLoop();
	}
}
