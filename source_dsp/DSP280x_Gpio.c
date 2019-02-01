//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example. 
	/*Gpio��ʼ������*/
void InitGpio(void)
{
    EALLOW;
   // Each GPIO pin can be: 
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs 

//��������PWM1/2/3�Ĺܽ�
  	// ʹ��GPIO0-GPIO5��PWM1-3���� 

    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;  //���ǿ��Ϊ��
    GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;  //���ǿ��Ϊ��
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;  //���ǿ��Ϊ��
    GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;  //���ǿ��Ϊ��
    GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;  //���ǿ��Ϊ��
    GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // ʹ�� pullup on GPIO0
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;   // ʹ�� pullup on GPIO1
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // ʹ�� pullup on GPIO2
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // ʹ�� pullup on GPIO3
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // ʹ�� pullup on GPIO4
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // ʹ�� pullup on GPIO5
 	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;	 //��GPIO0 ��������Ϊ:EPWM1A (OUT), ePWM1 ���A
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;	 //��GPIO1 ��������Ϊ:EPWM1B (OUT), ePWM1 ���B
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;	 //��GPIO2 ��������Ϊ:EPWM2A (OUT), ePWM2 ���A 
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;	 //��GPIO3 ��������Ϊ:EPWM2B (OUT)��ePWM2 ���B
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;  //��GPIO4 ��������Ϊ:EPWM3A (OUT)��ePWM3 ���A��
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;  //��GPIO5 ��������Ϊ:EPWM3B (OUT)��ePWM3 ���B��


	/*GPIO12ΪBREAK_K�ź�,��ʱ����Ϊ����*/
	GpioDataRegs.GPASET.bit.GPIO12 = 1;   // BREAK_K�ź�,��ʼ״̬Ϊ�ߵ�ƽ ����й��
	GpioCtrlRegs.GPAPUD.bit.GPIO12  = 0;   //ʹ���ڲ�����
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;  //��GPIO12��������Ϊ:(I/O) BREAK_K�źţ�й��ʹ��
	GpioCtrlRegs.GPADIR.bit.GPIO12  = 0;   //����Ϊ����


	/*GPIO23ΪWDI�ź�*/
	GpioCtrlRegs.GPAPUD.bit.GPIO23  = 1;   //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;  //��GPIO23��������Ϊ:(I/O) WDI�źţ����Ź���λ�źš�
	GpioCtrlRegs.GPADIR.bit.GPIO23  = 1;   //����Ϊ���
	GpioDataRegs.GPASET.bit.GPIO23 = 1;   // WDI�ź�,��ʼ״̬Ϊ�ߵ�ƽ

     /*�ֱ�����GPIO24��GPIO25��GPIO26ΪECAP1��ECAP2��ECAP3*/
	 GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;     /* Enable pull-up on GPIO24 (CAP1)*/
	 GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;    /* Configure GPIO24 as CAP1*/
	 GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;     /* Enable pull-up on GPIO25 (CAP2)*/
	 GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;    /* Configure GPIO25 as CAP2*/
	 GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;     /* Enable pull-up on GPIO26 (CAP3)*/
	 GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    /* Configure GPIO26 as CAP3*/

	//ʹ��GPIO27-GPIO28���ýӿڣ�����Ϊ����
	GpioCtrlRegs.GPAPUD.bit.GPIO27  = 1;  //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPAPUD.bit.GPIO28  = 1;  //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPAMUX2.bit.GPIO27  =0;  //��GPIO27��������Ϊͨ��IO��
	GpioCtrlRegs.GPAMUX2.bit.GPIO28  =0;  //��GPIO28��������Ϊͨ��IO��
	GpioCtrlRegs.GPADIR.bit.GPIO27  = 0;  // ��GPIO27��������Ϊ����
	GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;  // ��GPIO28��������Ϊ����
	GpioDataRegs.GPACLEAR.bit.GPIO27  = 1;   //�������ݼĴ���
	GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   //�������ݼĴ���


	/*GPIO29ΪEX_DOG���Ź��ź�*/
	GpioCtrlRegs.GPAPUD.bit.GPIO29  = 0;   //ʹ���ڲ�����
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0;  //��GPIO29��������Ϊ:(I/O)EX_DOG���Ź��źţ�EX_DOG���Ź���λ�źš�
	GpioCtrlRegs.GPADIR.bit.GPIO29 = 1;   //����Ϊ���
	GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // EX_DOG���Ź��ź�,��ʼ״̬Ϊ�͵�ƽ



	//ʹ��GPIO32�ӿڣ�ENKӲ�������źţ�����Ϊ���룬�͵�ƽ�й���
	GpioCtrlRegs.GPBPUD.bit.GPIO32  = 1;  //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPBMUX1.bit.GPIO32  =0;  //��GPIO32��������Ϊͨ��IO��
	GpioCtrlRegs.GPBDIR.bit.GPIO32  = 0;  // ��GPIO32��������Ϊ����
	GpioDataRegs.GPBDAT.bit.GPIO32  = 0;   //�������ݼĴ���

	/*GPIO14ΪBITѲ��ͨ��ѡ��,ADDR_B*/
	GpioCtrlRegs.GPAPUD.bit.GPIO14  = 1;   //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;  //��GPIO14��������Ϊ:(I/O) BITѲ��ͨ��ѡ��
	GpioCtrlRegs.GPADIR.bit.GPIO14  = 1;   //����Ϊ���
	GpioDataRegs.GPASET.bit.GPIO14 = 1;   //BITѲ��ͨ��ѡ��,��ʼ״̬Ϊ�ߵ�ƽ

    /*GPIO15ΪBITѲ��ͨ��ѡ��,ADDR_A*/
	GpioCtrlRegs.GPAPUD.bit.GPIO15  = 1;   //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;  //��GPIO15��������Ϊ:(I/O) BITѲ��ͨ��ѡ��
	GpioCtrlRegs.GPADIR.bit.GPIO15  = 1;   //����Ϊ���
	GpioDataRegs.GPASET.bit.GPIO15 = 1;   //BITѲ��ͨ��ѡ��,��ʼ״̬Ϊ�ߵ�ƽ

	/*GPIO34ΪBITѲ���ַCͨ���ź�,ADDR_C*/
	GpioCtrlRegs.GPBPUD.bit.GPIO34  = 1;   //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;   //��GPIO34��������Ϊ:(I/O) BITѲ��ͨ��ѡ��
	GpioCtrlRegs.GPBDIR.bit.GPIO34  = 1;   //����Ϊ���
	GpioDataRegs.GPBSET.bit.GPIO34  = 1;   //��ʼ״̬Ϊ�ߵ�ƽ

    /*��չ�ڳ�ʼ��*/
    GpioCtrlRegs.GPAMUX2.bit.GPIO16  = 0;  //��GPIO16��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO16   = 1;  // ��GPIO16��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // ʹ�� pullup on GPIO16
    GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX2.bit.GPIO17  = 0;  //��GPIO17��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO17   = 1;  // ��GPIO17��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // ʹ�� pullup on GPIO17
    GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;	 //��GPIO6��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO6  = 1;  // ��GPIO6��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // ʹ�� pullup on GPIO6
    GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX2.bit.GPIO19  = 0;  //��GPIO19��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO19   = 1;  // ��GPIO19��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // ʹ�� pullup on GPIO19
    GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;	 //��GPIO7��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO7  = 1;  // ��GPIO7��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;   // ʹ�� pullup on GPIO7
    GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;	 //��GPIO8��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO8  = 1;  // ��GPIO8��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // ʹ�� pullup on GPIO8
    GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX1.bit.GPIO11  = 0;  //��GPIO11��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO11   = 1;  // ��GPIO11��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;   // ʹ�� pullup on GPIO11
    GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;	 //��GPIO9��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO9  = 1;  // ��GPIO9��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // ʹ�� pullup on GPIO9
    GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX2.bit.GPIO18  = 0;  //��GPIO18��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO18   = 1;  // ��GPIO18��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // ʹ�� pullup on GPIO18
    GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX2.bit.GPIO20  = 0;  //��GPIO20��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO20   = 1;  // ��GPIO20��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // ʹ�� pullup on GPIO20
    GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;	 //��GPIO10��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO10  = 1;  // ��GPIO10��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;   // ʹ�� pullup on GPIO10
    GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;  //���ǿ��Ϊ��

    GpioCtrlRegs.GPAMUX2.bit.GPIO21  = 0;  //��GPIO21��������Ϊͨ��IO��
    GpioCtrlRegs.GPADIR.bit.GPIO21   = 1;  // ��GPIO21��������Ϊ���
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // ʹ�� pullup on GPIO21
    GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;  //���ǿ��Ϊ��
    EDIS;
}	
void InitOutputPin(void){
	/*Read the circuit diagram and find which Pin need to init as Output GPIO, finsish the code here*/
	/*
	 * GPIO12
	 * Pin index:			1
	 * Name in circuit:		BREAK_K
	 */
	GpioCtrlRegs.GPAPUD.bit.GPIO12  = 1;   //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;  //��GPIO23��������Ϊ:(I/O) WDI�źţ����Ź���λ�źš�
	GpioCtrlRegs.GPADIR.bit.GPIO12  = 1;   //����Ϊ���
	GpioDataRegs.GPASET.bit.GPIO12 = 1;   // WDI�ź�,��ʼ״̬Ϊ�ߵ�ƽ

	/*
	 * GPIO31
	 * Pin index:			7
	 * Name in circuit:		BREAK_K
	 */
	GpioCtrlRegs.GPAPUD.bit.GPIO13  = 1;   //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;  //��GPIO23��������Ϊ:(I/O) WDI�źţ����Ź���λ�źš�
	GpioCtrlRegs.GPADIR.bit.GPIO13  = 1;   //����Ϊ���
	GpioDataRegs.GPASET.bit.GPIO13 = 1;   // WDI�ź�,��ʼ״̬Ϊ�ߵ�ƽ

	/*
	 * GPIO34
	 * Pin index:			43
	 * Name in circuit:		VDD3.3V
	 */
	GpioCtrlRegs.GPAPUD.bit.GPIO13  = 1;   //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;  //��GPIO23��������Ϊ:(I/O) WDI�źţ����Ź���λ�źš�
	GpioCtrlRegs.GPADIR.bit.GPIO13  = 1;   //����Ϊ���
	GpioDataRegs.GPASET.bit.GPIO13 = 1;   // WDI�ź�,��ʼ״̬Ϊ�ߵ�ƽ



	/*GPIO23ΪWDI�ź�*/
	GpioCtrlRegs.GPAPUD.bit.GPIO23  = 1;   //��ֹʹ���ڲ�����
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;  //��GPIO23��������Ϊ:(I/O) WDI�źţ����Ź���λ�źš�
	GpioCtrlRegs.GPADIR.bit.GPIO23  = 1;   //����Ϊ���
	GpioDataRegs.GPASET.bit.GPIO23 = 1;   // WDI�ź�,��ʼ״̬Ϊ�ߵ�ƽ
}
void InitInputPin(void){

}
void Init_GPIO(){
	InitOutputPin();
	InitInputPin();
}

//===========================================================================
// End of file.
//===========================================================================
