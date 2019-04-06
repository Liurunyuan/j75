// TI File $Revision: /main/2 $
// Checkin $Date: December 2, 2004   11:50:58 $
//###########################################################################
//
// FILE:	DSP280x_Gpio.c
//
// TITLE:	DSP280x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x C/C++ Header Files V1.70 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File


#define OUTPUT 	1
#define INPUT 	0
#define GPIO	0


//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example. 
void InitGpio(void)
{
   EALLOW;
   
   // Each GPIO pin can be: 
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs 
   GpioCtrlRegs.GPAMUX1.all = 0x0000;     // GPIO functionality GPIO0-GPIO15
   GpioCtrlRegs.GPAMUX2.all = 0x0000;     // GPIO functionality GPIO16-GPIO31
   GpioCtrlRegs.GPBMUX1.all = 0x0000;     // GPIO functionality GPIO32-GPIO34

   GpioCtrlRegs.GPADIR.all = 0x0000;      // GPIO0-GPIO31 are GP inputs
   GpioCtrlRegs.GPBDIR.all = 0x0000;      // GPIO32-GPIO34 are inputs   
   
   // Each input can have different qualification
   // a) input synchronized to SYSCLKOUT
   // b) input qualified by a sampling window
   // c) input sent asynchronously (valid for peripheral inputs only)
   GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT 
   GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
   GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO34 Synch to SYSCLKOUT 

   // Pull-ups can be enabled or disabled. 
   GpioCtrlRegs.GPAPUD.all = 0x0000;      // Pullup's enabled GPIO0-GPIO31
   GpioCtrlRegs.GPBPUD.all = 0x0000;      // Pullup's enabled GPIO32-GPIO34
   //GpioCtrlRegs.GPAPUD.all = 0xFFFF;    // Pullup's disabled GPIO0-GPIO31
   //GpioCtrlRegs.GPBPUD.all = 0xFFFF;    // Pullup's disabled GPIO32-GPIO34
   EDIS;

}	

void InitOutputPin(void){

	EALLOW;
	/*
	 * GPIO12
	 * Pin index:			1
	 * Name in circuit:		BREAK_K
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO12 = OUTPUT;

	/*
	 * GPIO31
	 * Pin index:			7
	 * Name in circuit:		ENABLE
	 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO31 = OUTPUT;

	/*
	 * GPIO29
	 * Pin index:			4
	 * Name in circuit:		ERR_CLR
	 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO29 = OUTPUT;

	/*
	 * GPIO6
	 * Pin index:			56
	 * Name in circuit:		OUTK
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO6 = OUTPUT;

	/*
	 * GPIO2
	 * Pin index:			45
	 * Name in circuit:		PAMBH
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO2 = OUTPUT;

	/*
	 * GPIO0
	 * Pin index:			47
	 * Name in circuit:		PWMAH
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO0 = OUTPUT;

	/*
	 * GPIO1
	 * Pin index:			44
	 * Name in circuit:		PWMAL
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO1 = OUTPUT;

	/*
	 * GPIO3
	 * Pin index:			48
	 * Name in circuit:		PWMBL
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO3 = OUTPUT;

	/*
	 * GPIO4
	 * Pin index:			51
	 * Name in circuit:		PWMCH
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO4 = OUTPUT;

	/*
	 * GPIO5
	 * Pin index:			53
	 * Name in circuit:		PWMCL
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO5 = OUTPUT;

	/*
	 * GPIO9
	 * Pin index:			61
	 * Name in circuit:		TX_D
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO9 = OUTPUT;

	EDIS;
}
void InitInputPin(void){

	EALLOW;

	/*
	 * GPIO14
	 * Pin index:			8
	 * Name in circuit:		ERR_F_3V3
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO14 = INPUT;

	/*
	 * GPIO33
	 * Pin index:			5
	 * Name in circuit:		H_FAULT1
	 */
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = GPIO;
	GpioCtrlRegs.GPBDIR.bit.GPIO33 = INPUT;

	/*
	 * GPIO30
	 * Pin index:			6
	 * Name in circuit:		H_FAULT2
	 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO30 = INPUT;

	/*
	 * GPIO16
	 * Pin index:			50
	 * Name in circuit:		H_PGOOD
	 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO16 = INPUT;

	/*
	 * GPIO26
	 * Pin index:			99
	 * Name in circuit:		HA_3_3V
	 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO26 = INPUT;

	/*
	 * GPIO15
	 * Pin index:			9
	 * Name in circuit:		HARD_ERR_3V3
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO15 = INPUT;

	/*
	 * GPIO24
	 * Pin index:			83
	 * Name in circuit:		HB_3_3V
	 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO24 = INPUT;

	/*
	 * GPIO25
	 * Pin index:			91
	 * Name in circuit:		HC_3_3V
	 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO25 = INPUT;

	/*
	 * GPIO11
	 * Pin index:			70
	 * Name in circuit:		HD_3_3V
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO11 = INPUT;

	/*
	 * GPIO28
	 * Pin index:			92
	 * Name in circuit:		INA_DSP
	 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO28 = INPUT;

	/*
	 * GPIO13
	 * Pin index:			95
	 * Name in circuit:		INB_DSP
	 */
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO13 = INPUT;

	/*
	 * GPIO19
	 * Pin index:			57
	 * Name in circuit:		RX_D
	 */
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = GPIO;
	GpioCtrlRegs.GPADIR.bit.GPIO19 = INPUT;

	/*
	 * GPIO32
	 * Pin index:			100
	 * Name in circuit:		X_5V_PGOOD
	 */
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = GPIO;
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = INPUT;
	EDIS;

}

void InitGpioForJ75(void){
	InitOutputPin();
	InitInputPin();
}
	
//===========================================================================
// End of file.
//===========================================================================
