/*
 * adc.c
 *
 *  Created on: 2019��2��14��
 *      Author: Administrator
 */
#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "global.h"
#include "adc.h"
#include "kalman.h"


int64 tmp[64] = {0};
SysAnalogVar gSysAnalogVar = {0};
/********update anolog variable value******************************/
Uint16 updateU_AN_3V3_A0(void){return GET_U_AN_3V3_A0;}
Uint16 updateAGND_A1(void){return GET_AGND_A1;}
Uint16 updateI_AN_3V3_A2(void){
    Uint16 CurrentNoOffset;
    if(GET_I_AN_3V3_A2 <= gSysInfo.currentOffset){
        CurrentNoOffset = 0;
    }
    else{
        CurrentNoOffset = ((Uint16)GET_I_AN_3V3_A2) - gSysInfo.currentOffset;
    }
    return CurrentNoOffset;
    //return GET_I_AN_3V3_A2;
}
Uint16 updateAGND_A3(void){return GET_AGND_A3;}
Uint16 updateNO_USE_A4(void){return GET_NO_USE_A4;}
Uint16 updateNO_USE_A5(void){return GET_NO_USE_A5;}
Uint16 updateNO_USE_A6(void){return GET_NO_USE_A6;}
Uint16 updateAGND_A7(void){return GET_AGND_A7;}
Uint16 updateT_AN_3V3_B0(void){return GET_T_AN_3V3_B0;}
Uint16 updateNO_USE_B1(void){return GET_NO_USE_B1;}
Uint16 updateNO_USE_B2(void){return GET_NO_USE_B2;}
Uint16 updateNO_USE_B3(void){return GET_NO_USE_B3;}
Uint16 updateHP_I_AN_3V3_B4(void){return GET_HP_I_AN_3V3_B4;}
Uint16 updateAGND_B5(void){return GET_AGND_B5;}
Uint16 updateHPT_AN_3V3_B6(void){return GET_HPT_AN_3V3_B6;}
Uint16 updateAGND_B7(void){return GET_AGND_B7;}


const UV funcptr[] = {

	updateU_AN_3V3_A0,
	updateAGND_A1,
	updateI_AN_3V3_A2,
	updateAGND_A3,
	updateNO_USE_A4,
	updateNO_USE_A5,
	updateNO_USE_A6,
	updateAGND_A7,
	updateT_AN_3V3_B0,
	updateNO_USE_B1,
	updateNO_USE_B2,
	updateNO_USE_B3,
	updateHP_I_AN_3V3_B4,
	updateAGND_B5,
	updateHPT_AN_3V3_B6,
	updateAGND_B7
};
const int anologMaxMinInit[][4] = {
    //max,max2nd,min,min2nd
	{1636,1596,684,725},       //voltage max and min
	{1,0,0,0},
	{1096,958,0,0},        //current max, 2nd max and min
	{3,0,0,0},
	{4,0,0,0},
	{5,0,0,0},
	{6,0,0,0},
	{7,0,0,0},
	{0,0,500,610},		//temperature max and min
	{9,0,0,0},
	{10,0,0,0},
	{11,0,0,0},
	{12,0,0,0},
	{13,0,0,0},
	{14,0,0,0},
	{15,0,0,0},
};
void InitAdcVar(void){
	int index;
	for (index = 0; index < AnalogTotalChannel; ++index) {
		gSysAnalogVar.single.var[index].updateValue = funcptr[index];
		gSysAnalogVar.single.var[index].max = anologMaxMinInit[index][0];
		gSysAnalogVar.single.var[index].max2nd = anologMaxMinInit[index][1];
		gSysAnalogVar.single.var[index].min = anologMaxMinInit[index][2];
		gSysAnalogVar.single.var[index].min2nd = anologMaxMinInit[index][3];
	}
}

void UpdateSingleAnalogInput(void){
	int index;

	for(index = 0; index < AnalogTotalChannel; ++index){
		gSysAnalogVar.single.var[index].value = gSysAnalogVar.single.var[index].updateValue();
	}

}

void ReadAnalogValue(void){

    if((AdcRegs.ADCASEQSR.bit.SEQ_CNTR==0)&&
              (AdcRegs.ADCST.bit.SEQ1_BSY==0)){

    }
    else{
    	//TODO generate an alarm
    	return;
    }
}

int IsAnalogValueAbnormal(void){
	int index;
	int ret = 1;
	for(index = 0; index < AnalogTotalChannel; ++index){
		if((gSysAnalogVar.single.var[index].value > gSysAnalogVar.single.var[index].max) ||
				(gSysAnalogVar.single.var[index].value < gSysAnalogVar.single.var[index].min)) {
			ret = 0;
		}
	}
	return ret;
}

