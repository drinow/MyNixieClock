#include "ds3231.h"

TIME_TypeDef SetTime,GetTime;


/*����EXTI����ȥ���INT��*/
void DS3231_INT_EXTI_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline clock and AFIO clock */
	RCC_APB2PeriphClockCmd(DS3231_INT_RCC | RCC_APB2Periph_AFIO,ENABLE);
												
	/* config the NVIC */
//	NVIC_Configuration();//�����ط�������

	/* EXTI line gpio config*/	
  GPIO_InitStructure.GPIO_Pin = DS3231_INT_PIN;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // ��������
  GPIO_Init(DS3231_INT_PORT, &GPIO_InitStructure);

	/* EXTI line mode config */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void DS3231_GPIO_Init(void)
{
	//��ʼ��IIC���Ų����IIC�豸
	i2c_CheckDevice(DS3231_ADDRESS);
}

//�������жϣ������INT����
void DS3231_SetSecondAlarm(void)
{
	u8 ctrldata=0;
	u8 data=0x80;//Ϊʲô��0x80���ֲ�Table2
	
	//ʹ��Alarm1�ж�
	ctrldata=0x01;
	IIC_WriteBytes(&ctrldata,DS3231_ControlReg,1);
	
	//����Alarm1ģʽ
//	if(IIC_WriteBytes(&data,DS3231_A1SecReg,4)==1) return SUCCESS;
//	else return ERROR;
	IIC_WriteBytes(&data,DS3231_A1SecReg,1);//Ϊɶ��������д��
	IIC_WriteBytes(&data,DS3231_A1MinReg,1);
	IIC_WriteBytes(&data,DS3231_A1HourReg,1);
	IIC_WriteBytes(&data,DS3231_A1WeekReg,1);
}

/*����DS3231*/
void DS3231_Config(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); 
  
  DS3231_GPIO_Init();//config the iic
  DS3231_INT_EXTI_Init();//config the Int pin
  DS3231_SetSecondAlarm();//set second alarm
}

void DS3231_WriteTime(TIME_TypeDef* time)
{
	u8 setTime[7]={0};
  u8 i=0;
	setTime[0]=time->sec;
	setTime[1]=time->min;
	setTime[2]=time->hour;
	setTime[3]=time->week;
	setTime[4]=time->date;
	setTime[5]=time->month;
	setTime[6]=time->year;
//	if(IIC_WriteBytes(&setTime[0],DS3231_SecReg,7)==1) printf("Write OK\r\n");
//	else printf("Write Failed!\r\n");
  while(i<5)
  {
    i++;
    if(IIC_WriteBytes(&setTime[0],DS3231_SecReg,7)==1) 
    {
      printf("Write OK\r\n");
      break;
    }
	  else printf("Write Failed!\r\n");
  }
}

void DS3231_ReadTime(TIME_TypeDef* time)
{
	  u8 getTime[7]={0};
		if(IIC_ReadBytes(&getTime[0],DS3231_SecReg,7)==1) 
		{
//			printf("time:%x-%x-%x %x:%x:%x\r\n",getTime[6],getTime[5],getTime[4],getTime[2],getTime[1],getTime[0]);
			time->sec =getTime[0];
			time->min =getTime[1];
			time->hour =getTime[2];
			time->week =getTime[3];
			time->date =getTime[4];
			time->month =getTime[5];
			time->year =getTime[6];
		}
    #ifdef DEBUG
		else 
      printf("Read failed!\r\n");
    #endif
}

//��ȡָ���Ĵ�������
u8 DS3231_ReadReg(u8 Reg)
{
	u8 data;
	IIC_ReadBytes(&data,Reg,1);
	return data;
}

//��ָ���Ĵ���д������
u8 DS3231_WriteReg(u8 Reg,u8 data)
{
	if(IIC_WriteBytes(&data,Reg,1)==1) return SUCCESS;
	else return ERROR;
}

//��ȡ���мĴ���
void DS3231_ReadAll(void)
{
	  u8 array[19]={0},i=0;
		if(IIC_ReadBytes(&array[0],DS3231_SecReg,19)==1) 
		{
			for(i=0;i<19;i++)
			printf("Reg0x%x:0x%x\r\n",i,array[i]);
		}
		else printf("Read failed!\r\n");
}

//
//����2�������������κ�IIC�豸
//

