/**
 * HV57708����
 * оƬ��飺
 *     32MHz, 64ͨ������������벢��оƬ
 *     ���� 4 �� ���е� 16 λ��λ�Ĵ���
 * ���ߣ�    Blanboom
 * �����£�2014-07-17
 * http://blanboom.org
 *****************************************************************************
 * ʹ�ñ�����ʱ����Ҫ�ڴ˴��� PinDef.h �ж��� HV57708 �ĸ������ţ����������
 *     HV57708_CLK - CLK
 *     HV57708_LE  - LE
 *     HV57708_POL - POL
 *     HV57708_DI1 - Din1/Dout4(A)
 *     HV57708_DI2 - Din2/Dout3(A)
 *     HV57708_DI3 - Din3/Dout2(A)
 *     HV57708_DI4 - Din4/Dout1(A)
 *****************************************************************************
 *     HG57708 �� BL �Ӹߵ�ƽ��DIR �ӵ͵�ƽʱ��ʱ���ƴ棬�Ӹߵ�ƽʱ˳ʱ���ƴ�
 */
 
#include "HV57708.h"

void Delay(u32 time)
{
	u32 i,j;
	for(i=0;i < time;i++)
		for(j=0;j < 250;j++);
}
/**
 * void HV57708_Init(bool HV57708_Mode)
 * ��飺HV57708 ��ʼ��
 * ���ܣ�HV57708 ��ʼ�������������ģʽ
 * ���룺
 *       HV57708_Mode:
 *           HV57708_MODE_NORMAL    - ��׼���ģʽ
 *           HV57708_MODE_INVERTION - �������ģʽ
 * �������
 */
void HV57708_Init(u8 HV57708_Mode)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;														//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;														//�ٶ�50MHZ
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;														//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;														//�ٶ�50MHZ
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;														//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;														//�ٶ�50MHZ
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;														//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;														//�ٶ�50MHZ
	GPIO_Init(GPIOA,&GPIO_InitStructure);
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;														//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;														//�ٶ�50MHZ
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;														//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;														//�ٶ�50MHZ
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;														//��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
/***********************************************************************************************************/

	HV57708_POL_H;

	HV57708_DI1_L;
	HV57708_DI2_L;
	HV57708_DI3_L;
	HV57708_DI4_L;


	HV57708_CLK_L;
	HV57708_LE_L;
	 
	
}

/**
 * void HV57708_SendData(u32 datapart1, u32 datapart2)
 * ��飺�� HV57708 ��������
 * ���ܣ��� HV57708 ���� 64 λ������
 * ���룺
 *       datapart1 - ��һ�������ݣ�32λ
 *       datapart2 - �ڶ��������ݣ�32λ
 * �������
 */
void HV57708_SendData(u32 datapart2, u32 datapart1)
{
	u8 i;
	u32 tmp;
	tmp = datapart1;
  for(i=0; i < 8; i++)
	{
		HV57708_CLK_L;
 		if((tmp & 0x00000001) == 1) {
 			HV57708_DI4_H;
        } else {
            HV57708_DI4_L;
        }
 		tmp = tmp >> 1;
 		if((tmp & 0x00000001) == 1) {
 			HV57708_DI3_H;
        } else {
            HV57708_DI3_L;
        }
        tmp = tmp >> 1;
        if((tmp & 0x00000001) == 1) {
 			HV57708_DI2_H;
        } else {
            HV57708_DI2_L;
        }
        tmp = tmp >> 1;
        if((tmp & 0x00000001) == 1) {
 			HV57708_DI1_H;
        } else {
            HV57708_DI1_L;
        }
        tmp = tmp >> 1;
        
//		HV57708_DI1_H;
//		HV57708_DI2_L;
//		HV57708_DI3_H;
//		HV57708_DI4_H;
		
	Delay(20);
		HV57708_CLK_H;
	Delay(20);

		HV57708_CLK_L;
	}
	tmp = datapart2;
  for(i=0; i < 8; i++)
	{
		HV57708_CLK_L;
 		if((tmp & 0x00000001) == 1) {
 			HV57708_DI4_H;
        } else {
            HV57708_DI4_L;
        }
 		tmp = tmp >> 1;
 		if((tmp & 0x00000001) == 1) {
 			HV57708_DI3_H;
        } else {
            HV57708_DI3_L;
        }
        tmp = tmp >> 1;
        if((tmp & 0x00000001) == 1) {
 			HV57708_DI2_H;
        } else {
            HV57708_DI2_L;
        }
        tmp = tmp >> 1;
        if((tmp & 0x00000001) == 1) {
 			HV57708_DI1_H;
        } else {
            HV57708_DI1_L;
        }
        tmp = tmp >> 1;
//		HV57708_DI1_H;
//		HV57708_DI2_H;
//		HV57708_DI3_H;
//		HV57708_DI4_H;

			Delay(20);

		HV57708_CLK_H;
			Delay(20);

		HV57708_CLK_L;
			Delay(20);		
	}
}

