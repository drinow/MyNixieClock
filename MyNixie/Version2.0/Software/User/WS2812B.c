#include "WS2812B.h"

static __IO u8 WS2812_RGB[WS2812_NUM][3];

__IO RGB_TypeDef RGB_Msg={255,128,64,1,255,0};
__IO RGB_TypeDef RGB_Rcd={255,128,64,1,255,0};//记录Msg
  
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

//WS2812灯特效控制
//参数：RGB信息、亮度等级、是否呼吸，颜色模式
//RGB:0-255
//LEVEL:0-255
//mode:0-SingleColour;1-MultiColour
extern __IO u8 LightLevel;
extern float LightCoe;
//真正使用的数据
float Ruse=0,Guse=0,Buse=0;
void WS2812_Breath(void)
{
  //数据更新记录
  static u8 Rold=0,Gold=0,Bold=0;

  //方向记录
  static u8 Rdirect=1,Gdirect=1,Bdirect=1;
  u8 row=0,line=0;
  
  //RGB数据更新
  if(Rold!=RGB_Msg.R||Gold!=RGB_Msg.G||Bold!=RGB_Msg.B)
  {
    Rold=RGB_Msg.R;Gold=RGB_Msg.G;Bold=RGB_Msg.B;
    if(RGB_Msg.mode==SINGLECOLOUR)//单色模式按顺序增减
    {
      Ruse=0;Guse=0;Buse=0;//从0开始
    }
    if(RGB_Msg.mode==MULTICOLOUR)//彩色模式等比例增减
    {
      Ruse=Rold;Guse=Gold;Buse=Bold;
    }
  }
  
  //方向控制
  if(RGB_Msg.mode==SINGLECOLOUR)
  {
		//Ruse=0为了重新对齐数据
		if(Ruse+(Rold/85.0)>=Rold*LightCoe){Rdirect=0;}if(Ruse<Rold/85.0&&Rdirect==0){Rdirect=1;Ruse=0;Guse=0;Buse=0;}
		if(Guse+(Rold/85.0)>=Gold*LightCoe){Gdirect=0;}if(Guse<Gold/85.0&&Gdirect==0){Gdirect=1;Ruse=0;Guse=0;Buse=0;}
		if(Buse+(Rold/85.0)>=Bold*LightCoe){Bdirect=0;}if(Buse<Bold/85.0&&Bdirect==0){Bdirect=1;Ruse=0;Guse=0;Buse=0;}
  }
  if(RGB_Msg.mode==MULTICOLOUR)
  {
		if(Ruse+3>(250*LightCoe)){Rdirect=0;}if(Ruse<=3)Rdirect=1;
		if(Guse+3>(250*LightCoe)){Gdirect=0;}if(Guse<=3)Gdirect=1;
		if(Buse+3>(250*LightCoe)){Bdirect=0;}if(Buse<=3)Bdirect=1;  
  }
  
  //渐变
  if(RGB_Msg.state==EFFECTS_ON)
  {
    if(RGB_Msg.mode==SINGLECOLOUR)
    {
    if(Rdirect) {Ruse+=Rold/85.0; }else {Ruse-=Rold/85.0;}//等比例步长
    if(Gdirect) {Guse+=Gold/85.0; }else {Guse-=Gold/85.0;}
    if(Bdirect) {Buse+=Bold/85.0; }else {Buse-=Bold/85.0;}
    
    //=0的颜色信息不应该被修改
    if(Rold==0)Ruse=0;
    if(Gold==0)Guse=0;
    if(Bold==0)Buse=0;
    }
    if(RGB_Msg.mode==MULTICOLOUR)
    {
    if(Rdirect) {Ruse+=3; }else {Ruse-=3;}
    if(Gdirect) {Guse+=3; }else {Guse-=3;}
    if(Bdirect) {Buse+=3; }else {Buse-=3;}  
    }
  }
	else if(RGB_Msg.state==EFFECTS_OFF)
	{
		Ruse=RGB_Msg.R;//若state无变化，则RGB信息由EEPROM读出
		Guse=RGB_Msg.G;
		Buse=RGB_Msg.B;
	}
  
  for(row=0;row<WS2812_NUM;row++)
    for(line=0;line<3;line++)
    {
      switch(line)
      {
        case 0:WS2812_RGB[row][line]=Guse;break;//R、G调换一下，因为好像定义不一样
        case 1:WS2812_RGB[row][line]=Ruse;break;
        case 2:WS2812_RGB[row][line]=Buse;break;
      }
    }
    
  //熄灭
  if(RGB_Msg.state==RGB_OFF||(RGB_Msg.R==0&&RGB_Msg.G==0&&RGB_Msg.B==0)||LightCoe==0) memset((u8*)WS2812_RGB,0,sizeof(WS2812_RGB));
    
  WS2812_Send_Px();
}

//不管条件，强行写入RGB信息
void WS2812_Refresh(u8 R,u8 G,u8 B)
{
	u8 row=0,line=0;
	
	__disable_irq();
	
	memset((u8*)WS2812_RGB,0,sizeof(WS2812_RGB));
	for(row=0;row<WS2812_NUM;row++)
    for(line=0;line<3;line++)
    {
      switch(line)
      {
        case 0:WS2812_RGB[row][line]=G;break;//R、G调换一下，因为好像定义不一样
        case 1:WS2812_RGB[row][line]=R;break;
        case 2:WS2812_RGB[row][line]=B;break;
      }
    }
       
  WS2812_Send_Px();
		
	__enable_irq();
}
