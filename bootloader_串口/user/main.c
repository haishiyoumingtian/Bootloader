#include "bootloader.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//设置系统中断优先级分组2
	uart_init(115200);																//初始化串口波特率为115200
	GPIO__Init();																			//GPIO初始化
	boot_start();																			//启动bootloader
  delay_ms(500);																		//延时500ms
	write_flash(LEN_APP);															//写入falsh
	start_app();																			//启动应用程序
	while (1);
}