/*
*********************************************************************************************************
*	�� �� ��: IIC_WriteBytes
*	����˵��: ��ָ����ַд���������ݣ�����ҳд�������д��Ч��
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 _usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 _pWriteBuf : ���Ҫд�����ݵĻ�����ָ��
*	�� �� ֵ: 0 ��ʾʧ�ܣ�1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t IIC_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize)
{
	uint16_t i,m;
	uint16_t usAddr;
	

	usAddr = _usAddress;	
	for (i = 0; i < _usSize; i++)
	{
		/* �����͵�1���ֽڻ���ҳ���׵�ַʱ����Ҫ���·��������źź͵�ַ */
		if (i == 0)
		{
			/*���ڣ�������ֹͣ�źţ������ڲ�д������*/
			i2c_Stop();
			
			/* ͨ���������Ӧ��ķ�ʽ���ж��ڲ�д�����Ƿ����, һ��С�� 10ms 			
				CLKƵ��Ϊ200KHzʱ����ѯ����Ϊ30������
			*/
			for (m = 0; m < 100; m++)
			{				
				/* ��1��������I2C���������ź� */
				i2c_Start();
				
				/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
				i2c_SendByte(DS3231_ADDRESS | I2C_WR);	/* �˴���дָ�� */
				
				/* ��3��������һ��ʱ�ӣ��ж������Ƿ���ȷӦ�� */
				if (i2c_WaitAck() == 0)
				{
					break;
				}
			}
			if (m  == 1000)
			{
				goto cmd_fail;	/* д��ʱ */
			}
		
			/* ��4���������ֽڵ�ַ*/
			i2c_SendByte((uint8_t)usAddr);
			
			/* ��5��������ACK */
			if (i2c_WaitAck() != 0)
			{
				goto cmd_fail;	/* EEPROM������Ӧ�� */
			}
		}
	
		/* ��6������ʼд������ */
		i2c_SendByte(_pWriteBuf[i]);
	
		/* ��7��������ACK */
		if (i2c_WaitAck() != 0)
		{
			goto cmd_fail;	/* EEPROM������Ӧ�� */
		}

		usAddr++;	/* ��ַ��1 */		
	}
	
	/* ����ִ�гɹ�������I2C����ֹͣ�ź� */
	i2c_Stop();
	return 1;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: IIC_ReadBytes
*	����˵��: ��ָ����ַ����ʼ��ȡ��������
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 _usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 _pReadBuf : ��Ŷ��������ݵĻ�����ָ��
*	�� �� ֵ: 0 ��ʾʧ�ܣ�1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t IIC_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize)
{
	uint16_t i;
	
	/* ��1��������I2C���������ź� */
	i2c_Start();
	
	/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_SendByte(DS3231_ADDRESS | I2C_WR);	/* �˴���дָ�� */
	
	/* ��3��������ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* ������Ӧ�� */
	}

	/* ��4���������ֽڵ�ַ*/
	i2c_SendByte((uint8_t)_usAddress);
	
	/* ��5��������ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/*������Ӧ�� */
	}
	
	/* ��6������������I2C���ߡ�ǰ��Ĵ����Ŀ����EEPROM���͵�ַ�����濪ʼ��ȡ���� */
	i2c_Start();
	
	/* ��7������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	i2c_SendByte(DS3231_ADDRESS | I2C_RD);	/* �˴��Ƕ�ָ�� */
	
	/* ��8��������ACK */
	if (i2c_WaitAck() != 0)
	{
		goto cmd_fail;	/* ������Ӧ�� */
	}	
	
	/* ��9����ѭ����ȡ���� */
	for (i = 0; i < _usSize; i++)
	{
		_pReadBuf[i] = i2c_ReadByte();	/* ��1���ֽ� */
		
		/* ÿ����1���ֽں���Ҫ����Ack�� ���һ���ֽڲ���ҪAck����Nack */
		if (i != _usSize - 1)
		{
			i2c_Ack();	/* �м��ֽڶ����CPU����ACK�ź�(����SDA = 0) */
		}
		else
		{
			i2c_NAck();	/* ���1���ֽڶ����CPU����NACK�ź�(����SDA = 1) */
		}
	}
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 1;	/* ִ�гɹ� */

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	i2c_Stop();
	return 0;
}


/************************************end of file 2014-08-08*********************************/
