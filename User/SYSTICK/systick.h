#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f10x.h"
#include "core_cm3.h"

void SysTick_Delay_ms(uint32_t ms);
void SysTick_Delay_us(uint32_t us);
void SysTick_TI_Init(void);
void Delay_ms(uint32_t ms);

#endif	/* _SYSTICK_H_ */

