#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

								    
//按键初始化函数、
/*
 * K1 PC15   K2 PA0
 * K3 PC14   K4 PC13
 */
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//初始化 K2-->GPIOA.0	 	 设置成上拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0设置成输入，默认上拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
	
	//初始化 PWM1-0-->GPIOB0\1	  设置成上拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0设置成输入，默认上拉	  
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA.0


}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY1按下
//2，KEY2按下
//3，KEY3按下 
//4，KEY4按下
//注意此函数有响应优先级,KEY1>KEY2>KEY3>KEY4!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)		return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
		else if(KEY5==0)return KEY5_PRES;
		else if(KEY6==0)return KEY6_PRES;
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1&&KEY6==1)key_up=1; 	    
 	return 0;// 无按键按下
}
