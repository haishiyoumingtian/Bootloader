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
	SCB->VTOR = __Vectors;//设置偏移量
	
	GPIO__Init();	//GPIO初始化
	TIM__Init(); //定时器中断初始化
	FSMC_SRAM_Init();	//FSMC初始化
	CAN1_Mode_Init(CAN_Mode_Normal); //正常模式	
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init(); //LED FSMC读写初始化
	Adc_Init(); //ADC采样初始化
	Flash_Init(); //Flash初始化
	List_Init(32); //初始化队列长度
	
	printf("1.1");
	
	while (1){	
		//发送队列里的一个数据	
		if(top!=tail){
			CAN1_Send_Msg(top->StdId, (u8 *)top->data,8);
			top=top->next;
		}	
	}
}


