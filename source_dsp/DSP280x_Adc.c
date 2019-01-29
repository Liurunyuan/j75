// TI File $Revision: /main/1 $
// Checkin $Date: December 1, 2004   11:11:30 $
//###########################################################################
//
// FILE:	DSP280x_Adc.c
//
// TITLE:	DSP280x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x Header Files V1.60 $
// $Release Date: December 3, 2007 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "define.h"

//---------------------------------------------------------------------------
// InitAdc: 
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
// PLEASE NOTE, ADC INIT IS DIFFERENT ON 281x vs 280x DEVICES!!!
//

void InitAdc(void)
{
	EALLOW;
	/*ADC时钟使能 （ADC时钟使能，为高速时钟(HSPCLK))*/
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
	EDIS;
    /*应该修改延时方法*/
	extern void DSP28x_usDelay(Uint32 Count);
	
    EALLOW;
    /*上电顺序设置*/
    /* 能带隙和参考电路上电Power up bandgap/reference*/
    AdcRegs.ADCTRL3.bit.ADCBGRFDN = 3;
	/*上电延时5ms，Delay before converting ADC channels*/
    DELAY_US(ADC_usDELAY);
    /*内核内的模拟电路上电*/
  	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;
  	/* Delay at least 20us before converting ADC channels ，  至少20us延时*/
  	DELAY_US(20);


}
void ADC_Config(void){
	/*ADC控制寄存器3:ADCTRL3*/
	/*ADC核时钟设置ADCCLK = HSPCLK/[2*ADC_CLKPS*CPS]
	*					  = 75MHz/(2*4*1)=12.5MHz */
  	/*AD内核时钟分频：ADCCLKPS=4，进行6分频，AD最高工作速度为12.5MHz，6分频为12.5MHz*/
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;
	/* 同步采样模式*/
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 1;
	/*转换时间预定标，对外设时钟HSPCLK进行分频，CPS=0时不分频，
	 * 详见文件夹：《重点参考资料》文件：2808ADC.pdf 2.1 ADC控制寄存器*/
	AdcRegs.ADCTRL1.bit.CPS = 0;

    /*ADC控制寄存器1:ADCTRL1*/
	/*采集窗口大小 = (ACQ_PS+1)*ADCLK=28.125MHz，0.08us*/
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0;
    /*ADC处于级联模式*/
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
    /*启动\停止转换模式，读取完转换序列后停止*/
 	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
 	/*禁止排序器使能覆盖模式*/
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;
	/*完成当前转换、锁定结果且更新状态机制之后，序列发生器和其它轮询程序逻辑停止*/
	AdcRegs.ADCTRL1.bit.SUSMOD = 2;

	/*ADC控制寄存器2:ADCTRL2*/
	/*该位只在级联模式有效，这里设置为0表示禁止ePWMx的SOCB触发级联的排序器SEQ1转换*/
	/*清除等待的SOC*/
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;
	/*禁止ePWMx的SOCB触发*/
	AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ = 0;
	/* 禁止INT_SEQ1的中断请求*/
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;
	/* 每个SEQ1序列结束时设置INT_SEQ1*/
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;
	/*禁止ePWMx的SOCA触发转换序列*/
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 0;
	/*禁止外部触发转换序列*/
	AdcRegs.ADCTRL2.bit.EXT_SOC_SEQ1 = 0;
	/*清除等待的SOC*/
	AdcRegs.ADCTRL2.bit.SOC_SEQ2= 0;
	/*禁用INT_SEQ2的中断请求*/
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 0;
	/* 每个SEQ2序列结束时设置INT_SEQ2*/
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ2 = 0;
	/*禁止ePWMx的SOCB触发转换序列*/
	AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 0;

    /*AD最大转换通道数寄存器ADCMAXCONV*/
	/*  SEQ1转换通道数：8*/
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1= 0x5;
    /*AD状态和标志寄存器:ADCST，该寄存器有2个R/W位，其余为只读位*/
	/*清除SEQ1中断标志*/
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
	/*清除SEQ2中断标志*/
	AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;

    /* AD偏移修改寄存器:ADCOFFTRIM*/
    /* 该寄存器的配置由TI公司固化于OTP中，调用ADC_cal()已经完成了它的初始化 */
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x00; /*第0通道转换ADCINA0/B0，A0：IB_AN_DSP,B0:IA_AN_DSP*/
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x01; /*第1通道转换ADCINA1/B1，A1: IC_AN_DSP，B1扩展备用*/
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x02; /*第2通道转换ADCINA2/B2扩展备用*/
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x03; /*第3通道转换ADCINA2/B2扩展备用*/
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x04; /*第4通道转换ADCINA4/B4，A4: IBUS_AN_DSP，B4扩展备用*/
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x05; /*第5通道转换ADCINA5/B5，A5：U1_SEN_DSP，B5扩展备用*/
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x06; /*第6通道转换ADCINA6/B6，A6：U2_SEN_DSP，B6扩展备用*/
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x07; /*第7通道转换ADCINA7/B7，A7：AN_COM，A7扩展备用*/
	/*允许ePWMx的SOCA触发转换序列*/
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
	DELAY_US(ADC_usDELAY);         // Delay 5ms before converting ADC channels
    EDIS;
    /*启动AD转换*/
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;   /*复位排序器*/
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;	/*触发级联序列发生器开始转换*/
}
/*
 * Initialize ADC, including GPIO and configuration
 */
void Init_ADC(void)
{
	InitAdc();
	ADC_Config();
}
//===========================================================================
// End of file.
//===========================================================================
