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




/***ADC相关定义***/
#define ADC_usDELAY  5000L

#define SYSCLKOUT 75000000




