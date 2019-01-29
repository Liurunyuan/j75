/*
 * main.c
 */

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
int test = 0;
void Init_Peripheral(){
	/*Init IO pin */
	Init_GPIO();
	/*Init and config ADC*/
	Init_ADC();
	/*Init and cnofig XINTF*/
	//InitXINTF();
	/*Init and config SCI RS422*/
	//Init_SCI();
	/*Init and config SPI*/
	//InitSPI();
	/*Init and config A-CAN and B-CAN */
	//InitCAN();
	/*Init and config I2C*/
	//InitI2C();
	/*Init and config CAP4,CAP5,CAP6*/
	Init_ECAP();
	/*Init and config QEP2*/
	//InitQEP();
	/*PWM IO init and config*/
	Init_EPWM();
	/*DMA init and config*/
	//InitDMA();
}
void InitGlobalVar(){

}
void MainLoop(){


}
void Delay(int time){
	int i;
	for(i = 0; i < time; ++i){
		asm(" NOP");
	}
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
