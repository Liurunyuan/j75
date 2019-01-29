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
/***���������״̬����***/
#define INITIALIZE_STU  0x55   /*��ʼ��״̬*/
#define STOP_STU        0xAA   /*ͣ���ȴ�״̬*/
#define ALARM_STU       0xA5   /*���ϱ���״̬*/
#define RUN_STU         0x5A   /*��������״̬*/
#define SLEEP_STU       0x96   /*���ߵȴ�״̬*/
/***���������״̬�������***/

/********g_Error_Massageλ����********/
#define ERROR_SOFTWARE   0x0001   /*�������*/
#define ERROR_HALL       0x0002   /*����λ���źŹ���*/
#define ERROR_OC_PU      0x0004   /*��������*/
#define ERROR_NO_LOAD    0x0008   /*���ع���*/
#define ERROR_OV         0x0010   /*��ѹ����*/
#define ERROR_UV         0x0020   /*Ƿѹ����*/
#define ERROR_OT         0x0040   /*���¹���*/
#define ERROR_IN_POWER   0x0080   /*�ڲ���Դ����*/
#define ERROR_HARDWARE   0x0100   /*Ӳ������*/
#define ERROR_ENK_LOW    0x0200   /*Ӳ�������ź�ENKΪ�͵�ƽ*/
#define ERROR_SYX_JC     0x0400   /*�ϵ翪ʼ��������е�������*/
#define ERROR_IA_JIZHUN  0x0800   /*A�������λ���޴���*/
#define ERROR_IB_JIZHUN  0x1000   /*B�������λ���޴���*/
#define ERROR_IC_JIZHUN  0x2000   /*C�������λ���޴���*/
#define ERROR_IBUS_JIZHUN 0x4000   /*ĸ�ߵ�����λ���޴���*/
#define ERROR_ENK_HIGH   0x8000    /*Ӳ�������ź�ENKΪ�ߵ�ƽ*/
#define ERROR_OC_RUN1     0x10000   /*��������*/
#define ERROR_OC_RUN2     0x20000   /*��������*/
#define ERROR_OC_RUN3     0x40000   /*��������*/
#define ERROR_OT_T1       0x80000   /*T1���¹���*/
#define ERROR_OT_T2       0x100000  /*T2���¹���*/
#define ERROR_OT_PCBTEMP  0x200000  /*PCBTEMP���¹���*/
/********g_Error_Massageλ�������********/

/********g_Warning1_Massageλ����********/
#define PUW_BREAK_K     0x00000001   /*��ʼ��״̬����*/
#define PUW_EN_OUT_INT  0x00000002   /*��ʼ��״̬����*/
#define PUW_SPICLKA     0x00000004   /*��ʼ��״̬����*/
#define PUW_OUTK        0x00000008   /*��ʼ��״̬����*/
#define PUW_WDI         0x00000010   /*��ʼ��״̬����*/
#define PUW_GND         0x00000020   /*��ʼ��״̬����*/
#define PUW_EX_DOG      0x00000040   /*��ʼ��״̬����*/
#define PUW_KZ_EN_P     0x00000080   /*��ʼ��״̬����*/
#define PUW_KZ_EN_N     0x00000100   /*��ʼ��״̬����*/
#define PUW_CLR_OC      0x00000200   /*��ʼ��״̬����*/
#define RUN_HALL_SX     0x00000400   /*�����ڼ�����ź�ʱ�����*/
#define PUW_JIZHUN      0x00000800   /*��ʼ��ʱ�����������Ļ�׼����*/
#define RUN_HALL_SX_CLR 0x000003FF   /*������л����ź�ʱ�����*/
#define PUW_UBUS        0x00001000   /*��ʼ��ʱĸ�ߵ�ѹԽ��*/
#define RUN_IX_FLT      0x00002000   /*����ʱA��B��C������쳣*/
#define RUN_UBUS_FLT    0x00004000   /*����ʱĸ�ߵ�ѹԽ��*/
/********g_Warning1_Massageλ�������********/

/********g_AN_COM_Massageλ����********/
#define PUW_U11_TEMP    0x0001   /*����ʱU11����*/
#define PUW_IMAX        0x0002   /*����ʱ����������IMAX�쳣*/
#define PUW_RT1FLT      0x0004   /*����ʱ��������RT1�쳣*/
#define PUW_1D8LOADFLT  0x0008   /*����ʱ1.8V LOAD�쳣*/
#define PUW_5VFLT       0x0010   /*����ʱ5V��Դ�쳣*/
#define PUW_12VFLT      0x0020   /*����ʱ12V��Դ�쳣*/
#define PUW_IMIN        0x0040   /*����ʱ����������IMIN�쳣*/
#define PUW_RT2FLT      0x0080   /*����ʱ��������RT2�쳣*/
#define RUN_U11_TEMP    0x0100   /*����ʱU11����*/
#define RUN_IMAX        0x0200   /*����ʱ����������IMAX�쳣*/
#define RUN_RT1FLT      0x0400   /*����ʱ��������RT1�쳣*/
#define RUN_1D8LOADFLT  0x0800   /*����ʱ1.8V LOAD�쳣*/
#define RUN_5VFLT       0x1000   /*����ʱ5V��Դ�쳣*/
#define RUN_12VFLT      0x2000   /*����ʱ12V��Դ�쳣*/
#define RUN_IMIN        0x4000   /*����ʱ����������IMIN�쳣*/
#define RUN_RT2FLT      0x8000   /*����ʱ��������RT2�쳣*/
/********g_AN_COM_Massageλ�������********/

/***ADC��ض���***/
#define ADC_usDELAY  5000L
#define FALSE        0
/*����ADC��DEBUG*/
#define BUF_SIZE   1024  /* Sample buffer size*/
/*����ADC�ý���DEBUG*/
/*ϵͳ��Ƶ/Hz*/
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



