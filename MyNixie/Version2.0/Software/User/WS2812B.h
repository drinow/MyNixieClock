#ifndef __WS1812_H
#define __WS1812_H

#include "stm32f10x.h"
#include <string.h>
#include "stdio.h"

#define PORT_WS2812 GPIOB
#define Pin_WS2812  GPIO_Pin_0
#define RCC_WS2812  RCC_APB2Periph_GPIOB

#define WS2812_Set    PORT_WS2812->BSRR = Pin_WS2812;
#define WS2812_Reset  PORT_WS2812->BRR  = Pin_WS2812;

//��������
#define WS2812_NUM 4

//ģʽѡ��-mode
#define SINGLECOLOUR 0
#define MULTICOLOUR  1

//��Чѡ��-state
#define EFFECTS_ON   0
#define EFFECTS_OFF  1
#define RGB_OFF      2
//RGB�ṹ��
typedef struct{
  u8 R;
  u8 G;
  u8 B;
  u8 mode;//ɫ��ģʽ��mode=0-->��ɫģʽ��mode=1-->��ɫģʽ
  u8 level;//���ȵȼ�
  u8 state;//��Чѡ�� 0���������� 1�������� 2��Ϩ��
}RGB_TypeDef;
//�б�ʾ�����������б�ʾRGB��Ϣ

//extern __IO u8 WS2812_RGB[WS2812_NUM][3];
extern __IO RGB_TypeDef RGB_Msg,RGB_Rcd;

void WS2812_Init(void);
void WS2812_Send_Px(void);
void WS2812_Breath(void);
void WS2812_Refresh(u8 R,u8 G,u8 B);
#endif
