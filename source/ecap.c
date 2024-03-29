#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "ecap.h"


volatile Uint64  gECapCount = 0;
volatile int16 gMotorSpeedEcap = 0;

void InitEcapVar(void){
	gMotorSpeedEcap = 0;
	gECapCount = 0;
}

int GetECap1Count(void){

	if(ECap1Regs.ECFLG.bit.CEVT1){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap1Regs.CAP1;
	}
	else if(ECap1Regs.ECFLG.bit.CEVT2){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap1Regs.CAP2 - ECap1Regs.CAP1;
	}
	else if(ECap1Regs.ECFLG.bit.CEVT3){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap1Regs.CAP3 - ECap1Regs.CAP2;
	}
	else if(ECap1Regs.ECFLG.bit.CEVT4){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap1Regs.CAP4 - ECap1Regs.CAP3;
	}
	else if(ECap1Regs.ECFLG.bit.CTROVF){
		//TODO
		// ECap1Regs.ECCTL2.bit.REARM = 1;
	}
	else{
		
	}
	return gECapCount;
}
int GetECap2Count(void){

	if(ECap2Regs.ECFLG.bit.CEVT1){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap2Regs.CAP1;
	}
	else if(ECap2Regs.ECFLG.bit.CEVT2){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap2Regs.CAP2 - ECap2Regs.CAP1;
	}
	else if(ECap2Regs.ECFLG.bit.CEVT3){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap2Regs.CAP3 - ECap2Regs.CAP2;
	}
	else if(ECap2Regs.ECFLG.bit.CEVT4){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap2Regs.CAP4 - ECap2Regs.CAP3;
	}
	else if(ECap2Regs.ECFLG.bit.CTROVF){
		//TODO
		// ECap2Regs.ECCTL2.bit.REARM = 1;
	}
	else{

	}
	return gECapCount;
}

int GetECap3Count(void){

	if(ECap3Regs.ECFLG.bit.CEVT1){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap3Regs.CAP1;
	}
	else if(ECap3Regs.ECFLG.bit.CEVT2){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap3Regs.CAP2 - ECap3Regs.CAP1;
	}
	else if(ECap3Regs.ECFLG.bit.CEVT3){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap3Regs.CAP3 - ECap3Regs.CAP2;
	}
	else if(ECap3Regs.ECFLG.bit.CEVT4){
		gSysInfo.isEcapRefresh = 1;
		gECapCount = ECap3Regs.CAP4 - ECap3Regs.CAP3;
	}
	else if(ECap3Regs.ECFLG.bit.CTROVF){
		//TODO
		// ECap3Regs.ECCTL2.bit.REARM = 1;
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

	speed32 = ((double)2700000000)/capCount;//2700000000 = 90000000*60/2

	if((speed32 < 19200) && (speed32 >= 0)){
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
