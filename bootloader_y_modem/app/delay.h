#ifndef __DELAY_H
#define __DELAY_H
#include "sys.h"

#define LED1_OFF GPIO_SetBits(GPIOD, GPIO_Pin_2);
#define LED1_ON GPIO_ResetBits(GPIOD, GPIO_Pin_2);
 
void delay_us(u32 nus);			
void delay_ms(u16 nms);
void GPIO__Init(void);
 
#endif /* __DELAY_H */

