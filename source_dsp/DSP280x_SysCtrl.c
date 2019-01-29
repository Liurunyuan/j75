// TI File $Revision: /main/8 $
// Checkin $Date: November 14, 2007   11:00:37 $
//###########################################################################
//
// FILE:   DSP280x_SysCtrl.c
//
// TITLE:  DSP280x Device System Control Initialization & Support Functions.
//
// DESCRIPTION:
//
//         Example initialization of system resources.
//
//###########################################################################
// $TI Release: DSP280x C/C++ Header Files V1.70 $
// $Release Date: July 27, 2009 $
//###########################################################################


#include "DSP280x_Device.h"     // Headerfile Include File
#include "DSP280x_Examples.h"   // Examples Include File
#include "define.h"

#pragma CODE_SECTION(InitFlash, "ramfuncs");
void if_flash_init(void);
// Functions that will be run from RAM need to be assigned to
// a different section.  This section will then be mapped to a load and
// run address using the linker cmd file.
//---------------------------------------------------------------------------
// InitSysCtrl:
//---------------------------------------------------------------------------
// This function initializes the System Control registers to a known state.
// - Disables the watchdog
// - Set the PLLCR for proper SYSCLKOUT frequency
// - Set the pre-scaler for the high and low frequency peripheral clocks
// - Enable the clocks to the peripherals
/*系统初始化函数*/
void InitSysCtrl(void)
{
	int i;
	DisableDog();

   /*2调用设置时钟函数*/
   /*初始化参数：初始化锁相环，配置系统主频为 60MHz*/
   /*Initialize the PLL control: PLLCR and CLKINDIV*/
   /* DSP28_PLLCR and DSP28_CLKINDIV are defined in DSP280x_Examples.h*/
   /*频率为晶振频率 20MHz*DSP28_PLLCR/DSP28_CLKINDIV = 80MHz 为系统主频*/
	InitPll(DSP28_PLLCR,DSP28_CLKINDIV);


   /*6等待5个周期,详见文件夹：《重点参考资料》文件：SYSTEM.pdf
    * TMS320x280x, 2801x, 2804x DSPSystem Control and Interrupts 6.3.2*/
	for(i=0;i<5;i++)
	{
	}
	// Initialize the peripheral clocks
	InitPeripheralClocks();
	if_flash_init();
}
// This function initializes the Flash Control registers

//                   CAUTION
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results
void if_flash_init(void)
{
	#ifdef FLASH  	//下载
		memcpy(	&RamfuncsRunStart,
				&RamfuncsLoadStart,
				&RamfuncsLoadEnd - &RamfuncsLoadStart);
	// Call Flash Initialization to setup flash waitstates
	// This function must reside in RAM
		InitFlash();
	#endif
}

