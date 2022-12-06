#ifndef __i2cB_GPIO_H
#define __i2cB_GPIO_H

#include "stm32f10x.h"

#define BH1750B_i2cB_WR	0		
#define BH1750B_i2cB_RD	1		


#define BH1750B_GPIO_PORT_i2cB	GPIOB			
#define BH1750B_RCC_i2cB_PORT 	RCC_APB2Periph_GPIOB		
#define BH1750B_i2cB_SCL_PIN		GPIO_Pin_14	
#define BH1750B_i2cB_SDA_PIN		GPIO_Pin_15



#if 0	
	#define BH1750B_i2cB_SCL_1()  GPIO_SetBits(BH1750B_GPIO_PORT_i2cB, BH1750B_i2cB_SCL_PIN)		
	#define BH1750B_i2cB_SCL_0()  GPIO_ResetBits(BH1750B_GPIO_PORT_i2cB, BH1750B_i2cB_SCL_PIN)		
	
	#define BH1750B_i2cB_SDA_1()  GPIO_SetBits(BH1750B_GPIO_PORT_i2cB, BH1750B_i2cB_SDA_PIN)		
	#define BH1750B_i2cB_SDA_0()  GPIO_ResetBits(BH1750B_GPIO_PORT_i2cB, BH1750B_i2cB_SDA_PIN)		
	
	#define BH1750B_i2cB_SDA_READ()  GPIO_ReadInputDataBit(BH1750B_GPIO_PORT_i2cB, BH1750B_i2cB_SDA_PIN)	
#else	
	#define BH1750B_i2cB_SCL_1()  BH1750B_GPIO_PORT_i2cB->BSRR = BH1750B_i2cB_SCL_PIN				
	#define BH1750B_i2cB_SCL_0()  BH1750B_GPIO_PORT_i2cB->BRR = BH1750B_i2cB_SCL_PIN				
	
	#define BH1750B_i2cB_SDA_1()  BH1750B_GPIO_PORT_i2cB->BSRR = BH1750B_i2cB_SDA_PIN				
	#define BH1750B_i2cB_SDA_0()  BH1750B_GPIO_PORT_i2cB->BRR = BH1750B_i2cB_SDA_PIN				
	
	#define BH1750B_i2cB_SDA_READ()  ((BH1750B_GPIO_PORT_i2cB->IDR & BH1750B_i2cB_SDA_PIN) != 0)	
#endif


void i2cB_Start(void);
void i2cB_Stop(void);
void i2cB_SendByte(uint8_t _ucByte);
uint8_t i2cB_ReadByte(void);
uint8_t i2cB_WaitAck(void);
void i2cB_Ack(void);
void i2cB_NAck(void);
uint8_t i2cB_CheckDevice(uint8_t _Address);


#endif

