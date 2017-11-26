#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

/* ���κ꣬��������������һ��ʹ�� */
#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_6)

#define Dot1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_10)

#define Dot2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_10)
          
/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)			{p->BSRR=i;}			//����Ϊ�ߵ�ƽ		
#define digitalLo(p,i)			{p->BRR=i;}				//����͵�ƽ
#define digitalToggle(p,i)		{p->ODR ^=i;}			//�����ת״̬


/* �������IO�ĺ� */
#define LED1_TOGGLE		digitalToggle(GPIOA,GPIO_Pin_6)
#define LED1_OFF		digitalHi(GPIOA,GPIO_Pin_6)
#define LED1_ON			digitalLo(GPIOA,GPIO_Pin_6)

#define Dot1_TOGGLE		digitalToggle(GPIOB,GPIO_Pin_10)
#define Dot1_ON		    digitalHi(GPIOB,GPIO_Pin_10)
#define Dot1_OFF			digitalLo(GPIOB,GPIO_Pin_10)

#define Dot2_TOGGLE		digitalToggle(GPIOB,GPIO_Pin_11)
#define Dot2_ON		    digitalHi(GPIOB,GPIO_Pin_11)
#define Dot2_OFF			digitalLo(GPIOB,GPIO_Pin_11)

void LED_GPIO_Config(void);
void LED_STATE(void);
void Dot_Toggle(void);

#endif /* __LED_H */
