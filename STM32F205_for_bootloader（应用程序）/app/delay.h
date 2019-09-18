#ifndef __DELAY_H
#define __DELAY_H
 

#include "stm32f2xx_rcc.h"
#include "core_cm3.h"
#include "stm32f2xx_it.h"
#include "misc.h"
 
void delay_us(u32 nus);			
void delay_ms(u16 nms);
 
#endif /* __DELAY_H */

