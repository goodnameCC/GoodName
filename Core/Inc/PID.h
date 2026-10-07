//
// Created by 86188 on 2026/9/21.
//

#ifndef PID_PID_H
#define PID_PID_H
#include "main.h"

typedef  struct {
    float Kp;
    float Ki;
    float Kd;
    float sp;
    uint64_t t_k_1;
    float err_k_1;
    float err_i_k_1;
    float CO_SET_MAX;
    float CO_SET_MIN;
    float I_SET_MAX;
    float I_SET_MIN;
}PID_TypeDef;

void PID_Init(PID_TypeDef *PID,float Kp,float Ki,float Kd,float sp);
void PID_Set_sp(PID_TypeDef *PID,float sp);
void PID_CO_SET(PID_TypeDef *PID,float COMAX,float COMIN);
void PID_I_SET(PID_TypeDef *PID,float IMAX,float IMIN);
void PID_Reset(PID_TypeDef *PID);



#endif //PID_PID_H
