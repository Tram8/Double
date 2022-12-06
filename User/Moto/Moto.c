#include "stm32f10x.h" 
#include "stdio.h"
#include "./SYSTICK/systick.h"


unsigned short phasecw[4] ={0x0200,0x0100,0x0080,0x0040};// D-C-B-A   
unsigned short phaseccw[4]={0x0040,0x0080,0x0100,0x0200};// A-B-C-D   


void Moto_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3 ;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	 GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 );
}
void MotoRcw(void)  
{  
    int  i;  
  
    for(i=0;i<4;i++)  
    {  
        GPIO_Write(GPIOA,phasecw[i]);  
        SysTick_Delay_ms(3);  
			
    }  
}

void MotoRccw(void)  
{  
    int i;  
    for(i=0;i<4;i++)  
    {  
        GPIO_Write(GPIOA,phaseccw[i]);  
        SysTick_Delay_ms(3);  
    }  
}

void MotorStop(void) 
{  
    GPIO_Write(GPIOA,0x0000);  
}


//direction 1
//angle 0-360
void Motor_Ctrl_Direction_Angle(int direction, int angle)
{
	u16 j;
	if(direction == 1)
	{
		for(j=0;j<64*angle/45;j++) 
		{
			MotoRccw();
		}
		 MotorStop();
  }
	else
	{
		for(j=0;j<64*angle/45;j++) 
		{
			MotoRcw();
		}
		 MotorStop();
	}
}

/*int main(void)
 {	
	Moto_Init();	   			
	Delay_init();	    	 
	Motor_Ctrl_Direction_Angle(1,180);//180
	SysTick_Delay_ms(500);
	Motor_Ctrl_Direction_Angle(0,90);//90
	while(1)
	{
	}
 }*/

