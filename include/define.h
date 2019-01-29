/*烧入flash用*/

#define flash

/*烧入flash用结束*/
/***************************/
//PWM相关宏定义
//时基周期寄存器
//80MHz频率，40KHz斩波频率，则计数周期(80000/40)=2000
/***************************/
#define HIGH_PL 1
#define LOW_PL 0
#define PWM_TIMER_TBPRD 938 /*PWM时基周期寄存器的值*/
#define PWM_HALF  469        /*50%占空比对应的比较器A寄存器的初值*/
#define STAR_DUTY 0        /*电机运转时的初始占空比*/
#define DEAD_time 0         /*38---0.5uS=DBFED*TTBCLK*/
#define NO_ERROR	0	     /*无故障*/
/***电机控制器状态定义***/
#define INITIALIZE_STU  0x55   /*初始化状态*/
#define STOP_STU        0xAA   /*停机等待状态*/
#define ALARM_STU       0xA5   /*故障报警状态*/
#define RUN_STU         0x5A   /*正常运行状态*/
#define SLEEP_STU       0x96   /*休眠等待状态*/
/***电机控制器状态定义结束***/

/********g_Error_Massage位定义********/
#define ERROR_SOFTWARE   0x0001   /*软件故障*/
#define ERROR_HALL       0x0002   /*霍尔位置信号故障*/
#define ERROR_OC_PU      0x0004   /*过流故障*/
#define ERROR_NO_LOAD    0x0008   /*空载故障*/
#define ERROR_OV         0x0010   /*过压故障*/
#define ERROR_UV         0x0020   /*欠压故障*/
#define ERROR_OT         0x0040   /*过温故障*/
#define ERROR_IN_POWER   0x0080   /*内部电源故障*/
#define ERROR_HARDWARE   0x0100   /*硬件故障*/
#define ERROR_ENK_LOW    0x0200   /*硬件保护信号ENK为低电平*/
#define ERROR_SYX_JC     0x0400   /*上电开始电机试运行电流错误*/
#define ERROR_IA_JIZHUN  0x0800   /*A相电流零位超限错误*/
#define ERROR_IB_JIZHUN  0x1000   /*B相电流零位超限错误*/
#define ERROR_IC_JIZHUN  0x2000   /*C相电流零位超限错误*/
#define ERROR_IBUS_JIZHUN 0x4000   /*母线电流零位超限错误*/
#define ERROR_ENK_HIGH   0x8000    /*硬件保护信号ENK为高电平*/
#define ERROR_OC_RUN1     0x10000   /*过流故障*/
#define ERROR_OC_RUN2     0x20000   /*过流故障*/
#define ERROR_OC_RUN3     0x40000   /*过流故障*/
#define ERROR_OT_T1       0x80000   /*T1过温故障*/
#define ERROR_OT_T2       0x100000  /*T2过温故障*/
#define ERROR_OT_PCBTEMP  0x200000  /*PCBTEMP过温故障*/
/********g_Error_Massage位定义结束********/

/********g_Warning1_Massage位定义********/
#define PUW_BREAK_K     0x00000001   /*初始化状态错误*/
#define PUW_EN_OUT_INT  0x00000002   /*初始化状态错误*/
#define PUW_SPICLKA     0x00000004   /*初始化状态错误*/
#define PUW_OUTK        0x00000008   /*初始化状态错误*/
#define PUW_WDI         0x00000010   /*初始化状态错误*/
#define PUW_GND         0x00000020   /*初始化状态错误*/
#define PUW_EX_DOG      0x00000040   /*初始化状态错误*/
#define PUW_KZ_EN_P     0x00000080   /*初始化状态错误*/
#define PUW_KZ_EN_N     0x00000100   /*初始化状态错误*/
#define PUW_CLR_OC      0x00000200   /*初始化状态错误*/
#define RUN_HALL_SX     0x00000400   /*运行期间霍尔信号时序错误*/
#define PUW_JIZHUN      0x00000800   /*初始化时电流传感器的基准错误*/
#define RUN_HALL_SX_CLR 0x000003FF   /*清除运行霍尔信号时序错误*/
#define PUW_UBUS        0x00001000   /*初始化时母线电压越界*/
#define RUN_IX_FLT      0x00002000   /*运行时A、B、C相电流异常*/
#define RUN_UBUS_FLT    0x00004000   /*运行时母线电压越界*/
/********g_Warning1_Massage位定义结束********/

/********g_AN_COM_Massage位定义********/
#define PUW_U11_TEMP    0x0001   /*运行时U11过温*/
#define PUW_IMAX        0x0002   /*运行时过流保护限IMAX异常*/
#define PUW_RT1FLT      0x0004   /*运行时热敏电阻RT1异常*/
#define PUW_1D8LOADFLT  0x0008   /*运行时1.8V LOAD异常*/
#define PUW_5VFLT       0x0010   /*运行时5V电源异常*/
#define PUW_12VFLT      0x0020   /*运行时12V电源异常*/
#define PUW_IMIN        0x0040   /*运行时过流保护限IMIN异常*/
#define PUW_RT2FLT      0x0080   /*运行时热敏电阻RT2异常*/
#define RUN_U11_TEMP    0x0100   /*运行时U11过温*/
#define RUN_IMAX        0x0200   /*运行时过流保护限IMAX异常*/
#define RUN_RT1FLT      0x0400   /*运行时热敏电阻RT1异常*/
#define RUN_1D8LOADFLT  0x0800   /*运行时1.8V LOAD异常*/
#define RUN_5VFLT       0x1000   /*运行时5V电源异常*/
#define RUN_12VFLT      0x2000   /*运行时12V电源异常*/
#define RUN_IMIN        0x4000   /*运行时过流保护限IMIN异常*/
#define RUN_RT2FLT      0x8000   /*运行时热敏电阻RT2异常*/
/********g_AN_COM_Massage位定义结束********/

/***ADC相关定义***/
#define ADC_usDELAY  5000L
#define FALSE        0
/*调试ADC用DEBUG*/
#define BUF_SIZE   1024  /* Sample buffer size*/
/*调试ADC用结束DEBUG*/
/*系统主频/Hz*/
#define SYSCLKOUT 75000000
#define SPEED_MIN 2100000000
#define T_F -1
/*
#define A_JIZHUN_MAX 2291
#define A_JIZHUN_MIN 1805
#define B_JIZHUN_MAX 2248
#define B_JIZHUN_MIN 1848
#define C_JIZHUN_MAX 2248
#define C_JIZHUN_MIN 1848
#define I_BUS_JIZHUN_MAX 2348
#define I_BUS_JIZHUN_MIN 1748
*/
#define IZ_MAX 2291
#define IZ_MIN 1805

#define U1_LIM_MAX   2759
#define U1_LIM_MIN   1059
#define U2_LIM_MAX   2247
#define U2_LIM_MIN   973

#define IX_LIM_MAX   636
#define IX_LIM_MIN   0
#define IBUS_LIM_MAX 453
#define IBUS_LIM_MIN 35



