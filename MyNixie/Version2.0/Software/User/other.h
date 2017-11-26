#ifndef __OTHER_H
#define __OTHER_H

#include "include.h"

//EE设置存储地址
#define LightTimeAddr  0
#define LightLevelAddr 1
#define RGBStateAddr   2
#define AlarmAddr      3
#define RunTimeAddr		 4
#define RMsgAddr		 	 5
#define GMsgAddr		 	 6
#define BMsgAddr		   7
#define RGBModeAddr		 8
#define AlarmSwitchAddr   9
#define RGBTypeAddr      10
#define FirstRunFlagAddr 11
#define LightCoeAddr 		 12

//遥控功能普通模式下按键值定义
#define DEFAULT    255
#define SHOWTEMP   98
#define SHOWDATE   162
#define SHOWWEEK   226
#define SHOWSWITCH 194
#define SETTING    144
#define RGBSTATE   104
#define REDCOLOR   48
#define ORGCOLOR   24
#define YELCOLOR   122 //黄
#define GRNCOLOR   16  
#define CYACOLOR   56  //青
#define BLUCOLOR   90
#define PURCOLOR   66  //紫
#define WHTCOLOR   74  //百
#define COLORFUL   82  //彩
#define LIGHT_UP   168
#define LIGHT_DN   224
#define PREV			 34
#define NEXT			 2
#define P100			 152
#define P200			 176

//遥控功能设置模式下按键值定义
#define SET_TYPE  98
#define CHANNEL_DN   162
#define CHANNEL_UP   226
#define NUM0   104
#define NUM1   48
#define NUM2   24
#define NUM3   122 
#define NUM4   16  
#define NUM5   56  
#define NUM6   90
#define NUM7   66  
#define NUM8   74  
#define NUM9   82  
#define VALUE_UP  168
#define VALUE_DN  224

//SETChannel设置模式下的通道选择
#define CHANNEL0 0
#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3

//SetType设置类型选择
#define SETTIME 0
#define SETDATE 1
#define SETWEEK 2
#define SETYEAR 3
#define SETALARM 4

void HC595_PWM_Init(void);
void Nixie_TimeToHC595(void);
void Nixie_DateToHC595(void);
void Nixie_TempToHC595(void);
void Nixie_Cathode_Prevention(void);
void Nixie_Light_Ctl(u8 value);
void Nixie_DealRemote(__IO u8 *state);
void Nixie_Show(__IO u8 *state);
void Nixie_Set_Show(void);
void Nixie_Test(void);
void MyTest(void);

#endif

