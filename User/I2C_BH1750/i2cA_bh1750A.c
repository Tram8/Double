#include "./i2c_BH1750/i2cA_bh1750A.h"

//BH1750Aдһ���ֽ�
//����ֵ	�ɹ���0		ʧ�ܣ���0 
uint8_t BH1750A_Byte_Write(uint8_t data)
{
	i2cA_Start();
	//����д��ַ
	i2cA_SendByte(BH1750A_Addr|0);
	if(i2cA_WaitAck()==1)
		return 1;
	//���Ϳ�������
	i2cA_SendByte(data);
	if(i2cA_WaitAck()==1)
		return 2;
	i2cA_Stop();
	return 0;
}

//BH1750A��ȡ��������
//����ֵ �ɹ������ع���ǿ�� 	ʧ�ܣ�����0
uint16_t BH1750A_Read_Measure(void)
{
	uint16_t receive_data=0; 
	i2cA_Start();
	//���Ͷ���ַ
	i2cA_SendByte(BH1750A_Addr|1);
	if(i2cA_WaitAck()==1)
		return 0;
	//��ȡ�߰�λ
	receive_data=i2cA_ReadByte();
	i2cA_Ack();
	//��ȡ�Ͱ�λ
	receive_data=(receive_data<<8)+i2cA_ReadByte();
	i2cA_NAck();
	i2cA_Stop();
	return receive_data;	//���ض�ȡ��������
}


//BH1750As�ϵ�
void BH1750A_Power_ON(void)
{
	BH1750A_Byte_Write(POWER_ON);
}

//BH1750As�ϵ�
void BH1750A_Power_OFF(void)
{
	BH1750A_Byte_Write(POWER_OFF);
}

//BH1750A��λ	�����ϵ�ʱ��Ч
void BH1750A_RESET(void)
{
	BH1750A_Byte_Write(MODULE_RESET);
}

//BH1750A��ʼ��
void BH1750A_Init(void)
{
	BH1750A_Power_ON();	//BH1750As�ϵ�
	//BH1750A_RESET();			//BH1750A��λ
	BH1750A_Byte_Write(Measure_Mode);
	SysTick_Delay_ms(120);
}

//��ȡ����ǿ��
float LIghtA_Intensity(void)
{
	return (float)(BH1750A_Read_Measure()/1.2f*Resolurtion);
}
