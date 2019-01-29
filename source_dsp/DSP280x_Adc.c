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
	/*ADCʱ��ʹ�� ��ADCʱ��ʹ�ܣ�Ϊ����ʱ��(HSPCLK))*/
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
	EDIS;
    /*Ӧ���޸���ʱ����*/
	extern void DSP28x_usDelay(Uint32 Count);
	
    EALLOW;
    /*�ϵ�˳������*/
    /* �ܴ�϶�Ͳο���·�ϵ�Power up bandgap/reference*/
    AdcRegs.ADCTRL3.bit.ADCBGRFDN = 3;
	/*�ϵ���ʱ5ms��Delay before converting ADC channels*/
    DELAY_US(ADC_usDELAY);
    /*�ں��ڵ�ģ���·�ϵ�*/
  	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;
  	/* Delay at least 20us before converting ADC channels ��  ����20us��ʱ*/
  	DELAY_US(20);


}
void ADC_Config(void){
	/*ADC���ƼĴ���3:ADCTRL3*/
	/*ADC��ʱ������ADCCLK = HSPCLK/[2*ADC_CLKPS*CPS]
	*					  = 75MHz/(2*4*1)=12.5MHz */
  	/*AD�ں�ʱ�ӷ�Ƶ��ADCCLKPS=4������6��Ƶ��AD��߹����ٶ�Ϊ12.5MHz��6��ƵΪ12.5MHz*/
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;
	/* ͬ������ģʽ*/
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 1;
	/*ת��ʱ��Ԥ���꣬������ʱ��HSPCLK���з�Ƶ��CPS=0ʱ����Ƶ��
	 * ����ļ��У����ص�ο����ϡ��ļ���2808ADC.pdf 2.1 ADC���ƼĴ���*/
	AdcRegs.ADCTRL1.bit.CPS = 0;

    /*ADC���ƼĴ���1:ADCTRL1*/
	/*�ɼ����ڴ�С = (ACQ_PS+1)*ADCLK=28.125MHz��0.08us*/
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0;
    /*ADC���ڼ���ģʽ*/
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
    /*����\ֹͣת��ģʽ����ȡ��ת�����к�ֹͣ*/
 	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
 	/*��ֹ������ʹ�ܸ���ģʽ*/
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;
	/*��ɵ�ǰת������������Ҹ���״̬����֮�����з�������������ѯ�����߼�ֹͣ*/
	AdcRegs.ADCTRL1.bit.SUSMOD = 2;

	/*ADC���ƼĴ���2:ADCTRL2*/
	/*��λֻ�ڼ���ģʽ��Ч����������Ϊ0��ʾ��ֹePWMx��SOCB����������������SEQ1ת��*/
	/*����ȴ���SOC*/
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;
	/*��ֹePWMx��SOCB����*/
	AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ = 0;
	/* ��ֹINT_SEQ1���ж�����*/
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;
	/* ÿ��SEQ1���н���ʱ����INT_SEQ1*/
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;
	/*��ֹePWMx��SOCA����ת������*/
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 0;
	/*��ֹ�ⲿ����ת������*/
	AdcRegs.ADCTRL2.bit.EXT_SOC_SEQ1 = 0;
	/*����ȴ���SOC*/
	AdcRegs.ADCTRL2.bit.SOC_SEQ2= 0;
	/*����INT_SEQ2���ж�����*/
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 0;
	/* ÿ��SEQ2���н���ʱ����INT_SEQ2*/
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ2 = 0;
	/*��ֹePWMx��SOCB����ת������*/
	AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 0;

    /*AD���ת��ͨ�����Ĵ���ADCMAXCONV*/
	/*  SEQ1ת��ͨ������8*/
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1= 0x5;
    /*AD״̬�ͱ�־�Ĵ���:ADCST���üĴ�����2��R/Wλ������Ϊֻ��λ*/
	/*���SEQ1�жϱ�־*/
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
	/*���SEQ2�жϱ�־*/
	AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;

    /* ADƫ���޸ļĴ���:ADCOFFTRIM*/
    /* �üĴ�����������TI��˾�̻���OTP�У�����ADC_cal()�Ѿ���������ĳ�ʼ�� */
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x00; /*��0ͨ��ת��ADCINA0/B0��A0��IB_AN_DSP,B0:IA_AN_DSP*/
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x01; /*��1ͨ��ת��ADCINA1/B1��A1: IC_AN_DSP��B1��չ����*/
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x02; /*��2ͨ��ת��ADCINA2/B2��չ����*/
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x03; /*��3ͨ��ת��ADCINA2/B2��չ����*/
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x04; /*��4ͨ��ת��ADCINA4/B4��A4: IBUS_AN_DSP��B4��չ����*/
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x05; /*��5ͨ��ת��ADCINA5/B5��A5��U1_SEN_DSP��B5��չ����*/
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x06; /*��6ͨ��ת��ADCINA6/B6��A6��U2_SEN_DSP��B6��չ����*/
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x07; /*��7ͨ��ת��ADCINA7/B7��A7��AN_COM��A7��չ����*/
	/*����ePWMx��SOCA����ת������*/
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
	DELAY_US(ADC_usDELAY);         // Delay 5ms before converting ADC channels
    EDIS;
    /*����ADת��*/
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;   /*��λ������*/
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;	/*�����������з�������ʼת��*/
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
