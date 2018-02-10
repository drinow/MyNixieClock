#ifndef __MYIIC_H
#define __MYIIC_H
#include "stm32f10x.h"

//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 

//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 
   	   		   
//IO��������
#define SHT2x_SDA_IN()  {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=8<<16;}
#define SHT2x_SDA_OUT() {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=3<<16;}

//IO��������	 
#define SHT2x_IIC_SCL    PAout(7) //SCL
#define SHT2x_IIC_SDA    PAout(12) //SDA	 
#define SHT2x_READ_SDA   PAin(12)  //����SDA 
//#define SHT2x_SDA_IN()  {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=8<<28;}
//#define SHT2x_SDA_OUT() {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=3<<28;}

////IO��������	 
//#define SHT2x_IIC_SCL    PAout(12) //SCL
//#define SHT2x_IIC_SDA    PAout(7) //SDA	 
//#define SHT2x_READ_SDA   PAin(7)  //����SDA 

//IIC���в�������
void SHT2x_IIC_Init(void);                //��ʼ��IIC��IO��				 
void SHT2x_IIC_Start(void);				//����IIC��ʼ�ź�
void SHT2x_IIC_Stop(void);	  			//����IICֹͣ�ź�
void SHT2x_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 SHT2x_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 SHT2x_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void SHT2x_IIC_Ack(void);					//IIC����ACK�ź�
void SHT2x_IIC_NAck(void);				//IIC������ACK�ź�

void SHT2x_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 SHT2x_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