/**
 * void HV57708_OutputData(void)
 * ��飺�� HV57708 �Ĵ����е��������������
 * ���ܣ��� HV57708 �Ĵ����е��������������
 * ���룺��
 * �������
 */
void HV57708_OutputData(void)
{
	HV57708_LE_H;
	Delay(50);
	HV57708_LE_L;
	Delay(20);
}
// FBFEFFBF EFFBFEFF 666666
// BFF7FDFF 7FDFF7F0 233333
// FBFEFFBF EFFBFEFF 666666
// BFF7FDFF 7FDFF7F0 233333
// FBFEFFBF EFFBFEFF 666666
// BFF7FDFF 7FDFF7F0 233333
// FBFEFFBF EFFBFEFF 666666
// BFF7FDFF 7FDFF7F0 233333

void SetDisplay(unsigned char data[])
{
	u32 data_high = 0xffffffff;
	u32 data_low  = 0xffffffff;
	u16 hour_high, hour_low, minute_high, minute_low, sec_high, sec_low;
	int i = 0;
	u32 data_high_temp, data_low_temp;
	u16 middle_temp;
	
	 hour_high = 0xFDFF;
	if(data[0] == 0) {
		hour_high = 0xfffe;
	} else {
		for(i = 0; i < data[0] - 1; i++) {
			hour_high >>= 1;
			hour_high |= 0x8000;
		}
	}
	
	 hour_low = 0xFDFF;
	if(data[1] == 0) {
		hour_low = 0xfffe;
	} else {
		for(i = 0; i < data[1] - 1; i++) {
			hour_low >>= 1;
			hour_low |= 0x8000;
		}
	}
	
	 minute_high = 0xFDFF;
	if(data[2] == 0) {
		minute_high = 0xfffe;
	} else {
		for(i = 0; i < data[2] - 1; i++) {
			minute_high >>= 1;
			minute_high |= 0x8000;
		}
	}
	
	 minute_low = 0xFDFF;
	if(data[3] == 0) {
		minute_low = 0xfffe;
	} else {
		for(i = 0; i < data[3] - 1; i++) {
			minute_low >>= 1;
			minute_low |= 0x8000;
		}
	}
	
	 sec_high = 0xFDFF;
	if(data[4] == 0) {
		sec_high = 0xfffe;
	} else {
		for(i = 0; i < data[4] - 1; i++) {
			sec_high >>= 1;
			sec_high |= 0x8000;
		}
	}
	
	 sec_low = 0xFDFF;
	if(data[5] == 0) {
		sec_low = 0xfffe;
	} else {
		for(i = 0; i < data[5] - 1; i++) {
			sec_low >>= 1;
			sec_low |= 0x8000;
		}
	}
	
	data_high_temp = hour_high;
	data_high_temp <<= 22;
	data_high_temp |= 0x003FFFFF;
	data_high &= data_high_temp;
	
	data_high_temp = hour_low;
	data_high_temp <<= 12;
	data_high_temp |= 0xFFC00FFF;
	data_high &= data_high_temp;
	
	data_high_temp = minute_high;
	data_high_temp <<= 2;
	data_high_temp |= 0xFFFFF003;
	data_high &= data_high_temp;
	
	middle_temp = minute_low;
	middle_temp >>= 8;
	middle_temp |= 0xFFFC;
	data_high_temp = middle_temp;
	data_high_temp |= 0xFFFFFFFC;
	data_high &= data_high_temp;
	
	data_low_temp = minute_low;
	data_low_temp <<= 24;
	data_low_temp |= 0x00FFFFFF;
	data_low &= data_low_temp;
	
	data_low_temp = sec_high;
	data_low_temp <<= 14;
	data_low_temp |= 0xFF003FFF;
	data_low &= data_low_temp;
	
	data_low_temp = sec_low;
	data_low_temp <<= 4;
	data_low_temp |= 0xFFFFC00F;
	data_low &= data_low_temp;
	
	HV57708_SendData(data_high, data_low);
	HV57708_OutputData();
	
}
