//
// Created by 86188 on 2026/9/21.
//
#include "main.h"
#include "PID.h"

//
//比较简单的PID  需要后续更新改进
//


//PID的初始化
void PID_Init(PID_TypeDef *PID,float Kp,float Ki,float Kd,float sp){
    PID->Kp = Kp;
    PID->Ki = Ki;
    PID->Kd = Kd;
    PID->sp = 0.0f;
    PID->CO_SET_MAX=3.4e+38f;
    PID->CO_SET_MIN=-3.4e+38f;
    PID->I_SET_MAX=3.4e+38f;
    PID->I_SET_MIN=-3.4e+38f;
}

//改变设定的值
void PID_Set_sp(PID_TypeDef *PID,float sp) {
    PID->sp = sp;
}

//PID计算输出结果
float PID_Compute(PID_TypeDef *PID,float fd) {
    float err=PID->sp-fd;//计算err

    uint64_t t_k=HAL_GetTick();
    float delatT=t_k-PID->t_k_1;//计算时间差


    float err_d=0.0f;
    float err_i=0.0f;
    //PID的初次启动复位
    if (PID->t_k_1!=0) {
         err_d=(err-PID->err_k_1)/delatT;//计算微分项
         err_i=PID->err_i_k_1+(PID->err_k_1+err)*delatT/2.0f;//计算积分项
    }



    if (err_i>PID->I_SET_MAX){err_i=PID->I_SET_MAX;}//积分限幅
    if (err_i<PID->I_SET_MIN){err_i=PID->I_SET_MIN;}



    //对CO进行计算
    float COp=PID->Kp*err;
    float COi=err_i*PID->Ki;
    float COd=PID->Kd*err_d;
    float CO=COp+COi+COd;

    if (CO>PID->CO_SET_MAX){CO=PID->CO_SET_MAX;}//输出限幅
    if (CO<PID->CO_SET_MIN){CO=PID->CO_SET_MIN;}

    //更新值
    PID->t_k_1=t_k;
    PID->err_k_1=err;
    PID->err_i_k_1=err_i;

    return CO;
}

//输出限幅
void PID_CO_SET(PID_TypeDef *PID,float COMAX,float COMIN) {
    PID->CO_SET_MAX=COMAX;
    PID->CO_SET_MIN=COMIN;
}

//积分限幅
void PID_I_SET(PID_TypeDef *PID,float IMAX,float IMIN) {
    PID->I_SET_MAX=IMAX;
    PID->I_SET_MIN=IMIN;
}

//PID的复位
void PID_Reset(PID_TypeDef *PID) {
    PID->t_k_1=0;
    PID->err_k_1=0.0f;
    PID->err_i_k_1=0.0f;
}








