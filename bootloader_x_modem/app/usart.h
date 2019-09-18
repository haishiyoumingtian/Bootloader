#ifndef __USART_H
#define __USART_H
#include "sys.h"

#define USART_REC_LEN  			120*1024 //定义最大接收字节数 120K
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

#define SOH                     (0x01)  //128字节数据包开始
#define STX                     (0x02)  //1024字节的数据包开始
#define EOT                     (0x04)  //结束传输
#define ACK                     (0x06)  //回应
#define NAK                     (0x15)  //没回应
#define CA                      (0x18)  //这两个相继中止转移
#define CRC16                   (0x43)  //'C' == 0x43, 需要 16-bit CRC 
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern u32 USART_RX_CNT;				//接收的字节数	
extern u8 USART_RX_LIST[135];

//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
#endif


