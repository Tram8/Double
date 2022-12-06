#ifndef __i2cA_GPIO_H
#define __i2cA_GPIO_H

#include "stm32f10x.h"

#define BH1750A_i2cA_WR	0		/* д����bit */
#define BH1750A_i2cA_RD	1		/* ������bit */


/* ����i2cA�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */
#define BH1750A_GPIO_PORT_i2cA	GPIOB			/* GPIO�˿� */
#define BH1750A_RCC_i2cA_PORT 	RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define BH1750A_i2cA_SCL_PIN		GPIO_Pin_12			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define BH1750A_i2cA_SDA_PIN		GPIO_Pin_13			/* ���ӵ�SDA�����ߵ�GPIO */


/* �����дSCL��SDA�ĺ꣬�����Ӵ���Ŀ���ֲ�ԺͿ��Ķ��� */
#if 0	/* �������룺 1 ѡ��GPIO�Ŀ⺯��ʵ��IO��д */
	#define BH1750A_i2cA_SCL_1()  GPIO_SetBits(BH1750A_GPIO_PORT_i2cA, BH1750A_i2cA_SCL_PIN)		/* SCL = 1 */
	#define BH1750A_i2cA_SCL_0()  GPIO_ResetBits(BH1750A_GPIO_PORT_i2cA, BH1750A_i2cA_SCL_PIN)		/* SCL = 0 */
	
	#define BH1750A_i2cA_SDA_1()  GPIO_SetBits(BH1750A_GPIO_PORT_i2cA, BH1750A_i2cA_SDA_PIN)		/* SDA = 1 */
	#define BH1750A_i2cA_SDA_0()  GPIO_ResetBits(BH1750A_GPIO_PORT_i2cA, BH1750A_i2cA_SDA_PIN)		/* SDA = 0 */
	
	#define BH1750A_i2cA_SDA_READ()  GPIO_ReadInputDataBit(BH1750A_GPIO_PORT_i2cA, BH1750A_i2cA_SDA_PIN)	/* ��SDA����״̬ */
#else	/* �����֧ѡ��ֱ�ӼĴ�������ʵ��IO��д */
    /*��ע�⣺����д������IAR��߼����Ż�ʱ���ᱻ�����������Ż� */
	#define BH1750A_i2cA_SCL_1()  BH1750A_GPIO_PORT_i2cA->BSRR = BH1750A_i2cA_SCL_PIN				/* SCL = 1 */
	#define BH1750A_i2cA_SCL_0()  BH1750A_GPIO_PORT_i2cA->BRR = BH1750A_i2cA_SCL_PIN				/* SCL = 0 */
	
	#define BH1750A_i2cA_SDA_1()  BH1750A_GPIO_PORT_i2cA->BSRR = BH1750A_i2cA_SDA_PIN				/* SDA = 1 */
	#define BH1750A_i2cA_SDA_0()  BH1750A_GPIO_PORT_i2cA->BRR = BH1750A_i2cA_SDA_PIN				/* SDA = 0 */
	
	#define BH1750A_i2cA_SDA_READ()  ((BH1750A_GPIO_PORT_i2cA->IDR & BH1750A_i2cA_SDA_PIN) != 0)	/* ��SDA����״̬ */
#endif


void i2cA_Start(void);
void i2cA_Stop(void);
void i2cA_SendByte(uint8_t _ucByte);
uint8_t i2cA_ReadByte(void);
uint8_t i2cA_WaitAck(void);
void i2cA_Ack(void);
void i2cA_NAck(void);
uint8_t i2cA_CheckDevice(uint8_t _Address);


#endif

