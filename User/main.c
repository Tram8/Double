#include "stm32f10x.h"
#include "./USART/usart.h"
#include "./SYSTICK/systick.h"
#include "./I2C_BH1750/i2cA_bh1750A_gpio.h"
#include "./I2C_BH1750/i2cA_bh1750A.h"
#include "./I2C_BH1750/i2cB_bh1750B_gpio.h"
#include "./I2C_BH1750/i2cB_bh1750B.h"
#include "./OLED/OLED.h"
#include "./Encoder/Encoder.h"
//#include "./Moto/Moto.h"
#include "./step/step.h"

u8 page;
float data[8];
int main(void)
{
	
	OLED_Init();
	
	Encoder_Init();
	
	BH1750A_Init();
	BH1750B_Init();
	

	
	USART_Config();
	
	
	
	if(i2cA_CheckDevice(BH1750A_Addr)==0)
  printf("BH1750A设备检测成功\r\n");
  else printf("BH1750A设备检测失败\r\n");
	BH1750A_Init();
	//printf("光照强度传感器实验\r\n");
	
	if(i2cB_CheckDevice(BH1750B_Addr)==0)
  printf("BH1750B设备检测成功\r\n");
  else printf("BH1750B设备检测失败\r\n");
	BH1750B_Init();
	//printf("光照强度传感器实验\r\n");
	
	 OLED_ShowString(1,1,"Loading...");
   SysTick_Delay_ms(1000);
	 OLED_ShowString(1,1,"Loading1...");
		
		for(u8 i=0 ; i<4 ; i++ ){
			
		data[i]=LIghtA_Intensity();
			
	  SysTick_Delay_ms(300);}
		
		
		OLED_ShowString(1,1,"Loading...");
    SysTick_Delay_ms(1500);
		OLED_ShowString(1,1,"Loading2...");
		
		for(u8 i=4 ; i<8 ; i++ ){
			
		data[i]=LIghtB_Intensity();
			
	  SysTick_Delay_ms(300);}
		
		OLED_Clear();
	 while(1){
		
	while(1){
		
		page -= Encoder_Get();
		if(page<1||page>3)			page=1;
		OLED_ShowString(1,12,"PG");
		OLED_ShowNum(1, 15, page, 1);
		
	 
		
		if(page ==1 ){	
	
		OLED_ShowNum(1, 1, data[0], 6); 
		
		OLED_ShowNum(2, 1, data[1], 6); 
		
		OLED_ShowNum(3, 1, data[2], 6); 
		
		OLED_ShowNum(4, 1, data[3], 6); 
		OLED_ShowString(1,8,"Lx");		
		OLED_ShowString(2,8,"Lx");		
		OLED_ShowString(3,8,"Lx");		
		OLED_ShowString(4,8,"Lx");}
		
		if(page==2){
	  
		OLED_ShowNum(1, 1, data[4], 6); 
		
		OLED_ShowNum(2, 1, data[5], 6); 
		
		OLED_ShowNum(3, 1, data[6], 6); 
		
		OLED_ShowNum(4, 1, data[7], 6); 
		OLED_ShowString(1,8,"Lx");		
		OLED_ShowString(2,8,"Lx");		
		OLED_ShowString(3,8,"Lx");		
		OLED_ShowString(4,8,"Lx");}
    if(page==3)
			break;
	}
	while(1)
	{
		OLED_ShowNum(1, 1, LIghtA_Intensity(), 6); 
		OLED_ShowString(1,8,"Lx");
		OLED_ShowString(2,1,"IO    1  ");
		//OLED_ShowString(2,8,"Lx");
		OLED_ShowNum(3, 1, LIghtB_Intensity(), 6); 
		OLED_ShowString(3,8,"Lx");
		OLED_ShowString(4,1,"IO    2  ");
		//OLED_ShowString(4,8,"Lx");
		
		printf("光强A：%f lx\r\n",LIghtA_Intensity());
		printf("光强B：%f lx\r\n",LIghtB_Intensity());
		
		SysTick_Delay_ms(500);
		
		page -= Encoder_Get();
		if(page<1||page>3)			page=1;
		OLED_ShowString(1,12,"PG");
		OLED_ShowNum(1, 15, page, 1);
		
		if(page==1|page==2)
			break;
	}	
}
}
	
	/*while(1)
	{
		//printf("光强：%f lx\r\n",LIghtA_Intensity());
		OLED_ShowNum(1, 1, LIghtA_Intensity(), 6); 
		OLED_ShowString(1,8,"Lx");
		OLED_ShowNum(2, 1, LIghtA_Intensity(), 6); 
		OLED_ShowString(2,8,"Lx");
		OLED_ShowNum(3, 1, LIghtA_Intensity(), 6); 
		OLED_ShowString(3,8,"Lx");
		OLED_ShowNum(4, 1, LIghtA_Intensity(), 6); 
		OLED_ShowString(4,8,"Lx");
		
		page -= Encoder_Get();
		OLED_ShowNum(1, 13, page, 3);
		
		SysTick_Delay_ms(500);
	}*/


