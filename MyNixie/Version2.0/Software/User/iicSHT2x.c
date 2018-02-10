#include "iicSHT2x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/10 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
void SHT2x_IIC_Delay(void)
{
	uint8_t i;

	/*��
	 	�����ʱ����ͨ��������AX-Pro�߼������ǲ��Եõ��ġ�
		CPU��Ƶ72MHzʱ�����ڲ�Flash����, MDK���̲��Ż�
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
        
    IAR���̱���Ч�ʸߣ���������Ϊ7
	*/
	for (i = 0; i < 7; i++);
}

//��ʼ��IIC
void SHT2x_IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
  //��ʹ������IO PORTCʱ�� 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	SHT2x_IIC_SCL=1;
	SHT2x_IIC_SDA=1;

}
//����IIC��ʼ�ź�
void SHT2x_IIC_Start(void)
{
	SHT2x_SDA_OUT();     //sda�����
	SHT2x_IIC_SDA=1;	  	  
	SHT2x_IIC_SCL=1;
	SHT2x_IIC_Delay();//4
 	SHT2x_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	SHT2x_IIC_Delay();//4
	SHT2x_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
	SHT2x_IIC_Delay();//4
}	  
//����IICֹͣ�ź�
void SHT2x_IIC_Stop(void)
{
	SHT2x_SDA_OUT();//sda�����
	SHT2x_IIC_SCL=0;
	SHT2x_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	SHT2x_IIC_Delay();//4;
	SHT2x_IIC_SCL=1; 
		SHT2x_IIC_Delay();//1
	SHT2x_IIC_SDA=1;//����I2C���߽����ź�
	SHT2x_IIC_Delay();//4							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 SHT2x_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SHT2x_SDA_IN();      //SDA����Ϊ����  
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
	SHT2x_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void SHT2x_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SHT2x_SDA_OUT(); 	    
    SHT2x_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        SHT2x_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		SHT2x_IIC_Delay();   //��TEA5767��������ʱ���Ǳ����  5
		SHT2x_IIC_SCL=1;
		SHT2x_IIC_Delay();//5 
		SHT2x_IIC_SCL=0;	
		SHT2x_IIC_Delay();//5
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 SHT2x_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SHT2x_SDA_IN();//SDA����Ϊ����
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
        SHT2x_IIC_NAck();//����nACK
    else
        SHT2x_IIC_Ack(); //����ACK   
    return receive;
}



























