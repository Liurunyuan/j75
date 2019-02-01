/*
 * main.c
 */

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"

int test = 0;
void Init_Peripheral(){

	Init_GPIO();

	Init_ADC();

	Init_ECAP();

	Init_EPWM();
}
void InitGlobalVar(){

}
void MainLoop(){
	FEED_WATCH_DOG = 1;

}

void main(void) {
	/*system init*/
	InitSysCtrl();
	/*peripheral init*/
	Init_Peripheral();

	InitGlobalVar();

	Init_Interrupt();

	while(1){
		MainLoop();
		Delay(10000);
		++test;
	}
}
