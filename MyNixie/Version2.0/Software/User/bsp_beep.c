#include "bsp_beep.h"

void Beep_Delay(u32 j)
{
  u32 i=0;
  for(;j>0;j--)
    for(;i<0x1ffff;i++);
}

void BeepInit(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 									   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		  
		Beep(0); 
}

//鸣叫时间
void Beep_State(u32 num)
{
  Beep(1);
  Beep_Delay(num);
  Beep(0);
}

//整点报时音效
void Beep_OnTimeAlarm(void)
{
	Beep(1);
  Beep_Delay(5);
  Beep(0);
	Beep_Delay(800000);
	Beep(1);
	Beep_Delay(5);
	Beep(0);
}

extern __IO u8 AlarmState;
extern u8  __IO AlarmWaveFlag;
void Beep_Alarm(void)
{
  if(AlarmState>0&&AlarmState<62)
  {
    Beep(AlarmWaveFlag);
  }
	else
	{
		Beep(0);
	}
}
