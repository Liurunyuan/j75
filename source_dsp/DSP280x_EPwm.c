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

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
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

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)   
   
/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
   
    EDIS;
}

void InitEPwm2Gpio(void)
{
   EALLOW;
	
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)

/* Configure ePWM-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
   
    EDIS;
}

void InitEPwm3Gpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)
       
/* Configure ePWM-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM3 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
	
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

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (EPWM4B)

/* Configure ePWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM4 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B
	
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

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM5B)

/* Configure ePWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
	
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

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;    // Enable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up on GPIO11 (EPWM6B)

/* Configure ePWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
	
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

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up on GPIO32 (EPWMSYNCI)    

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)    

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.   

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Enable pull-up on GPIO32 (EPWMSYNCI)    



/* Configure EPWMSYNC0  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

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
   GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
   GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up on GPIO13 (TZ2)
   GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up on GPIO14 (TZ3)
   GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up on GPIO15 (TZ4)

   GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ5)
// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ5)

   GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ6) 
// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ6)  
   
/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.  
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;  // Asynch input GPIO13 (TZ2)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;  // Asynch input GPIO14 (TZ3)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (TZ4)

   GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ5)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ5)

   GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ6) 
// GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ6)  

   
/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.   
   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as TZ2
   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as TZ3
   GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;  // Configure GPIO15 as TZ4

   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ5
// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ5

   GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ6               
// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ6  

   EDIS;
}
void InitEPwm1()
{
	EALLOW;
	EPwm1Regs.TZCTL.bit.TZA=1;//发生错误时PWMA输出低电平
	EPwm1Regs.TZCTL.bit.TZB=1;//发生错误时PWMB输出低电平
	EDIS;

//	EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD;
//	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;
//	EPwm1Regs.TBCTR = 0x0000;
//
//	EPwm1Regs.CMPA.half.CMPA = EPWM1_TIMER_HALF_TBPRD;
//	//EPwm1Regs.CMPB = EPWM2_TIMER_HALF_TBPRD;
//	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
//	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
//	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
//	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
//	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
//	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
//	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
//	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
//	EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
//	EPwm1Regs.AQCTLB.bit.CAU = AQ_SET;
//	EPwm1Regs.AQCTLB.bit.CAD = AQ_CLEAR;
//
//	EPwm1Regs.AQSFRC.bit.RLDCSF = 3;
//
//
////	EPwm1Regs.DBCTL.all = 0x000b;
//	EPwm1Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA rising edge delay , EPWMXB falling edge delay
//	EPwm1Regs.DBCTL.bit.POLSEL = 2;  //EPWMxB  invert
//	EPwm1Regs.DBCTL.bit.OUT_MODE = 3;
//
//	EPwm1Regs.DBRED = 0;//180==1.5us
//	EPwm1Regs.DBFED = 0;//180==1.5us
//
//	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
//	EPwm1Regs.ETSEL.bit.INTEN = 1;
//	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;
//
//	EPwm1Regs.ETSEL.bit.SOCAEN = 1;
//	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;
//	EPwm1Regs.ETPS.bit.SOCAPRD = 1;
//	EPwm1Regs.AQCSFRC.all = 0x0006;


	    EPwm1Regs.TBPRD = EPWM1_TIMER_TBPRD;  // 设置 Set timer period TBCLKs  40KHz, 25us
		//设置时基相位寄存器TBPHS
	    EPwm1Regs.TBPHS.all = 0x0000;   // 初始相位为0
		//设置时基计数器TBCTR
	    EPwm1Regs.TBCTR = 0x0000;       // 清零时基计数器
		//设置时基控制寄存器
		EPwm1Regs.TBCTL.bit.PHSEN = 0;//相位角控制禁止
		EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;//高速时钟预分频,0:不分频
	  	EPwm1Regs.TBCTL.bit.CLKDIV = 0;//时钟预分频比设置，TBCLK=SYSCLKOUT/(HSPCLKDIV*CLKDIV)，0:不分频

		EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;//禁止同步信号输出
		EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;//更新时基周期寄存器时使用缓冲寄存器，即使用时基周期寄存器的影子寄存器
		EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//计数模式为：连续向上向下

		//计数比较模块寄存器设置:
		//计数比较控制寄存器CMPCTL设置
		EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;//启用占空比计数比较B影子寄存器
		EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;//启用占空比计数比较A影子寄存器
		EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;//当计数器为0时重载比较寄存器B
		EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;//当计数器为0时重载比较寄存器A

		//输出模块设置：
		//输出A控制寄存器AQCTLA设置
		//设置计数器值等于比较设定值CMPA时，EPWM1A极性:向下计数与比较值相等时置高
		EPwm1Regs.AQCTLA.bit.CAD =AQ_SET;//AQ_SET;
		//设置计数器值等于比较设定值CMPA时，EPWM1A极性:向上计数与比较值相等时置低
		EPwm1Regs.AQCTLA.bit.CAU =AQ_CLEAR;//AQ_CLEAR;
		//设置计数器值等于占空比设定值CMPB时，EPWM1A极性:不响应
		EPwm1Regs.AQCTLA.bit.CBD =AQ_NO_ACTION;//AQ_NO_ACTION;
		//设置计数器值等于占空比设定值CMPB时，EPWM1A极性:不响应
		EPwm1Regs.AQCTLA.bit.CBU =AQ_NO_ACTION;//AQ_NO_ACTION;
		//设置计数器值等于时基周期时EPWM1A动作：不响应
		EPwm1Regs.AQCTLA.bit.PRD =AQ_NO_ACTION;
		//设置计数器值等于0时EPWM1A动作：不响应
		EPwm1Regs.AQCTLA.bit.ZRO =AQ_NO_ACTION;

		//输出B控制寄存器AQCTLB设置
		//设置计数器值等于比较设定值CMPA时，EPWM1B极性:向下计数与比较值相等时置高
		EPwm1Regs.AQCTLB.bit.CAD =AQ_CLEAR;//AQ_CLEAR;
		//设置计数器值等于比较设定值CMPA时，EPWM1B极性:向上计数与比较值相等时置低
		EPwm1Regs.AQCTLB.bit.CAU =AQ_SET;//AQ_SET;
		//设置计数器值等于比较设定值CMPB时，E/PWM1B极性:不响应
		EPwm1Regs.AQCTLB.bit.CBD =AQ_NO_ACTION;
		//设置计数器值等于比较设定值CMPB时，EPWM1B极性:不响应
		EPwm1Regs.AQCTLB.bit.CBU =AQ_NO_ACTION;
		//设置计数器值等于时基周期时EPWM1A动作：不响应
		EPwm1Regs.AQCTLB.bit.PRD =AQ_NO_ACTION;
		//设置计数器值等于0时EPWM1A动作：不响应
		EPwm1Regs.AQCTLB.bit.ZRO =AQ_NO_ACTION;

		EPwm1Regs.CMPA.half.CMPA= EPWM1_TIMER_HALF_TBPRD ;//初始设置50%的占空比
		//动作软件连续软件强制输出控制寄存器AQSFRC设置
	   EPwm1Regs.AQSFRC.bit.RLDCSF = 3;//立即加载
		//关闭PWM1
	  //EPwm1Regs.AQCSFRC.all = 0x0009;   //这样设置是上管子和下管子都让它保持低电平

		EPwm1Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA是上升沿,B下降沿延迟信号源
		EPwm1Regs.DBCTL.bit.POLSEL = 2;	//极性控制，EPWMxB 翻转，EPWMxA不翻转
		EPwm1Regs.DBCTL.bit.OUT_MODE = 3; //死区输出模式控制

		//死区上升沿延迟寄存器DBRED设置
	 	EPwm1Regs.DBRED = 0;//死区时间:1us=DBFED*TTBCLK
	 	//死区下降沿延迟寄存器DBFED设置
	 	EPwm1Regs.DBFED = 0;//死区时间: 1us=DBFED*TTBCLK

		//PWM斩波控制寄存器PCCTL设置，暂不用
		//故障捕捉区设置：暂不用

		EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;//PWM中断次数：1次
		EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;//pwm中断时刻：计数器值=周期值
		EPwm1Regs.ETSEL.bit.INTEN =0; //disable INT

		/*使能EPWMxSOCA作为 ADC 转换触发脉冲*/
		EPwm1Regs.ETSEL.bit.SOCAEN=1;
		/*TBCTR=0时产生SOCA信号*/
		EPwm1Regs.ETSEL.bit.SOCASEL=1;
		/*第一个事件产生时，产生SOCA信号*/
		EPwm1Regs.ETPS.bit.SOCAPRD=1;

}
void InitEPwm2()
{
	EALLOW;
//	EPwm2Regs.TZSEL.bit.OSHT2=1;
//	EPwm2Regs.TZSEL.bit.OSHT3=1;
	EPwm2Regs.TZCTL.bit.TZA=1;
	EPwm2Regs.TZCTL.bit.TZB=1;
//	EPwm2Regs.TZEINT.bit.OST=1;
	EDIS;
//
//	EPwm2Regs.TBPRD = EPWM1_TIMER_TBPRD;
//	EPwm2Regs.TBPHS.half.TBPHS = 0x0000;
//	EPwm2Regs.TBCTR = 0x0000;
//	EPwm2Regs.CMPA.half.CMPA =EPWM1_TIMER_HALF_TBPRD;
//	//EPwm2Regs.CMPB = EPWM1_TIMER_HALF_TBPRD;
//	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
//	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;
//	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
//	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
//	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
//	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
//	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
//	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
//	EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
//	EPwm2Regs.AQCTLB.bit.CAU = AQ_SET;
//	EPwm2Regs.AQCTLB.bit.CAD = AQ_CLEAR;
//	EPwm2Regs.AQSFRC.bit.RLDCSF = 3;
//	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
//	EPwm2Regs.ETSEL.bit.INTEN = 1;
//	EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;
//
//
//	EPwm2Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA rising edge delay , EPWMXB falling edge delay
//	EPwm2Regs.DBCTL.bit.POLSEL = 2;  //EPWMxB  invert
//	EPwm2Regs.DBCTL.bit.OUT_MODE = 3;
//	EPwm2Regs.DBRED = 0;
//	EPwm2Regs.DBFED = 0;
//	EPwm2Regs.AQCSFRC.all = 0x0006;

	//初始化EPWM2，驱动B相。BH—EPWM1A，BL-EPWM1B
		//时基模块寄存器设置：
		    // 设置时基周期寄存器TBPRD
			//注意：在向上向下计数模式中，该值是PWM周期的1/2；其他模式下该值是PWM的周期
		    EPwm2Regs.TBPRD = EPWM1_TIMER_TBPRD;  // 设置 Set timer period TBCLKs  40KHz, 25us
			//设置时基相位寄存器TBPHS
		    EPwm2Regs.TBPHS.all = 0x0000;   // 初始相位为0
			//设置时基计数器TBCTR
		    EPwm2Regs.TBCTR = 0x0000;       // 清零时基计数器
			//设置时基控制寄存器
			EPwm2Regs.TBCTL.bit.PHSEN = 0;//相位角控制禁止
			EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;//高速时钟预分频,0:不分频
		  	EPwm2Regs.TBCTL.bit.CLKDIV = 0;//时钟预分频比设置，TBCLK=SYSCLKOUT/(HSPCLKDIV*CLKDIV)，0:不分频

			EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;//禁止同步信号输出
			EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;//更新时基周期寄存器时使用缓冲寄存器，即使用时基周期寄存器的影子寄存器
			EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//计数模式为：连续向上向下

			//计数比较模块寄存器设置:
			//计数比较控制寄存器CMPCTL设置
			EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;//启用占空比计数比较B影子寄存器
			EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;//启用占空比计数比较A影子寄存器
			EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;//当计数器为0时重载比较寄存器B
			EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;//当计数器为0时重载比较寄存器A

			//输出模块设置：
			//输出A控制寄存器AQCTLA设置
			//设置计数器值等于比较设定值CMPA时，EPWM1A极性:向下计数与比较值相等时置高
			EPwm2Regs.AQCTLA.bit.CAD =AQ_SET;//AQ_SET;
			//设置计数器值等于比较设定值CMPA时，EPWM1A极性:向上计数与比较值相等时置低
			EPwm2Regs.AQCTLA.bit.CAU =AQ_CLEAR;//AQ_CLEAR;
			//设置计数器值等于占空比设定值CMPB时，EPWM1A极性:不响应
			EPwm2Regs.AQCTLA.bit.CBD =AQ_NO_ACTION;//AQ_NO_ACTION;
			//设置计数器值等于占空比设定值CMPB时，EPWM1A极性:不响应
			EPwm2Regs.AQCTLA.bit.CBU =AQ_NO_ACTION;//AQ_NO_ACTION;
			//设置计数器值等于时基周期时EPWM1A动作：不响应
			EPwm2Regs.AQCTLA.bit.PRD =AQ_NO_ACTION;
			//设置计数器值等于0时EPWM1A动作：不响应
			EPwm2Regs.AQCTLA.bit.ZRO =AQ_NO_ACTION;

			//输出B控制寄存器AQCTLB设置
			//设置计数器值等于比较设定值CMPA时，EPWM1B极性:向下计数与比较值相等时置高
			EPwm2Regs.AQCTLB.bit.CAD =AQ_CLEAR;//AQ_CLEAR;
			//设置计数器值等于比较设定值CMPA时，EPWM1B极性:向上计数与比较值相等时置低
			EPwm2Regs.AQCTLB.bit.CAU =AQ_SET;//AQ_SET;
			//设置计数器值等于比较设定值CMPB时，E/PWM1B极性:不响应
			EPwm2Regs.AQCTLB.bit.CBD =AQ_NO_ACTION;
			//设置计数器值等于比较设定值CMPB时，EPWM1B极性:不响应
			EPwm2Regs.AQCTLB.bit.CBU =AQ_NO_ACTION;
			//设置计数器值等于时基周期时EPWM1A动作：不响应
			EPwm2Regs.AQCTLB.bit.PRD =AQ_NO_ACTION;
			//设置计数器值等于0时EPWM1A动作：不响应
			EPwm2Regs.AQCTLB.bit.ZRO =AQ_NO_ACTION;

			EPwm2Regs.CMPA.half.CMPA= EPWM1_TIMER_HALF_TBPRD/2 ;//初始设置50%的占空比
			//动作软件连续软件强制输出控制寄存器AQSFRC设置
		   EPwm2Regs.AQSFRC.bit.RLDCSF = 3;//立即加载
			//关闭PWM2
		  //EPwm2Regs.AQCSFRC.all = 0x0009;   //这样设置是上管子和下管子都让它保持低电平

			EPwm2Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA是上升沿,B下降沿延迟信号源
			EPwm2Regs.DBCTL.bit.POLSEL = 2;	//极性控制，EPWMxB 翻转，EPWMxA不翻转
			EPwm2Regs.DBCTL.bit.OUT_MODE = 3; //死区输出模式控制

			//死区上升沿延迟寄存器DBRED设置
		 	EPwm2Regs.DBRED = 0;//死区时间:1us=DBFED*TTBCLK
		 	//死区下降沿延迟寄存器DBFED设置
		 	EPwm2Regs.DBFED = 0;//死区时间: 1us=DBFED*TTBCLK

			//PWM斩波控制寄存器PCCTL设置，暂不用
			//故障捕捉区设置：暂不用

			EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;//PWM中断次数：1次
			EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;//pwm中断时刻：计数器值=0
			EPwm2Regs.ETSEL.bit.INTEN =0; //disable INT
}

