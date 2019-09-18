#include "bootloader.h"

u16 LEN_APP=0;	//接收到的应用程序长度

void write_flash(u16 LEN_APP){
	if(LEN_APP)
	{
		printf("开始更新固件...\r\n");	
		printf("APP长度为%d",LEN_APP);
		if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
		{	 
			iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,LEN_APP);//更新FLASH代码   
			printf("固件更新完成!\r\n");	
		}else 
		{
			printf("非FLASH应用程序!\r\n");
		}
	}else 
	{
		printf("没有可以更新的固件!\r\n");
	}
}

void flash_clean(u16 LEN_APP){
		if(LEN_APP)
		{																	 
			printf("固件清除完成!\r\n");    
			LEN_APP=0;
		}
		else 
		{
			printf("没有可以清除的固件!\r\n");
		}
}

void start_app(void){
		printf("开始执行FLASH用户代码!!\r\n\r\n");
		if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
		{	 
			iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
		}else 
		{
			printf("非FLASH应用程序,无法执行!\r\n"); 
		}		
}

void boot_start(void){
		u16 t=0;
		u16 Count=0;	//接收到的字符串长度
		printf("输入用户程序：\r\n");
		while(1){
			if(USART_RX_CNT)
			{
				if(Count==USART_RX_CNT)//新周期内,没有收到任何数据,认为本次数据接收完成.
				{
					LEN_APP=USART_RX_CNT;
					Count=0;
					USART_RX_CNT=0;
					printf("用户程序接收完成!\r\n");
					printf("用户程序长度为:%dBytes\r\n",LEN_APP);
					break;
				}else Count=USART_RX_CNT;	
			}		
				delay_ms(100);
				t++;
				if(t%10==0){
					printf("BOOT等待中...%d\r\n",10-t/10);
				}		
				if(t>=100){
					break;
				}
		}
}

