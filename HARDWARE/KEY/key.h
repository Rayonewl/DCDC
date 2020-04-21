#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 
/*
 * K1 -> PC15   K2 -> PA0
 * K3 -> PC14   K4 -> PC13
 */

//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)		//PE3 
//#define KEY2 PEin(2)		//PE2
//#define WK_UP PAin(0)		//PA0  WK_UP

#define KEY1  	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//读取按键0
#define KEY2  	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键1
#define KEY3  	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//读取按键2 
#define KEY4    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//读取按键3(WK_UP) 
#define KEY5    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取按键3(WK_UP) 
#define KEY6    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//读取按键3(WK_UP)  

#define KEY1_PRES 	1	//KEY0按下
#define KEY2_PRES	2	//KEY1按下
#define KEY3_PRES	3	//KEY2按下
#define KEY4_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)
#define KEY5_PRES   5	//KEY_UP按下(即WK_UP/KEY_UP)
#define KEY6_PRES   6	//KEY_UP按下(即WK_UP/KEY_UP)

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
