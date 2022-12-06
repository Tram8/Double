
#include "./I2C_BH1750B/i2c_bh1750B_gpio.h"


static void I2C_BH1750B_GPIOConfig(void);

static void i2c_Delay(void)
{
	uint8_t i;

	for (i = 0; i < 10; i++);
}

void i2c_Start(void)
{
	BH1750B_I2C_SDA_1();
	BH1750B_I2C_SCL_1();
	i2c_Delay();
	BH1750B_I2C_SDA_0();
	i2c_Delay();
	BH1750B_I2C_SCL_0();
	i2c_Delay();
}

void i2c_Stop(void)
{
	BH1750B_I2C_SDA_0();
	BH1750B_I2C_SCL_1();
	i2c_Delay();
	BH1750B_I2C_SDA_1();
}

void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			BH1750B_I2C_SDA_1();
		}
		else
		{
			BH1750B_I2C_SDA_0();
		}
		i2c_Delay();
		BH1750B_I2C_SCL_1();
		i2c_Delay();	
		BH1750B_I2C_SCL_0();
		if (i == 7)
		{
			 BH1750B_I2C_SDA_1(); 
		}
		_ucByte <<= 1;	
		i2c_Delay();
	}
}

uint8_t i2c_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		BH1750B_I2C_SCL_1();
		i2c_Delay();
		if (BH1750B_I2C_SDA_READ())
		{
			value++;
		}
		BH1750B_I2C_SCL_0();
		i2c_Delay();
	}
	return value;
}

uint8_t i2c_WaitAck(void)
{
	uint8_t re;

	BH1750B_I2C_SDA_1();	
	i2c_Delay();
	BH1750B_I2C_SCL_1();	
	i2c_Delay();
	if (BH1750B_I2C_SDA_READ())	
		re = 1;
	else
		re = 0;
	BH1750B_I2C_SCL_0();
	i2c_Delay();
	return re;
}

void i2c_Ack(void)
{
	BH1750B_I2C_SDA_0();	
	i2c_Delay();
	BH1750B_I2C_SCL_1();	
	i2c_Delay();
	BH1750B_I2C_SCL_0();
	i2c_Delay();
	BH1750B_I2C_SDA_1();	
}

void i2c_NAck(void)
{
	BH1750B_I2C_SDA_1();	
	i2c_Delay();
	BH1750B_I2C_SCL_1();	
	i2c_Delay();
	BH1750B_I2C_SCL_0();
	i2c_Delay();	
}

static void I2C_BH1750B_GPIOConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BH1750B_RCC_I2C_PORT, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = BH1750B_I2C_SCL_PIN | BH1750B_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  	
	GPIO_Init(BH1750B_GPIO_PORT_I2C, &GPIO_InitStructure);

	i2c_Stop();
}

uint8_t i2c_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	I2C_BH1750B_GPIOConfig();		

	i2c_Start();		

	i2c_SendByte(_Address | BH1750B_I2C_WR);
	ucAck = i2c_WaitAck();	

	i2c_Stop();			

	return ucAck;
}
