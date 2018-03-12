#include "WS2812B.h"

u8 WS2812_RGB[WS2812_NUM][3];

void WS2812_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_WS2812, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = Pin_WS2812;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(PORT_WS2812, &GPIO_InitStructure);
}


void WS2812_Send_0()   
{
	 WS2812_Set;
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();  
	 WS2812_Reset; 
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();  __NOP();__NOP();__NOP();
}

/*******************发送1码函数,高电平800ns,周期1.25us*************************/
void WS2812_Send_1()    
{
	 WS2812_Set;
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();  __NOP();__NOP();__NOP();
	 WS2812_Reset; 
   __NOP();__NOP();__NOP();__NOP();__NOP();
}

/***********************发送1个字节数据,高位先发*******************************/
void WS2812_Send_Data(unsigned char DATA)		
{
  u8 i=0;
  for(i=0;i<8;i++)
  {
    if(DATA&(0x80>>i))
      WS2812_Send_1();
    else
      WS2812_Send_0();
  }
}
/******************************发送1帧数据*************************************/
void WS2812_Send_Px(void)
{
	unsigned int row,line;
	for(line=0;line<WS2812_NUM;line++)
	{
    //强制转换为1维数组
    for(row=0;row<3;row++)
      WS2812_Send_Data(WS2812_RGB[line][row]); 
	}
}


void WS2812_Breath(u8 Red,u8 Green,u8 Blue,u8 level)
{
  static u8 Rold=0,Gold=0,Bold=0;
  static u8 Ruse=0,Guse=0,Buse=0;
  static u8 Rdirect=1,Gdirect=1,Bdirect=1;
  u8 update=0;
  u8 row=0,line=0;
  if(Rold!=Red||Gold!=Green||Bold!=Blue)
  {
    Rold=Red;Gold=Green;Bold=Blue;
    update=1;
  }
  if(update)
  {
    Ruse=Rold;Guse=Gold;Buse=Bold;
  }
  
  if(Rdirect) Ruse+=5; else Ruse-=5;
  if(Gdirect) Guse+=5; else Guse-=5;
  if(Bdirect) Buse+=5; else Buse-=5;
  
  if(Ruse>level)Rdirect=0;if(Ruse<5)Rdirect=1;
  if(Guse>level)Gdirect=0;if(Guse<5)Gdirect=1;
  if(Buse>level)Bdirect=0;if(Buse<5)Bdirect=1;
  
  for(row=0;row<WS2812_NUM;row++)
    for(line=0;line<3;line++)
    {
      switch(line)
      {
        case 0:WS2812_RGB[row][line]=Ruse;break;
        case 1:WS2812_RGB[row][line]=Guse;break;
        case 2:WS2812_RGB[row][line]=Buse;break;
      }
    }
  
  WS2812_Send_Px();
}

