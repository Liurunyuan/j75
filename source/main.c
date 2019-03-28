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

	InitAdcVar();
	InitSciRxVar();
	InitSciTxVar();
	InitEcapVar();
	InitPidVar();
	InitGlobalVar();
}
void MainLoop(){
	FEED_WATCH_DOG = 1;
	UnpackSciPackage(&gRS422RxQue);
	gMotorSpeedEcap = (KalmanFilter(CalculateSpeed(gECapCount), KALMAN_Q, KALMAN_R));
}

void main(void) {

	InitSysCtrl();

	InitPeripheral();

	InitVar();

	InitInterruptForJ75();

	while(1){
		MainLoop();
		Delay(10000);

		//test github
	}
}
