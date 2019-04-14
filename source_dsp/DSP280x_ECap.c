// TI File $Revision: /main/4 $
// Checkin $Date: August 2, 2006   13:51:14 $
//###########################################################################
//
// FILE:   DSP280x_ECap.c
//
// TITLE:  DSP280x eCAP Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x C/C++ Header Files V1.70 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

//---------------------------------------------------------------------------
// InitECap: 
//---------------------------------------------------------------------------
// This function initializes the eCAP(s) to a known state.
//
void InitECap(void)
{
   // Initialize eCAP1/2/3

   //tbd...
 
}

//---------------------------------------------------------------------------
// Example: InitECapGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ECAP pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
// Caution: 
// For each eCAP peripheral
// Only one GPIO pin should be enabled for ECAP operation. 
// Comment out other unwanted lines.

void InitECapGpio()
{
	//j75 use ecap1 for HB, ecap2 for HC, ecap3 for HA, ecap4 for HD
   InitECap1Gpio();
#if (DSP28_ECAP2)
   InitECap2Gpio();
#endif // endif DSP28_ECAP2
#if (DSP28_ECAP3)    
   InitECap3Gpio();
#endif // endif DSP28_ECAP3
#if (DSP28_ECAP4)
   InitECap4Gpio();
#endif // endif DSP28_ECAP4
}

void InitECap1Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;      // Enable pull-up on GPIO5 (CAP1)
   GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;     // Enable pull-up on GPIO24 (CAP1)

// Inputs are synchronized to SYSCLKOUT by default.  
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 0;    // Synch to SYSCLKOUT GPIO5 (CAP1)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;   // Synch to SYSCLKOUT GPIO24 (CAP1)

/* Configure eCAP-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP1 functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;     // Configure GPIO5 as CAP1
   GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;    // Configure GPIO24 as CAP1
    
    EDIS;
}

#if DSP28_ECAP2
void InitECap2Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;     // Enable pull-up on GPIO7 (CAP2)
 GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;    // Enable pull-up on GPIO25 (CAP2)

// Inputs are synchronized to SYSCLKOUT by default.  
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;    // Synch to SYSCLKOUT GPIO7 (CAP2)
 GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;   // Synch to SYSCLKOUT GPIO25 (CAP2)

/* Configure eCAP-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP2 functional pins.
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 3;    // Configure GPIO7 as CAP2
 GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;   // Configure GPIO25 as CAP2
    
    EDIS;
}
#endif // endif DSP28_ECAP2

#if DSP28_ECAP3 
void InitECap3Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;      // Enable pull-up on GPIO9 (CAP3)
 GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;     // Enable pull-up on GPIO26 (CAP3)

// Inputs are synchronized to SYSCLKOUT by default.  
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 0;    // Synch to SYSCLKOUT GPIO9 (CAP3)
 GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;   // Synch to SYSCLKOUT GPIO26 (CAP3)

/* Configure eCAP-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP3 functional pins.
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 3;     // Configure GPIO9 as CAP3
 GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    // Configure GPIO26 as CAP3
    
    EDIS;
}
#endif // endif DSP28_ECAP3   


#if DSP28_ECAP4 
void InitECap4Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;   // Enable pull-up on GPIO11 (CAP4)
// GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   // Enable pull-up on GPIO27 (CAP4)

// Inputs are synchronized to SYSCLKOUT by default.  
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 0; // Synch to SYSCLKOUT GPIO11 (CAP4)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0; // Synch to SYSCLKOUT GPIO27 (CAP4)

/* Configure eCAP-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP4 functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;  // Configure GPIO11 as CAP4
// GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;  // Configure GPIO27 as CAP4
    
    EDIS;
}   
#endif // endif DSP28_ECAP4
void ECap1Config(void){
	 EALLOW;
	 SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;
	 EDIS;
	 /* Initialize eCAP1/2/3 */
	 ECap1Regs.ECEINT.all = 0x0000;             /* Disable all capture interrupts */
	 ECap1Regs.ECCLR.all = 0xFFFF;              /* Clear all CAP interrupt flags  */
	 ECap1Regs.ECCTL1.bit.CAPLDEN = 0;          /* disable CAP1-CAP4 register loads*/
	 ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;        /* Make sure the counter is stopped*/

	 /* Configure peripheral registers*/
	 ECap1Regs.ECCTL2.bit.CONT_ONESHT = 0;

	 ECap1Regs.ECCTL1.bit.CAP1POL = 0;
	 ECap1Regs.ECCTL1.bit.CAP2POL = 0;
	 ECap1Regs.ECCTL1.bit.CAP3POL = 0;
	 ECap1Regs.ECCTL1.bit.CAP4POL = 0;

	 ECap1Regs.ECCTL1.bit.CTRRST1 = 0;
	 ECap1Regs.ECCTL1.bit.CTRRST2 = 0;
	 ECap1Regs.ECCTL1.bit.CTRRST3 = 0;
	 ECap1Regs.ECCTL1.bit.CTRRST4 = 1;

	 ECap1Regs.ECCTL2.bit.SYNCI_EN = 0;
	 ECap1Regs.ECCTL2.bit.SYNCO_SEL = 3;
	 ECap1Regs.ECCTL1.bit.PRESCALE =0;
	 ECap1Regs.ECCLR.all = 0xffff;
	 ECap1Regs.ECCTL2.bit.CAP_APWM = 0;

	 ECap1Regs.ECEINT.bit.CEVT1 = 1;            // 2 events = interrupt
	 ECap1Regs.ECEINT.bit.CEVT2 = 1;
	 ECap1Regs.ECEINT.bit.CEVT3 = 1;
	 ECap1Regs.ECEINT.bit.CEVT4 = 1;
	 ECap1Regs.ECEINT.bit.CTR_EQ_CMP = 0;
	 ECap1Regs.ECEINT.bit.CTR_EQ_PRD = 0;
	 ECap1Regs.ECEINT.bit.CTROVF =1;

	 ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	 ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;        /* Start Counter*/
}

