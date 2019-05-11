#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "pwm.h"
#include "adc.h"
#include "pid.h"
#include "ecap.h"

#define DUTYCHANGEINTERVAL (100)
/******************************************/
inline void openAH(void){
	EPwm1Regs.AQCSFRC.bit.CSFA = 3;
}

inline void closeAH(void){
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
}

inline void openAL(void){
	EPwm1Regs.AQCSFRC.bit.CSFB = 3;
}

inline void closeAL(void){
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;
}

inline void closeAHandAL(void){
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;
}
/******************************************/
inline void openBH(void){
	EPwm2Regs.AQCSFRC.bit.CSFA = 3;
}

inline void closeBH(void){
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
}
inline void openBL(void){
	EPwm2Regs.AQCSFRC.bit.CSFB = 3;
}

inline void closeBL(void){
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;
}
inline void closeBHandAL(void){
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;
}
/******************************************/
inline void openCH(void){
	EPwm3Regs.AQCSFRC.bit.CSFA = 3;
}

inline void closeCH(void){
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
}
inline void openCL(void){
	EPwm3Regs.AQCSFRC.bit.CSFB = 3;
}

inline void closeCL(void){
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;
}
inline void closeCHandAL(void){
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;
}
/******************************************/
inline void DisablePwm1(void){

	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;
}
inline void DisablePwm2(void){

	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;
}
inline void DisablePwm3(void){

	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;
}

void DisablePwmOutput(void){
	DisablePwm1();
	DisablePwm2();
	DisablePwm3();
	gSysInfo.duty = 0;
	gSysInfo.currentDuty = 0;
}
/******************************************/
inline void CPositiveToBNegtive(void) {

	DisablePwm1();

	EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;
    EPwm3Regs.AQCSFRC.bit.CSFA = 3;

	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	EPwm2Regs.AQCSFRC.bit.CSFB = 3;
}

inline void CPositiveToANegtive(void) {
	DisablePwm2();

	EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
    EPwm3Regs.AQCSFRC.bit.CSFB = 2;
	EPwm3Regs.AQCSFRC.bit.CSFA = 3;

	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	EPwm1Regs.AQCSFRC.bit.CSFB = 3;
}

inline void BPositiveToANegtive(void) {

	DisablePwm3();

	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;
    EPwm2Regs.AQCSFRC.bit.CSFA = 3;

	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	EPwm1Regs.AQCSFRC.bit.CSFB = 3;
}

inline void BPositiveToCNegtive(void) {

	DisablePwm1();

	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;
    EPwm2Regs.AQCSFRC.bit.CSFA = 3;

	EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm3Regs.AQCSFRC.bit.CSFB = 3;
}
inline void APositiveToCNegtive(void) {

	DisablePwm2();

	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;
    EPwm1Regs.AQCSFRC.bit.CSFA = 3;

	EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm3Regs.AQCSFRC.bit.CSFB = 3;
}
inline void APositiveToBNegtive(void) {

	DisablePwm3();

	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;
    EPwm1Regs.AQCSFRC.bit.CSFA = 3;

	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	EPwm2Regs.AQCSFRC.bit.CSFB = 3;
}

Uint16 GetCurrentHallValue(void){

	Uint16 temp;
	Uint16 a = 0;
	Uint16 b = 0;
	Uint16 c = 0;

	a = GpioDataRegs.GPADAT.bit.GPIO26;
	b = GpioDataRegs.GPADAT.bit.GPIO24;
	c = GpioDataRegs.GPADAT.bit.GPIO25;

	temp = ((c << 2) + (b << 1) + a);
	return temp;
}
/**************************************************************
 *Name:						SwitchDirection
 *Function:
 *Input:					none
 *Output:					none
 *Author:					Simon
 *Date:						2018.10.31
 **************************************************************/
