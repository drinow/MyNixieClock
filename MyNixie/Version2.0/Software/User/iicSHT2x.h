#ifndef __MYIIC_H
#define __MYIIC_H
#include "stm32f10x.h"

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 
   	   		   
//IO方向设置
#define SHT2x_SDA_IN()  {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=8<<16;}
#define SHT2x_SDA_OUT() {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=3<<16;}

//IO操作函数	 
#define SHT2x_IIC_SCL    PAout(7) //SCL
#define SHT2x_IIC_SDA    PAout(12) //SDA	 
#define SHT2x_READ_SDA   PAin(12)  //输入SDA 
//#define SHT2x_SDA_IN()  {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=8<<28;}
//#define SHT2x_SDA_OUT() {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=3<<28;}

////IO操作函数	 
//#define SHT2x_IIC_SCL    PAout(12) //SCL
//#define SHT2x_IIC_SDA    PAout(7) //SDA	 
//#define SHT2x_READ_SDA   PAin(7)  //输入SDA 

//IIC所有操作函数
void SHT2x_IIC_Init(void);                //初始化IIC的IO口				 
void SHT2x_IIC_Start(void);				//发送IIC开始信号
void SHT2x_IIC_Stop(void);	  			//发送IIC停止信号
void SHT2x_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 SHT2x_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 SHT2x_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void SHT2x_IIC_Ack(void);					//IIC发送ACK信号
void SHT2x_IIC_NAck(void);				//IIC不发送ACK信号

void SHT2x_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 SHT2x_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















