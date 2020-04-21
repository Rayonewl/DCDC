#ifndef __PID_H
#define __PID_H	 
#include "sys.h"
typedef struct PI            //定义电压控制结构体PI
{
  float Setpoint;            //基准值
  float SumError;            //误差积累，积分项
  float I;               	 //积分系数
  float Kp;                  //比例系数
  float Errors[10];          //误差队列
  float Dead_error;          //积分累积死区
}PI;

void PI_init(PI *pi,float setpoint,float kp,float I0,float dead_error);
float PI_Calc(PI *p,float nextpoint);
float PI2_Calc(PI *p,float vi1,float vi2);
void getinf(void);
void display(void);
void SCISendInt(int pnum);
void Send_picture(void) ;

#endif
