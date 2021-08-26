
/**********************************************************
                       康威科技
更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
https://kvdz.taobao.com/
**********************************************************/

#ifndef _ADF4351_H_
#define _ADF4351_H_

#include "sys.h"

#define ADF4351_CLK PBout(15)
#define ADF4351_OUTPUT_DATA PBout(14)
#define ADF4351_LE PBout(13)
#define ADF4351_CE PBout(12)

#define ADF4351_INPUT_DATA PBin(14)


void ADF4351Init(void);
void ReadToADF4351(u8 count, u8 *buf);
void WriteToADF4351(u8 count, u8 *buf);
void WriteOneRegToADF4351(u32 Regster);
void ADF4351_Init_some(void);
void ADF4351WriteFreq(float Fre);		//	(xx.x) M Hz

#endif

