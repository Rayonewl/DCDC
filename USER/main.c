#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"	
#include "adc.h"
#include "oled.h"
#include "Adjust.h"
#include "exti.h"
u8 key;
u8 Uo,Io;
u16 Duty;
u16 adcx;
float U_T,I_T;
extern u16 output;
PI U,I,*puz=&U,*piz=&I;
u16 stopcif;
u16 modecif_flag,modecif;//modecif = 0；充电模式 BUCk
						 //modecif = 1；放电模式 BOOST

void KEY_SET(void);
float I_Test(void);
float U_Test(void);

 int main(void)
 {	
	 float temp=0;
	delay_init();	 		 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	     //串口初始化为115200
 	LED_Init();			     //LED端口初始化
	Adc1_Init();
	KEY_Init();
	OLED_Init();			 //初始化OLED  
	OLED_Clear();
 	TIM3_PWM_Init(2399,0);	 //不分频。PWM频率=72000000/1800=30Khz
	TIM4_Int_Init(9999,71);
	PI_init(piz,1.000,250.0,20,200.000);//充电电流
	PI_init(puz,6.000,50.0,0,10.000);	//放电电压
	//初始化显示
	OLED_ShowString(0,0,"D:  %",16);
	OLED_ShowString(80,0,"MODE: ",16);
	OLED_ShowString(0,2,"U_T:00.00",16);
	OLED_ShowString(0,4,"I_T:0.00",16);
	OLED_ShowString(80,2,"Uo:00",16);
	OLED_ShowString(72,4,"Io:0.00",16);
	OLED_ShowNum(120,0,modecif,1,16);
   	while(1)
	{	
		KEY_SET();
		Duty = ((float)(output+1)/2400)*100;
		OLED_ShowNum(16,0,Duty,2,16);
		I_T = I_Test();							//输出电流检测
		U_T = U_Test();							//输出电压检测
		OLED_ShowNum(120,0,modecif,1,16);		//显示模式
		OLED_ShowNum(104,2,U.Setpoint,2,16);	//显示设定值
		temp = I.Setpoint;
		OLED_ShowNum(96,4,temp,1,16);	//显示设定值
		temp = (int)(I.Setpoint*10)%10;
		OLED_ShowNum(112,4,temp,1,16);	//显示设定值
		temp = (int)(I.Setpoint*100)%100;
		OLED_ShowNum(120,4,temp,1,16);	//显示设定值
	}	 
 }

 //电压检测
 float U_Test(void)
 {
	float temp_U=0;
	adcx=ADC_filter(ADC_Channel_2);
	temp_U=(float)adcx*(3.3/4096)*11;
	U_T = temp_U;
	OLED_ShowNum(32,2,temp_U,2,16);
	temp_U = (int)(temp_U*100)%100;
	OLED_ShowNum(56,2,temp_U,2,16);
	return U_T;
 }
 

//电流检测
 float I_Test(void)
 {
	float temp_I=0;
	adcx=ADC_filter(ADC_Channel_1); 
	temp_I = (float)adcx*(3.3/4096);
	temp_I = (temp_I-2.5)/0.185;
	I_T = temp_I;
	OLED_ShowNum(32,4,temp_I,1,16);
	temp_I = (int)(I_T*100)%100;
	OLED_ShowNum(48,4,temp_I,2,16);
	return I_T;
 } 
 
//电压稳压值和模式设定
void KEY_SET(void)
{
	key = KEY_Scan(0);
	if(key==KEY1_PRES)	 
	{		
		if(0==KEY1)
		{
			if(modecif==0)
			{
				if(I.Setpoint<2)
					I.Setpoint+=0.050001;
			}
			else if(modecif==1||modecif==2)
			{
				if(U.Setpoint<30)
					U.Setpoint+=1;
			}
		}
	}
	
	else if(key==KEY2_PRES)	 
	{	
		if(0==KEY2)
		{
			if(modecif==0)
			{
				if(I.Setpoint>0)
				I.Setpoint-=0.050001;
			}
			else if(modecif==1||modecif==2)
			{
				if(U.Setpoint>0)
				U.Setpoint-=1;
			
			}

		}
	}
	else if(key==KEY3_PRES)	 
	{	
		if(0==KEY3)
		{				
			modecif_flag++;
			modecif = modecif_flag%3;
		}
	}
}

