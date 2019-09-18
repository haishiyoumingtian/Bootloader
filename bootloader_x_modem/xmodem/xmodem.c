#include "xmodem.h"


u8 USART_RX_BUF[120*1024] __attribute__ ((at(0X20001000)));//接收缓冲,最大USART_REC_LEN个字节,起始地址为0X20001000. 
u16 LEN_APP=0;	//接收到的应用程序长度


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

void write_flash(u16 LEN_APP){
	if(LEN_APP)
	{
		printf("开始更新固件...\r\n");	
		printf("APP长度为%d",LEN_APP);
		if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
		{	 
			iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,LEN_APP);//更新FLASH代码   
			printf("固件更新完成!\r\n");	
		}
		else 
		{
			printf("非FLASH应用程序!\r\n");
		}
	}
	else 
	{
		printf("没有可以更新的固件!\r\n");
	}
 }

void flash_clean(u16 LEN_APP){  //flash清理
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

void start_xmodem_rx(void){
		u16 t=0,i;
		u16 Count=0;	//接收到的字符串长度
		u16 RE_FLAG=1;
		USART_SendData(USART1,NAK);
		while(1){
		if(USART_RX_CNT)
		{
			if(Count==USART_RX_CNT)//新周期内,没有收到任何数据,认为本次数据接收完成.
			{
				t=0;
//				LEN_APP=USART_RX_CNT;
				Count=0;
				USART_RX_CNT=0;
				printf("用户程序接收完成!\r\n");
				printf("用户程序长度为:%dBytes\r\n",LEN_APP);
				//判断结束位置
				if(USART_RX_LIST[0]== EOT){
					USART_SendData(USART1,0x43);
					break;
				}
				//判断数据包格式
				if(USART_RX_LIST[0]== SOH && USART_RX_LIST[1]==RE_FLAG && crc16_ccitt(&USART_RX_LIST[3],128)){
					RE_FLAG++;	
					for(i=3;i<=130;i++){
						if(USART_RX_LIST[i] == 0x1A && USART_RX_LIST[i+1] == 0x1A){
							break;
						}
						USART_RX_BUF[LEN_APP]=USART_RX_LIST[i];
						LEN_APP++;
					}
					USART_SendData(USART1,ACK);
				}
				else{
					USART_SendData(USART1,NAK);
				}
//				break;
			}else Count=USART_RX_CNT;	
		}		
			delay_ms(100);
			t++;
			if(t%10==0){
				printf("打开发送后复位开始接收..%d\r\n",10-t/10);
			}		
			if(t>=100){
				break;
			}
	}
}
unsigned short crc16_ccitt(const unsigned char *buf, int len)//CRC校验
{
	register int counter;
	register unsigned short crc = 0;
	for( counter = 0; counter < len; counter++)
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(char *)buf++)&0x00FF];
	return crc;
}



