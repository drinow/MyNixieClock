#include "TM1812.h"


//行表示灯的数量，列表示RGB数据
u8 TM1812_RGB[TM1812_NUM*4][3]={0};

void TM1812_Init(void)
{
//		GPIO_InitTypeDef GPIO_InitStructure;

//		RCC_APB2PeriphClockCmd(RCC_TM1812, ENABLE);
//		
//		GPIO_InitStructure.GPIO_Pin = Pin_TM1812;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_Init(PORT_TM1812, &GPIO_InitStructure);

		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TM1812_Send_0()   
{
	 TM1812_Set;
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();  
	 TM1812_Reset; 
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();  __NOP();__NOP();__NOP();
}

/*******************发送1码函数,高电平800ns,周期1.25us*************************/
void TM1812_Send_1()    
{
	 TM1812_Set;
	 __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();	 __NOP();__NOP();__NOP();__NOP();__NOP();
   __NOP();__NOP();__NOP();__NOP();__NOP();  __NOP();__NOP();__NOP();
	 TM1812_Reset; 
   __NOP();__NOP();__NOP();__NOP();__NOP();
}

/***********************发送1个字节数据,高位先发*******************************/
void TM1812_Send_Data(unsigned char DATA)		
{
  u8 i=0;
  for(i=0;i<8;i++)
  {
    if(DATA&(0x80>>i))
      TM1812_Send_1();
    else
      TM1812_Send_0();
  }
}

/******************************发送1帧数据*************************************/
void TM1812_Send_Px(void)
{
	unsigned int row,line;
	for(line=0;line<TM1812_NUM*4;line++)
	{
    for(row=0;row<3;row++)
      TM1812_Send_Data(TM1812_RGB[line][row]); 
	}
}


void TM1812_Flash_Test(void)
{
  static u8 state=0;
  u8 row=0,line=0;
  for(row=0;row<TM1812_NUM*4;row++)
    for(line=0;line<3;line++)
    {
      if(state)
        TM1812_RGB[row][line]=0xff;
      else
        TM1812_RGB[row][line]=0;
    }
    
  state=~state;
    
//    if(state)
//    {
//      TM1812_RGB[0][0]=255; TM1812_RGB[0][1]=255; TM1812_RGB[0][2]=255; 
//      TM1812_RGB[1][0]=0; TM1812_RGB[1][1]=0; TM1812_RGB[1][2]=0;
//      TM1812_RGB[2][0]=255; TM1812_RGB[2][1]=255; TM1812_RGB[2][2]=255;
//      TM1812_RGB[3][0]=0; TM1812_RGB[3][1]=0; TM1812_RGB[3][2]=0; 
//    }
//    else
//    {
//      TM1812_RGB[0][0]=0; TM1812_RGB[0][1]=0; TM1812_RGB[0][2]=0; 
//      TM1812_RGB[1][0]=255; TM1812_RGB[1][1]=255; TM1812_RGB[1][2]=255;
//      TM1812_RGB[2][0]=0; TM1812_RGB[2][1]=0; TM1812_RGB[2][2]=0;
//      TM1812_RGB[3][0]=255; TM1812_RGB[3][1]=255; TM1812_RGB[3][2]=255;
//    }  
  TM1812_Send_Px();
}
