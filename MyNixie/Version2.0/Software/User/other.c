#include "other.h"

//��ʾ���ݣ���1Byte��ʾ1bit
uint8_t Nixie_HC595_Data[4][10]={0};

void Nixie_Delay(void)
{
  u32 i=0,j=0;
  for(;j<3;j++)
    for(;i<0xfffff;i++);
}

//��Ҫ�������������괫����Ӧ��λ��
//���������ֵ��������꣬���Ƿ�Ӧ�õ���
void Nixie_HC595_Num2Bit(u8 row,u8 line,u8 value)
{
  u8 product=0;
  product=(row+1)*10+line;
  switch((row+1)*10)//�ȴ��·�Ϊ4�࣬�ɼ����жϴ���
  {
    case 10:
    {
      switch(product)
      {
        case 10:if(value) HC595_Data[4]|= (1ul<<7); else HC595_Data[4]&=~(1ul<<7);break;
        case 11:if(value) HC595_Data[4]|= (1ul<<6); else HC595_Data[4]&=~(1ul<<6);break;
        case 12:if(value) HC595_Data[4]|= (1ul<<5); else HC595_Data[4]&=~(1ul<<5);break;
        case 13:if(value) HC595_Data[4]|= (1ul<<4); else HC595_Data[4]&=~(1ul<<4);break;
        case 14:if(value) HC595_Data[4]|= (1ul<<3); else HC595_Data[4]&=~(1ul<<3);break;
        case 15:if(value) HC595_Data[4]|= (1ul<<2); else HC595_Data[4]&=~(1ul<<2);break;
        case 16:if(value) HC595_Data[4]|= (1ul<<1); else HC595_Data[4]&=~(1ul<<1);break;
        case 17:if(value) HC595_Data[4]|= (1ul<<0); else HC595_Data[4]&=~(1ul<<0);break;
        case 18:if(value) HC595_Data[3]|= (1ul<<7); else HC595_Data[3]&=~(1ul<<7);break;
        case 19:if(value) HC595_Data[3]|= (1ul<<6); else HC595_Data[3]&=~(1ul<<6);break;
      }
    }
    break;
    case 20:
    {
      switch(product)
      {
        case 20:if(value) HC595_Data[3]|= (1ul<<5); else HC595_Data[3]&=~(1ul<<5);break;
        case 21:if(value) HC595_Data[3]|= (1ul<<4); else HC595_Data[3]&=~(1ul<<4);break;
        case 22:if(value) HC595_Data[3]|= (1ul<<3); else HC595_Data[3]&=~(1ul<<3);break;
        case 23:if(value) HC595_Data[3]|= (1ul<<2); else HC595_Data[3]&=~(1ul<<2);break;
        case 24:if(value) HC595_Data[3]|= (1ul<<1); else HC595_Data[3]&=~(1ul<<1);break;
        case 25:if(value) HC595_Data[3]|= (1ul<<0); else HC595_Data[3]&=~(1ul<<0);break;
        case 26:if(value) HC595_Data[2]|= (1ul<<7); else HC595_Data[2]&=~(1ul<<7);break;
        case 27:if(value) HC595_Data[2]|= (1ul<<6); else HC595_Data[2]&=~(1ul<<6);break;
        case 28:if(value) HC595_Data[2]|= (1ul<<5); else HC595_Data[2]&=~(1ul<<5);break;
        case 29:if(value) HC595_Data[2]|= (1ul<<4); else HC595_Data[2]&=~(1ul<<4);break;
      }
    }
    break;
    case 30:
    {
      switch(product)
      {
        case 30:if(value) HC595_Data[2]|= (1ul<<3); else HC595_Data[2]&=~(1ul<<3);break;
        case 31:if(value) HC595_Data[2]|= (1ul<<2); else HC595_Data[2]&=~(1ul<<2);break;
        case 32:if(value) HC595_Data[2]|= (1ul<<1); else HC595_Data[2]&=~(1ul<<1);break;
        case 33:if(value) HC595_Data[2]|= (1ul<<0); else HC595_Data[2]&=~(1ul<<0);break;
        case 34:if(value) HC595_Data[1]|= (1ul<<7); else HC595_Data[1]&=~(1ul<<7);break;
        case 35:if(value) HC595_Data[1]|= (1ul<<6); else HC595_Data[1]&=~(1ul<<6);break;
        case 36:if(value) HC595_Data[1]|= (1ul<<5); else HC595_Data[1]&=~(1ul<<5);break;
        case 37:if(value) HC595_Data[1]|= (1ul<<4); else HC595_Data[1]&=~(1ul<<4);break;
        case 38:if(value) HC595_Data[1]|= (1ul<<3); else HC595_Data[1]&=~(1ul<<3);break;
        case 39:if(value) HC595_Data[1]|= (1ul<<2); else HC595_Data[1]&=~(1ul<<2);break;
      }
    }
    break;
    case 40:
    {
      switch(product)
      {
        case 40:if(value) HC595_Data[1]|= (1ul<<1); else HC595_Data[1]&=~(1ul<<1);break;
        case 41:if(value) HC595_Data[1]|= (1ul<<0); else HC595_Data[1]&=~(1ul<<0);break;
        case 42:if(value) HC595_Data[0]|= (1ul<<7); else HC595_Data[0]&=~(1ul<<7);break;
        case 43:if(value) HC595_Data[0]|= (1ul<<6); else HC595_Data[0]&=~(1ul<<6);break;
        case 44:if(value) HC595_Data[0]|= (1ul<<5); else HC595_Data[0]&=~(1ul<<5);break;
        case 45:if(value) HC595_Data[0]|= (1ul<<4); else HC595_Data[0]&=~(1ul<<4);break;
        case 46:if(value) HC595_Data[0]|= (1ul<<3); else HC595_Data[0]&=~(1ul<<3);break;
        case 47:if(value) HC595_Data[0]|= (1ul<<2); else HC595_Data[0]&=~(1ul<<2);break;
        case 48:if(value) HC595_Data[0]|= (1ul<<1); else HC595_Data[0]&=~(1ul<<1);break;
        case 49:if(value) HC595_Data[0]|= (1ul<<0); else HC595_Data[0]&=~(1ul<<0);break;
      }
    }
    break;
    default:break;
  }
}

