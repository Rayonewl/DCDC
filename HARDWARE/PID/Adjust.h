#ifndef __PID_H
#define __PID_H	 
#include "sys.h"
typedef struct PI            //�����ѹ���ƽṹ��PI
{
  float Setpoint;            //��׼ֵ
  float SumError;            //�����ۣ�������
  float I;               	 //����ϵ��
  float Kp;                  //����ϵ��
  float Errors[10];          //������
  float Dead_error;          //�����ۻ�����
}PI;

void PI_init(PI *pi,float setpoint,float kp,float I0,float dead_error);
float PI_Calc(PI *p,float nextpoint);
float PI2_Calc(PI *p,float vi1,float vi2);
void getinf(void);
void display(void);
void SCISendInt(int pnum);
void Send_picture(void) ;

#endif
