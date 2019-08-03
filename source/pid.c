/*
 * pid.c
 *
 *  Created on: 2019锟斤拷2锟斤拷14锟芥眽瀛�
 *      Author: Administrator
 */

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "pid.h"

volatile PIDPARA gPidPara = {0};
volatile int gTargetSpeed = 500;

void InitPidVar(void){
//	gPidPara.kp = 450;
//	gPidPara.ki = 500;
    gPidPara.kp = 300;
    gPidPara.ki = 400;
	gPidPara.kd = 0;
	gPidPara.targetPid = 0;  //锟斤拷锟斤拷牡锟角癙ID锟斤拷锟街�  什么锟斤拷思锟斤拷LUG

	gTargetSpeed = 500;
}

int32 sektest = 0;  //  锟叫硷拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷奂锟街碉拷锟绞裁达拷锟剿硷拷锟絃UG

int16 PidOutput(double currentSpeed){
	int16 pidOutput = 0;
	int64 ek1;
	//int16 dis_temp;

	ek1 = (int64)(gTargetSpeed - currentSpeed);
	if((ek1 > -gSysInfo.thresholdKiError) && (ek1 < gSysInfo.thresholdKiError))
	{
		if(((ek1 > 0) && (gSysInfo.sek < 1171070)) || ((ek1 < 0) && (gSysInfo.sek > -1171070)))
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

	/*startup distance*/
	/*
	if(200 > currentSpeed){
		dis_temp = ((int16)ek1) >> 2;
		if(MAXSTARTDISTANCE < dis_temp){
			dis_temp = MAXSTARTDISTANCE;
		}
		else if(MINSTARTDISTANCE > dis_temp){
			dis_temp = MINSTARTDISTANCE;
		}
	}
	else{
		dis_temp = gSysInfo.startDistance;
		if(1 < dis_temp){
			dis_temp = dis_temp - 1;
		}
		else{
			dis_temp = 0;
		}
	}
	gSysInfo.startDistance = dis_temp;
	*/
	/*end of startup distance*/
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
