#ifndef __ADC_H
#define __ADC_H	


#include "stm32f2xx_rcc.h"
#include "core_cm3.h"
#include "stm32f2xx_it.h"
#include "misc.h"
 
 							   
void Adc_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  
#endif 