//����ʾ����װ�ص�595�����뻺��������
void Nixie_Load(u8 array[][10])
{
  u8 row,line;
  for(row=0;row<4;row++)
    for(line=0;line<10;line++)
  {
    Nixie_HC595_Num2Bit(row,line,array[row][line]);
  }
}

//��595�����뻺����������������595��
void Nixie_Update(void)
{
  hc595_WriteBytes(HC595_Data,sizeof(HC595_Data));
}

//�Լ����
void Nixie_Test(void)
{
  u8 state=0;
  u8 row;
	Nixie_Light_Ctl(100);
  for(;state<10;state++)
  {
    //ѭ������
    memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));
    for(row=0;row<4;row++)
    {
      Nixie_HC595_Data[row][state]=1;
    }
    
    Nixie_Load(Nixie_HC595_Data);
    Nixie_Update();
    
    Nixie_Delay();
  }
}


//��ʱ������ת����HC595�����С�
extern __IO u8 LightLevel;
extern __IO u8 ForceLightOn;
void Nixie_TimeToHC595(void)
{
  memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));
  Nixie_HC595_Data[0][GetTime.hour>>4]=1;
  Nixie_HC595_Data[1][GetTime.hour&0x0F]=1;
  Nixie_HC595_Data[2][GetTime.min>>4]=1;
  Nixie_HC595_Data[3][GetTime.min&0x0F]=1;
  
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();
  
  if(LightLevel||ForceLightOn)
    Dot_Toggle();
  else
  {
    Dot1_OFF;Dot2_OFF;
  }
}

//����������ת����HC595�����С�
void Nixie_DateToHC595(void)
{
  memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));
  Nixie_HC595_Data[0][GetTime.month>>4]=1;
  Nixie_HC595_Data[1][GetTime.month&0x0F]=1;
  Nixie_HC595_Data[2][GetTime.date>>4]=1;
  Nixie_HC595_Data[3][GetTime.date&0x0F]=1;
  
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();
}

//����������ת����HC595�����С�
void Nixie_WeekToHC595(void)
{
  memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));

  Nixie_HC595_Data[2][GetTime.week>>4]=1;
  Nixie_HC595_Data[3][GetTime.week&0x0F]=1;
  
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();
}

//���¶�����ת����HC595�����С�
void Nixie_TempToHC595(void)
{
  memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));
  Nixie_HC595_Data[2][(u8)DS18B20_Temp/10]=1;
  Nixie_HC595_Data[3][(u8)DS18B20_Temp%10]=1;
  
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();
}


