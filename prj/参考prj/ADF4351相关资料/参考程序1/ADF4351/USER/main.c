
/**********************************************************
                       康威科技
更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
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
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();
	key_init();
	OLED_Init();			 //初始化OLED 
	welcome_KW();
	ADF4351Init();
	LCD_Show_CEStr(56,6,"35M...");
	while(1)
	{
		;
	}
}

