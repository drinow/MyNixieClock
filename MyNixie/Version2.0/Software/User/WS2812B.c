#include "WS2812B.h"

__IO u8 GammaLUT[256]={0};//Gamma Look Up Table
__IO u8 WS2812_RGB[WS2812_NUM][3];
__IO u8 RcdMAX_RGB[WS2812_NUM][3];

__IO RGB_TypeDef RGB_Msg={255,128,64,SINGLECOLOR,EFFECTS_ON};
//__IO RGB_TypeDef RGB_Rcd={255,128,64,1,255,0};//��¼Msg
  
//����gammaУ����
void BuildGammaCorrectionTable(void)
{
    #define GammaON 0
    #if GammaON
        int i;
        float f;
        float Precompensation=0.7;
        for( i=0;i<256;i++)
        {
         f=i/256.0;//��һ��
         f=(float)pow(f,Precompensation);
         GammaLUT[i]=(u8)(f*256.0+0.5);//����һ��
        }
    #else
        int i;
        for( i=0;i<256;i++)
        {
         GammaLUT[i]=i;
        }
    #endif
}

void WS2812_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_WS2812, ENABLE);

    GPIO_InitStructure.GPIO_Pin = Pin_WS2812;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_WS2812, &GPIO_InitStructure);
    BuildGammaCorrectionTable();
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

/*******************����1�뺯��,�ߵ�ƽ800ns,����1.25us*************************/
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

/***********************����1���ֽ�����,��λ�ȷ�*******************************/
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
/******************************����1֡����*************************************/
extern float LightCoe;//����ϵ��
void WS2812_Send_Px(void)
{
	unsigned int row,line;
	for(line=0;line<WS2812_NUM;line++)
	{
    //ǿ��ת��Ϊ1ά����
    for(row=0;row<3;row++)
        if(GetTime.hour>=22||GetTime.hour<6)
            WS2812_Send_Data(GammaLUT[(u8)(WS2812_RGB[line][row]*LightCoe*0.2)]);
        else
            WS2812_Send_Data(GammaLUT[(u8)(WS2812_RGB[line][row]*LightCoe)]); 
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

//������ɫ��Ϣ
//num:���ӱ�ţ�0-3��
//type:��ɫ���ͣ�G-0��R-1��B-2��
//value:��ɫǿ�ȣ�0-255��
u8 TubeFillColor(u8 num,u8 type,u8 value)
{
    WS2812_RGB[num][type]=value;
    return value;
}
//���������ɫ��Ϣ
//num:���ӱ�ţ�0-3��
//type:��ɫ���ͣ�G-0��R-1��B-2��
//value:��ɫǿ�ȣ�0-255��
void TubeMaxRGB(u8 num,u8 type,u8 value)
{
    RcdMAX_RGB[num][type]=value;
}

//���Ӻ���Ч��
//num ���ӱ��
void TubeBreath(u8 num)
{
    static float step[WS2812_NUM]={0};
    #define STEPLENGTH 2*3.1415926/256
    WS2812_RGB[num][GREEN]=sin(step[num])*RcdMAX_RGB[num][GREEN];
    WS2812_RGB[num][RED]  =sin(step[num])*RcdMAX_RGB[num][RED];
    WS2812_RGB[num][BLUE] =sin(step[num])*RcdMAX_RGB[num][BLUE];
    step[num]+=STEPLENGTH;

//    static u8 Rdown=0,Gdown=0,Bdown=0;
//    
//    if(Rdown)
//        WS2812_RGB[num][RED]--;
//    else
//        WS2812_RGB[num][RED]++;
//    if(Gdown)
//        WS2812_RGB[num][GREEN]--;
//    else
//        WS2812_RGB[num][GREEN]++;
//    if(Bdown)
//        WS2812_RGB[num][BLUE]--;
//    else
//        WS2812_RGB[num][BLUE]++;
//    
//    if(RcdMAX_RGB[num][RED]==0)WS2812_RGB[num][RED]=0;
//    if(RcdMAX_RGB[num][GREEN]==0)WS2812_RGB[num][GREEN]=0;
//    if(RcdMAX_RGB[num][BLUE]==0)WS2812_RGB[num][BLUE]=0;
//    
//    if(WS2812_RGB[num][RED]==RcdMAX_RGB[num][RED])Rdown=1;
//    else if(WS2812_RGB[num][RED]==0)Rdown=0;
//    if(WS2812_RGB[num][GREEN]==RcdMAX_RGB[num][GREEN])Gdown=1;
//    else if(WS2812_RGB[num][GREEN]==0)Gdown=0;
//    if(WS2812_RGB[num][BLUE]==RcdMAX_RGB[num][BLUE])Bdown=1;
//    else if(WS2812_RGB[num][BLUE]==0)Bdown=0;
}

//���Ӳʺ�Ч��
//num ���ӱ��
u8 RainBowstate[WS2812_NUM]={0,1,2,3};
void TubeRainbow(u8 num)
{
    //�����ӳ�ʼ״̬
    
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

//WS2812����Ч����
//������RGB��Ϣ�����ȵȼ����Ƿ��������ɫģʽ
//RGB:0-255
//LEVEL:0-255
//mode:0-SingleColour;1-MultiColour
extern __IO u16 LightLevel;
//����ʹ�õ�����
float Ruse=0,Guse=0,Buse=0;
void WS2812_Breath(void)
{
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
                        if(WS2812_RGB[TUBE0][RED]>=255)MultiColorState++;break;//�����ǵ���
                    case 1:
                        WS2812_RGB[TUBE0][GREEN]++;
                        WS2812_RGB[TUBE1][GREEN]++;
                        WS2812_RGB[TUBE2][GREEN]++;
                        WS2812_RGB[TUBE3][GREEN]++;
                        if(WS2812_RGB[TUBE3][GREEN]>=255)MultiColorState++;break;//��ʱ���Ǳ�ɫ
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
                        if(WS2812_RGB[TUBE3][BLUE]<=0)MultiColorState=1;break;//��Ӧ�ô�0��ʼ
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

//����������ǿ��д��RGB��Ϣ
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
        case 0:WS2812_RGB[row][line]=G;break;//R��G����һ�£���Ϊ�����岻һ��
        case 1:WS2812_RGB[row][line]=R;break;
        case 2:WS2812_RGB[row][line]=B;break;
      }
    }
       
  WS2812_Send_Px();
		
	__enable_irq();
}