void updateAndCheckTemperature(void){
    static int min_count = 0;
    static int min2nd_count = 0;
    static int over_limit_lasttime = 0;
    gSysAnalogVar.single.var[T_AN_3V3_B0].value = gSysAnalogVar.single.var[T_AN_3V3_B0].updateValue();

    if(over_limit_lasttime == 1){
        if(gSysAnalogVar.single.var[T_AN_3V3_B0].value > gSysAnalogVar.single.var[T_AN_3V3_B0].min2nd){
            ++min2nd_count;
            if(min2nd_count >5000){
                min2nd_count = 0;
                over_limit_lasttime = 0;
                gSysAlarm.bit.overTemperature = 0;
            }
        }
        else{
            gSysAlarm.bit.overTemperature = 1;
            over_limit_lasttime = 1;
        }
    }
    else if (over_limit_lasttime == 0){
        if(gSysAnalogVar.single.var[T_AN_3V3_B0].value < gSysAnalogVar.single.var[T_AN_3V3_B0].min) {
            ++min_count;
            if(min_count > 5000){
                min_count = 0;
                gSysAlarm.bit.overTemperature = 1;
                over_limit_lasttime = 1;
            }
        }
        else{
            min_count = 0;
        }
    }
    else{
    	gSysSWAlarm.bit.updateAndCheckTemperature = 1;
    	gSysAlarm.bit.softwareFault = 1;
    }
}

void updateAndCheckVoltage(void){
    static int count_max = 0;
    static int count_min = 0;

    gSysAnalogVar.single.var[U_AN_3V3_A0].value = gSysAnalogVar.single.var[U_AN_3V3_A0].updateValue();

    if(gSysAlarm.bit.overBusVoltage == 1){
        if((gSysAnalogVar.single.var[U_AN_3V3_A0].value < gSysAnalogVar.single.var[U_AN_3V3_A0].max2nd)){
            gSysAlarm.bit.overBusVoltage = 0;
        }
        else{
            gSysAlarm.bit.overBusVoltage = 1;
        }
    }
    else if(gSysAlarm.bit.overBusVoltage == 0){
        if((gSysAnalogVar.single.var[U_AN_3V3_A0].value > gSysAnalogVar.single.var[U_AN_3V3_A0].max)) {
            ++count_max;
            if(count_max > 10){
                count_max = 0;
                gSysAlarm.bit.overBusVoltage = 1;
            }
        }
        else{
            count_max = 0;
        }
    }
    else{
        gSysSWAlarm.bit.updateAndCheckVoltage = 1;
        gSysAlarm.bit.softwareFault = 1;
    }
    if(gSysAlarm.bit.lowBusVoltage == 1){
        if((gSysAnalogVar.single.var[U_AN_3V3_A0].value > gSysAnalogVar.single.var[U_AN_3V3_A0].min2nd)){
            gSysAlarm.bit.lowBusVoltage = 0;
        }
        else{
            gSysAlarm.bit.lowBusVoltage = 1;
        }
    }
    else if (gSysAlarm.bit.lowBusVoltage == 0){
        if((gSysAnalogVar.single.var[U_AN_3V3_A0].value < gSysAnalogVar.single.var[U_AN_3V3_A0].min)) {
            ++count_min;
            if(count_min > 10){
                count_min = 0;
                gSysAlarm.bit.lowBusVoltage = 1;
            }
        }
        else{
            count_min = 0;
        }
    }
    else {
    	gSysSWAlarm.bit.updateAndCheckVoltage = 1;
        gSysAlarm.bit.softwareFault = 1;
    }
}

void updateAndCheckCurrent(void){
	static int max_count = 0;
	gSysAnalogVar.single.var[I_AN_3V3_A2].value = gSysAnalogVar.single.var[I_AN_3V3_A2].updateValue();
	if(gSysAnalogVar.single.var[I_AN_3V3_A2].value > gSysAnalogVar.single.var[I_AN_3V3_A2].max2nd) {
	   gSysInfo.restrictduty = 1;
	    if(gSysAnalogVar.single.var[I_AN_3V3_A2].value > gSysAnalogVar.single.var[I_AN_3V3_A2].max) {
	        max_count = (gSysAnalogVar.single.var[I_AN_3V3_A2].value - gSysAnalogVar.single.var[I_AN_3V3_A2].max) + max_count;
	        if(max_count > 150){
	            max_count = 0;
	            gSysAlarm.bit.overCurrent = 1;
	        }
	    }
	    else{
	        --max_count;
	    }
	}
	else{
	    if(max_count >= 1){
	        --max_count;
	    }
	    else{
	        max_count = 0;
	    }
		gSysInfo.restrictduty = 0;
		gSysAlarm.bit.overCurrent = 0;
	}

	 if(gSysAnalogVar.single.var[I_AN_3V3_A2].value > gSysInfo.maxCurrent){
	 	gSysInfo.maxCurrent = gSysAnalogVar.single.var[I_AN_3V3_A2].value;
	 }
}