extern u8 SetChannel;
extern u8 NewNum;
u8 ChannelFlash=0;
extern u8  __IO Period_1S;
void Set_TimeToHC595(void)
{
	static u8 toggle=0;
  //��������
  if(NewNum!=0xff)
  {
    switch(SetChannel)
    {
      case CHANNEL0:if(NewNum>2)NewNum=0; SetTime.hour=(SetTime.hour&0x0f)|(NewNum<<4);NewNum=0xff; break;
      case CHANNEL1:if(SetTime.hour>=0x20&&NewNum>4)NewNum=4;SetTime.hour=(SetTime.hour&0xf0)|NewNum;NewNum=0xff;break;
      case CHANNEL2:if(NewNum>6)NewNum=0;SetTime.min=(SetTime.min&0x0f)|(NewNum<<4);NewNum=0xff;break;
      case CHANNEL3:SetTime.min=(SetTime.min&0xf0)|NewNum;NewNum=0xff;break;
      default :break;
    }
    SetChannel++;if(SetChannel>=4)SetChannel=0;
  }
  
  memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));
  Nixie_HC595_Data[0][SetTime.hour>>4]=1;
  Nixie_HC595_Data[1][SetTime.hour&0x0F]=1;
  Nixie_HC595_Data[2][SetTime.min>>4]=1;
  Nixie_HC595_Data[3][SetTime.min&0x0F]=1;

  //��ѡ�е�ͨ����˸
  if(ChannelFlash)
  {
    switch(SetChannel)
    {
      case CHANNEL0:Nixie_HC595_Data[0][SetTime.hour>>4]=0;break;
      case CHANNEL1:Nixie_HC595_Data[1][SetTime.hour&0x0F]=0;break;
      case CHANNEL2:Nixie_HC595_Data[2][SetTime.min>>4]=0;break;
      case CHANNEL3:Nixie_HC595_Data[3][SetTime.min&0x0F]=0;break;
      default :break;
    }
  }
    
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();
  
	if(toggle)
	{
		toggle=~toggle;
		Dot1_ON;Dot2_ON;
	}
	else
	{
		toggle=~toggle;
		Dot1_OFF;Dot2_OFF;
	}
}

void Set_DateToHC595(void)
{
  if(NewNum!=0xff)
  {
    switch(SetChannel)
    {
      case CHANNEL0:if(NewNum>2)NewNum=0;SetTime.month=(SetTime.month&0x0f)|(NewNum<<4);NewNum=0xff;break;
      case CHANNEL1:SetTime.month=(SetTime.month&0xf0)|NewNum;NewNum=0xff;break;
      case CHANNEL2:if(NewNum>3)NewNum=0;SetTime.date=(SetTime.date&0x0f)|(NewNum<<4);NewNum=0xff;break;
      case CHANNEL3:if(SetTime.date>=0x30&&NewNum>1)NewNum=0;SetTime.date=(SetTime.date&0xf0)|NewNum;NewNum=0xff;break;
      default :break;
    }
    SetChannel++;if(SetChannel>=4)SetChannel=0;
  }
  
  memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));
  Nixie_HC595_Data[0][SetTime.month>>4]=1;
  Nixie_HC595_Data[1][SetTime.month&0x0F]=1;
  Nixie_HC595_Data[2][SetTime.date>>4]=1;
  Nixie_HC595_Data[3][SetTime.date&0x0F]=1;

  //��ѡ�е�ͨ����˸
  if(ChannelFlash)
  {
    switch(SetChannel)
    {
      case CHANNEL0:Nixie_HC595_Data[0][SetTime.month>>4]=0;break;
      case CHANNEL1:Nixie_HC595_Data[1][SetTime.month&0x0F]=0;break;
      case CHANNEL2:Nixie_HC595_Data[2][SetTime.date>>4]=0;break;
      case CHANNEL3:Nixie_HC595_Data[3][SetTime.date&0x0F]=0;break;
      default :break;
    }
  }
    
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();
  
  Dot1_ON;Dot2_ON;
}

