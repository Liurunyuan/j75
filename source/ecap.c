#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "ecap.h"


long int  gECapCount = 0;
double gMotorSpeedEcap = 0;

void InitEcapVar(void){
	gMotorSpeedEcap = 0;
	gECapCount = 0;
}

int GetECap1Count(void){

	gSysInfo.isEcapRefresh = 1;

	if(ECap1Regs.ECFLG.bit.CEVT1){
		gECapCount = ECap1Regs.CAP1;
	}
	else if(ECap1Regs.ECFLG.bit.CEVT2){
		gECapCount = ECap1Regs.CAP2 - ECap1Regs.CAP1;
	}
	else if(ECap4Regs.ECFLG.bit.CEVT3){
		gECapCount = ECap1Regs.CAP3 - ECap1Regs.CAP2;
	}
	else if(ECap4Regs.ECFLG.bit.CEVT4){
		gECapCount = ECap1Regs.CAP4 - ECap1Regs.CAP3;
	}
	else{

	}
	return gECapCount;
}
int GetECap2Count(void){

	gSysInfo.isEcapRefresh = 1;

	if(ECap2Regs.ECFLG.bit.CEVT1){
		gECapCount = ECap2Regs.CAP1;
	}
	else if(ECap2Regs.ECFLG.bit.CEVT2){
		gECapCount = ECap2Regs.CAP2 - ECap2Regs.CAP1;
	}
	else if(ECap2Regs.ECFLG.bit.CEVT3){
		gECapCount = ECap2Regs.CAP3 - ECap2Regs.CAP2;
	}
	else if(ECap2Regs.ECFLG.bit.CEVT4){
		gECapCount = ECap2Regs.CAP4 - ECap2Regs.CAP3;
	}
	else{

	}
	return gECapCount;
}

int GetECap3Count(void){

	gSysInfo.isEcapRefresh = 1;

	if(ECap3Regs.ECFLG.bit.CEVT1){
		gECapCount = ECap3Regs.CAP1;
	}
	else if(ECap3Regs.ECFLG.bit.CEVT2){
		gECapCount = ECap3Regs.CAP2 - ECap3Regs.CAP1;
	}
	else if(ECap3Regs.ECFLG.bit.CEVT3){
		gECapCount = ECap3Regs.CAP3 - ECap3Regs.CAP2;
	}
	else if(ECap3Regs.ECFLG.bit.CEVT4){
		gECapCount = ECap3Regs.CAP4 - ECap3Regs.CAP3;
	}
	else{

	}
	return gECapCount;
}
int32 CalculateSpeed(Uint32 capCount){
	//TODO calculate the motor speed
	int32 speed32 = 0;
	if(capCount <= 0){
		return -1;
	}

	speed32 = ((2700000000.0)/(float)capCount);//2700000000 = 90000000*60/2

	if(speed32 < 19200){
		return speed32;
	}
	else{
		return -1;
	}
}

void ECap1_Isr(void){
	GetECap1Count();
}

void ECap2_Isr(void){
	GetECap2Count();
}

void ECap3_Isr(void){
	GetECap3Count();
}
