#include "bsp_74hc595.h"

uint8_t HC595_Data[5]={0};

void hc595_delay(u32 i)
{
  u8 j=0;
  for(j=0;j<0x1f;j++)
    while(i)i--;
}

/*
* Function:初始化595所用引脚
*/
void hc595_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(HC595_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = HC595_DATA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HC595_SCLK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HC595_RCLK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = HC595_OE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);
  
	GPIO_ResetBits(HC595_PORT, HC595_DATA);
	GPIO_ResetBits(HC595_PORT, HC595_SCLK);
	GPIO_ResetBits(HC595_PORT, HC595_RCLK);
	GPIO_ResetBits(HC595_PORT, HC595_OE);
}

/*
* Function:写入数据到移位寄存器里，先写低位
*/
void hc595_input(uint8_t byte)
{
	uint8_t i, num;
	num = byte;
	for (i=0; i<8; i++)
	{
		GPIO_ResetBits(HC595_PORT, HC595_SCLK);
		if ((num&0x01)==0x01)
			GPIO_SetBits(HC595_PORT, HC595_DATA);
		else
			GPIO_ResetBits(HC595_PORT, HC595_DATA);
		GPIO_SetBits(HC595_PORT, HC595_SCLK);
		num = num>>1;
    hc595_delay(1);
	}
}

/*
* Function:将数据从移位寄存器锁存到输出寄存器上
*/
void hc595_latch(void)
{
	GPIO_ResetBits(HC595_PORT, HC595_RCLK);
	GPIO_SetBits(HC595_PORT, HC595_RCLK);
  hc595_delay(1);
	GPIO_ResetBits(HC595_PORT, HC595_RCLK);
}

//功能：向595写入一串数据
//参数1：数组指针，每个字节为当前芯片的显示内容
//参数2：数组长度，等于级联的芯片数量减1
void hc595_WriteBytes(u8 *data,u8 num)
{
  u8 i;
  for(i=0;i<num;i++)
    hc595_input(data[i]);
  hc595_delay(1);
  hc595_latch();
}

void hc595_off(void)
{
  
}
