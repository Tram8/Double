#ifndef __I2C_GPIO_H
#define __I2C_GPIO_H

#include "stm32f10x.h"

#define BH1750B_I2C_WR	0		
#define BH1750B_I2C_RD	1		


#define BH1750B_GPIO_PORT_I2C	GPIOB			
#define BH1750B_RCC_I2C_PORT 	RCC_APB2Periph_GPIOB		
#define BH1750B_I2C_SCL_PIN		GPIO_Pin_12			
#define BH1750B_I2C_SDA_PIN		GPIO_Pin_13			



#if 0	
	#define BH1750B_I2C_SCL_1()  GPIO_SetBits(BH1750B_GPIO_PORT_I2C, BH1750B_I2C_SCL_PIN)		
	#define BH1750B_I2C_SCL_0()  GPIO_ResetBits(BH1750B_GPIO_PORT_I2C, BH1750B_I2C_SCL_PIN)		
	
	#define BH1750B_I2C_SDA_1()  GPIO_SetBits(BH1750B_GPIO_PORT_I2C, BH1750B_I2C_SDA_PIN)		
	#define BH1750B_I2C_SDA_0()  GPIO_ResetBits(BH1750B_GPIO_PORT_I2C, BH1750B_I2C_SDA_PIN)		
	
	#define BH1750B_I2C_SDA_READ()  GPIO_ReadInputDataBit(BH1750B_GPIO_PORT_I2C, BH1750B_I2C_SDA_PIN)	
#else	
	#define BH1750B_I2C_SCL_1()  BH1750B_GPIO_PORT_I2C->BSRR = BH1750B_I2C_SCL_PIN				
	#define BH1750B_I2C_SCL_0()  BH1750B_GPIO_PORT_I2C->BRR = BH1750B_I2C_SCL_PIN				
	
	#define BH1750B_I2C_SDA_1()  BH1750B_GPIO_PORT_I2C->BSRR = BH1750B_I2C_SDA_PIN				
	#define BH1750B_I2C_SDA_0()  BH1750B_GPIO_PORT_I2C->BRR = BH1750B_I2C_SDA_PIN				
	
	#define BH1750B_I2C_SDA_READ()  ((BH1750B_GPIO_PORT_I2C->IDR & BH1750B_I2C_SDA_PIN) != 0)	
#endif


void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(void);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);


#endif

