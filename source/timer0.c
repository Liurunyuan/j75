#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include <string.h>
#include "global.h"
#include "timer0.h"
#include "scitx.h"
#include "ecap.h"
#include "kalman.h"
#include "pid.h"
#define N (0)

#define CALSPEED (4)



void ThresholdProtectForDuty(void) {
	if (gSysInfo.currentDuty < gSysInfo.targetDuty) {
		gSysInfo.currentDuty++;
	} 
	else if (gSysInfo.currentDuty > gSysInfo.targetDuty) {
		gSysInfo.currentDuty--;
	} 
	else {
	}

	if (gSysInfo.currentDuty > 400) {
		gSysInfo.currentDuty = 400;
	} 
	else if (gSysInfo.currentDuty <= 0) {
		gSysInfo.currentDuty = 0;
	}
	// gSysInfo.duty = gSysInfo.currentDuty;//uncomment when pass test
}

void MotorSpeed(){
	static int count = 0;
	int calSpeed = 0;

  	if (gSysInfo.isEcapRefresh == 1){

		calSpeed = CalculateSpeed(gECapCount);
		if(calSpeed != -1){
			gMotorSpeedEcap = (KalmanFilter(CalculateSpeed(gECapCount),KALMAN_Q,KALMAN_R));
		}
		gSysInfo.isEcapRefresh = 0;
		count = 0;
  	}
  	else{
		count++;
		if(count > 5){
    		gMotorSpeedEcap = 0;
			count = 0;
		}
  	}
}


void EnableScibTxInterrupt(void){
	ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1;
	ScibRegs.SCIFFTX.bit.TXFFIENA = 1;
}

void Timer0_ISR_Thread(void){

	static unsigned char count = 0;

	++count;

	if(count > N){
		PackRS422TxData();
		count = 0;
	}
}

void Timer1_ISR_Thread(void){
	static unsigned char count = 0;

	MotorSpeed();
	if(gSysState.currentstate == START){
		gSysInfo.targetDuty =  PidOutput(gMotorSpeedEcap);
		ThresholdProtectForDuty(); 
	}

	++count;
	if(count >= CALSPEED){
		count = 0;
		if(gRS422TxQue.front != gRS422TxQue.rear
			&& ScibRegs.SCIFFTX.bit.TXFFST == 0){
		 	EnableScibTxInterrupt();
		}
	}
}
