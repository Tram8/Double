#include "./i2c_BH1750/i2cB_bh1750B.h"

uint8_t BH1750B_Byte_Write(uint8_t data)
{
	i2cB_Start();
	i2cB_SendByte(BH1750B_Addr|0);
	if(i2cB_WaitAck()==1)
		return 1;
	i2cB_SendByte(data);
	if(i2cB_WaitAck()==1)
		return 2;
	i2cB_Stop();
	return 0;
}

uint16_t BH1750B_Read_Measure(void)
{
	uint16_t receive_data=0; 
	i2cB_Start();
	i2cB_SendByte(BH1750B_Addr|1);
	if(i2cB_WaitAck()==1)
		return 0;
	receive_data=i2cB_ReadByte();
	i2cB_Ack();
	receive_data=(receive_data<<8)+i2cB_ReadByte();
	i2cB_NAck();
	i2cB_Stop();
	return receive_data;	
}

void BH1750B_Power_ON(void)
{
	BH1750B_Byte_Write(POWER_ON);
}

void BH1750B_Power_OFF(void)
{
	BH1750B_Byte_Write(POWER_OFF);
}

void BH1750B_RESET(void)
{
	BH1750B_Byte_Write(MODULE_RESET);
}

void BH1750B_Init(void)
{
	BH1750B_Power_ON();	
	BH1750B_Byte_Write(Measure_Mode);
	SysTick_Delay_ms(120);
}

float LIghtB_Intensity(void)
{
	return (float)(BH1750B_Read_Measure()/1.2f*Resolurtion);
}
