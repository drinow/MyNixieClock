#include "bsp_beep.h"

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

extern u8 __IO Period_1S;
void Beep_State(void)
{
  if(Period_1S) Beep(1);
  else Beep(0);
}
