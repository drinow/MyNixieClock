#include "SHT2x.h"
#include "iicSHT2x.h"
#include "bsp_SysTick.h"
#include <stdio.h>

SHT2x_data SHT20;

void SHT2X_Delay_ms(u16 cnt)
{
	Delay_Tk(cnt);
}

u8 SHT2x_Init(void)
{
    u8 err;
    SHT2x_IIC_Init();
    err = SHT2x_SoftReset();
    return err;
}

u8 SHT2x_SoftReset(void) //SHT20软件复位
{
    u8 err=0;
    SHT2x_IIC_Start();
    SHT2x_IIC_Send_Byte(0x80);
    err = SHT2x_IIC_Wait_Ack();
    SHT2x_IIC_Send_Byte(0xFE);
    err = SHT2x_IIC_Wait_Ack();
    SHT2x_IIC_Stop();
    return err;
}
float SHT2x_GetTempPoll(void)
{
    float TEMP;
    u8 ack, tmp1, tmp2;
    u16 ST;
    u16 i=0;
    SHT2x_IIC_Start();				//发送IIC开始信号
    SHT2x_IIC_Send_Byte(SHT2x_ADR_W);			//IIC发送一个字节 
    ack = SHT2x_IIC_Wait_Ack();	
    SHT2x_IIC_Send_Byte(TRIG_TEMP_MEASUREMENT_POLL);
    ack = SHT2x_IIC_Wait_Ack();

    do{
        SHT2X_Delay_ms(5);               
        SHT2x_IIC_Start();				//发送IIC开始信号
        SHT2x_IIC_Send_Byte(SHT2x_ADR_R);	
        i++;
        ack = SHT2x_IIC_Wait_Ack();
        if(i==100)break;
    } while(ack!=0);
    tmp1 = SHT2x_IIC_Read_Byte(1);
    tmp2 = SHT2x_IIC_Read_Byte(1);
		 SHT2x_IIC_Read_Byte(1);
    SHT2x_IIC_Stop();
    
    ST = (tmp1 << 8) | (tmp2 << 0);
	
    ST &= ~0x0003;
    TEMP = ((float)ST * 0.00268127) - 46.85;

    return (TEMP);	  
}

float SHT2x_GetHumiPoll(void)
{
    float HUMI;
    u8 ack, tmp1, tmp2;
    u16 SRH;
    u16 i=0;

    SHT2x_IIC_Start();				//发送IIC开始信号
    SHT2x_IIC_Send_Byte(SHT2x_ADR_W);			//IIC发送一个字节 
    ack = SHT2x_IIC_Wait_Ack();	
    SHT2x_IIC_Send_Byte(TRIG_HUMI_MEASUREMENT_POLL);
    ack = SHT2x_IIC_Wait_Ack();    
    do {
        SHT2X_Delay_ms(5);               
        SHT2x_IIC_Start();				//发送IIC开始信号
        SHT2x_IIC_Send_Byte(SHT2x_ADR_R);	
        i++;
        ack = SHT2x_IIC_Wait_Ack();
        if(i==100)break;
    } while(ack!=0);
    
    tmp1 = SHT2x_IIC_Read_Byte(1);

    tmp2 = SHT2x_IIC_Read_Byte(1);
    SHT2x_IIC_Read_Byte(1);
    SHT2x_IIC_Stop();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    HUMI = ((float)SRH * 0.00190735) - 6;

    return (HUMI);
}


