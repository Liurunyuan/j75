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

	EPwm1Regs.AQCSFRC.bit.CSFA = 2;
	EPwm1Regs.AQCSFRC.bit.CSFB = 1;
}
inline void DisablePwm2(void){

	EPwm2Regs.AQCSFRC.bit.CSFA = 2;
	EPwm2Regs.AQCSFRC.bit.CSFB = 1;
}
inline void DisablePwm3(void){

	EPwm3Regs.AQCSFRC.bit.CSFA = 2;
	EPwm3Regs.AQCSFRC.bit.CSFB = 1;
}

inline void CPositiveToBNegtive(void) {

	DisablePwm1();

	EPwm3Regs.AQCSFRC.bit.CSFB = 1;
	EPwm3Regs.AQCSFRC.bit.CSFA = 3;

	EPwm2Regs.AQCSFRC.bit.CSFA = 2;
	EPwm2Regs.AQCSFRC.bit.CSFB = 3;

	EPwm3Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;
	EPwm2Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;

}

inline void CPositiveToANegtive(void) {
	DisablePwm2();


	EPwm3Regs.AQCSFRC.bit.CSFB = 1;
	EPwm3Regs.AQCSFRC.bit.CSFA = 3;


	EPwm1Regs.AQCSFRC.bit.CSFA = 2;
	EPwm1Regs.AQCSFRC.bit.CSFB = 3;

	EPwm3Regs.CMPA.half.CMPA =  1250 - gSysInfo.duty;
	EPwm1Regs.CMPA.half.CMPA =  1250 - gSysInfo.duty;

}

inline void BPositiveToANegtive(void) {

	DisablePwm3();


	EPwm2Regs.AQCSFRC.bit.CSFB = 1;
	EPwm2Regs.AQCSFRC.bit.CSFA = 3;


	EPwm1Regs.AQCSFRC.bit.CSFA = 2;
	EPwm1Regs.AQCSFRC.bit.CSFB = 3;

	EPwm2Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;
	EPwm1Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;
}

inline void BPositiveToCNegtive(void) {

	DisablePwm1();


	EPwm2Regs.AQCSFRC.bit.CSFB = 1;
	EPwm2Regs.AQCSFRC.bit.CSFA = 3;


	EPwm3Regs.AQCSFRC.bit.CSFA = 2;
	EPwm3Regs.AQCSFRC.bit.CSFB = 3;

	EPwm2Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;
	EPwm3Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;
}
inline void APositiveToCNegtive(void) {

	DisablePwm2();


	EPwm1Regs.AQCSFRC.bit.CSFB = 1;
	EPwm1Regs.AQCSFRC.bit.CSFA = 3;


	EPwm3Regs.AQCSFRC.bit.CSFA = 2;
	EPwm3Regs.AQCSFRC.bit.CSFB = 3;

	EPwm1Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;
	EPwm3Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;
}
inline void APositiveToBNegtive(void) {

	DisablePwm3();


	EPwm1Regs.AQCSFRC.bit.CSFB = 1;
	EPwm1Regs.AQCSFRC.bit.CSFA = 3;


	EPwm2Regs.AQCSFRC.bit.CSFA = 2;
	EPwm2Regs.AQCSFRC.bit.CSFB = 3;

	EPwm1Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;
	EPwm2Regs.CMPA.half.CMPA = 1250 - gSysInfo.duty;
}

Uint16 GetCurrentHallValue(void){

	Uint16 temp;
	Uint16 a;
	Uint16 b;
	Uint16 c;
//TODO fix later
	a = GpioDataRegs.GPADAT.bit.GPIO24;
	b = GpioDataRegs.GPADAT.bit.GPIO25;
	c = GpioDataRegs.GPADAT.bit.GPIO26;

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
			//本项目电机会进行正转和反转。所以需要判断HALL相邻两个位置是否一样。
			if((3 == gSysInfo.lastTimeHalllPosition )
				|| (2 == gSysInfo.lastTimeHalllPosition)
				|| (1 == gSysInfo.lastTimeHalllPosition)){

				CPositiveToBNegtive();
			}
			break;
		case 1://C+ ---------------> A-
			if((1 == gSysInfo.lastTimeHalllPosition )
				|| (3 == gSysInfo.lastTimeHalllPosition)
				|| (5 == gSysInfo.lastTimeHalllPosition)){
				CPositiveToANegtive();

			}
			break;
		case 5://B+ ---------------> A-
			if((5 == gSysInfo.lastTimeHalllPosition )
				|| (1 == gSysInfo.lastTimeHalllPosition)
				|| (4 == gSysInfo.lastTimeHalllPosition)){

				BPositiveToANegtive();
			}
			break;
		case 4://B+ ---------------> C-
			if((4 == gSysInfo.lastTimeHalllPosition )
				|| (5 == gSysInfo.lastTimeHalllPosition)
				|| (6 == gSysInfo.lastTimeHalllPosition)){

				BPositiveToCNegtive();
			}
			break;
		case 6://A+ ---------------> C-
			if((6 == gSysInfo.lastTimeHalllPosition )
				|| (4 == gSysInfo.lastTimeHalllPosition)
				|| (2 == gSysInfo.lastTimeHalllPosition)){
				APositiveToCNegtive();
			}
			break;
		case 2://A+ ---------------> B-
			if((2 == gSysInfo.lastTimeHalllPosition )
				|| (3 == gSysInfo.lastTimeHalllPosition)
				|| (6 == gSysInfo.lastTimeHalllPosition)){
				APositiveToBNegtive();
			}
			break;
		default:
			DisablePwm1();
			DisablePwm2();
			DisablePwm3();
			break;
	}
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
	targetPid  = PidOutput(gMotorSpeedEcap);

	if(currentpid < targetPid){
		++currentpid;
	}
	else if(currentpid > targetPid){
		--currentpid;
	}
	else{

	}

	if(currentpid > 400){
		currentpid = 400;
	}
	else if(currentpid <= 0){
		currentpid = 0;
	}
	gSysInfo.duty = currentpid;


	SwitchDirection();
}

