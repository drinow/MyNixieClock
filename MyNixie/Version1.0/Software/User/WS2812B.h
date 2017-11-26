#ifndef __WS1812_H
#define __WS1812_H

#include "stm32f10x.h"


#define PORT_WS2812 GPIOB
#define Pin_WS2812  GPIO_Pin_0
#define RCC_WS2812  RCC_APB2Periph_GPIOB

#define WS2812_Set    PORT_WS2812->BSRR = Pin_WS2812;
#define WS2812_Reset  PORT_WS2812->BRR  = Pin_WS2812;

//灯珠数量
#define WS2812_NUM 4

//行表示灯珠数量，列表示RGB信息
extern u8 WS2812_RGB[WS2812_NUM][3];

void WS2812_Init(void);
void WS2812_Send_Px(void);
void WS2812_Breath(u8 Red,u8 Green,u8 Blue,u8 level);
#endif
