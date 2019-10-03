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

#define CALSPEED (6)

void updateKpAndKiPara(void)
{
	int64 kmi;
	int64 kmp;

	int64 ekabs = 0;
	ekabs = gTargetSpeed - gMotorSpeedEcap;
	if(ekabs < 0){
		ekabs = -ekabs;
	}

	kmi = 300 - (ekabs>>4);
	if(kmi < 50)
	{
		kmi = 50;
	}
	else if(kmi > 300){
		kmi = 300;
	}
	else{

	}

	kmp = 400 - (ekabs>>5);
	if(kmp < 100){
		kmp = 100;
	}
	else if(kmp > 400)
	{
		kmp = 400;
	}
	else{

	}

	gPidPara.ki = (gSysInfo.aKi * kmi) >> 10;
	gPidPara.kp = (gSysInfo.aKp * kmp) >> 10;
}

void changeKiWOnResonance(void){
	int ds = 0;
	ds = gTargetSpeed - gMotorSpeedEcap;
	if(gTargetSpeed == 4000){
		if(ds < 200 || ds > -200){
			gPidPara.ki = 270;
		}
		else{
			gPidPara.ki = 400;
		}
	}
	else if(gTargetSpeed == 8000){
		if(ds < 200 || ds > -200){
			gPidPara.ki = 270;
		}
		else{
			gPidPara.ki = 400;
		}
	}
	else{
		gPidPara.ki = 400;
	}
}

void motorSpeedForUI(void){

    static int i = 0;
    static int64 tmp[4] = {0, 0, 0, 0};
    int64 ret = 0;
    int j;
    tmp[i] = gMotorSpeedEcap;
    ++i;
    if(i >= 4){
        i = 0;
    }
    for(j = 0; j < 4; ++j){
        ret += tmp[j];
    }
    ret = ret >> 2;
    gSysInfo.speedUI  = (int16)ret;
}

void currentFilter(void){
	static int i = 0;
    static int64 tmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int64 ret = 0;
    int j;
    tmp[i] = gSysAnalogVar.single.var[I_AN_3V3_A2].updateValue();
    ++i;
    if(i >= 8){
        i = 0;
    }
    for(j = 0; j < 8; ++j){
        ret += tmp[j];
    }
    ret = ret >> 3;
	gSysInfo.aveCurrent = (int16)KalmanFilterCurrent(ret,1,300);
    // gSysInfo.aveCurrent = (int16)ret;
}

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
#if(SCI_PROTOCAL_401_SUPPORT == INCLUDE_FEATURE)
		PackRS422TxData401();
#else
		PackRS422TxData();
#endif
		count = 0;
	}
}
/*************************End of Timer0********************************/

/*************************Start of Timer1*************************************/
inline void ChangeDutyAddInterval(void){
    if((gMotorSpeedEcap < 200) && (gMotorSpeedEcap >= 0)){
        gSysInfo.dutyAddInterval = 3;
        gSysInfo.ddtmax = 1;
        gSysInfo.dtDuty = 0;
		gSysInfo.formularRa = 270;
    }
    else if((gMotorSpeedEcap >= 200) && (gMotorSpeedEcap <= 3000)){
        gSysInfo.dutyAddInterval = 3;
        gSysInfo.ddtmax = 1;
        gSysInfo.dtDuty = 0;
		gSysInfo.formularRa = 270;
    }
    else if((gMotorSpeedEcap > 3000) && (gMotorSpeedEcap < 6000)){
        gSysInfo.dutyAddInterval = 3;
        gSysInfo.ddtmax = 1;
        gSysInfo.dtDuty = 0;
		gSysInfo.formularRa = 270;
    }
    else if(gMotorSpeedEcap >=6000){
        gSysInfo.dutyAddInterval = 3;
        gSysInfo.ddtmax = 1;
        gSysInfo.dtDuty = 0;
		// gSysInfo.formularRa = 270 - gTargetSpeed - 6000 >> 5;
		gSysInfo.formularRa = (270 - ((gMotorSpeedEcap - 6000) >> 5));
    }
    gSysInfo.formularRa = gSysInfo.formularRa >> 3;

}

void t0_DisablePwmOutput(void){
#if(SCI_PROTOCAL_401_SUPPORT == INCLUDE_FEATURE)
	asm(" NOP");
#else
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;
#endif
}

/* interupt cpu every 5ms */
void Timer1_ISR_Thread(void){
	static unsigned char count = 0;
	int busVol;
	MotorSpeed();

	//disable this function. No more need to use this fucntion
	//changeKiWOnResonance();

	updateKpAndKiPara();

//    motorSpeedForUI();

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
			currentFilter();
		if(gRS422TxQue.front != gRS422TxQue.rear
			&& ScibRegs.SCIFFTX.bit.TXFFST == 0){
		 	EnableScibTxInterrupt();
		}
		else{
		    /* do nothing */
		}
	}
	else{
		/* no use */
	}
}

