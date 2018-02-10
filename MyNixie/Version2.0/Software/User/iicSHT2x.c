#include "iicSHT2x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//IIC 驱动函数	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/10 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
void SHT2x_IIC_Delay(void)
{
	uint8_t i;

	/*　
	 	下面的时间是通过安富莱AX-Pro逻辑分析仪测试得到的。
		CPU主频72MHz时，在内部Flash运行, MDK工程不优化
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
        
    IAR工程编译效率高，不能设置为7
	*/
	for (i = 0; i < 7; i++);
}

//初始化IIC
void SHT2x_IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
  //先使能外设IO PORTC时钟 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	SHT2x_IIC_SCL=1;
	SHT2x_IIC_SDA=1;

}
//产生IIC起始信号
void SHT2x_IIC_Start(void)
{
	SHT2x_SDA_OUT();     //sda线输出
	SHT2x_IIC_SDA=1;	  	  
	SHT2x_IIC_SCL=1;
	SHT2x_IIC_Delay();//4
 	SHT2x_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	SHT2x_IIC_Delay();//4
	SHT2x_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
	SHT2x_IIC_Delay();//4
}	  
//产生IIC停止信号
void SHT2x_IIC_Stop(void)
{
	SHT2x_SDA_OUT();//sda线输出
	SHT2x_IIC_SCL=0;
	SHT2x_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	SHT2x_IIC_Delay();//4;
	SHT2x_IIC_SCL=1; 
		SHT2x_IIC_Delay();//1
	SHT2x_IIC_SDA=1;//发送I2C总线结束信号
	SHT2x_IIC_Delay();//4							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 SHT2x_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SHT2x_SDA_IN();      //SDA设置为输入  
	SHT2x_IIC_SDA=1;SHT2x_IIC_Delay();//1	   
	SHT2x_IIC_SCL=1;SHT2x_IIC_Delay();//1	 
	while(SHT2x_READ_SDA)
	{
		ucErrTime++;
	//	SHT2x_IIC_Delay(1);
		if(ucErrTime>250)
		{
			SHT2x_IIC_Stop();
			return 1;
		}
	}
	SHT2x_IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void SHT2x_IIC_Ack(void)
{
	SHT2x_IIC_SCL=0;
	SHT2x_SDA_OUT();
	SHT2x_IIC_SDA=0;
	SHT2x_IIC_Delay();SHT2x_IIC_Delay();SHT2x_IIC_Delay();//20
	SHT2x_IIC_SCL=1;
	SHT2x_IIC_Delay();//2
	SHT2x_IIC_SCL=0;
}
//不产生ACK应答		    
void SHT2x_IIC_NAck(void)
{
	SHT2x_IIC_SCL=0;
	SHT2x_SDA_OUT();
	SHT2x_IIC_SDA=1;
	SHT2x_IIC_Delay();//5
	SHT2x_IIC_SCL=1;
	SHT2x_IIC_Delay();//5
	SHT2x_IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void SHT2x_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SHT2x_SDA_OUT(); 	    
    SHT2x_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        SHT2x_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		SHT2x_IIC_Delay();   //对TEA5767这三个延时都是必须的  5
		SHT2x_IIC_SCL=1;
		SHT2x_IIC_Delay();//5 
		SHT2x_IIC_SCL=0;	
		SHT2x_IIC_Delay();//5
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 SHT2x_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SHT2x_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
    SHT2x_IIC_SCL=0; 
    SHT2x_IIC_Delay();//5
		SHT2x_IIC_SCL=1;
    receive<<=1;
    if(SHT2x_READ_SDA)receive++;   
		SHT2x_IIC_Delay(); //5
    }					 
    if (!ack)
        SHT2x_IIC_NAck();//发送nACK
    else
        SHT2x_IIC_Ack(); //发送ACK   
    return receive;
}



























