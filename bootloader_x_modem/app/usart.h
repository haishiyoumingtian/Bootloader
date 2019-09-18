#ifndef __USART_H
#define __USART_H
#include "sys.h"

#define USART_REC_LEN  			120*1024 //�����������ֽ��� 120K
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

#define SOH                     (0x01)  //128�ֽ����ݰ���ʼ
#define STX                     (0x02)  //1024�ֽڵ����ݰ���ʼ
#define EOT                     (0x04)  //��������
#define ACK                     (0x06)  //��Ӧ
#define NAK                     (0x15)  //û��Ӧ
#define CA                      (0x18)  //�����������ֹת��
#define CRC16                   (0x43)  //'C' == 0x43, ��Ҫ 16-bit CRC 
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern u32 USART_RX_CNT;				//���յ��ֽ���	
extern u8 USART_RX_LIST[135];

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
#endif


