#include "xmodem.h"


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//����ϵͳ�ж����ȼ�����2
	uart_init(115200);																//��ʼ�����ڲ�����Ϊ115200
	GPIO__Init();																			//GPIO��ʼ��								
	start_xmodem_rx();																//����xmodem����	
	delay_ms(500);																		//��ʱ500ms
	write_flash(LEN_APP);															//д��flash
	start_app();																			//����Ӧ�ó���
  while (1);
}
