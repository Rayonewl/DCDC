#include "Adjust.h"
#include "led.h"
#include "adc.h"
#include "delay.h"
#include "usart.h"

void PI_init(PI *pi,float setpoint,float kp,float I0,float dead_error)     //初始化PI
{	
	u16 i=9;
	pi->Setpoint=setpoint;        
	pi->Kp=kp;
	pi->I=I0;
	pi->SumError=0;                                     //积分累积初始化为0
	pi->Dead_error=dead_error;
	while(i--)
    pi->Errors[i]=0;                                    //积分队列为零
}
float PI_Calc(PI *p,float nextpoint)					//电压控制计算
{
	float Error,U_error;                                //误差和反馈值
	u16 i=0;                                      
	Error=p->Setpoint-nextpoint;                		//实际误差
	if(p->SumError>p->Dead_error)           			//限制积分误差
		p->SumError=p->Dead_error;
	U_error=p->Kp*Error+p->I*p->SumError;   			//计算PI指
	p->SumError=p->SumError-p->Errors[9]+Error;         //重新计算积分误差，抛弃最早的

	while(i<9)
	{
		p->Errors[i+1]=p->Errors[i];                    //误差队列更新
		i++;
	}
	p->Errors[0]=Error;
	return U_error;                                     //返回PI值
}

