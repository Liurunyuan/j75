// TI File $Revision: /main/4 $
// Checkin $Date: August 2, 2006   13:51:13 $
//###########################################################################
//
// FILE:   DSP280x_EPwm.c
//
// TITLE:  DSP280x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x C/C++ Header Files V1.70 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP280x_Device.h"   // DSP280x Headerfile Include File
#include "DSP280x_Examples.h" // DSP280x Examples Include File
#include "global.h"

//---------------------------------------------------------------------------
// InitEPwm:
//---------------------------------------------------------------------------
// This function initializes the ePWM(s) to a known state.
//
void InitEPwm(void)
{
	// Initialize ePWM1/2/3/4/5/6

	//tbd...
}

//---------------------------------------------------------------------------
// Example: InitEPwmGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitEPwmGpio(void)
{
	/*
	For J75:
			GPIO0:	PWMAH
			GPIO1:	PWMAL

			GPIO2:	PWMBH
			GPIO3:	PWMBL

			GPIO4:	PWMCH
			GPIO5:	PWMCL
	*/
	InitEPwm1Gpio();
	InitEPwm2Gpio();
	InitEPwm3Gpio();
#if DSP28_EPWM4
	InitEPwm4Gpio();
#endif // endif DSP28_EPWM4
#if DSP28_EPWM5
	InitEPwm5Gpio();
#endif // endif DSP28_EPWM5
#if DSP28_EPWM6
	InitEPwm6Gpio();
#endif // endif DSP28_EPWM6
}

void InitEPwm1Gpio(void)
{
	EALLOW;

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0; // Enable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0; // Enable pull-up on GPIO1 (EPWM1B)

	/* Configure ePWM-1 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1; // Configure GPIO0 as EPWM1A
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1; // Configure GPIO1 as EPWM1B

	EDIS;
}

void InitEPwm2Gpio(void)
{
	EALLOW;

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0; // Enable pull-up on GPIO2 (EPWM2A)
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0; // Enable pull-up on GPIO3 (EPWM3B)

	/* Configure ePWM-2 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be ePWM2 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1; // Configure GPIO2 as EPWM2A
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1; // Configure GPIO3 as EPWM2B

	EDIS;
}

void InitEPwm3Gpio(void)
{
	EALLOW;

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0; // Enable pull-up on GPIO4 (EPWM3A)
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0; // Enable pull-up on GPIO5 (EPWM3B)

	/* Configure ePWM-3 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be ePWM3 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1; // Configure GPIO4 as EPWM3A
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1; // Configure GPIO5 as EPWM3B

	EDIS;
}

#if DSP28_EPWM4
void InitEPwm4Gpio(void)
{
	EALLOW;
	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0; // Enable pull-up on GPIO6 (EPWM4A)
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0; // Enable pull-up on GPIO7 (EPWM4B)

	/* Configure ePWM-4 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be ePWM4 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1; // Configure GPIO6 as EPWM4A
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1; // Configure GPIO7 as EPWM4B

	EDIS;
}
#endif // endif DSP28_EPWM4

#if DSP28_EPWM5
void InitEPwm5Gpio(void)
{
	EALLOW;
	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0; // Enable pull-up on GPIO8 (EPWM5A)
	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0; // Enable pull-up on GPIO9 (EPWM5B)

	/* Configure ePWM-5 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be ePWM5 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1; // Configure GPIO8 as EPWM5A
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1; // Configure GPIO9 as EPWM5B

	EDIS;
}
#endif // endif DSP28_EPWM5

#if DSP28_EPWM6
void InitEPwm6Gpio(void)
{
	EALLOW;

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0; // Enable pull-up on GPIO10 (EPWM6A)
	GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0; // Enable pull-up on GPIO11 (EPWM6B)

	/* Configure ePWM-6 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be ePWM6 functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1; // Configure GPIO10 as EPWM6A
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1; // Configure GPIO11 as EPWM6B

	EDIS;
}
#endif // endif DSP28_EPWM6

//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM Synch pins
//

void InitEPwmSyncGpio(void)
{

	EALLOW;

	/* Configure EPWMSYNCI  */

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0; // Enable pull-up on GPIO6 (EPWMSYNCI)
									   // GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up on GPIO32 (EPWMSYNCI)

	/* Set qualification for selected pins to asynch only */
	// This will select synch to SYSCLKOUT for the selected pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0; // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
										 // GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)

	/* Configure EPwmSync pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2; // Enable pull-up on GPIO6 (EPWMSYNCI)
										// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Enable pull-up on GPIO32 (EPWMSYNCI)

	/* Configure EPWMSYNC0  */

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.

	// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNC0)
	GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0; // Enable pull-up on GPIO33 (EPWMSYNC0)

	// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Enable pull-up on GPIO6 (EPWMSYNC0)
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2; // Enable pull-up on GPIO33 (EPWMSYNC0)
}

