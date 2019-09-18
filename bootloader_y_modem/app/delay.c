#include "Delay.h"
 

void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD = 9*nus;
	SysTick->VAL=0X00;
	SysTick->CTRL=0X01;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&(!(temp&(1<<16))));
	SysTick->CTRL=0x00; 
	SysTick->VAL =0X00; 
}
void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD = 9000*nms;
	SysTick->VAL=0X00;
	SysTick->CTRL=0X01;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&(!(temp&(1<<16))));
	SysTick->CTRL=0x00; 
	SysTick->VAL =0X00; //?????
}
void GPIO__Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//∏¥”√ ‰≥ˆ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	LED1_ON;
}

