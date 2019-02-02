// TI File $Revision: /main/1 $
// Checkin $Date: December 1, 2004   11:12:03 $
//###########################################################################
//
// FILE:	DSP280x_PieCtrl.c
//
// TITLE:	DSP280x Device PIE Control Register Initialization Functions.
//
//###########################################################################
// $TI Release: DSP280x C/C++ Header Files V1.70 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

//---------------------------------------------------------------------------
// InitPieCtrl: 
//---------------------------------------------------------------------------
// This function initializes the PIE control registers to a known state.
//
void InitPieCtrl(void)
{
    // Disable Interrupts at the CPU level:
    DINT;

    // Disable the PIE
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

	// Clear all PIEIER registers:
	PieCtrlRegs.PIEIER1.all = 0;
	PieCtrlRegs.PIEIER2.all = 0;
	PieCtrlRegs.PIEIER3.all = 0;	
	PieCtrlRegs.PIEIER4.all = 0;
	PieCtrlRegs.PIEIER5.all = 0;
	PieCtrlRegs.PIEIER6.all = 0;
	PieCtrlRegs.PIEIER7.all = 0;
	PieCtrlRegs.PIEIER8.all = 0;
	PieCtrlRegs.PIEIER9.all = 0;
	PieCtrlRegs.PIEIER10.all = 0;
	PieCtrlRegs.PIEIER11.all = 0;
	PieCtrlRegs.PIEIER12.all = 0;

	// Clear all PIEIFR registers:
	PieCtrlRegs.PIEIFR1.all = 0;
	PieCtrlRegs.PIEIFR2.all = 0;
	PieCtrlRegs.PIEIFR3.all = 0;	
	PieCtrlRegs.PIEIFR4.all = 0;
	PieCtrlRegs.PIEIFR5.all = 0;
	PieCtrlRegs.PIEIFR6.all = 0;
	PieCtrlRegs.PIEIFR7.all = 0;
	PieCtrlRegs.PIEIFR8.all = 0;
	PieCtrlRegs.PIEIFR9.all = 0;
	PieCtrlRegs.PIEIFR10.all = 0;
	PieCtrlRegs.PIEIFR11.all = 0;
	PieCtrlRegs.PIEIFR12.all = 0;


}	

//---------------------------------------------------------------------------
// EnableInterrupts: 
//---------------------------------------------------------------------------
// This function enables the PIE module and CPU interrupts
//
void EnableInterrupts()
{

    // Enable the PIE
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    		
	// Enables PIE to drive a pulse into the CPU 
	PieCtrlRegs.PIEACK.all = 0xFFFF;  

	//PieCtrlRegs.PIEIER1.bit.INTx1 = 1;//ADC中断,16通道转换完成后来中断
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;//定时器0中断。
//	PieCtrlRegs.PIEIER2.bit.INTx1= 1;//TZ_FAULTB触发
	//PieCtrlRegs.PIEIER2.bit.INTx2= 1;//TZ_FAULTA触发//
	//PieCtrlRegs.PIEIER2.bit.INTx3= 1;//IKA_BJ触发//
	//PieCtrlRegs.PIEIER2.bit.INTx4= 1;//IKB_BJ触发//
//	PieCtrlRegs.PIEIER2.bit.INTx6 = 1;//应急开关触发
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;//ePWM1中断

	PieCtrlRegs.PIEIER4.bit.INTx1 = 1;//ECAP1
	PieCtrlRegs.PIEIER4.bit.INTx2 = 1;//ECAP2
	PieCtrlRegs.PIEIER4.bit.INTx3 = 1;//ECAP3

	PieCtrlRegs.PIEIER8.bit.INTx5 = 1;//SCIC RX Interrupt
	PieCtrlRegs.PIEIER8.bit.INTx6 = 1;//SCIC TX Interrupt
	PieCtrlRegs.PIEIER9.bit.INTx3 = 1;//SCIB RX interrupt
	PieCtrlRegs.PIEIER9.bit.INTx4 = 1;//SCIB TX interrupt



	// Enable Interrupts at the CPU level 
    EINT;
    ERTM;
}

void InitInterruptForJ75(void){
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
    IER |= M_INT1;
    IER |= M_INT2;
    IER |= M_INT3;
    IER |= M_INT4;
    IER |= M_INT7;
 	IER |= M_INT8;//SCIc
    IER |= M_INT9;//SCIa//ECAN//scib
    IER |= M_INT13;//timer1
	EnableInterrupts();
}
//===========================================================================
// End of file.
//===========================================================================
