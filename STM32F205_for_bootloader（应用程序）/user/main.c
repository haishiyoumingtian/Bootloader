#include "stm32f2xx.h"
#include "stmflash.h"
#include "string.h"
#include "usart.h"
#include "delay.h"
#include "list.h"
#include "sram.h"
#include "gpio.h"
#include "tim.h"
#include "can.h"
#include "adc.h"

extern u32 __Vectors;

int main(void)
{
	SCB->VTOR = __Vectors;//����ƫ����
	
	GPIO__Init();	//GPIO��ʼ��
	TIM__Init(); //��ʱ���жϳ�ʼ��
	FSMC_SRAM_Init();	//FSMC��ʼ��
	CAN1_Mode_Init(CAN_Mode_Normal); //����ģʽ	
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init(); //LED FSMC��д��ʼ��
	Adc_Init(); //ADC������ʼ��
	Flash_Init(); //Flash��ʼ��
	List_Init(32); //��ʼ�����г���
	
	printf("1.1");
	
	while (1){	
		//���Ͷ������һ������	
		if(top!=tail){
			CAN1_Send_Msg(top->StdId, (u8 *)top->data,8);
			top=top->next;
		}	
	}
}


