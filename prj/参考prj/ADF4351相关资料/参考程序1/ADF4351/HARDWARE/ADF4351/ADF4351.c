
/**********************************************************
                       康威科技
更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
https://kvdz.taobao.com/
**********************************************************/

#include "ADF4351.h"
#include "delay.h"


void ADF_Output_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}

void ADF_Input_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING ; 
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}

void delay (int length)
{
	while (length >0)
    	length--;
}

void WriteToADF4351(u8 count, u8 *buf)
{
	u8 ValueToWrite = 0;
	u8 i = 0;
	u8 j = 0;
	
//	ADF_Output_GPIOInit();
	
	ADF4351_CE = 1;
	delay_us(1);
	ADF4351_CLK = 0;
	ADF4351_LE = 0;
	delay_us(1);
	
	for(i = count; i>0; i--)
	{
		ValueToWrite = *(buf+i-1);
		for(j=0; j<8; j++)
		{
			if(0x80 == (ValueToWrite & 0x80))
			{
				ADF4351_OUTPUT_DATA = 1;
			}
			else
			{
				ADF4351_OUTPUT_DATA = 0;
			}
			delay_us(1);
			ADF4351_CLK = 1;
			delay_us(1);
			ValueToWrite <<= 1;
			ADF4351_CLK = 0;	
		}
	}
	ADF4351_OUTPUT_DATA = 0;
	delay_us(1);
	ADF4351_LE = 1;
	delay_us(1);
	ADF4351_LE = 0;
}


void ReadToADF4351(u8 count, u8 *buf)
{
	u8 i = 0;
	u8 j = 0;
	u8 iTemp = 0;
	u8 RotateData = 0;
	
	ADF_Input_GPIOInit();
	ADF4351_CE = 1;
	delay_us(1);
	ADF4351_CLK = 0;
	ADF4351_LE = 0;
	delay_us(1);
	
	for(i = count; i>0; i--)
	{
		for(j = 0; j<8; j++)
		{
			RotateData <<=1;
			delay_us(1);
			iTemp = ADF4351_INPUT_DATA;
			ADF4351_CLK = 1;
			if(0x01 == (iTemp&0x01))
			{
				RotateData |= 1;
			}
			delay_us(1);
			ADF4351_CLK = 0;
		}
		*(buf+i-1) = RotateData;
	}
	delay_us(1);
	ADF4351_LE = 1;
	delay_us(1);
	ADF4351_LE = 0;
}


void ADF4351Init(void)
{
	u8 buf[4] = {0,0,0,0};
	
	ADF_Output_GPIOInit();
	
	buf[3] = 0x00;				//此处配置固定输出35M
	buf[2] = 0x58;
	buf[1] = 0x00;				//write communication register 0x00580005 to control the progress 
 	buf[0] = 0x05;				//to write Register 5 to set digital lock detector
	WriteToADF4351(4,buf);		

	buf[3] = 0x00;
	buf[2] = 0xec;				//(DB23=1)The signal is taken from the VCO directly;(DB22-20:4H)the RF divider is 16;(DB19-12:50H)R is 80
	buf[1] = 0x80;				//(DB11=0)VCO powerd up;
 	buf[0] = 0x3C;				//(DB5=1)RF output is enabled;(DB4-3=3H)Output power level is 5
	WriteToADF4351(4,buf);		

	buf[3] = 0x00;
	buf[2] = 0x00;
	buf[1] = 0x04;				//(DB14-3:96H)clock divider value is 150.
 	buf[0] = 0xB3;
	WriteToADF4351(4,buf);	

	buf[3] = 0x00;
	buf[2] = 0x01;				//(DB6=1)set PD polarity is positive;(DB7=1)LDP is 6nS;
	buf[1] = 0x0E;				//(DB8=0)enable fractional-N digital lock detect;
 	buf[0] = 0x42;				//(DB12-9:7H)set Icp 2.50 mA;
	WriteToADF4351(4,buf);		//(DB23-14:1H)R counter is 1

	buf[3] = 0x00;
	buf[2] = 0x00;
	buf[1] = 0x80;			   //(DB14-3:6H)MOD counter is 6;
 	buf[0] = 0x29;			   //(DB26-15:6H)PHASE word is 1,neither the phase resync 
	WriteToADF4351(4,buf);	   //nor the spurious optimization functions are being used
							   //(DB27=1)prescaler value is 8/9

	buf[3] = 0x00;
	buf[2] = 0x2c;
	buf[1] = 0x80;
 	buf[0] = 0x18;				//(DB14-3:0H)FRAC value is 0;
	WriteToADF4351(4,buf);		//(DB30-15:140H)INT value is 320;	
}
