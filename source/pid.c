/*
 * pid.c
 *
 *  Created on: 2019��2��14��
 *      Author: Administrator
 */

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "pid.h"

volatile PIDPARA gPidPara = {0};
volatile double gTargetSpeed = 500;

void InitPidVar(void){
//	gPidPara.kp = 450;
//	gPidPara.ki = 500;
    gPidPara.kp = 300;
    gPidPara.ki = 400;
	gPidPara.kd = 0;
	gPidPara.targetPid = 0;

	gTargetSpeed = 500;
}

int32 sek = 0;
int32 sektest = 0;

int16 PidOutput(double currentSpeed){
	int16 pidOutput = 0;
	int32 ek1;

	ek1 = (int32)(gTargetSpeed - currentSpeed);
	if((ek1 > -gSysInfo.thresholdKiError) && (ek1 < gSysInfo.thresholdKiError))
	{
		if(((ek1 > 0) && (sek < 585535)) || ((ek1 < 0) && (sek > -585535)))
		{
		        sek = sek + ek1;
		}
	}
	else
	{
		sek = 0;
	}
	sektest = sek;
	pidOutput = (int16)((ek1 * gPidPara.kp) >> 14) + (int16)(((sek >> 8) * gPidPara.ki) >> 11);

	if(pidOutput > 800){
		pidOutput = 800;
	}
	else if(pidOutput < -800){
		pidOutput = -800;
	}
	gPidPara.targetPid = pidOutput;

	return pidOutput;
}

int16 openLoopControl(int16 busVol, int16 targetSpeed){
	//find the target duty by bus voltage and motor speed
	int16 ret = 0;

	// ret = findOpenLoopDuty(busVol, targetSpeed);
	ret = findOpenLoopDutyByFormula(busVol, targetSpeed, gSysInfo.maxCurrent);

#if OPENLOOPDONE
	return ret;
#else
	return ret * 0.7;
#endif
}
