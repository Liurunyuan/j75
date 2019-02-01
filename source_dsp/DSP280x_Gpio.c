//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example. 
	/*Gpio初始化函数*/
void InitGpio(void)
{
    EALLOW;
   // Each GPIO pin can be: 
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs 

//以下配置PWM1/2/3的管脚
  	// 使能GPIO0-GPIO5的PWM1-3功能 

    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;  //输出强制为低
    GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;  //输出强制为低
    GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;  //输出强制为低
    GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;  //输出强制为低
    GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;  //输出强制为低
    GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;  //输出强制为低

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // 使能 pullup on GPIO0
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;   // 使能 pullup on GPIO1
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // 使能 pullup on GPIO2
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // 使能 pullup on GPIO3
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // 使能 pullup on GPIO4
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // 使能 pullup on GPIO5
 	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;	 //将GPIO0 引脚配置为:EPWM1A (OUT), ePWM1 输出A
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;	 //将GPIO1 引脚配置为:EPWM1B (OUT), ePWM1 输出B
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;	 //将GPIO2 引脚配置为:EPWM2A (OUT), ePWM2 输出A 
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;	 //将GPIO3 引脚配置为:EPWM2B (OUT)，ePWM2 输出B
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;  //将GPIO4 引脚配置为:EPWM3A (OUT)，ePWM3 输出A。
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;  //将GPIO5 引脚配置为:EPWM3B (OUT)，ePWM3 输出B。


	/*GPIO12为BREAK_K信号,临时设置为输入*/
	GpioDataRegs.GPASET.bit.GPIO12 = 1;   // BREAK_K信号,初始状态为高电平 ，不泄放
	GpioCtrlRegs.GPAPUD.bit.GPIO12  = 0;   //使用内部上拉
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;  //将GPIO12引脚配置为:(I/O) BREAK_K信号，泄放使能
	GpioCtrlRegs.GPADIR.bit.GPIO12  = 0;   //配置为输入


	/*GPIO23为WDI信号*/
	GpioCtrlRegs.GPAPUD.bit.GPIO23  = 1;   //禁止使用内部上拉
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;  //将GPIO23引脚配置为:(I/O) WDI信号，看门狗复位信号。
	GpioCtrlRegs.GPADIR.bit.GPIO23  = 1;   //配置为输出
	GpioDataRegs.GPASET.bit.GPIO23 = 1;   // WDI信号,初始状态为高电平

     /*分别配置GPIO24，GPIO25，GPIO26为ECAP1，ECAP2，ECAP3*/
	 GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;     /* Enable pull-up on GPIO24 (CAP1)*/
	 GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;    /* Configure GPIO24 as CAP1*/
	 GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;     /* Enable pull-up on GPIO25 (CAP2)*/
	 GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;    /* Configure GPIO25 as CAP2*/
	 GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;     /* Enable pull-up on GPIO26 (CAP3)*/
	 GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    /* Configure GPIO26 as CAP3*/

	//使能GPIO27-GPIO28备用接口，设置为输入
	GpioCtrlRegs.GPAPUD.bit.GPIO27  = 1;  //禁止使用内部上拉
	GpioCtrlRegs.GPAPUD.bit.GPIO28  = 1;  //禁止使用内部上拉
	GpioCtrlRegs.GPAMUX2.bit.GPIO27  =0;  //将GPIO27引脚配置为通用IO口
	GpioCtrlRegs.GPAMUX2.bit.GPIO28  =0;  //将GPIO28引脚配置为通用IO口
	GpioCtrlRegs.GPADIR.bit.GPIO27  = 0;  // 将GPIO27引脚配置为输入
	GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;  // 将GPIO28引脚配置为输入
	GpioDataRegs.GPACLEAR.bit.GPIO27  = 1;   //清零数据寄存器
	GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;   //清零数据寄存器


	/*GPIO29为EX_DOG看门狗信号*/
	GpioCtrlRegs.GPAPUD.bit.GPIO29  = 0;   //使用内部上拉
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0;  //将GPIO29引脚配置为:(I/O)EX_DOG看门狗信号，EX_DOG看门狗复位信号。
	GpioCtrlRegs.GPADIR.bit.GPIO29 = 1;   //配置为输出
	GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;   // EX_DOG看门狗信号,初始状态为低电平



	//使能GPIO32接口，ENK硬件故障信号，设置为输入，低电平有故障
	GpioCtrlRegs.GPBPUD.bit.GPIO32  = 1;  //禁止使用内部上拉
	GpioCtrlRegs.GPBMUX1.bit.GPIO32  =0;  //将GPIO32引脚配置为通用IO口
	GpioCtrlRegs.GPBDIR.bit.GPIO32  = 0;  // 将GPIO32引脚配置为输入
	GpioDataRegs.GPBDAT.bit.GPIO32  = 0;   //清零数据寄存器

	/*GPIO14为BIT巡检通道选择,ADDR_B*/
	GpioCtrlRegs.GPAPUD.bit.GPIO14  = 1;   //禁止使用内部上拉
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;  //将GPIO14引脚配置为:(I/O) BIT巡检通道选择
	GpioCtrlRegs.GPADIR.bit.GPIO14  = 1;   //配置为输出
	GpioDataRegs.GPASET.bit.GPIO14 = 1;   //BIT巡检通道选择,初始状态为高电平

    /*GPIO15为BIT巡检通道选择,ADDR_A*/
	GpioCtrlRegs.GPAPUD.bit.GPIO15  = 1;   //禁止使用内部上拉
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;  //将GPIO15引脚配置为:(I/O) BIT巡检通道选择
	GpioCtrlRegs.GPADIR.bit.GPIO15  = 1;   //配置为输出
	GpioDataRegs.GPASET.bit.GPIO15 = 1;   //BIT巡检通道选择,初始状态为高电平

	/*GPIO34为BIT巡检地址C通道信号,ADDR_C*/
	GpioCtrlRegs.GPBPUD.bit.GPIO34  = 1;   //禁止使用内部上拉
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;   //将GPIO34引脚配置为:(I/O) BIT巡检通道选择。
	GpioCtrlRegs.GPBDIR.bit.GPIO34  = 1;   //配置为输出
	GpioDataRegs.GPBSET.bit.GPIO34  = 1;   //初始状态为高电平

    /*扩展口初始化*/
    GpioCtrlRegs.GPAMUX2.bit.GPIO16  = 0;  //将GPIO16引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO16   = 1;  // 将GPIO16引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // 使能 pullup on GPIO16
    GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX2.bit.GPIO17  = 0;  //将GPIO17引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO17   = 1;  // 将GPIO17引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // 使能 pullup on GPIO17
    GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;	 //将GPIO6引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO6  = 1;  // 将GPIO6引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // 使能 pullup on GPIO6
    GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX2.bit.GPIO19  = 0;  //将GPIO19引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO19   = 1;  // 将GPIO19引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // 使能 pullup on GPIO19
    GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;	 //将GPIO7引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO7  = 1;  // 将GPIO7引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;   // 使能 pullup on GPIO7
    GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;	 //将GPIO8引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO8  = 1;  // 将GPIO8引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // 使能 pullup on GPIO8
    GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX1.bit.GPIO11  = 0;  //将GPIO11引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO11   = 1;  // 将GPIO11引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;   // 使能 pullup on GPIO11
    GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;	 //将GPIO9引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO9  = 1;  // 将GPIO9引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // 使能 pullup on GPIO9
    GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX2.bit.GPIO18  = 0;  //将GPIO18引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO18   = 1;  // 将GPIO18引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // 使能 pullup on GPIO18
    GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX2.bit.GPIO20  = 0;  //将GPIO20引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO20   = 1;  // 将GPIO20引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // 使能 pullup on GPIO20
    GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;	 //将GPIO10引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO10  = 1;  // 将GPIO10引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;   // 使能 pullup on GPIO10
    GpioDataRegs.GPACLEAR.bit.GPIO20 = 1;  //输出强制为低

    GpioCtrlRegs.GPAMUX2.bit.GPIO21  = 0;  //将GPIO21引脚配置为通用IO口
    GpioCtrlRegs.GPADIR.bit.GPIO21   = 1;  // 将GPIO21引脚配置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // 使能 pullup on GPIO21
    GpioDataRegs.GPACLEAR.bit.GPIO21 = 1;  //输出强制为低
    EDIS;
}	
void InitOutputPin(void){
	/*Read the circuit diagram and find which Pin need to init as Output GPIO, finsish the code here*/
	/*
	 * GPIO12
	 * Pin index:			1
	 * Name in circuit:		BREAK_K
	 */
	GpioCtrlRegs.GPAPUD.bit.GPIO12  = 1;   //禁止使用内部上拉
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;  //将GPIO23引脚配置为:(I/O) WDI信号，看门狗复位信号。
	GpioCtrlRegs.GPADIR.bit.GPIO12  = 1;   //配置为输出
	GpioDataRegs.GPASET.bit.GPIO12 = 1;   // WDI信号,初始状态为高电平

	/*
	 * GPIO31
	 * Pin index:			7
	 * Name in circuit:		BREAK_K
	 */
	GpioCtrlRegs.GPAPUD.bit.GPIO13  = 1;   //禁止使用内部上拉
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;  //将GPIO23引脚配置为:(I/O) WDI信号，看门狗复位信号。
	GpioCtrlRegs.GPADIR.bit.GPIO13  = 1;   //配置为输出
	GpioDataRegs.GPASET.bit.GPIO13 = 1;   // WDI信号,初始状态为高电平

	/*
	 * GPIO34
	 * Pin index:			43
	 * Name in circuit:		VDD3.3V
	 */
	GpioCtrlRegs.GPAPUD.bit.GPIO13  = 1;   //禁止使用内部上拉
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;  //将GPIO23引脚配置为:(I/O) WDI信号，看门狗复位信号。
	GpioCtrlRegs.GPADIR.bit.GPIO13  = 1;   //配置为输出
	GpioDataRegs.GPASET.bit.GPIO13 = 1;   // WDI信号,初始状态为高电平



	/*GPIO23为WDI信号*/
	GpioCtrlRegs.GPAPUD.bit.GPIO23  = 1;   //禁止使用内部上拉
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;  //将GPIO23引脚配置为:(I/O) WDI信号，看门狗复位信号。
	GpioCtrlRegs.GPADIR.bit.GPIO23  = 1;   //配置为输出
	GpioDataRegs.GPASET.bit.GPIO23 = 1;   // WDI信号,初始状态为高电平
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
