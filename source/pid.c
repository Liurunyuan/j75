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

int32 sektest = 0;

int16 PidOutput(double currentSpeed){
	int16 pidOutput = 0;
	int32 ek1;
	int16 dis_temp;

	ek1 = (int32)(gTargetSpeed - currentSpeed);
	if((ek1 > -gSysInfo.thresholdKiError) && (ek1 < gSysInfo.thresholdKiError))
	{
		if(((ek1 > 0) && (gSysInfo.sek < 585535)) || ((ek1 < 0) && (gSysInfo.sek > -585535)))
		{
			gSysInfo.sek = gSysInfo.sek + ek1;
		}
	}
	else
	{
		gSysInfo.sek = 0;
	}
	sektest = gSysInfo.sek;
	pidOutput = (int16)((ek1 * gPidPara.kp) >> 14) + (int16)(((gSysInfo.sek >> 8) * gPidPara.ki) >> 11);

	if(pidOutput > 800){
		pidOutput = 800;
	}
	else if(pidOutput < -800){
		pidOutput = -800;
	}
	gPidPara.targetPid = pidOutput;

	/*break distance*/
	if((300 < ek1) || (-300 > ek1)){
		dis_temp = ((int16)ek1) >> 2;
		if(MAXBREAKDISTANCE < dis_temp){
			dis_temp = MAXBREAKDISTANCE;
		}
		else if(MINBREAKDISTANCE > dis_temp){
			dis_temp = MINBREAKDISTANCE;
		}
		gSysInfo.breakDistance = dis_temp;
	}
	else{
		gSysInfo.breakDistance = 0;
	}
	return pidOutput;
}

int16 openLoopControl(int16 busVol, int16 targetSpeed){
	//find the target duty by bus voltage and motor speed
	int16 ret = 0;

	// ret = findOpenLoopDuty(busVol, targetSpeed);
	ret = findOpenLoopDutyByFormula(busVol, targetSpeed, gSysInfo.aveCurrent);

#if OPENLOOPDONE
	return ret;
#else
	return ret * 0.7;
#endif
}
