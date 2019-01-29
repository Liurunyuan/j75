// TI File $Revision: /main/4 $
// Checkin $Date: August 2, 2006   13:51:13 $
//###########################################################################
//
// FILE:   DSP280x_EPwm.c
//
// TITLE:  DSP280x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x Header Files V1.60 $
// $Release Date: December 3, 2007 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "define.h"

void InitEPwm1(void);  //��ʼ��EPwm1��������
void InitEPwm2(void);  //��ʼ��EPwm2��������
void InitEPwm3(void);  //��ʼ��EPwm3��������

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

void InitEPwm4Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWM4A)
    /*
     * In this project,only PWM4A is defined, so ONLY initialize GPO06
     */
    //GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (EPWM4B)

/* Configure ePWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM4 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    //GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B

    EDIS;
}


void InitEPwm5Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO8 (EPWM5A)
    /*
     * In this project,only PWM5A is defined, so ONLY initialize GPIO8
     */
    //GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM5B)

/* Configure ePWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    //GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B

    EDIS;
}


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

void InitEPwmGpio(void)
{
   InitEPwm1Gpio();
   InitEPwm2Gpio();
   InitEPwm3Gpio();
   InitEPwm4Gpio();
   InitEPwm5Gpio();
   //InitEPwm6Gpio();
}
//---------------------------------------------------------------------------
// InitEPwm: 
//---------------------------------------------------------------------------
// This function initializes the ePWM(s) to a known state.
/*��ʼ��EPwm����*/
void InitEPwm(void)
{
	EALLOW;
	/*ePWM1ʱ������ΪCPUʱ��SYSCLK*/
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;
	/*ePWM2ʱ������ΪCPUʱ��SYSCLK*/
	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;
	/*ePWM3ʱ������ΪCPUʱ��SYSCLK*/
	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;

	/*��ֹ��EPwmģ��ͬ��ʱ��ʹ��*/
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	/*���ó�ʼ��EPwm1����*/
	InitEPwm1();
	/*���ó�ʼ��EPwm2����*/
	InitEPwm2();
	/*���ó�ʼ��EPwm3*/
	InitEPwm3();

 	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1; //ʹ�ܸ�EPwmģ��ͬ��ʱ��ʹ��
 	EDIS;

}
/*��ʼ��EPwm1����*/
void InitEPwm1(void)
{



//��ʼ��EPWM1������C�ࡣCH��EPWM1A��CL-EPWM1B
	//ʱ��ģ��Ĵ������ã�
    // ����ʱ�����ڼĴ���TBPRD
	//ע�⣺���������¼���ģʽ�У���ֵ��PWM���ڵ�1/2������ģʽ�¸�ֵ��PWM������
    EPwm1Regs.TBPRD = PWM_TIMER_TBPRD;  // ���� Set timer period TBCLKs  40KHz, 25us
	//����ʱ����λ�Ĵ���TBPHS
    EPwm1Regs.TBPHS.all = 0x0000;   // ��ʼ��λΪ0
	//����ʱ��������TBCTR
    EPwm1Regs.TBCTR = 0x0000;       // ����ʱ��������
	//����ʱ�����ƼĴ���
	EPwm1Regs.TBCTL.bit.PHSEN = 0;//��λ�ǿ��ƽ�ֹ
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;//����ʱ��Ԥ��Ƶ,0:����Ƶ
  	EPwm1Regs.TBCTL.bit.CLKDIV = 0;//ʱ��Ԥ��Ƶ�����ã�TBCLK=SYSCLKOUT/(HSPCLKDIV*CLKDIV)��0:����Ƶ

	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;//��ֹͬ���ź����
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;//����ʱ�����ڼĴ���ʱʹ�û���Ĵ�������ʹ��ʱ�����ڼĴ�����Ӱ�ӼĴ���
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//����ģʽΪ��������������

	//�����Ƚ�ģ��Ĵ�������:
	//�����ȽϿ��ƼĴ���CMPCTL����
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;//����ռ�ձȼ����Ƚ�BӰ�ӼĴ���
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;//����ռ�ձȼ����Ƚ�AӰ�ӼĴ���
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;//��������Ϊ0ʱ���رȽϼĴ���B
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;//��������Ϊ0ʱ���رȽϼĴ���A

	//���ģ�����ã�
	//���A���ƼĴ���AQCTLA����
	//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1A����:���¼�����Ƚ�ֵ���ʱ�ø�
	EPwm1Regs.AQCTLA.bit.CAD =AQ_SET;//AQ_SET;
	//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1A����:���ϼ�����Ƚ�ֵ���ʱ�õ�	
	EPwm1Regs.AQCTLA.bit.CAU =AQ_CLEAR;//AQ_CLEAR;
	//���ü�����ֵ����ռ�ձ��趨ֵCMPBʱ��EPWM1A����:����Ӧ
	EPwm1Regs.AQCTLA.bit.CBD =AQ_NO_ACTION;//AQ_NO_ACTION;
	//���ü�����ֵ����ռ�ձ��趨ֵCMPBʱ��EPWM1A����:����Ӧ
	EPwm1Regs.AQCTLA.bit.CBU =AQ_NO_ACTION;//AQ_NO_ACTION;
	//���ü�����ֵ����ʱ������ʱEPWM1A����������Ӧ
	EPwm1Regs.AQCTLA.bit.PRD =AQ_NO_ACTION;
	//���ü�����ֵ����0ʱEPWM1A����������Ӧ
	EPwm1Regs.AQCTLA.bit.ZRO =AQ_NO_ACTION;

	//���B���ƼĴ���AQCTLB����
	//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1B����:���¼�����Ƚ�ֵ���ʱ�ø�
	EPwm1Regs.AQCTLB.bit.CAD =AQ_CLEAR;//AQ_CLEAR;
	//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1B����:���ϼ�����Ƚ�ֵ���ʱ�õ�
	EPwm1Regs.AQCTLB.bit.CAU =AQ_SET;//AQ_SET;
	//���ü�����ֵ���ڱȽ��趨ֵCMPBʱ��E/PWM1B����:����Ӧ
	EPwm1Regs.AQCTLB.bit.CBD =AQ_NO_ACTION;
	//���ü�����ֵ���ڱȽ��趨ֵCMPBʱ��EPWM1B����:����Ӧ
	EPwm1Regs.AQCTLB.bit.CBU =AQ_NO_ACTION;
	//���ü�����ֵ����ʱ������ʱEPWM1A����������Ӧ
	EPwm1Regs.AQCTLB.bit.PRD =AQ_NO_ACTION;
	//���ü�����ֵ����0ʱEPWM1A����������Ӧ
	EPwm1Regs.AQCTLB.bit.ZRO =AQ_NO_ACTION;

	EPwm1Regs.CMPA.half.CMPA= PWM_HALF ;//��ʼ����50%��ռ�ձ�
	//��������������ǿ��������ƼĴ���AQSFRC����
   EPwm1Regs.AQSFRC.bit.RLDCSF = 3;//��������
	//�ر�PWM1
  //EPwm1Regs.AQCSFRC.all = 0x0009;   //�����������Ϲ��Ӻ��¹��Ӷ��������ֵ͵�ƽ

	EPwm1Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA��������,B�½����ӳ��ź�Դ
	EPwm1Regs.DBCTL.bit.POLSEL = 2;	//���Կ��ƣ�EPWMxB ��ת��EPWMxA����ת
	EPwm1Regs.DBCTL.bit.OUT_MODE = 3; //�������ģʽ����

	//�����������ӳټĴ���DBRED����
 	EPwm1Regs.DBRED = DEAD_time;//����ʱ��:1us=DBFED*TTBCLK
 	//�����½����ӳټĴ���DBFED����
 	EPwm1Regs.DBFED = DEAD_time;//����ʱ��: 1us=DBFED*TTBCLK

	//PWMն�����ƼĴ���PCCTL���ã��ݲ���
	//���ϲ�׽�����ã��ݲ���

	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;//PWM�жϴ�����1��
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;//pwm�ж�ʱ�̣�������ֵ=����ֵ
	EPwm1Regs.ETSEL.bit.INTEN =0; //disable INT

	/*ʹ��EPWMxSOCA��Ϊ ADC ת����������*/
	EPwm1Regs.ETSEL.bit.SOCAEN=1;
	/*TBCTR=0ʱ����SOCA�ź�*/
	EPwm1Regs.ETSEL.bit.SOCASEL=1;
	/*��һ���¼�����ʱ������SOCA�ź�*/
	EPwm1Regs.ETPS.bit.SOCAPRD=1;

}
/*��ʼ��EPwm2����*/
void InitEPwm2(void)
{

//��ʼ��EPWM2������B�ࡣBH��EPWM1A��BL-EPWM1B
	//ʱ��ģ��Ĵ������ã�
	    // ����ʱ�����ڼĴ���TBPRD
		//ע�⣺���������¼���ģʽ�У���ֵ��PWM���ڵ�1/2������ģʽ�¸�ֵ��PWM������
	    EPwm2Regs.TBPRD = PWM_TIMER_TBPRD;  // ���� Set timer period TBCLKs  40KHz, 25us
		//����ʱ����λ�Ĵ���TBPHS
	    EPwm2Regs.TBPHS.all = 0x0000;   // ��ʼ��λΪ0
		//����ʱ��������TBCTR
	    EPwm2Regs.TBCTR = 0x0000;       // ����ʱ��������
		//����ʱ�����ƼĴ���
		EPwm2Regs.TBCTL.bit.PHSEN = 0;//��λ�ǿ��ƽ�ֹ
		EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;//����ʱ��Ԥ��Ƶ,0:����Ƶ
	  	EPwm2Regs.TBCTL.bit.CLKDIV = 0;//ʱ��Ԥ��Ƶ�����ã�TBCLK=SYSCLKOUT/(HSPCLKDIV*CLKDIV)��0:����Ƶ

		EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;//��ֹͬ���ź����
		EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;//����ʱ�����ڼĴ���ʱʹ�û���Ĵ�������ʹ��ʱ�����ڼĴ�����Ӱ�ӼĴ���
		EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//����ģʽΪ��������������

		//�����Ƚ�ģ��Ĵ�������:
		//�����ȽϿ��ƼĴ���CMPCTL����
		EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;//����ռ�ձȼ����Ƚ�BӰ�ӼĴ���
		EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;//����ռ�ձȼ����Ƚ�AӰ�ӼĴ���
		EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;//��������Ϊ0ʱ���رȽϼĴ���B
		EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;//��������Ϊ0ʱ���رȽϼĴ���A

		//���ģ�����ã�
		//���A���ƼĴ���AQCTLA����
		//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1A����:���¼�����Ƚ�ֵ���ʱ�ø�
		EPwm2Regs.AQCTLA.bit.CAD =AQ_SET;//AQ_SET;
		//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1A����:���ϼ�����Ƚ�ֵ���ʱ�õ�
		EPwm2Regs.AQCTLA.bit.CAU =AQ_CLEAR;//AQ_CLEAR;
		//���ü�����ֵ����ռ�ձ��趨ֵCMPBʱ��EPWM1A����:����Ӧ
		EPwm2Regs.AQCTLA.bit.CBD =AQ_NO_ACTION;//AQ_NO_ACTION;
		//���ü�����ֵ����ռ�ձ��趨ֵCMPBʱ��EPWM1A����:����Ӧ
		EPwm2Regs.AQCTLA.bit.CBU =AQ_NO_ACTION;//AQ_NO_ACTION;
		//���ü�����ֵ����ʱ������ʱEPWM1A����������Ӧ
		EPwm2Regs.AQCTLA.bit.PRD =AQ_NO_ACTION;
		//���ü�����ֵ����0ʱEPWM1A����������Ӧ
		EPwm2Regs.AQCTLA.bit.ZRO =AQ_NO_ACTION;

		//���B���ƼĴ���AQCTLB����
		//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1B����:���¼�����Ƚ�ֵ���ʱ�ø�
		EPwm2Regs.AQCTLB.bit.CAD =AQ_CLEAR;//AQ_CLEAR;
		//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1B����:���ϼ�����Ƚ�ֵ���ʱ�õ�
		EPwm2Regs.AQCTLB.bit.CAU =AQ_SET;//AQ_SET;
		//���ü�����ֵ���ڱȽ��趨ֵCMPBʱ��E/PWM1B����:����Ӧ
		EPwm2Regs.AQCTLB.bit.CBD =AQ_NO_ACTION;
		//���ü�����ֵ���ڱȽ��趨ֵCMPBʱ��EPWM1B����:����Ӧ
		EPwm2Regs.AQCTLB.bit.CBU =AQ_NO_ACTION;
		//���ü�����ֵ����ʱ������ʱEPWM1A����������Ӧ
		EPwm2Regs.AQCTLB.bit.PRD =AQ_NO_ACTION;
		//���ü�����ֵ����0ʱEPWM1A����������Ӧ
		EPwm2Regs.AQCTLB.bit.ZRO =AQ_NO_ACTION;

		EPwm2Regs.CMPA.half.CMPA= PWM_HALF/2 ;//��ʼ����50%��ռ�ձ�
		//��������������ǿ��������ƼĴ���AQSFRC����
	   EPwm2Regs.AQSFRC.bit.RLDCSF = 3;//��������
		//�ر�PWM2
	  //EPwm2Regs.AQCSFRC.all = 0x0009;   //�����������Ϲ��Ӻ��¹��Ӷ��������ֵ͵�ƽ

		EPwm2Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA��������,B�½����ӳ��ź�Դ
		EPwm2Regs.DBCTL.bit.POLSEL = 2;	//���Կ��ƣ�EPWMxB ��ת��EPWMxA����ת
		EPwm2Regs.DBCTL.bit.OUT_MODE = 3; //�������ģʽ����

		//�����������ӳټĴ���DBRED����
	 	EPwm2Regs.DBRED = DEAD_time;//����ʱ��:1us=DBFED*TTBCLK
	 	//�����½����ӳټĴ���DBFED����
	 	EPwm2Regs.DBFED = DEAD_time;//����ʱ��: 1us=DBFED*TTBCLK

		//PWMն�����ƼĴ���PCCTL���ã��ݲ���
		//���ϲ�׽�����ã��ݲ���

		EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;//PWM�жϴ�����1��
		EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;//pwm�ж�ʱ�̣�������ֵ=0
		EPwm2Regs.ETSEL.bit.INTEN =0; //disable INT

}
/*��ʼ��EPwm3����*/
void InitEPwm3(void)
{

//��ʼ��EPWM3������A�ࡣAH��EPWM1A��AL-EPWM1B
	//ʱ��ģ��Ĵ������ã�
	    // ����ʱ�����ڼĴ���TBPRD
		//ע�⣺���������¼���ģʽ�У���ֵ��PWM���ڵ�1/2������ģʽ�¸�ֵ��PWM������
	    EPwm3Regs.TBPRD = PWM_TIMER_TBPRD;  // ���� Set timer period TBCLKs  40KHz, 25us
		//����ʱ����λ�Ĵ���TBPHS
	    EPwm3Regs.TBPHS.all = 0x0000;   // ��ʼ��λΪ0
		//����ʱ��������TBCTR
	    EPwm3Regs.TBCTR = 0x0000;       // ����ʱ��������
		//����ʱ�����ƼĴ���
		EPwm3Regs.TBCTL.bit.PHSEN = 0;//��λ�ǿ��ƽ�ֹ
		EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0;//����ʱ��Ԥ��Ƶ,0:����Ƶ
	  	EPwm3Regs.TBCTL.bit.CLKDIV = 0;//ʱ��Ԥ��Ƶ�����ã�TBCLK=SYSCLKOUT/(HSPCLKDIV*CLKDIV)��0:����Ƶ

		EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;//��ֹͬ���ź����
		EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;//����ʱ�����ڼĴ���ʱʹ�û���Ĵ�������ʹ��ʱ�����ڼĴ�����Ӱ�ӼĴ���
		EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;//����ģʽΪ��������������

		//�����Ƚ�ģ��Ĵ�������:
		//�����ȽϿ��ƼĴ���CMPCTL����
		EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;//����ռ�ձȼ����Ƚ�BӰ�ӼĴ���
		EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;//����ռ�ձȼ����Ƚ�AӰ�ӼĴ���
		EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;//��������Ϊ0ʱ���رȽϼĴ���B
		EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;//��������Ϊ0ʱ���رȽϼĴ���A

		//���ģ�����ã�
		//���A���ƼĴ���AQCTLA����
		//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1A����:���¼�����Ƚ�ֵ���ʱ�ø�
		EPwm3Regs.AQCTLA.bit.CAD =AQ_SET;//AQ_SET;
		//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1A����:���ϼ�����Ƚ�ֵ���ʱ�õ�
		EPwm3Regs.AQCTLA.bit.CAU =AQ_CLEAR;//AQ_CLEAR;
		//���ü�����ֵ����ռ�ձ��趨ֵCMPBʱ��EPWM1A����:����Ӧ
		EPwm3Regs.AQCTLA.bit.CBD =AQ_NO_ACTION;//AQ_NO_ACTION;
		//���ü�����ֵ����ռ�ձ��趨ֵCMPBʱ��EPWM1A����:����Ӧ
		EPwm3Regs.AQCTLA.bit.CBU =AQ_NO_ACTION;//AQ_NO_ACTION;
		//���ü�����ֵ����ʱ������ʱEPWM1A����������Ӧ
		EPwm3Regs.AQCTLA.bit.PRD =AQ_NO_ACTION;
		//���ü�����ֵ����0ʱEPWM1A����������Ӧ
		EPwm3Regs.AQCTLA.bit.ZRO =AQ_NO_ACTION;

		//���B���ƼĴ���AQCTLB����
		//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1B����:���¼�����Ƚ�ֵ���ʱ�ø�
		EPwm3Regs.AQCTLB.bit.CAD =AQ_CLEAR;//AQ_CLEAR;
		//���ü�����ֵ���ڱȽ��趨ֵCMPAʱ��EPWM1B����:���ϼ�����Ƚ�ֵ���ʱ�õ�
		EPwm3Regs.AQCTLB.bit.CAU =AQ_SET;//AQ_SET;
		//���ü�����ֵ���ڱȽ��趨ֵCMPBʱ��E/PWM1B����:����Ӧ
		EPwm3Regs.AQCTLB.bit.CBD =AQ_NO_ACTION;
		//���ü�����ֵ���ڱȽ��趨ֵCMPBʱ��EPWM1B����:����Ӧ
		EPwm3Regs.AQCTLB.bit.CBU =AQ_NO_ACTION;
		//���ü�����ֵ����ʱ������ʱEPWM1A����������Ӧ
		EPwm3Regs.AQCTLB.bit.PRD =AQ_NO_ACTION;
		//���ü�����ֵ����0ʱEPWM1A����������Ӧ
		EPwm3Regs.AQCTLB.bit.ZRO =AQ_NO_ACTION;

		EPwm3Regs.CMPA.half.CMPA= PWM_HALF/3 ;//��ʼ����50%��ռ�ձ�
		//��������������ǿ��������ƼĴ���AQSFRC����
	   EPwm3Regs.AQSFRC.bit.RLDCSF = 3;//��������
		//�ر�PWM3
	  //EPwm3Regs.AQCSFRC.all = 0x0009;   //�����������Ϲ��Ӻ��¹��Ӷ��������ֵ͵�ƽ

		EPwm3Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA��������,B�½����ӳ��ź�Դ
		EPwm3Regs.DBCTL.bit.POLSEL = 2;	//���Կ��ƣ�EPWMxB ��ת��EPWMxA����ת
		EPwm3Regs.DBCTL.bit.OUT_MODE = 3; //�������ģʽ����

		//�����������ӳټĴ���DBRED����
	 	EPwm3Regs.DBRED = DEAD_time;//����ʱ��:1us=DBFED*TTBCLK
	 	//�����½����ӳټĴ���DBFED����
	 	EPwm3Regs.DBFED = DEAD_time;//����ʱ��: 1us=DBFED*TTBCLK

		//PWMն�����ƼĴ���PCCTL���ã��ݲ���
		//���ϲ�׽�����ã��ݲ���

		EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;//PWM�жϴ�����1��
		EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;//pwm�ж�ʱ�̣�������ֵ=0
		EPwm3Regs.ETSEL.bit.INTEN =0; //disable INT

}

void Init_EPWM(void)
{
	InitEPwmGpio();
	InitTzGpio();
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
