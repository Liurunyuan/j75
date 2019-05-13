#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include <string.h>
#include "global.h"
#include "timer0.h"
#include "scitx.h"
#include "ecap.h"
#include "kalman.h"
#include "pid.h"
#include "adc.h"
#define N (1)

#define CALSPEED (4)

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
	gSysAnalogVar.single.var[U_AN_3V3_A0].value = gSysAnalogVar.single.var[U_AN_3V3_A0].updateValue();
	int busVol = gSysAnalogVar.single.var[U_AN_3V3_A0].value;
	MotorSpeed();
	if(gSysState.currentstate == START){

		if(gSysInfo.enableFindTable){
			gSysInfo.openLoopTargetDuty = openLoopControl(busVol, gTargetSpeed);
		}
		else{
			gSysInfo.openLoopTargetDuty = gSysInfo.uiSetOpenLoopDuty;
		}
		
	#if CLOSELOOPDONE
		gSysInfo.closeLooptargetDuty =  PidOutput(gMotorSpeedEcap);
	#else
		gSysInfo.closeLooptargetDuty = 0;
	#endif
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