void Set_WeekToHC595(void)
{
  if(SetChannel<3)SetChannel=3;
  
  if(NewNum!=0xff)
  {
    switch(SetChannel)
    {
      case CHANNEL3:if(NewNum>7)NewNum=1;if(NewNum<1)NewNum=1;SetTime.week=(SetTime.week&0xf0)|NewNum;NewNum=0xff;break;
      default :break;
    }
    SetChannel++;if(SetChannel>=4)SetChannel=0;
  }
  
  memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));
  Nixie_HC595_Data[3][SetTime.week&0x0F]=1;
  
  //��ѡ�е�ͨ����˸
  if(ChannelFlash)
  {
    switch(SetChannel)
    {
      case CHANNEL3:Nixie_HC595_Data[3][SetTime.week&0x0F]=0;break;
      default :break;
    }
  }
    
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();
  
  Dot1_OFF;Dot2_OFF;
}

void Set_YearToHC595(void)
{
  if(SetChannel<2)SetChannel=2;
  
  if(NewNum!=0xff)
  {
    switch(SetChannel)
    {
      case CHANNEL2:SetTime.year=(SetTime.year&0x0f)|(NewNum<<4);NewNum=0xff;break;
      case CHANNEL3:SetTime.year=(SetTime.year&0xf0)|NewNum;NewNum=0xff;break;
      default :break;
    }
    SetChannel++;if(SetChannel>=4)SetChannel=0;
  }
  
  memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));
  Nixie_HC595_Data[0][2]=1;
  Nixie_HC595_Data[1][0]=1;
  Nixie_HC595_Data[2][SetTime.year>>4]=1;
  Nixie_HC595_Data[3][SetTime.year&0x0F]=1;

  //��ѡ�е�ͨ����˸
  if(ChannelFlash)
  {
    switch(SetChannel)
    {
      case CHANNEL2:Nixie_HC595_Data[2][SetTime.year>>4]=0;break;
      case CHANNEL3:Nixie_HC595_Data[3][SetTime.year&0x0F]=0;break;
      default :break;
    }
  }
    
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();
  
  Dot1_OFF;Dot2_OFF;
}

void Set_AlarmToHC595(void)
{
  //��������
  if(NewNum!=0xff)
  {
    switch(SetChannel)
    {
      case CHANNEL0:Alarm.hour=(Alarm.hour&0x0f)|(NewNum<<4);	NewNum=0xff; break;
      case CHANNEL1:Alarm.hour=(Alarm.hour&0xf0)|NewNum;			NewNum=0xff;break;
      case CHANNEL2:Alarm.min=(Alarm.min&0x0f)|(NewNum<<4);		NewNum=0xff;break;
      case CHANNEL3:Alarm.min=(Alarm.min&0xf0)|NewNum;				NewNum=0xff;break;
      default :break;
    }
    SetChannel++;if(SetChannel>=4)SetChannel=0;
  }
  
  memset(Nixie_HC595_Data,0,sizeof(Nixie_HC595_Data));
  Nixie_HC595_Data[0][Alarm.hour>>4]=1;
  Nixie_HC595_Data[1][Alarm.hour&0x0F]=1;
  Nixie_HC595_Data[2][Alarm.min>>4]=1;
  Nixie_HC595_Data[3][Alarm.min&0x0F]=1;

  //��ѡ�е�ͨ����˸
  if(ChannelFlash)
  {
    switch(SetChannel)
    {
      case CHANNEL0:Nixie_HC595_Data[0][Alarm.hour>>4]=0;break;
      case CHANNEL1:Nixie_HC595_Data[1][Alarm.hour&0x0F]=0;break;
      case CHANNEL2:Nixie_HC595_Data[2][Alarm.min>>4]=0;break;
      case CHANNEL3:Nixie_HC595_Data[3][Alarm.min&0x0F]=0;break;
      default :break;
    }
    Dot1_ON;Dot2_OFF; 
  }
  else
  {
    Dot1_OFF;Dot2_ON; 
  }
    
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();

}

extern u8 SetType;
void Nixie_Set_Show(void)
{
  switch(SetType)
  {
    case SETTIME:Set_TimeToHC595();break;
    case SETDATE:Set_DateToHC595();break;
    case SETWEEK:Set_WeekToHC595();break;
    case SETYEAR:Set_YearToHC595();break;
    case SETALARM:Set_AlarmToHC595();break;
    default:break;
  }
  ChannelFlash=~ChannelFlash;
}

