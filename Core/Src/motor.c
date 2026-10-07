//
// Created by 86188 on 2026/10/2.
//
#include "main.h"
#include "motor.h"

//
//这是最基本的电机驱动，后期对带编码器的要加入测角度测速以及DMA
//
//PWM的ARR设定为1000
//


void Motor_Init(motor *motor,TIM_HandleTypeDef *htim,uint32_t channel,GPIO_TypeDef  *IN1_Port,uint16_t IN1_Pin,GPIO_TypeDef *IN2_Port,uint16_t IN2_Pin){

    motor->htim=htim;
    motor->channel=channel;

    motor->IN1_Port=IN1_Port;
    motor->IN1_Pin=IN1_Pin;
    motor->IN2_Port=IN2_Port;
    motor->IN2_Pin=IN2_Pin;

    HAL_TIM_PWM_Start(motor->htim,motor->channel);

}


void Motor_PWM_Set(motor *motor,int need) {

    if (need>100){need=100;}else if (need<-100){need=-100;}

    motor->PWM_SET=need*10;
}


void Motor_Start(motor *motor) {

    if (motor->PWM_SET>0) {
        HAL_GPIO_WritePin(motor->IN1_Port,motor->IN1_Pin,GPIO_PIN_SET);         //引脚的高低需要进一步改动
        HAL_GPIO_WritePin(motor->IN2_Port,motor->IN2_Pin,GPIO_PIN_RESET);
    }else if(motor->PWM_SET<0) {
        HAL_GPIO_WritePin(motor->IN1_Port,motor->IN1_Pin,GPIO_PIN_RESET);         //引脚的高低需要进一步改动
        HAL_GPIO_WritePin(motor->IN2_Port,motor->IN2_Pin,GPIO_PIN_SET);
    }else if(motor->PWM_SET==0) {
        HAL_GPIO_WritePin(motor->IN1_Port,motor->IN1_Pin,GPIO_PIN_RESET);         //引脚的高低需要进一步改动
        HAL_GPIO_WritePin(motor->IN2_Port,motor->IN2_Pin,GPIO_PIN_RESET);
    }


    uint16_t PWM_Set;
    if (motor->PWM_SET<0) {PWM_Set=-(motor->PWM_SET);}else{PWM_Set=(motor->PWM_SET);}

    __HAL_TIM_SET_COMPARE(motor->htim,motor->channel,PWM_Set);
}
















