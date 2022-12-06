#ifndef __BH1750A_i2cA_H
#define __BH1750A_i2cA_H

#include "stm32f10x.h"
#include "./i2c_BH1750/i2cA_bh1750A_gpio.h"
#include "./SYSTICK/systick.h"

//BH1750A�ĵ�ַ
#define BH1750A_Addr				0x46  //H B8  L 46

//BH1750Aָ����
#define POWER_OFF					0x00
#define POWER_ON					0x01
#define MODULE_RESET			0x07
#define	CONTINUE_H_MODE		0x10
#define CONTINUE_H_MODE2	0x11
#define CONTINUE_L_MODE		0x13
#define ONE_TIME_H_MODE		0x20
#define ONE_TIME_H_MODE2	0x21
#define ONE_TIME_L_MODE		0x23

//����ģʽ
#define Measure_Mode			CONTINUE_H_MODE2

//�ֱ���	����ǿ�ȣ���λlx��=��High Byte  + Low Byte��/ 1.2 * ��������
#if ((Measure_Mode==CONTINUE_H_MODE2)|(Measure_Mode==ONE_TIME_H_MODE2))
	#define Resolurtion		1  //0.5
#elif ((Measure_Mode==CONTINUE_H_MODE)|(Measure_Mode==ONE_TIME_H_MODE))
	#define Resolurtion		1  //1
#elif ((Measure_Mode==CONTINUE_L_MODE)|(Measure_Mode==ONE_TIME_L_MODE))
	#define Resolurtion		1  //4
#endif

void BH1750A_Init(void);			//δ����IIC��ʼ��
float LIghtA_Intensity(void);	//��ȡ����ǿ�ȵ�ֵ
uint8_t BH1750A_Byte_Write(uint8_t data);
uint16_t BH1750A_Read_Measure(void);
void BH1750A_Power_ON(void);
void BH1750A_Power_OFF(void);
void BH1750A_RESET(void);

#endif /* __BH1750A_i2cA_H */