//---------------------------------------------------------------------------
// Example: InitTzGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitTzGpio(void)
{
	EALLOW;

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0; // Enable pull-up on GPIO12 (TZ1)
	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0; // Enable pull-up on GPIO13 (TZ2)
	GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0; // Enable pull-up on GPIO14 (TZ3)
	GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0; // Enable pull-up on GPIO15 (TZ4)

	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0; // Enable pull-up on GPIO16 (TZ5)
										// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ5)

	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0; // Enable pull-up on GPIO17 (TZ6)
										// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ6)

	/* Set qualification for selected pins to asynch only */
	// Inputs are synchronized to SYSCLKOUT by default.
	// This will select asynch (no qualification) for the selected pins.
	// Comment out other unwanted lines.

	GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // Asynch input GPIO12 (TZ1)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // Asynch input GPIO13 (TZ2)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; // Asynch input GPIO14 (TZ3)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3; // Asynch input GPIO15 (TZ4)

	GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (TZ5)
										  // GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ5)

	GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (TZ6)
										  // GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ6)

	/* Configure TZ pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be TZ functional pins.
	// Comment out other unwanted lines.
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1; // Configure GPIO12 as TZ1
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1; // Configure GPIO13 as TZ2
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1; // Configure GPIO14 as TZ3
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1; // Configure GPIO15 as TZ4

	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3; // Configure GPIO16 as TZ5
										 // GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ5

	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3; // Configure GPIO17 as TZ6
										 // GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ6

	EDIS;
}
void InitEPwm1()
{
	// EALLOW;
	// EPwm1Regs.TZCTL.bit.TZA = 1;
	// EPwm1Regs.TZCTL.bit.TZB = 1;
	// EDIS;

	EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD;
	EPwm1Regs.TBPHS.all = 0x0000;
	EPwm1Regs.TBCTR = 0x0000;
	EPwm1Regs.TBCTL.bit.PHSEN = 0;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm1Regs.TBCTL.bit.CLKDIV = 0;
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;
	EPwm1Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;
	EPwm1Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
	EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;
	EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.CBD = AQ_NO_ACTION;
	EPwm1Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;
	EPwm1Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;
	EPwm1Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;
	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD;
	EPwm1Regs.AQSFRC.bit.RLDCSF = 3;
	EPwm1Regs.DBCTL.bit.IN_MODE = 2;
	EPwm1Regs.DBCTL.bit.POLSEL = 2;
	EPwm1Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm1Regs.DBRED = 0;
	EPwm1Regs.DBFED = 0;
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
	EPwm1Regs.ETSEL.bit.INTEN = 0;
	EPwm1Regs.ETSEL.bit.SOCAEN = 1;
	EPwm1Regs.ETSEL.bit.SOCASEL = 1;
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;
}
void InitEPwm2()
{
	EALLOW;
	//	EPwm2Regs.TZSEL.bit.OSHT2=1;
	//	EPwm2Regs.TZSEL.bit.OSHT3=1;
	// EPwm2Regs.TZCTL.bit.TZA = 1;
	// EPwm2Regs.TZCTL.bit.TZB = 1;
	//	EPwm2Regs.TZEINT.bit.OST=1;
	EDIS;

	EPwm2Regs.TBPRD = EPWM1_TIMER_TBPRD;
	EPwm2Regs.TBPHS.all = 0x0000;
	EPwm2Regs.TBCTR = 0x0000;
	EPwm2Regs.TBCTL.bit.PHSEN = 0;
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm2Regs.TBCTL.bit.CLKDIV = 0;
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;
	EPwm2Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;
	EPwm2Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
	EPwm2Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
	EPwm2Regs.AQCTLB.bit.CAD = AQ_SET;
	EPwm2Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm2Regs.AQCTLB.bit.CBD = AQ_NO_ACTION;
	EPwm2Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;
	EPwm2Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;
	EPwm2Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;
	EPwm2Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD;
	EPwm2Regs.AQSFRC.bit.RLDCSF = 3;
	EPwm2Regs.DBCTL.bit.IN_MODE = 2;
	EPwm2Regs.DBCTL.bit.POLSEL = 2;
	EPwm2Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm2Regs.DBRED = 0;
	EPwm2Regs.DBFED = 0;
	EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;
	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	EPwm2Regs.ETSEL.bit.INTEN = 0;
}

void InitEPwm3()
{
	//	EALLOW;
	//	EPwm3Regs.TZSEL.bit.OSHT2=1;
	//	EPwm3Regs.TZSEL.bit.OSHT3=1;
	//	EPwm3Regs.TZCTL.bit.TZA=1;
	//	EPwm3Regs.TZCTL.bit.TZB=1;
	//	EPwm3Regs.TZEINT.bit.OST=1;
	//	EDIS;
	EPwm3Regs.TBPRD = EPWM1_TIMER_TBPRD;
	EPwm3Regs.TBPHS.all = 0x0000;
	EPwm3Regs.TBCTR = 0x0000;
	EPwm3Regs.TBCTL.bit.PHSEN = 0;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0;
	EPwm3Regs.TBCTL.bit.CLKDIV = 0;
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm3Regs.AQCTLA.bit.CBD = AQ_NO_ACTION;
	EPwm3Regs.AQCTLA.bit.CBU = AQ_NO_ACTION;
	EPwm3Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
	EPwm3Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
	EPwm3Regs.AQCTLB.bit.CAD = AQ_SET;
	EPwm3Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm3Regs.AQCTLB.bit.CBD = AQ_NO_ACTION;
	EPwm3Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;
	EPwm3Regs.AQCTLB.bit.PRD = AQ_NO_ACTION;
	EPwm3Regs.AQCTLB.bit.ZRO = AQ_NO_ACTION;
	EPwm3Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD;  
	EPwm3Regs.AQSFRC.bit.RLDCSF = 3;
	EPwm3Regs.DBCTL.bit.IN_MODE = 2;
	EPwm3Regs.DBCTL.bit.POLSEL = 2;
	EPwm3Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm3Regs.DBRED = 0;
	EPwm3Regs.DBFED = 0;
	EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;
	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	EPwm3Regs.ETSEL.bit.INTEN = 0;
}
void InitEpwmForJ75(void)
{
	InitEPwm1Gpio();
	InitEPwm2Gpio();
	InitEPwm3Gpio();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	InitEPwm1();
	InitEPwm2();
	InitEPwm3();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
