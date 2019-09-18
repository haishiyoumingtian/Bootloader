#include "bootloader.h"

u16 LEN_APP=0;	//���յ���Ӧ�ó��򳤶�

void write_flash(u16 LEN_APP){
	if(LEN_APP)
	{
		printf("��ʼ���¹̼�...\r\n");	
		printf("APP����Ϊ%d",LEN_APP);
		if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
		{	 
			iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,LEN_APP);//����FLASH����   
			printf("�̼��������!\r\n");	
		}else 
		{
			printf("��FLASHӦ�ó���!\r\n");
		}
	}else 
	{
		printf("û�п��Ը��µĹ̼�!\r\n");
	}
}

void flash_clean(u16 LEN_APP){
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

void boot_start(void){
		u16 t=0;
		u16 Count=0;	//���յ����ַ�������
		printf("�����û�����\r\n");
		while(1){
			if(USART_RX_CNT)
			{
				if(Count==USART_RX_CNT)//��������,û���յ��κ�����,��Ϊ�������ݽ������.
				{
					LEN_APP=USART_RX_CNT;
					Count=0;
					USART_RX_CNT=0;
					printf("�û�����������!\r\n");
					printf("�û����򳤶�Ϊ:%dBytes\r\n",LEN_APP);
					break;
				}else Count=USART_RX_CNT;	
			}		
				delay_ms(100);
				t++;
				if(t%10==0){
					printf("BOOT�ȴ���...%d\r\n",10-t/10);
				}		
				if(t>=100){
					break;
				}
		}
}

