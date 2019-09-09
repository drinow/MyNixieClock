/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   systick系统定时器
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 ISO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "include.h"


void NVIC_Config(void)
{	
	NVIC_InitTypeDef NVIC_InitStructure; 	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  //DS3231 INT
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  //HX1838 INT
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
  
}

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
void SettingFunc(void);
void CheckAlarm(void);
void OnTimeLightCheck(void);
void DealRemoteSignal(void);
void OnTimeAlarm(void);
void Recovery(void);
void EE_ReadConfig(void);
void Breathing(void);

extern u32 __IO tick;
extern u8 SecAlarm;
extern u8 __IO Breath_Frq;
extern u8 __IO Period_1S;
extern u8 __IO Pulse;
extern float LightCoe;
extern float Ruse,Guse,Buse;
extern u8 BeepDelayTime100ms;

__IO u8 RemoteKey=DEFAULT;
u8 ShowState=DEFAULT;
__IO u32 LightOnSecCnt=0;
__IO u32 RuntimeSecCnt=0;
u16 LightTime15min=0;
u16 RunTime15min=0;
__IO u16 LightLevel=180;
u8 Setting=0;
u8 SetChannel=0;//设置模式下的通道选择
u8 SetType=0;//设置类型选择
u8 NewNum=0xff;//期望被设置的数
u8 FirstRunFlag=0;
u16 EE_tmp=0;
__IO u8 AlarmState=0;//又是闹铃启动标志位又是闹铃计时变量，单位为秒
__IO u8 AlarmSwitch=0;//闹铃开关
__IO u8 ForceLightOn=0;
int main(void)
{	
    LED_GPIO_Config();
    USART1_Config();
    SysTick_Init();
    NVIC_Config();
    FLASH_Unlock();
    EE_Init();

    hc595_init();
    DS18B20_Init();
    DS3231_Config();
    SHT2x_Init();
    BeepInit();
    WS2812_Init();
    Remote_Init();
    HC595_PWM_Init();

    EE_ReadConfig();

    Nixie_Test();
	
//  SetTime.year =0x17;
//  SetTime.month =0x07;
//  SetTime.date =0x28;
//  SetTime.hour =0x16;
//  SetTime.min =0x51;
//  SetTime.sec =0x0;
//  SetTime.week =0x05;
//  DS3231_WriteTime(&SetTime);
//  DS3231_WriteTime(&SetTime);
//  while(1)
//	{
//		u32 i=0,j=0;
//		for(;j<3;j++)
//			for(;i<0xffff;i++);
//		printf("temp:%.2f ",SHT2x_GetTempPoll());//不能读太快。
//		printf("humi:%.2f\r\n",SHT2x_GetHumiPoll());
//	}

	Nixie_Light_Ctl(LightLevel);
	ForceLightOn=1;
	for(;;)
	{		
        Beep_Alarm();//蜂鸣器控制
        SettingFunc();//设置功能
        Nixie_DealRemote(&ShowState);//遥控信号解析
        if(SecAlarm)
        {
            SecAlarm=0;
            RuntimeSecCnt++;
            if(LightLevel!=0||TIM2->CCR4!=0)LightOnSecCnt++;//点亮的时间记录
            if(RuntimeSecCnt>=900){RuntimeSecCnt=0;RunTime15min++; EE_SaveConfig();}//运行时长记录
            if(LightOnSecCnt>=900){LightOnSecCnt=0;LightTime15min++;}
            if(GetTime.sec==0) Nixie_Cathode_Prevention();//阴极保护
            SHT20.HUMI_POLL	=SHT2x_GetHumiPoll();//未添加温湿度传感器则一定要屏蔽
            SHT20.TEMP_POLL	=SHT2x_GetTempPoll();//未添加温湿度传感器则一定要屏蔽
            DS18B20_Temp=DS18B20_Get_Temp();//温度传感器
            Nixie_Show(&ShowState);//显示函数
            OnTimeLightCheck();//遥控唤醒或强制点亮10秒
            OnTimeAlarm();//整点报时
            CheckAlarm();//闹钟检查
            LED1_TOGGLE;//运行状态指示
						//DEBUG
            printf("D:%02x-%02x T:%02x:%02x:%02x Wk:%x ",GetTime.month,GetTime.date,GetTime.hour ,GetTime.min ,GetTime.sec,GetTime.week );
            printf("Tmp:%3.1f℃ Humi:%3.1f%% | ",(DS18B20_Temp+SHT20.TEMP_POLL)/2 ,SHT20.HUMI_POLL);
            printf("LLvl:%d ",LightLevel);
            printf("FosLt:%d ",ForceLightOn);
            printf("Alm:%d ",AlarmState);
            printf("RmRdy:%d ",Remote_Rdy);
            printf("Rmkey:%d ",RemoteKey);
            printf("RmCnt:%d ",Remote_Cnt);
            printf("RGBste:%d | ",RGB_Msg.state);
            printf("LT:%dD-%02d:%02d:%02d ",(u8)((LightTime15min*15.0+LightOnSecCnt/60)/60/24),(LightTime15min*15+LightOnSecCnt/60)/60%24,(LightTime15min*15+LightOnSecCnt/60)%60,LightOnSecCnt%60);
            printf("RT:%dD-%02d:%02d:%02d ",(u8)((  RunTime15min*15.0+RuntimeSecCnt/60)/60/24),(  RunTime15min*15+RuntimeSecCnt/60)/60%24,(  RunTime15min*15+RuntimeSecCnt/60)%60,RuntimeSecCnt%60);
            printf("\r\n");
        }
        Breathing();//呼吸灯
        DealRemoteSignal();//处理遥控信号
	}     
}

