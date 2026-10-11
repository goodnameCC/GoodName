//
// Created by 86188 on 2026/10/11.
//

#ifndef MOTOR_MECANUM_H
#define MOTOR_MECANUM_H
#include "main.h"
#include "motor.h"

//通过蓝牙接收x,y,w 在此函数进行不同轮子的速度结算 换算为占空比 然后在motor函数中输出给电机

void motor_mecanum(motor *motor1,motor *motor2,motor *motor3,motor *motor4,int x,int y,int w);


#endif //MOTOR_MECANUM_H
