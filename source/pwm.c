#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "pwm.h"
#include "adc.h"
#include "pid.h"
#include "ecap.h"


int currentpid = 0;
int targetPid = 0;

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
}

inline void CPositiveToBNegtive(void) {

	DisablePwm1();

	// EPwm3Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm3Regs.AQCSFRC.bit.CSFA = 3;
	// EPwm3Regs.AQCSFRC.bit.CSFB = 2;
	// EPwm3Regs.AQCSFRC.all = 0x000b;

	// EPwm2Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	// EPwm2Regs.AQCSFRC.bit.CSFB = 3;
	// EPwm2Regs.AQCSFRC.all = 0x000d;

	EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm3Regs.AQCSFRC.bit.CSFA = 3;
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;

	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	EPwm2Regs.AQCSFRC.bit.CSFB = 3;
}

inline void CPositiveToANegtive(void) {
	DisablePwm2();

	// EPwm3Regs.CMPA.half.CMPA =  gSysInfo.duty;
	// EPwm3Regs.AQCSFRC.bit.CSFA = 3;
	// EPwm3Regs.AQCSFRC.bit.CSFB = 2;
	// EPwm3Regs.AQCSFRC.all = 0x000b;

	// EPwm1Regs.CMPA.half.CMPA =  gSysInfo.duty;
	// EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	// EPwm1Regs.AQCSFRC.bit.CSFB = 3;
	// EPwm1Regs.AQCSFRC.all = 0x000d;

	EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm3Regs.AQCSFRC.bit.CSFA = 3;
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;

	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	EPwm1Regs.AQCSFRC.bit.CSFB = 3;
}

inline void BPositiveToANegtive(void) {

	DisablePwm3();

	// EPwm2Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm2Regs.AQCSFRC.bit.CSFA = 3;
	// EPwm2Regs.AQCSFRC.bit.CSFB = 2;
	// EPwm2Regs.AQCSFRC.all = 0x000b;

	// EPwm1Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	// EPwm1Regs.AQCSFRC.bit.CSFB = 3;
	// EPwm1Regs.AQCSFRC.all = 0x000d;
	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm2Regs.AQCSFRC.bit.CSFA = 3;
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;

	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;
	EPwm1Regs.AQCSFRC.bit.CSFB = 3;
}

inline void BPositiveToCNegtive(void) {

	DisablePwm1();

	// EPwm2Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm2Regs.AQCSFRC.bit.CSFA = 3;
	// EPwm2Regs.AQCSFRC.bit.CSFB = 2;
	// EPwm2Regs.AQCSFRC.all = 0x000b;

	// EPwm3Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	// EPwm3Regs.AQCSFRC.bit.CSFB = 3;
	// EPwm3Regs.AQCSFRC.all = 0x000d;
	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm2Regs.AQCSFRC.bit.CSFA = 3;
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;

	EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm3Regs.AQCSFRC.bit.CSFB = 3;
}
inline void APositiveToCNegtive(void) {

	DisablePwm2();

	// EPwm1Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm1Regs.AQCSFRC.bit.CSFA = 3;
	// EPwm1Regs.AQCSFRC.bit.CSFB = 2;
	// EPwm1Regs.AQCSFRC.all = 0x000b;

	// EPwm3Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	// EPwm3Regs.AQCSFRC.bit.CSFB = 3;
	// EPwm3Regs.AQCSFRC.all = 0x000d;
	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm1Regs.AQCSFRC.bit.CSFA = 3;
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;

	EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;
	EPwm3Regs.AQCSFRC.bit.CSFB = 3;
}
inline void APositiveToBNegtive(void) {

	DisablePwm3();

	// EPwm1Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm1Regs.AQCSFRC.bit.CSFA = 3;
	// EPwm1Regs.AQCSFRC.bit.CSFB = 2;
	// EPwm1Regs.AQCSFRC.all = 0x000b;

	// EPwm2Regs.CMPA.half.CMPA = gSysInfo.duty;
	// EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	// EPwm2Regs.AQCSFRC.bit.CSFB = 3;
	// EPwm2Regs.AQCSFRC.all = 0x000d;
	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm1Regs.AQCSFRC.bit.CSFA = 3;
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;

	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD - gSysInfo.duty;
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;
	EPwm2Regs.AQCSFRC.bit.CSFB = 3;
}

Uint16 GetCurrentHallValue(void){

	Uint16 temp;
	Uint16 a = 0;
	Uint16 b = 0;
	Uint16 c = 0;
//TODO fix later
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
	//3:A 2:B 1:C
	switch (gSysInfo.currentHallPosition) {
		case 3://C+ ---------------> B-
			
			if((3 == gSysInfo.lastTimeHalllPosition )
				|| (2 == gSysInfo.lastTimeHalllPosition)
				|| (1 == gSysInfo.lastTimeHalllPosition)){
				APositiveToBNegtive();

			}
			break;
		case 1://C+ ---------------> A-
			if((1 == gSysInfo.lastTimeHalllPosition )
				|| (3 == gSysInfo.lastTimeHalllPosition)
				|| (5 == gSysInfo.lastTimeHalllPosition)){
				APositiveToCNegtive();

			}
			break;
		case 5://B+ ---------------> A-
			if((5 == gSysInfo.lastTimeHalllPosition )
				|| (1 == gSysInfo.lastTimeHalllPosition)
				|| (4 == gSysInfo.lastTimeHalllPosition)){
				BPositiveToCNegtive();

			}
			break;
		case 4://B+ ---------------> C-
			if((4 == gSysInfo.lastTimeHalllPosition )
				|| (5 == gSysInfo.lastTimeHalllPosition)
				|| (6 == gSysInfo.lastTimeHalllPosition)){
				BPositiveToANegtive();

			}
			break;
		case 6://A+ ---------------> C-
			if((6 == gSysInfo.lastTimeHalllPosition )
				|| (4 == gSysInfo.lastTimeHalllPosition)
				|| (2 == gSysInfo.lastTimeHalllPosition)){
				CPositiveToANegtive();
			}
			break;
		case 2://A+ ---------------> B-
			if((2 == gSysInfo.lastTimeHalllPosition )
				|| (3 == gSysInfo.lastTimeHalllPosition)
				|| (6 == gSysInfo.lastTimeHalllPosition)){
				CPositiveToBNegtive();
			}
			break;
		default:
			DisablePwm1();
			DisablePwm2();
			DisablePwm3();
			break;
	}
}

void ThresholdProtectForDuty() {
	if (currentpid < targetPid) {
		++currentpid;
	} else if (currentpid > targetPid) {
		--currentpid;
	} else {
	}

	if (currentpid > 400) {
		currentpid = 400;
	} else if (currentpid <= 0) {
		currentpid = 0;
	}

	gSysInfo.duty = currentpid;
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
	ReadAnalogValue();

	IsAnalogValueAbnormal();

	if(gSysState.currentstate == START){

		// targetPid  = PidOutput(gMotorSpeedEcap);

		// ThresholdProtectForDuty();

		SwitchDirection();
	}
	else{
		DisablePwmOutput();
	}
}

