#include "WS2812B.h"

__IO u8 WS2812_RGB[WS2812_NUM][3];

__IO RGB_TypeDef RGB_Msg={255,128,64,SINGLECOLOR,EFFECTS_ON};
//__IO RGB_TypeDef RGB_Rcd={255,128,64,1,255,0};//记录Msg
  
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

float SCurve(float Xvalue)
{
	float y=0;
	if(Xvalue<TurnPoint)
		y=1/( 1+pow(loge,-(Xvalue-TurnPoint/2) ) );
	else if(Xvalue<2*TurnPoint)
	{
		y=1-1/(1+pow(loge,-(Xvalue-3*TurnPoint/2.0)) );
	}
	
	return y;
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
  static u8 Rmax=0,Gmax=0,Bmax=0;
	static u8 MultiColorState=0;//彩色状态机控制
	static float step=0.0;//单色移步控制
  u8 row=0,line=0;
  
  //RGB数据更新
  if(Rmax!=RGB_Msg.R||Gmax!=RGB_Msg.G||Bmax!=RGB_Msg.B)
  {
    Rmax=RGB_Msg.R;Gmax=RGB_Msg.G;Bmax=RGB_Msg.B;
		Ruse=0;Guse=0;Buse=0;
		step=0;//从0开始
		MultiColorState=0;//用状态机控制
  }
  
  //渐变
  if(RGB_Msg.state==EFFECTS_ON)
  {
    if(RGB_Msg.mode==SINGLECOLOR)
    {
//			Ruse=Rmax*LightCoe*sin(step);//正弦曲线
//			Guse=Gmax*LightCoe*sin(step);
//			Buse=Bmax*LightCoe*sin(step);
//			if(Ruse<0)Ruse=-Ruse;
//			if(Guse<0)Guse=-Guse;
//			if(Buse<0)Buse=-Buse;
			
			 Ruse=Rmax*LightCoe*SCurve(step);//S型曲线
			 Guse=Gmax*LightCoe*SCurve(step);
			 Buse=Bmax*LightCoe*SCurve(step);
			 if(step>TurnPoint*2)step=0;
			step+=STEPSIZE;
    }
    if(RGB_Msg.mode==MULTICOLOR)
    {
				switch(MultiColorState)
				{
					case 0:Ruse+=4;if(Ruse>250*LightCoe)MultiColorState++;break;//首先是点亮
					case 1:Guse+=4;if(Guse>250*LightCoe)MultiColorState++;break;//此时才是变色
					case 2:Ruse-=4;if(Ruse==0)MultiColorState++;break;
					case 3:Buse+=4;if(Buse>250*LightCoe)MultiColorState++;break;
					case 4:Guse-=4;if(Guse==0)MultiColorState++;break;
					case 5:Ruse+=4;if(Ruse>250*LightCoe)MultiColorState++;break;
					case 6:Buse-=4;if(Buse==0)MultiColorState=1;break;//不应该从0开始
					default:break;
				}
    }
  }
	else if(RGB_Msg.state==EFFECTS_OFF)
	{
		Ruse=RGB_Msg.R;//若state无变化，则RGB信息由Flash读出
		Guse=RGB_Msg.G;
		Buse=RGB_Msg.B;
	}
  
	//数据填充
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