void SwitchDirection(void){
	gSysInfo.lastTimeHalllPosition = gSysInfo.currentHallPosition;
	gSysInfo.currentHallPosition = GetCurrentHallValue();
	//1:A 2:B 3:C
	switch (gSysInfo.currentHallPosition) {
		case 3://B+ --------------->C-
			if(2 == gSysInfo.lastTimeHalllPosition){
				EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
				EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
				closeBH();
				closeAH();
				closeCL();
				openCH();
				openAL();
				openBL();	
			}
			else if(3 == gSysInfo.lastTimeHalllPosition){
				CPositiveToANegtive();
			}
			else{
				DisablePwmOutput();
				gSysInfo.hallErrorCount++;
			}
			break;
		case 1://A+ --------------->C-
			if(3 == gSysInfo.lastTimeHalllPosition){
				EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
				EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
				closeCL();
				closeAH();
				closeBL();
				openBH();
				openAL();
				openCH();
			}
			else if(1 == gSysInfo.lastTimeHalllPosition){
				BPositiveToANegtive();
			}
			else{
				DisablePwmOutput();
				gSysInfo.hallErrorCount++;
			}
			break;
		case 5://A+ --------------->B-
			if(1 == gSysInfo.lastTimeHalllPosition){
				EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
				EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
				closeAH();
				closeBL();
				closeCH();
				openBH();
				openCL();
				openAL();
			}
			else if(5 == gSysInfo.lastTimeHalllPosition){
				BPositiveToCNegtive();
			}
			else{
				DisablePwmOutput();
				gSysInfo.hallErrorCount++;
			}
			break;
		case 4://C+ --------------->B-
			if(5 == gSysInfo.lastTimeHalllPosition){
				EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
				EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
				closeBL();
				closeCH();
				closeAL();
				openAH();
				openCL();
				openBH();
			}
			else if(4 == gSysInfo.lastTimeHalllPosition){
				APositiveToCNegtive();
			}
			else{
				DisablePwmOutput();
				gSysInfo.hallErrorCount++;
			}
			break;
		case 6://C+ --------------->A-
			if(4 == gSysInfo.lastTimeHalllPosition){
				EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
				EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
				closeCH();
				closeBH();
				closeAL();
				openAH();
				openBL();
				openCL();

			}
			else if(6 == gSysInfo.lastTimeHalllPosition){
				APositiveToBNegtive();
			}
			else{
				DisablePwmOutput();
				gSysInfo.hallErrorCount++;		
			}
			break;
		case 2://B+ --------------->A-
			if(6 == gSysInfo.lastTimeHalllPosition){
				EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
				EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
				closeAL();
				closeBH();
				closeCL();
				openCH();
				openBL();
				openAH();
			}
			else if(2 == gSysInfo.lastTimeHalllPosition){
				CPositiveToBNegtive();
			}
			else{
				DisablePwmOutput();
				gSysInfo.hallErrorCount++;
			}
			break;
		default:
			DisablePwmOutput();
			break;
	}
}

void TargetDutyGradualChange(int targetduty){
	static int count = 0;
	++count;
	if(count < DUTYCHANGEINTERVAL){
		return;
	}
	count = 0;
	if(gSysInfo.currentDuty < targetduty){
		gSysInfo.currentDuty = (gSysInfo.currentDuty + gSysInfo.ddtmax) > targetduty ? targetduty : (gSysInfo.currentDuty + gSysInfo.ddtmax);
	}
	else if(gSysInfo.currentDuty > targetduty){
		gSysInfo.currentDuty = (gSysInfo.currentDuty - gSysInfo.ddtmax) < targetduty ? targetduty : (gSysInfo.currentDuty - gSysInfo.ddtmax);
	}
	else{
		//nothing need change
	}
	//need to change the threshold value of the next line
	if (gSysInfo.currentDuty > 1500) {
		gSysInfo.currentDuty = 1500;
	} 
	else if (gSysInfo.currentDuty <= 0) {
		gSysInfo.currentDuty = 0;
	}
	// gSysInfo.duty = gSysInfo.currentDuty;//uncomment when pass test
}
/**************************************************************
 *Name:						PwmIsrThread
 *Function:					PWM interrupt function
 *Input:					none
 *Output:					none
 *Author:					Simon
 *Date:						2018.6.10
 **************************************************************/
void PwmIsrThread(void)
{
	if(gSysState.currentstate == START){
		TargetDutyGradualChange(gSysInfo.openLoopTargetDuty + gSysInfo.closeLooptargetDuty);
		SwitchDirection();
	}
	else{
		DisablePwmOutput();
	}
	ReadAnalogValue();

	IsAnalogValueAbnormal();
}
