
/**********************************************************
                       �����Ƽ�
������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
https://kvdz.taobao.com/
**********************************************************/

#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "ADF4351.h"
#include "task_manage.h"
u8 Task_ID = Max_Task;
extern u32 SysTimer;
extern u32 Keycode;
int main(void)
{		
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	key_init();
	OLED_Init();			 //��ʼ��OLED 
	welcome_KW();
	ADF4351Init();
	LCD_Show_CEStr(56,6,"35M...");
	while(1)
	{
		;
	}
}

