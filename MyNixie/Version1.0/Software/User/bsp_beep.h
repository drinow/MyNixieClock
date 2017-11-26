#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#include "include.h"

#define Beep(a)	if (a)	\
                  GPIO_SetBits(GPIOB,GPIO_Pin_6);\
                else		\
                  GPIO_ResetBits(GPIOB,GPIO_Pin_6)
          
void BeepInit(void);
void Beep_State(void);
                
#endif