void Breathing(void)
{
    //呼吸灯效果
    if(Breath_Frq)
    {
//      SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
//			__disable_irq();
      WS2812_Breath();
      Breath_Frq=0;
//			__enable_irq();
//      SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
    }
}


void EE_ReadConfig(void)
{
  //读取设置值
	EE_ReadVariable(VirtAddVarTab[FirstRunFlagAddr],&EE_tmp);FirstRunFlag=EE_tmp;
	if(FirstRunFlag!=0xAA)
	{
		FirstRunFlag=0xAA;
		Recovery();
	}
	
    EE_ReadVariable(VirtAddVarTab[RunTimeAddr],&EE_tmp);RunTime15min=EE_tmp;
    EE_ReadVariable(VirtAddVarTab[LightTimeAddr],&EE_tmp);LightTime15min=EE_tmp;
    EE_ReadVariable(VirtAddVarTab[LightLevelAddr],&EE_tmp);LightLevel=EE_tmp;
    EE_ReadVariable(VirtAddVarTab[RGBStateAddr],&EE_tmp);RGB_Msg.state=(EffectState_e)EE_tmp;
    EE_ReadVariable(VirtAddVarTab[AlarmAddr],&EE_tmp);Alarm.hour =(EE_tmp&0xff00)>>8;Alarm.min =EE_tmp&0x00ff;
    EE_ReadVariable(VirtAddVarTab[RGBStateAddr],&EE_tmp);RGB_Msg.state=(EffectState_e)EE_tmp;
    EE_ReadVariable(VirtAddVarTab[RMsgAddr],&EE_tmp); RGB_Msg.R=EE_tmp;
    EE_ReadVariable(VirtAddVarTab[GMsgAddr],&EE_tmp); RGB_Msg.G=EE_tmp;
    EE_ReadVariable(VirtAddVarTab[BMsgAddr],&EE_tmp); RGB_Msg.B=EE_tmp;
    EE_ReadVariable(VirtAddVarTab[RGBModeAddr],&EE_tmp);RGB_Msg.mode=(ColorMode_e)EE_tmp;
    EE_ReadVariable(VirtAddVarTab[AlarmSwitchAddr],&EE_tmp);AlarmSwitch=EE_tmp;
    EE_ReadVariable(VirtAddVarTab[LightCoeAddr],&EE_tmp);LightCoe=EE_tmp/100.0;	
	
    if(RGB_Msg.mode==SINGLECOLOR)
    {
        RcdMAX_RGB[TUBE0][RED]=RGB_Msg.R;RcdMAX_RGB[TUBE0][GREEN]=RGB_Msg.G;RcdMAX_RGB[TUBE0][BLUE]=RGB_Msg.B;
        RcdMAX_RGB[TUBE1][RED]=RGB_Msg.R;RcdMAX_RGB[TUBE1][GREEN]=RGB_Msg.G;RcdMAX_RGB[TUBE1][BLUE]=RGB_Msg.B;
        RcdMAX_RGB[TUBE2][RED]=RGB_Msg.R;RcdMAX_RGB[TUBE2][GREEN]=RGB_Msg.G;RcdMAX_RGB[TUBE2][BLUE]=RGB_Msg.B;
        RcdMAX_RGB[TUBE3][RED]=RGB_Msg.R;RcdMAX_RGB[TUBE3][GREEN]=RGB_Msg.G;RcdMAX_RGB[TUBE3][BLUE]=RGB_Msg.B;
    }
    
    printf("RunTime  :%.2f Hour \r\n",RunTime15min/4.0);
    printf("LightTime :%.2f Hour \r\n",LightTime15min/4.0);
    printf("LightLevel:%d \r\n",LightLevel);
    printf("LightCoe  :%.2f \r\n",LightCoe);
    printf("RGB:State-%d Mode-%d\r\n",RGB_Msg.state,RGB_Msg.mode);
    printf("R:%d G:%d B:%d  \r\n",RGB_Msg.R,RGB_Msg.G,RGB_Msg.B);
    printf("Alarm:%x:%x Switch:%d\r\n",Alarm.hour,Alarm.min,AlarmSwitch);
}

