// TI File $Revision: /main/1 $
// Checkin $Date: December 1, 2004   11:11:30 $
//###########################################################################
//
// FILE:	DSP280x_Adc.c
//
// TITLE:	DSP280x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x C/C++ Header Files V1.70 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

#define ADC_usDELAY  5000L

//---------------------------------------------------------------------------
// InitAdc: 
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
// PLEASE NOTE, ADC INIT IS DIFFERENT ON 281x vs 280x DEVICES!!!
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);

    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed 
	// after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the 
	// CPU_CLOCK_SPEED define statement in the DSP280x_Examples.h file must 
	// contain the correct CPU clock period in nanoseconds. 

    AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels
}

void ConfigAdc(void){
    extern void DSP28x_usDelay(Uint32 Count);

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
	//ADC_cal();
	EDIS;

	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 3;
	DELAY_US(ADC_usDELAY);
  	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;


	AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x5;
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 1;
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0x0;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
    AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;
    AdcRegs.ADCTRL1.bit.SUSMOD = 2;
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 	= 1;
    AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ = 0;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 0;
    AdcRegs.ADCTRL2.bit.SOC_SEQ2= 0;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 0;
    AdcRegs.ADCTRL2.bit.INT_MOD_SEQ2 = 0;
    AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 0;
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 =0x0007;
    //AdcRegs.ADCMAXCONV.bit.MAX_CONV1= 0x5;
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
    DELAY_US(ADC_usDELAY);

    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;
    // AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;
    // AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
    // AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;
    // AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;
    // AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;
    // AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;
    // AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;
    // AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;

    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
}

void InitAdcForJ75(void){
	ConfigAdc();
}
//===========================================================================
// End of file.
//===========================================================================
