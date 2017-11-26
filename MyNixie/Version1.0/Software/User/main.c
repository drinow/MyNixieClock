/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   systickϵͳ��ʱ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ISO-MINI STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "include.h"


void NVIC_Config(void)
{	
	NVIC_InitTypeDef NVIC_InitStructure; 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
extern u32 __IO tick;
extern TIME_TypeDef SetTime,GetTime;
extern u8 SecAlarm;
extern u8 WS2812_RGB[WS2812_NUM][3];
extern u8 __IO Pulse_1S,Breath_Frq;

u8 RemoteKey=0;
int main(void)
{	
	LED_GPIO_Config();
	SysTick_Init();
  NVIC_Config();
  DS18B20_Init();
  USART1_Config();
  DS3231_Config();
  BeepInit();
  WS2812_Init();
  TM1812_Init();
  Remote_Init();
//  SetTime.year =0x17;
//  SetTime.month =0x07;
//  SetTime.date =0x05;
//  SetTime.hour =0x14;
//  SetTime.min =0x13;
//  SetTime.sec =0x30;
//  SetTime.week =0x03;
//  DS3231_WriteTime(&SetTime);
//  DS3231_WriteTime(&SetTime);
  
  printf("Running...\n");
	for(;;)
	{
//		LED_STATE();	
//    Beep_State();
    if(SecAlarm)
    {
      SecAlarm=0;
      LED1_TOGGLE;
      printf("Time:%2x:%2x:%2x  ",GetTime.hour ,GetTime.min ,GetTime.sec );
      printf("Temp:%3.2f�� \r\n",DS18B20_Get_Temp());
    }
    if(Pulse_1S)
    {
//      SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
//      Nixie_Test();
//      SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
//      printf("Temp:%3.2f�� ",DS18B20_Get_Temp());
//      DS3231_ReadTime(&GetTime);
//      printf("Time:%2x:%2x:%2x  \r\n",GetTime.hour ,GetTime.min ,GetTime.sec );
      Pulse_1S=0;
    }
//    //������Ч��
    if(Breath_Frq)
    {
      SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
      WS2812_Breath(255,128,64,250);
//      printf("R:%3d G:%3d B:%3d %d\r\n",WS2812_RGB[0][0],WS2812_RGB[0][1],WS2812_RGB[0][1],tick);
      Breath_Frq=0;
      SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
    }
    if(Remote_Rdy)
		{
			RemoteKey=Remote_Process();
			printf("RemoteKey:%d ",RemoteKey);//��ʾ��ֵ
			printf("cnt:%d \r\n",Remote_Cnt);//��ʾ��������	
		}
	}     
}
/*********************************************END OF FILE**********************/
