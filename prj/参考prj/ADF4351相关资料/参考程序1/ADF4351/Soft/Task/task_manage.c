
/**********************************************************
                       �����Ƽ�
������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
https://kvdz.taobao.com/
**********************************************************/

#include "task_manage.h"
#include "ADF4351.h"
#include "delay.h"

u8 Firt_In = 1;
u8 Task_Index = 0;

u8 Task_Delay(u32 delay_time, u8* delay_ID)
{
	static u8 Time_Get = 0;
	static u32 Time_Triger;
    if(Time_Get == 0)
    {
      Time_Triger = SysTimer + delay_time;
      Time_Get = 1;
    }
    if(SysTimer >= Time_Triger)
    { 
      Time_Get = 0;
			*delay_ID = 1;		//	���������ѱ�ִ��һ��
			return 1;
    }
		return 0;
}

u8 TaskCycleDelay(u32 delay_time, u8* Last_delay_ID, u8* Self_delay_ID)
{
	static u8 Time_Get = 0;
	static u32 Time_Triger;
	
	if(!(*Last_delay_ID))
		return 0;
	if(Time_Get == 0)
	{
		Time_Triger = SysTimer + delay_time;
		Time_Get = 1;
	}
	if(SysTimer >= Time_Triger)
	{ 
		Time_Get = 0;
		*Last_delay_ID = 0;
		*Self_delay_ID = 1;		//	���������ѱ�ִ��һ��
		return 1;
	}
	return 0;
}
void welcome_KW(void)
{
	u8 delay_ID[11] = {0,0,0,0,0,0,0,0,0,0};
	u8 delay_ID_Welcome[3] = {0,0,0};
	u16 Wel_time0 = 5,Wel_time1 = 30;
	delay_ID[10] = 1;
	delay_ID_Welcome[2] = 1;
	LCD_Show_CEStr(16,4,"ADF435x");
	LCD_Show_CEStr(56,6,"��ʼ��");
	while(1)
	{
	if(TaskCycleDelay(Wel_time0, &delay_ID[10], &delay_ID[0]))
		LCD_Show_CEStr(32,0,"��");
	if(TaskCycleDelay(Wel_time0, &delay_ID[0], &delay_ID[1]))
		LCD_Show_CEStr(48,0,"��");
	if(TaskCycleDelay(Wel_time0, &delay_ID[1], &delay_ID[2]))
		LCD_Show_CEStr(64,0,"��");
	if(TaskCycleDelay(Wel_time0, &delay_ID[2], &delay_ID[3]))
		LCD_Show_CEStr(80,0,"��");
	if(TaskCycleDelay(Wel_time0, &delay_ID[3], &delay_ID[4]))
		LCD_Show_CEStr(16,2,"��");
	if(TaskCycleDelay(Wel_time0, &delay_ID[4], &delay_ID[5]))
		LCD_Show_CEStr(32,2,"��");
	if(TaskCycleDelay(Wel_time0, &delay_ID[5], &delay_ID[6]))
		LCD_Show_CEStr(48,2,"Ϊ");
	if(TaskCycleDelay(Wel_time0, &delay_ID[6], &delay_ID[7]))
		LCD_Show_CEStr(64,2,"��");
	if(TaskCycleDelay(Wel_time0, &delay_ID[7], &delay_ID[8]))
		LCD_Show_CEStr(80,2,"��");
	if(TaskCycleDelay(Wel_time0, &delay_ID[8], &delay_ID[9]))
		LCD_Show_CEStr(96,2,"��");
	if(TaskCycleDelay(Wel_time0, &delay_ID[9], &delay_ID[0]))
		break;
	if(TaskCycleDelay(Wel_time1, &delay_ID_Welcome[2], &delay_ID_Welcome[0]))
		LCD_Show_CEStr(104,6,".  ");
	if(TaskCycleDelay(Wel_time1, &delay_ID_Welcome[0], &delay_ID_Welcome[1]))
		LCD_Show_CEStr(112,6,".");
	if(TaskCycleDelay(Wel_time1, &delay_ID_Welcome[1], &delay_ID_Welcome[2]))
		LCD_Show_CEStr(120,6,".");
	}
}