//������������ѭ����������δ������һС��
void Nixie_Cathode_Prevention(void)
{
  static u8 state=0;
  u32 i=0;
  uint8_t Nixie_Prevention_Data[4][10]={0};

  Nixie_Prevention_Data[0][state]=1;
  Nixie_Prevention_Data[1][state]=1;
  Nixie_Prevention_Data[2][state]=1;
  Nixie_Prevention_Data[3][state]=1;
  
  if((state++)==10)state=0;

  Nixie_Load(Nixie_Prevention_Data);
  Nixie_Update();
  
  for(i=0;i<0x5;i++);
  
  Nixie_Load(Nixie_HC595_Data);
  Nixie_Update();
}

void Nixie_Show(__IO u8 *state)
{
  static u8 cnt=0;
  switch(*state)
  {
    case DEFAULT:Nixie_TimeToHC595();break;
    case SHOWTEMP:Nixie_TempToHC595();cnt++;if(cnt>=4){cnt=0;*state=DEFAULT;}break;
    case SHOWDATE:Nixie_DateToHC595();cnt++;if(cnt>=4){cnt=0;*state=DEFAULT;}break;
    case SHOWWEEK:Nixie_WeekToHC595();cnt++;if(cnt>=4){cnt=0;*state=DEFAULT;}break;
    default:break;
  }
}

