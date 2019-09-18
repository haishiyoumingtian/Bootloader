#include "xmodem.h"


u8 USART_RX_BUF[120*1024] __attribute__ ((at(0X20001000)));//���ջ���,���USART_REC_LEN���ֽ�,��ʼ��ַΪ0X20001000. 
u16 LEN_APP=0;	//���յ���Ӧ�ó��򳤶�


void start_app(void){
		printf("��ʼִ��FLASH�û�����!!\r\n\r\n");
		if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
		{	 
			iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
		}else 
		{
			printf("��FLASHӦ�ó���,�޷�ִ��!\r\n"); 
		}		
}

void write_flash(u16 LEN_APP){
	if(LEN_APP)
	{
		printf("��ʼ���¹̼�...\r\n");	
		printf("APP����Ϊ%d",LEN_APP);
		if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
		{	 
			iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,LEN_APP);//����FLASH����   
			printf("�̼��������!\r\n");	
		}
		else 
		{
			printf("��FLASHӦ�ó���!\r\n");
		}
	}
	else 
	{
		printf("û�п��Ը��µĹ̼�!\r\n");
	}
 }

void flash_clean(u16 LEN_APP){  //flash����
		if(LEN_APP)
		{																	 
			printf("�̼�������!\r\n");    
			LEN_APP=0;
		}
		else 
		{
			printf("û�п�������Ĺ̼�!\r\n");
		}
}

void start_xmodem_rx(void){
		u16 t=0,i;
		u16 Count=0;	//���յ����ַ�������
		u16 RE_FLAG=1;
		USART_SendData(USART1,NAK);
		while(1){
		if(USART_RX_CNT)
		{
			if(Count==USART_RX_CNT)//��������,û���յ��κ�����,��Ϊ�������ݽ������.
			{
				t=0;
//				LEN_APP=USART_RX_CNT;
				Count=0;
				USART_RX_CNT=0;
				printf("�û�����������!\r\n");
				printf("�û����򳤶�Ϊ:%dBytes\r\n",LEN_APP);
				//�жϽ���λ��
				if(USART_RX_LIST[0]== EOT){
					USART_SendData(USART1,0x43);
					break;
				}
				//�ж����ݰ���ʽ
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
				printf("�򿪷��ͺ�λ��ʼ����..%d\r\n",10-t/10);
			}		
			if(t>=100){
				break;
			}
	}
}
unsigned short crc16_ccitt(const unsigned char *buf, int len)//CRCУ��
{
	register int counter;
	register unsigned short crc = 0;
	for( counter = 0; counter < len; counter++)
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(char *)buf++)&0x00FF];
	return crc;
}



