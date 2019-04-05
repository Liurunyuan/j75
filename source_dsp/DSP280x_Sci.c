// TI File $Revision: /main/3 $
// Checkin $Date: August 2, 2006   13:51:10 $
//###########################################################################
//
// FILE:	DSP280x_Sci.c
//
// TITLE:	DSP280x SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x C/C++ Header Files V1.70 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

//---------------------------------------------------------------------------
// InitSci: 
//---------------------------------------------------------------------------
// This function initializes the SCI(s) to a known state.
//
void InitSci(void)
{
	// Initialize SCI-A:

	//tbd...
 	

	// Initialize SCI-B:

	//tbd...
}	

//---------------------------------------------------------------------------
// Example: InitSciGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SCI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
// Caution: 
// Only one GPIO pin should be enabled for SCITXDA/B operation.
// Only one GPIO pin shoudl be enabled for SCIRXDA/B operation. 
// Comment out other unwanted lines.

void InitSciGpio()
{
   InitSciaGpio();
#if DSP28_SCIB   
   InitScibGpio();
#endif // if DSP28_SCIB  
}

void InitSciaGpio()
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.  
// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.  
// This will select asynch (no qualification) for the selected pins.

	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)

/* Configure SCI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation
	
    EDIS;
}

#if DSP28_SCIB 
void InitScibGpio()
{
  EALLOW;
	
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.  
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;     // Enable pull-up for GPIO9  (SCITXDB)
  GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up for GPIO14 (SCITXDB)
//	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;	   // Enable pull-up for GPIO18 (SCITXDB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;    // Enable pull-up for GPIO22 (SCITXDB)

	
//  GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up for GPIO11 (SCIRXDB)
  GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up for GPIO15 (SCIRXDB)
//    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;	   // Enable pull-up for GPIO19 (SCIRXDB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;    // Enable pull-up for GPIO23 (SCIRXDB)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  // Asynch input GPIO11 (SCIRXDB)
  GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (SCIRXDB)
//	GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDB)
//  GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO23 (SCIRXDB)

/* Configure SCI-B pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;    // Configure GPIO9 for SCITXDB operation
  GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2;   // Configure GPIO14 for SCITXDB operation
//	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;   // Configure GPIO18 for SCITXDB operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;   // Configure GPIO22 for SCITXDB operation
	
//  GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;   // Configure GPIO11 for SCIRXDB operation
  GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;   // Configure GPIO15 for SCIRXDB operation
//    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   // Configure GPIO19 for SCIRXDB operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;   // Configure GPIO23 for SCIRXDB operation
	
  EDIS;
}
#endif // if DSP28_SCIB 
void scia_loopback_init(void)
{
 	SciaRegs.SCICCR.all 			= 0x0007;   // 1 stop bit,  No loopback
	SciaRegs.SCICTL1.all 			= 0x0003;  // enable TX, RX, internal SCICLK,
	SciaRegs.SCICTL2.all 			= 0x0003;
	SciaRegs.SCICTL2.bit.TXINTENA 	= 1;
	SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
	SciaRegs.SCIHBAUD    			= 0x01;//0x00;-------------------------0x01
  SciaRegs.SCILBAUD    			= 0x45;//0x1f:115200-------------------0x45:9600 100M
	SciaRegs.SCICCR.bit.LOOPBKENA 	= 0; // enable loop back
	SciaRegs.SCICTL1.all 			= 0x0023;     // Relinquish SCI from Reset
}
void scib_loopback_init(void)
{
 	ScibRegs.SCICCR.all 			= 0x0007;   // 1 stop bit,  No loopback
	ScibRegs.SCICTL1.all 			= 0x0003;  // enable TX, RX, internal SCICLK,
	ScibRegs.SCICTL2.all 			= 0x0003;
	ScibRegs.SCICTL2.bit.TXINTENA 	= 1;
	ScibRegs.SCICTL2.bit.RXBKINTENA = 1;
  ScibRegs.SCIHBAUD    			= 0x01;//0x00;-------------------------0x01
  ScibRegs.SCILBAUD    			= 0x45;//0x1f:115200-------------------0x45:9600 100M
	ScibRegs.SCICCR.bit.LOOPBKENA 	= 0; // enable loop back
	ScibRegs.SCICTL1.all 			= 0x0023;     // Relinquish SCI from Reset
}
void scia_fifo_init(void)
{
  SciaRegs.SCIFFTX.bit.TXFIFOXRESET	= 0;
  SciaRegs.SCIFFRX.bit.RXFIFORESET	= 0;
  SciaRegs.SCIFFTX.all				= 0xE028;
  SciaRegs.SCIFFTX.bit.TXFFIENA		= 0;

  SciaRegs.SCIFFTX.bit.TXFFINTCLR		= 1;
  SciaRegs.SCIFFRX.all				= 0x2028;

  SciaRegs.SCIFFRX.bit.RXFFIENA		= 1;
  SciaRegs.SCIFFCT.all				= 0x0;
}
void scib_fifo_init(void)
{
  ScibRegs.SCIFFTX.bit.TXFIFOXRESET	= 0;
  ScibRegs.SCIFFRX.bit.RXFIFORESET	= 0;
  ScibRegs.SCIFFTX.all				= 0xE028;
  ScibRegs.SCIFFTX.bit.TXFFIENA		= 0;

  ScibRegs.SCIFFTX.bit.TXFFINTCLR		= 1;
  ScibRegs.SCIFFRX.all				= 0x2028;

  ScibRegs.SCIFFRX.bit.RXFFIENA		= 1;
  ScibRegs.SCIFFCT.all				= 0x0;
}

void InitSciForJ75(void){
	InitSciGpio();
	scia_loopback_init();
	scia_fifo_init();
	scib_loopback_init();
	scib_fifo_init();
}
	
//===========================================================================
// End of file.
//===========================================================================