extern __IO u8 LightLevel;
extern u8 Setting;
extern u8 SetChannel;
extern u8 SetType;
extern u8 NewNum;
extern u8 __IO ForceLightOn;
extern u8 RGBType;
extern float Ruse,Guse,Buse;
//u8 LightSwitch=1;
float LightCoe=0;//����ϵ��
void Nixie_DealRemote(__IO u8 *state)
{
  if(Setting==0)
  {
    switch(*state)
    {
      case DEFAULT:break;
      case SHOWSWITCH:*state=DEFAULT;if(LightLevel==0)LightLevel=100;else {LightLevel=0;ForceLightOn=0;} 
											Nixie_Light_Ctl(LightLevel);printf("LightLevel:%d\r\n",LightLevel);
											EE_SaveConfig();
										break;
      case LIGHT_UP:*state=DEFAULT;
                    LightLevel=LightLevel+50;if(LightLevel>200)LightLevel=50;printf("LightLevel:%d\r\n",LightLevel);Nixie_Light_Ctl(LightLevel);
                    LightCoe=LightLevel/200.0;//ȡ200��Ϊ���������
										EE_SaveConfig();
										break;
      case LIGHT_DN:*state=DEFAULT;
                    LightLevel=LightLevel-50;if(LightLevel<50)LightLevel=200;printf("LightLevel:%d\r\n",LightLevel);Nixie_Light_Ctl(LightLevel);
                    LightCoe=LightLevel/200.0;
										EE_SaveConfig();
										break;
      case RGBSTATE:*state=DEFAULT;RGB_Msg.state++; if(RGB_Msg.state>=3)RGB_Msg.state=0;
										if(RGB_Msg.state==EFFECTS_OFF)
											{RGB_Msg.R=(u8)Ruse;RGB_Msg.G=(u8)Guse;RGB_Msg.B=(u8)Buse;}
										if(RGB_Msg.state==EFFECTS_ON)//������ɫ��Ϣ
											*state=RGBType;
										EE_SaveConfig();
										break;
      case REDCOLOR:*state=DEFAULT;RGB_Rcd.R=RGB_Msg.R=255,RGB_Rcd.G=RGB_Msg.G=  0,RGB_Rcd.B=RGB_Msg.B=  0;RGB_Msg.mode=SINGLECOLOUR;
										if(RGB_Msg.state==EFFECTS_OFF)RGB_Msg.state=EFFECTS_ON;
										RGBType=REDCOLOR;
										EE_SaveConfig();
										break;
      case ORGCOLOR:*state=DEFAULT;RGB_Rcd.R=RGB_Msg.R=255,RGB_Rcd.G=RGB_Msg.G=156,RGB_Rcd.B=RGB_Msg.B=  0;RGB_Msg.mode=SINGLECOLOUR;
										if(RGB_Msg.state==EFFECTS_OFF)RGB_Msg.state=EFFECTS_ON;
										RGBType=ORGCOLOR;
										EE_SaveConfig();
										break;
      case YELCOLOR:*state=DEFAULT;RGB_Rcd.R=RGB_Msg.R=255,RGB_Rcd.G=RGB_Msg.G=255,RGB_Rcd.B=RGB_Msg.B=  0;RGB_Msg.mode=SINGLECOLOUR;
										if(RGB_Msg.state==EFFECTS_OFF)RGB_Msg.state=EFFECTS_ON;
										RGBType=YELCOLOR;
										EE_SaveConfig();
										break;
      case GRNCOLOR:*state=DEFAULT;RGB_Rcd.R=RGB_Msg.R=  0,RGB_Rcd.G=RGB_Msg.G=255,RGB_Rcd.B=RGB_Msg.B=  0;RGB_Msg.mode=SINGLECOLOUR;
										if(RGB_Msg.state==EFFECTS_OFF)RGB_Msg.state=EFFECTS_ON;
										RGBType=GRNCOLOR;
										EE_SaveConfig();
										break;
      case CYACOLOR:*state=DEFAULT;RGB_Rcd.R=RGB_Msg.R=  0,RGB_Rcd.G=RGB_Msg.G=255,RGB_Rcd.B=RGB_Msg.B=255;RGB_Msg.mode=SINGLECOLOUR;
										if(RGB_Msg.state==EFFECTS_OFF)RGB_Msg.state=EFFECTS_ON;
										RGBType=CYACOLOR;
										EE_SaveConfig();
										break;
      case BLUCOLOR:*state=DEFAULT;RGB_Rcd.R=RGB_Msg.R=  0,RGB_Rcd.G=RGB_Msg.G=  0,RGB_Rcd.B=RGB_Msg.B=255;RGB_Msg.mode=SINGLECOLOUR;
										if(RGB_Msg.state==EFFECTS_OFF)RGB_Msg.state=EFFECTS_ON;
										RGBType=BLUCOLOR;
										EE_SaveConfig();
										break;
      case PURCOLOR:*state=DEFAULT;RGB_Rcd.R=RGB_Msg.R=255,RGB_Rcd.G=RGB_Msg.G=  0,RGB_Rcd.B=RGB_Msg.B=255;RGB_Msg.mode=SINGLECOLOUR;
										if(RGB_Msg.state==EFFECTS_OFF)RGB_Msg.state=EFFECTS_ON;
										RGBType=PURCOLOR;
										EE_SaveConfig();
										break;
      case WHTCOLOR:*state=DEFAULT;RGB_Rcd.R=RGB_Msg.R=255,RGB_Rcd.G=RGB_Msg.G=255,RGB_Rcd.B=RGB_Msg.B=255;RGB_Msg.mode=SINGLECOLOUR;
										if(RGB_Msg.state==EFFECTS_OFF)RGB_Msg.state=EFFECTS_ON;
										RGBType=WHTCOLOR;
										EE_SaveConfig();
										break;
      case COLORFUL:*state=DEFAULT;RGB_Rcd.R=RGB_Msg.R=255,RGB_Rcd.G=RGB_Msg.G=127,RGB_Rcd.B=RGB_Msg.B= 63;RGB_Msg.mode=MULTICOLOUR;
										if(RGB_Msg.state==EFFECTS_OFF)RGB_Msg.state=EFFECTS_ON;
										RGBType=COLORFUL;
										EE_SaveConfig();
										break;
      case SETTING: *state=DEFAULT;Setting=1;
									  break;
      default:if(*state!=SHOWTEMP&&*state!=SHOWDATE&&*state!=SHOWWEEK)*state=DEFAULT;break;
    }
  }
  else
  {
    switch(*state)
    {
      case DEFAULT:break;//����ģʽ�£���ʾ�����ó�����
      case SHOWSWITCH:*state=DEFAULT;if(LightLevel==0)LightLevel=100;Nixie_Light_Ctl(LightLevel);break;			
      case SET_TYPE:*state=DEFAULT;SetType++;if(SetType>=5)SetType=0;printf("type:%d\r\n",SetType);break;
      case CHANNEL_DN:*state=DEFAULT;SetChannel--;if(SetChannel==0xff)SetChannel=3;break;
      case CHANNEL_UP:*state=DEFAULT;SetChannel++;if(SetChannel==4)SetChannel=0;break;
      case NUM0:*state=DEFAULT;NewNum=0;break;
      case NUM1:*state=DEFAULT;NewNum=1;break;
      case NUM2:*state=DEFAULT;NewNum=2;break;
      case NUM3:*state=DEFAULT;NewNum=3;break;
      case NUM4:*state=DEFAULT;NewNum=4;break;
      case NUM5:*state=DEFAULT;NewNum=5;break;
      case NUM6:*state=DEFAULT;NewNum=6;break;
      case NUM7:*state=DEFAULT;NewNum=7;break;
      case NUM8:*state=DEFAULT;NewNum=8;break;
      case NUM9:*state=DEFAULT;NewNum=9;break;
      case VALUE_UP:*state=DEFAULT;break;
      case VALUE_DN:*state=DEFAULT;break;
      case SETTING :*state=DEFAULT;
      printf("SET:\r\n Dt:20%02x-%02x-%2x Tm:%02x:%02x:%02x  Wk:%2x\r\n"\
						,SetTime.year,SetTime.month,SetTime.date,SetTime.hour,SetTime.min,SetTime.sec,SetTime.week);
      Setting=0;
      break;
      default:*state=DEFAULT;break;
    }  
  }
}

