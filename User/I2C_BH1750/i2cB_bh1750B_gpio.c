
#include "./i2c_BH1750/i2cB_bh1750B_gpio.h"


static void i2cB_BH1750B_GPIOConfig(void);

static void i2cB_Delay(void)
{
	uint8_t i;

	for (i = 0; i < 10; i++);
}

void i2cB_Start(void)
{
	BH1750B_i2cB_SDA_1();
	BH1750B_i2cB_SCL_1();
	i2cB_Delay();
	BH1750B_i2cB_SDA_0();
	i2cB_Delay();
	BH1750B_i2cB_SCL_0();
	i2cB_Delay();
}

void i2cB_Stop(void)
{
	BH1750B_i2cB_SDA_0();
	BH1750B_i2cB_SCL_1();
	i2cB_Delay();
	BH1750B_i2cB_SDA_1();
}

void i2cB_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			BH1750B_i2cB_SDA_1();
		}
		else
		{
			BH1750B_i2cB_SDA_0();
		}
		i2cB_Delay();
		BH1750B_i2cB_SCL_1();
		i2cB_Delay();	
		BH1750B_i2cB_SCL_0();
		if (i == 7)
		{
			 BH1750B_i2cB_SDA_1(); 
		}
		_ucByte <<= 1;	
		i2cB_Delay();
	}
}

uint8_t i2cB_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		BH1750B_i2cB_SCL_1();
		i2cB_Delay();
		if (BH1750B_i2cB_SDA_READ())
		{
			value++;
		}
		BH1750B_i2cB_SCL_0();
		i2cB_Delay();
	}
	return value;
}

uint8_t i2cB_WaitAck(void)
{
	uint8_t re;

	BH1750B_i2cB_SDA_1();	
	i2cB_Delay();
	BH1750B_i2cB_SCL_1();	
	i2cB_Delay();
	if (BH1750B_i2cB_SDA_READ())	
		re = 1;
	else
		re = 0;
	BH1750B_i2cB_SCL_0();
	i2cB_Delay();
	return re;
}

void i2cB_Ack(void)
{
	BH1750B_i2cB_SDA_0();	
	i2cB_Delay();
	BH1750B_i2cB_SCL_1();	
	i2cB_Delay();
	BH1750B_i2cB_SCL_0();
	i2cB_Delay();
	BH1750B_i2cB_SDA_1();	
}

void i2cB_NAck(void)
{
	BH1750B_i2cB_SDA_1();	
	i2cB_Delay();
	BH1750B_i2cB_SCL_1();	
	i2cB_Delay();
	BH1750B_i2cB_SCL_0();
	i2cB_Delay();	
}

static void i2cB_BH1750B_GPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BH1750B_RCC_i2cB_PORT, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = BH1750B_i2cB_SCL_PIN | BH1750B_i2cB_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	
	GPIO_Init(BH1750B_GPIO_PORT_i2cB, &GPIO_InitStructure);

	i2cB_Stop();
}

uint8_t i2cB_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	i2cB_BH1750B_GPIOConfig();		

	i2cB_Start();		

	i2cB_SendByte(_Address | BH1750B_i2cB_WR);
	ucAck = i2cB_WaitAck();	

	i2cB_Stop();			

	return ucAck;
}
