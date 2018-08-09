#include "WS2812B.h"

__IO u8 WS2812_RGB[WS2812_NUM][3];
__IO u8 RcdMAX_RGB[WS2812_NUM][3];

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
extern float LightCoe;//亮度系数
void WS2812_Send_Px(void)
{
	unsigned int row,line;
	for(line=0;line<WS2812_NUM;line++)
	{
    //强制转换为1维数组
    for(row=0;row<3;row++)
      WS2812_Send_Data(WS2812_RGB[line][row]*LightCoe); 
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

//管子颜色信息
//num:管子编号（0-3）
//type:基色类型（G-0，R-1，B-2）
//value:颜色强度（0-255）
u8 TubeFillColor(u8 num,u8 type,u8 value)
{
    WS2812_RGB[num][type]=value;
    return value;
}
//管子最大颜色信息
//num:管子编号（0-3）
//type:基色类型（G-0，R-1，B-2）
//value:颜色强度（0-255）
void TubeMaxRGB(u8 num,u8 type,u8 value)
{
    RcdMAX_RGB[num][type]=value;
}

//管子呼吸效果
//num 管子编号
void TubeBreath(u8 num)
{
    static float step[WS2812_NUM]={0};
    #define STEPLENGTH 2*3.1415926/256
    WS2812_RGB[num][GREEN]=sin(step[num])*RcdMAX_RGB[num][GREEN];
    WS2812_RGB[num][RED]  =sin(step[num])*RcdMAX_RGB[num][RED];
    WS2812_RGB[num][BLUE] =sin(step[num])*RcdMAX_RGB[num][BLUE];
    step[num]+=STEPLENGTH;
}

//管子彩虹效果
//num 管子编号
u8 RainBowstate[WS2812_NUM]={0,1,2,3};
void TubeRainbow(u8 num)
{
    //各管子初始状态
    
    switch(RainBowstate[num])
    {
        case 0:
            WS2812_RGB[num][BLUE]++;
            if(WS2812_RGB[num][BLUE]>=255)RainBowstate[num]++;break;
        case 1:
            WS2812_RGB[num][RED]--;
            if(WS2812_RGB[num][RED]<=0)RainBowstate[num]++;break;
        case 2:
            WS2812_RGB[num][GREEN]++;
            if(WS2812_RGB[num][GREEN]>=255)RainBowstate[num]++;break;
        case 3:
            WS2812_RGB[num][BLUE]--;
            if(WS2812_RGB[num][BLUE]<=0)RainBowstate[num]++;break;
        case 4:
            WS2812_RGB[num][RED]++;
            if(WS2812_RGB[num][RED]>=255)RainBowstate[num]++;break;
        case 5:
            WS2812_RGB[num][GREEN]--;
            if(WS2812_RGB[num][GREEN]<=0)RainBowstate[num]=0;break;
        default:break;
    }
}

//WS2812灯特效控制
//参数：RGB信息、亮度等级、是否呼吸，颜色模式
//RGB:0-255
//LEVEL:0-255
//mode:0-SingleColour;1-MultiColour
extern __IO u16 LightLevel;
//真正使用的数据
float Ruse=0,Guse=0,Buse=0;
void WS2812_Breath(void)
{
//    //数据更新记录
//    static u8 Rmax=0,Gmax=0,Bmax=0;
//    static u8 MultiColorState=0;//彩色状态机控制
//    static float step=0.0;//单色移步控制
//    u8 row=0,line=0;

//    //RGB数据更新
//    if(Rmax!=RGB_Msg.R||Gmax!=RGB_Msg.G||Bmax!=RGB_Msg.B)
//    {
//        Rmax=RGB_Msg.R;Gmax=RGB_Msg.G;Bmax=RGB_Msg.B;
//        Ruse=0;Guse=0;Buse=0;
//        step=0;//从0开始
//        MultiColorState=0;//用状态机控制
//    }
//  
//    //渐变
//    if(RGB_Msg.state==EFFECTS_ON)
//    {
//        if(RGB_Msg.mode==SINGLECOLOR)
//        {
//        //			Ruse=Rmax*LightCoe*sin(step);//正弦曲线
//        //			Guse=Gmax*LightCoe*sin(step);
//        //			Buse=Bmax*LightCoe*sin(step);
//        //			if(Ruse<0)Ruse=-Ruse;
//        //			if(Guse<0)Guse=-Guse;
//        //			if(Buse<0)Buse=-Buse;

//            Ruse=Rmax*LightCoe*SCurve(step);//S型曲线
//            Guse=Gmax*LightCoe*SCurve(step);
//            Buse=Bmax*LightCoe*SCurve(step);
//            if(step>TurnPoint*2)step=0;
//            step+=STEPSIZE;
//        }
//        if(RGB_Msg.mode==MULTICOLOR)
//        {
//            switch(MultiColorState)
//            {
//                case 0:Ruse+=0.2;if(Ruse>250*LightCoe)MultiColorState++;break;//首先是点亮
//                case 1:Guse+=0.2;if(Guse>250*LightCoe)MultiColorState++;break;//此时才是变色
//                case 2:Ruse-=0.2;if(Ruse<=0)MultiColorState++;break;
//                case 3:Buse+=0.2;if(Buse>250*LightCoe)MultiColorState++;break;
//                case 4:Guse-=0.2;if(Guse<=0)MultiColorState++;break;
//                case 5:Ruse+=0.2;if(Ruse>250*LightCoe)MultiColorState++;break;
//                case 6:Buse-=0.2;if(Buse<=0)MultiColorState=1;break;//不应该从0开始
//                default:break;
//            }
//        }
//    }
//    else if(RGB_Msg.state==EFFECTS_OFF)
//    {
//        Ruse=RGB_Msg.R;//若state无变化，则RGB信息由Flash读出
//        Guse=RGB_Msg.G;
//        Buse=RGB_Msg.B;
//    }
//    
//    if(RGB_Msg.mode!=RAINBOW)
//    {
//        //数据填充
//        for(row=0;row<WS2812_NUM;row++)
//        for(line=0;line<3;line++)
//        {
//          switch(line)
//          {
//            case 0:WS2812_RGB[row][line]=Guse;break;//R、G调换一下，因为好像定义不一样
//            case 1:WS2812_RGB[row][line]=Ruse;break;
//            case 2:WS2812_RGB[row][line]=Buse;break;
//          }
//        }
//    }
//    else
//    {
//        //数据填充
//        for(row=0;row<WS2812_NUM;row++)
//        for(line=0;line<3;line++)
//        {
//          switch(line)
//          {
//            case 0:WS2812_RGB[row][line]=Guse;break;//R、G调换一下，因为好像定义不一样
//            case 1:WS2812_RGB[row][line]=Ruse;break;
//            case 2:WS2812_RGB[row][line]=Buse;break;
//          }
//        }
//    }

//    //熄灭
//    if(RGB_Msg.state==RGB_OFF||(RGB_Msg.R==0&&RGB_Msg.G==0&&RGB_Msg.B==0)||LightCoe==0) memset((u8*)WS2812_RGB,0,sizeof(WS2812_RGB));
//  
//    __disable_irq();
//    WS2812_Send_Px();
//    __enable_irq();



    u8 i=0;
    static u8 MultiColorState=0;
    if(RGB_Msg.state==EFFECTS_ON)
    {
        if(RGB_Msg.mode==RAINBOW)
        {
            for(i=TUBE0;i<=TUBE3;i++)
                TubeRainbow(i);
        }
        else
        {
            if(RGB_Msg.mode==SINGLECOLOR)
            {
                for(i=TUBE0;i<=TUBE3;i++)
                    TubeBreath(i);
            }
            if(RGB_Msg.mode==MULTICOLOR)
            {
                switch(MultiColorState)
                {
                    case 0:
                        WS2812_RGB[TUBE0][RED]++;
                        WS2812_RGB[TUBE1][RED]++;
                        WS2812_RGB[TUBE2][RED]++;
                        WS2812_RGB[TUBE3][RED]++;
                        if(WS2812_RGB[TUBE0][RED]>=255)MultiColorState++;break;//首先是点亮
                    case 1:
                        WS2812_RGB[TUBE0][GREEN]++;
                        WS2812_RGB[TUBE1][GREEN]++;
                        WS2812_RGB[TUBE2][GREEN]++;
                        WS2812_RGB[TUBE3][GREEN]++;
                        if(WS2812_RGB[TUBE3][GREEN]>=255)MultiColorState++;break;//此时才是变色
                    case 2:
                        WS2812_RGB[TUBE0][RED]--;
                        WS2812_RGB[TUBE1][RED]--;
                        WS2812_RGB[TUBE2][RED]--;
                        WS2812_RGB[TUBE3][RED]--;
                        if(WS2812_RGB[TUBE3][RED]<=0)MultiColorState++;break;
                    case 3:
                        WS2812_RGB[TUBE0][BLUE]++;
                        WS2812_RGB[TUBE1][BLUE]++;
                        WS2812_RGB[TUBE2][BLUE]++;
                        WS2812_RGB[TUBE3][BLUE]++;
                        if(WS2812_RGB[TUBE3][BLUE]>=255)MultiColorState++;break;
                    case 4:
                        WS2812_RGB[TUBE0][GREEN]--;
                        WS2812_RGB[TUBE1][GREEN]--;
                        WS2812_RGB[TUBE2][GREEN]--;
                        WS2812_RGB[TUBE3][GREEN]--;
                        if(WS2812_RGB[TUBE3][GREEN]<=0)MultiColorState++;break;
                    case 5:
                        WS2812_RGB[TUBE0][RED]++;
                        WS2812_RGB[TUBE1][RED]++;
                        WS2812_RGB[TUBE2][RED]++;
                        WS2812_RGB[TUBE3][RED]++;
                        if(WS2812_RGB[TUBE3][RED]>=255)MultiColorState++;break;
                    case 6:
                        WS2812_RGB[TUBE0][BLUE]--;
                        WS2812_RGB[TUBE1][BLUE]--;
                        WS2812_RGB[TUBE2][BLUE]--;
                        WS2812_RGB[TUBE3][BLUE]--;
                        if(WS2812_RGB[TUBE3][BLUE]<=0)MultiColorState=1;break;//不应该从0开始
                    default:break;
                }
            }
        }
    }
    else if(RGB_Msg.state==EFFECTS_OFF)
    {
    }
    
    if(RGB_Msg.state==RGB_OFF)
    {
        memset((u8*)WS2812_RGB,0,sizeof(WS2812_RGB));
        MultiColorState=0;
    }
        
    __disable_irq();
    WS2812_Send_Px();
    __enable_irq();
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