extern u16 LightTime15min;
extern u16 RunTime15min;
extern __IO u8 AlarmSwitch;
extern u8 FirstRunFlag;
void EE_SaveConfig(void)
{
	
	EE_WriteVariable(VirtAddVarTab[LightTimeAddr],LightTime15min);
	EE_WriteVariable(VirtAddVarTab[LightLevelAddr],LightLevel);
	EE_WriteVariable(VirtAddVarTab[RGBStateAddr],RGB_Msg.state);
	EE_WriteVariable(VirtAddVarTab[AlarmAddr],((u16)Alarm.hour<<8)|Alarm.min);
	EE_WriteVariable(VirtAddVarTab[RunTimeAddr],RunTime15min);
	EE_WriteVariable(VirtAddVarTab[RMsgAddr],RGB_Msg.R);
	EE_WriteVariable(VirtAddVarTab[GMsgAddr],RGB_Msg.G);
	EE_WriteVariable(VirtAddVarTab[BMsgAddr],RGB_Msg.B);
	EE_WriteVariable(VirtAddVarTab[RGBModeAddr],RGB_Msg.mode);
	EE_WriteVariable(VirtAddVarTab[AlarmSwitchAddr],AlarmSwitch);
	EE_WriteVariable(VirtAddVarTab[RGBTypeAddr],RGBType);
	EE_WriteVariable(VirtAddVarTab[FirstRunFlagAddr],FirstRunFlag);
	EE_WriteVariable(VirtAddVarTab[LightCoeAddr],(u16)(LightCoe*100));
}

void HC595_PWM_Init(void)
{
  {
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOB clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

    /* ���ú������õ���PB0���� */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  }
  
  {
  	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;																				
    
    /* ����TIM3CLK ʱ��Ϊ72MHZ */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 					//ʹ��TIM3ʱ��

    /* ������ʱ������ */		 
    TIM_TimeBaseStructure.TIM_Period = 255;       							  //����ʱ����0������255����Ϊ266�Σ�Ϊһ����ʱ����
    TIM_TimeBaseStructure.TIM_Prescaler = 1999;	    							//����Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;			//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* PWMģʽ���� */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    				//����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
    TIM_OCInitStructure.TIM_Pulse = 100;										  			//���ó�ʼPWM������Ϊ0	
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  	  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ

    TIM_OC4Init(TIM2, &TIM_OCInitStructure);	 									//ʹ��ͨ��3
    

    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);						//ʹ��Ԥװ��	

    TIM_ARRPreloadConfig(TIM2, ENABLE);			 										//ʹ��TIM3���ؼĴ���ARR

    /* TIM3 enable counter */
    TIM_Cmd(TIM2, ENABLE);                   										//ʹ�ܶ�ʱ��3	
  }
}

//�ָ���������
void Recovery(void)
{
  RGB_Msg.state=0;
  LightLevel=100;
}

static void Nixie_Light_delay(void)
{
	uint32_t i=0;
	for(i=0;i<10000;i++);
}
//PWM���ȿ���
//0-255���ȵȼ�
void Nixie_Light_Ctl(u8 value)
{
	u8 i=0;
	u8 lastValue=TIM2->CCR4;
	if(value>=lastValue) //��������
	{
		for(i=lastValue;i<value;i++)
		{
			TIM2->CCR4=i;
			Nixie_Light_delay();
		}
	}
	else {
		for(i=lastValue;i>value;i--)
		{
			TIM2->CCR4=i;
			Nixie_Light_delay();
		}
		TIM2->CCR4=i;//ȷ��i=0;
	}
}

void MyTest(void)
{

}

