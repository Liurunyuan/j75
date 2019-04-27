/*
 * adc.h
 *
 *  Created on: 2019��2��14��
 *      Author: Administrator
 */

#ifndef ADC_H_
#define ADC_H_

#define MAX_ANALOG_CHANNEL (16)
typedef Uint16 (*UV)(void);


enum ADC_INDEX
{
	U_AN_3V3_A0 = 0,		//0
	AGND_A1,		//1
	I_AN_3V3_A2,			//2
	AGND_A3,		//3
	NO_USE_A4,		//4
	NO_USE_A5,			//5
	NO_USE_A6,		//6
	AGND_A7,		//7
	T_AN_3V3_B0,	//8
	NO_USE_B1,		//9
	NO_USE_B2,		//10
	NO_USE_B3,		//11
	HP_I_AN_3V3_B4,
	AGND_B5,
	HPT_AN_3V3_B6,
	AGND_B7,
	AnalogTotalChannel
};

#define GET_U_AN_3V3_A0				((AdcRegs.ADCRESULT0) >> 4)
#define GET_AGND_A1					((AdcRegs.ADCRESULT2) >> 4)
#define GET_I_AN_3V3_A2				((AdcRegs.ADCRESULT4) >> 4)
#define GET_AGND_A3					((AdcRegs.ADCRESULT6) >> 4)
#define GET_NO_USE_A4				((AdcRegs.ADCRESULT8) >> 4)
#define GET_NO_USE_A5				((AdcRegs.ADCRESULT10) >> 4)
#define GET_NO_USE_A6				((AdcRegs.ADCRESULT12) >> 4)
#define GET_AGND_A7					((AdcRegs.ADCRESULT14) >> 4)
#define GET_T_AN_3V3_B0				((AdcRegs.ADCRESULT1) >> 4)
#define GET_NO_USE_B1				((AdcRegs.ADCRESULT3) >> 4)
#define GET_NO_USE_B2				((AdcRegs.ADCRESULT5) >> 4)
#define GET_NO_USE_B3				((AdcRegs.ADCRESULT7) >> 4)
#define GET_HP_I_AN_3V3_B4			((AdcRegs.ADCRESULT9) >> 4)
#define GET_AGND_B5					((AdcRegs.ADCRESULT11) >> 4)
#define GET_HPT_AN_3V3_B6			((AdcRegs.ADCRESULT13) >> 4)
#define GET_AGND_B7					((AdcRegs.ADCRESULT15) >> 4)


/********************system analog variable data struct**************************/
typedef struct _AnalogVar{
	int value;
	int max;
	int min;
	UV updateValue;
}AnalogVar;

typedef struct _SingleChannelA{
	AnalogVar var[MAX_ANALOG_CHANNEL];
}SingleChannelA;

typedef struct _SysAnalogVar{
	SingleChannelA single;

}SysAnalogVar;

void InitAdcVar(void);
int IsAnalogValueAbnormal(void);
void ReadAnalogValue(void);

#endif /* ADC_H_ */
