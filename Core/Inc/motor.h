//
// Created by 86188 on 2026/10/2.
//

#ifndef MOTOR_MOTOR_H
#define MOTOR_MOTOR_H

#include "main.h"

typedef struct {

    TIM_HandleTypeDef *htim;
    uint32_t channel;

    int PWM_SET;

    GPIO_TypeDef *IN1_Port;
    uint16_t IN1_Pin;
    GPIO_TypeDef *IN2_Port;
    uint16_t IN2_Pin;

}motor;

void Motor_Init(motor *motor,TIM_HandleTypeDef *htim,uint32_t channel,GPIO_TypeDef *IN1_Port,uint16_t IN1_Pin,GPIO_TypeDef *IN2_Port,uint16_t IN2_Pin);

void Motor_PWM_Set(motor *motor,int need);

void Motor_Start(motor *motor);






#endif //MOTOR_MOTOR_H