//恢复初始化设置
void Recovery(void)
{
	printf("Factory Reseting...\r\n\r\n");
	Alarm.hour=Alarm.min=0x88;
	AlarmSwitch=0;
	RGB_Msg.R=RGB_Msg.G=RGB_Msg.B=255;
	RGB_Msg.mode=RAINBOW;
	RGB_Msg.state=EFFECTS_ON;
//	RunTime15min=LightTime15min=0;
	LightLevel=180;
	LightCoe=0.7;
	
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
	EE_WriteVariable(VirtAddVarTab[FirstRunFlagAddr],FirstRunFlag);
	EE_WriteVariable(VirtAddVarTab[LightCoeAddr],(u16)(LightCoe*100));
	Beep_State(800000*2);
	
    printf("RunTime:%.2f Hour \r\n",RunTime15min/4.0);
    printf("LightTime:%.2f Hour \r\n",LightTime15min/4.0);
    printf("LightLevel:%d \r\n",LightLevel);
    printf("RGB:State-%d Mode-%d\r\n",RGB_Msg.state,RGB_Msg.mode);
    printf("R:%d G:%d B:%d  \r\n",RGB_Msg.R,RGB_Msg.G,RGB_Msg.B);
    printf("Alarm:%x:%x Switch:%d\r\n\r\n",Alarm.hour,Alarm.min,AlarmSwitch);
    Nixie_Light_Ctl(LightLevel);
}

//遥控按键处理
void DealRemoteSignal(void)
{
    static u8 finish=0;
    if(Remote_Cnt==0)
        finish=0;
	RemoteKey=Remote_Process();
	if(RemoteKey==SHOWTEMP||RemoteKey==SHOWDATE||RemoteKey==SHOWWEEK||RemoteKey==SHOWSWITCH||\
		 RemoteKey==SETTING ||RemoteKey==RGBSTATE||RemoteKey==REDCOLOR||RemoteKey==ORGCOLOR||\
		 RemoteKey==YELCOLOR||RemoteKey==GRNCOLOR||RemoteKey==CYACOLOR||RemoteKey==BLUCOLOR||\
		 RemoteKey==PURCOLOR||RemoteKey==WHTCOLOR||RemoteKey==COLORFUL||RemoteKey==LIGHT_UP||\
		 RemoteKey==LIGHT_DN||RemoteKey==PREV    ||RemoteKey==NEXT    ||RemoteKey==P100    ||RemoteKey==P200)//有些宏定义相同数值的不再写上
	{
		if(Remote_Cnt<=5&&finish==0)//短按
		{
            finish=1;
            AlarmState=0xff;
            if(GetTime.hour>=0x06&&GetTime.hour<0x22)
                Beep_State(1);
			if(LightLevel==0)//熄灭状态
			{
				if(RemoteKey==LIGHT_UP||RemoteKey==LIGHT_DN||RemoteKey==SETTING)
					ShowState=DEFAULT;
				else
					ShowState=RemoteKey;
				Nixie_Show(&ShowState);
				ForceLightOn=1;Nixie_Light_Ctl(180);
			}
			else //
			{
				if(RemoteKey==SETTING)
					ShowState=DEFAULT;
				else
					ShowState=RemoteKey;
				Nixie_Show(&ShowState);
			}
			
		}
		else if(Remote_Cnt==15)//长按
		{
			if(RemoteKey==SETTING)
			{
				Beep_State(1);
				ShowState=RemoteKey;
			}
			else if(RemoteKey==SHOWSWITCH)
			{
				Recovery();
			}
		}
		else
		{
		}
		printf("RemoteKey:%d ",RemoteKey);//显示键值
		printf("cnt:%d \r\n",Remote_Cnt);//显示按键次数	
	}
    else if(RemoteKey!=0)
    {
        printf("UnexpectRemoteKey:%d ",RemoteKey);//显示键值
		printf("UnexpectCnt:%d \r\n",Remote_Cnt);//显示按键次数	
    }
}