void ECap2Config(void){
	 EALLOW;
	 SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;
	 EDIS;
	 /* Initialize eCAP1/2/3 */
	 ECap2Regs.ECEINT.all = 0x0000;             /* Disable all capture interrupts */
	 ECap2Regs.ECCLR.all = 0xFFFF;              /* Clear all CAP interrupt flags  */
	 ECap2Regs.ECCTL1.bit.CAPLDEN = 0;          /* disable CAP1-CAP4 register loads*/
	 ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0;        /* Make sure the counter is stopped*/

	 /* Configure peripheral registers*/
	 ECap2Regs.ECCTL2.bit.CONT_ONESHT = 0;

	 ECap2Regs.ECCTL1.bit.CAP1POL = 0;
	 ECap2Regs.ECCTL1.bit.CAP2POL = 0;
	 ECap2Regs.ECCTL1.bit.CAP3POL = 0;
	 ECap2Regs.ECCTL1.bit.CAP4POL = 0;


	 ECap2Regs.ECCTL1.bit.CTRRST1 = 0;
	 ECap2Regs.ECCTL1.bit.CTRRST2 = 0;
	 ECap2Regs.ECCTL1.bit.CTRRST3 = 0;
	 ECap2Regs.ECCTL1.bit.CTRRST4 = 1;

	 ECap2Regs.ECCTL2.bit.SYNCI_EN = 0;
	 ECap2Regs.ECCTL2.bit.SYNCO_SEL = 3;
	 ECap2Regs.ECCTL1.bit.PRESCALE =0;
	 ECap2Regs.ECCLR.all = 0xffff;
	 ECap2Regs.ECCTL2.bit.CAP_APWM = 0;

	 ECap2Regs.ECEINT.bit.CEVT1 = 1;            // 2 events = interrupt
	 ECap2Regs.ECEINT.bit.CEVT2 = 1;
	 ECap2Regs.ECEINT.bit.CEVT3 = 1;
	 ECap2Regs.ECEINT.bit.CEVT4 = 1;
	 ECap2Regs.ECEINT.bit.CTR_EQ_CMP = 0;
	 ECap2Regs.ECEINT.bit.CTR_EQ_PRD = 0;
	 ECap2Regs.ECEINT.bit.CTROVF =1;

	 ECap2Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	 ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;        /* Start Counter*/
}

void ECap3Config(void){
	 EALLOW;
	 SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;
	 EDIS;
	 /* Initialize eCAP1/2/3 */
	 ECap3Regs.ECEINT.all = 0x0000;             /* Disable all capture interrupts */
	 ECap3Regs.ECCLR.all = 0xFFFF;              /* Clear all CAP interrupt flags  */
	 ECap3Regs.ECCTL1.bit.CAPLDEN = 0;          /* disable CAP1-CAP4 register loads*/
	 ECap3Regs.ECCTL2.bit.TSCTRSTOP = 0;        /* Make sure the counter is stopped*/

	 /* Configure peripheral registers*/
	 ECap3Regs.ECCTL2.bit.CONT_ONESHT = 0;

	 ECap3Regs.ECCTL1.bit.CAP1POL = 0;
	 ECap3Regs.ECCTL1.bit.CAP2POL = 0;
	 ECap3Regs.ECCTL1.bit.CAP3POL = 0;
	 ECap3Regs.ECCTL1.bit.CAP4POL = 0;


	 ECap3Regs.ECCTL1.bit.CTRRST1 = 0;
	 ECap3Regs.ECCTL1.bit.CTRRST2 = 0;
	 ECap3Regs.ECCTL1.bit.CTRRST3 = 0;
	 ECap3Regs.ECCTL1.bit.CTRRST4 = 1;

	 ECap3Regs.ECCTL2.bit.SYNCI_EN = 0;
	 ECap3Regs.ECCTL2.bit.SYNCO_SEL = 3;
	 ECap3Regs.ECCTL1.bit.PRESCALE =0;
	 ECap3Regs.ECCLR.all = 0xffff;
	 ECap3Regs.ECCTL2.bit.CAP_APWM = 0;

	 ECap3Regs.ECEINT.bit.CEVT1 = 1;
	 ECap3Regs.ECEINT.bit.CEVT2 = 1;
	 ECap3Regs.ECEINT.bit.CEVT3 = 1;
	 ECap3Regs.ECEINT.bit.CEVT4 = 1;
	 ECap3Regs.ECEINT.bit.CTR_EQ_CMP = 0;
	 ECap3Regs.ECEINT.bit.CTR_EQ_PRD = 0;
	 ECap3Regs.ECEINT.bit.CTROVF =1;

	 ECap3Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	 ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1;        /* Start Counter*/
}
void ConfigEcap(void){
	/*Read the data sheet and finish the CAP configuration coce here*/
	ECap1Config();
	ECap2Config();
	ECap3Config();
}
void InitEcapForJ75(void){
	InitECapGpio();
	ConfigEcap();
}


//===========================================================================
// End of file.
//===========================================================================
