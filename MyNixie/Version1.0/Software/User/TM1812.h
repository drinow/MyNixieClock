#ifndef __TM1812_H
#define __TM1812_H

#include "stm32f10x.h"


#define PORT_TM1812 GPIOA
#define Pin_TM1812  GPIO_Pin_0
#define RCC_TM1812  RCC_APB2Periph_GPIOA

#define TM1812_Set    PORT_TM1812->BSRR = Pin_TM1812;
#define TM1812_Reset  PORT_TM1812->BRR  = Pin_TM1812;

//TM1812芯片级联数量，一个芯片有4个灯
#define TM1812_NUM 1

extern u8 TM1812_RGB[TM1812_NUM*4][3];

void TM1812_Init(void);
void TM1812_Send_Px(void);
void TM1812_Flash_Test(void);
#endif
