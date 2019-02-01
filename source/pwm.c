#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "pwm.h"

int test2 = 0;

void DisablePwm1(void){
	EALLOW;
	EPwm1Regs.TZFRC.bit.OST = 1;
	EDIS;
}
void DisablePwm2(void){
	EALLOW;
	EPwm2Regs.TZFRC.bit.OST = 1;
	EDIS;
}
void DisablePwm3(void){
	EALLOW;
	EPwm3Regs.TZFRC.bit.OST = 1;
	EDIS;
}
void EnablePwm1(void){
	EALLOW;
	EPwm1Regs.TZCLR.all = 0x003f;
	EDIS;
}
void EnablePwm2(void){
	EALLOW;
	EPwm2Regs.TZCLR.all = 0x003f;
	EDIS;
}
void EnablePwm3(void){
	EALLOW;
	EPwm3Regs.TZCLR.all = 0x003f;
	EDIS;
}

inline void CPositiveToBNegtive(void) {

	DisablePwm1();
	EPwm3Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm2Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD - gSysInfo.duty;
	EnablePwm2();
	EnablePwm3();
}

inline void CPositiveToANegtive(void) {
	DisablePwm2();
	EPwm3Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm1Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD - gSysInfo.duty;
	EnablePwm1();
	EnablePwm3();
}

inline void BPositiveToANegtive(void) {

	DisablePwm3();
	EPwm2Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm1Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD - gSysInfo.duty;
	EnablePwm2();
	EnablePwm1();
}

inline void BPositiveToCNegtive(void) {

	DisablePwm1();
	EPwm2Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm3Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD - gSysInfo.duty;
	EnablePwm2();
	EnablePwm3();
}
inline void APositiveToCNegtive(void) {

	DisablePwm2();
	EPwm1Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm3Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD - gSysInfo.duty;
	EnablePwm1();
	EnablePwm3();
}
inline void APositiveToBNegtive(void) {

	DisablePwm3();
	EPwm1Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD + gSysInfo.duty;
	EPwm2Regs.CMPA.half.CMPA = EPWM2_TIMER_HALF_TBPRD - gSysInfo.duty;
	EnablePwm1();
	EnablePwm2();
}

Uint16 GetCurrentHallValue(void){

	Uint16 temp;
	Uint16 a;
	Uint16 b;
	Uint16 c;
//TODO fix later
	a = GpioDataRegs.GPADAT.bit.GPIO27;
	b = GpioDataRegs.GPADAT.bit.GPIO26;
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
			//本项目电机会进行正转和反转。所以需要判断HALL相邻两个位置是否一样。
			if((3 == gSysInfo.lastTimeHalllPosition )
				|| (2 == gSysInfo.lastTimeHalllPosition)
				|| (1 == gSysInfo.lastTimeHalllPosition)){

				CPositiveToANegtive();
			}
			break;
		case 1://C+ ---------------> A-
			if((1 == gSysInfo.lastTimeHalllPosition )
				|| (3 == gSysInfo.lastTimeHalllPosition)
				|| (5 == gSysInfo.lastTimeHalllPosition)){

				CPositiveToBNegtive();
			}
			break;
		case 5://B+ ---------------> A-
			if((5 == gSysInfo.lastTimeHalllPosition )
				|| (1 == gSysInfo.lastTimeHalllPosition)
				|| (4 == gSysInfo.lastTimeHalllPosition)){

				APositiveToBNegtive();
			}
			break;
		case 4://B+ ---------------> C-
			if((4 == gSysInfo.lastTimeHalllPosition )
				|| (5 == gSysInfo.lastTimeHalllPosition)
				|| (6 == gSysInfo.lastTimeHalllPosition)){

				APositiveToCNegtive();
			}
			break;
		case 6://A+ ---------------> C-
			if((6 == gSysInfo.lastTimeHalllPosition )
				|| (4 == gSysInfo.lastTimeHalllPosition)
				|| (2 == gSysInfo.lastTimeHalllPosition)){

				BPositiveToCNegtive();
			}
			break;
		case 2://A+ ---------------> B-
			if((2 == gSysInfo.lastTimeHalllPosition )
				|| (3 == gSysInfo.lastTimeHalllPosition)
				|| (6 == gSysInfo.lastTimeHalllPosition)){

				BPositiveToANegtive();
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
//	SwitchDirection();
	++test2;
}

