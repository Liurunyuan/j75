/*����flash��*/

#define flash

/*����flash�ý���*/
/***************************/
//PWM��غ궨��
//ʱ�����ڼĴ���
//80MHzƵ�ʣ�40KHzն��Ƶ�ʣ����������(80000/40)=2000
/***************************/
#define HIGH_PL 1
#define LOW_PL 0
#define PWM_TIMER_TBPRD 938 /*PWMʱ�����ڼĴ�����ֵ*/
#define PWM_HALF  469        /*50%ռ�ձȶ�Ӧ�ıȽ���A�Ĵ����ĳ�ֵ*/
#define STAR_DUTY 0        /*�����תʱ�ĳ�ʼռ�ձ�*/
#define DEAD_time 0         /*38---0.5uS=DBFED*TTBCLK*/
#define NO_ERROR	0	     /*�޹���*/




/***ADC��ض���***/
#define ADC_usDELAY  5000L

#define SYSCLKOUT 75000000




