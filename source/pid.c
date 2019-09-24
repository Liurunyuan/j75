/*
 * pid.c
 *
 *  Created on: 2019é”Ÿæ–¤æ‹·2é”Ÿæ–¤æ‹·14é”ŸèŠ¥çœ½ç€›ï¿½
 *      Author: Administrator
 */

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "pid.h"

volatile PIDPARA gPidPara = {0};
volatile int16 gTargetSpeed = 200;

void InitPidVar(void){
//	gPidPara.kp = 450;
//	gPidPara.ki = 500;
    gPidPara.kp = 300;
    gPidPara.ki = 400;
	gPidPara.kd = 0;
	gPidPara.targetPid = 0;  //é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·ç‰¡é”Ÿè§’ç™™IDé”Ÿæ–¤æ‹·é”Ÿè¡—ï¿½  ä»€ä¹ˆé”Ÿæ–¤æ‹·æ€�é”Ÿæ–¤æ‹·LUG

	gTargetSpeed = 200;
}

int32 sektest = 0;  //  é”Ÿå�«ç¡·æ‹·é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·å¥‚é”Ÿè¡—ç¢‰æ‹·é”Ÿç»žè£�è¾¾æ‹·é”Ÿå‰¿ç¡·æ‹·é”ŸçµƒUG

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
