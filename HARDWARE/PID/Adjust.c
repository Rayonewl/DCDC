#include "Adjust.h"
#include "led.h"
#include "adc.h"
#include "delay.h"
#include "usart.h"

void PI_init(PI *pi,float setpoint,float kp,float I0,float dead_error)     //��ʼ��PI
{	
	u16 i=9;
	pi->Setpoint=setpoint;        
	pi->Kp=kp;
	pi->I=I0;
	pi->SumError=0;                                     //�����ۻ���ʼ��Ϊ0
	pi->Dead_error=dead_error;
	while(i--)
    pi->Errors[i]=0;                                    //���ֶ���Ϊ��
}
float PI_Calc(PI *p,float nextpoint)					//��ѹ���Ƽ���
{
	float Error,U_error;                                //���ͷ���ֵ
	u16 i=0;                                      
	Error=p->Setpoint-nextpoint;                		//ʵ�����
	if(p->SumError>p->Dead_error)           			//���ƻ������
		p->SumError=p->Dead_error;
	U_error=p->Kp*Error+p->I*p->SumError;   			//����PIָ
	p->SumError=p->SumError-p->Errors[9]+Error;         //���¼�����������������

	while(i<9)
	{
		p->Errors[i+1]=p->Errors[i];                    //�����и���
		i++;
	}
	p->Errors[0]=Error;
	return U_error;                                     //����PIֵ
}