//检查闹铃，并持续响60秒
//灭铃控制在遥控那里
void CheckAlarm(void)
{
	if(AlarmSwitch)
	{
		//检查闹铃
		if(Alarm.hour==GetTime.hour&&Alarm.min==GetTime.min&&GetTime.sec==0)
			AlarmState=1;
		//闹铃计时
		if(AlarmState>0&&AlarmState<32)
		{
			AlarmState++;if(LightLevel==0)Nixie_Light_Ctl(180);
		}
		if(AlarmState==32)
		{
			AlarmState=0xff;Beep(0);if(LightLevel==0)ForceLightOn=1;
		}
	}
	if(AlarmState==0xff&&Alarm.min!=GetTime.min)AlarmState=0;
}

//灭灯时在整点时强制点亮10秒钟
void OnTimeLightCheck(void)
{
	if(LightLevel==0)
	{
		if(ForceLightOn)
			ForceLightOn++;
		
		if(GetTime.hour<0x06)//半夜修改为1小时间隔点亮
		{
			if(GetTime.min == 0&&GetTime.sec == 0)
			{
				ForceLightOn++;
			}
		}
		else
		{
			if(GetTime.sec == 0x00||GetTime.sec == 0x10||GetTime.sec == 0x20||
               GetTime.sec == 0x30||GetTime.sec == 0x40||GetTime.sec == 0x50)
			{
				ForceLightOn++;
			}
		}
		
		if(ForceLightOn>0&&ForceLightOn<6)
			Nixie_Light_Ctl(180);
		
		if(ForceLightOn>=6&&GetTime.sec>0x10&&GetTime.sec<0x50)
		{
			ForceLightOn=0;
			Nixie_Light_Ctl(0);
		}
	}
	else
	{
		ForceLightOn=0;
	}
}

//9-21点整点报时
void OnTimeAlarm(void)
{
	if(GetTime.sec==0&&GetTime.min==0&&GetTime.hour>0x08&&GetTime.hour<0x22&&AlarmState==0)
	{
		Beep_OnTimeAlarm();
	}
}

void SettingFunc(void)
{
	u8 lightflag=0;
  if(Setting)
  {
    SetTime.year=GetTime.year;
    SetTime.month=GetTime.month;
    SetTime.date=GetTime.date;
    SetTime.hour=GetTime.hour;
    SetTime.min=GetTime.min;
    SetTime.sec=0;
    SetTime.week=GetTime.week;
    SetChannel=0;
		SetType=4;//先进入Alarm设置模式下
		if(LightLevel==0)
		{
			Nixie_Light_Ctl(180);//强制点亮
			lightflag=1;
		}
    while(Setting)//注意进来后因为未松按钮导致又退出去
    {
      Nixie_DealRemote(&ShowState); 
      if(SecAlarm)
      {
        SecAlarm=0;
				RuntimeSecCnt++;
        if(LightLevel!=0)LightOnSecCnt++;//运行时间计时
				if(RuntimeSecCnt==900){RuntimeSecCnt=0;RunTime15min++;}
        if(LightOnSecCnt==900){LightOnSecCnt=0;LightTime15min++;}
				if(GetTime.sec==0)
				{
					Nixie_Cathode_Prevention();
				}        
				LED1_TOGGLE;
      }
      if(Pulse)
      {
        Nixie_Set_Show();
        Pulse=0;
      }

			RemoteKey=Remote_Process();
			if(RemoteKey!=0&&Remote_Cnt==1)//利用Remote_Cnt不自动清空，防止长按设置后直接跳进来
			{
				Beep_State(5);
				ShowState=RemoteKey;
//				printf("RemoteKey:%d ",RemoteKey);//显示键值
//				printf("cnt:%d \r\n",Remote_Cnt);//显示按键次数	
			}
			else ShowState=DEFAULT;
			
    }
		if(lightflag==1)
			Nixie_Light_Ctl(0);
    //闹钟设置模式下不修改时间
    if(SetType==SETALARM)
    {
      Dot1_ON;Dot2_ON;
			if(Alarm.hour>0x24||Alarm.min>=60)AlarmSwitch=0;else AlarmSwitch=1;
			EE_SaveConfig();
    }
    else
		{
      DS3231_WriteTime(&SetTime);
		}
  }
}
/*********************************************END OF FILE**********************/
