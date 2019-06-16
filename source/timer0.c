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
	int calSpeed = -1;

  	if (gSysInfo.isEcapRefresh == 1){

		calSpeed = CalculateSpeed(gECapCount);
		if(calSpeed != -1){
			gMotorSpeedEcap = (int16)KalmanFilter(calSpeed, KALMAN_Q, KALMAN_R);
		}
		gSysInfo.isEcapRefresh = 0;
		count = 0;
  	}
  	else{
		count++;
		if(count > 5){
		    gMotorSpeedEcap = (int16)KalmanFilter(0, KALMAN_Q, KALMAN_R);
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

	if(count >= N){
		FEED_WATCH_DOG = 1;
		PackRS422TxData();
		count = 0;
	}
}
/*************************End of Timer0********************************/

/*************************Start of Timer1*************************************/
inline void ChangeDutyAddInterval(void){
    if((gMotorSpeedEcap >= 0) && (gMotorSpeedEcap <= 3000)){
        gSysInfo.dutyAddInterval = 3;
    }
    else if((gMotorSpeedEcap > 3000) && (gMotorSpeedEcap < 6000)){
        gSysInfo.dutyAddInterval = 2;
    }
    else if(gMotorSpeedEcap >=6000){
        gSysInfo.dutyAddInterval = 1;
    }
}

void t0_DisablePwmOutput(void){
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;
}

/* interupt cpu every 5ms */
void Timer1_ISR_Thread(void){
	static unsigned char count = 0;
	int busVol;
	MotorSpeed();
	switch(gSysState.currentstate){
		case START:
			busVol = gSysAnalogVar.single.var[U_AN_3V3_A0].value = gSysAnalogVar.single.var[U_AN_3V3_A0].updateValue();
			ChangeDutyAddInterval();
			gSysInfo.openLoopTargetDuty = openLoopControl(busVol, gTargetSpeed);
			#if CLOSELOOPDONE
				gSysInfo.closeLooptargetDuty =  PidOutput(gMotorSpeedEcap);
			#else
				gSysInfo.closeLooptargetDuty = 0;
			#endif
			break;
		default:
			t0_DisablePwmOutput();
			break;
	}
	++count;
	/* count = 0,1,2,3*/
	if(count >= CALSPEED){
		/*send package per 20ms */
		count = 0;
		if(gRS422TxQue.front != gRS422TxQue.rear
			&& ScibRegs.SCIFFTX.bit.TXFFST == 0){
		 	EnableScibTxInterrupt();
		}
		else{
			t0_DisablePwmOutput();
			gSysSWAlarm.bit.txBufferFull = 1;
			gSysAlarm.bit.softwareFault = 1;
		}
	}
	else{
		/* no use */
	}
}

