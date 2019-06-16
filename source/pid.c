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
	int16 maxbreak;
	int16 minbreak;

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
	dis_temp = ((int16)ek1) >> 2;
	if(2000 > gTargetSpeed){
		maxbreak = MAXBREAKDISTANCE;
		minbreak = MINBREAKDISTANCE;
	}
	else if(4000 > gTargetSpeed){
		maxbreak = MAXBREAKDISTANCE >> 2;
		minbreak = MINBREAKDISTANCE >> 2;
	}
	else{
		maxbreak = MAXBREAKDISTANCE >> 3;
		minbreak = MINBREAKDISTANCE >> 3;
	}
	if(maxbreak < dis_temp){
		dis_temp = maxbreak;
	}
	else if(minbreak > dis_temp){
		dis_temp = minbreak;
	}
	if((300 < ek1) || (-300 > ek1)){
		gSysInfo.breakDistance = dis_temp;
	}
	else{
		dis_temp = gSysInfo.breakDistance;
		if(3 < dis_temp){
			dis_temp = dis_temp - 3;
		}
		else if(-3 > dis_temp){
			dis_temp = dis_temp + 3;
		}
		else{
			dis_temp = 0;
		}
		gSysInfo.breakDistance = dis_temp;
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
