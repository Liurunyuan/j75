/*
 * main.c
 */

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "pwm.h"

int test = 0;
void InitPeripheral(){

	InitGpioForJ75();

	InitAdcForJ75();

	InitEcapForJ75();

	InitSciForJ75();

	InitEpwmForJ75();

	Init_CpuTimer_J75();
}
void InitGlobalVar(){
	InitTest2();
	gSysInfo.duty = 0;
}
void MainLoop(){
	FEED_WATCH_DOG = 1;

}

void main(void) {
	/*system init*/
	InitSysCtrl();
	/*peripheral init*/
	InitPeripheral();

	InitGlobalVar();

	InitInterruptForJ75();

	while(1){
		MainLoop();
		Delay(10000);
		++test;
	}
}