//---------------------------------------------------------------------------
// Example: DisableDog:
//---------------------------------------------------------------------------
// This function disables the watchdog timer.
/*禁止看门狗函数*/
void DisableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;// 0110 1000 禁止看门狗，5~3位必须写101，否则引起复位
    EDIS;
}
/*使能看门狗函数*/
void EnableDog(void)
{
	EALLOW;
	SysCtrlRegs.WDCR = 0x002F;
	EDIS;
}
//---------------------------------------------------------------------------
// Example: InitPll:
//---------------------------------------------------------------------------
// This function initializes the PLLCR register.
/*2调用设置时钟函数*/
void InitPll(Uint16 val, Uint16 clkindiv)
{
   volatile Uint16 iVol;

   // Make sure the PLL is not running in limp mode
   if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
   {
      // Missing external clock has been detected
      // Replace this line with a call to an appropriate
      // SystemShutdown(); function.
      asm("        ESTOP0");
   }

   // CLKINDIV MUST be 0 before PLLCR can be changed from
   // 0x0000. It is set to 0 by an external reset XRSn
   if (SysCtrlRegs.PLLSTS.bit.CLKINDIV != 0)
   {
       EALLOW;
       SysCtrlRegs.PLLSTS.bit.CLKINDIV = 0;
       EDIS;
   }

   // Change the PLLCR
   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {

      EALLOW;
      // Before setting PLLCR turn off missing clock detect logic
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
      SysCtrlRegs.PLLCR.bit.DIV = val;
      EDIS;

      // Optional: Wait for PLL to lock.
      // During this time the CPU will switch to OSCCLK/2 until
      // the PLL is stable.  Once the PLL is stable the CPU will
      // switch to the new PLL value.
      //
      // This time-to-lock is monitored by a PLL lock counter.
      //
      // Code is not required to sit and wait for the PLL to lock.
      // However, if the code does anything that is timing critical,
      // and requires the correct clock be locked, then it is best to
      // wait until this switching has completed.

      // Wait for the PLL lock bit to be set.
      // Note this bit is not available on 281x devices.  For those devices
      // use a software loop to perform the required count.

      // The watchdog should be disabled before this loop, or fed within
      // the loop via ServiceDog().

	  // Uncomment to disable the watchdog
      DisableDog();

      while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)
      {
	      // Uncomment to service the watchdog
          // ServiceDog();
      }

      EALLOW;
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
      SysCtrlRegs.PLLSTS.bit.CLKINDIV = clkindiv;
      EDIS;
    }
}
//--------------------------------------------------------------------------
// Example: InitPeripheralClocks:
//---------------------------------------------------------------------------
// This function initializes the clocks to the peripheral modules.
// First the high and low clock prescalers are set
// Second the clocks are enabled to each peripheral.
// To reduce power, leave clocks to unused peripherals disabled
//
// Note: If a peripherals clock is not enabled then you cannot
// read or write to the registers for that peripheral
/*设置外设高低速时钟，并关闭所有外设时钟函数*/
void InitPeripheralClocks(void)
{
   EALLOW;

// HISPCP/LOSPCP prescale register settings, normally it will be set to default values
   SysCtrlRegs.HISPCP.all = 0x0000;	//高速时钟= SYSCLKOUT,即为75MHz
   SysCtrlRegs.LOSPCP.all = 0x0000;	//低速时钟= SYSCLKOUT,即为75MHz
// XCLKOUT to SYSCLKOUT ratio.  By default XCLKOUT = 1/4 SYSCLKOUT
   SysCtrlRegs.XCLK.bit.XCLKOUTDIV = 0; //外部时钟输出XCLKOUT= 1/4 SYSCLKOUT等于系统时钟

// Peripheral clock enables set for the selected peripherals.
// If you are not using a peripheral leave the clock off
// to save on power.
// Note: not all peripherals are available on all 280x derivates.
// Refer to the datasheet for your particular device.
// This function is not written to be an example of efficient code.

   SysCtrlRegs.PCLKCR0.bit.ECANBENCLK = 0;  // ECAN-B时钟禁止
   SysCtrlRegs.PCLKCR0.bit.ECANAENCLK = 0;  // ECAN-A时钟禁止
   SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 0;   // SCI-B时钟禁止
   SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 0;   // SCI-A时钟禁止
   SysCtrlRegs.PCLKCR0.bit.SPIBENCLK = 0;   // SPI-B时钟禁止
   SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 0;   // SPI-A时钟禁止
   SysCtrlRegs.PCLKCR0.bit.SPIDENCLK = 0;   // SPI-D时钟禁止
   SysCtrlRegs.PCLKCR0.bit.SPICENCLK = 0;   // SPI-C时钟禁止
   SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 0;   // I2C时钟禁止
   SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0;    //ADC时钟先禁止 //（ADC时钟使能，为高速时钟(HSPCLK））
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // ePWM内的时基时钟使能

//   SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1; // CPU Timer 0
//	SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 1; // CPU Timer 1
//	SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = 1; // CPU Timer 2

   SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = 0;  // eQEP2时钟禁止
   SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 0;  // eQEP1时钟禁止
   SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = 0;  // eCAP4时钟禁止
   SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 0;  // eCAP3时钟先禁止
   SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 0;  // eCAP2时钟先禁止
   SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;  // eCAP1时钟先禁止
   SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 0;  // ePWM6时钟禁止
   SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 0;  // ePWM5时钟禁止
   SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;  // ePWM4时钟禁止
   SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 0;  // ePWM3时钟先禁止，为CPU时钟SYSCLK
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 0;  // ePWM2时钟先禁止，为CPU时钟SYSCLK
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 0;  // ePWM1时钟先禁止，为CPU时钟SYSCLK

   /*调试时验证是否执行本语句，若执行，则去掉判断条件，若不执行，则删除*/
   if(DevEmuRegs.PARTID.bit.PARTNO == PARTNO_2808 ||
      DevEmuRegs.PARTID.bit.PARTNO == PARTNO_2809)
   {
	   SysCtrlRegs.PCLKCR0.bit.ECANBENCLK=0;    // eCAN-B
   }

   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;       // Enable TBCLK within the ePWM

   EDIS;
}

#pragma CODE_SECTION(InitFlash, "ramfuncs");
void InitFlash(void)
{
   EALLOW;
   //Enable Flash Pipeline mode to improve performance
   //of code executed from Flash.
   FlashRegs.FOPT.bit.ENPIPE = 1;

   //                CAUTION
   //Minimum waitstates required for the flash operating
   //at a given CPU rate must be characterized by TI.
   //Refer to the datasheet for the latest information.

   //Set the Paged Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 3;

   //Set the Random Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 3;

   //Set the Waitstate for the OTP
   FlashRegs.FOTPWAIT.bit.OTPWAIT = 5;

   //                CAUTION
   //ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;
   EDIS;

   //Force a pipeline flush to ensure that the write to
   //the last register configured occurs before returning.

   asm(" RPT #7 || NOP");
}
//===========================================================================
// End of file.
//===========================================================================
