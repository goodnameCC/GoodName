//
// Created by 86188 on 2026/10/11.
//

#include "main.h"
#include "motor.h"
#include "Mecanum.h"
#include "USART_self.h"
#include "stdlib.h"



//
//我想通过蓝牙发送数据包  依次对应x,y,w   这样可以做一个控制速度的
//但是这要在后续改进  我就先只制作不控速的了
//
void motor_mecanum(motor *motor1,motor *motor2,motor *motor3,motor *motor4,int x,int y,int w){


    //每个轮子的状态
    int16_t f_l=0;
    int16_t f_r=0;
    int16_t b_l=0;
    int16_t b_r=0;

    //
    //后期要更改每个轮子加的数  这里不考虑速度的变化
    //

    f_l=y+x+w;
    f_r=y-x-w;
    b_l=y-x+w;
    b_r=y+x-w;

    //把结果转换为最大值为100
    //输入到每个电机的pwm

    int16_t max=abs(f_l);
    if (abs(f_r)>max) {max=abs(f_r);}
    if (abs(b_l)>max) {max=abs(b_l);}
    if (abs(b_r)>max) {max=abs(b_r);}

    if (max>100) {
        f_l=f_l*100/max;
        f_r=f_r*100/max;
        b_l=b_l*100/max;
        b_r=b_r*100/max;
    }

    Motor_PWM_Set(motor1,f_l);
    Motor_PWM_Set(motor2,f_r);
    Motor_PWM_Set(motor3,b_l);
    Motor_PWM_Set(motor4,b_r);

    Motor_Start(motor1);
    Motor_Start(motor2);
    Motor_Start(motor3);
    Motor_Start(motor4);
}









