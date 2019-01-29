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
	/*禁止CPU级中断,Disable Interrupts at the CPU level*/
    DINT;
    /*禁止PIE  Disable the PIE*/
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

	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;//使能epwm1中间级中断

	// Enable Interrupts at the CPU level 
    EINT;

}
/*
 * Initialize all the Interrupt
 */
void Init_Interrupt(void)
{
	//初始化CPU_T0
//	InitCpuTimers();
//	ConfigCpuTimer(&CpuTimer0, 120, 200);//t = freq * priod/150000000,0.2ms
//    CpuTimer0Regs.TCR.bit.TIE= 1;
//    CpuTimer0Regs.TCR.bit.TSS = 0;
//	ConfigCpuTimer(&CpuTimer1, 120, 10000);
//    CpuTimer1Regs.TCR.bit.TIE= 1;
//    CpuTimer1Regs.TCR.bit.TSS = 0;
    //中断配置
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
    EINT;   // Enable Global interrupt INTM
    ERTM;
    AdcRegs.ADCST.bit.INT_SEQ1_CLR=1;//此句要有，否则进步了中断，应为在该行代码执行前，seq1中断标识已经被立起，此处需要清除

    //ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1;

    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;//此句做用同上


    EALLOW;
    EPwm1Regs.TZCLR.bit.CBC=1;//清除CBC时间标志位
    EPwm1Regs.TZCLR.bit.INT=1;//清除中断标识位
    EDIS;
    EPwm1Regs.ETCLR.bit.INT = 1;
}

//===========================================================================
// End of file.
//===========================================================================