void InitEPwm3()
{
//	EALLOW;
////	EPwm3Regs.TZSEL.bit.OSHT2=1;
////	EPwm3Regs.TZSEL.bit.OSHT3=1;
//	EPwm3Regs.TZCTL.bit.TZA=1;
//	EPwm3Regs.TZCTL.bit.TZB=1;
////	EPwm3Regs.TZEINT.bit.OST=1;
//	EDIS;
//
//	EPwm3Regs.TBPRD = EPWM1_TIMER_TBPRD;
//	EPwm3Regs.TBPHS.half.TBPHS = 0x0000;
//	EPwm3Regs.TBCTR = 0x0000;
//	EPwm3Regs.CMPA.half.CMPA =EPWM1_TIMER_HALF_TBPRD;
//	//EPwm3Regs.CMPB = EPWM1_TIMER_HALF_TBPRD;
//	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
//	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;
//	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
//	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
//	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
//	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
//	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
//	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
//	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
//	EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
//	EPwm3Regs.AQCTLB.bit.CAU = AQ_SET;
//	EPwm3Regs.AQCTLB.bit.CAD = AQ_CLEAR;
//	EPwm3Regs.AQSFRC.bit.RLDCSF = 3;
//	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
//	EPwm3Regs.ETSEL.bit.INTEN = 1;
//	EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;
//
//
////	EPwm3Regs.DBCTL.all = 0xb;
//	EPwm3Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA rising edge delay , EPWMXB falling edge delay
//	EPwm3Regs.DBCTL.bit.POLSEL = 2;  //EPWMxB  invert
//	EPwm3Regs.DBCTL.bit.OUT_MODE = 3;
//	EPwm3Regs.DBRED = 0;
//	EPwm3Regs.DBFED = 0;
//	EPwm3Regs.AQCSFRC.all = 0x0006;


	//初始化EPWM3，驱动A相。AH—EPWM1A，AL-EPWM1B
		//时基模块寄存器设置：
		    // 设置时基周期寄存器TBPRD
			//注意：在向上向下计数模式中，该值是PWM周期的1/2；其他模式下该值是PWM的周期
		    EPwm3Regs.TBPRD = EPWM1_TIMER_TBPRD;  // 设置 Set timer period TBCLKs  40KHz, 25us
			//设置时基相位寄存器TBPHS
		    EPwm3Regs.TBPHS.all = 0x0000;   // 初始相位为0
			//设置时基计数器TBCTREPWM1_TIMER_HALF_TBPRD
		    EPwm3Regs.TBCTR = 0x0000;       // 清零时基计数器
			//设置时基控制寄存器
			EPwm3Regs.TBCTL.bit.PHSEN = 0;//相位角控制禁止
			EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0;//高速时钟预分频,0:不分频
		  	EPwm3Regs.TBCTL.bit.CLKDIV = 0;//时钟预分频比设置，TBCLK=SYSCLKOUT/(HSPCLKDIV*CLKDIV)，0:不分频

			EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;//禁止同步信号输出
			EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;//更新时基周期寄存器时使用缓冲寄存器，即使用时基周期寄存器的影子寄存器
			EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//计数模式为：连续向上向下

			//计数比较模块寄存器设置:
			//计数比较控制寄存器CMPCTL设置
			EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;//启用占空比计数比较B影子寄存器
			EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;//启用占空比计数比较A影子寄存器
			EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;//当计数器为0时重载比较寄存器B
			EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;//当计数器为0时重载比较寄存器A

			//输出模块设置：
			//输出A控制寄存器AQCTLA设置
			//设置计数器值等于比较设定值CMPA时，EPWM1A极性:向下计数与比较值相等时置高
			EPwm3Regs.AQCTLA.bit.CAD =AQ_SET;//AQ_SET;
			//设置计数器值等于比较设定值CMPA时，EPWM1A极性:向上计数与比较值相等时置低
			EPwm3Regs.AQCTLA.bit.CAU =AQ_CLEAR;//AQ_CLEAR;
			//设置计数器值等于占空比设定值CMPB时，EPWM1A极性:不响应
			EPwm3Regs.AQCTLA.bit.CBD =AQ_NO_ACTION;//AQ_NO_ACTION;
			//设置计数器值等于占空比设定值CMPB时，EPWM1A极性:不响应
			EPwm3Regs.AQCTLA.bit.CBU =AQ_NO_ACTION;//AQ_NO_ACTION;
			//设置计数器值等于时基周期时EPWM1A动作：不响应
			EPwm3Regs.AQCTLA.bit.PRD =AQ_NO_ACTION;
			//设置计数器值等于0时EPWM1A动作：不响应
			EPwm3Regs.AQCTLA.bit.ZRO =AQ_NO_ACTION;

			//输出B控制寄存器AQCTLB设置
			//设置计数器值等于比较设定值CMPA时，EPWM1B极性:向下计数与比较值相等时置高
			EPwm3Regs.AQCTLB.bit.CAD =AQ_CLEAR;//AQ_CLEAR;
			//设置计数器值等于比较设定值CMPA时，EPWM1B极性:向上计数与比较值相等时置低
			EPwm3Regs.AQCTLB.bit.CAU =AQ_SET;//AQ_SET;
			//设置计数器值等于比较设定值CMPB时，E/PWM1B极性:不响应
			EPwm3Regs.AQCTLB.bit.CBD =AQ_NO_ACTION;
			//设置计数器值等于比较设定值CMPB时，EPWM1B极性:不响应
			EPwm3Regs.AQCTLB.bit.CBU =AQ_NO_ACTION;
			//设置计数器值等于时基周期时EPWM1A动作：不响应
			EPwm3Regs.AQCTLB.bit.PRD =AQ_NO_ACTION;
			//设置计数器值等于0时EPWM1A动作：不响应
			EPwm3Regs.AQCTLB.bit.ZRO =AQ_NO_ACTION;

			EPwm3Regs.CMPA.half.CMPA= EPWM1_TIMER_HALF_TBPRD/3 ;//初始设置50%的占空比
			//动作软件连续软件强制输出控制寄存器AQSFRC设置
		   EPwm3Regs.AQSFRC.bit.RLDCSF = 3;//立即加载
			//关闭PWM3
		  //EPwm3Regs.AQCSFRC.all = 0x0009;   //这样设置是上管子和下管子都让它保持低电平

			EPwm3Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA是上升沿,B下降沿延迟信号源
			EPwm3Regs.DBCTL.bit.POLSEL = 2;	//极性控制，EPWMxB 翻转，EPWMxA不翻转
			EPwm3Regs.DBCTL.bit.OUT_MODE = 3; //死区输出模式控制

			//死区上升沿延迟寄存器DBRED设置
		 	EPwm3Regs.DBRED = 0;//死区时间:1us=DBFED*TTBCLK
		 	//死区下降沿延迟寄存器DBFED设置
		 	EPwm3Regs.DBFED = 0;//死区时间: 1us=DBFED*TTBCLK

			//PWM斩波控制寄存器PCCTL设置，暂不用
			//故障捕捉区设置：暂不用

			EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;//PWM中断次数：1次
			EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;//pwm中断时刻：计数器值=0
			EPwm3Regs.ETSEL.bit.INTEN =0; //disable INT
//
}
void InitEpwmForJ75(void){
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
