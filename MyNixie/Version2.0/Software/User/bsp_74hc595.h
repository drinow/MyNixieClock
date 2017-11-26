#ifndef __BSP_74HC595_H
#define __BSP_74HC595_H

#include "stm32f10x.h"

// 74HC595
#define HC595_PORT  GPIOA
#define HC595_RCC   RCC_APB2Periph_GPIOA
#define HC595_DATA  GPIO_Pin_0    // serial data input, pin14
#define HC595_SCLK  GPIO_Pin_1    // shift register clock input, pin11
#define HC595_RCLK  GPIO_Pin_2     // storage register clock input, pin12
#define HC595_OE    GPIO_Pin_3     // output enable,active low,pin13

#define hc595_OFF()   GPIO_SetBits(HC595_PORT,HC595_OE); 
#define hc595_ON()    GPIO_ResetBits(HC595_PORT,HC595_OE); 

extern uint8_t HC595_Data[5];
//其他引脚连接
//Reset(PIN10)=VCC
//SQh(PIN9)(级联输出端)=下一个595的输入端
//程序里没有把OE接地，例程需要手动接地！
void hc595_init(void);
void hc595_input(uint8_t byte);
void hc595_latch(void);
void hc595_WriteBytes(u8 *data,u8 num);
void hc595_off(void);
#endif
