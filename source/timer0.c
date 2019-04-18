#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include <string.h>
#include "global.h"
#include "timer0.h"
#include "scitx.h"
#include "ecap.h"
#include "kalman.h"
#include "pid.h"
#define N (45)

#define CALSPEED (60)



void ThresholdProtectForDuty(void) {
	if (gSysInfo.currentDuty < gSysInfo.targetDuty) {
		gSysInfo.currentDuty++;
	} 
	else if (gSysInfo.currentDuty > gSysInfo.targetDuty) {
		gSysInfo.currentDuty--;
	} 
	else {
	}

	if (gSysInfo.currentDuty > 300) {
		gSysInfo.currentDuty = 300;
	} 
	else if (gSysInfo.currentDuty <= 0) {
		gSysInfo.currentDuty = 0;
	}
//	gSysInfo.duty = gSysInfo.currentDuty;//uncomment when pass test
}

void MotorSpeed()
{
    if (gSysInfo.isEcapRefresh == 1){
		// gMotorSpeedEcap = (KalmanFilter(CalculateSpeed(gECapCount),KALMAN_Q,KALMAN_R));
		gMotorSpeedEcap = CalculateSpeed(gECapCount);
		gSysInfo.isEcapRefresh = 0;
    }
    else{
        // gMotorSpeedEcap = 0;
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
	// gSysInfo.targetDuty =  PidOutput(gMotorSpeedEcap);
	// ThresholdProtectForDuty(); 
}

void Timer1_ISR_Thread(void){
	static unsigned char count = 0;

	++count;

	if(count >= CALSPEED){
		count = 0;
		MotorSpeed();
	}

	if(gRS422TxQue.front != gRS422TxQue.rear
			&& ScibRegs.SCIFFTX.bit.TXFFST == 0){

		 EnableScibTxInterrupt();
	}
}
