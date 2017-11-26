/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE); 			
    
    //LED_Debug
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
    //Dot1,2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);
  
		GPIO_SetBits(GPIOA, GPIO_Pin_6); 
    GPIO_SetBits(GPIOB, GPIO_Pin_10|GPIO_Pin_11); 
}

void Dot_Toggle(void)
{
  Dot1_TOGGLE;
  Dot2_TOGGLE;
}

extern u8 __IO Period_1S;
void LED_STATE(void)
{
  if(Period_1S) LED1(1);
  else LED1(0);
}

/*********************************************END OF FILE**********************/

