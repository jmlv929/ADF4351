/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2016-05-05
  * @brief   ADF435X EVAL BD
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 
  * 淘宝    :https://shop129810565.taobao.com/
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "bsp_led.h"
#include "ADF4351.h"
void Delay(u32 nCount);


/**
  * @brief  
 0* @retval 
  */
int main(void)
{	
 ADF4351_Initiate();
	//Frequency_35MHz();
	ADF_SetFre();
	while (1)
	{
			
		}
}	


void Delay(u32 nCount)
{
 u32 TimingDelay; 
 while(nCount--)
   {
    for(TimingDelay=0;TimingDelay<10000;TimingDelay++);
   }
}



/*********************************************END OF FILE**********************/
