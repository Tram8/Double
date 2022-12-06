#include "./SYSTICK/systick.h"

uint32_t TimingDelay = 0;

#if 0

static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* 超出重装在寄存器的值Reload value impossible */
                                                               
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* 设置重装在寄存器的值set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* 设置中断优先级set Priority for Cortex-M0 System Interrupts */
  SysTick->VAL   = 0;                                          /* 初始化counter的值为0 Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    /* 使能中断以及使能定时器 配置时钟为AHB的时钟 Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}

#endif

//延时us
void SysTick_Delay_us(uint32_t us)
{
	uint32_t i;
	SysTick_Config(72);			//t=72*(1/72M)=1us
	for(i=0;i<us;i++)
	{
		while(!(SysTick->CTRL&(1<<16)));			//读取标志位的值
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭定时器  使能关
}

//延时ms
void SysTick_Delay_ms(uint32_t ms)
{
	uint32_t i;
	SysTick_Config(72000);	//t=72000*(1/72M)=1ms
	for(i=0;i<ms;i++)
	{
		while(!(SysTick->CTRL&(1<<16)));			//读取标志位的值
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭定时器	使能关
}

void SysTick_TI_Init(void)					//使用中断进行ms延时初始化
{
	/* SystemFrequency / 1000    1ms中断一次
	* SystemFrequency / 100000	 10us中断一次
	* SystemFrequency / 1000000 1us中断一次
	*/
	SysTick_Config(SystemCoreClock/1000);
	
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;			// 关闭滴答定时器 
}

void Delay_ms(uint32_t ms)			//使用中断进行ms延时
{
	TimingDelay = ms;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;			// 使能滴答定时器 
	while(TimingDelay > 0);			//中断里面TimingDelay--
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;			// 关闭滴答定时器 
}

void Delay_us(uint32_t us)			//使用中断进行us延时
{
	TimingDelay = us;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;			// 使能滴答定时器 
	while(TimingDelay > 0);			//中断里面TimingDelay--
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;			// 关闭滴答定时器 
}

